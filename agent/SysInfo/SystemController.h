// Document modified at : Wednesday, March 29, 2006 1:44:09 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO


//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemController.h: interface for the CSystemController class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMCONTROLLER_H__C2B544BB_1F51_4D7F_8978_17AF12FF645B__INCLUDED_)
#define AFX_SYSTEMCONTROLLER_H__C2B544BB_1F51_4D7F_8978_17AF12FF645B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SYSTEM_CONTROLER_FLOPPY		_T( "Floppy Controller")
#define SYSTEM_CONTROLER_IDE		_T( "IDE Controller")
#define SYSTEM_CONTROLER_SCSI		_T( "SCSI Controller")
#define SYSTEM_CONTROLER_INFRARED	_T( "Infrared Controller")
#define SYSTEM_CONTROLER_USB		_T( "USB Controller")
#define SYSTEM_CONTROLER_IEEE1394	_T( "IEEE1394 Controller")
#define SYSTEM_CONTROLER_PCMCIA		_T( "PCMCIA Controller")
#define SYSTEM_CONTROLER_SATA		_T( "Serial ATA Controller")

#include "SysInfoClasses.h"

class DLL_CLASS CSystemController  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemController();
	virtual ~CSystemController();

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
	LPCTSTR GetDescription();
	LPCTSTR GetCaption();
	LPCTSTR GetHardwareVersion();
	LPCTSTR GetName();
	LPCTSTR GetType();
	LPCTSTR GetManufacturer();
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
	void Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrName, LPCTSTR lpstrVersion, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetCaption( LPCTSTR lpstrCaption);
	void SetHardwareVersion( LPCTSTR lpstrVersion);
	void SetName( LPCTSTR lpstrName);
	void SetType( LPCTSTR lpstrType);
	void SetManufacturer( LPCTSTR lpstrManufacturer);

protected: // Attributes
	ULONG	m_ulID;				// Database record ID
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString m_csType;			// Controller type (Floppy, IDE, SCSI, PCMCIA...)
	CString m_csManufacturer;	// Manufacturer
	CString m_csName;			// Name
	CString m_csHardwareVersion;// Hardware or firmware version
	CString m_csCaption;		// Caption
	CString m_csDescription;	// Description
};
#endif // !defined(AFX_SYSTEMCONTROLLER_H__C2B544BB_1F51_4D7F_8978_17AF12FF645B__INCLUDED_)

