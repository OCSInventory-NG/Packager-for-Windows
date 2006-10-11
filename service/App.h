#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "ntserv.h"
#include "ntservServiceControlManager.h"
#include "service_utils.h"
#define		TTO_WAIT				"TTO_WAIT"
#define		PROLOG_FREQ				"PROLOG_FREQ"
#define		OLD_PROLOG_FREQ			"OLD_PROLOG_FREQ"
#define		SERVICE_NME				"service"
#define		SERVICE_EXT				"ini"
#define		DEFAULT_PROLOG_FREQ		10
#define		WRITE_TTOWAIT_EACH		60
#define		RUN_OCS					"ocsinventory.exe /debug"
#define		OCS_SERVICE				"OCS_SERVICE"
#define		OCS_INSTALL				"MISCELLANEOUS"
#define		RAND_FILE				"rand"
#define		PROLOG_FREQ_UNIT		3600 //sec

class CMyService : public CNTService
{
private:
	HANDLE		m_hMutexOneInstance;
	BOOL		m_bkillMe;
	CFile		m_fServiceIni;
	int			m_iTToWait;
	int			m_iOldPrologFreq;
	int			m_iPrologFreq;
	CString		m_sServIni;
	CString		m_sCurDir;
	CObArray	m_tHandles;
	CString		m_csServer;
	int			m_iProxy;
	CString		m_csPort;
	CString		m_csMisc;

	void runAgent();	
	int generateRandNumber(int max);
	void readIniFile( CString section=OCS_SERVICE, int* storeVar=NULL, CString toRead="", CString def="" );
	void readIniFile( CString section, CString & storeVar, CString toRead, CString defaultVal="" );
	void writeIniFile( int* toBeStored=NULL, CString toWrite="" );	
	void openHandles();
	void closeHandles();
	void addOpenFile( LPCSTR fname );
	BOOL openIni();
	void closeIni();
	void preInit();

public:	
	CMyService();
	~CMyService();
	virtual void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
	virtual void OnStop();

protected:
	volatile BOOL m_bWantStop;
};

class CApp : public CWinApp
{
public:
	CApp();

protected:
	//{{AFX_VIRTUAL(CApp)
	virtual BOOL InitInstance();
  virtual int ExitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  DWORD m_dwExitCode;
};
