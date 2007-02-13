// download.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "download.h"
#include "downloadDlg.h"
#include "../include/_common/defines.h"
#include "../include/_common/commonDownload.h"
#include "../include/fileoperations/FileOperations.h"
#include <afxinet.h>
#include "utils.h"
#include "../include/_common/net_utils.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDownloadApp

BEGIN_MESSAGE_MAP(CDownloadApp, CWinApp)
	//{{AFX_MSG_MAP(CDownloadApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDownloadApp construction

CDownloadApp::CDownloadApp()
{
	error = 0;
	m_iProxy	= INTERNET_OPEN_TYPE_PRECONFIG;	
	m_iPort		= DEFAULT_PORT;
	m_csServer	= DEFAULT_SERVER_NAME;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDownloadApp object

CDownloadApp theApp;

BOOL CDownloadApp::InitInstance()
{
    HANDLE hMutexOneInstance = ::CreateMutex( NULL, TRUE,
	 _T("OCSINVENTORY-DOWNLOAD"));

    if ( GetLastError() == ERROR_ALREADY_EXISTS ) {
		return FALSE; // terminates the application
	}
	
	OpenLog("download", AfxGetApp()->m_lpCmdLine);
	
	CString csMessage;
	CTime cStartTime;
	cStartTime = CTime::GetCurrentTime();
	cStartTime.Format( _T( "%Y-%m-%d"));
	csMessage.Format( _T("\nOCS INVENTORY DOWNLOAD ver. %s"),"1");
	AddLog( csMessage);
	AddLog( _T( "Starting on %s...\nCommand line parameters: <<%s>>"),
							   cStartTime.Format( _T( "%#c")),
							   AfxGetApp()->m_lpCmdLine);	

	if( ! SetCurrentDirectory("download") ) {
		AddLog("ERROR: Can't chdir to download folder");		
		finish();
		return 0;
	}

	char direc[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,direc);
	CString serIni;
	serIni.Format("%s\\config.ini",direc);

	while(1) {

		CFile suspend;
		UINT err;
		if( ! suspend.Open("suspend", CFile::modeRead ) ) {
			err = GetLastError();
			if( err != ERROR_FILE_NOT_FOUND ) {
				AddLog("ERROR: Error %i occured while trying to open suspend", err);
			}	
		}
		else  {
			AddLog("WARNING: OCS agent is still running, waiting 10 seconds");
			suspend.Close();
			Sleep(10000);
			continue;
		}

		BOOL end = TRUE;
		clean();
		char buf[255];
		GetPrivateProfileString(OCS_AGENT_KEY, "FragLatency", FRAG_LATENCY_DEFAULT, buf, sizeof(buf), serIni);
		m_csFragLatency = buf;
		if( m_csFragLatency == "0" ) {
			m_csFragLatency = FRAG_LATENCY_DEFAULT;
			AddLog("ERROR: Frag latency can't be zero, it was set to %s", FRAG_LATENCY_DEFAULT);
		}
		GetPrivateProfileString(OCS_AGENT_KEY, "CycleLatency", CYCLE_LATENCY_DEFAULT, buf ,sizeof(buf), serIni);
		m_csCycleLatency = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "PeriodLatency", PERIOD_LATENCY_DEFAULT, buf ,sizeof(buf), serIni);
		m_csPeriodLatency = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "PeriodLength", PERIOD_LENGTH_DEFAULT, buf ,sizeof(buf), serIni);
		m_csPeriodLength = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "Timeout", TIMEOUT_DEFAULT, buf ,sizeof(buf), serIni);
		m_csTimeout = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "On", "0", buf ,sizeof(buf), serIni);
		m_csOn = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "Http_u", "0", buf ,sizeof(buf), serIni);
		m_csHttp_u = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "Http_w", "0", buf ,sizeof(buf), serIni);
		m_csHttp_w = buf;
		
		GetPrivateProfileString(OCS_AGENT_KEY, "DeviceId", "0", buf ,sizeof(buf), serIni);
		m_csDeviceId = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "Server", DEFAULT_SERVER_NAME, buf ,sizeof(buf), serIni);
		m_csServer = buf;
		GetPrivateProfileString(OCS_AGENT_KEY, "Proxy", "err", buf ,sizeof(buf), serIni);
		if( CString(buf) != "err" )
			m_iProxy = atoi(buf);
		GetPrivateProfileString(OCS_AGENT_KEY, "Port", "err", buf ,sizeof(buf), serIni);
		if( CString(buf) != "err" )
			m_iPort = atoi(buf);

		if( m_csOn == "0" ) {
			AddLog("Option turned off, quitting");
			return FALSE;
		}

		HANDLE found;
		LPWIN32_FIND_DATA dataFound;
		WIN32_FIND_DATA dataFoundPile;
		dataFound = &dataFoundPile;
		CString fName;

		if( ( found = FindFirstFile( "*", dataFound) ) == INVALID_HANDLE_VALUE ){
			DWORD parsingError=0;
			if( (parsingError = GetLastError()) != ERROR_NO_MORE_FILES  ){
				AddLog("ERROR: FindFirstFile: %i", parsingError);
				finish();
				ExitProcess(1);
			}
		}

		do {	
			fName = dataFound->cFileName;

			if( ! (dataFound->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || ! isAN(fName) )
				continue;

			// To delay install stage
			if( blackListed( fName ) ) {
				AddLog("Package %s blacklisted...skipping", fName);
				continue;
			}

			AddLog("");
			AddLog("%s directory parsing...", fName);
			
			CString xmlInfo = getFileContent( "info", fName );
			if( xmlInfo == "__ERROR__" ) {
				cleanPackage( fName );
				continue;
			}

			CMarkup xml;
			if( ! xml.SetDoc( xmlInfo ) ) {
				AddLog("\tERROR: Info file %s\\%s is not XML","info", fName);
				cleanPackage( fName );
				continue;
			}
			
			CPackage * pPack = new CPackage(this);
			pPack->fromXml(&xml);
			if( pPack->Id != fName ) {
				AddLog("\tERROR: ID [%s] differs from the directory [%s]",pPack->Id,fName);
				
				if( ! CNetUtils::downloadMessage(ERR_BAD_ID,fName,m_csDeviceId, m_csServer, m_iPort, m_iProxy, m_csHttp_u, m_csHttp_w ))
					cleanPackage( fName );
				delete pPack;
				continue;
			}
			
			CString csSince = getFileContent( "since", fName );
			if( csSince == "__ERROR__" ) {
				delete pPack;
				continue;
			}

			if( ! isAN(csSince) )  {
				AddLog("\tERROR: Since is not a timestamp");
				cleanPackage( fName );
				delete pPack;
				continue;
			}

			DWORD lSince = atol( csSince );
			if( ! lSince ) {
				AddLog("\tERROR: Can't atol since");
				delete pPack;
				continue;
			}

			DWORD lTimeout = atol( m_csTimeout );				
			if( (((float)(time(NULL) - lSince) / 86400)) > ((float)(lTimeout)) ) {
				AddLog("\tERROR: Package timed out (now:%ld, since:%ld, Timeout:%ld)",time(NULL),lSince,lTimeout);
				if( ! CNetUtils::downloadMessage(ERR_TIMEOUT,pPack->Id,m_csDeviceId, m_csServer, m_iPort, m_iProxy, m_csHttp_u, m_csHttp_w) ) {
					cleanPackage( fName );
				}
				delete pPack;
				continue;
			}

			if( (fileExists("task", fName) == 0) || (fileExists("task_done", fName) == 0) ) {
				CString taskPath, taskDonePath;
				taskPath.Format("%s\\task", fName);
				taskDonePath.Format("%s\\task_done", fName);

				CFile task, task_done;
				if( ! task.Open(taskPath, CFile::modeWrite|CFile::modeCreate)) {
					AddLog("\tERROR: Can't create task file (%s)", taskPath);
					delete pPack;
					task.Close();
					continue;
				}
				
				if( pPack->Frags ) {
					for( UINT fcount=1; fcount <= pPack->Frags; fcount++ ) {
						CString fragName;
						fragName.Format("%s-%i\n", fName, fcount);
						task.Write( fragName, fragName.GetLength() );
					}
				}
				task.Close();

				if( ! task_done.Open(taskDonePath, CFile::modeCreate|CFile::modeWrite ) ){
					AddLog("\tERROR: Can't create task_done file (%s)", taskDonePath);
					task_done.Close();
					continue;
				}
				task_done.Close();

			}
			packages.Add(pPack);
			end = FALSE;
		}
		while( FindNextFile(found,dataFound) );

		if( !FindClose( found ) ){
			AddLog("ERROR: FindClose: %i", GetLastError());
			finish();
			ExitProcess(1);
		}
		
		if( end ) {
			AddLog("\nEverything done...");
			break;
		}
		else {
			period( & packages );
		}		
		Sleep(1000);
	}

	finish();
	return FALSE;
}

