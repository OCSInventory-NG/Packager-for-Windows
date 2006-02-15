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

// LogicalDrive.cpp: implementation of the CLogicalDrive class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "LogicalDrive.h"

#pragma comment(lib, "mpr.lib")

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLogicalDrive::CLogicalDrive()
{
	Clear();
}

CLogicalDrive::~CLogicalDrive()
{
	Clear();
}

ULONG CLogicalDrive::GetID()
{
	return m_ulID;
}

LPCTSTR CLogicalDrive::GetDeviceID()
{
	return m_csDeviceID;
}

LPCTSTR CLogicalDrive::GetFileSystem()
{
	return m_csFileSystem;
}

LPCTSTR CLogicalDrive::GetDriveType()
{
	return m_csDriveType;
}

LPCTSTR CLogicalDrive::GetVolumName()
{
	return m_csVolumName;
}

LPCTSTR CLogicalDrive::GetDriveLetter()
{
	return m_csDriveLetter;
}

LONG CLogicalDrive::GetTotalMB()
{
	return m_lTotalSize;
}

LONG CLogicalDrive::GetFreeMB()
{
	return m_lFreeSpace;
}

LPCTSTR CLogicalDrive::GetPercentFree()
{
	static CString csMessage;

	if (m_lTotalSize > 0)
		csMessage.Format( _T( "%ld %%"), m_lFreeSpace*100/m_lTotalSize);
	else
		csMessage = NOT_AVAILABLE;
	return csMessage;
}

BOOL CLogicalDrive::RetrieveDriveInfo( LPCTSTR lpstrDrive)
{
	BOOL	bIsLocalDrive;				// TRUE is logical drive is a hard drive
	TCHAR	strName[255];				// Volum Name buffer
	DWORD	dwName = 255;				// Max size of Volum Name buffer
	TCHAR	strFSName[255];				// FS name buffer
	DWORD	dwFSName = 255;				// Max size of FS Name buffer
	DWORD	dwMaximumComponentLength;	// Max filename length for this FS
	DWORD	dwFSFlags;					// FS settings
	TCHAR	strRemoteShare[_MAX_PATH+1];// Remote share name
	DWORD	dwRemoteShare = _MAX_PATH+1;// Max size of remote share name
	CString	csDrive;					// Formatting the drive name for WNetGetConnection

	m_csDriveLetter = lpstrDrive;
	// Retrieve drive type
	switch (::GetDriveType( lpstrDrive))
		{
		case DRIVE_FIXED :		// Local HDD
			m_csDriveType = _T( "Hard Drive");
			bIsLocalDrive = TRUE;
			// Retrieve File System information
			if (GetVolumeInformation( lpstrDrive, strName, dwName, NULL, &dwMaximumComponentLength, &dwFSFlags, strFSName, dwFSName))
			{
				// OK
				m_csVolumName = strName;
				m_csFileSystem = strFSName;
			}
			else
			{
				// Error
				m_csVolumName = NOT_AVAILABLE;
				m_csFileSystem = NOT_AVAILABLE;
			}
			break;
		case DRIVE_REMOVABLE :	// Removable Drive
			m_csDriveType = _T( "Removable Drive");
			bIsLocalDrive = FALSE;
			m_csVolumName = NOT_AVAILABLE;
			m_csFileSystem = NOT_AVAILABLE;
			break;
		case DRIVE_CDROM:		// CD-Rom drive
			m_csDriveType = _T( "CD-Rom Drive");
			bIsLocalDrive = FALSE;
			m_csVolumName = NOT_AVAILABLE;
			m_csFileSystem = NOT_AVAILABLE;
			break;
		case DRIVE_REMOTE :		// Network drive
			m_csDriveType = _T( "Network Drive");
			bIsLocalDrive = FALSE;
			// Retrieve File System information
			if (GetVolumeInformation( lpstrDrive, strName, dwName, NULL, &dwMaximumComponentLength, &dwFSFlags, strFSName, dwFSName))
				// OK
				m_csFileSystem = strFSName;
			else
				// Error
				m_csFileSystem = NOT_AVAILABLE;
			// Get remote share
			csDrive = lpstrDrive;
			csDrive.Remove( '\\');
			if (WNetGetConnection( csDrive, strRemoteShare, &dwRemoteShare) == NO_ERROR)
				// OK
				m_csVolumName.Format( _T( "%s"), strRemoteShare);
			else
				// Error
				m_csVolumName.Format( _T( "%s"), NOT_AVAILABLE);
			break;
		case DRIVE_RAMDISK:		// RAM Disk
			m_csDriveType = _T( "RAM Drive");
			bIsLocalDrive = FALSE;
			// Retrieve File System information
			if (GetVolumeInformation( lpstrDrive, strName, dwName, NULL, &dwMaximumComponentLength, &dwFSFlags, strFSName, dwFSName))
			{
				// OK
				m_csVolumName = strName;
				m_csFileSystem = strFSName;
			}
			else
			{
				// Error
				m_csVolumName = NOT_AVAILABLE;
				m_csFileSystem = NOT_AVAILABLE;
			}
			break;
		case DRIVE_NO_ROOT_DIR:	// Disk does not have root dir
		case DRIVE_UNKNOWN:
		default :				// Unknown
			m_csDriveType = NOT_AVAILABLE;
			bIsLocalDrive = FALSE;
			m_csVolumName = NOT_AVAILABLE;
			m_csFileSystem = NOT_AVAILABLE;
			break;
		}
	// Retrieve Total size and Free space
	if (bIsLocalDrive)
	{
		m_lTotalSize = RetrieveTotalSize( lpstrDrive);
		m_lFreeSpace = RetrieveFreeSpace( lpstrDrive);
	}
	else
	{
		// Total size and Free space not available
		m_lTotalSize = 0;
		m_lFreeSpace = 0;
	}
	StrForSQL( m_csDriveLetter);
	StrForSQL( m_csDriveType);
	StrForSQL( m_csFileSystem);
	StrForSQL( m_csVolumName);
	// Return TRUE if this is a hard drive
	return bIsLocalDrive;
}

