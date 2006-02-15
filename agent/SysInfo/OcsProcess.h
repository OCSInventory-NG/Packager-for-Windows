// Document modified at : Saturday, December 06, 2003 11:36:20 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// OcsProcess.h: interface for the CProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OCSPROCESS_H__05D45087_83E3_482C_9927_E7423B6C0502__INCLUDED_)
#define AFX_OCSPROCESS_H__05D45087_83E3_482C_9927_E7423B6C0502__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class CProcess  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CProcess();
	virtual ~CProcess();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	static BOOL IsProcessRunning(LPCTSTR lpstrProcessName);

protected: // Methods
	static BOOL IsProcessRunning9X(LPCTSTR lpstrProcessName);
	static BOOL IsProcessRunningNT(LPCTSTR lpstrProcessName);
};

#endif // !defined(AFX_OCSPROCESS_H__05D45087_83E3_482C_9927_E7423B6C0502__INCLUDED_)