BOOL CDownloadApp::blackListed( CString fName ){
	return (blacklist.Find( "/" + fName + "/" ) != -1);
}

void CDownloadApp::blackList( CString fName ){
	blacklist += ("/" + fName + "/");
}

BOOL CDownloadApp::isAN( LPCSTR st ) {
	int i;
	for(i=0 ; i<sizeof(st) ; i++) {
		if( st[i] < 48 || st[i] > 57 )
			return FALSE;
	}
	return TRUE;
}

void CDownloadApp::clean() {
	for(int i=0; i<packages.GetSize();i++) {
		CPackage * pC = (CPackage*) packages.GetAt(i);
		delete( pC );
	}
	packages.RemoveAll();
}

BOOL CPackage::fromXml( CMarkup* pX ) {

	char cPath[_MAX_PATH], cCommand[255];
	pX->ResetPos();
	pX->FindElem("DOWNLOAD");

	Id = pX->GetAttrib("ID");
	Pri = atoi( pX->GetAttrib("PRI") );
	Act = pX->GetAttrib("ACT");
	Name = pX->GetAttrib("NAME");
	Digest = pX->GetAttrib("DIGEST");
	Loc = pX->GetAttrib("LOC");
	Proto = pX->GetAttrib("PROTO");
	Frags = atoi( pX->GetAttrib("FRAGS") );
	DigestAlgo = pX->GetAttrib("DIGEST_ALGO");
	DigestEncode = pX->GetAttrib("DIGEST_ENCODE");

	if( !ExpandEnvironmentStrings( pX->GetAttrib("PATH"), cPath, _MAX_PATH )){
		AddLog("ERROR: FromXML: Cannot expand env strings in path. Abort...");
		return FALSE;
	}
	else{
		Path = cPath;
	}
	
	if( !ExpandEnvironmentStrings( pX->GetAttrib("COMMAND"), cCommand, 255 )){
		AddLog("ERROR: FromXML: Cannot expand env strings in command. Abort...");
		return FALSE;
	}
	else{
		Command = cCommand;
	}

	GardeFou = pX->GetAttrib("GARDEFOU");
	
	/* User notification */
	if ( notifyUser = BOOL ( atoi( pX->GetAttrib("NOTIFY_USER") ) ) ) {
		notifyCountdown = atoi( pX->GetAttrib("NOTIFY_COUNTDOWN") );
		notifyText = pX->GetAttrib("NOTIFY_TEXT");
		notifyCanAbort = BOOL ( atoi( pX->GetAttrib("NOTIFY_CAN_ABORT") ) );
		notifyCanDelay = BOOL ( atoi( pX->GetAttrib("NOTIFY_CAN_DELAY") ) );
	}
	if( needDoneAction = BOOL ( atoi( pX->GetAttrib("NEED_DONE_ACTION") ) ) ){
		needDoneActionText = pX->GetAttrib("NEED_DONE_ACTION_TEXT");
	}

	return TRUE;
}


