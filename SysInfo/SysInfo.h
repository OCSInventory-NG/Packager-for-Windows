// Document modified at : Wednesday, March 29, 2006 1:48:40 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SysInfo.h
//
//////////////////////////////////////////////////////////////////////

#ifndef SYSINFO_H_
#define SYSINFO_H_

#include "OcsWmi.h"
#include "SetupApi.h"
#include "SysInfoClasses.h"
#include "AccessLog.h"
#include "Bios.h"
#include "FileVersion.h"
#include "InputDevice.h"
#include "InputDeviceList.h"
#include "LogicalDrive.h"
#include "LogicalDriveList.h"
#include "Memory.h"
#include "MemorySlot.h"
#include "MemorySlotList.h"
#include "Monitor.h"
#include "MonitorList.h"
#include "Modem.h"
#include "ModemList.h"
#include "NetworkAdapter.h"
#include "NetworkAdapterList.h"
#include "Printer.h"
#include "PrinterList.h"
#include "RegistryValue.h"
#include "RegistryValueList.h"
#include "Software.h"
#include "SoftwareList.h"
#include "StoragePeripheral.h"
#include "StoragePeripheralList.h"
#include "SoundDevice.h"
#include "SoundDeviceList.h"
#include "SystemController.h"
#include "SystemControllerList.h"
#include "SystemPort.h"
#include "SystemPortList.h"
#include "SystemSlot.h"
#include "SystemSlotList.h"
#include "VideoAdapter.h"
#include "VideoAdapterList.h"
#include "WindowsSocket.h"
#include "DeviceComments.h"
#include "DeviceCommentsList.h"
#include "DeviceInventory.h"
#include "DeviceInventoryList.h"
#include "DeviceRepairs.h"
#include "DeviceRepairsList.h"
#include "DeviceProperties.h"
#include "Wmi.h"
#include "EDID.h"
#include "Registry.h"
#include "DebugLog.h"
#include "AccountInfo.h"
#include "OcsCrypto.h"
#include <tlhelp32.h>

class DLL_CLASS SysInfo
{
public: // Methods
	BOOL getWindowsProductKey(CString &productKey);
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	SysInfo();
	virtual ~SysInfo();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// OS information
	UINT getOS( CString &csName, CString &csVersion, CString &csComment, CString &csDescription);
	BOOL getDomainOrWorkgroup( CString &csDomain);
	BOOL getUserDomain( CString &csUserDomain);

	// Memory information
	BOOL getMemory( ULONG *m_ulPhysicalMemory, ULONG *m_ulSwapSize);

	// Hardware informations
	BOOL getBiosInfo( CBios *pMyBios);
	BOOL getInputDevices( CInputDeviceList *pList);
	LPCTSTR getLocalIP();
	BOOL getMemorySlots( CMemorySlotList *pMyList);
	BOOL getModems( CModemList *pMyList);
	BOOL getMonitors( CMonitorList *pMyList);
	BOOL getNetworkAdapters( CNetworkAdapterList *pMyList);
	BOOL getSystemPorts( CSystemPortList *pMyList);
	BOOL getPrinters( CPrinterList *pMyList);
	DWORD getProcessors( CString &csProcType, CString &csProcSpeed);
	BOOL getSoundDevices( CSoundDeviceList *pMyList);
	BOOL getStoragePeripherals( CStoragePeripheralList *pMyList);
	BOOL getSystemControllers( CSystemControllerList *pMyList);
	BOOL getSystemSlots( CSystemSlotList *pMyList);
	BOOL getVideoAdapters( CVideoAdapterList *pMyList);
	BOOL getWindowsRegistration( CString &csCompany, CString &csOwner, CString &csProductID);
	BOOL isNotebook();

	// User informations
	BOOL getUserName( CString &csUserName);

	// Software informations
	BOOL getRegistryApplications( CSoftwareList *pList, BOOL hkcu);

	// Registry informations
	BOOL getRegistryValue( UINT uKeyTree, LPCTSTR lpstrSubKey, LPCTSTR lpstrValue, CString &csResult);
	BOOL getRegistryMultipleValues(LPCTSTR lpstrDeviceID, LPCTSTR lpstrName, UINT uKeyTree, LPCTSTR lpstrSubKey, CRegistryValueList *pMyList);

	// Device ID
	LPCTSTR getDeviceID();
	BOOL setDeviceID( LPCTSTR lpstrDeviceID);
	CWmi		m_wmiInfo;		// Class to get informations from WMI
protected: // Methods
	BOOL setFileDeviceID( LPCTSTR lpstrDeviceID);
	LPCTSTR getFileDeviceID();

protected: // Attributes
	SYSTEM_INFO m_SystemInfo;	// System informations
	CRegistry	m_registryInfo;	// Class to get informations from registry
	CWindowsSocket	m_Sock;		// Class to get informations from Windows Sockets
	CEdid		m_edidInfo;		// Class to get information for EDID enabled display
};

inline BOOL getFileVersion( LPCTSTR lpstrFile, CString &csPublisher, CString &csName, CString &csVersion, CString &csComment)
{
	CFileVersion myFileVersion;

	try
	{
		if (!myFileVersion.Open( lpstrFile))
		{
			csPublisher = NOT_AVAILABLE;
			csName = NOT_AVAILABLE;
			csVersion = NOT_AVAILABLE;
			csComment = NOT_AVAILABLE;
			return FALSE;
		}
		csPublisher = myFileVersion.GetCompanyName();
		csPublisher.Replace( _T( "\r"), _T( " "));
		csName = myFileVersion.GetProductName();
		csName.Replace( _T( "\r"), _T( " "));
		if (csName.IsEmpty())
			csName = myFileVersion.GetInternalName();
		csVersion = myFileVersion.GetFileVersion();
		csVersion.Replace( _T( "\r"), _T( " "));
		csComment = myFileVersion.GetFileDescription();
		csComment.Replace( _T( "\r"), _T( " "));
		myFileVersion.Close();
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		csPublisher = NOT_AVAILABLE;
		csName = NOT_AVAILABLE;
		csVersion = NOT_AVAILABLE;
		csComment = NOT_AVAILABLE;
		return FALSE;
	}
	return TRUE;
}

#endif