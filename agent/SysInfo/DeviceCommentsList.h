// Document modified at : Tuesday, December 09, 2003 11:34:06 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceCommentsList.h: interface for the CDeviceCommentsList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICECOMMENTSLIST_H__657D97A6_9211_4919_82BA_20794D56AFF4__INCLUDED_)
#define AFX_DEVICECOMMENTSLIST_H__657D97A6_9211_4919_82BA_20794D56AFF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CDeviceCommentsList : public CList<CDeviceComments, CDeviceComments&>  
{
public:
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceCommentsList();
	virtual ~CDeviceCommentsList();
};

#endif // !defined(AFX_DEVICECOMMENTSLIST_H__657D97A6_9211_4919_82BA_20794D56AFF4__INCLUDED_)
