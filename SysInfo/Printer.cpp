// Document modified at : Wednesday, March 29, 2006 11:11:49 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// Printer.cpp: implementation of the CPrinter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Printer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPrinter::CPrinter()
{
	Clear();
}

CPrinter::~CPrinter()
{
	Clear();
}

void CPrinter::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CPrinter::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CPrinter::SetName( LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void CPrinter::SetDriver( LPCTSTR lpstrDriver)
{
	m_csDriver = lpstrDriver;
	StrForSQL( m_csDriver);
}

void CPrinter::SetPort( LPCTSTR lpstrPort)
{
	m_csPort = lpstrPort;
	StrForSQL( m_csPort);
}

void CPrinter::Set(LPCTSTR lpstrName, LPCTSTR lpstrDriver, LPCTSTR lpstrPort)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
	m_csDriver = lpstrDriver;
	StrForSQL( m_csDriver);
	m_csPort = lpstrPort;
	StrForSQL( m_csPort);
}

ULONG CPrinter::GetID()
{
	return m_ulID;
}

LPCTSTR CPrinter::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CPrinter::GetName()
{
	return m_csName;
}

LPCTSTR CPrinter::GetDriver()
{
	return m_csDriver;
}

LPCTSTR CPrinter::GetPort()
{
	return m_csPort;
}

BOOL CPrinter::FormatXML(CMarkup* pX)
{
	pX->AddElem("PRINTERS");
	pX->IntoElem();
		pX->AddElemNV("NAME",m_csName);
		pX->AddElemNV("DRIVER",m_csDriver);
		pX->AddElemNV("PORT",m_csPort);
	pX->OutOfElem();
	return TRUE;
}

void CPrinter::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CPrinter::GetDeviceName()
{
	return m_csDeviceName;
}

void CPrinter::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csName.Empty();		
	m_csDriver.Empty();		
	m_csPort.Empty();		
}
