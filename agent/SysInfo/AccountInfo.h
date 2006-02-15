// Document modified at : Sunday, January 04, 2004 5:46:36 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET 2005
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// AccountInfo.h: interface for the CAccountInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Gie_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_)
#define AFX_Gie_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CAccountInfo  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CAccountInfo();
	virtual ~CAccountInfo();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX,CString file );

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////


	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name

protected: // Attributes
	CString	m_csDeviceID;	// Device unique ID

};

#endif // !defined(AFX_Gie_H__FC47C324_9B26_4C73_945F_5E7761E676F9__INCLUDED_)