void CDownloadApp::period( CObArray * pC ) {
	
	AddLog("New period nb of cycles:%s", m_csPeriodLength);
	
	CObArray rt;
	int i;

	for(i=0; i<pC->GetSize(); i++) {
		CPackage * pP = (CPackage*)pC->GetAt(i);
		
		if( pP->Pri == 0 )
			rt.Add(pP);
	}
	
	for(i=1; i<=atoi(m_csPeriodLength) ; i++) {
		
		int j;
		//CPackage * pP;
		if( rt.GetSize() ) {
			for( j=0; j < rt.GetSize(); j++ ) {
				CPackage * pP = (CPackage*)rt[j];
				if( blackListed( pP->Id )) 
					continue;
				// highest priority package
				if( rt.GetSize() ) {
					if( fileExists("done", pP->Id ) > 0 ) {
						pP->done();
						AddLog("Now pausing for fragment latency(%s secs)", m_csFragLatency);
						Sleep( atoi(m_csFragLatency) * 1000 );
						continue;
					}
					download( pP );
					AddLog("Now pausing for fragment latency(%s secs)", m_csFragLatency);
					Sleep( atoi(m_csFragLatency) * 1000 );
					continue;
				}
			}
		continue;
		}

		for( j=0; j < pC->GetSize(); j++ ) {
			CPackage * pP = (CPackage*)pC->GetAt(j);
			if( blackListed( pP->Id )) 
					continue;
			//regular priority package
			if( fileExists("done", pP->Id ) > 0 ) {
				pP->done();
				AddLog("Now pausing for fragment latency(%s secs)", m_csFragLatency);
				Sleep( atoi(m_csFragLatency) * 1000 );
				continue;
			}

			if(pP->Pri == 0)
				continue;
			
			if( (i % pP->Pri) != 0 )
				continue;

			download( pP );

			AddLog("Now pausing for fragment latency");
			Sleep( atoi(m_csFragLatency) * 1000 );		
		}
		AddLog("Now pausing for cycle latency(%s secs)", m_csCycleLatency);
		Sleep( atoi(m_csCycleLatency) * 1000 );
	}
	AddLog("Now pausing for period latency(%s secs)", m_csPeriodLatency);
	Sleep( atoi(m_csPeriodLatency) * 1000 );

}

