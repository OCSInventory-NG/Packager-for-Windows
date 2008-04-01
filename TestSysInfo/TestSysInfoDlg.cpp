// Document modified at : Wednesday, March 29, 2006 1:50:01 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// TestSysInfoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestSysInfo.h"
#include "TestSysInfoDlg.h"
#include "OcsWmi.h"
#include "SysInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSysInfoDlg dialog

CTestSysInfoDlg::CTestSysInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestSysInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestSysInfoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSysInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestSysInfoDlg)
	DDX_Control(pDX, IDC_LIST1, m_List);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestSysInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CTestSysInfoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_WMI, OnOcsWmi)
	ON_BN_CLICKED(ID_SYSINFO, OnSysInfo)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestSysInfoDlg message handlers

BOOL CTestSysInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestSysInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestSysInfoDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestSysInfoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestSysInfoDlg::OnOcsWmi() 
{
	CWaitCursor cWait;
	COcsWmi		myWmiDll;

	m_List.ResetContent();
	if (myWmiDll.ConnectWMI( _T( "\\\\.\\root\\cimv2")))
		m_List.AddString( "Connected to WMI");
	else
	{
		m_List.AddString( "Error connecting to WMI");
		return ;
	}
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "System Enclosure infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_SystemEnclosure")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "System Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "System Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "System S/N = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SerialNumber"));
			str += res;
			m_List.AddString( str);
			str = "SKU = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SKU"));
			str += res;
			m_List.AddString( str);
			str = "ChassisTypes = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ChassisTypes"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Computer System infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_ComputerSystem")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "System Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "System Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Base board infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_BaseBoard")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Base board Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Base board Product = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Product"));
			str += res;
			m_List.AddString( str);
			str = "Base board S/N = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SerialNumber"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "BIOS infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_BIOS")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "BIOS Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Version = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Version"));
			str += res;
			m_List.AddString( str);
			str = "BIOS Version = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "BIOSVersion"));
			str += res;
			m_List.AddString( str);
			str = "SMBIOS BIOS Version = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SMBIOSBIOSVersion"));
			str += res;
			m_List.AddString( str);
			str = "BIOS date = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ReleaseDate"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "PhysicalMemory infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_PhysicalMemory")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str =  "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "BankLabel = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "BankLabel"));
			str += res;
			str =  "DeviceLocator = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "DeviceLocator"));
			str += res;
			m_List.AddString( str);
			str = "Capacity = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Capacity"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "MemoryType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MemoryType"));
			str += res;
			m_List.AddString( str);
			str = "Speed = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Speed"));
			str += res;
			m_List.AddString( str);
			str = "Status = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Status"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "PhysicalMemoryArray infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_PhysicalMemoryArray")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str =  "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "MaxCapacity = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MaxCapacity"));
			str += res;
			m_List.AddString( str);
			str =  "MemoryDevices = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MemoryDevices"));
			str += res;
			m_List.AddString( str);
			str =  "Use = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Use"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Status = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Status"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "System Slot infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_SystemSlot")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str =  "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str =  "PurposeDescription = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "PurposeDescription"));
			str += res;
			m_List.AddString( str);
			str =  "SlotDesignation = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SlotDesignation"));
			str += res;
			m_List.AddString( str);
			str =  "Shared = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Shared"));
			str += res;
			m_List.AddString( str);
			str = "ConnectorType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ConnectorType"));
			str += res;
			m_List.AddString( str);
			str = "CurrentUsage = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CurrentUsage"));
			str += res;
			m_List.AddString( str);
			str = "Status = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Status"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Battery infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_Battery")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Availability = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Availability"));
			str += res;
			m_List.AddString( str);
			str = "BatteryStatus = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "BatteryStatus"));
			str += res;
			m_List.AddString( str);
			str = "EstimatedChargeRemaining = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "EstimatedChargeRemaining"));
			str += res;
			m_List.AddString( str);
			str = "EstimatedRunTime = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "EstimatedRunTime"));
			str += res;
			m_List.AddString( str);
			str = "ExpectedLife = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ExpectedLife"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "PortableBattery infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_PortableBattery")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Availability = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Availability"));
			str += res;
			m_List.AddString( str);
			str = "BatteryStatus = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "BatteryStatus"));
			str += res;
			m_List.AddString( str);
			str = "EstimatedChargeRemaining = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "EstimatedChargeRemaining"));
			str += res;
			m_List.AddString( str);
			str = "EstimatedRunTime = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "EstimatedRunTime"));
			str += res;
			m_List.AddString( str);
			str = "ExpectedLife = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ExpectedLife"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Processor infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_Processor")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Processor Family = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Speed = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CurrentClockSpeed"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "MotherBoard Device infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_MotherboardDevice")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "PrimaryBusType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "PrimaryBusType"));
			str += res;
			m_List.AddString( str);
			str =  "SecondaryBusType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SecondaryBusType"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "OnBoard Device infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_OnBoardDevice")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str =  "Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Video Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_VideoController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Chipset = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "VideoProcessor"));
			str += res;
			m_List.AddString( str);
			str = "Memoire = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "AdapterRAM"));
			str += res;
			m_List.AddString( str);
			str = "Horz res = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CurrentHorizontalResolution"));
			str += res;
			m_List.AddString( str);
			str = "Vert res = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CurrentVerticalResolution"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Desktop Monitor infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_DesktopMonitor")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "MonitorManufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MonitorManufacturer"));
			str += res;
			m_List.AddString( str);
			str = "MonitorType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MonitorType"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str.Format( _T( "Status %lu"), myWmiDll.GetClassObjectDwordValue( _T( "Status")));
			m_List.AddString( str);
			str.Format( _T( "StatusInfo %lu"), myWmiDll.GetClassObjectDwordValue( _T( "StatusInfo")));
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Serial Port infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_SerialPort")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "OSAutoDiscovered = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "OSAutoDiscovered"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Parallel Port infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_ParallelPort")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "OSAutoDiscovered = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "OSAutoDiscovered"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( " Keyboard infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_Keyboard")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "NumberOfFunctionKeys = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "NumberOfFunctionKeys"));
			str += res;
			m_List.AddString( str);
			str = "Layout = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Layout"));
			str += res;
			m_List.AddString( str);
			str = "Status = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Status"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( " Pointing Device infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_PointingDevice")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "HardwareType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "HardwareType"));
			str += res;
			m_List.AddString( str);
			str = "PointingType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "PointingType"));
			str += res;
			m_List.AddString( str);
			str = "DeviceInterface = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "DeviceInterface"));
			str += res;
			m_List.AddString( str);
			str = "NumberOfButtons = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "NumberOfButtons"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Floppy Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_FloppyController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "IDE Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_IDEController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "SCSI Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_SCSIController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "HardwareVersion = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "HardwareVersion"));
			str += res;
			m_List.AddString( str);
			str =  "DriverName = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "DriverName"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "InfraRed Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_InfraredDevice")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "USB Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_USBController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "IEEE 1394 Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_1394Controller")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "PCMCIA Controler infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_PCMCIAController")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Floppy Drives infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_FloppyDrive")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;
			unsigned __int64  u64;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Name  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "MediaType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MediaType"));
			str += res;
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "MaxMediaSize"));
			str.Format( "MaxMediaSize in MB = %lu ", u64/1000);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "Size"));
			str.Format( "Size in Bytes = %lu ", u64);
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Disk Drives infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_DiskDrive")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;
			unsigned __int64  u64;
			ULONG	ulCylinder,
					ulTracksPerCylinder,
					ulSectorPerTrack,
					ulBytesPerSector;
			

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Model  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "Name  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "MediaType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MediaType"));
			str += res;
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "MaxMediaSize"));
			str.Format( "MaxMediaSize in MB = %lu ", u64/1000);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "Size"));
			str.Format( "Size in Bytes = %lu ", u64);
			m_List.AddString( str);
			ulCylinder = myWmiDll.GetClassObjectDwordValue( _T( "TotalCylinders"));
			str.Format( "Cylinders = %lu ", ulCylinder);
			m_List.AddString( str);
			ulTracksPerCylinder = myWmiDll.GetClassObjectDwordValue( _T( "TracksPerCylinder"));
			str.Format( "Tracks per Cylinder = %lu ", ulTracksPerCylinder);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "TotalTracks"));
			str.Format( "Total Tracks = %lu ", u64);
			m_List.AddString( str);
			ulSectorPerTrack = myWmiDll.GetClassObjectDwordValue( _T( "SectorsPerTrack"));
			str.Format( "Sectors per Track = %lu ", ulSectorPerTrack);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "TotalSectors"));
			str.Format( "Total Sectors = %lu ", u64);
			m_List.AddString( str);
			ulBytesPerSector = myWmiDll.GetClassObjectDwordValue( _T( "BytesPerSector"));
			str.Format( "Bytes per Sector = %lu ", ulBytesPerSector);
			m_List.AddString( str);
			str.Format( "Total size = %lu ", ulCylinder*ulTracksPerCylinder*ulSectorPerTrack*ulBytesPerSector);
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Disk Drive Physical Medias infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_DiskDrivePhysicalMedia")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;
			unsigned __int64  u64;
			ULONG	ulCylinders,
					ulTracksPerCylinder,
					ulSectorPerTrack,
					ulBytesPerSector;
			

			str =  "Win32_DiskDrive Manufacturer = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Win32_DiskDrive Caption = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Win32_DiskDrive Description  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Win32_DiskDrive Model  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "Win32_DiskDrive Name  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "Win32_DiskDrive MediaType = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "MediaType"));
			str += res;
			m_List.AddString( str);
			u64 = myWmiDll.GetRefElementClassObjectU64Value( _T( "Dependent"), _T( "MaxMediaSize"));
			str.Format( "Win32_DiskDrive MaxMediaSize in MB = %lu ", u64/1000);
			m_List.AddString( str);
			u64 = myWmiDll.GetRefElementClassObjectU64Value( _T( "Dependent"), _T( "Size"));
			str.Format( "Win32_DiskDrive Size in MB = %lu ", u64/1000000);
			m_List.AddString( str);
			ulCylinders = myWmiDll.GetRefElementClassObjectDwordValue( _T( "Dependent"), _T( "TotalCylinders"));
			str.Format( "Win32_DiskDrive Cylinders = %lu ", ulCylinders);
			m_List.AddString( str);
			ulTracksPerCylinder = myWmiDll.GetRefElementClassObjectDwordValue( _T( "Dependent"), _T( "TracksPerCylinder"));
			str.Format( "Win32_DiskDrive Tracks per Cylinder = %lu ", ulTracksPerCylinder);
			m_List.AddString( str);
			u64 = myWmiDll.GetRefElementClassObjectU64Value( _T( "Dependent"), _T( "TotalTracks"));
			str.Format( "Win32_DiskDrive Total Tracks = %lu ", u64);
			m_List.AddString( str);
			ulSectorPerTrack = myWmiDll.GetRefElementClassObjectDwordValue( _T( "Dependent"), _T( "SectorsPerTrack"));
			str.Format( "Win32_DiskDrive Sectors per Track = %lu ", ulSectorPerTrack);
			m_List.AddString( str);
			u64 = myWmiDll.GetRefElementClassObjectU64Value( _T( "Dependent"), _T( "TotalSectors"));
			str.Format( "Win32_DiskDrive Total Sectors = %lu ", u64);
			m_List.AddString( str);
			ulBytesPerSector = myWmiDll.GetRefElementClassObjectDwordValue( _T( "Dependent"), _T( "BytesPerSector"));
			str.Format( "Win32_DiskDrive Bytes per Sector = %lu ", ulBytesPerSector);
			m_List.AddString( str);
			str.Format( "Win32_DiskDrive Total size = %lu ", ulCylinders*ulTracksPerCylinder*ulSectorPerTrack*ulBytesPerSector);
			m_List.AddString( str);

			str =  "Win32_PhysicalMedia Manufacturer = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Win32_PhysicalMedia Caption = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Win32_PhysicalMedia Description  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Win32_PhysicalMedia Model  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Model"));
			str += res;
			m_List.AddString( str);
			str = "Win32_PhysicalMedia Name  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Name"));
			str += res;
			m_List.AddString( str);
			ulCylinders = myWmiDll.GetRefElementClassObjectDwordValue( _T( "Antecedent"), _T( "MediaType"));
			str.Format( "Win32_PhysicalMedia MediaType = %lu ", ulCylinders);
			m_List.AddString( str);
			u64 = myWmiDll.GetRefElementClassObjectU64Value( _T( "Antecedent"), _T( "Capacity"));
			str.Format( "Win32_PhysicalMedia Capacity in KBytes = %lu ", u64/1024);
			m_List.AddString( str);

			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "CD-ROM Drives infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_CDROMDrive")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;
			unsigned __int64  u64;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Name  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "MediaType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MediaType"));
			str += res;
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "MaxMediaSize"));
			str.Format( "MaxMediaSize in MB = %lu ", u64/1000);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "Size"));
			str.Format( "Size in MB = %lu ", u64/1000000);
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Tape Drives infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_TapeDrive")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;
			unsigned __int64  u64;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Name  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "MediaType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "MediaType"));
			str += res;
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "MaxMediaSize"));
			str.Format( "MaxMediaSize in MB = %lu ", u64/1000);
			m_List.AddString( str);
			u64 = myWmiDll.GetClassObjectU64Value( _T( "Size"));
			str.Format( "Size in MB = %lu ", u64/1000000);
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Sound Device infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_SoundDevice")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "ProductName = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ProductName"));
			str += res;
			m_List.AddString( str);
			str = "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Network Adapter infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_NetworkAdapterSetting")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "AdapterType = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "AdapterType"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "ProductName  = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "ProductName"));
			str += res;
			m_List.AddString( str);
			str =  "MaxSpeed = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Speed"));
			str += res;
			m_List.AddString( str);
			str =  "MACAddress = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "MACAddress"));
			str += res;
			m_List.AddString( str);
			str =  "IPAddress = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "IPAddress"));
			str += res;
			m_List.AddString( str);
			str =  "IPSubnet = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "IPSubnet"));
			str += res;
			m_List.AddString( str);
			str =  "Status = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Status"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Telephony Modem infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_POTSModem")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "DeviceType  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "DeviceType"));
			str += res;
			m_List.AddString( str);
			str =  "Model = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Model"));
			str += res;
			m_List.AddString( str);
			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Printer infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_Printer")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "DriverName  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "DriverName"));
			str += res;
			m_List.AddString( str);
			str =  "PortName = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "PortName"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "OS infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_OperatingSystem")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
