// Document modified at : Sunday, January 04, 2004 7:30:44 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemControllerList.h: interface for the CSystemControllerList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMCONTROLLERLIST_H__09308B4F_199B_4D87_AEF9_AE219D44B044__INCLUDED_)
#define AFX_SYSTEMCONTROLLERLIST_H__09308B4F_199B_4D87_AEF9_AE219D44B044__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CSystemControllerList : public CList<CSystemController, CSystemController&>   
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemControllerList();
	virtual ~CSystemControllerList();

};

#endif // !defined(AFX_SYSTEMCONTROLLERLIST_H__09308B4F_199B_4D87_AEF9_AE219D44B044__INCLUDED_)
