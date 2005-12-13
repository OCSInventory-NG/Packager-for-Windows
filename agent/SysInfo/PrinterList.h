// Document modified at : Monday, November 03, 2003 11:02:30 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// PrinterList.h: interface for the CPrinterList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PRINTERLIST_H__EB59F014_89CE_11D5_B284_0040055338AF__INCLUDED_)
#define AFX_PRINTERLIST_H__EB59F014_89CE_11D5_B284_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CPrinterList : public CList<CPrinter, CPrinter&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CPrinterList();
	virtual ~CPrinterList();

};

#endif // !defined(AFX_PRINTERLIST_H__EB59F014_89CE_11D5_B284_0040055338AF__INCLUDED_)
