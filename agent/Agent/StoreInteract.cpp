// Document modified at : Saturday, January 03, 2004 11:32:46 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// StoreInteract.cpp: implementation of the CStoreInteract class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"

#include "Resource.h"
#include "SysInfo.h"
#include "StoreInteract.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStoreInteract::CStoreInteract()
{
	m_bSearchFiles = FALSE;		// By default, do not search for files in disks
	m_bLogAccess = FALSE;		// By default, do not store all computer access
	m_bDisplayStatus = TRUE;	// By default, display splash screen
	m_bDisplayError = TRUE;		// by default, display errors
	m_lFrequency = 1;			// By default, run check every day
	m_bProcess = FALSE;			// By default, disable search process status
	m_bAutoWorkgroupMap = TRUE; // By default, enable build of network map view based on domains or workgroups
}

CStoreInteract::~CStoreInteract()
{
}

BOOL CStoreInteract::OpenDB(LPCTSTR lpstrExecutionFolder)
{
	return FALSE;
}


BOOL CStoreInteract::IsOpen()
{
	return FALSE;
}

LPCTSTR CStoreInteract::GetErrorMessage( CException *pEx)
{
	static CString strMsg;
	TCHAR   szErr[256];
	CString csMessage;

	if (pEx == NULL)
	{
		strMsg = _T( "An unspecified error occurred");
		return strMsg;
	}
	if (!pEx->GetErrorMessage( szErr, 256))
		sprintf( szErr, _T( "Unknown error"));
	strMsg.FormatMessage( IDS_ERROR_UNKNOWN_EXCEPTION, szErr);
	return strMsg;
}

void CStoreInteract::DisplayException( CException *pEx)
{
	CStoreInteract myStore;
	//AfxMessageBox( myStore.GetErrorMessage( pEx), MB_ICONSTOP);
}

LONG CStoreInteract::GetFrequency()
{
	return m_lFrequency;
}

BOOL CStoreInteract::GetDisplayVisible()
{
	return m_bDisplayStatus;
}

BOOL CStoreInteract::GetDisplayError()
{
	return m_bDisplayError;
}

BOOL CStoreInteract::GetLogAccess()
{
	return m_bLogAccess;
}

BOOL CStoreInteract::GetAutoWorkgroupMap()
{
	return m_bAutoWorkgroupMap;
}

COleDateTime CStoreInteract::GetLastCheckDate(LPCTSTR lpstrComputerName)
{
	COleDateTime	cOleLastCheck;

	cOleLastCheck.SetDate( 1900, 1, 1);
	return cOleLastCheck;
}

void CStoreInteract::CloseDB()
{
}

BOOL CStoreInteract::UpdateDevice(CDeviceProperties &pPC)
{
	return FALSE;
}

BOOL CStoreInteract::AddAccessLog(CAccessLog *pAccessLog)
{
	return FALSE;
}

BOOL CStoreInteract::GetSettings()
{
	return FALSE;
}

BOOL CStoreInteract::RetrieveRegistryValues(CDeviceProperties &pPC)
{
	return FALSE;
}

void CStoreInteract::SetCmdL(LPCSTR cmdL) {
	m_csCmdL = cmdL;
}

BOOL CStoreInteract::GetProcess()
{
	return m_bProcess;
}

LPCTSTR CStoreInteract::GetProcessFilenames()
{
	return m_csProcesses;
}


UINT CStoreInteract::GetStorageMethod()
{
	return UNKNOWN_STORAGE;
}


BOOL CStoreInteract::IsExtensionToSearch(LPCTSTR lpstrFilename)
{
	CString	csFile = lpstrFilename,
			csExt,
			csData,
			csTemp,
			csBuffer = m_csExtensionToSearch;
	int		nPos;

	if (m_csExtensionToSearch.IsEmpty())
		return FALSE;
	csFile.MakeLower();
	if ((nPos = csFile.ReverseFind( '.')) == -1)
		return FALSE;
	csExt = csFile.Mid( nPos+1);
	while ((nPos = csBuffer.Find(_T( ","))) >= 0)
	{
		csData = csBuffer.Left( nPos);
		if (csExt.Compare( csData) == 0)
			return TRUE;
		csTemp = csBuffer.Mid( nPos + 1);
		csBuffer = csTemp;
	}
	if (csExt.Compare( csBuffer) == 0)
		return TRUE;
	return FALSE;
}

BOOL CStoreInteract::IsExcludeFolder( LPCTSTR lpstrFolder)
{
	CString	csFolder = lpstrFolder,
			csData,
			csTemp,
			csBuffer = m_csExcludeFolder;
	int		nPos;


	if (m_csExcludeFolder.IsEmpty())
		return FALSE;
	csFolder.MakeLower();
	while ((nPos = csBuffer.Find(_T( ","))) >= 0)
	{
		csData = csBuffer.Left( nPos);
		if (csFolder.Find( csData) >= 0)
			return TRUE;
		csTemp = csBuffer.Mid( nPos + 1);
		csBuffer = csTemp;
	}
	if (csFolder.Find( csBuffer) >= 0)
		return TRUE;
	return FALSE;
}

BOOL CStoreInteract::IsSearchDiskEnabled()
{
	return m_bSearchFiles;
}
