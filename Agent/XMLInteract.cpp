// Document modified at : Friday, March 31, 2006 3:43:44 PM , by user : didier , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// MODIFIED BY PIERRE LEMMET
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// XMLInteract.cpp: implementation of the CXMLInteract class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Resource.h"
#include "SysInfo.h"
#include "OCSInventoryState.h"
#include "StoreInteract.h"
#include "XMLInteract.h"
#include "OCSInventory.h"
#include "../include/_common/utils.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXMLInteract::CXMLInteract()
	:CStoreInteract()
{
}

CXMLInteract::CXMLInteract( LPCTSTR lpstrExecutionFolder)
	:CStoreInteract()
{
	m_csExecutionFolder = lpstrExecutionFolder;
}

CXMLInteract::~CXMLInteract()
{
	m_csExecutionFolder.Empty();
}

BOOL CXMLInteract::OpenDB(LPCTSTR lpstrExecutionFolder)
{
	m_csExecutionFolder = lpstrExecutionFolder;
	return TRUE;
}

BOOL CXMLInteract::IsOpen()
{
	return TRUE;
}

void CXMLInteract::CloseDB()
{
}

UINT CXMLInteract::GetStorageMethod()
{
	return XML_STORAGE;
}

LPCTSTR CXMLInteract::GetErrorMessage( CException *pEx)
{
	CFileException *pFileEx;
	static CString strMsg;
	TCHAR   szErr[256];
	CString strDetail, strErrorOS;

	if (pEx == NULL)
	{
		strMsg = _T( "An unspecified error occurred");
		return strMsg;
	}
	if (!pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
	{
		if (!pEx->GetErrorMessage( szErr, 256))
			sprintf( szErr, _T( "An unspecified error occurred"));
		strMsg.FormatMessage( IDS_ERROR_UNKNOWN_EXCEPTION, szErr);
		return strMsg;
	}
	pFileEx = (CFileException *)pEx;
	switch (pFileEx->m_cause)
	{
	case CFileException::none:
		strDetail = _T( "No error");
		break;
	case CFileException::fileNotFound:
		strDetail = _T( "The file could not be located");
		break;
	case CFileException::badPath:
		strDetail = _T( "All or part of the path is invalid");
		break;
	case CFileException::tooManyOpenFiles:
		strDetail = _T( "The permitted number of open files was exceeded");
		break;
	case CFileException::accessDenied:
		strDetail = _T( "The file could not be accessed");
		break;
	case CFileException::invalidFile:
		strDetail = _T( "There was an attempt to use an invalid file handle");
		break;
	case CFileException::removeCurrentDir:
		strDetail = _T( "The current working directory cannot be removed");
		break;
	case CFileException::directoryFull:
		strDetail = _T( "There are no more directory entries");
		break;
	case CFileException::badSeek:
		strDetail = _T( "There was an error trying to set the file pointer");
		break;
	case CFileException::hardIO:
		strDetail = _T( "There was a hardware error");
		break;
	case CFileException::sharingViolation:
		strDetail = _T( "There was a sharing violation");
		break;
	case CFileException::lockViolation:
		strDetail = _T( "There was an attempt to lock a region that was already locked");
		break;
	case CFileException::diskFull:
		strDetail = _T( "The disk is full");
		break;
	case CFileException::endOfFile:
		strDetail = _T( "The end of file was reached");
		break;
	case CFileException::generic:
	default:
		strDetail = _T( "An unspecified error occurred");
		break;
	}
	strErrorOS.Format( _T( "%ld"), pFileEx->m_lOsError);
	strMsg.FormatMessage( IDS_ERROR_XML_EXCEPTION, pFileEx->m_strFileName, strDetail, strErrorOS);
	return strMsg;
}

void CXMLInteract::DisplayXMLException( CException *pEx)
{
	CXMLInteract myStore;
	//AfxMessageBox( myStore.GetErrorMessage( pEx), MB_ICONSTOP);
}

BOOL CXMLInteract::GetSettings()
{
/*	CStdioFile	cFile;
	CString		csBuffer,
				csTemp,
				csName,
				csTextValue;
	int			nValue,
				nPos;

	try
	{
		AddLog( _T( "XML Load OCS Inventory Settings...\n"));
		// Open the settings file
		csTemp.Format( _T( "%s%s"), m_csExecutionFolder, SETTINGS_FILE);
		if (!cFile.Open( csTemp, CFile::modeRead|CFile::shareDenyWrite|CFile::typeText))
		{
			AddLog( _T( "XML Load Settings: Failed because unable to open file <%s> ! Using default values.\n"),
					csTemp);
			return FALSE;
		}
		// Read all the settings
		while (cFile.ReadString( csBuffer))
		{
			// Get the setting name
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csName = csBuffer.Left(nPos);
			csTemp = csBuffer.Mid(nPos + 1);
			csBuffer = csTemp;
			// Get the setting integer value
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csTemp = csBuffer.Left(nPos);
			nValue = _ttoi( csTemp);
			// Get the setting text value
			csTemp = csBuffer.Mid( nPos +1);
			if ((nPos = csTemp.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csTemp);
				continue;
			}
			csTextValue = csTemp.Left(nPos);
			// Load the check frequency
			if (csName.CompareNoCase( FREQUENCY_OPTION) == 0)
				m_lFrequency = nValue;
			// Check if we have to be visible on the client computer
			if (csName.CompareNoCase( VISIBLE_OPTION) == 0)
				m_bDisplayStatus = (nValue != 0);
			// Check if we have to display error on the client computer
			if (csName.CompareNoCase( DISPLAY_ERROR_OPTION) == 0)
				m_bDisplayError = (nValue != 0);
			// Check if we have to store everyone using the client computer
			if (csName.CompareNoCase( LOG_ACCESS_OPTION) == 0)
				m_bLogAccess = (nValue != 0);
			// Check if we have to automatically build network map view based on domains or workgroups
			if (csName.CompareNoCase( AUTO_WORKGROUP_MAP_OPTION) == 0)
				m_bAutoWorkgroupMap = (nValue != 0);
			// Check if we have to search for some running processes on the client computer
			if (csName.CompareNoCase( PROCESSES_OPTION) == 0)
			{
				m_bProcess = (nValue != 0);
				m_csProcesses = csTextValue;
			}
			// Check if we have to search for unknown apps on the client computer
			if (csName.CompareNoCase( SEARCH_DISKS_OPTION) == 0)
			{
				if (nValue != 0)
				{
					m_bSearchFiles = TRUE;
					m_csExtensionToSearch = csTextValue;
					m_csExtensionToSearch.MakeLower();
				}
				else
				{
					m_bSearchFiles = FALSE;
					m_csExtensionToSearch.Empty();
				}
			}
			// Check if we have to exclude some folders from search on the client computer
			if (csName.CompareNoCase( EXCLUDE_FOLDER_OPTION) == 0)
			{
				if (nValue != 0)
				{
					m_csExcludeFolder = csTextValue;
					m_csExcludeFolder.MakeLower();
				}
				else
					m_csExcludeFolder.Empty();
			}
		}
		// Close the setting file
		cFile.Close();
		AddLog( _T( "XML Load Settings: OK.\n"));
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "XML Load Settings: Failed because XML Exception <%s> ! Using default values.\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "XML Load Settings: Failed because Unknown Exception ! Using default values.\n"));
		pEx->Delete();
		cFile.Abort();
		return FALSE;
	}
*/	return TRUE;
}

COleDateTime CXMLInteract::GetLastCheckDate(LPCTSTR lpstrDeviceName)
{
	CString			csBuffer,
					csItem,
					csDate;
	int				nPos;
	CStdioFile		cFile;
	COleDateTime	cOleLastCheck;
	UINT			uField = 0;

	try
	{
		AddLog( _T( "\tXML Load Device Last Inventory Date..."));
		// By default, no previous file => set the last date at 1/1/1900
		cOleLastCheck.SetDate( 1970, 1, 1);
		// Try opnening file
		csBuffer.Format( _T( "%s%s.zip"), m_csExecutionFolder, lpstrDeviceName);
		if (cFile.Open( csBuffer, CFile::modeRead|CFile::shareDenyWrite|CFile::typeText))
		{
			// Read file content
			cFile.ReadString( csBuffer);
			// The last check date is the 12 field
			while (((nPos = csBuffer.Find(_T( ";"))) != -1) && (uField < 12))
			{
				csDate = csBuffer.Left(nPos);
				csItem = csBuffer.Mid(nPos + 1);
				csBuffer = csItem;
				uField ++;
			}
			cOleLastCheck.ParseDateTime( csDate, VAR_DATEVALUEONLY);
			cFile.Close();
			if (cOleLastCheck.GetStatus() != COleDateTime::valid)
			{
				// Null or invalid value => set the last date at 1970-1-1
				cOleLastCheck.SetDate( 1970, 1, 1);
				AddLog( _T( "Failed because bad date format ! Using 1970-01-01 as Last Inventory Date.\n"));
			}
			else
				AddLog( _T( "OK.\n"));
		}
		else
			AddLog( _T( "\n\nFailed because ZIP file <%s> does not exist ! Using 1970-01-01 as Last Inventory Date.\n\n"),
					csBuffer);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "Failed because XML Exception <%s> ! Using 1970-01-01 as Last Inventory Date.\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "Failed because Unknown Exception ! Using 1970-01-01 as Last Inventory Date.\n"));
		pEx->Delete();
		cFile.Abort();
		return cOleLastCheck;
	}
	return cOleLastCheck;
}

BOOL CXMLInteract::UpdateDevice(CDeviceProperties &pPC)
{
	BOOL		bSuccess;
	m_csBiosInfoBuffer="";
	AddLog( _T( "XML Update Device properties...\n"));
	// Update Memory slots file
	bSuccess = UpdateMemorySlots( pPC);
	// Update Hardware file 
	bSuccess = bSuccess && UpdateHardware( pPC);
	// Update BIOS file
	bSuccess = bSuccess && UpdateBIOS( pPC);
	// Update Logical Drives file
	bSuccess = bSuccess && UpdateDrives( pPC);
	// Update Input Devices file
	bSuccess = bSuccess && UpdateInputDevices( pPC);
	// Update Modems file
	bSuccess = bSuccess && UpdateModems( pPC);
	// Update Monitors file
	bSuccess = bSuccess && UpdateMonitors( pPC);
	// Update Networks file
	bSuccess = bSuccess && UpdateNetworks( pPC);
	// Update System Ports file
	bSuccess = bSuccess && UpdateSystemPorts( pPC);
	// Update Printers file
	bSuccess = bSuccess && UpdatePrinters( pPC);
	// Update Registry Values file
	bSuccess = bSuccess && UpdateRegistryValues( pPC);
	// Update Softwares file
	bSuccess = bSuccess && UpdateSoftwares( pPC);
	// Update Sounds file
	bSuccess = bSuccess && UpdateSounds( pPC);
	// Update Storages file
	bSuccess = bSuccess && UpdateStorages( pPC);
	// Update System Controllers file
	bSuccess = bSuccess && UpdateSystemControllers( pPC);
	// Update System Slots file
	bSuccess = bSuccess && UpdateSystemSlots( pPC);
	// Update Videos file
	bSuccess = bSuccess && UpdateVideos( pPC);
	bSuccess = bSuccess && UpdateAccountInfo( pPC);

	if (bSuccess)
		AddLog( _T( "XML Update Device properties: OK.\n"));
	else
		AddLog( _T( "XML Update Device properties: Failed !\n"));
	return bSuccess;
}

BOOL CXMLInteract::parseProcessor( CDeviceProperties &pPC )
{
	AddLog("BIOSINFO: Searching processor informations...\n");
	CMarkup x;
	CString name,speed,number;
	x.SetDoc(m_csBiosInfoBuffer);	

	x.FindElem("OCSINVENTORY");
	x.IntoElem();
	x.FindElem("HARDWARE");

	x.FindChildElem("PROCESSORT");		
	name = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("PROCESSORS");
	speed = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("PROCESSORN");
	number = x.GetChildData();
	x.ResetChildPos();

	pPC.SetProcessor(name,speed,atoi(number.GetBuffer(0)));
	return TRUE;
}

BOOL CXMLInteract::parseMemorySlots( CDeviceProperties &pPC )
{
	AddLog("BIOSINFO: Searching Memory Slots...\n");
	CMarkup x;
	CMemorySlot leS;
	x.SetDoc(m_csBiosInfoBuffer);

	x.FindElem("OCSINVENTORY");
	x.IntoElem();

	while(x.FindElem("MEMORIES"))
	{
		x.FindChildElem("CAPTION");
		leS.SetCaption(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("DESCRIPTION");
		leS.SetDescription(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("CAPACITY");

		// Convert biosinfo memory in kbytes to mbytes
		UINT mem = atoi(x.GetChildData());
		DOUBLE memd = atof(x.GetChildData());
		
		while( mem > 5000) {
			mem = mem/1024;
			memd = memd /1024;
		}

		if( (memd - mem) > 0.5 )
			mem++;
				
		CString lamem;
		lamem.Format("%u",mem);
		leS.SetCapacity(lamem);
		x.ResetChildPos();
		x.FindChildElem("PURPOSE");
		leS.SetUsage(x.GetChildData());
		x.ResetChildPos();
		
		x.FindChildElem("TYPE");
		leS.SetType(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("NUMSLOTS");
		leS.SetSlotNumber(atoi(x.GetChildData().GetBuffer(0)));
		x.ResetChildPos();

		pPC.m_MemoryList.AddHead(leS);
	}

	return TRUE;
}

BOOL CXMLInteract::parseSystemSlots( CDeviceProperties &pPC )
{
	AddLog("BIOSINFO: Searching System Slots...\n");
	CMarkup x;
	CSystemSlot leS;
	x.SetDoc(m_csBiosInfoBuffer);

	x.FindElem("OCSINVENTORY");
	x.IntoElem();
	while(x.FindElem("SLOTS"))
	{
		x.FindChildElem("NAME");
		leS.SetName(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("DESCRIPTION");
		leS.SetDescription(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("DESIGNATION");
		leS.SetSlotDesignation(x.GetChildData());
		x.ResetChildPos();

		x.FindChildElem("STATUS");
		leS.SetStatus(x.GetChildData());
		x.ResetChildPos();

		pPC.m_SlotList.AddHead(leS);
	}

	return TRUE;
}

BOOL CXMLInteract::AddAccessLog( CAccessLog *pAccessLog)
{
	pAccessLog->FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS); //app*	
	
	return TRUE;
}

BOOL CXMLInteract::UpdateBIOS(CDeviceProperties &pPC)
{
	if( ((CString)pPC.m_BIOS.GetSystemSerialNumber()).GetLength()<4 ) {
		if(GetBiosInfoXml(pPC)) {
			AddLog("BIOSINFO: Searching BIOS informations...\n");
			pPC.m_BIOS.ParseFromXML(m_csBiosInfoBuffer);
		}
	}

	pPC.m_BIOS.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);	
	return TRUE;
}

BOOL CXMLInteract::launchBiosInfo( CDeviceProperties &pPC )
{
	return TRUE;
}

BOOL CXMLInteract::GetBiosInfoXml(CDeviceProperties &pPC)
{
	if(!launchBiosInfo(pPC) ||  m_csBiosInfoBuffer=="na" )
		return FALSE;
	else if(m_csBiosInfoBuffer!="")
		return TRUE;

	CString os=pPC.GetOSName();

	CString optBinfo = "";
	if( CUtils::IsRequired(m_csCmdL, "biosfunc") ) {
		optBinfo = " -F";
		AddLog( _T( "BIOSINFO: Launching in BIOS FUNCTIONS mode\n"));
	}
	else if( CUtils::IsRequired(m_csCmdL, "dmi") || os.Find(NT4) != -1 ) {
		optBinfo = " -T";
		AddLog( _T( "BIOSINFO: Launching in DMI mode\n"));
	}
	else
		AddLog( _T( "BIOSINFO: Launching in default mode\n"));

	CString cmd;
	cmd.Format( _T( "BIOSINFO.EXE%s %s %s"), optBinfo, pPC.GetDeviceID(),"bios.tmp" );	
	CFile cf;
	CFileException e;
	if(!cf.Open("BIOSINFO.EXE",CFile::modeRead,&e))
	{
			AddLog( _T( "BIOSINFO: ERROR BiosInfo.exe not found, S/N will not be available !\n"));
			m_csBiosInfoBuffer="na";
			return FALSE;
	}
	else
	{
		cf.Close();
		
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );
		si.dwFlags=STARTF_USESHOWWINDOW;
		si.wShowWindow=SW_HIDE;
		if (CreateProcess(NULL,cmd.GetBuffer(0),NULL, NULL, FALSE, 0, NULL, NULL, &si,&pi ))
		{
			// Process created
			if (WaitForSingleObject( pi.hProcess, 10000 ) == WAIT_TIMEOUT)
			{
				// Process did not ended correctly, kill it
				AddLog( _T( "BIOSINFO: ERROR: Process did not ended after 10s, trying to kill it..."));
				if (!TerminateProcess( pi.hProcess, 0))
					AddLog( "Unable to kill process !\n");
				else
					AddLog( "OK\n");
			}
			CStdioFile f;

			if(f.Open( _T( "bios.tmp"),CFile::modeRead,&e))
			{
				CString csTmp;
				
				while(f.ReadString(csTmp))
					m_csBiosInfoBuffer+=csTmp;

				f.Close();
				DeleteFile( _T( "bios.tmp"));
			}
			else
			{
				AddLog( _T( "BIOSINFO: ERROR: Biosinfo did not generate file !\n"));
				m_csBiosInfoBuffer= _T( "na");
				return FALSE;
			}
		}
		else
		{
			// Unable to create process
			AddLog( _T( "BIOSINFO: ERROR: Unable to launch BiosInfo.exe tool !\n"));
			m_csBiosInfoBuffer= _T( "na");
			return FALSE;
		}
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateDrives(CDeviceProperties &pPC)
{
	CLogicalDrive	cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Logical Drives...\n"));		
		pos = pPC.m_DriveList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_DriveList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);		
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_DriveList.GetNext( pos);
		}

		AddLog( _T( "\tXML Update Logical Drives: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Logical Drives: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Logical Drives: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateHardware(CDeviceProperties &pPC)
{
	CString processorS=pPC.GetProcessorSpeed();
	int trad=atoi(processorS.GetBuffer(0));
	if( trad == 0 || processorS.GetLength()<1) {
		if(GetBiosInfoXml(pPC))		
			parseProcessor(pPC);
	}

	pPC.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*	
	return TRUE;
}

BOOL CXMLInteract::UpdateInputDevices(CDeviceProperties &pPC)
{
	CInputDevice cObject;
	POSITION	pos;
	BOOL		bContinue;
	UINT		uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Input Devices...\n"));
		// Create new file
	
		pos = pPC.m_InputList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_InputList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_InputList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Input Devices: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Input Devices: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Input Devices: Failed because Unknown Exception !\n"));
		pEx->Delete();
	
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateMemorySlots(CDeviceProperties &pPC)
{
	if( pPC.m_MemoryList.GetCount() == 0 ) {
		if(GetBiosInfoXml(pPC))
			parseMemorySlots(pPC);
	}

	CMemorySlot		cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;
	UINT			memTotale = 0;

	try
	{
		// Insert new object records from List
		pos = pPC.m_MemoryList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_MemoryList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			memTotale += atoi(cObject.GetCapacity());
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_MemoryList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Memory Slots: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Memory Slots: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Memory Slots: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	//New global memory counting
	if(memTotale > 0) {		
		
		UINT memStart = pPC.GetPhysicalMemory();
		UINT memToSet = memStart;
		
		UINT diff = abs(memTotale - memStart);

		if( diff < 16 ) {			
			AddLog("MEM: Set to %u (instead of %u)\n", memTotale, memStart);
			memToSet = memTotale;
		}
		else
			AddLog("MEM: Bogus summed memoryslots, %u is too far from %u (keeping the last one)\n", memTotale, memStart);
		
		pPC.SetMemory( memToSet, pPC.GetPageFileSize());
	}

	return TRUE;
}

BOOL CXMLInteract::UpdateModems(CDeviceProperties &pPC)
{
	CModem			cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{	
		// Insert new object records from List
		pos = pPC.m_ModemList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_ModemList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_ModemList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Modems: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Modems: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Modems: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateMonitors(CDeviceProperties &pPC)
{
	CString			csBuffer;
	CMonitor		cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		pos = pPC.m_MonitorList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_MonitorList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_MonitorList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Monitors: OK. (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Monitors: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Monitors: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateNetworks(CDeviceProperties &pPC)
{
	CNetworkAdapter	cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		pos = pPC.m_NetworkList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_NetworkList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);			
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_NetworkList.GetNext( pos);
		}
		AddLog( _T( "\tXML Update Network Adapters: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Network Adapters: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Network Adapters: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateSystemPorts(CDeviceProperties &pPC)
{
	CSystemPort	cObject;
	POSITION	pos;
	BOOL		bContinue;
	UINT		uCount = 0;

	try
	{
		// Insert new object records from List
		pos = pPC.m_PortList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_PortList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_PortList.GetNext( pos);
		}
		AddLog( _T( "\tXML Update System Ports: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update System Ports: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update System Ports: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdatePrinters(CDeviceProperties &pPC)
{
	CPrinter	cObject;
	POSITION	pos;
	BOOL		bContinue;
	UINT		uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Printers...\n"));
		// Insert new object records from List
		pos = pPC.m_PrinterList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_PrinterList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_PrinterList.GetNext( pos);
		}
	
		AddLog( _T( "\tXML Update Printers: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Printers: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Printers: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateAccountInfo(CDeviceProperties &pPC)
{
	CAccountInfo gie;
	gie.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS,CUtils::getDir(1));
	return TRUE;
}

BOOL CXMLInteract::UpdateRegistryValues(CDeviceProperties &pPC)
{
	CRegistryValue cObject;	
	POSITION	pos;
	BOOL		bContinue;
	UINT		uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Registry Values...\n"));
		// Insert new object records from List
		pos = pPC.m_RegistryList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_RegistryList.GetNext( pos);

		BOOL didPresent=FALSE;
		while (bContinue)
		{
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);
			bContinue = (pos != NULL);		

			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_RegistryList.GetNext( pos);
		}

		AddLog( _T( "\tXML Update Registry Values: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Registry Values: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Registry Values: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateSoftwares(CDeviceProperties &pPC)
{
	CSoftware	cObject;
	POSITION	pos;
	BOOL		bContinue;
	UINT		uCount = 0;

	try
	{
		// Check for switch on command line nosoft
		if( CUtils::IsRequired(m_csCmdL, "nosoft") )
		{
			// do not report installed softwares
			return TRUE;
		}

		AddLog( _T( "\tXML Update Softwares...\n"));
		// Insert new object records from List
		pos = pPC.m_SoftwareList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_SoftwareList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_SoftwareList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Softwares: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Softwares: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Softwares: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateSounds(CDeviceProperties &pPC)
{
	CSoundDevice	cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Sound Devices...\n"));
		// Insert new object records from List
		pos = pPC.m_SoundList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_SoundList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_SoundList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update Sound Devices: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Sound Devices: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Sound Devices: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateStorages(CDeviceProperties &pPC)
{
	CStoragePeripheral cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Storage Peripherals...\n"));
		// Insert new object records from List
		pos = pPC.m_StorageList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_StorageList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_StorageList.GetNext( pos);
		}
	
		AddLog( _T( "\tXML Update Storage Peripherals: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Storage Peripherals: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Storage Peripherals: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateSystemControllers(CDeviceProperties &pPC)
{
	CSystemController cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update System Controllers...\n"));	
		// Insert new object records from List
		pos = pPC.m_SystemControllerList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_SystemControllerList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_SystemControllerList.GetNext( pos);
		}
		
		AddLog( _T( "\tXML Update System Controllers: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update System Controllers: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update System Controllers: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateSystemSlots(CDeviceProperties &pPC)
{	
	if( pPC.m_SlotList.GetCount() == 0) {
		if(GetBiosInfoXml(pPC))
			parseSystemSlots(pPC);
	}
	
	CSystemSlot		cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update System Slots...\n"));
		// Insert new object records from List
		pos = pPC.m_SlotList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_SlotList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);//app*
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_SlotList.GetNext( pos);
		}

		AddLog( _T( "\tXML Update System Slots: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update System Slots: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update System Slots: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::UpdateVideos(CDeviceProperties &pPC)
{
	CVideoAdapter	cObject;
	POSITION		pos;
	BOOL			bContinue;
	UINT			uCount = 0;

	try
	{
		AddLog( _T( "\tXML Update Video Adapters...\n"));
		// Insert new object records from List
		pos = pPC.m_VideoList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			// There is one record => get the first
			cObject = pPC.m_VideoList.GetNext( pos);
		while (bContinue)
		{
			bContinue = (pos != NULL);
			cObject.FormatXML( &((COCSInventoryApp*)AfxGetApp())->m_markupOCS);
			uCount ++;
			if (pos != NULL)
				cObject = pPC.m_VideoList.GetNext( pos);
		}
	
		AddLog( _T( "\tXML Update Video Adapters: OK (%u objects).\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Update Video Adapters: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Update Video Adapters: Failed because Unknown Exception !\n"));
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::RetrieveRegistryValues( CDeviceProperties &pPC)
{
/*	CStdioFile		cFile;
	CString			csBuffer,
					csTemp,
					csName,
					csRegKey,
					csRegValue,
					csResult;
	UINT			uIndex = 0;
	int				nRegTree,
					nPos;
	CRegistry		myRegistry;
	CRegistryValue  myObject;

	try
	{
		AddLog( _T( "XML RetrieveRegistryValues...\n"));
		// Open the registry config file
		csTemp.Format( _T( "%s%s"), m_csExecutionFolder, REGISTRY_SETTINGS_FILE);
		if (!cFile.Open( csTemp, CFile::modeRead|CFile::shareDenyWrite|CFile::typeText))
		{
			AddLog( _T( "XML RetrieveRegistryValues: Failed because unable to open file <%s> ! Using default values.\n"),
					csTemp);
			return FALSE;
		}
		while (cFile.ReadString( csBuffer))
		{
			myObject.Clear();
			// Get the name
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csName = csBuffer.Left(nPos);
			csTemp = csBuffer.Mid(nPos + 1);
			csBuffer = csTemp;
			// Get the registry tree to query
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csTemp = csBuffer.Left(nPos);
			nRegTree = _ttoi( csTemp);
			csTemp = csBuffer.Mid(nPos + 1);
			csBuffer = csTemp;
			// Get the registry key to query
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csRegKey = csBuffer.Left(nPos);
			csTemp = csBuffer.Mid(nPos + 1);
			csBuffer = csTemp;
			// Get the registry value to query
			if ((nPos = csBuffer.Find(_T( ";"))) == -1)
			{
				AddLog( _T( "\tFailed to parse XML buffer <%s> ! Skipping this value.\n"),
						csBuffer);
				continue;
			}
			csRegValue = csBuffer.Left(nPos);
			if (myRegistry.GetRegistryValue( nRegTree, csRegKey, csRegValue, csResult))
			{
				// Add result to list
				myObject.SetDeviceID( pPC.GetDeviceID());
				myObject.Set( csName, csResult);
				pPC.m_RegistryList.AddTail( myObject);
				uIndex ++;
			}
		}
		// Close file
		cFile.Close();
		AddLog( _T( "XML RetrieveRegistryValues: OK (%u objects).\n"), uIndex);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "XML RetrieveRegistryValues: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "XML RetrieveRegistryValues: Failed because Unknown Exception !\n"));
		cFile.Abort();
		pEx->Delete();
		return FALSE;
	}
*/	return TRUE;
}

BOOL CXMLInteract::ReadBIOS(LPCTSTR lpstrFilename, CDeviceProperties &pPC)
{
	CString		csBuffer;
	CStdioFile	cFile;
	UINT		uCount = 0;

	try
	{
		AddLog( _T( "\tXML Read BIOS from file <%s>...\n"), lpstrFilename);
		if (!cFile.Open( lpstrFilename, CFile::modeRead|CFile::shareDenyWrite|CFile::typeText))
		{
			pPC.m_BIOS.Clear();
			AddLog( _T( "\tXML Read BIOS: Failed because unable to open file !\n"));
			return FALSE;
		}
		while (cFile.ReadString( csBuffer))
		{
			// Fill Device hardware properties from string
			if (!pPC.m_BIOS.ParseFromXML( csBuffer))
			{
				cFile.Abort();
				AddLog( _T( "\tXML Read BIOS: Failed because unable to parse XML buffer <%s> !\n"), csBuffer);
				return FALSE;
			}
			uCount ++;
		}
		cFile.Close();
		if (uCount == 1)
			AddLog( _T( "\tXML Read BIOS: OK.\n"));
		else
			AddLog( _T( "\tXML Read BIOS: Warning because %s objects read !\n"), uCount);
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "\tXML Read BIOS: Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "\tXML Read BIOS: Failed because Unknown Exception !\n"));
		pEx->Delete();
		cFile.Abort();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::ReadLastInventoryState(LPCTSTR lpstrFilename, COCSInventoryState &myState)
{
	CStdioFile cFile;
	CString		csBuffer,
				csTmp;

	try
	{
		csBuffer.Empty();
		AddLog( _T( "\tXML Read last inventory state from file <%s>..."), lpstrFilename);
		if (cFile.Open( lpstrFilename,CFile::modeRead, NULL))
		{
			while (cFile.ReadString( csTmp))
				csBuffer+=csTmp;
			cFile.Close();
			// Fill Device hardware properties from string
			if (!myState.ParseFromXML( csBuffer))
			{
				cFile.Abort();
				AddLog( _T( "Failed because unable to parse XML buffer <%s> !\n"), csBuffer);
				return FALSE;
			}
		}
		else
		{
			AddLog("Unable to open file !\n");
			return FALSE;
		}
		AddLog( _T( "OK\n"));
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "Failed because Unknown Exception !\n"));
		pEx->Delete();
		cFile.Abort();
		return FALSE;
	}
	return TRUE;
}

BOOL CXMLInteract::WriteLastInventoryState(LPCTSTR lpstrFilename, COCSInventoryState &myState)
{
	CMarkup	myXml;
	CStdioFile cFile;

	try
	{
		AddLog( _T( "\tXML Write new inventory state to file <%s>..."), lpstrFilename);
		if (cFile.Open( lpstrFilename,CFile::modeCreate|CFile::modeWrite, NULL))
		{
			myXml.SetDoc( XML_HEADERS);
			myState.FormatXML( &myXml);
			cFile.Write( myXml.GetDoc(),myXml.GetDoc().GetLength());
			cFile.Close();
		}
		else
		{
			AddLog("Unable to open file !\n");
			return FALSE;
		}
		AddLog( _T( "OK\n"));
	}
	catch( CException *pEx)
	{
		// Exception=> free exception, but continue
		if (pEx->IsKindOf( RUNTIME_CLASS( CFileException)))
			// XML exception
			AddLog( _T( "Failed because XML Exception <%s> !\n"), GetErrorMessage( pEx));
		else
			// Unknown error 
			AddLog( _T( "Failed because Unknown Exception !\n"));
		cFile.Abort();
		pEx->Delete();
		return FALSE;
	}
	return TRUE;
}
