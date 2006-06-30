// Document modified at : Wednesday, March 29, 2006 1:13:27 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// AccessLogInfo.h: interface for the CAccessLogInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ACCESSLOG_H__3A200601_4875_11D5_B231_0040055338AF__INCLUDED_)
#define AFX_ACCESSLOG_H__3A200601_4875_11D5_B231_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CAccessLog  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CAccessLog();
	virtual ~CAccessLog();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return the database record ID
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	// Return the User ID
	LPCTSTR GetUserID();
	// Return the logon date
	LPCTSTR GetLogonDate();
	// Return the processes status
	LPCTSTR GetProcessesStatus();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX );


	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	void SetID( ULONG ulID);
	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	// Set the user ID
	void SetUserID( LPCTSTR lpstrUserID);
	// Set user's logon date from string
	void SetLogonDate( LPCTSTR lpstrDate);
	// Set user's logon date from date object
	void SetLogonDate( COleDateTime &dtDate);
	// Set process status string
	void SetProcessesStatus( LPCTSTR lpstrProcess);
	// Retrieve the informations for the current Device
	BOOL Retrieve( LPCTSTR lpstrDeviceID, LPCTSTR lpstrUserID, LPCTSTR lpstrProcessesNames);

protected: // Methods
	// Return TRUE if no error
	BOOL CheckRunningProcesses( LPCTSTR lpstrProcessesNames, CString &csProcessesStatus);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csUserID;			// User identity
	CString m_csLogonDate;		// User logon date
	CString m_csProcessesStatus;// Result of the processes check status
};
#endif // !defined(AFX_ACCESSLOG_H__3A200601_4875_11D5_B231_0040055338AF__INCLUDED_)

