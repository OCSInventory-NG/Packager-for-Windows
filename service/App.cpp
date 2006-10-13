#include "stdafx.h"
#include "ntserv_msg.h"
#include "ntservEventLog.h"
#include "app.h"
#include "direct.h"
#include <openssl/rand.h>
#include <openssl/aes.h>
#include <openssl/sha.h>
#include "../include/_common/base64.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//The one and only one application
CApp theApp;


BEGIN_MESSAGE_MAP(CApp, CWinApp)
	//{{AFX_MSG_MAP(CApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CApp::CApp()
{
  m_dwExitCode = ERROR_SUCCESS;
}

#ifdef _DEBUG
BOOL CALLBACK EnumServices(DWORD /*dwData*/, ENUM_SERVICE_STATUS& Service)
#else
BOOL CALLBACK EnumServices(DWORD /*dwData*/, ENUM_SERVICE_STATUS& /*Service*/)
#endif
{
#ifdef _DEBUG
  TRACE(_T("Service name is %s\n"), Service.lpServiceName);
  TRACE(_T("Friendly name is %s\n"), Service.lpDisplayName);
#endif

  return TRUE; //continue enumeration
}

BOOL CApp::InitInstance()
{
	//All that is required to get the service up and running
	CNTServiceCommandLineInfo cmdInfo;
	CMyService Service;
	//Service.SetDisplayName("mu");
	Service.SetAllowCommandLine(TRUE);
	Service.SetAllowNameChange(TRUE);       
	Service.SetAllowDescriptionChange(TRUE);
	Service.SetAllowDisplayNameChange(TRUE);

	// Défini les interactions utilisateur
	Service.m_dwServiceType = SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS;


	//	Service.SetControlsAccepted(0); //peut plus etre arrété/redemarré par le ctrl panel

	Service.m_dwStartType = SERVICE_AUTO_START;
	Service.m_dwErrorControl = SERVICE_ERROR_IGNORE;
	//Uncomment the following code to setup the service with different requirements
	Service.ParseCommandLine(cmdInfo);
	m_dwExitCode = Service.ProcessShellCommand(cmdInfo);

	return FALSE;
}

int CApp::ExitInstance()
{
	//Call the base class
	CWinApp::ExitInstance();

	//Return the error code as reported by the service framework
	return (int) m_dwExitCode;
}

CMyService::CMyService() : CNTService(_T("OCS INVENTORY"), _T("OCS INVENTORY SERVICE"), SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE, _T("Automatic inventory and software deployment system")) 
{
	m_bWantStop = FALSE;     //Simple boolean which is set to request the service to stop
}

CMyService::~CMyService() 
{
}

void CMyService::preInit() {

	char direc[_MAX_PATH+1];
	char retrn[4][_MAX_PATH+1];
	char paths[2][_MAX_PATH+1];

		/*****
	 *
	 *	Checks wether another instance of ocsservice.exe is 
	 *	already running. (win98 and win95 in debug mode)
	 *
	 ****/
    ::CreateMutex( NULL, TRUE, _T("OCSSERVICE-088FA840-B10D-11D3-BC36-006067709674") );
	int Err = GetLastError();
	if ( Err == ERROR_ALREADY_EXISTS || Err == ERROR_ACCESS_DENIED ) {

	    ExitProcess(0); // terminates the application
	}

	//GetCurrentDirectory(MAX_PATH,direc);
	GetModuleFileName(NULL, direc, _MAX_PATH );
	_splitpath( direc, retrn[0], retrn[1], retrn[2], retrn[3] );
	_makepath( paths[0], retrn[0], retrn[1], NULL, NULL );
	_makepath( paths[1], retrn[0], retrn[1], SERVICE_NME, SERVICE_EXT );
	m_sCurDir = paths[0];
	m_sServIni = paths[1];

	_chdir( m_sCurDir.GetBuffer(0) );

	// no service.ini file
	if( ! openIni() ) {
		m_iPrologFreq = DEFAULT_PROLOG_FREQ;
		m_iOldPrologFreq = DEFAULT_PROLOG_FREQ;
		m_iTToWait = generateRandNumber(DEFAULT_PROLOG_FREQ * PROLOG_FREQ_UNIT);
		writeIniFile();			
	}
	else {
		closeIni();
		readIniFile();
		if( m_iPrologFreq <= 0 )
			m_iPrologFreq = DEFAULT_PROLOG_FREQ;

		if( m_iPrologFreq != m_iOldPrologFreq ) {
			m_iTToWait = generateRandNumber(m_iPrologFreq*PROLOG_FREQ_UNIT);
			m_iOldPrologFreq = m_iPrologFreq;
			writeIniFile();
		}
	}
}

