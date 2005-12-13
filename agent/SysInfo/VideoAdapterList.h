// Document modified at : Monday, November 03, 2003 11:06:38 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

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

};

#endif // !defined(AFX_VIDEOADAPTERLIST_H__DE761F15_8847_11D5_B278_0040055338AF__INCLUDED_)
