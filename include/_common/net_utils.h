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
static CMarkup sendXml(CHttpConnection* pConnect,CMarkup* pX)
{
	CMarkup ret;

	try
	{
		
		CByteArray* pCompresse = compressStr(pX->GetDoc());	
		CByteArray* reponseCompresse = req(pConnect,(BYTE*)(pCompresse->GetData()),pCompresse->GetSize());		
		
		if(reponseCompresse)
		{
			CString reponseDecompresse = deCompressStr(reponseCompresse);
			if( reponseDecompresse == "" )
			{
				AddLog("\nHTTP SERVER: Server <%s> answer is empty or unreadable\nHTTP Response: %s\n",pConnect->GetServerName(),reponseCompresse->GetData());
			}
			ret.SetDoc(reponseDecompresse);		
		}

		if(pCompresse!=NULL)
			delete pCompresse;
		if(reponseCompresse!=NULL)
			delete reponseCompresse;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		ret.SetDoc( "");
	}
	return ret;
}

/**
 *	compress and sends the "pX" xml using the pConnect connection
 */
static CString sendXmlSimple(CHttpConnection* pConnect,CMarkup* pX, UINT* pHttpCode )
{

	CString csResponse;

	try
	{
		CByteArray *pCompresse, *reponseCompresse;
		UINT httpCode = 0;

		csResponse.Empty();

		if( !(pCompresse = compressStr(pX->GetDoc()))){
			return csResponse;
		}
								  
		if( !( reponseCompresse = req(pConnect,(BYTE*)(pCompresse->GetData()),pCompresse->GetSize(), TRUE, URL_SUFFIX, &httpCode) ) ){
			*pHttpCode = httpCode;
			delete pCompresse;
			return csResponse;
		}
		
		for( int i=0; i<reponseCompresse->GetSize() ; i++)
			csResponse += char( reponseCompresse->GetAt(i) );

		delete pCompresse;
		delete reponseCompresse;
		*pHttpCode = httpCode;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		csResponse.Empty();
	}
	return csResponse;
}



/**
 *	Returns a deflate compressed byte array of the "data" string
 */