int CDownloadApp::download( CPackage * pP ) {
	CString uri;
	CString taskName, taskTempName;
	taskName.Format("%s\\task", pP->Id);
	taskTempName.Format("%s\\task.tmp", pP->Id);

	//If a .tmp file is present, it replaces the task file
	if( fileExists( "task.tmp", pP->Id ) ) {
		DeleteFile( taskName );
		MoveFile( taskTempName, "task" );
	}

	CString taskCont = getFileContent( "task", pP->Id );
	if( taskCont == "__ERROR__" ) {
		return 1;
	}

	CString currentFrag = taskCont.Left( taskCont.Find("\n") );

	if( currentFrag != "" ) {
		DWORD httpCode;
		CString fragPath;
		fragPath.Format("%s\\%s",pP->Id,currentFrag);
		uri.Format("%s://%s/%s/%s", pP->Proto, pP->Loc, pP->Id, currentFrag);
		
		//assumes URL names have been initialized
		CInternetSession session("download_session");
		CStdioFile* pFile = NULL;
		CFile downloadedFile;
		AddLog("Downloading %s to %s",uri,fragPath);
		//TODO: proxy support
		if( ! downloadedFile.Open(fragPath, CFile::modeCreate|CFile::modeWrite)) {
			AddLog("ERROR: can't open %s for writing", fragPath);
			return 1;
		}

		
		CException * err = new CException;
		try {
			if (! (pFile = session.OpenURL(uri)) ) {
				AddLog("Session opening error while attempting to download %s", uri);
				throw(err);
			}

			if (! ((CHttpFile*)pFile)->QueryInfoStatusCode( httpCode ) ) {
				AddLog("Cannot read http code while attempting to download %s", uri);
				throw(err);
			}
			else {
				if (httpCode != 200) {
					AddLog("Http error while attempting to download: %d", httpCode);
					throw(err);
				}
				else {
					AddLog("Http code (%d)...OK", httpCode);
				}

			}
		

			BYTE szBuff[1024];
			int read;
			while( (read = pFile->Read(szBuff,sizeof(szBuff))) > 0) {
				downloadedFile.Write( szBuff, read );
			}
			pFile->Close();
			delete pFile;			
		}
		catch(CException * e) {
			error++;			
			AddLog("ERROR: In downloading %s",uri);
			Sleep(atoi(m_csFragLatency) * 1000);
			e->Delete();
			downloadedFile.Close();
			if( error > atoi(MAX_ERROR_COUNT) ) {
				AddLog("ERROR: Max error count reached, exiting...");
				finish();
				ExitProcess(1);
			}

			if( pFile){
				pFile->Close();
				delete pFile;
			}
			return 1;
		}
		err->Delete();
		error = 0;
		AddLog("Fragment %s successfully downloaded from %s",fragPath,uri);
		downloadedFile.Close();
		session.Close();

		taskCont = taskCont.Right( taskCont.GetLength() - taskCont.Find("\n") - 1 );
		CopyFile( taskName, taskTempName, FALSE);
		CFile taskFile;
		if( ! taskFile.Open( taskName, CFile::modeWrite|CFile::modeCreate ) ) {
			AddLog("ERROR: Can't open %s", taskName);
			return 1;
		}
		taskFile.Write( taskCont, taskCont.GetLength() );
		taskFile.Close();
		DeleteFile( taskTempName );
	}
	else {
		AddLog("File %s successfully downloaded, executing package",pP->Id);
		int errExec = pP->execute();
		
		if( errExec ) {
			// if errExec == 2 no setcurrentdirectory was previously done, we do not need to chdir back to ..\..
			if( errExec != 2 &&  errExec != 3  &&  errExec != 4 &&  errExec != 6)
				if( ! SetCurrentDirectory("..\\..") ) {
					AddLog("ERROR: Can't chdir to ..\\..");
					finish();
					ExitProcess(1);
				} 
		
			//4 = user aborted process
			if( errExec == 4 ) {
				if( ! CNetUtils::downloadMessage(ERR_ABORTED,pP->Id,m_csDeviceId, m_csServer, m_iPort, m_iProxy, m_csHttp_u, m_csHttp_w) ) {
					cleanPackage(pP->Id);
				}
				return 1;
			}
			//5 = program returned an error value
			else if( errExec == 5 ) {
				pP->done(FALSE);
				return 0;
			}
			//6 = install has been canceled
			else if( errExec == 6 ) {
				AddLog("Package %s delayed (will process it next time)", pP->Id);
				blackList(pP->Id);
				return 0;
			}
			//3 = Bad digest (have not changed directory yet)
			else if( errExec == 3 ) {
				cleanPackage(pP->Id);
				return 1;
			}

			if( ! CNetUtils::downloadMessage(ERR_EXECUTE,pP->Id,m_csDeviceId, m_csServer, m_iPort, m_iProxy, m_csHttp_u, m_csHttp_w)) {
				cleanPackage(pP->Id);
			}
			return 1;
		}

		else {
			if( ! SetCurrentDirectory("..\\..") ) {
				AddLog("ERROR: Can't chdir to ..\\..");
				finish();
				ExitProcess(1);
			}
			pP->done();
		}
	}
	return 0;
}

