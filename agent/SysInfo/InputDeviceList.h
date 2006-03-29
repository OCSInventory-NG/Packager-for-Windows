// Document modified at : Tuesday, March 28, 2006 3:58:10 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// InputDeviceList.h: interface for the CInputDeviceList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INPUTDEVICELIST_H__91B9F0C4_E2FD_4855_B89B_888B2CCE0616__INCLUDED_)
#define AFX_INPUTDEVICELIST_H__91B9F0C4_E2FD_4855_B89B_888B2CCE0616__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CInputDeviceList : public CList<CInputDevice, CInputDevice&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CInputDeviceList();
	virtual ~CInputDeviceList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};

#endif // !defined(AFX_INPUTDEVICELIST_H__91B9F0C4_E2FD_4855_B89B_888B2CCE0616__INCLUDED_)

