// Document modified at : Saturday, January 03, 2004 11:36:40 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// OSInfo.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SysInfoClasses.h"

#include "OSInfo.h"
#include "DebugLog.h"
#include <lmcons.h>
#include <lmerr.h>
#include <lmserver.h>


// NetServerGetInfo function

// This struct is declared in the svrapi.h file which conflict with lmservers.h
// So copy of declaration here to resolve conflict
typedef struct server_info_1 {
    char	    sv1_name[CNLEN + 1];
    unsigned char   sv1_version_major;		/* Major version # of net   */
    unsigned char   sv1_version_minor;		/* Minor version # of net   */
    unsigned long   sv1_type;	     		/* Server type 		    */
    char FAR *	    sv1_comment; 			/* Exported server comment  */
} server_info_1, *Pserver_info_1, *LPserver_info_1;	 /* server_info_1 */

NET_API_STATUS (__stdcall *pfnNetServerGetInfoNT) (LPWSTR lpstrComputerName, DWORD dwLevel, LPBYTE *lpBuffer);
NET_API_STATUS (__stdcall *pfnNetApiBufferFreeNT) (LPVOID lpBuffer);

// Defines for retrieving Vendor and Processor names from registry
#define NT_PRODUCT_OPTIONS			_T( "System\\CurrentControlSet\\Control\\ProductOptions")
// Define for retrieving computer description from 9X registry
#define WIN_COMPUTER_DESCRIPTION	_T( "System\\CurrentControlSet\\Services\\VxD\\VNETSUP")

COSInfo::COSInfo()
{
	_tcscpy( m_szOSName, NOT_AVAILABLE);
	_tcscpy( m_szOSName, NOT_AVAILABLE);
	_tcscpy( m_szOSName, NOT_AVAILABLE);
	_tcscpy( m_szDeviceDescription, NOT_AVAILABLE);
	m_bIsServer = FALSE;
	m_bIsWinNT = FALSE;
	determineOSInfo();
}

COSInfo::COSInfo(const COSInfo& source)
{
	assign(source);
}

COSInfo& COSInfo::operator=(const COSInfo& right)
{
	if (this != &right)
		assign(right);
	return (*this);
}

COSInfo::~COSInfo()
{
   // nothing to do yet
}

void COSInfo::assign(const COSInfo& source)
{
	_tcsncpy( m_szOSName, source.m_szOSName, 256);
	_tcsncpy( m_szOSVersion, source.m_szOSVersion, 256);
	_tcsncpy( m_szOSComment, source.m_szOSComment, 256);
	_tcsncpy( m_szDeviceDescription, source.m_szDeviceDescription, 256);
	m_bIsServer = source.m_bIsServer;
	m_bIsWinNT = source.m_bIsWinNT;
}