/*			str = "ServicePackMajorVersion = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ServicePackMajorVersion"));
			str += res;
			m_List.AddString( str);
			str = "ServicePackMinorVersion = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ServicePackMinorVersion"));
			str += res;
			m_List.AddString( str);
*/			str = "BuildNumber = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "BuildNumber"));
			str += res;
			m_List.AddString( str);
			str =  "CSDVersion = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CSDVersion"));
			str += res;
			m_List.AddString( str);
			str =  "Manufacturer = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Manufacturer"));
			str += res;
			m_List.AddString( str);
			str =  "SerialNumber = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SerialNumber"));
			str += res;
			m_List.AddString( str);
			str = "Scoping System = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "CSName"));
			str += res;
			m_List.AddString( str);
			str = "Description = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "OSProductSuite = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "OSProductSuite"));
			str += res;
			m_List.AddString( str);
			str = "OtherTypeDescription = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "OtherTypeDescription"));
			str += res;
			m_List.AddString( str);
			str = "ProductType = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "ProductType"));
			str += res;
			m_List.AddString( str);
			str = "SuiteMask = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SuiteMask"));
			str += res;
			m_List.AddString( str);
			str = "Version = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Version"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

/*	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Domain infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_LoggedOnUser")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "User Name = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "User Description = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "User Caption = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str =  "User Domain = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Antecedent"), _T( "Domain"));
			str += res;
			m_List.AddString( str);
			str = "Logon Name = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Name"));
			str += res;
			m_List.AddString( str);
			str = "Logon Description = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Description"));
			str += res;
			m_List.AddString( str);
			str = "Logon Caption = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Logon ID = ";
			res = myWmiDll.GetRefElementClassObjectStringValue( _T( "Dependent"), _T( "LogonId"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}
*/
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Software infos");
	m_List.AddString( "------------------------------------------------------");
	if (myWmiDll.BeginEnumClassObject( _T( "Win32_Product")))
	{
		while (myWmiDll.MoveNextEnumClassObject())
		{
			CString str, res;

			str = "Vendor  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Vendor"));
			str += res;
			m_List.AddString( str);
			str =  "Name = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Name"));
			str += res;
			m_List.AddString( str);
			str =  "Version = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Version"));
			str += res;
			m_List.AddString( str);
			str = "Caption = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Caption"));
			str += res;
			m_List.AddString( str);
			str = "Description  = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "Description"));
			str += res;
			m_List.AddString( str);
			str =  "SKUNumber = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "SKUNumber"));
			str += res;
			m_List.AddString( str);
			str =  "IdentifyingNumber = ";
			res = myWmiDll.GetClassObjectStringValue( _T( "IdentifyingNumber"));
			str += res;
			m_List.AddString( str);
			m_List.AddString( "");
		}
		myWmiDll.CloseEnumClassObject();
	}

	myWmiDll.DisconnectWMI();
	m_List.AddString( "");
	m_List.AddString( "Disconnected from WMI");
}

