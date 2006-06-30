/*  
Module : NTSERVSERVICECONTROLMANAGER.CPP
Purpose: Implementation for the class CNTServiceControlManager
Created: PJN / 14-07-1997
History: PJN / 11-01-2006 CNTServiceControlManager::EnumServices method now uses a void* parameter for its 
                          item data instead of a DWORD.

Copyright (c) 1996 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "ntservServiceControlManager.h"



////////////////////////////////// Macros / Defines ///////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Implementation //////////////////////////////


//Class which handles additional Windows 2000 service related calls, which 
//must be constructed at run time since they are not implemented on NT 4,
//only Windows 2000. To avoid the loader bringing up a message such as 
//"Failed to load due to missing export...", the function is constructed 
//using GetProcAddress. The CNTService methods which use these functions
//then checks to see if the function pointer is NULL and if it is it 
//returns FALSE from the function and sets the error code to 
//ERROR_CALL_NOT_IMPLEMENTED which is what NT would have done if it had 
//implemented a stub for it in the first place !!
//
//Note that I could have used VC 6's support for delay loading but this would
//mean that the code would not work on VC 5 which I aim to provide support
//for in my code.

class _NTSERV_SERVICCONTROLMANAGER_DATA
{
public:
//Constructors /Destructors
  _NTSERV_SERVICCONTROLMANAGER_DATA();

//typedefs of the function pointers
  typedef SERVICE_STATUS_HANDLE (WINAPI REGISTERSERVICECTRLHANDLEREX)(LPCTSTR, LPHANDLER_FUNCTION_EX, LPVOID);
  typedef REGISTERSERVICECTRLHANDLEREX* LPREGISTERSERVICECTRLHANDLEREX;
  typedef BOOL (WINAPI ENUMSERVICESSTATUSEX)(SC_HANDLE, SC_ENUM_TYPE, DWORD, DWORD, LPBYTE, DWORD, LPDWORD, LPDWORD, LPDWORD, LPCTSTR);
  typedef ENUMSERVICESSTATUSEX* LPENUMSERVICESSTATUSEX;

//Member variables
  HINSTANCE                      m_hAdvapi32;  //Instance handle of the "ADVAPI32.DLL" which houses all of the NT Service functions
  LPREGISTERSERVICECTRLHANDLEREX m_lpfnRegisterServiceCtrlHandlerEx;
  LPENUMSERVICESSTATUSEX         m_lpfnEnumServicesStatusEx;
};

_NTSERV_SERVICCONTROLMANAGER_DATA::_NTSERV_SERVICCONTROLMANAGER_DATA()
{
  m_hAdvapi32 = GetModuleHandle(_T("ADVAPI32.DLL"));
  VERIFY(m_hAdvapi32 != NULL);

#ifdef _UNICODE
  m_lpfnRegisterServiceCtrlHandlerEx = (LPREGISTERSERVICECTRLHANDLEREX) GetProcAddress(m_hAdvapi32, "RegisterServiceCtrlHandlerExW");
  m_lpfnEnumServicesStatusEx  = (LPENUMSERVICESSTATUSEX) GetProcAddress(m_hAdvapi32, "EnumServicesStatusExW");
#else
  m_lpfnRegisterServiceCtrlHandlerEx = (LPREGISTERSERVICECTRLHANDLEREX) GetProcAddress(m_hAdvapi32, "RegisterServiceCtrlHandlerExA");
  m_lpfnEnumServicesStatusEx  = (LPENUMSERVICESSTATUSEX) GetProcAddress(m_hAdvapi32, "EnumServicesStatusExA");
#endif
}

//The local variable which handle the function pointers

_NTSERV_SERVICCONTROLMANAGER_DATA _NtServData;



CNTServiceControlManager::CNTServiceControlManager()
{
  m_hSCM = NULL;
  m_hLock = NULL;
}

CNTServiceControlManager::~CNTServiceControlManager()
{
  Unlock();
  Close();
}

CNTServiceControlManager::operator SC_HANDLE() const
{
  return m_hSCM;
}

BOOL CNTServiceControlManager::Attach(SC_HANDLE hSCM)
{
  if (m_hSCM != hSCM)
    Close();

  m_hSCM = hSCM;
  return TRUE;
}

SC_HANDLE CNTServiceControlManager::Detach()
{
  SC_HANDLE hReturn = m_hSCM;
  m_hSCM = NULL;
  return hReturn;
}

BOOL CNTServiceControlManager::Open(LPCTSTR pszMachineName, DWORD dwDesiredAccess)
{
  Close();
  m_hSCM = ::OpenSCManager(pszMachineName, SERVICES_ACTIVE_DATABASE, dwDesiredAccess);
  return (m_hSCM != NULL);
}

void CNTServiceControlManager::Close()
{
  if (m_hSCM)
  {
    ::CloseServiceHandle(m_hSCM);
    m_hSCM = NULL;
  }
}

BOOL CNTServiceControlManager::QueryLockStatus(LPQUERY_SERVICE_LOCK_STATUS& lpLockStatus) const
{
  ASSERT(m_hSCM != NULL);
  ASSERT(lpLockStatus == NULL); //To prevent double overwrites, this function
                                //asserts if you do not send in a NULL pointer

  DWORD dwBytesNeeded;
  BOOL bSuccess = ::QueryServiceLockStatus(m_hSCM, NULL, 0, &dwBytesNeeded);
  if (!bSuccess && ::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    lpLockStatus = (LPQUERY_SERVICE_LOCK_STATUS) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = ::QueryServiceLockStatus(m_hSCM, lpLockStatus, dwBytesNeeded, &dwSize);
  }
  return bSuccess;
}

BOOL CNTServiceControlManager::EnumServices(DWORD dwServiceType, DWORD dwServiceState, void* pUserData, ENUM_SERVICES_PROC lpEnumServicesFunc) const
{
  ASSERT(m_hSCM != NULL);

  DWORD dwBytesNeeded;
  DWORD dwServices;
  DWORD dwResumeHandle = 0;
  BOOL bSuccess = ::EnumServicesStatus(m_hSCM, dwServiceType, dwServiceState, NULL, 0, &dwBytesNeeded, &dwServices, &dwResumeHandle);
  if (!bSuccess && ::GetLastError() == ERROR_MORE_DATA)
  {
    LPENUM_SERVICE_STATUS lpServices = (LPENUM_SERVICE_STATUS) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = ::EnumServicesStatus(m_hSCM, dwServiceType, dwServiceState, (LPENUM_SERVICE_STATUS) lpServices, dwBytesNeeded, &dwSize, &dwServices, &dwResumeHandle);
    if (bSuccess)
    {
      BOOL bContinue = TRUE;
      for (DWORD i=0; i<dwServices && bContinue; i++)
        bContinue = lpEnumServicesFunc(pUserData, lpServices[i]);
    }
    delete [] lpServices;
  }
  return bSuccess;
}

BOOL CNTServiceControlManager::EnumServices(DWORD dwServiceType, DWORD dwServiceState, LPCTSTR pszGroupName, void* pUserData, ENUM_SERVICES_PROC2 lpEnumServicesFunc) const
{
  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnEnumServicesStatusEx == NULL)
  {
    TRACE(_T("CNTServiceControlManager::EnumServices, EnumServicesStatusEx function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  DWORD dwBytesNeeded;
  DWORD dwServices;
  DWORD dwResumeHandle = 0;
  BOOL bSuccess = _NtServData.m_lpfnEnumServicesStatusEx(m_hSCM, SC_ENUM_PROCESS_INFO, dwServiceType, dwServiceState, 
                                                         NULL, 0, &dwBytesNeeded, &dwServices, &dwResumeHandle, pszGroupName);
  if (!bSuccess && ::GetLastError() == ERROR_MORE_DATA)
  {
    LPENUM_SERVICE_STATUS_PROCESS lpServices = (LPENUM_SERVICE_STATUS_PROCESS) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = _NtServData.m_lpfnEnumServicesStatusEx(m_hSCM, SC_ENUM_PROCESS_INFO, dwServiceType, dwServiceState, 
                                                      (LPBYTE) lpServices, dwBytesNeeded, &dwSize, &dwServices, &dwResumeHandle, pszGroupName);
    if (bSuccess)
    {
      BOOL bContinue = TRUE;
      for (DWORD i=0; i<dwServices && bContinue; i++)
        bContinue = lpEnumServicesFunc(pUserData, lpServices[i]);
    }
    delete [] lpServices;
  }
  return bSuccess;
}

BOOL CNTServiceControlManager::OpenService(LPCTSTR lpServiceName,	DWORD dwDesiredAccess, CNTScmService& service) const
{
  ASSERT(m_hSCM != NULL);

  SC_HANDLE hService = ::OpenService(m_hSCM, lpServiceName, dwDesiredAccess);
  if (hService != NULL)
    service.Attach(hService);
  return (hService != NULL);
}

BOOL CNTServiceControlManager::Lock()
{
  ASSERT(m_hSCM != NULL);

  m_hLock = LockServiceDatabase(m_hSCM);
  return (m_hLock != NULL);
}

BOOL CNTServiceControlManager::Unlock()
{
  BOOL bSuccess = TRUE;
  if (m_hLock)
  {
    bSuccess = ::UnlockServiceDatabase(m_hLock);
    m_hLock = NULL;
  }

  return bSuccess;
}
