// Document modified at : Wednesday, March 29, 2006 1:42:09 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Software.h: interface for the CSoftware class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFTWARE_H__C4903B6B_8BDE_11D4_8077_0040055338AF__INCLUDED_)
#define AFX_SOFTWARE_H__C4903B6B_8BDE_11D4_8077_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CSoftware  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSoftware();
	virtual ~CSoftware();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return the database record ID
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	// Get the app publisher
	LPCTSTR GetPublisher();
	// Get the app friendly name
	LPCTSTR GetName();
	// Get the app version
	LPCTSTR GetVersion();
	// Get the app folder location C:\MyAppFolder
	LPCTSTR GetFolder();
	// Get the app comments
	LPCTSTR GetComments();
	// Get the app GUID
	LPCTSTR GetGUID();
	// Get the app language
	LPCTSTR GetLanguage();
	// Get the app filename
	LPCTSTR GetFilename();
	// Get the app filezie
	ULONG GetFilesize();
	// Is app extracted from registry
	BOOL IsFromRegistry();
	// Get the source in string format
	LPCTSTR GetSource();
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
	// Set the Software attributes
	void Set( LPCTSTR lpstrPublisher, LPCTSTR lpstrName, LPCTSTR lpstrVersion, LPCTSTR lpstrFolder, LPCTSTR lpstrComments, LPCTSTR lpstrFilename = NOT_AVAILABLE, ULONG ulSize = 0, BOOL bFromRegistry = FALSE);
	// Set the publisher name
	void SetPublisher( LPCTSTR lpstrPublisher);
	// Set the app name
	void SetName( LPCTSTR lpstrName);
	// Set the app version
	void SetVersion( LPCTSTR lpstrVersion);
	// Set the app folder location
	void SetFolder( LPCTSTR lpstrFolder);
	// Set the app comments
	void SetComments( LPCTSTR lpstrComments);
	// Set the app GUID
	void SetGUID( LPCTSTR lpstrGUID);
	// Set the app language
	void SetLanguage( LPCTSTR lpstrLanguage);
	// Set the app filename
	void SetFilename( LPCTSTR lpstrFilename);
	// Set the app filesize
	void SetFilesize( ULONG ulSize);
	// Set if the app is extracted from the registry
	void SetFromRegistry( BOOL bFromRegistry = FALSE);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csPublisher;	// Publisher Microsoft
	CString m_csName;		// Name Word
	CString m_csVersion;	// Version
	CString m_csFolder;		// File folder C:\MyAppDir
	CString m_csComments;	// Comments
	CString m_csGUID;		// GUID of app
	CString m_csLanguage;	// Language of app
	CString m_csFilename;	// Filename of app
	ULONG	m_ulFilesize;	// Size in bytes of file app
	BOOL	m_bFromRegistry;// Extracted from registry ?
};
#endif // !defined(AFX_SOFTWARE_H__C4903B6B_8BDE_11D4_8077_0040055338AF__INCLUDED_)