void CMyService::ServiceMain(DWORD /*dwArgc*/, LPTSTR* /*lpszArgv*/)
{	
	//Pretend that starting up takes some time
	ReportStatus(SERVICE_START_PENDING, 1, 1100);
	Sleep(1000);
	ReportStatus(SERVICE_RUNNING);

	preInit();

	openHandles();	
	
	CString status;
	status.Format("Service started successfully with parameters FREQ: %i, OLD_FREQ: %i, TTO_WAIT: %i", m_iPrologFreq, m_iOldPrologFreq, m_iTToWait);
	m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, MSG_INFO_OCS, status);

	while (!m_bWantStop) {
		
		if( m_iTToWait % (m_iWriteIniLatency?m_iWriteIniLatency:WRITE_TTOWAIT_EACH) == 0 ) 
			writeIniFile(& m_iTToWait, TTO_WAIT );

		if( m_iTToWait <= 0 ) {
			UINT vOld = m_iOldPrologFreq;
			closeHandles();
			//closeIni();
			runAgent();
			//openIni();
			openHandles();
			readIniFile( OCS_SERVICE, & m_iPrologFreq, PROLOG_FREQ );

			if( m_iPrologFreq != m_iOldPrologFreq )
				m_iTToWait = generateRandNumber(m_iPrologFreq*PROLOG_FREQ_UNIT);			
			else
				m_iTToWait = m_iPrologFreq*PROLOG_FREQ_UNIT;

			m_iOldPrologFreq = m_iPrologFreq;
			writeIniFile();

			status.Format("Service lauched OCS. New parameters: FREQ: %i, OLD_FREQ: %i, TTO_WAIT: %i", m_iPrologFreq, vOld, m_iTToWait);
			m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, MSG_INFO_OCS, status);
		}
		Sleep(1000);
		m_iTToWait--;
	}

	//Pretend that closing down takes some time
	ReportStatus(SERVICE_STOP_PENDING, 1, 1100);
	Sleep(1000);

	//Report to the event log that the service has stopped successfully
	m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, CNTS_MSG_SERVICE_STOPPED, m_sDisplayName);
	closeHandles();
}

void CMyService::OnStop()
{
	//Signal the other thread to end via the boolean variable
	InterlockedExchange((LONG volatile*) &m_bWantStop, TRUE);
}

void CMyService::runAgent() {
	//RUN inventory !
	CString cmd,
			csAuth;
	
	Sleep( generateRandNumber(m_iWriteIniLatency?m_iWriteIniLatency:WRITE_TTOWAIT_EACH) );

	// Check if Basic authentication required
	csAuth.Empty();
	if (!m_csAuthUser.IsEmpty())
	{
		CString csUser, csPwd;

		Decrypt( m_csAuthUser, csUser);
		Decrypt( m_csAuthPwd, csPwd);
		csAuth.Format( _T( " /auth_user:%s /auth_pwd:%s"), csUser, csPwd);
	}
	//cmd.Format("%s%s /server:%s /port:%s%s", m_sCurDir, RUN_OCS, m_csServer, m_csPort, (m_iProxy?"":" /np") );
	cmd.Format("%s%s %s %s", m_sCurDir, RUN_OCS, m_csMisc, csAuth );
	//AfxMessageBox("INVENTAIRE!");
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );

	si.dwFlags=STARTF_USESHOWWINDOW;
	si.wShowWindow=SW_SHOW;
	DWORD waitRet;
	if( ! CreateProcess( NULL, cmd.GetBuffer(0), NULL, NULL, FALSE,0/*CREATE_DEFAULT_ERROR_MODE|IDLE_PRIORITY_CLASS*/, NULL, NULL, &si,&pi )) {
		CString errString;
		errString.Format("Cant't launch OCS Agent, error:%d",GetLastError());
		m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, errString);
	}
	/*else if( (waitRet = WaitForSingleObject( pi.hProcess, 30000 )) == WAIT_TIMEOUT ) {
		m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, "OCS agent timeout !");
	}*/
	//waitRet = WaitForMultipleObjects(1, &pi.hProcess,TRUE, 30000 );
	waitRet = WaitForSingleObject( pi.hProcess, INFINITE );
}

int CMyService::generateRandNumber(int max) {
	
	CString namePath;
	namePath.Format("%s%s", m_sCurDir, RAND_FILE);
	
	RAND_write_file(namePath.GetBuffer(0));
	BYTE* randBuf= new BYTE[sizeof(UINT)];
	CFile fRand;
	CFileException e;

	BOOL errorOccured = FALSE;
	while( ! fRand.Open(namePath, CFile::modeRead,&e) ) {		
		if( ! ( e.m_cause == CFileException::sharingViolation) ) {
			m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, "Can't open rand file, will seed with timestamp.");
			errorOccured = TRUE;
			break;
		}		
	}

	if( ! errorOccured ) {
		fRand.Read( randBuf, 4);
		fRand.Close();
		CFile::Remove(namePath);
		UINT dest;
		memcpy( &dest, randBuf, sizeof(UINT));
		srand(dest);
	}
	else {
		srand ( UINT (time(NULL)) );
	}
	delete [] randBuf;
	return UINT((max*rand())/RAND_MAX);
}

