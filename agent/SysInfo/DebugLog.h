// Document modified at : Friday, October 10, 2003 10:44:32 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DebugLog.h: interface for the CDebugLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUGLOG_H__0CB97901_C4D7_11D5_B2E3_0040055338AF__INCLUDED_)
#define AFX_DEBUGLOG_H__0CB97901_C4D7_11D5_B2E3_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


void DLL_CLASS OpenLog( LPCTSTR lpstrFolder, LPCTSTR lpstrCommandLine);
void DLL_CLASS AddLog( LPCTSTR lpstrLog,...);
void DLL_CLASS CloseLog();

#endif // !defined(AFX_DEBUGLOG_H__0CB97901_C4D7_11D5_B2E3_0040055338AF__INCLUDED_)
