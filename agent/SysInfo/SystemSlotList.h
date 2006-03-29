// Document modified at : Tuesday, March 28, 2006 9:20:19 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemSlotList.h: interface for the CSystemSlotList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMSLOTLIST_H__206470BA_A221_41A4_B55E_4BD618E23911__INCLUDED_)
#define AFX_SYSTEMSLOTLIST_H__206470BA_A221_41A4_B55E_4BD618E23911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CSystemSlotList : public CList<CSystemSlot, CSystemSlot&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemSlotList();
	virtual ~CSystemSlotList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_SYSTEMSLOTLIST_H__206470BA_A221_41A4_B55E_4BD618E23911__INCLUDED_)

