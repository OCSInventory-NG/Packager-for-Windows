// Document modified at : Sunday, January 04, 2004 5:05:20 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// InputDevice.h: interface for the CInputDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTDEVICE_H__5BCE7A79_F8EC_4281_BF76_58D394AE4E08__INCLUDED_)
#define AFX_INPUTDEVICE_H__5BCE7A79_F8EC_4281_BF76_58D394AE4E08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


#define INPUT_DEVICE_KEYBOARD	_T( "Keyboard")
#define INPUT_DEVICE_POINTING	_T( "Pointing")

class DLL_CLASS CInputDevice  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CInputDevice();
	virtual ~CInputDevice();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return the database record ID
	ULONG GetID();
	// Return the Device ID
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	LPCTSTR GetType();
	LPCTSTR GetManufacturer();
	LPCTSTR GetCaption();
	LPCTSTR GetDescription();
	LPCTSTR GetPointingType();
	LPCTSTR GetPointingInterface();
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
	void Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCTSTR lpstrPointingType, LPCTSTR lpstrInterface);
	void SetType( LPCTSTR lpstrType);
	void SetManufacturer( LPCTSTR lpstrManufacturer);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetCaption( LPCTSTR lpstrCaption);
	void SetPointingType( LPCTSTR lpstrPointingType);
	void SetPointingType( DWORD dwPointingType);
	void SetPointingInterface( LPCTSTR lpstrInterface);
	void SetPointingInterface( DWORD dwInterface);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csType;			// Input type (keyboard, pointing)
	CString m_csManufacturer;	// Input Device manufacturer
	CString m_csCaption;		// Caption
	CString m_csDescription;	// Description
	CString m_csPointingType;	// Pointing device type (trackball, trackpoint,touchpad,mouse...)
	CString m_csInterface;		// Pointing device interface (Serial, PS/2, Infrared, USB...)
};

#endif // !defined(AFX_INPUTDEVICE_H__5BCE7A79_F8EC_4281_BF76_58D394AE4E08__INCLUDED_)
