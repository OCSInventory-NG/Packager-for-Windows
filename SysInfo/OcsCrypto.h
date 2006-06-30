// Document modified at : Wednesday, March 29, 2006 11:05:43 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO


//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// OcsCrypto.h: interface for the COcsCrypto class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COCSCRYPTO_H__213BCCE2_C103_4127_A208_BEF1F271A958__INCLUDED_)
#define AFX_COCSCRYPTO_H__213BCCE2_C103_4127_A208_BEF1F271A958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"

class DLL_CLASS COcsCrypto  
{
public:
	COcsCrypto();
	virtual ~COcsCrypto();

	// Initialize hash algorithm, actually SHA1
	// Must be called before any Hash operation
	BOOL HashInit();
	// Compute Hash on pData which have length of ulLength
	// Can be called as many time as you want
	BOOL HashUpdate( LPCVOID pData, ULONG ulLength);
	// Finalize Hash and return in csHash computed hash in hex format
	// Return NULL if error
	LPCTSTR HashFinal();

protected:
	LPVOID m_pHash;		// Pointer du hash algorithm context
};

#endif // !defined(AFX_COCSCRYPTO_H__213BCCE2_C103_4127_A208_BEF1F271A958__INCLUDED_)
