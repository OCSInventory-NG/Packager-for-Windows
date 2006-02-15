// Document modified at : Saturday, December 06, 2003 11:25:04 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SNMP.h: interface for the CSNMP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNMP_H__3CFE0AD8_CC5A_4A0C_8BED_28A055A3C960__INCLUDED_)
#define AFX_SNMP_H__3CFE0AD8_CC5A_4A0C_8BED_28A055A3C960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CSNMP  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSNMP();
	virtual ~CSNMP();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	static BOOL GetNetworkAdapters( CNetworkAdapterList *pList);
};

#endif // !defined(AFX_SNMP_H__3CFE0AD8_CC5A_4A0C_8BED_28A055A3C960__INCLUDED_)
