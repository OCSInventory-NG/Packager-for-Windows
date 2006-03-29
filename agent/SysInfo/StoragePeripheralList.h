// Document modified at : Tuesday, March 28, 2006 9:12:29 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// StoragePeripheralList.h: interface for the CStoragePeripheralList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STORAGEPERIPHERALLIST_H__21D2FFA5_E1B2_460A_AA3E_56712989CAC3__INCLUDED_)
#define AFX_STORAGEPERIPHERALLIST_H__21D2FFA5_E1B2_460A_AA3E_56712989CAC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS  CStoragePeripheralList : public CList<CStoragePeripheral, CStoragePeripheral&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CStoragePeripheralList();
	virtual ~CStoragePeripheralList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_STORAGEPERIPHERALLIST_H__21D2FFA5_E1B2_460A_AA3E_56712989CAC3__INCLUDED_)

