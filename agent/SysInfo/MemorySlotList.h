
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

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

};

#endif // !defined(AFX_MEMORYSLOTLIST_H__C516FC9E_571E_4CFE_BB73_0E6D7C0ECA66__INCLUDED_)
