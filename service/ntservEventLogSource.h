/*
Module : NTSERVEVENTLOGSOURCE.H
Purpose: Defines the interface for the class CNTEventLogSource.
Created: PJN / 14-07-1998

Copyright (c) 1997 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __NTSERVEVENTLOGSOURCE_H__
#define __NTSERVEVENTLOGSOURCE_H__

#ifndef CNTSERVICE_EXT_CLASS
#define CNTSERVICE_EXT_CLASS
#endif



////////////////////////////// Includes //////////////////////////////////////////////

#ifndef __AFXMT_H__
#include <afxmt.h>
#pragma message("To avoid this message please put afxmt.h in your PCH (normally stdafx.h)")
#endif



////////////////////////////// Classes ///////////////////////////////////////////////

//An encapsulation of the APIs used to register, unregister, write, install and uninstall Event log entries 
//i.e. the server side to the Event log APIs
class CNTSERVICE_EXT_CLASS CNTEventLogSource
{
public:
//Constructors / Destructors
  CNTEventLogSource();
	CNTEventLogSource(LPCTSTR lpUNCServerName, LPCTSTR lpSourceName);
	~CNTEventLogSource();

//Accessors / Mutators
  void    SetServerName(const CString& sServerName) { m_sServerName = sServerName; };
  CString GetServerName() const { return m_sServerName; };
  void    SetSourceName(const CString& sSourceName) { m_sSourceName = sSourceName; };
  CString GetSourceName() const { return m_sSourceName; };

//Methods
	operator HANDLE() const;
	BOOL Attach(HANDLE hEventSource);
	HANDLE Detach();
	BOOL Register(LPCTSTR lpUNCServerName, // server name for source 
                LPCTSTR lpSourceName 	   // source name for registered handle  
                );
	BOOL Deregister();
  BOOL Report(WORD wType,	        // event type to log 
							WORD wCategory,	    // event category 
							DWORD dwEventID,	  // event identifier 
							PSID lpUserSid,	    // user security identifier (optional) 
							WORD wNumStrings,	  // number of strings to merge with message  
							DWORD dwDataSize,	  // size of binary data, in bytes
							LPCTSTR* lpStrings,	// array of strings to merge with message 
							LPVOID lpRawData 	  // address of binary data 
 						  );
  BOOL Report(WORD wType, DWORD dwEventID);
  BOOL Report(WORD wType, LPCTSTR lpszString);
  BOOL Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString);
  BOOL Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2);
  BOOL Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2, LPCTSTR lpszString3);
  BOOL Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString1, LPCTSTR lpszString2, DWORD dwCode, BOOL bReportAsHex=FALSE);
  BOOL Report(WORD wType, DWORD dwEventID, LPCTSTR lpszString, DWORD dwCode, BOOL bReportAsHex=FALSE);
  BOOL Report(WORD wType, DWORD dwEventID, DWORD dwCode, BOOL bReportAsHex=FALSE);

	static BOOL Install(LPCTSTR lpSourceName, LPCTSTR lpEventMessageFile, DWORD dwTypesSupported);
  static BOOL Uninstall(LPCTSTR lpSourceName);
  static BOOL GetStringArrayFromRegistry(HKEY hKey, LPCTSTR lpszEntry, CStringArray& array, DWORD* pLastError = NULL);
  static BOOL SetStringArrayIntoRegistry(HKEY hKey, LPCTSTR lpszEntry, const CStringArray& array, DWORD* pLastError = NULL);
  
protected:
  HANDLE           m_hEventSource;
  CString          m_sServerName;
  CString          m_sSourceName;
  CCriticalSection m_csReport; //Critical section to protect multiple threads calling Report at the one time

  friend class CNTService;
};

#endif //__NTSERVEVENTLOGSOURCE_H__
