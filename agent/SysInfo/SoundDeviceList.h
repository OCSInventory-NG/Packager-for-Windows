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

// SoundDeviceList.h: interface for the CSoundDeviceList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDDEVICELIST_H__C69CD4E2_060A_488D_982C_CE8626CFD27B__INCLUDED_)
#define AFX_SOUNDDEVICELIST_H__C69CD4E2_060A_488D_982C_CE8626CFD27B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CSoundDeviceList : public CList<CSoundDevice, CSoundDevice&>  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CSoundDeviceList();
	virtual ~CSoundDeviceList();

};

#endif // !defined(AFX_SOUNDDEVICELIST_H__C69CD4E2_060A_488D_982C_CE8626CFD27B__INCLUDED_)
