// Document modified at : Wednesday, March 29, 2006 11:05:43 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// COcsCrypto.cpp: implementation of the OcsCrypto class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "OcsCrypto.h"
#include <openssl/sha.h>
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
COcsCrypto::COcsCrypto()
{
	m_pHash = NULL;
}
COcsCrypto::~COcsCrypto()
{
	if (m_pHash != NULL)
		free( m_pHash);
}
BOOL COcsCrypto::HashInit()
{
	if (m_pHash != NULL)
		free( m_pHash);
	if ((m_pHash = (SHA_CTX *) malloc( sizeof( SHA_CTX))) == NULL)
		return FALSE;
	SHA1_Init( (SHA_CTX *)m_pHash);
	return TRUE;
}
BOOL COcsCrypto::HashUpdate(LPCVOID pData, ULONG ulLength)
{
	if ((m_pHash == NULL) || (pData == NULL))
		return FALSE;
	SHA1_Update( (SHA_CTX *)m_pHash, pData, ulLength);
	return TRUE;
}
LPCTSTR COcsCrypto::HashFinal()
{
	BYTE	digest[SHA_DIGEST_LENGTH];
	UINT	uLength = SHA_DIGEST_LENGTH;
	CString csTemp;
	static CString csHash;
	if (m_pHash == NULL)
		return NULL;
	SHA1_Final( digest, (SHA_CTX *)m_pHash);
	free( m_pHash);
	m_pHash = NULL;
	// Store hash in hex
	csHash.Empty();
	for (UINT i=0; i<uLength; i++)
	{
		csTemp.Format( _T( "%.02X"), digest[i]);
		csHash += csTemp;
	}
	return csHash;
}