void CMyService::readIniFile( CString section, int* storeVar, CString toRead, CString def ) {
	
	if( storeVar != NULL){
		//closeIni(); TODO: voir
		char intRead[11];

		if( ! GetPrivateProfileString(section, toRead, def,  intRead, 11, m_sServIni)) {
			m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, "Can't get private profile string");
		}

		*storeVar = atoi(intRead);
		//openIni(); TODO: voir
	}
	else {	
		readIniFile( OCS_SERVICE, & m_iPrologFreq, PROLOG_FREQ, "10" );
		readIniFile( OCS_SERVICE, & m_iOldPrologFreq, OLD_PROLOG_FREQ, "0" );
		readIniFile( OCS_SERVICE, & m_iTToWait, TTO_WAIT, "-1" );

		readIniFile( OCS_SERVICE, m_csServer, "SERVER", "ocsinventory-ng" );
		readIniFile( OCS_SERVICE, & m_iProxy, "NOPROXY", "0" );
		readIniFile( OCS_SERVICE, m_csPort, "port", "80" );
		readIniFile( OCS_SERVICE, m_csMisc, "MISCELLANEOUS", "" );
		readIniFile( OCS_SERVICE, & m_iWriteIniLatency, "WRITE_INI_LATENCY", WRITE_TTOWAIT_EACH );
		readIniFile( OCS_SERVICE, m_csAuthUser, AUTH_USER, "" );
		readIniFile( OCS_SERVICE, m_csAuthPwd, AUTH_PWD, "" );
		readIniFile( OCS_SERVICE, m_csProxyHost, PROXY_HOST, "" );
		readIniFile( OCS_SERVICE, m_csProxyPort, PROXY_PORT, "" );
		readIniFile( OCS_SERVICE, m_csProxyUser, PROXY_USER, "" );
		readIniFile( OCS_SERVICE, m_csProxyPwd, PROXY_PWD, "" );
	}	
}

void CMyService::readIniFile( CString section, CString & storeVar, CString toRead, CString defaultVal ) {
	
	//closeIni(); TODO: voir
	char read[255];

	if( ! GetPrivateProfileString(section, toRead, defaultVal,  read, 255, m_sServIni)) {
		m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, "Can't get private profile string");
		storeVar = defaultVal;
	}
	else
		storeVar = read;
	//openIni(); TODO: voir		
}

void CMyService::writeIniFile( int* toBeStored, CString toWrite ) {
	
	if( toBeStored != NULL){
		//closeIni();
		char intWrite[11];
		_itoa( *toBeStored, intWrite, 10 );
		if( ! WritePrivateProfileString(OCS_SERVICE, toWrite, intWrite, m_sServIni)) {
			m_EventLogSource.Report(EVENTLOG_ERROR_TYPE, MSG_ERROR_OCS, "Can't write private profile string");
		}
		//openIni();
	}
	else {	
		writeIniFile( & m_iPrologFreq, PROLOG_FREQ );
		writeIniFile( & m_iOldPrologFreq, OLD_PROLOG_FREQ );
		writeIniFile( & m_iTToWait, TTO_WAIT );
	}
}

void CMyService::openHandles() {
	return;//TODO: voir
	addOpenFile( "ocsinventory.exe");
	addOpenFile( "last_state");
	addOpenFile( "libeay.dll");
	addOpenFile( "ocswmi.dll");
	addOpenFile( "sysinfo.dll");
	addOpenFile( "last_state");
	addOpenFile( "ocsinventory.dat");
	addOpenFile( "admininfo.conf");
	addOpenFile( "update.exe");
	addOpenFile( "mfc42.dll");
}

void CMyService::closeHandles() {
	return;//TODO: voir
	for( int cptHandle=0; cptHandle < m_tHandles.GetSize(); cptHandle++) {
		CFile * pFile = ((CFile*)m_tHandles.GetAt(cptHandle));
		//pFile->Close();
		delete( pFile );		
	}
	m_tHandles.RemoveAll();
}

void CMyService::addOpenFile( LPCSTR fname ) {
	CString fnamedir;
	fnamedir.Format("%s%s",m_sCurDir,fname);
	CFile* newFile=new CFile();
	newFile->Open(fnamedir, CFile::shareExclusive|CFile::modeReadWrite);
	m_tHandles.Add( newFile );
}

BOOL CMyService::openIni() {
	return m_fServiceIni.Open(m_sServIni, /*CFile::shareExclusive|*/CFile::modeReadWrite);
}

