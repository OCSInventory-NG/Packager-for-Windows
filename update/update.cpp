// update.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Zip\ziparchive.h"
#include "update.h"
#include "updateDlg.h"
#include "defines.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL writeParamFile(CString name,CString value)
{
	HANDLE	hFile;
	// Create the file with system and hidden attributes
	if ((hFile = CreateFile( OCS_IDENTIFICATION_FILE, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL,
							 CREATE_NEW, FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN, NULL)) == INVALID_HANDLE_VALUE)
	{
		;	
	}
	else
		CloseHandle( hFile);

	if (WritePrivateProfileString( OCS_AGENT_KEY, name, value, OCS_IDENTIFICATION_FILE) == 0)
	{
		return FALSE;
	}
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CUpdateApp

BEGIN_MESSAGE_MAP(CUpdateApp, CWinApp)
	//{{AFX_MSG_MAP(CUpdateApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUpdateApp construction

CUpdateApp::CUpdateApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUpdateApp object
void CUpdateApp::AddLog(LPCTSTR lpstrLog,...)
{

	if (!bOpened)
		return;
	try
	{
		CString			csBuffer;
		char antiN = '\n';
		va_list			argList;

		// Format arguments
		va_start(argList, lpstrLog);
		csBuffer.FormatV( lpstrLog, argList);
		va_end( argList);
		// Write string
		myFile.Write( csBuffer,csBuffer.GetLength());
		myFile.Write( &antiN,1);
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		myFile.Abort();
	}
}

void CUpdateApp::CloseLog()
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

BOOL CUpdateApp::IsRequired(LPCTSTR lpstrCommandLine,CString option) {
	CString	csCommand = lpstrCommandLine;
	CString csOpt;
	
	option.MakeLower();
	csOpt.Format("/%s ",option);
	csCommand.MakeLower();
	int tst = 0;
	int iRgOpt = csCommand.Find( _T(csOpt) );
	
	if( iRgOpt == -1 ) {
		if(  option.Compare( csCommand.Right(option.GetLength()) ) == 0 && csCommand.GetAt( csCommand.GetLength() - option.GetLength() - 1 ) == '/' ) {
			return TRUE;
		}
	}		
	return iRgOpt != -1;
}

CUpdateApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUpdateApp initialization

BOOL CUpdateApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

if( IsRequired(this->m_lpCmdLine,"debug") ) {
	myFile.Open("upd.log",CFile::modeCreate|CFile::modeWrite);
	bOpened=TRUE;
}

CString params = this->m_lpCmdLine;

	CObArray oldFiles;
	
		// Unzipping upd.zip file
		//////////////////////////////////
		
		AddLog("\nPROCESSING ZIP FILE\n");
		CZipArchive c;
		try
		{
			try
			{
				c.Open("upd.zip");
			}
			catch (CException * pE)
			{
				AddLog("ERROR: could not open upd.zip");
				pE->Delete();
				c.Close();

				try	{	
					CFile::Remove("upd.zip");
					AddLog("CLEAN: deleting upd.zip");
				}
				catch (CException * pE){
					pE->Delete();
				}
				
				CloseLog();
				return FALSE;
			}
				
			for(WORD i=0;i<c.GetNoEntries();i++)
			{
				CFileHeader h;
				c.GetFileInfo(h, i);				
				CString* oldName=new CString();

				try
				{
					oldName->Format("%s.old",h.m_szFileName);
					CFile::Rename(h.m_szFileName,*oldName);						
					oldFiles.Add((CObject*)oldName);
					AddLog("Renaming %s to %s",h.m_szFileName,*oldName);
				}
				catch (CException * pE)
				{
					pE->Delete();
					delete oldName;
				}
				AddLog("%s extracted",h.m_szFileName);
				c.ExtractFile(i,".");
			}
		}
		catch (CException * pE)
		{
			pE->Delete();
			
		}
		c.Close();
		CFile::Remove("upd.zip");
		AddLog("CLEAN: Deleting upd.zip");

		// Client testing
		//////////////////////////////////

		AddLog("\nCLIENT TESTING\n");
		try
		{
			CFile::Remove("ok.ok");
			AddLog("CLEAN: Deleting ok.ok");
		}
		catch (CException * pE)
		{
			pE->Delete();
		}

		CString cmd,fname;
		fname.Format( _T( "ocsinventory.exe"));
		cmd.Format( _T(" /test %s") ,params) ;
		AddLog("LAUNCH: Launched [%s] with params [%s]",fname,cmd);
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );
		si.cb = sizeof(si);
		ZeroMemory( &pi, sizeof(pi) );
		si.dwFlags=STARTF_USESHOWWINDOW;
		si.wShowWindow=SW_HIDE;
		LPSTR bu = cmd.GetBuffer(0);
		CreateProcess(fname.GetBuffer(0),cmd.GetBuffer(0),NULL, NULL, FALSE, 0, NULL, NULL, &si,&pi );
			
		WaitForInputIdle( pi.hProcess,60000);

		AddLog("OCSInventory.exe launched");
		CFile okTest;
		CFileException pE;

		if(okTest.Open("ok.ok",CFile::modeRead,&pE))//&&agTest.Open("upd.age",CFile::modeRead,&pE2))
		{
			// test file deletion, and old files removal		
			okTest.Close();

			AddLog("The downloaded client is working well");
			CFile::Remove("ok.ok");
			AddLog("CLEAN: Deleting ok.ok");

			for(int k=0;k<oldFiles.GetSize();k++)
			{
				AddLog("CLEAN: Deleting old file %s",*(CString*)oldFiles.ElementAt(k));
				try
				{
					CFile::Remove(*(CString*)oldFiles.ElementAt(k));
				}
				catch (CException * pE)
				{
					pE->Delete();
				}
			}
		}
		else
		{			
			AddLog("ERROR: Downloaded client is not working");			

			for(int k=0;k<oldFiles.GetSize();k++)
			{
				try
				{
					CString nomCourt=*(CString*)oldFiles.ElementAt(k);
					nomCourt=nomCourt.Left(nomCourt.GetLength()-4);
					CFile::Remove(nomCourt);
					CFile::Rename(*(CString*)oldFiles.ElementAt(k),nomCourt);
					AddLog("CLEAN: Deleting %s",nomCourt);
					AddLog("CLEAN: Renaming %s to %s",*(CString*)oldFiles.ElementAt(k),nomCourt);
				}
				catch (CException * pE)
				{
					pE->Delete();
				}
			}
		}	

	for(int j=0;j<oldFiles.GetSize();j++)
			delete (CString*)oldFiles.ElementAt(j);
	
	AddLog("Finished");
	CloseLog();	
	return FALSE;
}
