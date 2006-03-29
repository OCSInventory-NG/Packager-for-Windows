// Document modified at : Wednesday, March 29, 2006 11:11:00 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// MemorySlot.cpp: implementation of the CMemorySlot class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemorySlot.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemorySlot::CMemorySlot()
{
	Clear();
}

CMemorySlot::~CMemorySlot()
{
	Clear();
}

ULONG CMemorySlot::GetID()
{
	return m_ulID;
}

LPCTSTR CMemorySlot::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CMemorySlot::GetCaption()
{
	return m_csCaption;
}

LPCTSTR CMemorySlot::GetDescription()
{
	return m_csDescription;
}

LPCTSTR CMemorySlot::GetCapacity()
{
	return m_csCapacity;
}

LPCTSTR CMemorySlot::GetUsage()
{
	return m_csUsage;
}

LPCTSTR CMemorySlot::GetSpeed()
{
	return m_csSpeed;
}

LPCTSTR CMemorySlot::GetType()
{
	return m_csType;
}

UINT CMemorySlot::GetSlotNumber()
{
	return m_uSlotNumber;
}

void CMemorySlot::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CMemorySlot::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CMemorySlot::SetCaption(LPCTSTR lpstrCaption)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
}

void CMemorySlot::SetDescription(LPCTSTR lpstrDescription)
{
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
}

void CMemorySlot::SetCapacity(LPCTSTR lpstrCapacity)
{
	if ((lpstrCapacity != NULL) &&
		(_tcslen( lpstrCapacity) > 0))
		m_csCapacity = lpstrCapacity;
	else
		m_csCapacity = NOT_AVAILABLE;
	StrForSQL( m_csCapacity);
}

void CMemorySlot::SetUsage(DWORD dwUsage)
{
	switch (dwUsage)
	{
	case MEMORY_SLOT_USAGE_RESERVED:
		m_csUsage = _T( "Reserved");
		break;
	case MEMORY_SLOT_USAGE_OTHER:
		m_csUsage = _T( "Other");
		break;
	case MEMORY_SLOT_USAGE_SYSTEM:
		m_csUsage = _T( "System Memory");
		break;
	case MEMORY_SLOT_USAGE_VIDEO:
		m_csUsage = _T( "Video Memory");
		break;
	case MEMORY_SLOT_USAGE_FLASH:
		m_csUsage = _T( "Flash Memory");
		break;
	case MEMORY_SLOT_USAGE_NONVOLATILE:
		m_csUsage = _T( "Non-volatile RAM");
		break;
	case MEMORY_SLOT_USAGE_CACHE:
		m_csUsage = _T( "Cache Memory");
		break;
	case MEMORY_SLOT_USAGE_UNKNOWN:
		m_csUsage = _T( "Unknown");
		break;
	default:
		m_csUsage.Format( _T( "%s (%lu)"), NOT_AVAILABLE, dwUsage);
		break;
	}
}

void CMemorySlot::SetUsage(LPCTSTR lpstrUsage)
{
	m_csUsage = lpstrUsage;
	StrForSQL( m_csUsage);
}

void CMemorySlot::SetSpeed(LPCTSTR lpstrSpeed)
{
	if ((lpstrSpeed != NULL) &&
		(_tcslen( lpstrSpeed) > 0))
		m_csSpeed = lpstrSpeed;
	else
		m_csSpeed = NOT_AVAILABLE;
	StrForSQL( m_csSpeed);
}

