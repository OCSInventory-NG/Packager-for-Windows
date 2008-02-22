// Document modified at : Friday, March 31, 2006 12:51:40 PM , by user : didier , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

//  OCSInventory.h : main header file for the OCSInventory application
//

#if !defined(AFX_OCSINVENTORY_H__C4903B55_8BDE_11D4_8077_0040055338AF__INCLUDED_)
#define AFX_OCSINVENTORY_H__C4903B55_8BDE_11D4_8077_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <afxmt.h>
/////////////////////////////////////////////////////////////////////////////
// COCSInventoryApp:
// See  OCSInventory.cpp for the implementation of this class
//
#include "DeviceProperties.h" // XML

// Application exit codes
#define OCS_APP_NO_ERROR				0
#define OCS_APP_GENERIC_ERROR			1
#define OCS_APP_ALREADY_RUNNING_ERROR	2
#define OCS_APP_INVENTORY_ERROR			3
#define OCS_APP_NETWORK_ERROR			4

class COCSInventoryApp : public CWinApp
{
public:
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	COCSInventoryApp();

	CMarkup			 m_markupOCS; // General CMarkup object to OCS App
	ULONG			 m_netNumber;
	ULONG			 m_hostFound;
	CCriticalSection m_cs;
	

	// Function SendARP of IPHLPAPI.DLL (available on Windows 98 or higher and NT4 SP4 or higher)
	DWORD (WINAPI *lpfn_SendARP)(IPAddr DestIP, IPAddr SrcIP, PULONG pMacAddr, PULONG PhyAddrLen);
	// Functions from Winsock2
	u_long (WINAPI *lpfn_htonl)(u_long hostlong);
	u_long (WINAPI *lpfn_ntohl)(u_long netlong);
	unsigned long (WINAPI *lpfn_inet_addr)(const char* cp);
	char* FAR (WINAPI *lpfn_inet_ntoa)(struct in_addr in);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCSInventoryApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COCSInventoryApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected: // Methods
	// Check whether or not to run the inventory with the Last Check Date loaded
	// Return TRUE if it's time to check for softwares
	BOOL IsCheckDate();
	// Search for the apps loaded in the local hard drives
	void SearchLocalHDD();
	// Search for the apps loaded in a specific directory (recursive search)
	void SearchFilesInDirectory( LPCTSTR lpstrDir);
	// Load BIOS informations from XML file created by DumpBIOS.exe
	BOOL LoadBIOS( LPCTSTR lpstrCommandLine, LPCTSTR lpstrExecutionFolder, CDeviceProperties &pPC);
	// Find the filename of the CSV BIOS file from the Command Line or build it
	BOOL GetBiosFilename( CString &csCommandLine, LPCTSTR lpstrExecutionFolder, CDeviceProperties &pPC, CString &csFilename);
	// Connection to database (either with OcsDB or CSV)
	BOOL ConnectDB( LPCTSTR lpstrExecutionFolder);
	// Determine if inventory information have changed since last inventory
	BOOL HasChanged( CDeviceProperties *pPC, LPCTSTR lpstrExecutionFolder);

protected: // Attributes

	LONG			m_lNumberOfFiles;	// Number of files on a logical drive
	CStoreInteract  * m_pTheDB;			// Inventory storing object interaction
	BOOL			m_bNeedUpdate;		// Agent need to be updated if true
	CDeviceProperties m_ThePC;			// Device properties
	COCSInventoryState m_State;			// Inventory state for detecting changes
	int				m_nAppExitCode;		// Application exit code (0 no error, 1 network error, 2 generic failure)
};

class CInputDlg : public CDialog
{
// Construction
public:
	CInputDlg(CWnd* pParent = NULL);   // standard constructor
	CString label;
// Dialog Data
	//{{AFX_DATA(CInputDlg)
	enum { IDD = IDD_CU };
	CEdit	m_ValC;
	CString	m_ValV;
	CString	m_LabelText;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputDlg)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInputDlg)
	virtual void OnOK();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OCSINVENTORY_H__C4903B55_8BDE_11D4_8077_0040055338AF__INCLUDED_)
