// Document modified at : Saturday, December 06, 2003 11:25:02 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// LogicalDriveList.h: interface for the CLogicalDriveList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICALDRIVELIST_H__859CC4DB_15B4_4DEE_A9D9_0EA772FC76A9__INCLUDED_)
#define AFX_LOGICALDRIVELIST_H__859CC4DB_15B4_4DEE_A9D9_0EA772FC76A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CLogicalDriveList : public CList<CLogicalDrive, CLogicalDrive&>   
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CLogicalDriveList();
	virtual ~CLogicalDriveList();

};

#endif // !defined(AFX_LOGICALDRIVELIST_H__859CC4DB_15B4_4DEE_A9D9_0EA772FC76A9__INCLUDED_)
