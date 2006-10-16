
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleDownload.cpp: implementation of the CModuleDownload class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "ocsinventory.h"
#include "ModuleDownload.h"
#include "../include/_common/utils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CModuleDownload::CModuleDownload(CString commandLine,CDeviceProperties * pC, CString serv, UINT prox, INTERNET_PORT port, CString http_u, CString http_w ) : CModuleApi( commandLine, pC, serv, prox, port, http_u, http_w )
{
}

CModuleDownload::~CModuleDownload()
{
	int i = 0;
	while(i < m_tPackages.GetSize())
	{
		delete m_tPackages[i];
		i++;
	}	
}

int CModuleDownload::response(CMarkup* pXml, CString* pRawResponse) {
	
	if( ! CUtils::isActivatedOption(*pXml,"DOWNLOAD") )
		return (1);
	
	DWORD ErrorNum;

	/* Create working directory */
	if ( CreateDirectory ( "download", NULL ) == FALSE) {
		if ( ( ErrorNum = GetLastError() ) == ERROR_ALREADY_EXISTS) {
			AddLog("DOWNLOAD: Working directory already exists\n");
		}
		else {
			AddLog("ERROR: DOWNLOAD: Cannot create working directory (%i)\n", ErrorNum);
			return(1);
		}
	}

	/* trying to create suspend file */
	CFile suspend;
	if( ! suspend.Open("download\\suspend", CFile::modeCreate | CFile::modeWrite ) ) {
		AddLog("ERROR: DOWNLOAD: Cannot create suspend file\n");
		return(1);
	}
	suspend.Close();

	/* Trying to open lock file */
	CFile lock;
	if (! lock.Open("download\\lock", CFile::modeCreate|CFile::modeNoTruncate|CFile::shareExclusive) ) {
		AddLog("ERROR: DOWNLOAD: Cannot create/open lock file (%i)\n", GetLastError());	
		try{ CFile::Remove("download\\suspend"); } catch(CException *e) { e->Delete();}
		return(1);
	}

	/* Create history file if needed */
	CFile history;
	if (! history.Open("download\\history", CFile::modeCreate|CFile::modeRead|CFile::modeNoTruncate|CFile::shareExclusive) ) {
		AddLog("ERROR: DOWNLOAD: Cannot create history file\n");
		try{ CFile::Remove("download\\suspend"); } catch(CException *e) { e->Delete();}
		return(1);
	}

	CString csCertFile, csId, csLoc, csType, TmpValue;
	CMapStringToString* pmType=NULL;
	CMapStringToString* pmRecup=NULL;
	COptDownloadPackage* pOptDownloadPackage;

	int cmpt = 1;
	do 
	{
		CUtils::cleanCm(pmType);
		CUtils::cleanCm(pmRecup);
		
		pmType = CUtils::getOptionAttributes(*pXml,cmpt,"DOWNLOAD","TYPE", "");
		
		if ( pmType->GetCount() == 0 )
			break;

		pmType->Lookup("TYPE",csType);
		if( !(csType.CompareNoCase("CONF")) ) {
			pmRecup = CUtils::getOptionAttributes(*pXml,cmpt, "DOWNLOAD", 
				"FRAG_LATENCY", "PERIOD_LATENCY", "CYCLE_LATENCY", 
				"PERIOD_LENGTH", "TIMEOUT", "ON", "");
			pmRecup->Lookup("FRAG_LATENCY", m_csDownloadFragLatency);
			pmRecup->Lookup("CYCLE_LATENCY", m_csDownloadCycleLatency);
			pmRecup->Lookup("PERIOD_LATENCY", m_csDownloadPeriodLatency);
			pmRecup->Lookup("PERIOD_LENGTH", m_csDownloadPeriodLength);
			pmRecup->Lookup("TIMEOUT", m_csDownloadTimeout);
			pmRecup->Lookup("ON", m_csDownloadOn);
			configToFile();
		}
		else if( ! csType.CompareNoCase("PACK") ) {
			pmRecup = CUtils::getOptionAttributes(*pXml,cmpt,"DOWNLOAD","ID","CERT_FILE","CERT_PATH","PACK_LOC","INFO_LOC", "");
			pOptDownloadPackage = new COptDownloadPackage(this);

			pmRecup->Lookup("ID", TmpValue);
			
			char histBuf[100];
			int nreadH = 0;
			CString csHistBuf;
			history.SeekToBegin();
			while( nreadH = history.Read(histBuf,sizeof(histBuf))) {
				histBuf[ nreadH + 1 ] = '\0';
				csHistBuf += histBuf;
			}
							
			if( csHistBuf.Find( TmpValue ) != -1 ) {
				AddLog("DOWNLOAD: Will not download %s that is already in the history file\n", TmpValue);
				delete pOptDownloadPackage;
				cmpt++;
				continue;
			}

			pOptDownloadPackage->setId(TmpValue);				
			pmRecup->Lookup("CERT_PATH", TmpValue);
			TmpValue.Replace( "INSTALL_PATH", "." );
			TmpValue.Replace( "/", "\\" );
			pOptDownloadPackage->setCertPath(TmpValue);
			pmRecup->Lookup("CERT_FILE", TmpValue);
			TmpValue.Replace( "INSTALL_PATH", "." );
			TmpValue.Replace( "/", "\\" );
			pOptDownloadPackage->setCertFile(TmpValue);

			pmRecup->Lookup("INFO_LOC", TmpValue);
			pOptDownloadPackage->setInfoLoc(TmpValue);

			pmRecup->Lookup("PACK_LOC", TmpValue);
			pOptDownloadPackage->setPackLoc(TmpValue);

			m_tPackages.Add(pOptDownloadPackage);
		}
		else {
			AddLog("ERROR: DOWNLOAD: Unknown type in download options\n");	
		}
		
		cmpt++;							
	}
	while(pmType->GetCount()>0);

	CUtils::cleanCm(pmType);	
	
	trace();

	int i = 0;
	while(i < m_tPackages.GetSize())
	{
		( (COptDownloadPackage*) (m_tPackages[i]) )->makeDirectory();
		if( fileExists("info", ((COptDownloadPackage*) (m_tPackages[i]) )->getId(), "download") == 0 )
			( (COptDownloadPackage*) (m_tPackages[i]) )->getInfoFile();
		i++;
	}
	
	try { 
		CFile::Remove("download\\suspend"); 
	} 
	catch(CException *e) { 
		e->Delete();
	}

	return 0;
}

