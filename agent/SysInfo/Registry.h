// Document modified at : Thursday, May 06, 2004 1:59:38 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Registry.h: interface for the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGISTRY_H__599ACCD2_83FA_4ED3_9006_8C315E043D08__INCLUDED_)
#define AFX_REGISTRY_H__599ACCD2_83FA_4ED3_9006_8C315E043D08__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"
#include "..\defines.h"

class DLL_CLASS CRegistry  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CRegistry();
	virtual ~CRegistry();

	//////////////////////////////////
	// Connection methods
	//////////////////////////////////

	BOOL Connect( LPCTSTR lpstrDevice = NULL);
	BOOL Disconnect();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	BOOL GetBiosInfo( CBios *pMyBios);
	LPCTSTR GetDeviceDescription();
	LPCTSTR GetDeviceID();
	BOOL GetDomainOrWorkgroup( CString &csDomain);
	BOOL GetInputDevices( CInputDeviceList *pList);
	BOOL GetLoggedOnUser( CString &csUser);
	BOOL GetModems( CModemList *pMyList);
	BOOL GetMonitors( CMonitorList *pMyList);
	BOOL GetSystemPorts( CSystemPortList *pMyList);
	BOOL GetPrinters( CPrinterList *pMyList);
	DWORD GetProcessors( CString &csProcType, CString &csProcSpeed);
	BOOL GetRegistryApplications( CSoftwareList *pList, BOOL hkcu);
	BOOL GetSoundDevices( CSoundDeviceList *pMyList);
	BOOL GetStoragePeripherals( CStoragePeripheralList *pMyList);
	BOOL GetSystemControllers( CSystemControllerList *pMyList);
	BOOL GetVideoAdapters( CVideoAdapterList *pMyList);
	BOOL GetWindowsRegistration( CString &csCompany, CString &csOwner, CString &csProductID);
	BOOL IsNotebook();

	BOOL GetRegistryValue( UINT uKeyTree, LPCTSTR lpstrSubKey, LPCTSTR lpstrValue, CString &csResult);
	BOOL GetRegistryMultipleValues( LPCTSTR lpstrDeviceID, LPCTSTR lpstrName, UINT uKeyTree, LPCTSTR lpstrSubKey, CRegistryValueList *pMyList);

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////
	BOOL SetDeviceID( LPCTSTR lpstrDeviceID);

protected: // Methods
	BOOL GetBiosInfo9X( CBios *pMyBios);
	BOOL GetBiosInfoNT( CBios *pMyBios);
	LPCTSTR GetDeviceDescription9X();
	LPCTSTR GetDeviceDescriptionNT();
	BOOL GetDomainOrWorkgroup9X( CString &csDomain);
	BOOL GetDomainOrWorkgroupNT( CString &csDomain);
	BOOL GetInputDevices9X( CInputDeviceList *pList);
	BOOL GetInputDevicesNT( CInputDeviceList *pList);
	BOOL GetLoggedOnUser9X( CString &csUser);
	BOOL GetLoggedOnUserNT( CString &csUser);
	BOOL GetModems9X( CModemList *pMyList);
	BOOL GetModemsNT( CModemList *pMyList);
	BOOL GetMonitors9X( CMonitorList *pList);
	BOOL GetMonitorsNT( CMonitorList *pList);
	BOOL GetSystemPorts9X( CSystemPortList *pMyList);
	BOOL GetSystemPortsNT( CSystemPortList *pMyList);
	DWORD GetProcessors9X( CString &csProcType, CString &csProcSpeed);
	DWORD GetProcessorsNT( CString &csProcType, CString &csProcSpeed);
	BOOL GetRegistryApplications9X( CSoftwareList *pList, HKEY__* curHive);
	BOOL GetRegistryApplicationsNT( CSoftwareList *pList, HKEY__* curHive);
	BOOL GetSoundDevices9X( CSoundDeviceList *pList);
	BOOL GetSoundDevicesNT( CSoundDeviceList *pList);
	BOOL GetStoragePeripherals9X( CStoragePeripheralList *pMyList);
	BOOL GetStoragePeripheralsNT( CStoragePeripheralList *pMyList);
	BOOL GetSystemControllers9X( CSystemControllerList *pMyList);
	BOOL GetSystemControllersNT( CSystemControllerList *pMyList);
	BOOL GetVideoAdapters9X( CVideoAdapterList *pMyList);
	BOOL GetVideoAdaptersNT_2K( CVideoAdapterList *pMyList);
	BOOL GetVideoAdaptersXP( CVideoAdapterList *pMyList);
	BOOL GetWindowsRegistration9X( CString &csCompany, CString &csOwner, CString &csProductID);
	BOOL GetWindowsRegistrationNT( CString &csCompany, CString &csOwner, CString &csProductID);
	BOOL IsNotebook9X();
	BOOL IsNotebookNT();
	// Get screen resolution
	BOOL GetScreenResolution( CString &csResolution);
	// Parse multi string registry value
	LPCTSTR ParseMultiSZ( LPCTSTR lpstrCurrent = NULL);
	// Find status of a device component under HKRY_DYN_DATA\Config Manager\Enum
	BOOL ValidateComponent9X( LPCTSTR lpstrComponentKey);

protected: // Attributes
	BOOL m_bRemoteRegistry;	// TRUE if connecting to a remote computer
	HKEY m_hKey;			// Handle to HKLM key on computer
	DWORD m_dwPlatformId;	// OS Platform ID to determine if Win9X or NT
	BOOL  m_bIsXP;			// TRUE if Win XP or higher
};

#endif // !defined(AFX_REGISTRY_H__599ACCD2_83FA_4ED3_9006_8C315E043D08__INCLUDED_)
