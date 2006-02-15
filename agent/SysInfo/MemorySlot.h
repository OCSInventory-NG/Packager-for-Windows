// Document modified at : Saturday, January 03, 2004 11:32:46 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// MemorySlot.h: interface for the CMemorySlot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSLOT_H__B07E0FAA_CE82_4915_B2B4_5E622AA26582__INCLUDED_)
#define AFX_MEMORYSLOT_H__B07E0FAA_CE82_4915_B2B4_5E622AA26582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


#define MEMORY_SLOT_USAGE_RESERVED			0
#define MEMORY_SLOT_USAGE_OTHER				1
#define MEMORY_SLOT_USAGE_UNKNOWN			2
#define MEMORY_SLOT_USAGE_SYSTEM			3
#define MEMORY_SLOT_USAGE_VIDEO				4
#define MEMORY_SLOT_USAGE_FLASH				5
#define MEMORY_SLOT_USAGE_NONVOLATILE		6
#define MEMORY_SLOT_USAGE_CACHE				7

#define MEMORY_SLOT_TYPE_UNKNOWN			0
#define MEMORY_SLOT_TYPE_OTHER				1
#define MEMORY_SLOT_TYPE_DRAM				2
#define MEMORY_SLOT_TYPE_SYNCHRONOUS_DRAM	3
#define MEMORY_SLOT_TYPE_CACHE_DRAM			4
#define MEMORY_SLOT_TYPE_EDO				5
#define MEMORY_SLOT_TYPE_EDRAM				6
#define MEMORY_SLOT_TYPE_VRAM				7
#define MEMORY_SLOT_TYPE_SRAM				8
#define MEMORY_SLOT_TYPE_RAM				9
#define MEMORY_SLOT_TYPE_ROM				10
#define MEMORY_SLOT_TYPE_FLASH				11
#define MEMORY_SLOT_TYPE_EEPROM				12
#define MEMORY_SLOT_TYPE_FEPROM				13
#define MEMORY_SLOT_TYPE_EPROM				14
#define MEMORY_SLOT_TYPE_CDRAM				15
#define MEMORY_SLOT_TYPE_3DRAM				16
#define MEMORY_SLOT_TYPE_SDRAM				17
#define MEMORY_SLOT_TYPE_SGRAM				18
#define MEMORY_SLOT_TYPE_RDRAM				19
#define MEMORY_SLOT_TYPE_DDR				20

#define MEMORY_SLOT_ECC_RESERVED			0
#define MEMORY_SLOT_ECC_OTHER				1
#define MEMORY_SLOT_ECC_UNKNOWN				2
#define MEMORY_SLOT_ECC_NONE				3
#define MEMORY_SLOT_ECC_PARITY				4
#define MEMORY_SLOT_ECC_SINGLE_BIT			5
#define MEMORY_SLOT_ECC_MULTI_BIT			6
#define MEMORY_SLOT_ECC_CRC					7

class DLL_CLASS CMemorySlot  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CMemorySlot();
	virtual ~CMemorySlot();

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
	LPCTSTR GetCaption();
	LPCTSTR GetDescription();
	// Get memory max capacity in KB
	LPCTSTR GetCapacity();
	// Get memory usage (system, video, flash...)
	LPCTSTR GetUsage();
	// Get memory speed in MHz
	LPCTSTR GetSpeed();
	// Get memory type (EDO, SDRAM, DDR...)
	LPCTSTR GetType();
	// Get number of slots in the memory block
	UINT	GetSlotNumber();
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
	void Set( LPCTSTR lpstrCaption, LPCTSTR lpstrDescription, LPCTSTR lpstrCapacity, LPCTSTR lpstrUsage, LPCTSTR lpstrSpeed, LPCTSTR lpstrType, UINT uNumber);
	void SetCaption( LPCTSTR lpstrCaption);
	void SetDescription( LPCTSTR lpstrDescription);
	void SetCapacity( LPCTSTR lpstrCapacity);
	void SetUsage( LPCTSTR lpstrUsage);
	void SetUsage( DWORD dwUsage);
	void SetSpeed( LPCTSTR lpstrSpeed);
	void SetType( LPCTSTR lpstrType);
	void SetType( DWORD dwType);
	void SetTypeECC( DWORD dwECC);
	void SetSlotNumber( UINT uNumber);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csCaption;	// Caption
	CString m_csDescription;// Description
	CString m_csCapacity;	// Max capacity in KB
	CString m_csType;		// Memory type (EDO, SDRAM, DDR...)
	CString m_csSpeed;		// Memory access speed in MHz
	CString	m_csUsage;		// Memory usage (system, video, flash...)
	UINT	m_uSlotNumber;	// Number of slots in the memory block
};

#endif // !defined(AFX_MEMORYSLOT_H__B07E0FAA_CE82_4915_B2B4_5E622AA26582__INCLUDED_)