int CModuleDownload::end() {
	//TODO: remove
	//return 0;
	if( m_csDownloadOn == "0" ) {
		AddLog("DOWNLOAD: Download is off\n");
		return 0;
	}
	CString cmd;
	cmd.Format( "download.exe %s", cmdL );
		
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	si.dwFlags=STARTF_USESHOWWINDOW;
	si.wShowWindow=SW_SHOW;
	if( ! CreateProcess( NULL, cmd.GetBuffer(0), NULL, NULL, FALSE, 0, NULL, NULL, &si,&pi )) {
		AddLog("ERROR: DOWNLOAD: Can't create download process\n");
		return 1;
	}

	return 0;
} 

void CModuleDownload::trace()
{
	TRACE("m_csDownloadFragLatency:%s, m_csDownloadCycleLatency: %s,  m_csDownloadPeriodLatency: %s, m_csDownloadPeriodLength: %s, m_csDownloadTimeout: %s, m_csDownloadOn: %s\n", m_csDownloadFragLatency,
		m_csDownloadCycleLatency,
		m_csDownloadPeriodLatency,
		m_csDownloadPeriodLength,
		m_csDownloadTimeout,
		m_csDownloadOn);
	TRACE("PACKAGES:\n");
	int i = 0;
	while(i < m_tPackages.GetSize())
	{
		( (COptDownloadPackage*) (m_tPackages[i]) )->trace();
		i++;
	}
	TRACE("---------\n");
}