void CTestSysInfoDlg::SysInfoLog (CString str)
{
	static FILE *Log=NULL;

	if (!Log) 
		Log = fopen("TestSysInfo.txt", "wt");
	if (Log) {
		fputs (str, Log);
		fputs ("\n", Log);
	}
	m_List.AddString( str);
}
void CTestSysInfoDlg::OnSysInfo() 
{
	CWaitCursor		cWait;
	CDeviceProperties myPC;
	SysInfo			mySys;
	CString			str;
	POSITION		pos;
	BOOL			bContinue;

	remove( "c:\\TestSysInfo_trace.log");
	OpenLog( "c:\\TestSysInfo_trace", "-DEBUG");
	myPC.RetrieveHardwareAndOS( &mySys, _T( ""));
	CloseLog();
	m_List.ResetContent();
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "BIOS infos");
	SysInfoLog( "------------------------------------------------------");
	str.Format( "System Manufacturer: %s", myPC.m_BIOS.GetSystemManufacturer());
	SysInfoLog( str);
	str.Format( "System Model: %s", myPC.m_BIOS.GetSystemModel());
	SysInfoLog( str);
	str.Format( "System S/N: %s", myPC.m_BIOS.GetSystemSerialNumber());
	SysInfoLog( str);
	str.Format( "Machine Type: %s", myPC.m_BIOS.GetMachineType());
	SysInfoLog( str);
	str.Format( "BIOS Manufacturer: %s", myPC.m_BIOS.GetBiosManufacturer());
	SysInfoLog( str);
	str.Format( "BIOS Version: %s", myPC.m_BIOS.GetBiosVersion());
	SysInfoLog( str);
	str.Format( "BIOS Date: %s", myPC.m_BIOS.GetBiosDate());
	SysInfoLog( str);
	SysInfoLog( "");
	str.Format( "Bios Hash: %s", myPC.m_BIOS.GetHash());
	SysInfoLog( str);

	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Processors infos");
	SysInfoLog( "------------------------------------------------------");
	str.Format( "Number of Processors: %u", myPC.GetNumberOfProcessors());
	SysInfoLog( str);
	str.Format( "Processor name: %s", myPC.GetProcessorType());
	SysInfoLog( str);
	str.Format( "Processor speed: %s", myPC.GetProcessorSpeed());
	SysInfoLog( str);

	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Memory Slots infos");
	SysInfoLog( "------------------------------------------------------");
	CMemorySlot myMemSlot;
	pos = myPC.m_MemoryList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myMemSlot = myPC.m_MemoryList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Caption: %s", myMemSlot.GetCaption());
		SysInfoLog( str);
		str.Format( "Description: %s", myMemSlot.GetDescription());
		SysInfoLog( str);
		str.Format( "Capacity: %s KB", myMemSlot.GetCapacity());
		SysInfoLog( str);
		str.Format( "Usage: %s", myMemSlot.GetUsage());
		SysInfoLog( str);
		str.Format( "Type: %s", myMemSlot.GetType());
		SysInfoLog( str);
		str.Format( "Speed: %s MHz", myMemSlot.GetSpeed());
		SysInfoLog( str);
		str.Format( "Slot Number: %u", myMemSlot.GetSlotNumber());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myMemSlot = myPC.m_MemoryList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Memory Slots Hash: %s", myPC.m_MemoryList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Video Controlers infos");
	SysInfoLog( "------------------------------------------------------");
	CVideoAdapter myVideo;
	pos = myPC.m_VideoList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myVideo = myPC.m_VideoList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Name: %s", myVideo.GetName());
		SysInfoLog( str);
		str.Format( "Chipset: %s", myVideo.GetChipset());
		SysInfoLog( str);
		str.Format( "Memory: %s MB", myVideo.GetMemory());
		SysInfoLog( str);
		str.Format( "Resolution: %s", myVideo.GetScreenResolution());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myVideo = myPC.m_VideoList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Video Controlers Hash: %s", myPC.m_VideoList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Desktop Monitors infos");
	SysInfoLog( "------------------------------------------------------");
	CMonitor myMonitor;
	pos = myPC.m_MonitorList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myMonitor = myPC.m_MonitorList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Manufacturer: %s", myMonitor.GetManufacturer());
		SysInfoLog( str);
		str.Format( "Caption: %s", myMonitor.GetCaption());
		SysInfoLog( str);
		str.Format( "Description: %s", myMonitor.GetDescription());
		SysInfoLog( str);
		str.Format( "Type: %s", myMonitor.GetType());
		SysInfoLog( str);
		str.Format( "S/N: %s", myMonitor.GetSerial());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myMonitor = myPC.m_MonitorList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Monitors Hash: %s", myPC.m_MonitorList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Sound Devices infos");
	SysInfoLog( "------------------------------------------------------");
	CSoundDevice mySound;
	pos = myPC.m_SoundList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		mySound = myPC.m_SoundList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Manufacturer: %s", mySound.GetManufacturer());
		SysInfoLog( str);
		str.Format( "Name: %s", mySound.GetName());
		SysInfoLog( str);
		str.Format( "Description: %s", mySound.GetDescription());
		SysInfoLog( str);
		if (pos != NULL)
		{
			mySound = myPC.m_SoundList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Sound Devices Hash: %s", myPC.m_SoundList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "System Slots infos");
	SysInfoLog( "------------------------------------------------------");
	CSystemSlot mySlot;
	pos = myPC.m_SlotList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		mySlot = myPC.m_SlotList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Name: %s", mySlot.GetName());
		SysInfoLog( str);
		str.Format( "Description: %s", mySlot.GetDescription());
		SysInfoLog( str);
		str.Format( "Slot Designation: %s", mySlot.GetSlotDesignation());
		SysInfoLog( str);
		str.Format( "Usage: %s", mySlot.GetUsage());
		SysInfoLog( str);
		str.Format( "Status: %s", mySlot.GetStatus());
		SysInfoLog( str);
		str.Format( "Is shared: %s", mySlot.IsShared() ? "TRUE" : "FALSE");
		SysInfoLog( str);
		if (pos != NULL)
		{
			mySlot = myPC.m_SlotList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "System Slots Hash: %s", myPC.m_SlotList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "System Port infos");
	SysInfoLog( "------------------------------------------------------");
	CSystemPort myPort;
	pos = myPC.m_PortList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myPort = myPC.m_PortList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myPort.GetType());
		SysInfoLog( str);
		str.Format( "Name: %s", myPort.GetName());
		SysInfoLog( str);
		str.Format( "Caption: %s", myPort.GetCaption());
		SysInfoLog( str);
		str.Format( "Description: %s", myPort.GetDescription());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myPort = myPC.m_PortList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "System Ports Hash: %s", myPC.m_PortList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Input Devices infos");
	SysInfoLog( "------------------------------------------------------");
	CInputDevice myInput;
	pos = myPC.m_InputList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myInput = myPC.m_InputList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myInput.GetType());
		SysInfoLog( str);
		str.Format( "Manufacturer: %s", myInput.GetManufacturer());
		SysInfoLog( str);
		str.Format( "Caption: %s", myInput.GetCaption());
		SysInfoLog( str);
		str.Format( "Description: %s", myInput.GetDescription());
		SysInfoLog( str);
		str.Format( "PointingType: %s", myInput.GetPointingType());
		SysInfoLog( str);
		str.Format( "Pointing Interface: %s", myInput.GetPointingInterface());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myInput = myPC.m_InputList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Input Devices Hash: %s", myPC.m_InputList.GetHash());
	SysInfoLog( str);

	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "System Controlers infos");
	SysInfoLog( "------------------------------------------------------");
	CSystemController myController;
	pos = myPC.m_SystemControllerList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myController = myPC.m_SystemControllerList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myController.GetType());
		SysInfoLog( str);
		str.Format( "Manufacturer: %s", myController.GetManufacturer());
		SysInfoLog( str);
		str.Format( "Name: %s", myController.GetName());
		SysInfoLog( str);
		str.Format( "Caption: %s", myController.GetCaption());
		SysInfoLog( str);
		str.Format( "Description: %s", myController.GetDescription());
		SysInfoLog( str);
		str.Format( "HW version: %s", myController.GetHardwareVersion());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myController = myPC.m_SystemControllerList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "System Controlers Hash: %s", myPC.m_SystemControllerList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Storage Peripherals infos");
	SysInfoLog( "------------------------------------------------------");
	CStoragePeripheral myStorage;
	pos = myPC.m_StorageList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myStorage = myPC.m_StorageList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myStorage.GetType());
		SysInfoLog( str);
		str.Format( "Manufacturer: %s", myStorage.GetManufacturer());
		SysInfoLog( str);
		str.Format( "Name: %s", myStorage.GetName());
		SysInfoLog( str);
		str.Format( "Model: %s", myStorage.GetModel());
		SysInfoLog( str);
		str.Format( "Description: %s", myStorage.GetDescription());
		SysInfoLog( str);
		str.Format( "Size: %I64u MB", myStorage.GetSize());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myStorage = myPC.m_StorageList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Storage Peripherals Hash: %s", myPC.m_StorageList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Network Adapters infos");
	SysInfoLog( "------------------------------------------------------");
	CNetworkAdapter myNetwork;
	pos = myPC.m_NetworkList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myNetwork = myPC.m_NetworkList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myNetwork.GetType());
		SysInfoLog( str);
		str.Format( "Description: %s", myNetwork.GetDescription());
		SysInfoLog( str);
		str.Format( "Speed: %s", myNetwork.GetSpeed());
		SysInfoLog( str);
		str.Format( "MAC: %s", myNetwork.GetMACAddress());
		SysInfoLog( str);
		str.Format( "IP @: %s", myNetwork.GetIPAddress());
		SysInfoLog( str);
		str.Format( "IP mask: %s", myNetwork.GetIPNetMask());
		SysInfoLog( str);
		str.Format( "IP Gateway: %s", myNetwork.GetGateway());
		SysInfoLog( str);
		str.Format( "DHCP Server: %s", myNetwork.GetDhcpServer());
		SysInfoLog( str);
		str.Format( "Status: %s", myNetwork.GetOperationalStatus());
		SysInfoLog( str);
		str.Format( "MIB Type: %s", myNetwork.GetTypeMIB());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myNetwork = myPC.m_NetworkList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Network Adapters Hash: %s", myPC.m_NetworkList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Telephony Modems infos");
	SysInfoLog( "------------------------------------------------------");
	CModem myModem;
	pos = myPC.m_ModemList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myModem = myPC.m_ModemList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Type: %s", myModem.GetType());
		SysInfoLog( str);
		str.Format( "Name: %s", myModem.GetName());
		SysInfoLog( str);
		str.Format( "Model: %s", myModem.GetModel());
		SysInfoLog( str);
		str.Format( "Description: %s", myModem.GetDescription());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myModem = myPC.m_ModemList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Telephony Modems Hash: %s", myPC.m_ModemList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Printers infos");
	SysInfoLog( "------------------------------------------------------");
	CPrinter myPrinter;
	pos = myPC.m_PrinterList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myPrinter = myPC.m_PrinterList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Name: %s", myPrinter.GetName());
		SysInfoLog( str);
		str.Format( "Driver: %s", myPrinter.GetDriver());
		SysInfoLog( str);
		str.Format( "Port: %s", myPrinter.GetPort());
		SysInfoLog( str);
		if (pos != NULL)
		{
			myPrinter = myPC.m_PrinterList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Printers Hash: %s", myPC.m_PrinterList.GetHash());
	SysInfoLog( str);


	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "OS infos");
	SysInfoLog( "------------------------------------------------------");
	str.Format( "Name: %s", myPC.GetOSName());
	SysInfoLog( str);
	str.Format( "Version: %s", myPC.GetOSVersion());
	SysInfoLog( str);
	str.Format( "Comment: %s", myPC.GetOSComment());
	SysInfoLog( str);
	str.Format( "Description: %s", myPC.GetDescription());
	SysInfoLog( str);
	switch (myPC.GetDeviceType())
	{
	case WINDOWS_SERVER:
		str = _T( "Windows Server");
		break;
	case WINDOWS_NOTEBOOK:
		str = _T( "Windows Notebook");
		break;
	default:
		str = _T( "Windows Workstation");
		break;
	}
	SysInfoLog( str);
	str.Format( "Domain or Workgroup: %s", myPC.GetDomainOrWorkgroup());
	SysInfoLog( str);
	str.Format( "OS Registered Company: %s", myPC.GetWindowsRegisteredCompany());
	SysInfoLog( str);
	str.Format( "OS Registered Owner: %s", myPC.GetWindowsRegisteredOwner());
	SysInfoLog( str);
	str.Format( "OS Product ID : %s", myPC.GetWindowsProductID());
	SysInfoLog( str);
	SysInfoLog( "");
	str.Format( "Device Hash: %s", myPC.GetHash());
	SysInfoLog( str);

	SysInfoLog( "");
	SysInfoLog( "------------------------------------------------------");
	SysInfoLog( "Registered Applications infos");
	SysInfoLog( "------------------------------------------------------");
	CSoftware myApp;
	pos = myPC.m_SoftwareList.GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myApp = myPC.m_SoftwareList.GetNext( pos);
	while (bContinue)
	{
		bContinue = (pos != NULL);
		str.Format( "Publisher: %s", myApp.GetPublisher());
		SysInfoLog( str);
		str.Format( "Name: %s", myApp.GetName());
		SysInfoLog( str);
		str.Format( "Version: %s", myApp.GetVersion());
		SysInfoLog( str);
		str.Format( "Folder: %s", myApp.GetFolder());
		SysInfoLog( str);
		str.Format( "Comments: %s", myApp.GetComments());
		SysInfoLog( str);
		if (myApp.IsFromRegistry())
			SysInfoLog( "Extracted from registry");
		else
			SysInfoLog( "Find on disk");
		if (pos != NULL)
		{
			myApp = myPC.m_SoftwareList.GetNext( pos);
			SysInfoLog( "");
		}
	}
	SysInfoLog( "");
	str.Format( "Registered Applications Hash: %s", myPC.m_SoftwareList.GetHash());
	SysInfoLog( str);

	m_List.AddString( "");
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Checking all registry values for key HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup");
	m_List.AddString( "------------------------------------------------------");
	CRegistryValue myRegVal;
	CRegistryValueList myRegList;
	CRegistry myReg;
	myReg.GetRegistryMultipleValues( myPC.GetDeviceID(), "Windows Setup", HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", &myRegList);
	pos = myRegList.GetHeadPosition();
	while (pos)
	{
		myRegVal = myRegList.GetNext( pos);
		m_List.AddString( myRegVal.GetValue());
	}
	m_List.AddString( "");

	m_List.AddString( "");
	m_List.AddString( "------------------------------------------------------");
	m_List.AddString( "Checking some registry value on key HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup");
	m_List.AddString( "------------------------------------------------------");
	CString csValue;
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "CDInstall", csValue);
	str.Format( "REG_DWORD CDInstall=%s", csValue);
	m_List.AddString( str);
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\", "InstallDate", csValue);
	str.Format( "REG_DWORD Windows NT InstallDate=%s", csValue);
	m_List.AddString( str);
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "BootDir", csValue);
	str.Format( "REG_SZ BootDir=%s", csValue);
	m_List.AddString( str);
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "DriverCachePath", csValue);
	str.Format( "REG_EXPAND_SZ DriverCachePath=%s", csValue);
	m_List.AddString( str);
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "Installation Sources", csValue);
	str.Format( "REG_MULTI_SZ Installation Sources=%s", csValue);
	m_List.AddString( str);
	myReg.GetRegistryValue( HKLM_TREE, "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Setup", "PrivateHash", csValue);
	str.Format( "REG_BINARY PrivateHash=%s", csValue);
	m_List.AddString( str);
	CloseLog();
}

void CTestSysInfoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	m_List.ResetContent();
}

