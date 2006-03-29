// Document modified at : Wednesday, March 29, 2006 1:32:43 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Memory.h
//
//////////////////////////////////////////////////////////////////////

#ifndef _MEMORY_HEADER_
#define _MEMORY_HEADER_

#include "SysInfoClasses.h"


class DLL_CLASS CMemory
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
   CMemory();
   CMemory( const CMemory& source);
   virtual ~CMemory();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

   ULONGLONG getTotalRAM() const;
   ULONGLONG getAvailRAM() const;
   ULONGLONG getTotalPageFile() const;
   ULONGLONG getAvailPageFile() const;
   ULONGLONG getTotalVirtual() const;
   ULONGLONG getAvailVirtual() const;

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

   CMemory& operator=( const CMemory& right);

protected: // Methods
   void assign( const CMemory& source);
   void determineMemory();
   BOOL determineMemory2K();
   BOOL determineMemory9X_NT();

protected: // Attributes
   ULONGLONG m_ulTotalRam;		// Installed physical memory
   ULONGLONG m_ulAvailRam;		// Free physical memory
   ULONGLONG m_ulTotalPageFile;	// Swap file max size
   ULONGLONG m_ulAvailPageFile;	// Free swap file size
   ULONGLONG m_ulTotalVirtual;	// Total virtual memory (pkysical + swap)
   ULONGLONG m_ulAvailVirtual;	// Free virtual memory (physical + swap)
};
#endif