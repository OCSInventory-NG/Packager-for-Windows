// Document modified at : Sunday, January 04, 2004 5:46:06 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET 2005
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Gie.cpp: implementation of the CAccountInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AccountInfo.h"
#include "..\defines.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAccountInfo::CAccountInfo()
{
	
}

CAccountInfo::~CAccountInfo()
{

}

LPCTSTR CAccountInfo::GetDeviceID()
{
	return m_csDeviceID;
}

void CAccountInfo::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

BOOL CAccountInfo::FormatXML(CMarkup* pX,CString file)
{
	CFile cf;
	if(cf.Open(file,CFile::modeRead))
	{
		int size=cf.GetLength();
		int sizeRead;
		cf.Close();
		char* ret=new char[size];

		sizeRead=GetPrivateProfileString( OCS_AGENT_KEY, NULL, _T(""), ret, _MAX_PATH, file);
		
		for(int i=0;i<size;i++)
		{
			if(ret[i]==0)
			{
				ret[i]='-';
			}
			else if(i>=sizeRead)
			{
				ret[i]=0;
			}
		}

		char seps[]   = "-";
		char *token1;
		char* token2=new char[size];

		token1 = strtok( ret, seps );
		while( token1 != NULL )
		{			
			GetPrivateProfileString( OCS_AGENT_KEY, token1, _T(""), token2, _MAX_PATH, file);
		
			pX->AddElem("ACCOUNTINFO");
			pX->IntoElem();
				pX->AddElem("KEYNAME",token1);
				pX->AddElem("KEYVALUE",CString(token2));
			pX->OutOfElem();				
			
			token1 = strtok( NULL, seps );
		}

		delete ret;
		delete token2;
		
	} 

	return TRUE;
}

