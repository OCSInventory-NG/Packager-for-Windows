// Document modified at : Wednesday, March 29, 2006 4:37:33 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO
//====================================================================================
// Open Computer and Software Inventory
// Copyleft PIERRE LEMMET 2005
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

#ifndef _NET_UTILS_H_
#define _NET_UTILS_H_


#include "../zlib/flate.h"
#include <afxinet.h>
#include <string.h>
#include "../_common/defines.h"
#include "../xml/markup.h"


class CNetUtils
{

public:


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
 *	compress and sends the "pX" xml using the pConnect connection
 */
static CString sendXmlSimple(CHttpConnection* pConnect,CMarkup* pX, UINT* pHttpCode ) {
	
	CByteArray *pCompresse, *reponseCompresse;
	UINT httpCode = 0;

	if( !(pCompresse = compressStr(pX->GetDoc()))){
		return CString("");
	}
							  
	if( !( reponseCompresse = req(pConnect,(BYTE*)(pCompresse->GetData()),pCompresse->GetSize(), TRUE, URL_SUFFIX, &httpCode) ) ){
		*pHttpCode = httpCode;
		delete pCompresse;
		return CString("");
	}
	
	CString mess;
	
	for( int i=0; i<reponseCompresse->GetSize() ; i++)
		mess += char( reponseCompresse->GetAt(i) );

	delete pCompresse;
	delete reponseCompresse;
	*pHttpCode = httpCode;
	return mess;
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
 *  Runs a query with content "content" and a "size" length using the "pConnect" connexion
 *  Returns a byte array containing the server answer
 */
static CByteArray* req(CHttpConnection* pConnect,BYTE content[],int size,BOOL post=TRUE,CString url=URL_SUFFIX, UINT* pHttpCode=NULL) {

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
		
		CException * err = new CException;
		ULONG httpCode=0;

		if (! ((CHttpFile*)pF)->QueryInfoStatusCode( httpCode ) ) {
			AddLog("ERR: Cannot get http code\n");
			throw(err);
		}
		else {
			if( pHttpCode )
				*pHttpCode = httpCode;

			if (httpCode != 200) {
				AddLog("ERROR: Http error: %ld\n", httpCode);
				throw(err);
			}
			else {
				AddLog("Http code (%ld)...OK\n", httpCode);
			}
		}	
		
		reqRes=reqResult(pF);		
		res->Copy(*reqRes);
		
		pF->Close();		
		delete pF;
		err->Delete();
		delete reqRes;
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

static int downloadMessage( CString mess ,CString Id, CString did, CString server, INTERNET_PORT port, UINT proxy ) {
	
	AddLog("Sending download message: %s ID:%s\n", mess, did);
	
	CHttpConnection		*pConnect		= NULL;
	CInternetSession	* pSess			= NULL;
	CMarkup				xml,xmlResp;
	CString				reponse,contentS;
	
	UINT httpCode;

	xml.AddElem("REQUEST");
	xml.AddAttrib("DEVICEID", did);
	xml.AddAttrib("QUERY", "DOWNLOAD");
	xml.AddAttrib("ID", Id);
	xml.AddAttrib("ERR", mess);
	TRACE( xml.GetDoc());

	try{
		pSess = new CInternetSession("windows_download_agent", 1, proxy);	
		pConnect = pSess->GetHttpConnection(server, port);
	}
	catch(CException *err){
		AddLog("ERROR: Error with HTTP connection\n");
		err->Delete();
	}

	CString ret("");
	ret = CNetUtils::sendXmlSimple( pConnect, &xml, &httpCode );
	
	if( ret != "" || httpCode != 200) {
		
		pConnect->Close();
		if( pConnect ) delete pConnect;
		if( pSess) delete pSess;
		AddLog("ERROR: download message was not successfully sent, [%s] received\n", ret);
		return 1;
	}
	AddLog("Message [%s] successfully sent\n", mess);
	pConnect->Close();
	if( pConnect ) delete pConnect;
	if( pSess) delete pSess;
	return 0;
};

};

#endif