void COSInfo::determineOSInfo(void)
{
	OSVERSIONINFOEX osvi;
	BOOL			bIsWindows64Bit = FALSE;
	BOOL			bOsVersionInfoEx = FALSE;
	UINT			uNTProduct = PLATFORM_NT_UNKNOWN,
					uNTRole = ROLE_NT_UNKNOWN;


	// Try calling GetVersionEx using the OSVERSIONINFOEX structure.
	// If that fails, try using the OSVERSIONINFO structure.
	memset( &osvi, 0, sizeof (OSVERSIONINFOEX));
	osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFOEX);

	if (!(bOsVersionInfoEx = GetVersionEx ((OSVERSIONINFO *) &osvi)))
	{
		// If OSVERSIONINFOEX doesn't work, try OSVERSIONINFO.
		osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
		if (!GetVersionEx ((OSVERSIONINFO *) &osvi))
		{
			return;
		}
	}

	switch (osvi.dwPlatformId)
	{
	case VER_PLATFORM_WIN32s:
		_tcscpy( m_szOSName, _T( "Win32 Emulation"));
		_stprintf( m_szOSVersion, _T( "%u.%u"), osvi.dwMajorVersion, osvi.dwMinorVersion);
		_stprintf( m_szOSComment, _T( "build %u %s"),
							LOWORD( osvi.dwBuildNumber), 
							osvi.szCSDVersion);
		m_bIsServer = FALSE;
		m_bIsWinNT = FALSE;
		break;

	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/ME
		m_bIsServer = FALSE;
		m_bIsWinNT = FALSE;
		switch (osvi.dwMajorVersion)
		{
		case 0:
		case 1: // Windows 1.X
		case 2:	// Windows 2.X
		case 3: // Windows 3.X
			// Error because 16 bits OS or unknown
			break;
		case 4:	// Windows 9X
			switch (osvi.dwMinorVersion)
			{
			case 0:	// Windows 95
				_tcscpy( m_szOSName, _T( "Windows 95"));
				if ((LOWORD( osvi.dwBuildNumber) > 950) & (LOWORD( osvi.dwBuildNumber) < 1080))
				{
					// SR1
					_stprintf( m_szOSComment, _T( "build %u (Service Pack 1) %s"),
											  LOWORD( osvi.dwBuildNumber), 
											  osvi.szCSDVersion);
				}
				else
				{
					if (LOWORD( osvi.dwBuildNumber) >= 1080)
					{
						// OSR2
						_stprintf( m_szOSComment, _T( "build %u (Operating System Release 2) %s"),
												  LOWORD( osvi.dwBuildNumber), 
												  osvi.szCSDVersion);
					}
					else
					{
						// First version
						_stprintf( m_szOSComment, _T( "build %u %s"),
												  LOWORD( osvi.dwBuildNumber), 
												  osvi.szCSDVersion);
					}
				}
				break;
			case 10: // Windows 98
				if (LOWORD( osvi.dwBuildNumber) == 1998)
				{
					// First version
					_tcscpy( m_szOSName, _T( "Windows 98"));
					_stprintf( m_szOSComment, _T( "build %u %s"),
											  LOWORD( osvi.dwBuildNumber), 
											  osvi.szCSDVersion);
				}
				else
				{
					if (LOWORD( osvi.dwBuildNumber) < 2183)
					{
						// SR1
						_tcscpy( m_szOSName, _T( "Windows 98"));
						_stprintf( m_szOSComment, _T( "build %u (Service Pack 1) %s"),
												  LOWORD( osvi.dwBuildNumber), 
												  osvi.szCSDVersion);
					}
					else
					{
						// Second Edition
						_tcscpy( m_szOSName, _T( "Windows 98 SE"));
						_stprintf( m_szOSComment, _T( "build %u %s"),
												  LOWORD( osvi.dwBuildNumber), 
												  osvi.szCSDVersion);
					}
				}
				break;
			case 90: // Windows ME
			default:
				_tcscpy( m_szOSName, _T( "Windows ME"));
				_stprintf( m_szOSComment, _T( "build %u %s"),
										  LOWORD( osvi.dwBuildNumber), 
										  osvi.szCSDVersion);
				break;
			}
			break;
		default: // Windows ME ?
			_tcscpy( m_szOSName, _T( "Windows ME"));
			_stprintf( m_szOSComment, _T( "build %u %s"),
									  LOWORD( osvi.dwBuildNumber), 
									  osvi.szCSDVersion);
			break;
		}
		_stprintf( m_szOSVersion, _T( "%u.%u"), osvi.dwMajorVersion, osvi.dwMinorVersion);
		break;

	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		m_bIsWinNT = TRUE;
		if (osvi.dwMajorVersion <= 4)
			_tcscpy( m_szOSName, "Windows NT");
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			_tcscpy( m_szOSName, "Windows 2000");
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			_tcscpy( m_szOSName, "Windows XP");

		// Test for NT platform type.
		if (bOsVersionInfoEx)
			uNTProduct = WhichNTProduct( &osvi);
		if (uNTProduct == PLATFORM_NT_UNKNOWN)
			// Check NT platform type from the registry
			uNTProduct = WhichNTProductRegistry();
		switch (uNTProduct)
		{
		case PLATFORM_NT_PERSONAL:
			_tcscat( m_szOSName, _T( " Home Edition"));
			m_bIsServer = FALSE;
			break;
		case PLATFORM_NT_WORKSTATION:
			if (osvi.dwMajorVersion <= 4)
				_tcscat( m_szOSName, _T( " Workstation"));
			else
				_tcscat( m_szOSName, _T( " Professional"));
			m_bIsServer = FALSE;
			break;
		case PLATFORM_NT_SERVER:
			// Check for 2003 Server instead of Windows XP.
			if (osvi.dwMajorVersion >= 5 && osvi.dwMinorVersion >= 1)
				_tcscpy( m_szOSName, "Windows 2003 Server");
			else
				_tcscat( m_szOSName, _T( " Server"));
			m_bIsServer = TRUE;
			break;
		case PLATFORM_NT_TERMINAL_SERVER:
			// Check for 2003 Server instead of Windows XP.
			if (osvi.dwMajorVersion >= 5 && osvi.dwMinorVersion >= 1)
				_tcscpy( m_szOSName, "Windows 2003 Server");
			else
			{
				if (osvi.dwMajorVersion <= 4)
					// Windows NT4 Terminal
					_tcscat( m_szOSName, _T( " Terminal Server"));
				else
					// Windows 2000 Server has terminal service enabled
					_tcscat( m_szOSName, _T( " Server"));
			}
			m_bIsServer = TRUE;
			break;
		case PLATFORM_NT_ENTERPRISE_SERVER:
			// Enterprise mean that clustering is supported (NT Enterprise/2K Adanced/2003 Enterprise)
			// Check for 2003 Server instead of Windows XP.
			if (osvi.dwMajorVersion >= 5 && osvi.dwMinorVersion >= 1)
				_tcscpy( m_szOSName, "Windows 2003 Enterprise Server");
			else
			{
				// Check for Windows 2000 Advanced instead of Enterprise
				if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
					_tcscat( m_szOSName, _T( " Advanced Server"));
				else
					_tcscat( m_szOSName, _T( " Enterprise Server"));
			}
			m_bIsServer = TRUE;
			break;
		case PLATFORM_NT_DATACENTER_SERVER:
			// Enterprise mean that clustering is supported (NT Enterprise/2K Adanced/2003 Enterprise)
			// Check for 2003 Server instead of Windows XP.
			if (osvi.dwMajorVersion >= 5 && osvi.dwMinorVersion >= 1)
				_tcscpy( m_szOSName, "Windows 2003 DataCenter Server");
			else
				_tcscat( m_szOSName, _T( " DataCenter Server"));
			m_bIsServer = TRUE;
			break;
		default:
			// Unknown NT product
			_tcscpy( m_szOSName, _T( "Windows NT based"));
			m_bIsServer = FALSE;
			break;
		}

		// Store version
		_stprintf( m_szOSVersion, _T( "%u.%u.%u"), 
					osvi.dwMajorVersion,
					osvi.dwMinorVersion,
					LOWORD( osvi.dwBuildNumber));
		
		// Store comments
		_stprintf( m_szOSComment, _T( "%s"), osvi.szCSDVersion);

		// Check for 64 bits XP/2003 support
		if (osvi.dwMajorVersion >= 5 && osvi.dwMinorVersion >= 1)
		{
			// Windows XP and 2003 server.support 64 bits processors
			typedef BOOL (CALLBACK* LPFNPROC) (HANDLE, BOOL *);
			HINSTANCE hKernelDLL; 
			LPFNPROC DLLProc;
			
			// Load the Kernel32 DLL.
			hKernelDLL = LoadLibrary ("kernel32");
			if (hKernelDLL != NULL)
			{ 
				// Only XP and 2003 Server support IsWOW64Process so... Load dynamically!
				DLLProc = (LPFNPROC) GetProcAddress (hKernelDLL, "IsWow64Process"); 
			 
				// If the function address is valid, call the function.
				if (DLLProc != NULL)
					(DLLProc) (GetCurrentProcess (), &bIsWindows64Bit);
				else 
					bIsWindows64Bit = FALSE;
			 
				// Free the DLL module.
				FreeLibrary (hKernelDLL); 
			} 
 			// IsWow64Process ();
			if (bIsWindows64Bit)
				_tcscat( m_szOSComment, " 64-Bit");
		}

		// check server role if needed
		if (m_bIsServer)
		{
			uNTRole = WhichNTRole();
			if (uNTRole == ROLE_NT_UNKNOWN)
				uNTRole = WhichNTRoleRegistry();
			switch (uNTRole)
			{
			case ROLE_NT_STAND_ALONE_SERVER:
				_tcscat( m_szOSComment, _T( " (Stand Alone Server)"));
				break;
			case ROLE_NT_PRIMARY_DOMAIN_CONTROLLER:
				_tcscat( m_szOSComment, _T( " (Primary Domain Controler)"));
				break;
			case ROLE_NT_BACKUP_DOMAIN_CONTROLLER:
				_tcscat( m_szOSComment, _T( " (Backup Domain Controler)"));
				break;
			default:
				break;
			}
		}
		break;

	default:
		// Unknown
		_tcscpy( m_szOSName, NOT_AVAILABLE);
		_stprintf( m_szOSVersion, _T( "%u.%u.%u"), 
					osvi.dwMajorVersion,
					osvi.dwMinorVersion,
					LOWORD( osvi.dwBuildNumber));
		_stprintf( m_szOSComment, _T( "%s"), osvi.szCSDVersion);
		m_bIsServer = FALSE;
		m_bIsWinNT = FALSE;
		break;
	}
}

