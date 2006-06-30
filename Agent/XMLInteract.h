// Document modified at : Friday, March 31, 2006 2:36:07 PM , by user : didier , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pirerre LEMMET 2005
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// XMLInteract.h: interface for the CXMLInteract class.
//
// Storage class using CStdioFile class to load from and store
// informations to XML.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLINTERACT_H__02015424_D9B0_11D4_8F75_00600889DFA5__INCLUDED_)
#define AFX_XMLINTERACT_H__02015424_D9B0_11D4_8F75_00600889DFA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define SETTINGS_FILE		_T( "Config.csv")
#define REGISTRY_SETTINGS_FILE _T( "RegConfig.csv")
#define APPLICATIONS_FILE	_T( "Apps.csv")
#define ACCESS_FOLDER		_T( "Access\\")
#define BIOS_FOLDER			_T( "Bios\\")
#define CONTROLLERS_FOLDER	_T( "Controllers\\")
#define DRIVES_FOLDER		_T( "Drives\\")
#define HARDWARE_FOLDER		_T( "Hardware\\")
#define INPUTS_FOLDER		_T( "Inputs\\")
#define MEMORY_FOLDER		_T( "Memories\\")
#define MODEMS_FOLDER		_T( "Modems\\")
#define MONITORS_FOLDER		_T( "Monitors\\")
#define NETWORKS_FOLDER		_T( "Networks\\")
#define PORTS_FOLDER		_T( "Ports\\")
#define PRINTERS_FOLDER		_T( "Printers\\")
#define REGISTRY_FOLDER		_T( "Registry\\")
#define SLOTS_FOLDER		_T( "Slots\\")
#define SOFTWARES_FOLDER	_T( "Softwares\\")
#define SOUNDS_FOLDER		_T( "Sounds\\")
#define STORAGES_FOLDER		_T( "Storages\\")
#define VIDEOS_FOLDER		_T( "Videos\\")


class CXMLInteract : public CStoreInteract 
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CXMLInteract();
	CXMLInteract( LPCTSTR lpstrExecutionFolder);
	virtual ~CXMLInteract();

	//////////////////////////////////
	// Operations
	//////////////////////////////////
	CString m_csBiosInfoBuffer;
	// Open the XML connection and set the execution folder path
	// Return always TRUE
	BOOL OpenDB( LPCTSTR lpstrExecutionFolder);
	// Check if the XML connection is opened
	BOOL IsOpen();
	// Close the XML connection
	void CloseDB();
	// Display XML Error message
	static void DisplayXMLException( CException *pEx = NULL);
	// Get a string describing the last error
	LPCTSTR	GetErrorMessage( CException *pEx = NULL);	
	
	// Update device properties in XML files
	// return TRUE if all is good
	BOOL UpdateDevice( CDeviceProperties &pPC);
	// Update User Access Logs in the the DB
	// return TRUE if all is good
	BOOL AddAccessLog( CAccessLog *pAccessLog);
	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return a string describing the storage method (DB, XML,...)
	UINT GetStorageMethod();
	// Load all settings from the XML file
	BOOL GetSettings();
	// Get the last check date from the XML file
	COleDateTime GetLastCheckDate( LPCTSTR lpstrComputerName);
	// Retrieve values in the registry
	BOOL RetrieveRegistryValues( CDeviceProperties &pPC);

	BOOL ReadBIOS(LPCTSTR lpstrFilename, CDeviceProperties &pPC);
	BOOL GetBiosInfoXml(CDeviceProperties &pPC);
	BOOL parseProcessor( CDeviceProperties &pPC );
	BOOL parseMemorySlots( CDeviceProperties &pPC );
	BOOL parseSystemSlots( CDeviceProperties &pPC );
	BOOL launchBiosInfo( CDeviceProperties &pPC );
	BOOL ReadLastInventoryState( LPCTSTR lpstrFilename, COCSInventoryState &myState);
	BOOL WriteLastInventoryState( LPCTSTR lpstrFilename, COCSInventoryState &myState);

protected: // Methods

	// Write BIOS in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateBIOS( CDeviceProperties &pPC);
	// Write logical drives in the XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateDrives( CDeviceProperties &pPC);
	// Write input devices in the XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateInputDevices( CDeviceProperties &pPC);
	// Write hardware info in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateHardware( CDeviceProperties &pPC);
	// Write memory slots in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateMemorySlots( CDeviceProperties &pPC);
	// Write modems in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateModems( CDeviceProperties &pPC);
	// Write monitors in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateMonitors( CDeviceProperties &pPC);
	// Write network adapters in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateNetworks( CDeviceProperties & pPC);
	// Write printers in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdatePrinters( CDeviceProperties & pPC);
	// Write registry values in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateRegistryValues( CDeviceProperties & pPC);
	// Write system ports in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateSystemPorts( CDeviceProperties &pPC);
	// Write system slots in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateSystemSlots( CDeviceProperties &pPC);
	// Write softwares in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateSoftwares( CDeviceProperties &pPC);
	// Write sounds devices in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateSounds( CDeviceProperties & pPC);
	// Write storages peripherals in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateStorages( CDeviceProperties & pPC);
	// Write system controllers in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateSystemControllers( CDeviceProperties &pPC);
	// Write video adapters in XML file
	// Return TRUE if they are successfully updated
	BOOL UpdateVideos( CDeviceProperties & pPC);
	BOOL UpdateAccountInfo(CDeviceProperties &pPC);

protected: // Attributes
	CString m_csExecutionFolder;	// Execution folder
};

#endif // !defined(AFX_XMLINTERACT_H__02015424_D9B0_11D4_8F75_00600889DFA5__INCLUDED_)
