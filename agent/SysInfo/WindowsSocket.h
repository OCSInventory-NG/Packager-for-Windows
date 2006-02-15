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

// WindowsSocket.h: interface for the CWindowsSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWSSOCKET_H__91E29D3E_FE3D_49BC_A386_611A6718999E__INCLUDED_)
#define AFX_WINDOWSSOCKET_H__91E29D3E_FE3D_49BC_A386_611A6718999E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CWindowsSocket  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CWindowsSocket();
	virtual ~CWindowsSocket();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	LPCTSTR GetIPAddress();

protected: // Attributes
	CString m_csIP;
};

#endif // !defined(AFX_WINDOWSSOCKET_H__91E29D3E_FE3D_49BC_A386_611A6718999E__INCLUDED_)