int CPackage::execute() {
	
	AddLog("Executing orders for package %s", Id);

	UINT msgType, notifyRet;
	
	/* Popup the message if there is a user notification */
	if( notifyUser ) {
		/* If canAbort, the user can cancel execute process */
		if ( notifyCanAbort )
			msgType = MB_OKCANCEL;
		else
			msgType = MB_OK;
	
		CDownloadDlg dlg;
		dlg.canAbort = notifyCanAbort;
		dlg.notifyCountdown = notifyCountdown;
		dlg.m_Edit = notifyText;
		dlg.canDelay = notifyCanDelay;
		
		notifyRet = dlg.DoModal();
		
		if ( notifyRet == IDCANCEL) {
			CNetUtils::downloadMessage(ERR_ABORTED, Id ,pA->m_csDeviceId, pA->m_csServer, pA->m_iPort, pA->m_iProxy, pA->m_csHttp_u, pA->m_csHttp_w);
			return 4;
		}
		else if ( notifyRet == IDOK && dlg.delayed == TRUE ) {
			return 6;

		}
		
	}
	
	int errCode = 0;
	if( errCode = buildPackage() ) {
		return errCode;
	}
	else {
		CString tmpPath;
		tmpPath.Format("%s\\tmp", Id );
		if( ! SetCurrentDirectory(tmpPath) ) {
			AddLog( "ERROR: Can't chdir to %s", tmpPath);
			((CDownloadApp*)AfxGetApp())->finish();
			ExitProcess(1);
		}

		//createRestorePoint(Id);
	
		if( Act == "LAUNCH" ) {
			if ( Frags )
				if( unzip( "build.zip", "." ) ) {
					return 1;
				}
			
			if( !Name.GetLength() ) {
				AddLog("ERROR: No Name for a LAUNCH action");
				return 1;
			}

			if( !fileExists( "..\\..\\..\\inst32.exe" ) ) {
				AddLog("ERROR: Cannot find launcher...execute stage aborted");
				return 1;
			}

			AddLog("LAUNCH: Launching %s",Name);
			
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory( &si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );

			si.wShowWindow = SW_HIDE;

			si.dwFlags=STARTF_USESHOWWINDOW;
			CString commandLine = "..\\..\\..\\inst32.exe /exe:" + CString("\"") + Name + CString("\"") + " /log:instlog.txt";

			if( ! CreateProcess( NULL, commandLine.GetBuffer(0), NULL, NULL, TRUE, 0, NULL, NULL, &si,&pi )) {
				AddLog("ERROR: Error %d occured while running %s", GetLastError(), Name);
				return 1;
			}
			
			if( WaitForSingleObject( pi.hProcess, INFINITE ) ){
				AddLog("ERROR: while waiting for %s (error %s)", Name, GetLastError());
			}

			if( needDoneAction ){
				AfxMessageBox( needDoneActionText.GetBuffer( NULL ) , MB_OK|MB_ICONINFORMATION|MB_SYSTEMMODAL, 0);
			}
			
			DWORD exitCode;
			if ( ! GetExitCodeProcess( pi.hProcess , &exitCode ) ) {
				AddLog("ERROR: Cannot get the return status");
				return 0;
			}
			else {
				AddLog("Launcher returned %i code", exitCode);
				if( exitCode != INST32_OK_CODE ){
					CString csExitCode;
					ltoa(exitCode, csExitCode.GetBuffer(NULL), 10);
					csExitCode.Format("%s_%s", ERR_EXECUTE, csExitCode.GetBuffer(NULL));
					CNetUtils::downloadMessage( csExitCode, Id, pA->m_csDeviceId, pA->m_csServer, pA->m_iPort, pA->m_iProxy, pA->m_csHttp_u, pA->m_csHttp_w);	
					return 5;
				}
				//CString code;
				CNetUtils::downloadMessage( CODE_SUCCESS, Id, pA->m_csDeviceId, pA->m_csServer, pA->m_iPort, pA->m_iProxy, pA->m_csHttp_u, pA->m_csHttp_w);	
				return 5;
			}

		}
		else if( Act == "EXECUTE" ) {
			if( !Command.GetLength() ) {
				AddLog("ERROR: No Command for an EXECUTE action");
				return 1;
			}
			AddLog("EXECUTE: Executing command: %s",Command);
			if ( Frags )
				if( unzip( "build.zip", "." ) ) {
					return 1;
				}
			//system("..\\..\\run.bat "+Command);
			system( Command );
			
			if( needDoneAction ){
				AfxMessageBox( needDoneActionText.GetBuffer( NULL ) , MB_OK|MB_ICONINFORMATION|MB_SYSTEMMODAL, 0);
			}

			if( errno ) {
				AddLog("ERROR: Error occured while running %s: %s", Name, strerror(errno));
				return 1;
			}
		}
		else if( Act == "STORE" ) {
			AddLog("STORE: Storing in: %s",Path);

			Path.Replace( "/", "\\" );
			
			if( !Path.GetLength() ) {
				AddLog("ERROR: No Path for a STORE action");
				return 1;
			}

			if( Path[0] == '\\' )
				Path = Path.Right( Path.GetLength() -1 );

			Path.Replace( "INSTALL_PATH", "..\\.." );

			// Windows path must begin with ..\ or x:\ , else we are copying directory in itself
			if( Path.Left(3) != "..\\" && Path.Mid(1,2) != ":\\" ) {
				AddLog("ERROR: Can't store in tmp folder");
				return 1;
			}

			// trying to bypass previous checkings
			if( Path.Left(6) == "..\\tmp" ) {
				AddLog("ERROR: Can't store in tmp folder");
				return 1;
			}
			
			char seps[]   = "\\/";			
			char* token;
			CString tokenize = Path;
			token = strtok( tokenize.GetBuffer(0), seps );
			CString concat = token;

			while( token != NULL ) {
				if( ! CreateDirectory( concat, NULL ) ) {
					AddLog("Directory %s already exists", token);
				}
				token = strtok( NULL, seps );
				concat += CString("\\") + token ;
			}

			/*CFileOperation cf;
			cf.SetOverwriteMode( true );
			if( ! cf.Copy( ".", Path) ) {
				AddLog("ERROR: move of %s to %s failed with error:\n\t\t\t[%s]", Id, Path, cf.GetErrorString());
				return 1;
			}*/

			delete token;
			
			if( unzip( "build.zip", Path )) {
				return 1;
			}
			if( needDoneAction ){
				AfxMessageBox( needDoneActionText.GetBuffer( NULL ) , MB_OK|MB_ICONINFORMATION|MB_SYSTEMMODAL, 0);
			}
		}	
	}

	return 0;
}

