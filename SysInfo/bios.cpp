// Document modified at : Wednesday, March 29, 2006 2:55:12 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Modified by Pierre LEMMET 2005
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// Bios.cpp: implementation of the CBios class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Bios.h"
#include "OcsCrypto.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CBios::CBios()
{
	Clear();
}

CBios::~CBios()
{
}

void CBios::Set( LPCTSTR lpstrSystemManufacturer, LPCTSTR lpstrSystemModel, LPCTSTR lpstrSystemSerialNumber, LPCTSTR lpstrMachineType, LPCTSTR lpstrBiosManufacturer, LPCTSTR lpstrBiosVersion, LPCTSTR lpstrBiosDate, LPCTSTR lpstrBiosAssetTag)
{
	m_csSystemManufacturer = lpstrSystemManufacturer;
	StrForSQL( m_csSystemManufacturer);
	m_csSystemModel = lpstrSystemModel;
	StrForSQL( m_csSystemModel);
	m_csSystemSerialNumber = lpstrSystemSerialNumber;
	StrForSQL( m_csSystemSerialNumber);
	m_csMachineType = lpstrMachineType;
	StrForSQL( m_csMachineType);
	m_csBiosManufacturer = lpstrBiosManufacturer;
	StrForSQL( m_csBiosManufacturer);
	m_csBiosVersion = lpstrBiosVersion;
	StrForSQL( m_csBiosVersion);
	m_csBiosDate = lpstrBiosDate;
	StrForSQL( m_csBiosDate);
	m_csBiosAssetTag = lpstrBiosAssetTag;
	StrForSQL( m_csBiosAssetTag);
}

void CBios::SetSystemManufacturer(LPCTSTR lpstrSystemManufacturer)
{
	m_csSystemManufacturer = lpstrSystemManufacturer;
	StrForSQL( m_csSystemManufacturer);
}

void CBios::SetSystemModel(LPCTSTR lpstrSystemModel)
{
	m_csSystemModel = lpstrSystemModel;
	StrForSQL( m_csSystemModel);
}

void CBios::SetSystemSerialNumber(LPCTSTR lpstrSystemSerialNumber)
{
	m_csSystemSerialNumber = lpstrSystemSerialNumber;
	StrForSQL( m_csSystemSerialNumber);
}

void CBios::SetMachineType(LPCTSTR lpstrMachineType)
{
	m_csMachineType = lpstrMachineType;
	StrForSQL( m_csMachineType);
}

void CBios::SetBiosManufacturer(LPCTSTR lpstrBiosManufacturer)
{
	m_csBiosManufacturer = lpstrBiosManufacturer;
	StrForSQL( m_csBiosManufacturer);
}

void CBios::SetBiosVersion(LPCTSTR lpstrBiosVersion)
{
	m_csBiosVersion = lpstrBiosVersion;
	StrForSQL( m_csBiosVersion);
}

void CBios::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CBios::SetBiosDate(LPCTSTR lpstrBiosDate)
{
	m_csBiosDate = lpstrBiosDate;
	//Interpretation dates avec *** ou 000
	if(m_csBiosDate.GetLength()>8)
		if(m_csBiosDate.GetAt(8)=='*'||m_csBiosDate.GetAt(8)=='0')
		{
			CString d,m,y;
			d+=m_csBiosDate[6]; d+=m_csBiosDate[7]; 
			m+=m_csBiosDate[4]; m+=m_csBiosDate[5]; 
			y+=m_csBiosDate[0]; y+=m_csBiosDate[1];
			y+=m_csBiosDate[2]; y+=m_csBiosDate[3];
			m_csBiosDate.Format("%s/%s/%s",d,m,y);
		}
	StrForSQL( m_csBiosDate);
}

void CBios::SetBiosAssetTag( LPCTSTR lpstrBiosAssetTag)
{
	m_csBiosAssetTag = lpstrBiosAssetTag;
	StrForSQL( m_csBiosAssetTag);
}

LPCTSTR CBios::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CBios::GetSystemManufacturer()
{
	return m_csSystemManufacturer;
}

LPCTSTR CBios::GetSystemModel()
{
	return m_csSystemModel;
}

LPCTSTR CBios::GetSystemSerialNumber()
{
	return m_csSystemSerialNumber;
}

LPCTSTR CBios::GetMachineType()
{
	return m_csMachineType;
}

LPCTSTR CBios::GetBiosManufacturer()
{
	return m_csBiosManufacturer;
}

LPCTSTR CBios::GetBiosVersion()
{
	return m_csBiosVersion;
}

LPCTSTR CBios::GetBiosDate()
{
	return m_csBiosDate;
}

LPCTSTR CBios::GetBiosAssetTag()
{
	return m_csBiosAssetTag;
}

BOOL CBios::ParseFromXML(CString &xml)
{
	CMarkup x;
	x.SetDoc(xml);

	x.FindElem("OCSINVENTORY");
	x.IntoElem();
	x.FindElem("BIOS");
	x.FindChildElem("SSN");		
	m_csSystemSerialNumber = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("SMODEL");
	m_csSystemModel = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("BVERSION");
	m_csBiosVersion = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("BDATE");
	m_csBiosDate = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("SMANUFACTURER");
	m_csSystemManufacturer = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("BMANUFACTURER");
	m_csBiosManufacturer = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("TYPE");
	m_csMachineType = x.GetChildData();
	x.ResetChildPos();

	x.FindChildElem("ASSETTAG");
	m_csBiosAssetTag = x.GetChildData();
	x.ResetChildPos();

	return TRUE;
}

void CBios::Clear()
{
	m_csSystemManufacturer.Empty();
	m_csSystemModel.Empty();
	m_csSystemSerialNumber.Empty();
	m_csMachineType.Empty();
	m_csBiosManufacturer.Empty();
	m_csBiosVersion.Empty();
	m_csBiosDate.Empty();
	m_csBiosAssetTag.Empty();
}

BOOL CBios::FormatXML(CMarkup* pX)
{
	pX->AddElem("BIOS");
	pX->IntoElem();
		pX->AddElemNV("SMANUFACTURER",m_csSystemManufacturer);
		pX->AddElemNV("SMODEL",m_csSystemModel);
		pX->AddElemNV("SSN", m_csSystemSerialNumber);
		pX->AddElemNV("TYPE",m_csMachineType);
		pX->AddElemNV("BMANUFACTURER",m_csBiosManufacturer);
		pX->AddElemNV("BVERSION",m_csBiosVersion);
		pX->AddElemNV("BDATE",m_csBiosDate);
		pX->AddElemNV("BASSETTAG",m_csBiosAssetTag);
	pX->OutOfElem();
	return TRUE;
}

void CBios::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CBios::GetDeviceName()
{
	return m_csDeviceName;
}

LPCTSTR CBios::GetHash()
{
	COcsCrypto	myHash;
	static CString		csToHash;

	if (!myHash.HashInit())
		return NULL;
	csToHash.Format( _T( "%s%s%s%s%s%s%s%s"), m_csSystemManufacturer, m_csSystemModel,
					 m_csSystemSerialNumber, m_csBiosManufacturer, m_csBiosVersion,
					 m_csBiosDate,m_csMachineType, m_csBiosAssetTag);
	myHash.HashUpdate( LPCTSTR( csToHash), csToHash.GetLength());
	return myHash.HashFinal();
}
