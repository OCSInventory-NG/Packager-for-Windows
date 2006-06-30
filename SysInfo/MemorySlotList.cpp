// Document modified at : Wednesday, March 29, 2006 3:00:00 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// MemorySlotList.cpp: implementation of the CMemorySlotList class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "MemorySlot.h"
#include "MemorySlotList.h"
#include "OcsCrypto.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemorySlotList::CMemorySlotList()
{
}

CMemorySlotList::~CMemorySlotList()
{
}

LPCTSTR CMemorySlotList::GetHash()
{
	COcsCrypto	myHash;
	CMemorySlot myObject;
	POSITION	pos;
	BOOL		bContinue;
	static CString		csToHash;

	if (!myHash.HashInit())
		return NULL;
	pos = GetHeadPosition();
	bContinue = (pos != NULL);
	if (bContinue)
		// There is one record => get the first
		myObject = GetNext( pos);
	while (bContinue)
	{
		csToHash.Format( _T( "%s%s%s%s%s%s%u"), myObject.GetCaption(), myObject.GetDescription(),
						 myObject.GetCapacity(), myObject.GetUsage(), myObject.GetType(),
						 myObject.GetSpeed(), myObject.GetSlotNumber());
		myHash.HashUpdate( LPCTSTR( csToHash), csToHash.GetLength());
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}
