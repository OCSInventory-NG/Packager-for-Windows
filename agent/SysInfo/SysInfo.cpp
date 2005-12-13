// Document modified at : Friday, May 07, 2004 9:52:44 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//------------------------------------------------------------------------------

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SysInfo.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SysInfo.h"
#include "Cpu_Info.h"
#include "IPHelper.h"
#include "SNMP.h"
#include "FileVersion.h"
#include "dtwinver.h"

CString getDir(int dir=0)
{
	char direc[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,direc);
	CString ret;

	if(dir==0)
	{
		ret.Format("%s\\%s",direc,OCS_IDENTIFICATION_FILE);
	}
	else
	{
		ret.Format("%s\\%s",direc,OCS_ACCOUNTINFO_FILE);
	}
	return ret;
}

SysInfo::SysInfo()
{
	GetSystemInfo( &m_SystemInfo);
	m_wmiInfo.Connect();
	m_registryInfo.Connect();
	m_edidInfo.Connect();
}

SysInfo::~SysInfo()
{
	// Nothing to do yet
	m_wmiInfo.Disconnect();
	m_registryInfo.Disconnect();
	m_edidInfo.Disconnect();
}

UINT SysInfo::getOS( CString &csName, CString &csVersion, CString &csComment, CString &csDescription)
{
	if (m_wmiInfo.IsWmiConnected())
		return m_wmiInfo.GetOS( csName, csVersion, csComment, csDescription);
	AddLog( _T( "dtWinVer GetOS..."));
	COSVersion::OS_VERSION_INFO osvi;
	COSVersion					os;
	BOOL						bIsServer = FALSE;

	memset(&osvi, 0, sizeof(osvi));
	if (os.GetVersion(&osvi))
	{
		// Get OS name and comments
		switch (osvi.UnderlyingPlatform)
		{
			case COSVersion::Dos:               
			{
				csName = _T("DOS");
				csComment.Empty();
				break;
			}
			case COSVersion::Windows3x:         
			{
				csName = _T("Microsoft Windows 3.X");
				csComment.Empty();
				break;
			}
			case COSVersion::WindowsCE:            
			{
				csName = _T("Microsoft Windows CE");
				csComment.Empty();
				break;
			}
			case COSVersion::Windows9x:           
			{
				if (os.IsWindows95(&osvi))
				{
					csName = _T( "Microsoft Windows 95");
					csComment.Empty();
				}
				else if (os.IsWindows95SP1(&osvi))
				{
					csName = _T( "Microsoft Windows 95");
					csComment = _T( "Service Pack 1");
				}
				else if (os.IsWindows95B(&osvi))
				{
					csName = _T( "Microsoft Windows 95");
					csComment = _T( "Operating System Release 2.0/2.1 (B)");
				}
				else if (os.IsWindows95C(&osvi))
				{
					csName = _T( "Microsoft Windows 95");
					csComment = _T( "Operating System Release 2.5 (C)");
				}
				else if (os.IsWindows98(&osvi))
				{
					csName = _T( "Microsoft Windows 98");
					csComment.Empty();
				}
				else if (os.IsWindows98SP1(&osvi))
				{
					csName = _T( "Microsoft Windows 98");
					csComment = _T( "Service Pack 1");
				}
				else if (os.IsWindows98SE(&osvi))
				{
					csName = _T( "Microsoft Windows 98");
					csComment = _T( "Second Edition");
				}
				else if (os.IsWindowsME(&osvi))
				{
					csName = _T( "Microsoft Windows Millenium");
					csComment.Empty();
				}
				else
				{
					csName = _T( "Unknown OS");
					csComment.Empty();
				}
				break;
			}
			case COSVersion::WindowsNT:    
			{
				if (os.IsNTPreWin2k(&osvi))
				{
					csName.Format( _T( "Microsoft Windows NT %d.%d"),
									osvi.dwUnderlyingMajorVersion,
									osvi.dwUnderlyingMinorVersion);

					if (os.IsNTWorkstation(&osvi))
						csName += _T(" Workstation");
					else if (os.IsNTDatacenterServer(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Datacenter");
					}
					else if (os.IsNTEnterpriseServer(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Enterprise");
					}
					else 
					{
						bIsServer = TRUE;
						csName += _T(" Server");
					}
					csComment = osvi.szUnderlyingCSDVersion;
				}
				else if (os.IsWindows2000(&osvi))
				{
					csName = _T("Microsoft Windows 2000");

					if (os.IsWin2000Professional(&osvi))
						csName += _T(" Professional");
					else if (os.IsWin2000DatacenterServer(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Datacenter");
					}
					else if (os.IsWin2000AdvancedServer(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Advanced Server");
					}
					else 
					{
						bIsServer = TRUE;
						csName += _T(" Server");
					}
					csComment = osvi.szUnderlyingCSDVersion;
				}
				else if (os.IsWindowsXP(&osvi))
				{
					csName = _T("Microsoft Windows XP");

					if (os.IsXPPersonal(&osvi))
						csName += _T(" Home");                  
					else if (os.IsXPProfessional(&osvi))
						csName += _T(" Professional");                  
					csComment = osvi.szUnderlyingCSDVersion;
				}
				else if (os.IsWindowsServer2003(&osvi))
				{
					csName = _T("Microsoft Windows Server 2003");

					if (os.IsWin2000Professional(&osvi))
						csName += _T(" Professional");
					else if (os.IsDatacenterWindowsServer2003(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Datacenter Edition");
					}
					else if (os.IsEnterpriseWindowsServer2003(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Enterprise Edition");
					}
					else if (os.IsWebWindowsServer2003(&osvi))
					{
						bIsServer = TRUE;
						csName += _T(" Web Edition");
					}
					csComment = osvi.szUnderlyingCSDVersion;
				}
				else if (os.IsWindowsVista(&osvi))
				{
					csName = _T("Microsoft Windows Vista");

					if (os.IsXPPersonal(&osvi))
						csName += _T(" Home");                  
					else if (os.IsXPProfessional(&osvi))
						csName += _T(" Professional");                  
					csComment = osvi.szUnderlyingCSDVersion;
				}

				if (os.IsTerminalServicesInRemoteAdminMode(&osvi))
					csComment += _T(" (Terminal Services in Remote Admin Mode)");
				else if (os.IsTerminalServicesInstalled(&osvi))
					csComment += _T(" (Terminal Services)");
				if (os.ISSmallBusinessEditionInstalled(&osvi))
					csComment += _T(" (BackOffice Small Business Edition)");
				if (os.IsEmbedded(&osvi))
					csComment += _T(" (Embedded)");
				if (os.IsEmulated64Bit(&osvi))
					csComment += _T(" (64 Bit Edition)");
				break;
			}
			default:                         
			{
				csName = _T("Unknown OS");
				csComment.Empty();
				break;
			}
		}
		// Format version and build number
		csVersion.Format( _T("%d.%d.%d"), osvi.dwUnderlyingMajorVersion,
											 osvi.dwUnderlyingMinorVersion,
											 osvi.dwUnderlyingBuildNumber);
	}
	else
	{
		AddLog( _T( "Failed in call to GetVersion !\n"));
		csName = _T( "Unbknown OS");
		csVersion = NOT_AVAILABLE;
		csComment.Empty();
		return WINDOWS_WORKSTATION;
	}
	AddLog( _T( "%s %s %s. OK\n"), csName, csVersion, csComment);
	csDescription = m_registryInfo.GetDeviceDescription();
	return (bIsServer ? WINDOWS_SERVER : WINDOWS_WORKSTATION);
}

BOOL SysInfo::getMemory( ULONG *m_ulPhysicalMemory, ULONG *m_ulSwapSize)
{
	CMemory		memoryInfo;
	ULONGLONG	ulTotalRAM,
				ulTotalSwap;

	AddLog( _T( "getMemory..."));
	ulTotalRAM = memoryInfo.getTotalRAM() / ONE_MEGABYTE;
	*m_ulPhysicalMemory = (ULONG) ulTotalRAM;
	ulTotalSwap = memoryInfo.getTotalPageFile() / ONE_MEGABYTE;
	*m_ulSwapSize = (ULONG) ulTotalSwap;
	AddLog( _T( "Physical: %I64u bytes, Swap: %I64u bytes. OK\n"), memoryInfo.getTotalRAM(), memoryInfo.getTotalPageFile());
	return TRUE;
}

LPCTSTR SysInfo::getLocalIP()
{
	return m_Sock.GetIPAddress();
}

DWORD SysInfo::getProcessors( CString &csProcType, CString &csProcSpeed)
{
	CString csRegType = NOT_AVAILABLE,
			csRegSpeed = NOT_AVAILABLE;
	DWORD	dwRegNumber = 0;

	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetProcessors( csProcType, csProcSpeed))	
	{
		AddLog( _T( "WMI GetProcessors: %lu processor(s) found.\n"), m_SystemInfo.dwNumberOfProcessors);
		return m_SystemInfo.dwNumberOfProcessors;
	}
			
	// WMI not available => using CAMEL
	try
	{
		dwRegNumber = m_registryInfo.GetProcessors( csRegType, csRegSpeed);
		AddLog( _T( "CAMEL getProcessors: Trying to use CAMEL classes..."));
		CPUInfo    cpuInfo;
		// Get Processor name
		csProcType.Format( _T( "%s %s"), cpuInfo.GetVendorID(), cpuInfo.GetExtendedProcessorName());
		// Get Processor Speed
		if ((dwRegNumber > 0) && (csRegSpeed != NOT_AVAILABLE))
			// We've found at least 1 proc in registry and
			// Speed is available in registry => use it
			csProcSpeed = csRegSpeed;
		else
			// Use CAMEL speed => may be inconsistent
			csProcSpeed.Format( _T( "%d"), cpuInfo.GetProcessorClockFrequency());
		
		AddLog( _T( "%s %s (Family %d Model %d Stepping %d) %d MHz. OK\n"),
				cpuInfo.GetVendorID(),
				cpuInfo.GetExtendedProcessorName(), m_SystemInfo.wProcessorLevel,
				(m_SystemInfo.wProcessorRevision & 0xFF00) >> 8,
				m_SystemInfo.wProcessorRevision & 0X00FF,
				cpuInfo.GetProcessorClockFrequency());
	}
	catch (CException *pEx)
	{
		AddLog( _T( "CAMEL getProcessors: Failed because unknown exception...\n"));
		pEx->Delete();
		// Try registry
		return m_registryInfo.GetProcessors( csProcType, csProcSpeed);
	}
	// return the number of processors
	AddLog( _T( "CAMEL getProcessors: %lu processor(s) found.\n"), m_SystemInfo.dwNumberOfProcessors);
	return m_SystemInfo.dwNumberOfProcessors;
}

BOOL SysInfo::getSystemPorts( CSystemPortList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetSystemPorts( pMyList))
		return TRUE;
	return m_registryInfo.GetSystemPorts( pMyList);
}

BOOL SysInfo::getPrinters( CPrinterList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetPrinters( pMyList))
		return TRUE;
	return m_registryInfo.GetPrinters( pMyList);
}

BOOL SysInfo::getSoundDevices( CSoundDeviceList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetSoundDevices( pMyList))
		return TRUE;
	return m_registryInfo.GetSoundDevices( pMyList);
}

BOOL SysInfo::getMemorySlots( CMemorySlotList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetMemorySlots( pMyList))
		return TRUE;
	return FALSE;
}

BOOL SysInfo::getModems( CModemList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetModems( pMyList))
		return TRUE;
	return m_registryInfo.GetModems( pMyList);
}

