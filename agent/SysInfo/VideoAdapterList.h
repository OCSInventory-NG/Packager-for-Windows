// Document modified at : Tuesday, March 28, 2006 9:22:52 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// VideoAdapterList.h: interface for the CVideoAdapterList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIDEOADAPTERLIST_H__DE761F15_8847_11D5_B278_0040055338AF__INCLUDED_)
#define AFX_VIDEOADAPTERLIST_H__DE761F15_8847_11D5_B278_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CVideoAdapterList : public CList<CVideoAdapter, CVideoAdapter&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CVideoAdapterList();
	virtual ~CVideoAdapterList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_VIDEOADAPTERLIST_H__DE761F15_8847_11D5_B278_0040055338AF__INCLUDED_)