UINT COSInfo::WhichNTProduct( OSVERSIONINFOEX *posvi)
{
	// check product options, in order of likelihood   
	if (posvi->wProductType == VER_NT_WORKSTATION)
	{
		if (posvi->wSuiteMask & VER_SUITE_PERSONAL)
			return PLATFORM_NT_PERSONAL;
		else
			return PLATFORM_NT_WORKSTATION;
	}
	if (posvi->wProductType == VER_NT_SERVER)
	{
		// Continue with the type detection.
		if (posvi->wSuiteMask & VER_SUITE_DATACENTER)
			return PLATFORM_NT_DATACENTER_SERVER;
		else
		{
			if (posvi->wSuiteMask & VER_SUITE_ENTERPRISE)
				return PLATFORM_NT_ENTERPRISE_SERVER;
			else
				return PLATFORM_NT_SERVER;
		}
	}
	return PLATFORM_NT_UNKNOWN;
}

UINT COSInfo::WhichNTProductRegistry()
{
	// check product options, in order of likelihood   
	if (IsHomeEdition())
		return PLATFORM_NT_PERSONAL;
	if (IsProfessional())
		return PLATFORM_NT_WORKSTATION;
	if (IsDataCenterServer())
		return PLATFORM_NT_DATACENTER_SERVER;
	if (IsEnterpriseServer())
		return PLATFORM_NT_ENTERPRISE_SERVER;
	if (IsTerminalServer())
		return PLATFORM_NT_TERMINAL_SERVER;
	if (IsStandAloneServer() || IsPDC() || IsBDC())
		return PLATFORM_NT_SERVER;
	return PLATFORM_NT_UNKNOWN;
}

