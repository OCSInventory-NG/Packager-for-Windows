// Document modified at : Tuesday, March 28, 2006 7:18:27 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// MonitorList.h: interface for the CMonitorList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MONITORLIST_H__6DCE229B_71C0_4A4D_B442_FA2BE2606853__INCLUDED_)
#define AFX_MONITORLIST_H__6DCE229B_71C0_4A4D_B442_FA2BE2606853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS CMonitorList : public CList<CMonitor, CMonitor&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CMonitorList();
	virtual ~CMonitorList();
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
};
#endif // !defined(AFX_MONITORLIST_H__6DCE229B_71C0_4A4D_B442_FA2BE2606853__INCLUDED_)

