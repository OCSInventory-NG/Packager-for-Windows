// Document modified at : Wednesday, March 29, 2006 4:35:38 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// StoreInteract.h: interface for the CStoreInteract class.
//
// Generic storage class. Real storage class as Dao, CSV or ODBC
// will inherit of this class
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STOREINTERACT_H__7CAE8F55_10A1_11D5_8E72_0040055338AF__INCLUDED_)
#define AFX_STOREINTERACT_H__7CAE8F55_10A1_11D5_8E72_0040055338AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Name of settings
#define DISPLAY_ERROR_OPTION	_T( "Error")		// Whether or not display error on client computer
#define VISIBLE_OPTION			_T( "Visible")		// Whether or not agent is visible on client computer
#define FREQUENCY_OPTION		_T( "Frequency")	// Check frequency
#define LOG_ACCESS_OPTION		_T( "LogAccess")	// Whether or not store everyone using client computers
#define PROCESSES_OPTION		_T( "Processes")	// Whether or not check for some running processes on client computer
#define SEARCH_DISKS_OPTION		_T( "SearchDisks")	// Whether or not scan drives for apps
#define EXCLUDE_FOLDER_OPTION	_T( "ExcludeFolder") // Whether or not exclude folder from search
#define AUTO_IMPORT_OPTION		_T( "AutoImport")	// Wether or not manager have to import CSV inventory results at startup
#define COMPANY_OPTION			_T( "Company")		// Name of the company using OCS Inventory for buitin reports
#define AUTO_WORKGROUP_MAP_OPTION _T( "AutoWorkgroupMap") // Whether or not automatically network map view based on domains or workgroups
#define AUTO_DICTIONARY_SYNCH_OPTION _T( "AutoDictionarySynch") // Whether or not automatically update detected softwares from dictionary

class CStoreInteract
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CStoreInteract();
	virtual ~CStoreInteract();

	//////////////////////////////////
	// Operations
	//////////////////////////////////

	// Open the connection to the storing object
	// Return TRUE if successfully opened
	// FALSE if error
	virtual BOOL OpenDB( LPCTSTR lpstrExecutionFolder);
	// Check if the storing connection is opened
	virtual BOOL IsOpen();
	// Close the storing connection
	virtual void CloseDB();
	// Display Error message
	static void DisplayException( CException *pEx);
	// Get a string describing the last error
	virtual LPCTSTR	GetErrorMessage( CException *pEx = NULL);	

	// Update device properties in the the storing connection
	// return TRUE if all is good
	virtual BOOL UpdateDevice( CDeviceProperties &pPC);
	// Update User Access Logs in the the storing connection
	// return TRUE if all is good
	virtual BOOL AddAccessLog( CAccessLog *pAccessLog);


	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return a string describing the storage method (DAO, CSV,...)
	virtual UINT GetStorageMethod();
	// Get Frequency from the storing connection
	LONG GetFrequency();
	// Get Visible option value
	BOOL GetDisplayVisible();
	// Get Error option value
	BOOL GetDisplayError();
	// Get Log Access option value
	BOOL GetLogAccess();
	// Get Check Process option value
	BOOL GetProcess();
	// Get Process filenames option value
	LPCTSTR GetProcessFilenames();
	// Get Auto Workgroup Map option value
	BOOL GetAutoWorkgroupMap();
	// Load all settings from the storing connection
	virtual BOOL GetSettings();
	// Get the last check date from the storing connection
	virtual COleDateTime GetLastCheckDate( LPCTSTR lpstrComputerName);
	// Get all apps to search for from the storing connection
	BOOL IsExtensionToSearch( LPCTSTR lpstrFilename);
	BOOL IsExcludeFolder( LPCTSTR lpstrFolder);
	// Retrieve values in the registry
	virtual BOOL RetrieveRegistryValues( CDeviceProperties &pPC);

	void SetCmdL(LPCSTR cmdL); 
	virtual BOOL ReadLastInventoryState( LPCTSTR lpstrFilename, COCSInventoryState &myState);
	virtual BOOL WriteLastInventoryState( LPCTSTR lpstrFilename, COCSInventoryState &myState);
	virtual	BOOL NotifyInventoryState( LPCTSTR lpstrFilename, COCSInventoryState &myState);

public: // Enums
	BOOL IsSearchDiskEnabled();
	enum StorageType
	{
		UNKNOWN_STORAGE = 0,
		DB_STORAGE,
		XML_STORAGE
	};

protected: // Attributes
	BOOL			m_bSearchFiles;		// Whether or not searching files on disks
	CString			m_csProcesses;		// Filenames of processes to check
	BOOL			m_bProcess;			// Whether or not check for running processes
	BOOL			m_bLogAccess;		// Whether or not store user connecting
	BOOL			m_bDisplayStatus;	// Whether or not display Status Information to user on the client computer
	BOOL			m_bDisplayError;	// Whether or not display errors
	BOOL			m_bAutoWorkgroupMap;// Whether or not automatically build network map view based on domains or workgroups
	LONG			m_lFrequency;		// Delay between 2 checks
	CString			m_csExtensionToSearch; // File extension to search for when searching unknown apps
	CString			m_csExcludeFolder;	// Folders to not scan
	CString			m_csCmdL;
};

#endif // !defined(AFX_STOREINTERACT_H__7CAE8F55_10A1_11D5_8E72_0040055338AF__INCLUDED_)
