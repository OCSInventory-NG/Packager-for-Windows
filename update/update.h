// update.h : main header file for the UPDATE application
//

#if !defined(AFX_UPDATE_H__E372414F_C09C_4A94_AB1B_4253B3CE180F__INCLUDED_)
#define AFX_UPDATE_H__E372414F_C09C_4A94_AB1B_4253B3CE180F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#define EXE_NAME "update.exe"
/////////////////////////////////////////////////////////////////////////////
// CUpdateApp:
// See update.cpp for the implementation of this class
//

class CUpdateApp : public CWinApp
{
public:
	BOOL bOpened;
	CFile myFile;
	CUpdateApp();
	void AddLog(LPCTSTR lpstrLog,...);
	void CloseLog();	
	BOOL IsRequired(LPCTSTR lpstrCommandLine,CString option);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUpdateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUpdateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UPDATE_H__E372414F_C09C_4A94_AB1B_4253B3CE180F__INCLUDED_)
