// Document modified at : Saturday, December 06, 2003 11:25:02 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
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
