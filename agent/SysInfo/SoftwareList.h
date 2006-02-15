// Document modified at : Sunday, December 07, 2003 11:23:26 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SoftwareList.h: interface for the CSoftwareList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOFTWARELIST_H__E36BC909_5DB5_4FD4_BB2F_260128477168__INCLUDED_)
#define AFX_SOFTWARELIST_H__E36BC909_5DB5_4FD4_BB2F_260128477168__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CSoftwareList : public CList<CSoftware, CSoftware&>   
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSoftwareList();
	virtual ~CSoftwareList();

};

#endif // !defined(AFX_SOFTWARELIST_H__E36BC909_5DB5_4FD4_BB2F_260128477168__INCLUDED_)