void CDownloadApp::finish() {
	clean();
	//END//
	if (hMutexOneInstance != NULL) {
        ::ReleaseMutex(hMutexOneInstance);
    }
	
	AddLog("End of work");
	CloseLog();
	///ExitProcess(1);
}

void CPackage::done(BOOL needToSendSuccess) {
	
	CFile done;
	if( done.Open( Id + "\\done", CFile::modeCreate|CFile::modeWrite )) {
		done.Close();
	}
	else {
		AddLog("ERROR: Can't create done (%s), error %i", Id + "\\done", GetLastError());
	}

	CStdioFile history;
	if (history.Open("history", CFile::modeWrite|CFile::modeNoTruncate)){
		history.SeekToEnd();
		history.WriteString( Id + "\n" );
		history.Close();
	}
	else{
		AddLog("ERROR: Cannot open history file\n");
	}
	
	if (needToSendSuccess) {
		AddLog("Package %s done, sending message", Id);
		if( ! CNetUtils::downloadMessage( CODE_SUCCESS, Id ,pA->m_csDeviceId, pA->m_csServer, pA->m_iPort, pA->m_iProxy, pA->m_csHttp_u, pA->m_csHttp_w)) {
			cleanPackage( Id );
		}
	}
	else {
		AddLog("Package %s done, will not sending message", Id);
		cleanPackage( Id );
	}
}

