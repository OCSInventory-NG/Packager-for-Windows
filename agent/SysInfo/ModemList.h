// Document modified at : Saturday, December 06, 2003 11:25:02 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

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

};

#endif // !defined(AFX_MODEMLIST_H__D965CF4B_51B1_474D_B615_3D4150A16F44__INCLUDED_)
