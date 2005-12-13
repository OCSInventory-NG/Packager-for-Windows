//====================================================================================
// Open Computer and Software Inventory
// Copyleft PIERRE LEMMET 2005
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

#ifndef _UTILS_H_
#define _UTILS_H_

#include "zlib\flate.h"
#include <afxinet.h>
#include <string.h>
#include "../defines.h"

class CUtils
{

public:

/**
 *	Returns the path to:
 *		conf file (dir==0)
 *		accountinfo file (otherwise)
 */
static CString getDir(int dir=0) {
	char direc[_MAX_PATH+1];
	GetCurrentDirectory(_MAX_PATH,direc);
	CString ret;

	if(dir==0) {		
		ret.Format("%s\\%s",direc,OCS_IDENTIFICATION_FILE);
	}
	else {
		ret.Format("%s\\%s",direc,OCS_ACCOUNTINFO_FILE);
	}
	return ret;
}

/**
 *	writes in OCS_ACCOUNTINFO_FILE every accountinfo in xml
 */
static void	parseAccountParams(CMarkup xml) {
	try {
		CFile::Remove(getDir(1));
	}
	catch (CException * pE) {
		pE->Delete();
	}
	
	xml.ResetPos();
	xml.FindElem("REPLY");
	xml.IntoElem();
	while(xml.FindElem("ACCOUNTINFO"))
	{
		xml.FindChildElem("KEYNAME");
		CString name=xml.GetChildData();
		xml.ResetChildPos();
		xml.FindChildElem("KEYVALUE");
		CString value=xml.GetChildData();
		CUtils::writeParamFile(name,value,FALSE,1);		
		AddLog("Couple ( %s <=> %s ) added in configuration file\n",name,value);
	}
}

/**
 *	Returns TRUE if server option "option" is present in xml
 */
static BOOL isActivatedOption(CMarkup xml,CString option) {
	xml.ResetPos();
	xml.FindElem("REPLY");
	xml.IntoElem();
	while(xml.FindElem("OPTION")) {
		xml.IntoElem();
		xml.FindElem("NAME");
		if( option.CompareNoCase(xml.GetData()) == 0 )
			return TRUE;
		xml.OutOfElem();			
	}
	return FALSE;
}

/**
 *	TODO
 */
static CMapStringToString* getOptionAttributes(CMarkup xml,int rang,CString option,...) {
	xml.ResetPos();
	xml.FindElem("REPLY");
	xml.IntoElem();
	CMapStringToString * pMap = new CMapStringToString();
	int rangAct=1;
	
	while(xml.FindElem("OPTION")) {
		xml.IntoElem();
		xml.FindElem("NAME");
		
		if( option.CompareNoCase(xml.GetData()) != 0 ) {
			xml.OutOfElem();
			continue;
		}		
		
		while(xml.FindElem("PARAM")) {
			
			if( rang > rangAct) {				
				rangAct++;
				continue;
			}
			pMap->SetAt("VAL",xml.GetData());
			
			CString i=option;
			va_list marker;
			va_start( marker,option  );     /* Initialize variable arguments. */
			if (i != "")
				do {				
					i = va_arg( marker, LPCSTR);
					if( i != "" )
						pMap->SetAt(i,xml.GetAttrib(i));
				}
				while( i != "" );
			va_end( marker );
			return pMap;
		}				
	}
	
	return pMap;
}


/**
 *	Empty pM
 */
static void cleanCm(CMapStringToString* & pM) {
	if( pM != NULL) {
		pM->RemoveAll();
		delete pM;
		pM = NULL;
	}
}

/**
 *	Writes the couple name/value in the "file" file
 *	If noEmpty==TRUE AND Value=="" the line is not written
 */
static BOOL writeParamFile(CString name,CString value,BOOL noEmpty=FALSE,int file=0) {
	if(noEmpty&&value.GetLength()==0)
		return TRUE;

	HANDLE	hFile;
	// Create the file with system and hidden attributes
	if ((hFile = CreateFile( CUtils::getDir(file), GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL,
							 CREATE_NEW, FILE_ATTRIBUTE_SYSTEM|FILE_ATTRIBUTE_HIDDEN, NULL)) == INVALID_HANDLE_VALUE)
	{
		//AddLog( _T( "Failed in call to <CreateFile> function with error %lu !\n"), GetLastError());
		
	}
	else
		CloseHandle( hFile);

	if (WritePrivateProfileString( OCS_AGENT_KEY, name, value, CUtils::getDir(file)) == 0)
	{
		AddLog( _T( "Failed in call to <WritePrivateProfileString> function with error %lu !\n"), GetLastError());
		return FALSE;
	}
	
	return TRUE;
}

/**
 *	reads the "param" parameter 
 */
static CString readParamFile(CString param,int file=0) {	
	CString fileToRead;
	BOOL specialCase = FALSE;

	if(param=="Agent"||param=="tagDialog") {
		fileToRead = param=="Agent" ? VERSION_FILE : LABEL_FILE ;
		specialCase = TRUE;
	}

	if(specialCase) {
		CFile cf;
		CString reto="";

		if(cf.Open(fileToRead,CFile::modeRead))
		{				
			const int MAX=50;		
			char buf[MAX];
			int nb=0;
			do
			{			
				nb= cf.Read(buf,MAX);
				buf[MAX]=0;

				if(nb<MAX)
					buf[nb]=0;

				reto+=buf;		
			}
			while(nb==MAX);
			
			cf.Close();
			reto.TrimLeft(_T(" \t\n\r"));
			reto.TrimRight(_T(" \t\n\r"));
		}		

		return reto;

	}

	char ret[_MAX_PATH+1];

	if (GetPrivateProfileString( OCS_AGENT_KEY, param, _T(""), ret, _MAX_PATH, CUtils::getDir(file)) == 0)
	{
		return "";
	}

	return (CString)ret;
}

/**
 *	Returns a ByteArray containing the data answered by the server in the "pF" Http file pointer
 */
static CByteArray* reqResult(CHttpFile* pF) {
	CByteArray* ret=new CByteArray();
	try
	{
		BYTE buf;	
		int nb=0;
		do
		{			
			nb= pF->Read(&buf,1);
			if(nb!=0)
				ret->Add(buf);	
		}
		while(nb==1);
	}
	catch (CInternetException* pEx)
	{
		TCHAR sz[1024];
		pEx->GetErrorMessage(sz, 1024);
		AddLog("\nHTTP SERVER: REQS: %s \n", sz);
		pEx->Delete();
		delete ret;
		ret=NULL;
	}
	
	return ret;
}

/**
 *	Writes the byte array pointed by pB in a "filename" file
 */
static BOOL byteToFile(CByteArray* pB,CString filename) {
	if(pB==NULL)
		return FALSE;
	
	try
	{
		CFile f;
		f.Open(filename,CFile::modeCreate|CFile::modeWrite);
		f.Write(pB->GetData(),pB->GetSize());
		f.Close();
	}
	catch (CException* pEx)
	{
		AddLog("ERROR: could not write file %s\n", filename);
		pEx->Delete();
		return FALSE;
	}
	
	return TRUE;
}

/**
 *	Writes the byte array pointed by pB in a "filename" file
 */
static CByteArray* fileToByte( CString filename ) {
		
	CByteArray* res = new CByteArray();
	try
	{		
		BYTE lu;
		CFile f;
		if( f.Open(filename,CFile::modeRead)) {
			while( f.Read(&lu,1))
				res->Add( lu );
			f.Close();
		}
		else  {
			delete res;
			res = NULL;
		}
	}
	catch (CException* pEx)
	{
		AddLog("ERROR: could not read file %s\n", filename);
		pEx->Delete();
		delete res;
		res = NULL;
	}
	
	return res;
}

/**
 *  Runs a query with content "content" and a "size" length using the "pConnect" connexion
 *  Returns a byte array containing the server answer
 */
static CByteArray* req(CHttpConnection* pConnect,BYTE content[],int size,BOOL post=TRUE,CString url=URL_SUFFIX) {
	CByteArray* res=new CByteArray();
	CByteArray* reqRes=NULL;
	CHttpFile* pF;

	try
	{
		CString headers=HTTP_HEADERS;		
		if(post) {		
			pF=pConnect->OpenRequest(CHttpConnection::HTTP_VERB_POST,url,NULL,1,NULL,"HTTP/1.1", INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT );
			pF->SendRequest(headers,headers.GetLength(),content,size);
		} else {
			pF=pConnect->OpenRequest(CHttpConnection::HTTP_VERB_GET, url,NULL,1,NULL,"HTTP/1.1", INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT );
			pF->SendRequest();			
		}			

		reqRes=reqResult(pF);		
		res->Copy(*reqRes);
		delete reqRes;	
		pF->Close();		
		delete pF;
	}
	catch (CInternetException* pEx)
	{
		TCHAR sz[1024];
		pEx->GetErrorMessage(sz, 1024);
		AddLog("\nHTTP SERVER: %s\n", sz);
		pEx->Delete();
		delete res;
		res=NULL;

		if(pF!=NULL) {
			pF->Close();
			delete pF;
		}
		
		if(reqRes!=NULL) {
			delete reqRes;
		}
	}
	return res;
}

/**
 *	Returns TRUE if the option "option" was asked, FALSE otherwise
 */
static BOOL IsRequired(LPCTSTR lpstrCommandLine,CString option) {
	CString	csCommand = lpstrCommandLine;
	CString csOpt;
	
	option.MakeLower();
	csOpt.Format("/%s ",option);
	csCommand.MakeLower();
	int tst = 0;
	int iRgOpt = csCommand.Find( _T(csOpt));
	
	if( iRgOpt == -1 ) {
		if(  option.Compare( csCommand.Right(option.GetLength()) ) == 0 && csCommand.GetAt( csCommand.GetLength() - option.GetLength() - 1 ) == '/' ) {
			return TRUE;
		}
	}		
	return iRgOpt != -1;
}

/**
 * TODO
 */
static INTERNET_PORT getPort(LPCTSTR lpstrCommandLine) {
	CString par = getParamValue(lpstrCommandLine,"pnum");
	INTERNET_PORT iPort = atoi(par.GetBuffer(0)) == 0 ? DEFAULT_PORT : atoi(par.GetBuffer(0));
	return iPort;
}

/**
 *	Returns TRUE if the option "option" was asked, FALSE otherwise
 */
static CString getParamValue(LPCTSTR lpstrCommandLine,CString param) {
	
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

/**
 *	Removes any binary data from the "pX" xml markup
 */
static void cleanXml( CMarkup* pX ) {
	CString bef = pX->GetDoc();
	
	for(int i=0;i<bef.GetLength();i++) {	
		UCHAR cut = (UCHAR)bef.GetAt(i);
		if( (cut<32 || cut>244) && cut!=10 && cut!=13 ) {			
			bef.SetAt(i,'x');		
		}
	}
	pX->SetDoc(bef);
}


/**
 *	Returns a deflate compressed byte array of the "data" string
 */
static CByteArray* compressStr(CString data) {	
	CByteArray *pDst=new CByteArray();
	CByteArray src;
	
	for(int i=0;i<data.GetLength();i++) {
		src.Add(data.GetAt(i)) ;
	}

	Flate f;
	f.Compress(*pDst,src);
	return pDst;
}

/**
 *	Returns a decompressed String of the "data" byte array
 */
static CString deCompressStr(CByteArray* data) {
	if( data == NULL )
		return CString("");
	
	CByteArray* dst=deCompressBin(data);
	if(dst==NULL)
		return CString("");

	CString b=dst->GetData();
	if( b.GetLength() >= dst->GetSize() )
		b.SetAt(dst->GetSize(),0);
	delete dst;
	return b;
}

/**
 *	Returns a decompressed byte array of the "data" byte array
 */
static CByteArray* deCompressBin(CByteArray* data) {
	CByteArray* dst=new CByteArray();

	Flate f;
	if( ! f.Uncompress(*dst,*data)) {
		delete dst;
		dst=NULL;
	}

	return dst;
}

/**
 *	compress and sends the "pX" xml using the pConnect connection
 */
static CMarkup sendXml(CHttpConnection* pConnect,CMarkup* pX) {
	
	CByteArray* pCompresse = compressStr(pX->GetDoc());	
	CByteArray* reponseCompresse = req(pConnect,(BYTE*)(pCompresse->GetData()),pCompresse->GetSize());	
	
	CMarkup ret;
	if(reponseCompresse) {
		CString reponseDecompresse = deCompressStr(reponseCompresse);	
		if( reponseDecompresse == "" ) {
			AddLog("\nHTTP SERVER: The server <%s> is not a well configured OCS server\nHTTP ERROR: %s\n",pConnect->GetServerName(),reponseCompresse->GetData());
		}
		ret.SetDoc(reponseDecompresse);		
	}

	if(pCompresse!=NULL) delete pCompresse;
	if(reponseCompresse!=NULL) delete reponseCompresse;

	return ret;
}

/**
 *	Returns the "RESPONSE" tag value of the xmlresp markup
 */
static CString getResponse(CMarkup xmlResp) {	
	
	if(xmlResp.GetDoc()=="")
		return CString("");

	xmlResp.FindElem("REPLY");
	xmlResp.IntoElem();
	xmlResp.FindElem("RESPONSE");
	return xmlResp.GetData();
}

static CString getVersion() {
		
		CString myVer;
		myVer.Format("%u%u%u%u",VER_D1, VER_D2, VER_D3, VER_D4);
		return myVer;
}

static CString getMacs(SysInfo* pSysInfo, CDeviceProperties & m_ThePC) {

		CNetworkAdapter	cObject;
		POSITION		pos;
		BOOL			bContinue;
		CString			lesMacs;

		pSysInfo->getNetworkAdapters( &m_ThePC.m_NetworkList );	
		pos = m_ThePC.m_NetworkList.GetHeadPosition();
		bContinue = (pos != NULL);
		if (bContinue)
			cObject = m_ThePC.m_NetworkList.GetNext( pos);

		while (bContinue) {
			bContinue = (pos != NULL);
			lesMacs += cObject.GetMACAddress();
			if (pos != NULL)
				cObject = m_ThePC.m_NetworkList.GetNext( pos);
		}
		return lesMacs;
}

static CString cleanVersion(CString target) {
	target.Replace(" ","");
	target.Replace(",","");
	target.Replace(".","");
	return target;
}

static void CUtils::getMacDeviceid(CString & csDeviceID, CString & csMac,LPCTSTR lpstrCommandLine) {
	
 	CFile conf;
	CString confValue = CUtils::getParamValue( lpstrCommandLine, "conf" );
	CString fileToOpen = OCS_CHECK_FILE;
	if(confValue != "") {		
		if( conf.Open(confValue, CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate) != 0) {
			fileToOpen = confValue;
			conf.Close();
		}
		else
			AddLog("ERROR: Using /conf option, file %s can't be used, use of %s instead\n", confValue, OCS_CHECK_FILE);
	}		
	
	CByteArray * pCb = CUtils::fileToByte(fileToOpen);
	CString content = CUtils::deCompressStr( pCb );
	delete pCb;

	csDeviceID = content.Left( content.Find('\n') );
	csMac = content.Right( content.GetLength()-content.Find('\n')-1);
	
	if( content.GetLength() == 0 )
		AddLog("CHECKINGS: No %s file found !\n",OCS_CHECK_FILE);
	else
		AddLog("CHECKINGS: read <%s> and <%s> in %s\n", csDeviceID, csMac, fileToOpen );
}

static void CUtils::writeMacDeviceid(CString csDeviceID, CString csMac, LPCTSTR lpstrCommandLine) {
	
	CFile conf;
	CString confValue = CUtils::getParamValue( lpstrCommandLine, "conf" );
	CString fileToOpen = OCS_CHECK_FILE;
	if(confValue != "") {		
		if( conf.Open(confValue, CFile::modeReadWrite|CFile::modeCreate|CFile::modeNoTruncate) != 0) {
			fileToOpen = confValue;
			conf.Close();
		}
		else
			AddLog("ERROR: Using /conf option, file %s can't be used, use of %s instead\n", confValue, OCS_CHECK_FILE);
	}			
	
	AddLog("CHECKINGS: write <%s> and <%s> in %s\n", csDeviceID, csMac, fileToOpen);
	CByteArray * pCb = CUtils::compressStr( csDeviceID + '\n' + csMac);
	CUtils::byteToFile( pCb, fileToOpen );
	delete pCb;
}
	
};
#endif //_UTILS_H_