int CPackage::buildPackage() {
	AddLog("Building package %s", Id);
	CString tmpPath;
	tmpPath.Format("%s\\tmp", Id);
	if( ! CreateDirectory( tmpPath, NULL ) ) {
		if ( GetLastError() != ERROR_ALREADY_EXISTS ) {
			AddLog("ERROR: can't create %s\\tmp directory", Id);
			return 2;
		}
		else {
			AddLog("Will not create %s\\tmp directory, it already exists", Id);
		}
	}

	if( ! Frags )
		return 0;

	CFile zipArchive, curFrag;
	char pt[10];
	zipArchive.Open(tmpPath + "\\build.zip", CFile::modeWrite|CFile::modeCreate);
	for( UINT i = 1; i <= Frags; i++ ) {
		if( ! fileExists( Id + "-" + itoa(i,pt,10), Id )) {
			AddLog("ERROR: File %s\\%s is missing", Id, Id + "-" + itoa(i,pt,10));
			return 2;
		}

		if( ! curFrag.Open( Id + "\\"+ Id + "-" + itoa(i,pt,10), CFile::modeRead)) {
			AddLog("ERROR: Can't open %s\\%s for reading", Id, Id + "-" + itoa(i,pt,10));
			return 2;
		}
		UINT len = curFrag.GetLength();
		BYTE * buf = new BYTE[ len ];
		curFrag.Read( buf, len );
		zipArchive.Write( buf, len );
		curFrag.Close();
		delete [] buf;
	}
	
	zipArchive.Close();	

	if( checkSignature() ) {
		CNetUtils::downloadMessage(ERR_BAD_DIGEST,Id,pA->m_csDeviceId, pA->m_csServer, pA->m_iPort, pA->m_iProxy, pA->m_csHttp_u, pA->m_csHttp_w);
		return 3;
	}
	
	AddLog("Building of %s OK", Id);
	return 0;
}

