// Document modified at : Wednesday, March 29, 2006 2:58:56 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// InputDeviceList.cpp: implementation of the CInputDeviceList class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "InputDevice.h"
#include "InputDeviceList.h"
#include "OcsCrypto.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CInputDeviceList::CInputDeviceList()
{
}

CInputDeviceList::~CInputDeviceList()
{
}

LPCTSTR CInputDeviceList::GetHash()
{
	COcsCrypto	myHash;
	CInputDevice myObject;
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
		csToHash.Format( _T( "%s%s%s%s%s%s"), myObject.GetType(), myObject.GetManufacturer(),
						 myObject.GetCaption(), myObject.GetDescription(), myObject.GetPointingInterface(),
						 myObject.GetPointingType());
		myHash.HashUpdate( LPCTSTR( csToHash), csToHash.GetLength());
		bContinue = (pos != NULL);
		if (bContinue)
			myObject = GetNext( pos);
	}
	return myHash.HashFinal();
}
