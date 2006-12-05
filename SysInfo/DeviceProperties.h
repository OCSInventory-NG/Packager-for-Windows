// Document modified at : Friday, March 31, 2006 12:45:33 PM , by user : didier , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// DeviceProperties.h: interface for the CDeviceProperties class.
//
// Class storing informations about Hardware and OS of a device
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICEPROPERTIES_H__02015421_D9B0_11D4_8F75_00600889DFA5__INCLUDED_)
#define AFX_DEVICEPROPERTIES_H__02015421_D9B0_11D4_8F75_00600889DFA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"
class SysInfo;

#define		WINDOWS_WORKSTATION	0	// Windows workstation device type
#define		WINDOWS_SERVER		1	// Windows server device type
#define     WINDOWS_NOTEBOOK	2	// Windows notebook or laptop device type
#define		NOVELL_SERVER		3	// Novell Netware server device type
#define		MAC_WORKSTATION		4	// Apple MacOS workstation device type
#define		MAC_SERVER			5	// Apple MacOS server device type
#define		MAC_NOTEBOOK		6	// Apple MacOS notebook or laptop device type
#define		UNIX_WORKSTATION	7	// Unix workstation device type
#define		UNIX_SERVER			8	// Unix server device type
#define		UNIX_NOTEBOOK		9	// Unix notebook or laptop device type
#define		HANDHELD_DEVICE		10	// HandHeld device like Palm or Pocket PC
#define		NETWORK_PRINTER		11	// Network printer device type
#define		NETWORK_HUB			12	// Hub device type
#define		NETWORK_SWITCH		13	// Switch device type
#define		NETWORK_ROUTER		14	// Router device type
#define		IP_PHONE			15	// IP phone device type
#define		IP_PABX				16	// IP PABX device type
#define		USER_WORKGROUP		17	// User workgroup device type
#define		UNKNOWN_DEVICE		18	// Unknown device type
#define		NEW_DEVICE			65535 // Constant for adding new device
#define		CURRENT_DEVICE		65534 // Constant for retrieving the device type of the current device

