// Document modified at : Tuesday, March 28, 2006 12:50:22 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// DeviceComments.cpp: implementation of the CDeviceComments class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DeviceComments.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeviceComments::CDeviceComments()
{
	Clear();
}

CDeviceComments::~CDeviceComments()
{
	Clear();
}

void	CDeviceComments::Clear()
{
	m_ulID = 0;
	m_csDeviceID.Empty();
	m_csName.Empty();
	m_csComments.Empty();	
}

void	CDeviceComments::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void	CDeviceComments::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void	CDeviceComments::SetName( LPCTSTR lpstrName)
{
	m_csName = lpstrName;
	StrForSQL( m_csName);
}

void	CDeviceComments::SetComments( LPCTSTR lpstrComments)
{
	m_csComments = lpstrComments;
	StrForSQL( m_csComments);
}

ULONG	CDeviceComments::GetID()
{
	return m_ulID;
}

LPCTSTR	CDeviceComments::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR	CDeviceComments::GetName()
{
	return m_csName;
}

LPCTSTR	CDeviceComments::GetComments()
{
	return m_csComments;
}

void CDeviceComments::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CDeviceComments::GetDeviceName()
{
	return m_csDeviceName;
}
