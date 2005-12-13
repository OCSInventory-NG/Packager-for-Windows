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

};

#endif // !defined(AFX_MONITORLIST_H__6DCE229B_71C0_4A4D_B442_FA2BE2606853__INCLUDED_)
