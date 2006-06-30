/*  
Module : NTSERVEVENTLOG.CPP
Purpose: Implementation for the class CNTEventLog
Created: PJN / 14-07-1997
History: None

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
#include "ntservEventlog.h"



/////////////////////////////////  Macros /////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Implementation //////////////////////////////

CNTEventLog::CNTEventLog()
{
  m_hEventLog = NULL;
}

CNTEventLog::~CNTEventLog()
{
  Close();
}

CNTEventLog::operator HANDLE() const
{
  return m_hEventLog;
}

BOOL CNTEventLog::Attach(HANDLE hEventLog)
{
  if (m_hEventLog != hEventLog)
    Close();

  m_hEventLog = hEventLog;
  return TRUE;
}

HANDLE CNTEventLog::Detach()
{
  HANDLE hReturn = m_hEventLog;
  m_hEventLog = NULL;
  return hReturn;
}

BOOL CNTEventLog::Open(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName)
{
  Close();
  m_hEventLog = ::OpenEventLog(lpUNCServerName, lpSourceName);
  return (m_hEventLog != NULL);
}

BOOL CNTEventLog::OpenApplication(LPCTSTR lpUNCServerName)
{
  return Open(lpUNCServerName, _T("Application"));
}

BOOL CNTEventLog::OpenSystem(LPCTSTR lpUNCServerName)
{
  return Open(lpUNCServerName, _T("System"));
}

BOOL CNTEventLog::OpenSecurity(LPCTSTR lpUNCServerName)
{
  return Open(lpUNCServerName, _T("Security"));
}

BOOL CNTEventLog::OpenBackup(LPCTSTR lpUNCServerName, LPCTSTR lpFileName)
{
  Close();
  m_hEventLog = ::OpenBackupEventLog(lpUNCServerName, lpFileName);
  return (m_hEventLog != NULL);
}

BOOL CNTEventLog::Close()
{
  BOOL bSuccess = TRUE;
  if (m_hEventLog != NULL)
  {
    bSuccess = ::CloseEventLog(m_hEventLog);
    m_hEventLog = NULL;
  }

  return bSuccess;
}

BOOL CNTEventLog::Backup(LPCTSTR lpBackupFileName) const
{
  ASSERT(m_hEventLog != NULL);
  return ::BackupEventLog(m_hEventLog, lpBackupFileName);
}

BOOL CNTEventLog::Clear(LPCTSTR lpBackupFileName) const
{
  ASSERT(m_hEventLog != NULL);
  return ::ClearEventLog(m_hEventLog, lpBackupFileName);
}

BOOL CNTEventLog::GetNumberOfRecords(DWORD& dwNumberOfRecords) const
{
  ASSERT(m_hEventLog != NULL);
  return ::GetNumberOfEventLogRecords(m_hEventLog, &dwNumberOfRecords);
}

BOOL CNTEventLog::GetOldestRecord(DWORD& dwOldestRecord) const
{
  ASSERT(m_hEventLog != NULL);
  return ::GetOldestEventLogRecord(m_hEventLog, &dwOldestRecord);
}

BOOL CNTEventLog::NotifyChange(HANDLE hEvent) const
{
  ASSERT(m_hEventLog != NULL);
  return ::NotifyChangeEventLog(m_hEventLog, hEvent);
}

BOOL CNTEventLog::ReadNext(CEventLogRecord& record) const
{
  ASSERT(m_hEventLog != NULL);

  DWORD dwBytesRead;
  DWORD dwBytesNeeded;
  EVENTLOGRECORD el;
  BOOL bSuccess = ::ReadEventLog(m_hEventLog, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ, 0, &el, sizeof(EVENTLOGRECORD), &dwBytesRead, &dwBytesNeeded);
  if (bSuccess)
    record = CEventLogRecord(&el);
  else if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    //buffer was too small allocate a new one and call again
    BYTE* lpBuffer = new BYTE[dwBytesNeeded];
    bSuccess = ::ReadEventLog(m_hEventLog, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_FORWARDS_READ, 0, lpBuffer, dwBytesNeeded, &dwBytesRead, &dwBytesNeeded);
    if (bSuccess)
      record = CEventLogRecord((EVENTLOGRECORD*) lpBuffer);
    delete [] lpBuffer;
  }

  return bSuccess;
}

BOOL CNTEventLog::ReadPrev(CEventLogRecord& record) const
{
  ASSERT(m_hEventLog != NULL);

  DWORD dwBytesRead;
  DWORD dwBytesNeeded;
  EVENTLOGRECORD el;
  BOOL bSuccess = ::ReadEventLog(m_hEventLog, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_BACKWARDS_READ, 0, &el, sizeof(EVENTLOGRECORD), &dwBytesRead, &dwBytesNeeded);
  if (bSuccess)
    record = CEventLogRecord(&el);
  else if (::GetLastError() == ERROR_INSUFFICIENT_BUFFER)
  {
    //buffer was too small allocate a new one and call again
    BYTE* lpBuffer = new BYTE[dwBytesNeeded];
    bSuccess = ::ReadEventLog(m_hEventLog, EVENTLOG_SEQUENTIAL_READ | EVENTLOG_BACKWARDS_READ, 0, lpBuffer, dwBytesNeeded, &dwBytesRead, &dwBytesNeeded);
    if (bSuccess)
      record = CEventLogRecord((EVENTLOGRECORD*) lpBuffer);
    delete [] lpBuffer;
  }

  return bSuccess;
}



