// download.h : main header file for the DOWNLOAD application
//

#if !defined(AFX_DOWNLOAD_H__0F0F9CBB_4576_4E37_896E_12F657F99F28__INCLUDED_)
#define AFX_DOWNLOAD_H__0F0F9CBB_4576_4E37_896E_12F657F99F28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "../include/xml/markup.h"

#define INST32_OK_CODE 130
/////////////////////////////////////////////////////////////////////////////
// CDownloadApp:
// See download.cpp for the implementation of this class
//

class CPackage;

class CDownloadApp : public CWinApp
{		
	CObArray packages;
	CString m_csFragLatency,
			m_csCycleLatency,
			m_csPeriodLatency,
			m_csPeriodLength,
			m_csTimeout,
			m_csOn;

	HANDLE hMutexOneInstance;
	CString blacklist;


public:
	int error;
	UINT m_iProxy;	
	UINT m_iPort;
	CString m_csDeviceId,
			m_csServer,
			m_csHttp_u,
			m_csHttp_w;

	CDownloadApp();
	BOOL isAN( LPCSTR st );
	void inline clean();
	void period( CObArray * pC );
	int download( CPackage * pP );
	void finish();
	
	BOOL blackListed( CString );
	void blackList( CString );



//	void cleanId( CString Id );

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDownloadApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CPackage : public CObject {

public:
	CString Id;
	UINT Pri;
	CString Act;
	CString Name;
	CString Digest;
	CString Loc;
	CString Proto;
	UINT Frags;
	CString DigestAlgo;
	CString DigestEncode;
	CString Path;
	CString Command;
	CString GardeFou;
	CDownloadApp * pA;

	/* User notification */
	BOOL notifyUser;
	UINT notifyCountdown;
	CString notifyText;
	BOOL notifyCanAbort;
	BOOL notifyCanDelay;
	BOOL needDoneAction;
	CString needDoneActionText;

	CPackage(CDownloadApp * p) { pA = p;};
	BOOL fromXml( CMarkup* pX ); 
	int execute();	
	void done(BOOL needToSendSuccess = TRUE);
	int buildPackage();
	int checkSignature() ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOAD_H__0F0F9CBB_4576_4E37_896E_12F657F99F28__INCLUDED_)
