// downloadDlg.h : header file
//

#if !defined(AFX_DOWNLOADDLG_H__8A654D8E_45A7_47CA_AFE6_FB0847891469__INCLUDED_)
#define AFX_DOWNLOADDLG_H__8A654D8E_45A7_47CA_AFE6_FB0847891469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDownloadDlg dialog

#define MAX_LINES 15
#define MIN_LINES 3

class CDownloadDlg : public CDialog
{
// Construction
public:
	CDownloadDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL canAbort;
	BOOL canDelay;
	BOOL delayed;
	UINT notifyCountdown;
	UINT waited;

// Dialog Data
	//{{AFX_DATA(CDownloadDlg)
	enum { IDD = IDD_DOWNLOAD_DIALOG };
	CButton	m_Wait;
	CEdit	m_cEdit;
	CButton	m_OkButton;
	CButton	m_CancelButton;
	CString	m_Edit;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDownloadDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDownloadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnDelay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOWNLOADDLG_H__8A654D8E_45A7_47CA_AFE6_FB0847891469__INCLUDED_)
