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

// TestSysInfoDlg.h : header file
//

#if !defined(AFX_TESTOCSWMIDLG_H__47D17915_FB57_445F_A612_69396C326699__INCLUDED_)
#define AFX_TESTOCSWMIDLG_H__47D17915_FB57_445F_A612_69396C326699__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestSysInfoDlg dialog

class CTestSysInfoDlg : public CDialog
{
// Construction
public:
	CTestSysInfoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestSysInfoDlg)
	enum { IDD = IDD_TESTOCSWMI_DIALOG };
	CListBox	m_List;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestSysInfoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestSysInfoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOcsWmi();
	afx_msg void OnSysInfo();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTOCSWMIDLG_H__47D17915_FB57_445F_A612_69396C326699__INCLUDED_)
