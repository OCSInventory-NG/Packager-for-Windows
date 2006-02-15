// Document modified at : Saturday, January 03, 2004 11:32:46 AM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// LogicalDrive.h: interface for the CLogicalDrive class.
//
// Class storing informations about one computer logical drive.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICALDRIVE_H__A1610561_ACE7_11D4_8F74_00600889DFA5__INCLUDED_)
#define AFX_LOGICALDRIVE_H__A1610561_ACE7_11D4_8F74_00600889DFA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CLogicalDrive  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CLogicalDrive();
	virtual ~CLogicalDrive();

	void Clear();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	// Return the database record ID
	ULONG GetID();
	// Return a string with the device unique ID
	LPCTSTR GetDeviceID();
	// Return a string with the device NetBIOS name
	LPCTSTR GetDeviceName();
	// Return the free space in mega bytes of the logical drive
	LONG GetFreeMB();
	// Return the physical size in mega bytes of the logical drive
	LONG GetTotalMB();
	// Return the letter associated by the OS to the logical drive (A, C, D...)
	LPCTSTR GetDriveLetter();
	// Return the operating system volum name of the logical drive
	LPCTSTR GetVolumName();
	// Return the drive type the logical drive (Hard drive, CD-rom...)
	LPCTSTR GetDriveType();
	// Return the file system of the logical drive (FAT, FAT32, NTFS...)
	LPCTSTR GetFileSystem();
	// Return the number of files found on the logical drive
	LONG GetFilesNumber();
	// Return a string containing percantage of free space
	LPCTSTR GetPercentFree();
	// Format informations in a XML string
	BOOL FormatXML( CMarkup* pX );

	//////////////////////////////////
	// Set attributes values
	//////////////////////////////////

	void SetID( ULONG ulID);
	// Set the device unique ID
	void SetDeviceID( LPCTSTR lpstrDeviceID);
	// Set the device NetBIOS name
	void SetDeviceName( LPCTSTR lpstrName);
	void SetDriveType( LPCTSTR lpstrType);
	void SetVolumName( LPCTSTR lpstrVolumn);
	void SetFileSystem( LPCTSTR lpstrFileSystem);
	void SetDriveLetter( LPCTSTR lpstrLetter);
	void SetTotalSize( LONG lSize);
	void SetFreeSpace( LONG lFree);
	void SetFilesNumber( LONG lNum);
	// Retrieve all others logical drive informations
	BOOL RetrieveDriveInfo( LPCTSTR lpstrDrive);
	// Retrieve the informations from a CSV buffer
	BOOL ParseFromCSV( CString &csCSV);

protected: // Methods
	ULONG RetrieveFreeSpace( LPCTSTR lpstrDrive);
	ULONG RetrieveTotalSize( LPCTSTR lpstrDrive);

protected: // Attributes
	ULONG	m_ulID;			// Database record ID
	CString	m_csDeviceID;	// Device unique ID
	CString	m_csDeviceName;	// Device netbios or DNS name
	CString m_csDriveType;	// Drive type (HD, FD, CDRom, REMOVABLE, NETWORK)
	CString m_csVolumName;	// OS volum name
	CString m_csFileSystem;	// File system type (FAT, FAT32, NTFS...)
	CString m_csDriveLetter;// OS drive letter
	LONG	m_lTotalSize;	// Total size in MB
	LONG	m_lFreeSpace;	// Free space in MB
	LONG	m_lNumberOfFiles;// Total number of files
};

#endif // !defined(AFX_LOGICALDRIVEINFO_H__A1610561_ACE7_11D4_8F74_00600889DFA5__INCLUDED_)
