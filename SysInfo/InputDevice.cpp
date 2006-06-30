// Document modified at : Wednesday, March 29, 2006 11:10:21 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// InputDevice.cpp: implementation of the CInputDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "InputDevice.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInputDevice::CInputDevice()
{
	Clear();
}

CInputDevice::~CInputDevice()
{
	Clear();
}

ULONG CInputDevice::GetID()
{
	return m_ulID;
}

LPCTSTR CInputDevice::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CInputDevice::GetManufacturer()
{
	return m_csManufacturer;
}

LPCTSTR CInputDevice::GetType()
{
	return m_csType;
}

LPCTSTR CInputDevice::GetCaption()
{
	return m_csCaption;
}

LPCTSTR CInputDevice::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CInputDevice::GetPointingType()
{
	return m_csPointingType;
}

LPCTSTR CInputDevice::GetPointingInterface()
{
	return m_csInterface;
}

void CInputDevice::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CInputDevice::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CInputDevice::SetManufacturer(LPCTSTR lpstrManufacturer)
{
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
}

void CInputDevice::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CInputDevice::SetCaption(LPCTSTR lpstrCaption)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
}

void CInputDevice::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CInputDevice::SetPointingType(LPCTSTR lpstrPointingType)
{
	m_csPointingType = lpstrPointingType;
	StrForSQL( m_csPointingType);
}

void CInputDevice::SetPointingType(DWORD dwPointingType)
{
	switch (dwPointingType)
	{
	case 1: // Other
		m_csPointingType = _T( "Other");
		break;
	case 2: // Unknown
		m_csPointingType = NOT_AVAILABLE;
		break;
	case 3: // Mouse
		m_csPointingType = _T( "Mouse");
		break;
	case 4: // Track Ball
		m_csPointingType = _T( "Track Ball");
		break;
	case 5: // Track Point
		m_csPointingType = _T( "Track Point");
		break;
	case 6: // Glide Point
		m_csPointingType = _T( "Glide Point");
		break;
	case 7: // Touch Pad
		m_csPointingType = _T( "Touch Pad");
		break;
	case 8: // Touch Screen
		m_csPointingType = _T( "Touch Screen");
		break;
	case 9: // Mouse - Optical Sensor
		m_csPointingType = _T( "Mouse - Optical Sensor");
		break;
	default: // Unknown
		m_csPointingType.Format( _T( "%s (%lu)"), NOT_AVAILABLE, dwPointingType);
		break;
	}
}

void CInputDevice::SetPointingInterface(LPCTSTR lpstrInterface)
{
	m_csInterface = lpstrInterface;
	StrForSQL( m_csInterface);
}

void CInputDevice::SetPointingInterface(DWORD dwInterface)
{
	switch (dwInterface)
	{
	case 1: // Other
		m_csInterface = _T( "Other");
		break;
	case 2: // Unknown
		m_csInterface = NOT_AVAILABLE;
		break;
	case 3: // Serial
		m_csInterface = _T( "Serial");
		break;
	case 4: // PS/2
		m_csInterface = _T( "PS/2");
		break;
	case 5: // Infrared
		m_csInterface = _T( "Infrared");
		break;
	case 6: // HP-HIL
		m_csInterface = _T( "HP-HIL");
		break;
	case 7: // Bus mouse
		m_csInterface = _T( "Bus mouse");
		break;
	case 8: // ADB
		m_csInterface = _T( "Apple Desktop Bus");
		break;
	case 160: // Bus mouse DB-9
		m_csInterface = _T( "Bus mouse DB-9");
		break;
	case 161: // Bus mouse micro-DIN
		m_csInterface = _T( "Bus mouse micro-DIN");
		break;
	case 162: // USB
		m_csInterface = _T( "USB");
		break;
	default: // Unknwon
		m_csInterface.Format( _T( "%s (%lu)"), NOT_AVAILABLE, dwInterface);
		break;
	}
}

void CInputDevice::Set( LPCTSTR lpstrType, LPCTSTR lpstrManufacturer, LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCTSTR lpstrPointingType, LPCTSTR lpstrInterface)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_csManufacturer = lpstrManufacturer;
	StrForSQL( m_csManufacturer);
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
	m_csPointingType = lpstrPointingType;
	StrForSQL( m_csPointingType);
	m_csInterface = lpstrInterface;
	StrForSQL( m_csInterface);
}

BOOL CInputDevice::FormatXML(CMarkup* pX)
{
	pX->AddElem("INPUTS");
	pX->IntoElem();
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("MANUFACTURER",m_csManufacturer);
		pX->AddElemNV("CAPTION",m_csCaption);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("INTERFACE",m_csInterface);
		pX->AddElemNV("POINTTYPE",m_csPointingType);
	pX->OutOfElem();
	return TRUE;
}

void CInputDevice::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CInputDevice::GetDeviceName()
{
	return m_csDeviceName;
}

void CInputDevice::Clear()
{
	m_ulID = 0;	
	m_csDeviceID.Empty();
	m_csDeviceName.Empty();		
	m_csType.Empty();			
	m_csManufacturer.Empty();	
	m_csCaption.Empty();		
	m_csDescription.Empty();	
	m_csPointingType.Empty();	
	m_csInterface.Empty();		
}
