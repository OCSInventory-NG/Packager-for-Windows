// Document modified at : Tuesday, March 28, 2006 7:02:12 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

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
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_LOGICALDRIVELIST_H__859CC4DB_15B4_4DEE_A9D9_0EA772FC76A9__INCLUDED_)

