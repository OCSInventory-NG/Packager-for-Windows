// Document modified at : Tuesday, May 25, 2004 10:16:42 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// SysInfoClasses.h
//    
//   This file uses #pragma's and #define's that are shared between all 
//   SysInfo classes. In order to link statically, #define 
//   SYSINFO_LINKSTATIC in your project's settings. 
// 

#ifndef SYSINFOCLASSES_H_
#define SYSINFOCLASSES_H_

#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "markup.h"

#define NOT_AVAILABLE	_T( "N/A")
#define ONE_KILOBYTE	1024
#define ONE_MEGABYTE	1048576 // (1024 * 1024)
#define MAX_OBJECTS		128		// Max number of processes and modules we can check

//------------------------------------------------------
// this allows us to export/import a class
// to link with the dll, do nothing; 
//
#if defined(SYSINFO_EXPORTS)
#   undef DLL_CLASS
#   define DLL_CLASS __declspec(dllexport)
#else 
#   undef DLL_CLASS
#   define DLL_CLASS __declspec(dllimport)
#   if defined(_DEBUG)
#      pragma comment(lib, "SysInfo.lib")
#   else
#      pragma comment(lib, "SysInfo.lib")
#   endif
#endif

//-------------------------------------------------------
// this gets rid of annoying 4251 warning about 
// std::string needing dll interface
// it also gets rid of 4800 -- BOOL to bool cast warnings
//
#pragma warning(disable : 4251 4800)

inline void StrForSQL( CString &csMyStr)
{
	csMyStr.Replace( _T( "'"), _T( "''"));
	csMyStr.Replace( _T( "\\"), _T( "/"));
	csMyStr.Replace( _T( "\n"), _T( " "));
	csMyStr.TrimLeft();
	csMyStr.TrimRight();
}


inline BOOL isLocalDrive( LPCTSTR lpstrDrive)
{
	return (GetDriveType( lpstrDrive) == DRIVE_FIXED);
}

#endif