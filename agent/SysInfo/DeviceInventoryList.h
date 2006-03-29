// Document modified at : Wednesday, March 29, 2006 1:28:13 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceInventoryList.h: interface for the CDeviceInventoryList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEINVENTORYLIST_H__E96C751D_5F89_478C_AA46_EBC40199FA9B__INCLUDED_)
#define AFX_DEVICEINVENTORYLIST_H__E96C751D_5F89_478C_AA46_EBC40199FA9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CDeviceInventoryList : public CList<CDeviceInventory, CDeviceInventory&>    
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceInventoryList();
	virtual ~CDeviceInventoryList();
};
#endif // !defined(AFX_DEVICEINVENTORYLIST_H__E96C751D_5F89_478C_AA46_EBC40199FA9B__INCLUDED_)

