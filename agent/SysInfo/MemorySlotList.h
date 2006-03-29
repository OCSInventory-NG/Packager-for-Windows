// Document modified at : Tuesday, March 28, 2006 7:12:17 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// MemorySlotList.h: interface for the CMemorySlotList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYSLOTLIST_H__C516FC9E_571E_4CFE_BB73_0E6D7C0ECA66__INCLUDED_)
#define AFX_MEMORYSLOTLIST_H__C516FC9E_571E_4CFE_BB73_0E6D7C0ECA66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CMemorySlotList : public CList<CMemorySlot, CMemorySlot&> 
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CMemorySlotList();
	virtual ~CMemorySlotList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};

#endif // !defined(AFX_MEMORYSLOTLIST_H__C516FC9E_571E_4CFE_BB73_0E6D7C0ECA66__INCLUDED_)