int verify_callback(int ok, X509_STORE_CTX *store)
{
    char data[256];
 
    if (!ok)
    {
        X509 *cert = X509_STORE_CTX_get_current_cert(store);
        int  depth = X509_STORE_CTX_get_error_depth(store);
        int  err = X509_STORE_CTX_get_error(store);
 
        AddLog("ERROR: DOWNLOAD: SSL: -Error with certificate at depth: %i\n", depth);
        X509_NAME_oneline(X509_get_issuer_name(cert), data, 256);
        AddLog("ERROR: DOWNLOAD: SSL: issuer   = %s\n", data);
        X509_NAME_oneline(X509_get_subject_name(cert), data, 256);
        AddLog("ERROR: DOWNLOAD: SSL: subject  = %s\n", data);
        AddLog("ERROR: DOWNLOAD: SSL: err %i:%s\n", err, X509_verify_cert_error_string(err));
    }
 
    return ok;
}

void COptDownloadPackage::trace()
{
	TRACE("m_csId: %s, m_csCertFile: %s, m_csCertPath: %s, m_csInfoLoc: %s, m_csPackLoc: %s\n",
		m_csId, m_csCertFile, m_csCertPath, m_csInfoLoc, m_csPackLoc);
}

void CModuleDownload::configToFile()
{
	char useless[255];
	WritePrivateProfileString(OCS_AGENT_KEY, "FragLatency", m_csDownloadFragLatency, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "CycleLatency", m_csDownloadCycleLatency, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "PeriodLatency", m_csDownloadPeriodLatency, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "PeriodLength", m_csDownloadPeriodLength, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "Timeout", m_csDownloadTimeout, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "On", m_csDownloadOn, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "DeviceId",pC->GetDeviceID(), "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "Server",server, "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "Proxy",itoa(proxy,useless,10), "download\\config.ini");
	WritePrivateProfileString(OCS_AGENT_KEY, "Port",itoa(port,useless,10), "download\\config.ini");
}

SSL_CTX * COptDownloadPackage::setup_client_ctx(void)
{
    SSL_CTX *ctx;
 
    ctx = SSL_CTX_new(SSLv23_method(  ));
    if (SSL_CTX_load_verify_locations(ctx, m_csCertFile.GetBuffer(0), m_csCertPath.GetBuffer(0)) != 1)
	   AddLog("ERROR: DOWNLOAD: loading CA file and/or directory\n");
    if (SSL_CTX_set_default_verify_paths(ctx) != 1)
        AddLog("ERROR: DOWNLOAD: loading default CA file and/or directory\n");
    
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
    SSL_CTX_set_verify_depth(ctx, VERIFY_DEPTH);
    return ctx;
}
 
int COptDownloadPackage::sendGetRequest(SSL *ssl)
{
    CString getBuf;
	getBuf.Format("GET /%s/%s/info HTTP/1.0\n\n", m_csInfoLoc, m_csId );
	
	int err = SSL_write(ssl, getBuf.GetBuffer(0), getBuf.GetLength());
    if (err <= 0)
		return 0;

    return 1;
}

int COptDownloadPackage::makeDirectory() {
	
	int ErrorNum;
	CString directory;
	directory.Format( "download\\%s", m_csId );
	if ( CreateDirectory ( directory.GetBuffer(0), NULL ) == FALSE) {
		if ( ( ErrorNum = GetLastError() ) != ERROR_ALREADY_EXISTS) {
			AddLog("ERROR: DOWNLOAD: Cannot create Id directory %s (%i)\n", m_csId, ErrorNum);
			return(ErrorNum);
		}
	}
	return 0;
}