int CPackage::checkSignature() {

	BOOL base64 = FALSE;
	if( ! DigestEncode.CompareNoCase("base64") ) {
		base64 = TRUE;
		AddLog("Digest format:%s recognized as base64", DigestEncode);
	}
	else if( ! DigestEncode.CompareNoCase("hexa") ) {
		AddLog("Digest format:%s recognized as hexadecimal", DigestEncode);
	}
	else {
		AddLog("ERROR: Digest format:%s not supported", DigestEncode);
		return 1;
	}

	CString algo;
	if( ! DigestAlgo.CompareNoCase("md5") ) {
		algo = "md5";
		AddLog("Digest algo: md5");
	}
	else if( ! DigestAlgo.CompareNoCase("sha1") ) {
		algo = "sha1";
		AddLog("Digest algo: sha1");
	}
	else {	
		AddLog("ERROR: Digest algo:%s not supported", DigestAlgo);
		return 1;
	}

	UINT olen;
	unsigned char *pDigest=NULL;
	CString hash;

	// Compute the digest
	if( simple_digest( algo.GetBuffer(0), Id+"\\tmp\\build.zip", &olen, &pDigest) == 0 ) {
		// Encode it, either base 64 or hexadecimal form
		if( base64 )
			hash = base64_encode (pDigest, olen );
		else
			hash = print_hex (pDigest, olen );

		// Freeing binary digest...
		free(pDigest);
			
		if( hash.Compare(Digest) == 0 ) {
			AddLog("Package hash (%s) OK", Digest );
		}
		else {
			AddLog("ERROR: Package hash (%s) differs from file hash (%s)", Digest, hash );
			return 1;
		}
		return 0;
	}
	else {
		return 1;
	}
}

/*

*/
/*
void CDownloadApp::cleanId( CString Id ) {
	for( j=0; j < packages.GetSize(); j++ ) {
		CPackage * pP = packages[j];
		if( pP->Id == Id ) {
			delete pP;
			packages.RemoveAt(j);
			break;
		}

	}
}*/




