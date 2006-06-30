// downloadDlg.cpp : implementation file
//

#include "stdafx.h"
#include "download.h"
#include "downloadDlg.h"
#include "Math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownloadDlg dialog

CDownloadDlg::CDownloadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownloadDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDownloadDlg)
	m_Edit = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDownloadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownloadDlg)
	DDX_Control(pDX, IDC_DELAY, m_Wait);
	DDX_Control(pDX, IDC_EDIT1, m_cEdit);
	DDX_Control(pDX, IDOK, m_OkButton);
	DDX_Control(pDX, IDCANCEL, m_CancelButton);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDownloadDlg, CDialog)
	//{{AFX_MSG_MAP(CDownloadDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DELAY, OnDelay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownloadDlg message handlers

BOOL CDownloadDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	if( notifyCountdown )
		SetTimer( WM_TIMER, 1000, NULL );	
	delayed = FALSE;
	waited = 0;	

	CRect cr, win;
	int nbl = m_cEdit.GetLineCount();
	if( nbl > MAX_LINES ) nbl = MAX_LINES;
	if( nbl < MIN_LINES ) nbl = MIN_LINES;

	m_cEdit.GetWindowRect(&cr);
	GetWindowRect(&win);

	int newHeight = int(ceil((nbl*cr.Height()) / 3));
	m_cEdit.SetWindowPos( &CWnd::wndTop, 0, 0, cr.Width() , newHeight, SWP_NOMOVE );
	SetWindowPos( &CWnd::wndTopMost, 0, 0, win.Width() , newHeight + win.Height() - cr.Height() + 10, SWP_NOMOVE );

	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDownloadDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_OkButton.SetFocus();
		m_cEdit.SetSel(-1);
		CRect fen, ok, cancel, wait;
		CRect v_fen, v_ok, v_cancel, v_wait;
		int xok,xcancel,xwait,y;	

		GetClientRect(&fen);
		m_OkButton.GetClientRect(&ok);
		m_CancelButton.GetClientRect(&cancel);
		m_Wait.GetClientRect(&wait);

		GetWindowRect(&v_fen);
		m_OkButton.GetWindowRect(&v_ok);
		m_CancelButton.GetWindowRect(&v_cancel);
		m_Wait.GetWindowRect(&v_wait);

		m_CancelButton.ShowWindow( canAbort );
		m_Wait.ShowWindow( canDelay );

		if( ! canAbort && ! canDelay ) {// OK seul
			xok = (fen.Width() - ok.Width() ) / 2;
			y = fen.bottom - 10 - ok.bottom ;
			m_OkButton.SetWindowPos( &CWnd::wndTop, xok, y, 0, 0, SWP_NOSIZE );
		}
		else if( !canDelay ) {// ok et cancel
			xok     = ((  fen.Width()/2) -     ok.Width() ) / 2;
			xcancel = (( (fen.Width()/2) - cancel.Width() ) / 2) + fen.Width()/2 ;
			y = fen.bottom - 10 - ok.bottom ;
			m_OkButton.SetWindowPos( &CWnd::wndTop, xok, y, 0, 0, SWP_NOSIZE );
			m_CancelButton.SetWindowPos( &CWnd::wndTop, xcancel, y, 0, 0, SWP_NOSIZE );
		}
		else if( ! canAbort ) { // ok et delay
			xok     = ((  fen.Width()/2) -     ok.Width() ) / 2;
			xwait = (( (fen.Width()/2) - wait.Width() ) / 2) + fen.Width()/2 ;
			y = fen.bottom - 10 - ok.bottom ;
			m_OkButton.SetWindowPos( &CWnd::wndTop, xok, y, 0, 0, SWP_NOSIZE );
			m_Wait.SetWindowPos( &CWnd::wndTop, xwait, y, 0, 0, SWP_NOSIZE );
		}
		else { // les trois
			y = fen.bottom - 10 - ok.bottom ;

			xok     = ((  fen.Width()/3) -     ok.Width() ) / 2;
			xcancel = (( (fen.Width()/3) - cancel.Width() ) / 2) + fen.Width()/3 ;
			xwait = (( (fen.Width()/3) - wait.Width() ) / 2) + (fen.Width()/3)*2 ;

			m_OkButton.SetWindowPos( &CWnd::wndTop, xok , y, 0, 0, SWP_NOSIZE );
			m_Wait.SetWindowPos( &CWnd::wndTop, xcancel, y, 0, 0, SWP_NOSIZE );
			m_CancelButton.SetWindowPos( &CWnd::wndTop, xwait, y, 0, 0, SWP_NOSIZE );
		}

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDownloadDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDownloadDlg::OnTimer(UINT nIDEvent) 
{
	waited++;
	if( waited >= notifyCountdown )
		OnOK();
	
	char useless[255];
	SetWindowText( "VALIDATING IN " + CString(_itoa( notifyCountdown - waited ,useless,10)) + " SECONDS" ); 
	CDialog::OnTimer(nIDEvent);
}

int CDownloadDlg::DoModal()  
{
	return CDialog::DoModal();
}

void CDownloadDlg::OnCancel() 
{
	if( canAbort )
		CDialog::OnCancel();
}

void CDownloadDlg::OnDelay() 
{
	delayed = TRUE;
	CDialog::OnOK();
}