int COptDownloadPackage::readResponse(SSL *ssl) {
    
	CFile infoFile;
	CString fName;
	CString tempBuf, line;
	fName.Format("download\\%s\\info", m_csId);
	int nread;	
	char buf;
	BOOL firstLineFeed = TRUE;
	BOOL httpHeaders = TRUE;
	
	while( 1 ) {
		
		nread = 0;
		nread = SSL_read( ssl, &buf, 1);

		if( nread <= 0 ) {
			int error = SSL_get_error(ssl, nread);
			if( error == SSL_ERROR_NONE || error == SSL_ERROR_ZERO_RETURN )
				break;
			else if(error == SSL_ERROR_WANT_READ) {
				Sleep(1000);
				continue;
			}
			else {
				AddLog("ERROR: DOWNLOAD: Info file SSL error %i\n", error );
				break;
			}			
		}

		line += buf;

		if( line == "\r\n") {
			httpHeaders = FALSE;
			line = "";
		}

		if( firstLineFeed && buf == '\n' ) {
			if( line.Find( "200 OK", 0) < 0 ) {
				line.TrimRight();
				AddLog( "ERROR: DOWNLOAD: Line: %s, Id:%s\n", line, m_csId );				
				CNetUtils::downloadMessage(ERR_DOWNLOAD_INFO, m_csId, pM->pC->GetDeviceID(), pM->server, pM->port, pM->proxy );
				return -2;
			}
			firstLineFeed = FALSE;
		}

		if( buf == '\n' ) {
			if( ! httpHeaders )
				tempBuf += line;
			line = "";
		}
	}
	
	CMarkup xml;

	if( ! xml.SetDoc( tempBuf ) ) {
		AddLog("\tERROR: Info file is not XML\n");
		return -1;
	}
	
	xml.FindElem("DOWNLOAD");
	xml.SetAttrib("LOC", m_csPackLoc);

	if( ! infoFile.Open(fName, CFile::modeCreate|CFile::modeWrite) ) {
		AddLog("ERROR: DOWNLOAD: Can't open %s\n", fName );
		return -1;
	}

	infoFile.Write( xml.GetDoc(), xml.GetDoc().GetLength() );
	infoFile.Close();

	CString sinceF;
	sinceF.Format("download\\%s\\since", m_csId);
	CFile sinceFile;
	if( ! sinceFile.Open(sinceF, CFile::modeCreate|CFile::modeWrite)) {
		AddLog("ERROR: DOWNLOAD: Can't open %s\n", sinceF );
		return -1;
	}

	char dummy[33];
	_ltoa(time(NULL),dummy,10);
	sinceFile.Write( dummy, strlen(dummy));
	AddLog("DOWNLOAD: Retrieve info file...OK (pack %s)\n", m_csId );
    return 1;	
}
 
int COptDownloadPackage::getInfoFile()
{
    BIO     *conn;
    SSL     *ssl;
    SSL_CTX *ctx;
	
	if( init_OpenSSL(  ) ) {
		AddLog("ERROR: DOWNLOAD: Can't init openssl\n");
		return 1;
	}
	seed_prng(  );
 
    ctx = setup_client_ctx(  );

	// Get server name+port and ressource info file location
	CString srvName, infoUrl;
	char * resToken;

	resToken = strtok(m_csInfoLoc.GetBuffer(0), "/");

	if( resToken == NULL){
		// There is only a server name
		srvName = m_csInfoLoc;
	}
	// There is an url
	else{
		srvName = resToken;
		resToken = strtok(NULL, "/");
		// Extract URL
		while( resToken != NULL ){
			infoUrl += (CString("/") + resToken);
			resToken = strtok(NULL, "/");;
		}
		setInfoLoc(infoUrl);
	}
	    
	// SSL connection
	if( srvName.Find(":", 0) < 0){
		srvName += ":";
		srvName += SSL_PORT;
	}

	AddLog("DOWNLOAD: Info file for package %s is located at : %s%s\n", m_csId, srvName, m_csInfoLoc);

	conn = BIO_new_connect( srvName.GetBuffer(0) );
    if (!conn)
        AddLog("ERROR: DOWNLOAD: creating connection BIO\n");
 
    if (BIO_do_connect(conn) <= 0)
        AddLog("ERROR: DOWNLOAD: connecting to remote machine\n");
 
    ssl = SSL_new(ctx);
    SSL_set_bio(ssl, conn, conn);

    if (SSL_connect(ssl) <= 0) {
        AddLog("ERROR: DOWNLOAD: connecting SSL object\n");
	}
	else{
		AddLog("DOWNLOAD: SSL Connection opened...OK (pack %s)\n", m_csId);
		if (sendGetRequest(ssl)) {
	        SSL_shutdown(ssl);
			readResponse(ssl);
		}
		else
	        SSL_clear(ssl);
	    AddLog("DOWNLOAD: SSL Connection closed...OK (pack %s)\n", m_csId);
	}
 
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    return 0;
}

