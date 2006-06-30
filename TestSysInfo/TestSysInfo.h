// Document modified at : Saturday, November 15, 2003 9:41:24 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// TestSysInfo.h : main header file for the TESTOCSWMI application
//

#if !defined(AFX_TESTOCSWMI_H__6EFD6A5B_292C_447E_AA5E_BF79F458470F__INCLUDED_)
#define AFX_TESTOCSWMI_H__6EFD6A5B_292C_447E_AA5E_BF79F458470F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestSysInfoApp:
// See TestSysInfo.cpp for the implementation of this class
//

class CTestSysInfoApp : public CWinApp
{
public:
	CTestSysInfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSysInfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestSysInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOCSWMI_H__6EFD6A5B_292C_447E_AA5E_BF79F458470F__INCLUDED_)