LONG CLogicalDrive::GetFilesNumber()
{
	return m_lNumberOfFiles;
}

void CLogicalDrive::SetID( ULONG ulID)
{
	m_ulID = ulID;
}

void CLogicalDrive::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	m_csDeviceID = lpstrDeviceID;
	StrForSQL( m_csDeviceID);
}

void CLogicalDrive::SetDriveType( LPCTSTR lpstrType)
{
	m_csDriveType = lpstrType;
	StrForSQL( m_csDriveType);
}

void CLogicalDrive::SetVolumName( LPCTSTR lpstrVolumn)
{
	m_csVolumName = lpstrVolumn;
	StrForSQL( m_csVolumName);
}

void CLogicalDrive::SetFileSystem( LPCTSTR lpstrFileSystem)
{
	m_csFileSystem = lpstrFileSystem;
	StrForSQL( m_csFileSystem);
}

void CLogicalDrive::SetDriveLetter( LPCTSTR lpstrLetter)
{
	m_csDriveLetter = lpstrLetter;
	StrForSQL( m_csDriveLetter);
}

void CLogicalDrive::SetTotalSize( LONG lSize)
{
	m_lTotalSize = lSize;
}

void CLogicalDrive::SetFreeSpace( LONG lFree)
{
	m_lFreeSpace = lFree;
}

void CLogicalDrive::SetFilesNumber(LONG lNum)
{
	m_lNumberOfFiles = lNum;
}

BOOL CLogicalDrive::ParseFromCSV(CString &csCSV)
{
	CString		csBuffer = csCSV,
				csTemp,
				csData;
	int			nPos;

	// Read Computer ID
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Drive letter
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDriveLetter = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Drive type
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csDriveType = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Drive total size
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csData = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	m_lTotalSize = _ttol( csData);
	// Read Drive free space
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csData = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	m_lFreeSpace = _ttol( csData);
	// Read Drive volum name
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csVolumName = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read Drive filesystem
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	m_csFileSystem = csBuffer.Left( nPos);
	csTemp = csBuffer.Mid( nPos + 1);
	csBuffer = csTemp;
	// Read number of files
	if ((nPos = csBuffer.Find(_T( ";"))) == -1)
		return FALSE;
	csData = csBuffer.Left( nPos);
	m_lNumberOfFiles = _ttol( csData);
	return TRUE;
}

ULONG CLogicalDrive::RetrieveTotalSize(LPCTSTR lpstrDrive)
{
	DWORD	dwSectPerClust,
			dwBytesPerSect,
			dwFreeClusters,
			dwTotalClusters;

	unsigned __int64 i64FreeBytesToCaller,
                       i64TotalBytes,
                       i64FreeBytes;
    BOOL  fResult;

	typedef BOOL (WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER,
		PULARGE_INTEGER, PULARGE_INTEGER);

    P_GDFSE pGetDiskFreeSpaceEx = NULL;

//         Use GetDiskFreeSpaceEx if available; otherwise, use
//         GetDiskFreeSpace.
//
//         Note: Since GetDiskFreeSpaceEx is not in Windows 95 Retail, we
//         dynamically link to it and only call it if it is present.  We 
//         don't need to call LoadLibrary on KERNEL32.DLL because it is 
//         already loaded into every Win32 process's address space.

#ifndef _UNICODE
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
                               GetModuleHandle( _T( "KERNEL32.DLL")),
                                                _T( "GetDiskFreeSpaceExA"));
