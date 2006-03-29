// Document modified at : Wednesday, March 29, 2006 1:31:09 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO


//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// IPHelper.h: interface for the CIPHelper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPHELPER_H__609EE787_2041_44FB_863D_75B36F337728__INCLUDED_)
#define AFX_IPHELPER_H__609EE787_2041_44FB_863D_75B36F337728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CIPHelper  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CIPHelper();
	virtual ~CIPHelper();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////
	static BOOL GetNetworkAdapters( CNetworkAdapterList *pList);
};
#endif // !defined(AFX_IPHELPER_H__609EE787_2041_44FB_863D_75B36F337728__INCLUDED_)

