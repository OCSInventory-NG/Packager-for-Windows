/*  
Module : NTSERVSCMSERVICE.CPP
Purpose: Implementation for the class CNTScmService
Created: PJN / 14-07-1997
History: PJN / 09-01-2006 1. When registering the service, the quoting of the path name to use for the service 
                          is now done in CNTService::ProcessShellCommand instead of CNTScmService::Create.

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
#include "ntservScmService.h"
#include "ntservServiceControlManager.h"



////////////////////////////////// Macros / Defines ////////////////////////////

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

class _NTSERV_SCMSERVICE_DATA
{
public:
//Constructors /Destructors
  _NTSERV_SCMSERVICE_DATA();

//typedefs of the function pointers
  typedef BOOL (WINAPI QUERYSERVICECONFIG2)(SC_HANDLE, DWORD, LPBYTE, DWORD, LPDWORD);
  typedef QUERYSERVICECONFIG2* LPQUERYSERVICECONFIG2;
  typedef BOOL (WINAPI CHANGESERVICECONFIG2)(SC_HANDLE, DWORD, LPVOID);
  typedef CHANGESERVICECONFIG2* LPCHANGESERVICECONFIG2;
  typedef BOOL (WINAPI QUERYSERVICESTATUSEX)(SC_HANDLE, SC_STATUS_TYPE, LPBYTE, DWORD, LPDWORD);
  typedef QUERYSERVICESTATUSEX* LPQUERYSERVICESTATUSEX;

//Member variables
  HINSTANCE              m_hAdvapi32;  //Instance handle of the "ADVAPI32.DLL" which houses all of the NT Service functions
  LPQUERYSERVICECONFIG2  m_lpfnQueryServiceConfig2;
  LPCHANGESERVICECONFIG2 m_lpfnChangeServiceConfig2;
  LPQUERYSERVICESTATUSEX m_lpfnQueryServiceStatusEx;
};

_NTSERV_SCMSERVICE_DATA::_NTSERV_SCMSERVICE_DATA()
{
  m_hAdvapi32 = GetModuleHandle(_T("ADVAPI32.DLL"));
  VERIFY(m_hAdvapi32 != NULL);

#ifdef _UNICODE
  m_lpfnQueryServiceConfig2 = (LPQUERYSERVICECONFIG2) GetProcAddress(m_hAdvapi32, "QueryServiceConfig2W");
  m_lpfnChangeServiceConfig2 = (LPCHANGESERVICECONFIG2) GetProcAddress(m_hAdvapi32, "ChangeServiceConfig2W");
#else
  m_lpfnQueryServiceConfig2 = (LPQUERYSERVICECONFIG2) GetProcAddress(m_hAdvapi32, "QueryServiceConfig2A");
  m_lpfnChangeServiceConfig2 = (LPCHANGESERVICECONFIG2) GetProcAddress(m_hAdvapi32, "ChangeServiceConfig2A");
#endif
  m_lpfnQueryServiceStatusEx = (LPQUERYSERVICESTATUSEX) GetProcAddress(m_hAdvapi32, "QueryServiceStatusEx");
}

//The local variable which handle the function pointers

_NTSERV_SCMSERVICE_DATA _NtServData;



CNTScmService::CNTScmService()
{
  m_hService = NULL;
}

CNTScmService::~CNTScmService()
{
  Close();
}

void CNTScmService::Close()
{
  if (m_hService)
  {
    CloseServiceHandle(m_hService);
    m_hService = NULL;
  }
}

CNTScmService::operator SC_HANDLE() const
{
  return m_hService;
}

BOOL CNTScmService::Attach(SC_HANDLE hService)
{
  if (m_hService != hService)
    Close();

  m_hService = hService;
  return TRUE;
}

SC_HANDLE CNTScmService::Detach()
{
  SC_HANDLE hReturn = m_hService;
  m_hService = NULL;
  return hReturn;
}

BOOL CNTScmService::ChangeConfig(DWORD dwServiceType,	DWORD dwStartType,
 									               DWORD dwErrorControl, LPCTSTR lpBinaryPathName,
									               LPCTSTR lpLoadOrderGroup, LPDWORD lpdwTagId,
                                 LPCTSTR lpDependencies, LPCTSTR lpServiceStartName,
 									               LPCTSTR lpPassword, LPCTSTR lpDisplayName) const
{
  ASSERT(m_hService != NULL);
  return ::ChangeServiceConfig(m_hService, dwServiceType, dwStartType,
 				        					     dwErrorControl, lpBinaryPathName, lpLoadOrderGroup, lpdwTagId,
                               lpDependencies, lpServiceStartName, lpPassword, lpDisplayName);
}

BOOL CNTScmService::Control(DWORD dwControl)
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  return ::ControlService(m_hService, dwControl, &ServiceStatus);
}

BOOL CNTScmService::Stop() const
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  return ::ControlService(m_hService, SERVICE_CONTROL_STOP, &ServiceStatus);
}

BOOL CNTScmService::WaitForStop(DWORD dwTimeout)
{
  return WaitForServiceStatus(dwTimeout, SERVICE_STOPPED);
}

BOOL CNTScmService::WaitForServiceStatus(DWORD dwTimeout, DWORD dwWaitForStatus, DWORD dwPollingInterval)
{
  //wait for our desired status
  DWORD dwStartTime = GetTickCount();
  SERVICE_STATUS ss;
  for (;;)
  {
    if (!QueryStatus(ss))
      break;

    //if this is the status we were waiting for then we're done
    if (ss.dwCurrentState == dwWaitForStatus)
      return TRUE;

    //Do the wait
    ::Sleep(dwPollingInterval);

    //check for timeout
    if ((dwTimeout != INFINITE) && ((GetTickCount() - dwStartTime) > dwTimeout))
    {
      SetLastError(ERROR_TIMEOUT);
      break;
    }
  }
  return FALSE;
}

BOOL CNTScmService::Pause() const
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  return ::ControlService(m_hService, SERVICE_CONTROL_PAUSE, &ServiceStatus);
}

BOOL CNTScmService::Continue() const
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  return ::ControlService(m_hService, SERVICE_CONTROL_CONTINUE, &ServiceStatus);
}

BOOL CNTScmService::Interrogate() const
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  return ::ControlService(m_hService, SERVICE_CONTROL_INTERROGATE, &ServiceStatus);
}

BOOL CNTScmService::Start(DWORD dwNumServiceArgs,	LPCTSTR* lpServiceArgVectors) const
{
  ASSERT(m_hService != NULL);
  return ::StartService(m_hService, dwNumServiceArgs, lpServiceArgVectors);
}

BOOL CNTScmService::AcceptStop(BOOL& bStop)
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  BOOL bSuccess = QueryStatus(ServiceStatus);
  if (bSuccess)
    bStop = ((ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_STOP) != 0);

  return bSuccess;
}

BOOL CNTScmService::AcceptPauseContinue(BOOL& bPauseContinue)
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  BOOL bSuccess = QueryStatus(ServiceStatus);
  if (bSuccess)
    bPauseContinue = ((ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE) != 0);

  return bSuccess;
}

BOOL CNTScmService::AcceptShutdown(BOOL& bShutdown)
{
  ASSERT(m_hService != NULL);
  SERVICE_STATUS ServiceStatus;
  BOOL bSuccess = QueryStatus(ServiceStatus);
  if (bSuccess)
    bShutdown = ((ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN) != 0);

  return bSuccess;
}

BOOL CNTScmService::QueryStatus(SERVICE_STATUS& ServiceStatus) const
{
  ASSERT(m_hService != NULL);
  return ::QueryServiceStatus(m_hService, &ServiceStatus);
}

BOOL CNTScmService::QueryStatus(SERVICE_STATUS_PROCESS& ssp) const
{
  ASSERT(m_hService != NULL);

  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnQueryServiceStatusEx == NULL)
  {
    TRACE(_T("CNTScmService::QueryStatus, QueryServiceStatusEx function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  //Call through the function pointer
  DWORD dwBytesNeeded;
  return _NtServData.m_lpfnQueryServiceStatusEx(m_hService, SC_STATUS_PROCESS_INFO, (LPBYTE) &ssp, sizeof(SERVICE_STATUS_PROCESS), &dwBytesNeeded);
}

BOOL CNTScmService::QueryConfig(LPQUERY_SERVICE_CONFIG& lpServiceConfig) const
{
  ASSERT(m_hService != NULL);
  ASSERT(lpServiceConfig == NULL); //To prevent double overwrites, this function
                                   //asserts if you do not send in a NULL pointer

  DWORD dwBytesNeeded;
  BOOL bSuccess = ::QueryServiceConfig(m_hService, NULL, 0, &dwBytesNeeded);
  if (!bSuccess && ::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    lpServiceConfig = (LPQUERY_SERVICE_CONFIG) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = ::QueryServiceConfig(m_hService, lpServiceConfig, dwBytesNeeded, &dwSize);
  }
  return bSuccess;
}

BOOL CNTScmService::Create(CNTServiceControlManager& Manager, LPCTSTR lpServiceName, LPCTSTR lpDisplayName,	  
						               DWORD dwDesiredAccess,	DWORD dwServiceType, DWORD dwStartType,	DWORD dwErrorControl,	    
						               LPCTSTR lpBinaryPathName, LPCTSTR lpLoadOrderGroup, LPDWORD lpdwTagId,	        
						               LPCTSTR lpDependencies, LPCTSTR lpServiceStartName, LPCTSTR lpPassword)
{
  Close();

  m_hService = ::CreateService(Manager, lpServiceName, lpDisplayName,	dwDesiredAccess, dwServiceType, 
                               dwStartType,	dwErrorControl,	lpBinaryPathName, lpLoadOrderGroup, 
                               lpdwTagId,	lpDependencies, lpServiceStartName, lpPassword);
  return (m_hService != NULL);
}

BOOL CNTScmService::Delete() const
{
  ASSERT(m_hService != NULL);
  return ::DeleteService(m_hService);
}

BOOL CNTScmService::SetObjectSecurity(SECURITY_INFORMATION dwSecurityInformation,
                                      PSECURITY_DESCRIPTOR lpSecurityDescriptor) const

{
  ASSERT(m_hService != NULL);
  return ::SetServiceObjectSecurity(m_hService, dwSecurityInformation, lpSecurityDescriptor);
}

BOOL CNTScmService::QueryObjectSecurity(SECURITY_INFORMATION dwSecurityInformation,
                                        PSECURITY_DESCRIPTOR& lpSecurityDescriptor) const
{
  ASSERT(m_hService != NULL);
  ASSERT(lpSecurityDescriptor == NULL); //To prevent double overwrites, this function
                                        //asserts if you do not send in a NULL pointer

  DWORD dwBytesNeeded;
  BOOL bSuccess = ::QueryServiceObjectSecurity(m_hService, dwSecurityInformation, NULL, 0, &dwBytesNeeded);
  if (!bSuccess && ::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    lpSecurityDescriptor = (PSECURITY_DESCRIPTOR) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = ::QueryServiceObjectSecurity(m_hService, dwSecurityInformation, lpSecurityDescriptor, dwBytesNeeded, &dwSize);
  }

  return bSuccess;
}

BOOL CNTScmService::EnumDependents(DWORD dwServiceState, DWORD dwUserData, ENUM_SERVICES_PROC lpEnumServicesFunc) const
{
  ASSERT(m_hService != NULL);

  DWORD dwBytesNeeded;
  DWORD dwServices;
  BOOL bSuccess = ::EnumDependentServices(m_hService, dwServiceState, NULL, 0, &dwBytesNeeded, &dwServices);
  if (!bSuccess && ::GetLastError() == ERROR_MORE_DATA)
  {
    LPENUM_SERVICE_STATUS lpServices = (LPENUM_SERVICE_STATUS) new BYTE[dwBytesNeeded];
    DWORD dwSize;
    bSuccess = ::EnumDependentServices(m_hService, dwServiceState, lpServices, dwBytesNeeded, &dwSize, &dwServices);
    if (bSuccess)
    {
      BOOL bContinue = TRUE;
      for (DWORD i=0; i<dwServices && bContinue; i++)
        bContinue = lpEnumServicesFunc(dwUserData, lpServices[i]);
    }
    delete [] lpServices;
  }
  return bSuccess;
}

BOOL CNTScmService::QueryDescription(CString& sDescription) const
{
  ASSERT(m_hService != NULL);

  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnQueryServiceConfig2 == NULL)
  {
    TRACE(_T("CNTScmService::QueryDescription, QueryServiceConfig2 function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  //Call through the function pointer
  DWORD dwBytesNeeded = 0;
  BOOL bSuccess = _NtServData.m_lpfnQueryServiceConfig2(m_hService, SERVICE_CONFIG_DESCRIPTION, NULL, 0, &dwBytesNeeded);
  if (!bSuccess && ::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    BYTE* lpData = new BYTE[dwBytesNeeded];
    bSuccess = _NtServData.m_lpfnQueryServiceConfig2(m_hService, SERVICE_CONFIG_DESCRIPTION, lpData, dwBytesNeeded, &dwBytesNeeded);
    if (bSuccess)
      sDescription = ((LPSERVICE_DESCRIPTION) lpData)->lpDescription;
    delete [] lpData;
  }

  return bSuccess;
}

BOOL CNTScmService::QueryFailureActions(LPSERVICE_FAILURE_ACTIONS& lpActions) const
{
  ASSERT(m_hService != NULL);
  ASSERT(lpActions == NULL); //To prevent double overwrites, this function
                             //asserts if you do not send in a NULL pointer

  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnQueryServiceConfig2 == NULL)
  {
    TRACE(_T("CNTScmService::QueryFailureActions, QueryServiceConfig2 function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  //Call through the function pointer
  DWORD dwBytesNeeded = 0;
  BOOL bSuccess = _NtServData.m_lpfnQueryServiceConfig2(m_hService, SERVICE_CONFIG_FAILURE_ACTIONS, NULL, 0, &dwBytesNeeded);
  if (!bSuccess && ::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    lpActions = (LPSERVICE_FAILURE_ACTIONS) new BYTE[dwBytesNeeded];
    bSuccess = _NtServData.m_lpfnQueryServiceConfig2(m_hService, SERVICE_CONFIG_FAILURE_ACTIONS, (LPBYTE) lpActions, dwBytesNeeded, &dwBytesNeeded);
  }

  return bSuccess;
}

BOOL CNTScmService::ChangeDescription(const CString& sDescription)
{
  ASSERT(m_hService != NULL);

  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnChangeServiceConfig2 == NULL)
  {
    TRACE(_T("CNTScmService::ChangeDescription, ChangeServiceConfig2 function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  //Call through the function pointer
  CString sTemp(sDescription);
  SERVICE_DESCRIPTION sd;
  sd.lpDescription = sTemp.GetBuffer(sTemp.GetLength());
  BOOL bSuccess = _NtServData.m_lpfnChangeServiceConfig2(m_hService, SERVICE_CONFIG_DESCRIPTION, &sd);
  sTemp.ReleaseBuffer();
  return bSuccess;
}

BOOL CNTScmService::ChangeFailureActions(SERVICE_FAILURE_ACTIONS& Actions)
{
  ASSERT(m_hService != NULL);

  //Check to see if the function pointer is available
  if (_NtServData.m_lpfnChangeServiceConfig2 == NULL)
  {
    TRACE(_T("CNTScmService::ChangeFailureActions, ChangeServiceConfig2 function is not supported on this OS. You need to be running at least Windows 2000 to use this function\n"));
    ::SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
  }

  //Call through the function pointer
  return _NtServData.m_lpfnChangeServiceConfig2(m_hService, SERVICE_CONFIG_FAILURE_ACTIONS, &Actions);
}



