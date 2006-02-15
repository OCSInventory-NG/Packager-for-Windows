// Document modified at : Wednesday, December 10, 2003 12:05:22 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceRepairsList.h: interface for the CDeviceRepairsList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEREPAIRSLIST_H__373129CF_544C_4DC3_9536_313B900BC615__INCLUDED_)
#define AFX_DEVICEREPAIRSLIST_H__373129CF_544C_4DC3_9536_313B900BC615__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CDeviceRepairsList : public CList<CDeviceRepairs, CDeviceRepairs&>    
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceRepairsList();
	virtual ~CDeviceRepairsList();

};

#endif // !defined(AFX_DEVICEREPAIRSLIST_H__373129CF_544C_4DC3_9536_313B900BC615__INCLUDED_)