BOOL SysInfo::getMonitors( CMonitorList *pMyList)
{
	// First try EDID
	if (m_edidInfo.IsConnected() && m_edidInfo.GetMonitors( pMyList))
		return TRUE;
	// Next, try WMI
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetMonitors( pMyList))
		return TRUE;
	// Else use registry
	return m_registryInfo.GetMonitors( pMyList);
}

BOOL SysInfo::getNetworkAdapters( CNetworkAdapterList *pMyList)
{
	if (CIPHelper::GetNetworkAdapters( pMyList))
		return TRUE;
	return CSNMP::GetNetworkAdapters( pMyList);
}

BOOL SysInfo::getVideoAdapters( CVideoAdapterList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetVideoAdapters( pMyList))
		return TRUE;
	return m_registryInfo.GetVideoAdapters( pMyList);
}

BOOL SysInfo::getSystemControllers( CSystemControllerList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetSystemControllers( pMyList))
		return TRUE;
	return m_registryInfo.GetSystemControllers( pMyList);
}

BOOL SysInfo::getStoragePeripherals( CStoragePeripheralList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetStoragePeripherals( pMyList))
		return TRUE;
	return m_registryInfo.GetStoragePeripherals( pMyList);
}

BOOL SysInfo::getSystemSlots( CSystemSlotList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetSystemSlots( pMyList))
		return TRUE;
	return FALSE;
}

