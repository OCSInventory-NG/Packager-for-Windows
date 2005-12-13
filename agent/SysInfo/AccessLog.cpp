// Document modified at : Tuesday, May 25, 2004 11:13:54 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// AccessLog.cpp: implementation of the CAccessLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OcsProcess.h"
#include "AccessLog.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccessLog::CAccessLog()
{

}

CAccessLog::~CAccessLog()
{

}

ULONG CAccessLog::GetID()
{
	return m_ulID;
}

LPCTSTR CAccessLog::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CAccessLog::GetUserID()
{
	return m_csUserID;
}

LPCTSTR CAccessLog::GetLogonDate()
{
	return (m_csLogonDate.IsEmpty() ? NULL : LPCTSTR( m_csLogonDate));
}

LPCTSTR CAccessLog::GetProcessesStatus()
{
	return m_csProcessesStatus;
}

void CAccessLog::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CAccessLog::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CAccessLog::SetUserID( LPCTSTR lpstrUserID)
{
	m_csUserID = lpstrUserID;
	StrForSQL( m_csUserID);
}

void CAccessLog::SetLogonDate( LPCTSTR lpstrDate)
{
	m_csLogonDate = lpstrDate;
	StrForSQL( m_csLogonDate);
}

void CAccessLog::SetLogonDate( COleDateTime &dtDate)
{
	m_csLogonDate = dtDate.Format( _T( "%Y-%m-%d %H:%M:%S"));
	StrForSQL( m_csLogonDate);
}

void CAccessLog::SetProcessesStatus( LPCTSTR lpstrProcess)
{
	m_csProcessesStatus = lpstrProcess;
	StrForSQL( m_csProcessesStatus);
}

BOOL CAccessLog::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp,
				csData;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDeviceID = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read User ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csUserID = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read logon date
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csLogonDate = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read processes status
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csProcessesStatus = csBuffer.Left( nPos);
	return TRUE;
}

BOOL CAccessLog::CheckRunningProcesses(LPCTSTR lpstrProcessesNames, CString &csProcessesStatus)
{
	CString strHeadings = lpstrProcessesNames;
	int		nPos;

	// Serach the lpstrProcessNames string for each process names, comma separated
	while ((nPos = strHeadings.Find(_T(","))) != -1)
	{
		CString strItem;

		strItem = strHeadings.Left(nPos);
		if (CProcess::IsProcessRunning( strItem))
			csProcessesStatus += strItem + _T( " Started, ");
		else
			csProcessesStatus += strItem + _T( " MISSING, ");
		strItem = strHeadings.Mid(nPos + 1);
		strHeadings = strItem;
	}
	if (CProcess::IsProcessRunning( strHeadings))
		csProcessesStatus += strHeadings + _T( " Started, ");
	else
		csProcessesStatus += strHeadings + _T( " MISSING, ");
	return TRUE;
}

BOOL CAccessLog::Retrieve( LPCTSTR lpstrDeviceID, LPCTSTR lpstrUserID, LPCTSTR lpstrProcessesNames)
{
	COleDateTime	cTime = COleDateTime::GetCurrentTime();
	BOOL			bResult = FALSE;

	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
	m_csUserID = lpstrUserID;
	StrForSQL( m_csUserID);
	m_csLogonDate = cTime.Format( _T( "%Y-%m-%d %H:%M:%S"));
	if (lpstrProcessesNames != NULL)
		bResult = CheckRunningProcesses( lpstrProcessesNames, m_csProcessesStatus);
	StrForSQL( m_csProcessesStatus);
	return bResult;
}

BOOL CAccessLog::FormatXML( CMarkup* pX )
{
	pX->AddElem("ACCESSLOG");
	pX->IntoElem();
		pX->AddElemNV("USERID",m_csUserID);
		pX->AddElemNV("LOGDATE",m_csLogonDate);
		pX->AddElemNV("PROCESSES",m_csProcessesStatus);
	pX->OutOfElem();
	return TRUE;
}

void CAccessLog::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CAccessLog::GetDeviceName()
{
	return m_csDeviceName;
}
