// Document modified at : Tuesday, March 28, 2006 7:16:05 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModemList.h: interface for the CModemList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODEMLIST_H__D965CF4B_51B1_474D_B615_3D4150A16F44__INCLUDED_)
#define AFX_MODEMLIST_H__D965CF4B_51B1_474D_B615_3D4150A16F44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CModemList : public CList<CModem, CModem&>
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CModemList();
	virtual ~CModemList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_MODEMLIST_H__D965CF4B_51B1_474D_B615_3D4150A16F44__INCLUDED_)