BOOL SysInfo::getBiosInfo( CBios *pMyBios)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetBiosInfo( pMyBios))
		return TRUE;
	return m_registryInfo.GetBiosInfo( pMyBios);
}

BOOL SysInfo::isNotebook()
{
	if (m_wmiInfo.IsWmiConnected())
		return m_wmiInfo.IsNotebook();
	return m_registryInfo.IsNotebook();
}


BOOL SysInfo::getUserName(CString &csUserName)
{

	TCHAR szUserName[80]; 
	DWORD dwUserName = 80; 
 
	// Call the GetUserName function.
	AddLog( _T( "getUserName: Trying to get logged on User ID..."));
	if (GetUserName( szUserName, &dwUserName))
	{
		AddLog( _T( "OK (%s).\n"), szUserName);
		csUserName = szUserName;
		return TRUE;
	}
	AddLog( _T( "Failed !\n"));
	return m_registryInfo.GetLoggedOnUser( csUserName);
}

BOOL SysInfo::getRegistryApplications(CSoftwareList *pList, BOOL hkcu)
{
	return m_registryInfo.GetRegistryApplications( pList, hkcu);
}

BOOL SysInfo::getDomainOrWorkgroup(CString &csDomain)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetDomainOrWorkgroup( csDomain))
		return TRUE;
	return m_registryInfo.GetDomainOrWorkgroup( csDomain);
}

