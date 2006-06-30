// Document modified at : Wednesday, March 29, 2006 3:06:34 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SystemPortList.cpp: implementation of the CSystemPortList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SystemPort.h"
#include "SystemPortList.h"
#include "OcsCrypto.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSystemPortList::CSystemPortList()
{
}

CSystemPortList::~CSystemPortList()
{
}

LPCTSTR CSystemPortList::GetHash()
{
	COcsCrypto	myHash;
	CSystemPort myObject;
	POSITION	pos;
	BOOL		bContinue;
	CString		csToHash;

	if (!myHash.HashInit())
		return NULL;
	pos = GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myObject = GetNext( pos);
	while (bContinue)
	{
		csToHash.Format( _T( "%s%s%s%s"), myObject.GetType(), myObject.GetName(),
						 myObject.GetCaption(), myObject.GetDescription());
		myHash.HashUpdate( LPCTSTR( csToHash), csToHash.GetLength());
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}
