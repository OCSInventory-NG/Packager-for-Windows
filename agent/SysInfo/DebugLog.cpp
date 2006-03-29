// Document modified at : Tuesday, March 28, 2006 12:50:22 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// DebugLog.cpp: implementation of the CDebugLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DebugLog.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CStdioFile	myFile;
BOOL	bOpened = FALSE;

void OpenLog( LPCTSTR lpstrFolder, LPCTSTR lpstrCommandLine)
{

	try
	{
		CString	csFileName,
				csCommand = lpstrCommandLine;
		
		if (bOpened)
			myFile.Close();
		bOpened = FALSE;
		// Check if debug log is required
		csCommand.MakeLower();
		if ((csCommand.Find( _T( "-debug")) == -1) && (csCommand.Find( _T( "/debug")) == -1))
			return;
		csFileName.Format( _T( "%s.log"), lpstrFolder);
		if (!myFile.Open( csFileName, CFile::modeCreate|CFile::modeWrite|CFile::typeText))
			// Unable to open file
			return;
		// Seek to End
		myFile.SeekToEnd();
		bOpened = TRUE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		myFile.Abort();
		bOpened = FALSE;
	}
}

void AddLog(LPCTSTR lpstrLog,...)
{
	if (!bOpened)
		return;
	try
	{
		CString			csBuffer;
		va_list			argList;

		// Format arguments
		va_start(argList, lpstrLog);
		csBuffer.FormatV( lpstrLog, argList);
		va_end( argList);
		// Write string
		myFile.WriteString( csBuffer);
		myFile.Flush();
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		myFile.Abort();
	}
}

void CloseLog()
{
	try
	{
		if (bOpened)
			myFile.Close();
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		myFile.Abort();
	}
	bOpened = FALSE;
}