class DLL_CLASS CDeviceProperties  
{
// Methods
public:
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CDeviceProperties();
	virtual ~CDeviceProperties();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	// Return a string with the operating system name
	LPCTSTR GetOSName();
	// Return a string with the operating system version
	LPCTSTR GetOSVersion();
	// Return a string with the operating system comments
	LPCTSTR GetOSComment();
	// Return a string with the processor type
	LPCTSTR GetProcessorType();
	// Return a string with the processor speed
	LPCTSTR GetProcessorSpeed();
	// Return the number of processors
	DWORD GetNumberOfProcessors();
	// Return the physical memory size in mega bytes
	ULONG GetPhysicalMemory();
	// Return the paging file size in mega bytes
	ULONG GetPageFileSize();
	// Return a string with the network primary IP address
	LPCTSTR GetIPAddress();
	// Return a string with the last check date
	LPCTSTR GetLastCheckDate();
	// Return a string with the execution duration
	LPCTSTR GetExecutionDuration();
	// Return a string with the logged on user when device has been checked
	LPCTSTR GetLoggedOnUser();
	// Return a string with the device description extracted from OS
	LPCTSTR GetDescription();
	// Return the NT domain name or workgroup
	LPCTSTR GetDomainOrWorkgroup();
	// return the NT user domain 
	LPCTSTR GetUserDomain();
	// Return the device type
	UINT	GetDeviceType();
	// Return Windows registered company
	LPCTSTR GetWindowsRegisteredCompany();
	// Return Windows registered owner
	LPCTSTR GetWindowsRegisteredOwner();
	// Return Windows product ID
	LPCTSTR GetWindowsProductID();
	// Return Windows product key
	LPCTSTR GetWindowsProductKey();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX );
	// Get hash code of data, to determine if changed since last inventory
	LPCTSTR GetHash();
	// Get current checksum
	ULONG GetChecksum();

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	// Set the operating system informations
	void SetOS( LPCTSTR lpstrName, LPCTSTR lpstrVersion, LPCTSTR lpstrComment);
	// Set the processors informations
	void SetProcessor( LPCTSTR lpstrName, LPCTSTR lpstrSpeed, DWORD dwNumber);
	// Set the physical and paging file size in mega bytes
	void SetMemory( ULONG ulPhysical, ULONG ulPageFile);
	// Set the IP Address
	void SetIPAddress( LPCTSTR lpstrIP);
	// Set the last check date
	void SetLastCheckDate( LPCTSTR lpstrDate);
	// Compute and store the execution duration
	void SetExecutionDuration( CTime &cBeginTime, CTime &cEndTime);
	// Set the execution duration from string
	void SetExecutionDuration( LPCTSTR lpstrDuration);
	// Set the last check date
	void SetLoggedOnUser( LPCTSTR lpstrUser);
	// Set the device type
	void SetDeviceType( UINT uType);
	// Set the device description extracted from OS
	void SetDescription( LPCTSTR lpstrDescription);
	// Set the NT Domain name or workgroup
	void SetDomainOrWorkgroup( LPCTSTR lpstrDomain);
	// Set the NT User Domain
	void SetUserDomain( LPCTSTR lpstrUserDomain);
	// Set informations about Windows registration
	void SetWindowsRegistration( LPCTSTR lpstrCompany, LPCTSTR lpstrOwner, LPCTSTR lpstrProductID);
	// Set informations about Windows key
	void SetWindowsProductKey( LPCTSTR lpstrProductKey);
	// Retrieve and set the attributes values from the device
	// Set bRenewUID to TRUE to force generating a new Device ID
	// Otherwise, a Device ID will be generated only if this is
	// the first the Device is inventoried
	BOOL RetrieveHardwareAndOS(SysInfo * myPC, LPCSTR cmdL);
	// Generate a unique device ID
	void GenerateUID();
	// Set checksum
	void SetChecksum( ULONG ulchecksum);

	//////////////////////////////////
	// Public Attributes
	//////////////////////////////////

	// BIOS informations
	CBios		 m_BIOS;
	// List of Comments extra infos
	CDeviceCommentsList m_CommentList;
	// List of Input devices infos
	CInputDeviceList m_InputList;
	// List of Physical inventory and waranties infos
	CDeviceInventoryList m_InventoryList;
	// List of Device repairs infos
	CDeviceRepairsList m_RepairList;
	// List of Logical Drives (Volum name, File system, Total size, Free space...)
	CLogicalDriveList m_DriveList;
	// List of Memory slots
	CMemorySlotList m_MemoryList;
	// List of Modems
	CModemList m_ModemList;
	// List of Monitors
	CMonitorList m_MonitorList;
	// List of Network adapters
	CNetworkAdapterList m_NetworkList;
	// List of Printers
	CPrinterList m_PrinterList;
	// List of Device registry values infos
	CRegistryValueList m_RegistryList;
	// List of Software
	CSoftwareList m_SoftwareList;
	// List of Sound Devices
	CSoundDeviceList m_SoundList;
	// List of Storage devices (Floppy disk, IDE Disk, SCSI Disk, CD-Rom...)
	CStoragePeripheralList m_StorageList;
	// List of System Controlers (Floppy, IDE, SCSI, USB, IEEE1394, PCMCIA, SATA)
	CSystemControllerList m_SystemControllerList;
	// List of System Slots (PCI, AGP...)
	CSystemSlotList m_SlotList;
	// List of ports
	CSystemPortList m_PortList;
	// List of Video adapters
	CVideoAdapterList m_VideoList;

protected: // Attributes
	CString	m_csDeviceID;		// Device unique ID
	CString	m_csDeviceName;		// Device netbios or DNS name
	CString	m_csOSName;			// OS Name of the device (ex "Windows NT")
	CString	m_csOSVersion;		// OS Version of the device (ex "4.0 Build 1381")
	CString	m_csOSComment;		// OS Comment of the device (ex "Service Pack 6")
	CString	m_csProcessorType;	// First Processor type of the device (ex "Intel Pentium II Model 1280 Stepping 2")
	CString	m_csProcessorSpeed; // Processor speed
	DWORD	m_dwNumberOfProcessor; // Number of processor of the device
	ULONG	m_ulPhysicalMemory;	// Physical memory of the device
	ULONG	m_ulSwapSize;		// Swap Size of the device
	CString	m_csIPAddress;		// IP Address of the device if available (ex "192.3.4.1" or "Unavailable")
	CString	m_csLastCheckDate;	// Last check date when reading from CSV
	CString	m_csExecutionDuration; // Excution duration in string format
	CString	m_csLoggedOnUser;	// Logged on username when device have been checked
	CString	m_csDescription;	// Description extracted from OS
	UINT	m_uType;			// Network device type
	CString	m_csDomain;			// NT Domain name or workgroup
	CString	m_csUserDomain		;// NT user Domain name 
	CString	m_csWinRegCompany;	// Windows registered company
	CString	m_csWinRegOwner;	// Windows registered owner
	CString m_csWinRegProductID;// Windows product ID
	CString m_csWinProductKey;	// Windows product key
	ULONG	m_ulChecksum;		// Checksum for detecting changes
};
#endif // !defined(AFX_DEVICEPROPERTIES_H__02015421_D9B0_11D4_8F75_00600889DFA5__INCLUDED_)

