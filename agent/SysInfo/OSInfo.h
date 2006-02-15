// Document modified at : Saturday, November 15, 2003 9:39:28 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// OSInfo.h
//
//////////////////////////////////////////////////////////////////////

#ifndef _OSINFO_HEADER_
#define _OSINFO_HEADER_

#include "SysInfoClasses.h"


class DLL_CLASS COSInfo
{
public:        // object creation/destruction
   COSInfo();
   COSInfo( const COSInfo& source);
   COSInfo& operator=( const COSInfo& right);
   virtual ~COSInfo();

public:        // attribute manipulation
	LPCTSTR	getOSName();
	LPCTSTR getOSVersion();
	LPCTSTR getOSComment();
	BOOL isServer();
	BOOL isWinNT();
	LPCTSTR getDeviceDescription();

protected:     // protected members
    virtual void assign( const COSInfo& source);
    virtual void determineOSInfo();
	UINT WhichNTProduct( OSVERSIONINFOEX *posvi);
	UINT WhichNTProductRegistry();
	UINT WhichNTRole();
	UINT WhichNTRoleRegistry();
	BOOL IsDataCenterServer();
	BOOL IsEnterpriseServer();
	BOOL IsTerminalServer();
	BOOL IsHomeEdition();
	BOOL IsProfessional();
	BOOL IsStandAloneServer();
	BOOL IsPDC();
	BOOL IsBDC();
	BOOL ValidateProductSuite(LPCTSTR lpszSuiteToValidate); 
	BOOL ValidateProductType(LPCTSTR lpszTypeToValidate); 
	LPCTSTR GetDeviceDescription9X();
	LPCTSTR GetDeviceDescriptionNT();

protected:     // attributes
	// NT platform Enumeration
	enum PLATFORM_NT {
		PLATFORM_NT_UNKNOWN = 0,
		PLATFORM_NT_PERSONAL,					// Home Edition
		PLATFORM_NT_WORKSTATION,				// Workstation/Professional
		PLATFORM_NT_SERVER,						// NT/2000/.NET standard server
		PLATFORM_NT_TERMINAL_SERVER,			// NT Terminal Server Edtion
		PLATFORM_NT_ENTERPRISE_SERVER,			// NT Enterprise server/2000 Advanced server/.NET Enterprise server
												//    (clustering support)
		PLATFORM_NT_DATACENTER_SERVER			// 2000/.NET DataCenter
	};

	enum ROLE_NT {
		ROLE_NT_UNKNOWN = 0,
		ROLE_NT_STAND_ALONE_SERVER,			// Stand alone server
		ROLE_NT_PRIMARY_DOMAIN_CONTROLLER,	// Primary domain controler
		ROLE_NT_BACKUP_DOMAIN_CONTROLLER	// Backup domain controler
	};

	TCHAR m_szOSName[256];
	TCHAR m_szOSVersion[256];
	TCHAR m_szOSComment[256];
	TCHAR m_szDeviceDescription[256];
	BOOL  m_bIsServer;
	BOOL  m_bIsWinNT;
};

#endif