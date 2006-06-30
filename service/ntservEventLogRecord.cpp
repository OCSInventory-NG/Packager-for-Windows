/*  
Module : NTSERVEVENTLOGRECORD.CPP
Purpose: Implementation for the class CNTEventLogRecord
Created: PJN / 14-07-1997
History: PJN / 14-08-2005 1. Fixed an issue where the SID and binary values was not being set correctly in the 
                          overloaded CEventLogRecord constructor which takes a EVENTLOGRECORD pointer. Thanks 
                          to Brian Lee for reporting this issue. Also the arrays which this information is 
                          copied into is now preallocated to improve performance.

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
#include "ntservEventLogRecord.h"
#ifndef __AFXPRIV_H__
#pragma message("To avoid this message, please put AFXPRIV.H in your PCH (normally stdafx.h)")
#include <AFXPRIV.H>
#endif



/////////////////////////////////  Macros /////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Implementation //////////////////////////////

CEventLogRecord::CEventLogRecord()
{
  m_dwRecordNumber = 0;
  m_TimeGenerated = CTime(0);
  m_TimeWritten = CTime(0);
  m_dwEventID = 0;
  m_wEventType = 0;
  m_wEventCategory = 0;
}

CEventLogRecord::CEventLogRecord(const CEventLogRecord& record)
{
  *this = record;
}

CEventLogRecord::CEventLogRecord(const EVENTLOGRECORD* pRecord)
{
  ASSERT(pRecord);

  //First the easy ones
  m_dwRecordNumber = pRecord->RecordNumber;
  m_TimeGenerated = pRecord->TimeGenerated;
  m_TimeWritten = pRecord->TimeWritten;
  m_dwEventID = pRecord->EventID;
  m_wEventType = pRecord->EventType;
  m_wEventCategory = pRecord->EventCategory;

  //Copy over the SID
  DWORD i = 0;
  BYTE* pBeginRecord = (BYTE*) pRecord;
  DWORD dwCurOffset = pRecord->UserSidOffset;
  if (pRecord->UserSidLength)
    m_UserSID.SetSize(0, pRecord->UserSidLength); //Preallocate the array to improve performance
  while (i < pRecord->UserSidLength)
  {
    m_UserSID.Add(pBeginRecord[dwCurOffset + i]);
    i++;
  }
  dwCurOffset += pRecord->UserSidLength;

  //Copy over the Binary data
  i = 0;
  dwCurOffset = pRecord->DataOffset;
  if (pRecord->DataLength)
    m_Data.SetSize(0, pRecord->DataLength); //Preallocate the array to improve performance
  while (i < pRecord->DataLength)
  {
    m_Data.Add(pBeginRecord[dwCurOffset + i]);
    i++;
  }
  dwCurOffset += pRecord->DataLength;

  //Copy over the SourceName
  TCHAR* pszBeginRecord = (TCHAR*) (pBeginRecord + sizeof(EVENTLOGRECORD));
  dwCurOffset = 0;
  DWORD dwStartOffset = dwCurOffset;
  while (pszBeginRecord[dwCurOffset])
    dwCurOffset++;
  m_sSourceName = &pszBeginRecord[dwStartOffset];

  //Skip over the NULL 
  dwCurOffset++;

  //Copy over the ComputerName
  dwStartOffset = dwCurOffset;
  while (pszBeginRecord[dwCurOffset])
    dwCurOffset++;
  m_sComputerName = &pszBeginRecord[dwStartOffset];

  //Copy over the strings array
  int nStringsRead = 0;
  pszBeginRecord = (TCHAR*) (pBeginRecord + pRecord->StringOffset);
  dwCurOffset = 0;
  while (nStringsRead < pRecord->NumStrings)
  {
    //Find the next string
    dwStartOffset = dwCurOffset;
    while (pszBeginRecord[dwCurOffset])
      dwCurOffset++;

    //Add it to the array
    CString sText(&pszBeginRecord[dwStartOffset]);
    m_Strings.Add(sText);

    //Increment the number of strings read
    nStringsRead++;

    //Skip over the NULL
    dwCurOffset++;
  }
}

CEventLogRecord& CEventLogRecord::operator=(const CEventLogRecord& record)
{
  m_dwRecordNumber = record.m_dwRecordNumber;
  m_TimeGenerated = record.m_TimeGenerated;
  m_TimeWritten = record.m_TimeWritten;
  m_dwEventID = record.m_dwEventID;
  m_wEventType = record.m_wEventType;
  m_wEventCategory = record.m_wEventCategory;
  m_UserSID.Copy(record.m_UserSID);
  m_Strings.Copy(record.m_Strings);
  m_Data.Copy(record.m_Data);
  m_sSourceName = record.m_sSourceName;
  m_sComputerName = record.m_sComputerName;

  return *this;
}