void CMemorySlot::SetType(DWORD dwType)
{
	// Type of memory
	switch (dwType)
	{
	case MEMORY_SLOT_TYPE_OTHER:
		m_csType = _T( "Other");
		break;
	case MEMORY_SLOT_TYPE_DRAM:
		m_csType = _T( "DRAM");
		break;
	case MEMORY_SLOT_TYPE_SYNCHRONOUS_DRAM:
		m_csType = _T( "Synchronous DRAM");
		break;
	case MEMORY_SLOT_TYPE_CACHE_DRAM:
		m_csType = _T( "Cache DRAM");
		break;
	case MEMORY_SLOT_TYPE_EDO:
		m_csType = _T( "EDO");
		break;
	case MEMORY_SLOT_TYPE_EDRAM:
		m_csType = _T( "EDRAM");
		break;
	case MEMORY_SLOT_TYPE_VRAM:
		m_csType = _T( "VRAM");
		break;
	case MEMORY_SLOT_TYPE_SRAM:
		m_csType = _T( "SRAM");
		break;
	case MEMORY_SLOT_TYPE_RAM:
		m_csType = _T( "RAM");
		break;
	case MEMORY_SLOT_TYPE_ROM:
		m_csType = _T( "ROM");
		break;
	case MEMORY_SLOT_TYPE_FLASH:
		m_csType = _T( "Flash");
		break;
	case MEMORY_SLOT_TYPE_EEPROM:
		m_csType = _T( "EEPROM");
		break;
	case MEMORY_SLOT_TYPE_FEPROM:
		m_csType = _T( "FEPROM");
		break;
	case MEMORY_SLOT_TYPE_EPROM:
		m_csType = _T( "EPROM");
		break;
	case MEMORY_SLOT_TYPE_CDRAM:
		m_csType = _T( "CDRAM");
		break;
	case MEMORY_SLOT_TYPE_3DRAM:
		m_csType = _T( "3DRAM");
		break;
	case MEMORY_SLOT_TYPE_SDRAM:
		m_csType = _T( "SDRAM");
		break;
	case MEMORY_SLOT_TYPE_SGRAM:
		m_csType = _T( "SGRAM");
		break;
	case MEMORY_SLOT_TYPE_RDRAM:
		m_csType = _T( "RDRAM");
		break;
	case MEMORY_SLOT_TYPE_DDR:
		m_csType = _T( "DDR");
		break;
	case MEMORY_SLOT_TYPE_UNKNOWN:
		m_csType = _T( "Unknown");
		break;
	default:
		m_csType.Format( _T( "%s (%lu)"), NOT_AVAILABLE, dwType);
		break;
	}
}

void CMemorySlot::SetTypeECC( DWORD dwECC)
{
	CString csECC;

	// Error correction
	switch (dwECC)
	{
	case MEMORY_SLOT_ECC_RESERVED:
		csECC.Format( _T( " (Reserved ECC)"));
		break;
	case MEMORY_SLOT_ECC_OTHER:
		csECC.Format( _T( " (Other ECC)"));
		break;
	case MEMORY_SLOT_ECC_NONE:
		csECC.Format( _T( " (No ECC)"));
		break;
	case MEMORY_SLOT_ECC_PARITY:
		csECC.Format( _T( " (Parity ECC)"));
		break;
	case MEMORY_SLOT_ECC_SINGLE_BIT:
		csECC.Format( _T( " (Single-bit ECC)"));
		break;
	case MEMORY_SLOT_ECC_MULTI_BIT:
		csECC.Format( _T( " (Multi-bit ECC)"));
		break;
	case MEMORY_SLOT_ECC_CRC:
		csECC.Format( _T( " (CRC ECC)"));
		break;
	case MEMORY_SLOT_ECC_UNKNOWN:
	default:
		csECC.Format( _T( " (Unknown ECC)"));
		break;
	}
	m_csDescription += csECC;
}

void CMemorySlot::SetType(LPCTSTR lpstrType)
{
	m_csType = lpstrType;
	StrForSQL( m_csType);
}

void CMemorySlot::SetSlotNumber(UINT uNumber)
{
	m_uSlotNumber = uNumber;
}

void CMemorySlot::Set( LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCTSTR lpstrCapacity, LPCTSTR lpstrUsage, LPCTSTR lpstrSpeed, LPCTSTR lpstrType, UINT uNumber)
{
	m_csCaption = lpstrCaption;
	StrForSQL( m_csCaption);
	m_csDescription = lpstrDescription;
	StrForSQL( m_csDescription);
	m_csCapacity = lpstrCapacity;
	StrForSQL( m_csCapacity);
	m_csUsage = lpstrUsage;
	StrForSQL( m_csUsage);
	m_csSpeed = lpstrSpeed;
	StrForSQL( m_csSpeed);
	m_csType = lpstrType;
	StrForSQL( m_csType);
	m_uSlotNumber = uNumber;
}

BOOL CMemorySlot::FormatXML(CMarkup* pX)
{
pX->AddElem("MEMORIES");
	pX->IntoElem();
		pX->AddElemNV("CAPTION",m_csCaption);
		pX->AddElemNV("DESCRIPTION",m_csDescription);
		pX->AddElemNV("CAPACITY",m_csCapacity);
		pX->AddElemNV("PURPOSE",m_csUsage);
		pX->AddElemNV("TYPE",m_csType);
		pX->AddElemNV("SPEED",m_csSpeed);
		pX->AddElemNV("NUMSLOTS",m_uSlotNumber);	
	pX->OutOfElem();		
	return TRUE;
}

void CMemorySlot::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CMemorySlot::GetDeviceName()
{
	return m_csDeviceName;
}

void CMemorySlot::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csCaption.Empty();	
	m_csDescription.Empty();
	m_csCapacity.Empty();	
	m_csType.Empty();		
	m_csSpeed.Empty();		
	m_csUsage.Empty();		
	m_uSlotNumber = 0;	
}
