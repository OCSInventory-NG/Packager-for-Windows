// Document modified at : Tuesday, March 28, 2006 9:18:43 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemPortList.h: interface for the CSystemPortList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMPORTLIST_H__2A8DF271_A4B9_47A1_ACD7_455B1E6C24B5__INCLUDED_)
#define AFX_SYSTEMPORTLIST_H__2A8DF271_A4B9_47A1_ACD7_455B1E6C24B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CSystemPortList : public CList<CSystemPort, CSystemPort&> 
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSystemPortList();
	virtual ~CSystemPortList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_SYSTEMPORTLIST_H__2A8DF271_A4B9_47A1_ACD7_455B1E6C24B5__INCLUDED_)