static CByteArray* compressStr(CString data)
{	
	CByteArray *pDst=new CByteArray();
	CByteArray src;
	
	for(int i=0;i<data.GetLength();i++)
	{
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
static CByteArray* req(CHttpConnection* pConnect,BYTE content[],int size,BOOL post=TRUE,CString url=URL_SUFFIX, UINT* pHttpCode=NULL)
{

	CByteArray* res=new CByteArray();
	CByteArray* reqRes=NULL;
	CHttpFile* pF;

	try
	{
		CString headers=HTTP_HEADERS;		
		if(post)
		{		
			pF=pConnect->OpenRequest(CHttpConnection::HTTP_VERB_POST,url,NULL,1,NULL,"HTTP/1.1", INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT );
			pF->SendRequest(headers,headers.GetLength(),content,size);
		}
		else
		{
			pF=pConnect->OpenRequest(CHttpConnection::HTTP_VERB_GET, url,NULL,1,NULL,"HTTP/1.1", INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE | INTERNET_FLAG_EXISTING_CONNECT );
			pF->SendRequest();			
		}			
		
		CException * err = new CException;
		ULONG httpCode=0;

		if (! ((CHttpFile*)pF)->QueryInfoStatusCode( httpCode ) )
		{
			AddLog("ERR: Cannot get HTTP status code\n");
			throw(err);
		}
		else
		{
			if( pHttpCode )
				*pHttpCode = httpCode;

			if (httpCode != 200)
			{
				AddLog("ERROR: HTTP status code %ld\n", httpCode);
				throw(err);
			}
			else
			{
				AddLog("HTTP status %ld OK\n", httpCode);
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
		pEx->GetErrorMessage( sz, 1024);
		AddLog("\nHTTP SERVER: %s\n", sz);
		pEx->Delete();
		delete res;
		res=NULL;

		if(pF!=NULL)
		{
			pF->Close();
			delete pF;
		}
		
		if(reqRes!=NULL)
		{
			delete reqRes;
		}
	}
	return res;
}


/**
 *	Returns a decompressed String of the "data" byte array
 */
static CString deCompressStr(CByteArray* data)
{
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
static CByteArray* reqResult(CHttpFile* pF)
{
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
static CByteArray* deCompressBin(CByteArray* data)
{
	CByteArray* dst=new CByteArray();

	Flate f;
	if( ! f.Uncompress(*dst,*data))
	{
		delete dst;
		dst=NULL;
	}

	return dst;
}

static int downloadMessage( CString mess ,CString Id, CString did, CString server, INTERNET_PORT port, UINT proxy, CString http_u, CString http_w )
{

	AddLog("Sending download message: %s ID:%s\n", mess, did);
	
	try
	{
		CHttpConnection		*pConnect		= NULL;
		CInternetSession	* pSess			= NULL;
		CMarkup				xml,xmlResp;
		CString				csResponse, csUserAgent;
		
		UINT httpCode;

		xml.AddElem("REQUEST");
		xml.AddAttrib("DEVICEID", did);
		xml.AddAttrib("QUERY", "DOWNLOAD");
		xml.AddAttrib("ID", Id);
		xml.AddAttrib("ERR", mess);
		TRACE( xml.GetDoc());

		csUserAgent.Format( _T( "%s_%s"), OCS_DOWNLOAD_USER_AGENT, OCS_DOWNLOAD_VERSION);
		pSess = new CInternetSession( csUserAgent, 1, proxy);	
		pConnect = pSess->GetHttpConnection(server, port, http_u, http_w);

		csResponse.Empty();
		csResponse = CNetUtils::sendXmlSimple( pConnect, &xml, &httpCode );
		
		if( csResponse != "" || httpCode != 200)
		{
			pConnect->Close();
			if( pConnect )
				delete pConnect;
			if( pSess)
				delete pSess;
			AddLog("ERROR: download message was not successfully sent, [%s] received\n", csResponse);
			return 1;
		}
		AddLog("Message [%s] successfully sent\n", mess);
		pConnect->Close();
		if( pConnect )
			delete pConnect;
		if( pSess)
			delete pSess;
		return 0;
	}
	catch(CException *pEx)
	{
		TCHAR sz[1024];
		pEx->GetErrorMessage( sz, 1024);
		AddLog("ERROR: HTTP connection exception <%s>\n", sz);
		pEx->Delete();
		return 1;
	}
};

static BOOL downloadLabel( CString csLabelFile, CString csServer, INTERNET_PORT iPort, UINT uProxy, CString csHttpUser, CString csHttpPw)
{
	CString csURI, csUserAgent;

	csURI.Format( _T( "http://%s:%u/ocsinventory/deploy/label"), csServer, iPort);
	AddLog( _T( "HTTP SERVER: Opening Internet connection to download <%s>..."), csURI);

	csUserAgent.Format( _T( "OCS-NG_windows_client_%s"), __DATE__);
	CInternetSession mySession( csUserAgent, 1, uProxy);
	CStdioFile* pFile = NULL;
	CFile downloadedFile;
	DWORD	dwHttpCode;
	BOOL	bReturn = FALSE;
	
	try
	{
		// Open Internet connection
		if ((pFile = mySession.OpenURL( csURI)) != NULL)
		{
			if (!((CHttpFile*)pFile)->QueryInfoStatusCode( dwHttpCode ))
			{
				AddLog( _T( "ERROR: cannot read HTTP status code\n"), csURI);
				pFile->Abort();
				pFile = NULL;
			}
			else
			{
				if (dwHttpCode != 200)
				{
					AddLog(_T( "ERROR: HTTP status code %d\n"), dwHttpCode);
					pFile->Abort();
					pFile = NULL;
				}
				else 
				{
					AddLog(_T( "HTTP status code %d OK\n"), dwHttpCode);
				}
			}
		}
		else
		{
			AddLog(_T( "Unable to open Internet session\n"), csURI);
			pFile = NULL;
		}

		if (pFile != NULL)
		{
			AddLog( _T( "HTTP SERVER: Downloading file <%s> to <%s>..."), csURI, csLabelFile);
			// Open label file to store
			if(downloadedFile.Open( csLabelFile, CFile::modeCreate|CFile::modeWrite))
			{
				BYTE szBuff[1024];
				int read;
				while( (read = pFile->Read(szBuff,sizeof(szBuff))) > 0)
				{
					downloadedFile.Write( szBuff, read);
				}
				downloadedFile.Close();
				bReturn = TRUE;
				AddLog( _T( "OK\n"));
			}
			else
				AddLog( _T( "ERROR: cannot open file <%s> for writing\n"), csLabelFile, csURI);
			pFile->Close();
			delete pFile;			
		}
		else
			downloadedFile.Abort();
	}
	catch (CException* pEx)
	{
		TCHAR sz[1024];
		pEx->GetErrorMessage( sz, 1024);
		AddLog( _T( "ERROR: Unable to download <%s>: %s\n"), csURI, sz);
		pEx->Delete();
		if (pFile != NULL)
			pFile->Abort();
		downloadedFile.Abort();
	}
	AddLog( _T( "HTTP SERVER: Closing HTTP connection..."));
	mySession.Close();
	AddLog( _T( "OK\n"));
	return bReturn;
}

};

#endif