UINT COSInfo::WhichNTRole()
{
	HINSTANCE	    hDll;
	LPBYTE			myBuffer;

	// Windows NT/2000/XP	
	// Load the netapi 32 bit DLL
	if ((hDll = LoadLibrary( _T( "netapi32.dll"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.
		return ROLE_NT_UNKNOWN;
	}
	// Load the NetServerGetInfo function
	if ((*(FARPROC*)&pfnNetServerGetInfoNT = GetProcAddress( hDll, _T( "NetServerGetInfo"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.                                  
		FreeLibrary( hDll);
		return ROLE_NT_UNKNOWN;
	}
	// Load the NetApiBufferFree function
	if ((*(FARPROC*)&pfnNetApiBufferFreeNT = GetProcAddress( hDll, _T( "NetApiBufferFree"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.                                  
		FreeLibrary( hDll);
		return ROLE_NT_UNKNOWN;
	}
	if (pfnNetServerGetInfoNT( NULL, 101, &myBuffer) == NERR_Success)
	{
		DWORD dwType = ((LPSERVER_INFO_101)myBuffer)->sv101_type;

		if (((SERVER_INFO_101 *)myBuffer)->sv101_type & SV_TYPE_DOMAIN_CTRL)
		{
			// Primary domain controler
			pfnNetApiBufferFreeNT( myBuffer);
			FreeLibrary( hDll);
		    return ROLE_NT_PRIMARY_DOMAIN_CONTROLLER;
		}
		if (((SERVER_INFO_101 *)myBuffer)->sv101_type & SV_TYPE_DOMAIN_BAKCTRL)
		{
			// Backup domain controler
			pfnNetApiBufferFreeNT( myBuffer);
			FreeLibrary( hDll);
		    return ROLE_NT_BACKUP_DOMAIN_CONTROLLER;
		}
		if (((SERVER_INFO_101 *)myBuffer)->sv101_type & SV_TYPE_SERVER_NT)
		{
			// Stand alone server
			pfnNetApiBufferFreeNT( myBuffer);
			FreeLibrary( hDll);
			return ROLE_NT_STAND_ALONE_SERVER;
		}
	}
	FreeLibrary( hDll);
	return ROLE_NT_UNKNOWN;
}

UINT COSInfo::WhichNTRoleRegistry()
{
	if (IsStandAloneServer())
		return ROLE_NT_STAND_ALONE_SERVER;
	if (IsPDC())
		return ROLE_NT_PRIMARY_DOMAIN_CONTROLLER;
	if (IsBDC())
		return ROLE_NT_BACKUP_DOMAIN_CONTROLLER;
	return ROLE_NT_UNKNOWN;
}

BOOL COSInfo::IsHomeEdition() 
{
	return ValidateProductType( _T( "WINNT")) && ValidateProductSuite( _T( "Personal"));
}

BOOL COSInfo::IsProfessional() 
{
	return ValidateProductType( _T( "WINNT"));;
}

BOOL COSInfo::IsStandAloneServer() 
{
	return ValidateProductType( _T( "SERVERNT"));;
}

BOOL COSInfo::IsPDC() 
{
	return ValidateProductType( _T( "LANMANNT"));;
}

BOOL COSInfo::IsBDC() 
{
	return ValidateProductType( _T( "LANSECNT"));;
}

BOOL COSInfo::IsTerminalServer() 
{
	return (IsStandAloneServer() ||IsPDC() || IsBDC()) && ValidateProductSuite( _T( "Terminal Server"));;
}

BOOL COSInfo::IsEnterpriseServer()
{
	return (IsStandAloneServer() ||IsPDC() || IsBDC()) && ValidateProductSuite( _T( "Enterprise"));
}

BOOL COSInfo::IsDataCenterServer()
{
	return (IsStandAloneServer() ||IsPDC() || IsBDC()) && ValidateProductSuite( _T( "DataCenter"));
}

BOOL COSInfo::ValidateProductSuite( LPCTSTR lpszSuiteToValidate) 
{
	// Open the ProductOptions key.
	HKEY	hKey = NULL;
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, NT_PRODUCT_OPTIONS, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
		return FALSE;

	// Determine required size of ProductSuite buffer.
	DWORD dwType = 0;
	DWORD dwSize = 0;
	lResult = RegQueryValueEx(hKey, _T( "ProductSuite"), NULL, &dwType, NULL, &dwSize);
	if (lResult != ERROR_SUCCESS || !dwSize)
	{
		RegCloseKey( hKey);
		return FALSE;
	}

	// Allocate buffer.
	LPTSTR lpszProductSuites = (LPTSTR) new BYTE[dwSize];

	// Retrieve array of product suite strings.
	lResult = RegQueryValueEx( hKey, _T( "ProductSuite"), NULL, &dwType, (LPBYTE) lpszProductSuites, &dwSize);
	if (lResult != ERROR_SUCCESS || dwType != REG_MULTI_SZ)
	{
		//Don't forget to free up the resource we used
		delete [] lpszProductSuites;
		RegCloseKey( hKey);
		return FALSE;
	}

	//All string comparisons will be sub string only and case insensitive
	LPTSTR lpszLocalSuite = new TCHAR[_tcslen( lpszSuiteToValidate)+1];
	_tcscpy( lpszLocalSuite, lpszSuiteToValidate);
	_tcsupr( lpszLocalSuite);

	// Search for suite name in array of strings.
	BOOL bValidated = FALSE;
	LPTSTR lpszSuite = lpszProductSuites;
	while (*lpszSuite) 
	{
		//Ensure the string is upper case
		_tcsupr( lpszSuite);

		//Does the suite match up with the current item?
		if (_tcsstr( lpszSuite, lpszLocalSuite)) 
		{
			bValidated = TRUE;
			break;
		}
		lpszSuite += (lstrlen( lpszSuite) + 1);
	}

	//Don't forget to free up the resource we used
	delete [] lpszLocalSuite;
	delete [] lpszProductSuites;
	RegCloseKey( hKey);
	return bValidated;
}

BOOL COSInfo::ValidateProductType( LPCTSTR lpszTypeToValidate) 
{
	// Open the ProductOptions key.
	HKEY	hKey = NULL;
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, NT_PRODUCT_OPTIONS, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
		return FALSE;

	const int MY_BUFSIZE = 100;
	TCHAR szProductType[MY_BUFSIZE];
	DWORD dwBufLen = MY_BUFSIZE * sizeof(TCHAR);

	if (RegQueryValueEx(hKey, _T( "ProductType"), NULL, NULL, (LPBYTE) szProductType, &dwBufLen) != ERROR_SUCCESS)
		return PLATFORM_NT_UNKNOWN;

	RegCloseKey(hKey);

	return (_tcsicmp( lpszTypeToValidate, szProductType) == 0);
}

LPCTSTR	COSInfo::getOSName()
{
	return m_szOSName;
}

LPCTSTR COSInfo::getOSVersion()
{
	return m_szOSVersion;
}

LPCTSTR COSInfo::getOSComment()
{
	return m_szOSComment;
}

BOOL COSInfo::isServer()
{
	return m_bIsServer;
}

BOOL COSInfo::isWinNT()
{
	return m_bIsWinNT;
}


LPCTSTR COSInfo::getDeviceDescription()
{
	if (m_bIsWinNT)
		return GetDeviceDescriptionNT();
	return GetDeviceDescription9X();
}

LPCTSTR COSInfo::GetDeviceDescription9X()
{
	HKEY hKey = NULL;

	_stprintf( m_szDeviceDescription, NOT_AVAILABLE);
	AddLog( _T( "Registry 9X/me GetDeviceDescription..."));
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, WIN_COMPUTER_DESCRIPTION, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"), WIN_COMPUTER_DESCRIPTION);
		return m_szDeviceDescription;
	}

	// Get description.
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	lResult = RegQueryValueEx( hKey, _T( "Comment"), NULL, &dwType, (LPBYTE) m_szDeviceDescription, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
	//	AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\Comment !\n"), WIN_COMPUTER_DESCRIPTION);
		RegCloseKey( hKey);
		return m_szDeviceDescription;
	}
	RegCloseKey( hKey);
	AddLog( _T( "OK.\n"));
	return m_szDeviceDescription;
}

LPCTSTR COSInfo::GetDeviceDescriptionNT()
{
	HINSTANCE	    hDll;
	LPBYTE	myBuffer;

	_stprintf( m_szDeviceDescription, NOT_AVAILABLE);
	// Windows NT/2000/XP	
	AddLog( _T( "NT netapi32 GetDeviceDescription..."));
	// Load the netapi 32 bit DLL
	if ((hDll = LoadLibrary( _T( "netapi32.dll"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.                                  
		AddLog( _T( "Failed to load <netapi32.dll> ! "));
		return m_szDeviceDescription;
	}
	// Load the NetServerGetInfo function
	if ((*(FARPROC*)&pfnNetServerGetInfoNT = GetProcAddress( hDll, _T( "NetServerGetInfo"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.                                  
		AddLog( _T( "Failed to load <NetServerGetInfo> function from netapi32.dll !\n"));
		FreeLibrary( hDll);
		return m_szDeviceDescription;
	}
	// Load the NetApiBufferFree function
	if ((*(FARPROC*)&pfnNetApiBufferFreeNT = GetProcAddress( hDll, _T( "NetApiBufferFree"))) == NULL)
	{
		// Tell the user that we could not find a usable netapi32 DLL.                                  
		AddLog( _T( "Failed to load <NetApiBufferFree> function from netapi32.dll !\n"));
		FreeLibrary( hDll);
		return m_szDeviceDescription;
	}
	if (pfnNetServerGetInfoNT( NULL, 101, &myBuffer) == NERR_Success)
	{
		_stprintf( m_szDeviceDescription, _T( "%S"), ((LPSERVER_INFO_101)myBuffer)->sv101_comment);
		AddLog( _T( "OK.\n"));
	}
	else
		AddLog( _T( "Failed in call to <NetServerGetInfo> function from netapi32.dll !\n"));
	pfnNetApiBufferFreeNT( myBuffer);
	FreeLibrary( hDll);
	return m_szDeviceDescription;
}