LPCTSTR SysInfo::getDeviceID()
{
	LPCTSTR lpstrDeviceID;

	// First, try to get Device ID from file (backup method)
	lpstrDeviceID = getFileDeviceID();
/*	if (lpstrDeviceID == NULL)
		// Unable to get Device ID from file => try to get it from registry (normal method)
		lpstrDeviceID = m_registryInfo.GetDeviceID();*/
	return lpstrDeviceID;
}

BOOL SysInfo::setDeviceID( LPCTSTR lpstrDeviceID)
{
	// First, try to set Device ID in the registry
	// ASPLE
	//if (!m_registryInfo.SetDeviceID( lpstrDeviceID))
		// Unable to set Device ID in the registry => try to set in file
		return setFileDeviceID( lpstrDeviceID);
	//return TRUE;
}

BOOL SysInfo::getWindowsRegistration( CString &csCompany, CString &csOwner, CString &csProductID)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetWindowsRegistration( csCompany, csOwner, csProductID))
		return TRUE;
	return m_registryInfo.GetWindowsRegistration( csCompany, csOwner, csProductID);
}

BOOL SysInfo::getRegistryValue( UINT uKeyTree, LPCTSTR lpstrSubKey, LPCTSTR lpstrValue, CString &csResult)
{
	return m_registryInfo.GetRegistryValue( uKeyTree, lpstrSubKey, lpstrValue, csResult);
}

BOOL SysInfo::getRegistryMultipleValues(LPCTSTR lpstrDeviceID, LPCTSTR lpstrName, UINT uKeyTree, LPCTSTR lpstrSubKey, CRegistryValueList *pMyList)
{
	return m_registryInfo.GetRegistryMultipleValues( lpstrDeviceID, lpstrName, uKeyTree, lpstrSubKey, pMyList);
}

BOOL SysInfo::getInputDevices( CInputDeviceList *pMyList)
{
	if (m_wmiInfo.IsWmiConnected() && m_wmiInfo.GetInputDevices( pMyList))
		return TRUE;
	return m_registryInfo.GetInputDevices( pMyList);
}

LPCTSTR SysInfo::getFileDeviceID()
{
	static TCHAR szDeviceID[_MAX_PATH+1];
	
	AddLog( _T( "File GetDeviceID on %s..."), getDir(0));
	if (GetPrivateProfileString( OCS_AGENT_KEY, OCS_DEVICE_ID_VALUE, _T( ""), szDeviceID, _MAX_PATH, getDir()) == 0)
	{
		AddLog( _T( "Failed in call to <GetPrivateProfileString> function with error %lu !\n"), GetLastError());
		return NULL;
	}
	AddLog( _T( "OK (%s).\n"), szDeviceID);
	return szDeviceID;
}

BOOL SysInfo::setFileDeviceID(LPCTSTR lpstrDeviceID)
{
	HANDLE	hFile;

	AddLog( _T( "File SetDeviceID on %s..."), getDir());
	// Create the file with system and hidden attributes
	if ((hFile = CreateFile( getDir(), GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL,
							 CREATE_NEW, FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN, NULL)) == INVALID_HANDLE_VALUE)
	{
		AddLog( _T( "Failed in call to <CreateFile> function with error %lu !\n"), GetLastError());	
	}
	else
		CloseHandle( hFile);

	if (WritePrivateProfileString( OCS_AGENT_KEY, OCS_DEVICE_ID_VALUE, lpstrDeviceID, getDir()) == 0)
	{
		AddLog( _T( "Failed in call to <WritePrivateProfileString> function with error %lu !\n"), GetLastError());
		return FALSE;
	}
	AddLog( _T( "OK (%s).\n"), lpstrDeviceID);
	return TRUE;
}
