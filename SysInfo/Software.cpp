// Document modified at : Wednesday, March 29, 2006 11:12:25 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// Software.cpp: implementation of the CSoftware class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Software.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoftware::CSoftware()
{
	Clear();
}

CSoftware::~CSoftware()
{
	Clear();
}

ULONG CSoftware::GetID()
{
	return m_ulID;
}

LPCTSTR CSoftware::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CSoftware::GetPublisher()
{
	return m_csPublisher;
}

LPCTSTR CSoftware::GetName()
{
	return m_csName;
}

LPCTSTR CSoftware::GetVersion()
{
	return m_csVersion;
}

LPCTSTR CSoftware::GetFolder()
{
	return m_csFolder;
}

LPCTSTR CSoftware::GetComments()
{
	return m_csComments;
}

LPCTSTR CSoftware::GetFilename()
{
	return m_csFilename;
}

ULONG CSoftware::GetFilesize()
{
	return m_ulFilesize;
}

BOOL CSoftware::IsFromRegistry()
{
	return m_bFromRegistry;
}

LPCTSTR CSoftware::GetSource()
{
	if (m_bFromRegistry)
		return _T( "Registry");
	return _T( "Disk");
}

void CSoftware::Set( LPCTSTR lpstrPublisher, LPCTSTR lpstrName, LPCTSTR lpstrVersion, LPCTSTR lpstrFolder, LPCTSTR lpstrComments, LPCTSTR lpstrFilename, ULONG ulSize, BOOL bFromRegistry)
{
	m_csPublisher = lpstrPublisher;
	StrForSQL( m_csPublisher);
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csVersion = lpstrVersion;
	StrForSQL( m_csVersion);
	m_csFolder = lpstrFolder;
	StrForSQL( m_csFolder);
	m_csComments = lpstrComments;
	StrForSQL( m_csComments);
	m_csFilename = lpstrFilename;
	StrForSQL( m_csFilename);
	m_ulFilesize = ulSize;
	m_bFromRegistry = bFromRegistry;
}

void CSoftware::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CSoftware::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CSoftware::SetPublisher(LPCTSTR lpstrPublisher)
{
	m_csPublisher = lpstrPublisher;
	StrForSQL( m_csPublisher);
}

void CSoftware::SetName(LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CSoftware::SetVersion(LPCTSTR lpstrVersion)
{
	m_csVersion = lpstrVersion;
	StrForSQL( m_csVersion);
}

void CSoftware::SetFolder(LPCTSTR lpstrFolder)
{
	m_csFolder = lpstrFolder;
	StrForSQL( m_csFolder);
}

void CSoftware::SetComments(LPCTSTR lpstrComments)
{
	m_csComments = lpstrComments;
	StrForSQL( m_csComments);
}

void CSoftware::SetFilename(LPCTSTR lpstrFilename)
{
	m_csFilename = lpstrFilename;
	StrForSQL( m_csFilename);
}

void CSoftware::SetFilesize(ULONG ulSize)
{
	m_ulFilesize = ulSize;
}

void CSoftware::SetFromRegistry( BOOL bFromRegistry)
{
	m_bFromRegistry = bFromRegistry;
}

BOOL CSoftware::FormatXML(CMarkup* pX)
{
	pX->AddElem("SOFTWARES");
	pX->IntoElem();
		pX->AddElemNV("PUBLISHER",m_csPublisher);
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("VERSION",m_csVersion);
		pX->AddElemNV("FOLDER",m_csFolder);
		pX->AddElemNV("COMMENTS",m_csComments);
		pX->AddElemNV("FILENAME",m_csFilename);
		pX->AddElemNV("FILESIZE",m_ulFilesize);
		pX->AddElemNV("SOURCE",m_bFromRegistry ? 1 : 0);
	pX->OutOfElem();
	return TRUE;
}

void CSoftware::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CSoftware::GetDeviceName()
{
	return m_csDeviceName;
}

void CSoftware::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csPublisher.Empty();	
	m_csName.Empty();		
	m_csVersion.Empty();	
	m_csFolder.Empty();		
	m_csComments.Empty();	
	m_csFilename.Empty();	
	m_ulFilesize = 0;	
	m_bFromRegistry = FALSE;
}
