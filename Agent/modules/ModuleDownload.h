
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleDownload.h: interface for the CModuleDownload class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MODULEDOWNLOAD_H__961B32A5_C536_4BBA_B9E5_D043051601B5__INCLUDED_)
#define AFX_MODULEDOWNLOAD_H__961B32A5_C536_4BBA_B9E5_D043051601B5__INCLUDED_

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

//#include "reentrant.h"

#ifndef WIN32
#include <pthread.h>
#define THREAD_CC
#define THREAD_TYPE                    pthread_t
#define THREAD_CREATE(tid, entry, arg) pthread_create(&(tid), NULL, \
                                                      (entry), (arg))
#else
#include <windows.h>
#define THREAD_CC                      __cdecl
#define THREAD_TYPE                    DWORD
#define THREAD_CREATE(tid, entry, arg) do { _beginthread((entry), 0, (arg));\
                                            (tid) = GetCurrentThreadId();   \
                                       } while (0)
#endif /* WIN32 */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../include/_common/commonDownload.h"
#include "../../include/_common/FilePackageHistory.h"
#include "ModuleApi.h"

class CModuleDownload : public CModuleApi
{
private:
	CObArray m_tPackages;
	CString m_csDownloadFragLatency,
		m_csDownloadCycleLatency,
		m_csDownloadPeriodLatency,
		m_csDownloadPeriodLength,
		m_csDownloadTimeout,
		m_csDownloadOn;
public:
	int inventory(CMarkup* ,CDeviceProperties* );
	void configToFile();
	CModuleDownload(CString commandLine,CDeviceProperties * pC, CString serv, UINT prox, INTERNET_PORT port, CString http_user, CString http_pwd );
	virtual ~CModuleDownload();
	void trace();
	int response(CMarkup* pXml, CString* pRawResponse=NULL);
	int end();
};

class COptDownloadPackage : public CObject
{
private:
	CString m_csId,
		m_csCertFile,
		m_csCertPath,
		m_csInfoLoc,
		m_csPackLoc;

	CModuleDownload * pM;

public:
	void setId(LPCSTR Id) { m_csId = Id; }
	void setCertPath(LPCSTR CertPath) { m_csCertPath = CertPath; }
	void setCertFile(LPCSTR CertFile) { m_csCertFile = CertFile; }
	void setInfoLoc(LPCSTR infoLoc) { m_csInfoLoc = infoLoc; }
	void setPackLoc(LPCSTR packLoc) { m_csPackLoc = packLoc; }
	CString getId() { return m_csId; }
	void trace();
	int sendGetRequest(SSL *ssl);
	int getInfoFile();
	SSL_CTX * setup_client_ctx(void);
	int readResponse(SSL *ssl);	
	int makeDirectory();
	COptDownloadPackage( CModuleDownload * pC) {pM=pC;};
};





#endif // !defined(AFX_MODULEDOWNLOAD_H__961B32A5_C536_4BBA_B9E5_D043051601B5__INCLUDED_)
