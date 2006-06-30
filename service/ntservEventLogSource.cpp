/*  
Module : NTSERVEVENTLOGSOURCE.CPP
Purpose: Implementation for the class CNTEventLogSource
Created: PJN / 14-07-1997
History: PJN / 23-07-2005 1. Provided an overriden version of Report which has 3 string parameters
                          2. GetStringArrayFromRegistry and SetStringArrayIntoRegistry methods
                          are now public as they are helpful to have available externally
         PJN / 11-01-2006 1. Addition of a default constructor for CNTEventLogSource 
                          2. Addition of CNTEventLogSource::SetServerName, CNTEventLogSource::GetServerName,
                          CNTEventLogSource::SetSourceName and CNTEventLogSource::GetSourceName methods
                          3. Addition of a DWORD* parameter to the CNTEventLogSource::GetStringArrayFromRegistry
                          and CNTEventLogSource::SetStringArrayFromRegistry functions. This allow the details
                          of the last error to be returned to client code.

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
#include "ntservEventLogSource.h"
#include "ntserv_msg.h"



/////////////////////////////////  Macros /////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Includes ////////////////////////////////////

CNTEventLogSource::CNTEventLogSource() : m_hEventSource(NULL)
{
}

CNTEventLogSource::CNTEventLogSource(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName) : m_hEventSource(NULL)
{
  m_sServerName = lpUNCServerName;
  m_sSourceName = lpSourceName;
}

CNTEventLogSource::~CNTEventLogSource()
{
  Deregister();
}

CNTEventLogSource::operator HANDLE() const
{
  return m_hEventSource;
}

BOOL CNTEventLogSource::Attach(HANDLE hEventSource)
{
  if (m_hEventSource != hEventSource)
    Deregister();

  m_hEventSource = hEventSource;
  return TRUE;
}

HANDLE CNTEventLogSource::Detach()
{
  HANDLE hReturn = m_hEventSource;
  m_hEventSource = NULL;
  return hReturn;
}

BOOL CNTEventLogSource::Register(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName)
{
  Deregister();
  m_hEventSource = ::RegisterEventSource(lpUNCServerName, lpSourceName);
  return (m_hEventSource != NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, WORD wCategory, DWORD dwEventID, PSID lpUserSid,
                               WORD wNumStrings, DWORD dwDataSize, LPCTSTR* lpStrings, LPVOID lpRawData)
{
  CSingleLock sl(&m_csReport, TRUE);

  ASSERT(m_hEventSource == NULL);
  Register(m_sServerName, m_sSourceName);

  //Call the SDK version of the function
  BOOL bSuccess = ::ReportEvent(m_hEventSource, wType,	wCategory, dwEventID, lpUserSid,
                                wNumStrings, dwDataSize, lpStrings, lpRawData);
  Deregister();  

  return bSuccess;
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID)
{
  return Report(wType, 0, dwEventID, NULL, 0, 0, NULL, NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, LPCTSTR lpszString)
{
  return Report(wType, CNTS_MSG_SERVICE_FULLSTRING, lpszString);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString)
{
  ASSERT(lpszString);
  return Report(wType, 0, dwEventID, NULL, 1, 0, &lpszString, NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2)
{
  ASSERT(lpszString1);
  ASSERT(lpszString2);
  LPCTSTR lpStrings[2];
  lpStrings[0] = lpszString1;
  lpStrings[1] = lpszString2;
  return Report(wType, 0, dwEventID, NULL, 2, 0, lpStrings, NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2, DWORD dwCode, BOOL bReportAsHex)
{
  ASSERT(lpszString1);
  ASSERT(lpszString2);
  LPCTSTR lpStrings[3];
  lpStrings[0] = lpszString1;
  lpStrings[1] = lpszString2;
  CString sError;
  if (bReportAsHex)
    sError.Format(_T("%x"), dwCode);
  else
    sError.Format(_T("%d"), dwCode);
  lpStrings[2] = sError;
  return Report(wType, 0, dwEventID, NULL, 3, 0, lpStrings, NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2, LPCTSTR lpszString3)
{
  ASSERT(lpszString1);
  ASSERT(lpszString2);
  ASSERT(lpszString3);
  LPCTSTR lpStrings[3];
  lpStrings[0] = lpszString1;
  lpStrings[1] = lpszString2;
  lpStrings[2] = lpszString3;
  return Report(wType, 0, dwEventID, NULL, 3, 0, lpStrings, NULL);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, DWORD dwCode, BOOL bReportAsHex)
{
  CString sError;
  if (bReportAsHex)
    sError.Format(_T("%x"), dwCode);
  else
    sError.Format(_T("%d"), dwCode);
  return Report(wType, dwEventID, sError);
}

BOOL CNTEventLogSource::Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString, DWORD dwCode, BOOL bReportAsHex)
{
  CString sError;
  if (bReportAsHex)
    sError.Format(_T("%x"), dwCode);
  else
    sError.Format(_T("%d"), dwCode);
  return Report(wType, dwEventID, lpszString, sError);
}

BOOL CNTEventLogSource::Deregister()
{
  BOOL bSuccess = TRUE;
  if (m_hEventSource != NULL)
  {
    bSuccess = ::DeregisterEventSource(m_hEventSource);
    m_hEventSource = NULL;
  }

  return bSuccess;
}

BOOL CNTEventLogSource::Install(LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, DWORD dwTypesSupported)
{
  //Validate our parameters
  ASSERT(lpSourceName);
  ASSERT(lpEventMessageFile);

  //Make the necessary updates to the registry
  BOOL bSuccess = FALSE;
  HKEY hAppKey;
  if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"), 0, 
                     KEY_WRITE|KEY_READ, &hAppKey) == ERROR_SUCCESS)
  {
		DWORD dw;
    HKEY hSourceKey;
		if (RegCreateKeyEx(hAppKey, lpSourceName, 0, REG_NONE, REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
			                 &hSourceKey, &dw) == ERROR_SUCCESS)
		{
      //Write the Message file string
  		bSuccess = (RegSetValueEx(hSourceKey, _T("EventMessageFile"), NULL, REG_SZ, (LPBYTE)lpEventMessageFile, 
                                (lstrlen(lpEventMessageFile)+1)*sizeof(TCHAR)) == ERROR_SUCCESS);

      //Write the Types supported dword
      bSuccess = bSuccess && (RegSetValueEx(hSourceKey, _T("TypesSupported"), NULL, REG_DWORD,
		                                        (LPBYTE)&dwTypesSupported, sizeof(dwTypesSupported)) == ERROR_SUCCESS);
      //Close the registry key we opened
      ::RegCloseKey(hSourceKey);

      //Update the sources registry key so that the event viewer can filter 
      //on the events which we write to the event log
      CStringArray sources;
      if (GetStringArrayFromRegistry(hAppKey, _T("Sources"), sources))
      {
        //If our name is not in the array then add it
        BOOL bFoundMyself = FALSE;
        for (int i=0; i<sources.GetSize() && !bFoundMyself; i++)
          bFoundMyself = (sources.GetAt(i) == lpSourceName);
        if (!bFoundMyself)
        {
          sources.Add(lpSourceName);
          SetStringArrayIntoRegistry(hAppKey, _T("Sources"), sources);
        }
      }
    }

    //Close the registry key we opened
    ::RegCloseKey(hAppKey);
  }

  return bSuccess;
}

BOOL CNTEventLogSource::Uninstall(LPCTSTR lpSourceName)
{
  //Validate our parameters
  ASSERT(lpSourceName);

  //Remove the settings from the registry
  CString sSubKey(_T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"));
  sSubKey += lpSourceName;
  BOOL bSuccess = (RegDeleteKey(HKEY_LOCAL_MACHINE, sSubKey) == ERROR_SUCCESS);

  //Remove ourself from the "Sources" registry key
  HKEY hAppKey;
  if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"), 0, 
                     KEY_WRITE|KEY_READ, &hAppKey) == ERROR_SUCCESS)
  {
    CStringArray sources;
    if (GetStringArrayFromRegistry(hAppKey, _T("Sources"), sources))
    {
      //If our name is in the array then remove it
      BOOL bFoundMyself = FALSE;
      for (int i=0; i<sources.GetSize() && !bFoundMyself; i++)
      {
        bFoundMyself = (sources.GetAt(i) == lpSourceName);
        if (bFoundMyself)
          sources.RemoveAt(i);
      }
      if (bFoundMyself)
        SetStringArrayIntoRegistry(hAppKey, _T("Sources"), sources);
    }

    //Close the registry key we opened
    ::RegCloseKey(hAppKey);
  }

  return bSuccess;
}

BOOL CNTEventLogSource::GetStringArrayFromRegistry(HKEY hKey, LPCTSTR lpszEntry, CStringArray& array, DWORD* pLastError)
{
	ASSERT(hKey != NULL);
	ASSERT(lpszEntry != NULL);

  //Assume the worst
  BOOL bSuccess = FALSE;

  //Empty the array before we go any further
  array.RemoveAll();

	DWORD dwType, dwCount;
	LONG lResult = RegQueryValueEx(hKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
	if (lResult == ERROR_SUCCESS)
	{
		if (dwType == REG_MULTI_SZ)
    {
		  LPBYTE lpBuffer = new BYTE[dwCount];
		  lResult = RegQueryValueEx(hKey, (LPTSTR)lpszEntry, NULL, &dwType, lpBuffer, &dwCount);
      if (lResult == ERROR_SUCCESS)
      {
        LPTSTR lpszStrings = (LPTSTR) lpBuffer;
        while (lpszStrings[0] != 0)
        {
          array.Add((LPCTSTR) lpszStrings);
          lpszStrings += (_tcslen(lpszStrings ) + 1);
        }

        bSuccess = TRUE;
      }
      else
      {
        if (pLastError)
          *pLastError = lResult;
      }

      //Tidy up the heap memory we have used
      delete [] lpBuffer;
    }
    else
    {
      SetLastError(ERROR_INVALID_DATA);

      if (pLastError)
        *pLastError = ERROR_INVALID_DATA;
    }
	}
  else
  {
    if (pLastError)
      *pLastError = lResult;
  }

  return bSuccess;
}

BOOL CNTEventLogSource::SetStringArrayIntoRegistry(HKEY hKey, LPCTSTR lpszEntry, const CStringArray& array, DWORD* pLastError)
{   
  //Validate our input parameters
  ASSERT(hKey);
  ASSERT(lpszEntry != NULL);

  //Work out the size of the buffer we will need
  DWORD dwSize = 0;
#if (_MSC_VER >= 1300)  
  INT_PTR nStrings = array.GetSize();
  INT_PTR i;
#else
  int nStrings = array.GetSize();
  int i;
#endif  
  for (i=0; i<nStrings; i++)
    dwSize += array.GetAt(i).GetLength() + 1; //1 extra for each NULL terminator

  //Need one second NULL for the double NULL at the end
  dwSize++;

  //Convert from BYTE size to character size
  dwSize *= sizeof(TCHAR);

  //Allocate the memory we want
  BYTE* lpBuffer = new BYTE[dwSize];
  memset(lpBuffer, 0, dwSize);

  //Now copy the strings into the buffer
  int nCurOffset = 0;
  LPTSTR lpszString = (LPTSTR) lpBuffer;
  for (i=0; i<nStrings; i++)
  {
    CString sText = array.GetAt(i);
    _tcscpy(&lpszString[nCurOffset], sText);
    nCurOffset += sText.GetLength();
    nCurOffset++;
  }
  //Don't forgot to doubly NULL terminate
  lpszString[nCurOffset] = _T('\0');

  //Finally write it into the registry
  LONG lResult = ::RegSetValueEx(hKey, lpszEntry, NULL, REG_MULTI_SZ, lpBuffer, dwSize);
	BOOL bSuccess = (lResult == ERROR_SUCCESS);
  if (!bSuccess && pLastError)
    *pLastError = lResult;

  //free up the memory we used
  delete [] lpBuffer;

  return bSuccess;
}

