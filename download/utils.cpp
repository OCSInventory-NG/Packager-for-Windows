
#include "stdafx.h"
#include "utils.h"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include "../include/Zip/ziparchive.h"
#include "../include/fileoperations/FileOperations.h"
#include "download.h"
#include "../include/_common/commonDownload.h"

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
		if (!myFile.Open( csFileName, CFile::shareDenyNone|CFile::modeCreate|CFile::modeWrite|CFile::typeText))
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
		csBuffer += '\n';
		// Write string
		
		char direc[_MAX_PATH+1];
		GetCurrentDirectory(_MAX_PATH,direc);
		myFile.WriteString( direc+CString("\t-\t")+csBuffer);
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

/////////////////////////////////////////////////////////////////////////////
// CDownloadApp initialization

CString getFilePath( LPCSTR file, LPCSTR id) {
	CString path;
	path.Format("%s\\%s", id, file);
	return path;
}

CString  getFileContent( LPCSTR file, LPCSTR id ) {
	CString path = getFilePath( file, id);
	
	CFile fil;
	if( ! fil.Open(path, CFile::modeRead ) ) {
		AddLog("\t\tERROR: Can't open %s",path);
		return CString("__ERROR__");
	}

	CString info;
	int read = fil.Read( info.GetBufferSetLength(fil.GetLength()) , fil.GetLength() );
	info.ReleaseBuffer();
	fil.Close();
	return(info);
}

void createRestorePoint( CString nme ) {

	//In the _tmain function in Install.cpp, create the two variables shown in the following code:
	RESTOREPOINTINFO RstPt;
//	STATEMGRSTATUS MgrStat;						

	//Add the following statements that populate the RstPt variable with information that 
	//indicates that an application is about to be installed:
	RstPt.dwEventType = BEGIN_SYSTEM_CHANGE;
	RstPt.dwRestorePtType = APPLICATION_INSTALL;
	strcpy(RstPt.szDescription, nme );						

	//Create a Restore Point to mark the beginning of the installation using the SRSetRestorePoint
	//function. In the event of a failure, report the reason for the failure and exit:
	/*if (!SRSetRestorePoint(&RstPt, &MgrStat))
	{
		AddLog("ERROR: Unable to set restore point. Error %ld\n",MgrStat.nStatus);
		return;
	}	*/

	//Display the sequence number for the newly created Restore Point:
	//AddLog("Restore point created. Sequence %ld\n",	MgrStat.llSequenceNumber);					
}


void cleanPackage( CString id ) {
	AddLog("Cleaning package %s",id);	
	CFileOperation cf;
	if( ! cf.Delete( id ) ) {
		Sleep(1000);
		AddLog("ERROR: clean of %s failed with error:\n\t\t\t%s", id, cf.GetErrorString());
		((CDownloadApp*)AfxGetApp())->error++;

		if( ((CDownloadApp*)AfxGetApp())->error > atoi( MAX_ERROR_COUNT ) )
			( (CDownloadApp*)AfxGetApp() )->finish();
	}
	((CDownloadApp*)AfxGetApp())->blackList( id );
}

CString simple_digest (char *alg, CString fname, UINT *olen) {
  
	CFile	fRead;
	if( ! fRead.Open( fname, CFile::modeRead )) {
		AddLog("ERROR: Can't open %s, error:%i", fname, GetLastError());
		return CString("__ERROR__");
	}
	UINT len = fRead.GetLength();
	BYTE * buf = new BYTE[ len ];
	fRead.Read( buf, len );
	fRead.Close();
	const EVP_MD *m;
	EVP_MD_CTX ctx;
	unsigned char *ret;

	OpenSSL_add_all_digests ();

	if (!(m = EVP_get_digestbyname (alg))){
		delete [] buf;
		return CString("");
	}

	if (!(ret = (unsigned char *) malloc (EVP_MAX_MD_SIZE))){
		delete [] buf;
		return CString("");
	}

	EVP_DigestInit (&ctx, m);
	EVP_DigestUpdate (&ctx, buf, len);
	EVP_DigestFinal( &ctx, ret, olen);
	CString csRet = ret;
	free( ret );
	delete [] buf;	
	return csRet;
}

CString print_hex (unsigned char *bs, unsigned int n) {
	UINT i;
	CString ret, format;

	for (i = 0; i < n; i++) {
		format.Format("%02x", bs[i]);
		ret += format;
	}
	return ret;
}

/* A helper function for base64 encoding */
CString base64_encode (unsigned char *buf, unsigned int len)
{
  unsigned char *ret;
  unsigned int b64_len;

/* the b64data to data ratio is 3 to 4.
* integer divide by 3 then multiply by 4, add one for NULL terminator.
*/
  b64_len = (((len + 2) / 3) * 4) + 1;
  ret = (unsigned char *) malloc (b64_len);
  EVP_EncodeBlock (ret, buf, len);
  ret[b64_len - 1] = 0;
  CString csRet = ret;
  free( ret );
  return csRet;
}

int unzip(CString file, CString path) {
		// Unzipping upd.zip file
		//////////////////////////////////
		
		AddLog("Unzipping %s", file);
		fflush( myFile.m_pStream );
		CZipArchive c;
		try
		{
			try
			{
				c.Open(file);
			}
			catch (CException * pE)
			{
				AddLog("ERROR: could not open %s for unzipping", file);
				pE->Delete();
				return 1;
			}
				
			for(WORD i=0;i<c.GetNoEntries();i++)
			{
				CFileHeader h;
				c.GetFileInfo(h, i);				
				AddLog("Extract : %s", path);
				c.ExtractFile(i,path);
				AddLog("%s extracted",h.m_szFileName);
			}
		}
		catch (CException * pE)
		{		
			fflush( myFile.m_pStream );
			AddLog("ERROR: while unzipping %s", file  );
			pE->Delete();
			c.Close();
			return 1;			
		}
		c.Close();
		return 0;
}