void  CMyService::closeIni() {
	if( m_fServiceIni.m_hFile != (UINT)m_fServiceIni.hFileNull )
		m_fServiceIni.Close();
}

CString CMyService::getParamValue(LPCTSTR lpstrCommandLine, CString param) {
	
	CString	csCommand = lpstrCommandLine;
	CString option;

	option.Format("%s:",param);
	
	csCommand.MakeLower();
	int iRngOpt = csCommand.Find( _T( option));
	if( iRngOpt == -1 ) {
			return "";
	}
	
	int iFin = csCommand.Find(" ", iRngOpt) != -1 ? csCommand.Find( " ", iRngOpt) : csCommand.GetLength();
	CString csName = csCommand.Mid( iRngOpt + option.GetLength() , iFin - iRngOpt - option.GetLength() );
	return csName;
}

BOOL CMyService::Install(CString &sErrorMsg, DWORD &dwError)
{
	char direc[_MAX_PATH+1];
	char retrn[4][_MAX_PATH+1];
	char paths[2][_MAX_PATH+1];
	CString csCrypt;
	// First, isntall service
	BOOL bReturn = CNTService::Install( sErrorMsg, dwError);

	// Next, store encrypted user and passwd if needed
	GetModuleFileName(NULL, direc, _MAX_PATH );
	_splitpath( direc, retrn[0], retrn[1], retrn[2], retrn[3] );
	_makepath( paths[0], retrn[0], retrn[1], NULL, NULL );
	_makepath( paths[1], retrn[0], retrn[1], SERVICE_NME, SERVICE_EXT );
	m_sCurDir = paths[0];
	m_sServIni = paths[1];
	m_csAuthUser = getParamValue( AfxGetApp()->m_lpCmdLine, AUTH_USER);
	m_csAuthPwd = getParamValue( AfxGetApp()->m_lpCmdLine, AUTH_PWD);

	if (!m_csAuthUser.IsEmpty())
	{
		// Encrypt Basic Authentication user and password
		if (Encrypt( m_csAuthUser, csCrypt))
			m_csAuthUser = csCrypt;
		WritePrivateProfileString(OCS_SERVICE, AUTH_USER, csCrypt, m_sServIni);
		if (Encrypt( m_csAuthPwd, csCrypt))
			m_csAuthPwd = csCrypt;
		WritePrivateProfileString(OCS_SERVICE, AUTH_PWD, csCrypt, m_sServIni);
	}

	return bReturn;
}


BOOL CMyService::Encrypt(CString &csClear, CString &csCrypted)
{
	unsigned char	plainKey[17];
	unsigned char	aesKey[33];
	AES_KEY			ekey;
	char			szClear[17];
	char			szCrypt[17];
	CString			csTemp;
	char			*szB64 = NULL;

	_tcsncpy( szClear, csClear, 16);
	memset( szCrypt, 0, 17);
	memset( plainKey, 0, 17);
	// Generate encrypt key
	memcpy( plainKey, OCS_SERVICE, sizeof( OCS_SERVICE)); 
	SHA256( (const unsigned char *)plainKey, 16, aesKey);
	AES_set_encrypt_key((const unsigned char*) aesKey, 256, &ekey);
	// Encrypt value
	AES_encrypt((const unsigned char*)szClear, (unsigned char*)szCrypt, &ekey);
	// Transform to encrypted value to base64
	csCrypted.Empty();
	size_t outlen = base64_encode_alloc( szCrypt, 16, &szB64);
	if (szB64 == NULL && outlen == 0)
		return FALSE;
	if (szB64 == NULL)
		return FALSE;
	csCrypted = szB64;
	free( szB64);
	return TRUE;
}

BOOL CMyService::Decrypt(CString &csCrypted, CString &csClear)
{
	// Generate decrypt key
	unsigned char	plainKey[17];
	unsigned char	aesKey[33];
	AES_KEY			dkey;
	char			*szCrypt = NULL;
	char			szClear[17];
	unsigned int	outlen;

	// Generate decrypt key
	memset( szClear, 0, 17);
	memset( plainKey, 0, 17);
	memcpy( plainKey, OCS_SERVICE, sizeof( OCS_SERVICE)); 
	SHA256( (const unsigned char *)plainKey, 16, aesKey);
	AES_set_decrypt_key((const unsigned char*) aesKey, 256, &dkey);
	// Convert base64 encrypted pwd to unsigned char
	if (!base64_decode_alloc ( LPCTSTR( csCrypted), csCrypted.GetLength(), &szCrypt, &outlen))
		return FALSE;
	if (szCrypt == NULL)
		return FALSE;
	AES_decrypt((const unsigned char*)szCrypt, (unsigned char*)szClear, &dkey);
	free( szCrypt);
	csClear = szClear;
	return TRUE;
}