#else
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
                               GetModuleHandle( _T( "KERNEL32.DLL")),
                                                _T( "GetDiskFreeSpaceExW"));
#endif
    if (pGetDiskFreeSpaceEx)
    {
		fResult = pGetDiskFreeSpaceEx (lpstrDrive,
							(PULARGE_INTEGER)&i64FreeBytesToCaller,
                            (PULARGE_INTEGER)&i64TotalBytes,
                            (PULARGE_INTEGER)&i64FreeBytes);
    }
	else
	{
		// Cannot load GetDiskFreeSpaceEx => use GetDiskFreeSpace
        fResult = GetDiskFreeSpace (lpstrDrive, 
                             &dwSectPerClust,
                             &dwBytesPerSect, 
                             &dwFreeClusters,
                             &dwTotalClusters);

        if (fResult)
        {
            // force 64-bit math
			i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust *
                              dwBytesPerSect;
            i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust *
                              dwBytesPerSect;
        }
	}
	
	if (!fResult)
		// Error
		return -1;

    return (ULONG) (i64TotalBytes/ONE_MEGABYTE);
}

ULONG CLogicalDrive::RetrieveFreeSpace(LPCTSTR lpstrDrive)
{
	DWORD	dwSectPerClust,
			dwBytesPerSect,
			dwFreeClusters,
			dwTotalClusters;

	unsigned __int64 i64FreeBytesToCaller,
                     i64TotalBytes,
                     i64FreeBytes;
    BOOL	fResult;

	typedef BOOL (WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER,
		PULARGE_INTEGER, PULARGE_INTEGER);

    P_GDFSE pGetDiskFreeSpaceEx = NULL;

//         Use GetDiskFreeSpaceEx if available; otherwise, use
//         GetDiskFreeSpace.
//
//         Note: Since GetDiskFreeSpaceEx is not in Windows 95 Retail, we
//         dynamically link to it and only call it if it is present.  We 
//         don't need to call LoadLibrary on KERNEL32.DLL because it is 
//         already loaded into every Win32 process's address space.

#ifndef _UNICODE
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
                               GetModuleHandle( _T( "KERNEL32.DLL")),
                                                _T( "GetDiskFreeSpaceExA"));
#else
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress(
                               GetModuleHandle( _T( "KERNEL32.DLL")),
                                                _T( "GetDiskFreeSpaceExW"));
#endif
    if (pGetDiskFreeSpaceEx)
    {
		fResult = pGetDiskFreeSpaceEx (lpstrDrive,
							(PULARGE_INTEGER)&i64FreeBytesToCaller,
                            (PULARGE_INTEGER)&i64TotalBytes,
                            (PULARGE_INTEGER)&i64FreeBytes);
    }
	else
	{
		// Cannot load GetDiskFreeSpaceEx => use GetDiskFreeSpace
        fResult = GetDiskFreeSpace (lpstrDrive, 
                             &dwSectPerClust,
                             &dwBytesPerSect, 
                             &dwFreeClusters,
                             &dwTotalClusters);

        if (fResult)
        {
            // force 64-bit math
			i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust *
                              dwBytesPerSect;
            i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust *
                              dwBytesPerSect;
        }
	}
	
	if (!fResult)
		// Error
		return -1;

    return (ULONG) (i64FreeBytes/ONE_MEGABYTE);
}

BOOL CLogicalDrive::FormatXML(CMarkup* pX)
{		
	pX->AddElem("DRIVES");
	pX->IntoElem();
		pX->AddElemNV("LETTER",m_csDriveLetter);
		pX->AddElemNV("TYPE",m_csDriveType);
		pX->AddElemNV("FILESYSTEM",m_csFileSystem);
		pX->AddElemNV("TOTAL",m_lTotalSize);
		pX->AddElemNV("FREE",m_lFreeSpace);
		pX->AddElemNV("NUMFILES",m_lNumberOfFiles);
		pX->AddElemNV("VOLUMN",m_csVolumName);
	pX->OutOfElem();		
	return TRUE;
}

void CLogicalDrive::SetDeviceName( LPCTSTR lpstrDeviceName)
{
	m_csDeviceName = lpstrDeviceName;
	StrForSQL( m_csDeviceName);
}

LPCTSTR CLogicalDrive::GetDeviceName()
{
	return m_csDeviceName;
}

void CLogicalDrive::Clear()
{
	m_ulID = 0;			
	m_csDeviceID.Empty();	
	m_csDeviceName.Empty();	
	m_csDriveType.Empty();	
	m_csVolumName.Empty();	
	m_csFileSystem.Empty();	
	m_csDriveLetter.Empty();
	m_lTotalSize = 0;	
	m_lFreeSpace = 0;	
	m_lNumberOfFiles = 0;
}
