#include "stdafx.h"
#include "ntserv_msg.h"
#include "ntservEventLog.h"
#include "app.h"

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
  //Uncomment the following code to test the persistance functions
  /* 
  DWORD dwError;
  CMyService testService;
  UINT nValue = testService.GetProfileInt(_T("General"), _T("IntValue"), 33, &dwError);
  CString sValue = testService.GetProfileString(_T("General"), _T("StringValue"), _T("DefaultValue"), &dwError);

  BOOL bSuccess = testService.WriteProfileInt(_T("General"), _T("IntValue"), 37);
  bSuccess = testService.WriteProfileString(_T("General"), _T("StringValue"), _T("Test Value"));

  nValue = testService.GetProfileInt(_T("General"), _T("IntValue"), 33, &dwError);
  sValue = testService.GetProfileString(_T("General"), _T("StringValue"), NULL, &dwError);


  CStringArray array;
  array.SetAtGrow(0, _T("First String"));
  array.SetAtGrow(1, _T("Second and Last String"));
  bSuccess = testService.WriteProfileStringArray(_T("General"), _T("StringArrayValue"), array);
  bSuccess = testService.GetProfileStringArray(_T("General"), _T("StringArrayValue"), array);
  bSuccess = testService.GetProfileStringArray(_T("General"), _T("Does Not Exist"), array);

  BYTE* pSetData = new BYTE[10];
  for (int i=0; i<10; i++)
    pSetData[i] = (BYTE) i;
	bSuccess = testService.WriteProfileBinary(_T("General"), _T("BinaryValue"), pSetData, 10);
  delete [] pSetData;

  array.SetSize(0);
  bSuccess = testService.GetProfileStringArray(_T("General"), _T("StringArrayValue"), array); 

  BYTE* pGetData = NULL;
  UINT nBytes;
	bSuccess = testService.GetProfileBinary(_T("General"), _T("BinaryValue"), &pGetData, &nBytes);
  if (bSuccess)
  {
    delete [] pGetData;
  }

  testService.WriteProfileString(_T("General"), _T("BinaryValue"), NULL);
  testService.WriteProfileString(_T("General"), NULL, NULL);

  return FALSE;
  */


  //Uncomment the following to test out the instance enumeration function
  /*
  {
  CMyService testService;
  CStringArray instances;
  DWORD dwError;
  testService.EnumerateInstances(instances, dwError);
  for (int i=0; i<instances.GetSize(); i++)
    TRACE(_T("Found instance, %s\n"), (LPCTSTR) instances.GetAt(i));
  }
  */


  //Uncomment the following code to test the CNTServiceControlManager
  //and the CNTScmService classes
  /*
  CNTServiceControlManager manager;
  SC_HANDLE hScm = manager;
  BOOL bSuccess2 = manager.Open(NULL, SC_MANAGER_ALL_ACCESS);
  hScm = manager;
  LPQUERY_SERVICE_LOCK_STATUS lpLockStatus = NULL;
  bSuccess2 = manager.QueryLockStatus(lpLockStatus);
  BOOL bIsLocked = (lpLockStatus->fIsLocked != 0);
  LPCTSTR lpszOwner = lpLockStatus->lpLockOwner;
  DWORD dwDuration = lpLockStatus->dwLockDuration;
  delete [] (BYTE*) lpLockStatus;
  bSuccess2 = manager.Lock();
  lpLockStatus = NULL;
  bSuccess2 = manager.QueryLockStatus(lpLockStatus);
  bIsLocked = (lpLockStatus->fIsLocked != 0);
  lpszOwner = lpLockStatus->lpLockOwner;
  dwDuration = lpLockStatus->dwLockDuration;
  delete [] (BYTE*) lpLockStatus;
  bSuccess2 = manager.EnumServices(SERVICE_WIN32, SERVICE_STATE_ALL, 0, EnumServices);
  CNTScmService service;
  SC_HANDLE hService = service;
  bSuccess2 = manager.OpenService(_T("Browser"), SERVICE_ALL_ACCESS, service);
  hService = service;
  bSuccess2 = service.Start(0, NULL);
  Sleep(4000);
  bSuccess2 = service.Control(128);
  bSuccess2 = service.Pause();
  Sleep(4000);
  bSuccess2 = service.Continue();
  BOOL bStop;
  bSuccess2 = service.AcceptStop(bStop);
  BOOL bPauseContinue;
  bSuccess2 = service.AcceptPauseContinue(bPauseContinue);
  BOOL bShutdown;
  bSuccess2 = service.AcceptShutdown(bShutdown);
  bSuccess2 = service.Stop();
  LPQUERY_SERVICE_CONFIG lpServiceConfig = NULL;
  bSuccess2 = service.QueryConfig(lpServiceConfig);
  TRACE(_T("dwServiceType is %d\n"),    lpServiceConfig->dwServiceType);
  TRACE(_T("dwStartType is %d\n"),      lpServiceConfig->dwStartType);
  TRACE(_T("dwErrorControl is %d\n"),   lpServiceConfig->dwErrorControl);
  TRACE(_T("lpBinaryPathName is %s\n"), lpServiceConfig->lpBinaryPathName);
  TRACE(_T("lpLoadOrderGroup is %s\n"), lpServiceConfig->lpLoadOrderGroup);
  TRACE(_T("dwTagId is %d\n"),          lpServiceConfig->dwTagId);
  TRACE(_T("lpDependencies are %s\n"),  lpServiceConfig->lpDependencies);
  TRACE(_T("lpServiceStartName is %s\n"), lpServiceConfig->lpServiceStartName);
  TRACE(_T("lpDisplayName is %s\n"), lpServiceConfig->lpDisplayName);
  delete [] (BYTE*) lpServiceConfig;
  service.EnumDependents(SERVICE_STATE_ALL, 0, EnumServices);
  */


  //Uncomment the following code to test the CNTEventLog 
  //and the CEventLogRecord classes
  /*
  CNTEventLog el;
  HANDLE hEventLog = el;
  BOOL bSuccess3 = el.OpenSecurity(NULL);
  hEventLog = el;
  bSuccess3 = el.OpenSystem(NULL);
  bSuccess3 = el.OpenApplication(NULL);
  DWORD dwOldest;
  bSuccess3 = el.GetOldestRecord(dwOldest);
  bSuccess3 = el.Backup(_T("C:\\BACKUPLOG.TXT"));
  bSuccess3 = el.Close();
  bSuccess3 = el.OpenBackup(NULL, _T("C:\\BACKUPLOG.TXT"));
  DWORD dwRecords;
  bSuccess3 = el.OpenSystem(NULL);
  bSuccess3 = el.GetNumberOfRecords(dwRecords);
  //bSuccess = el.Clear(NULL);
  CEventLogRecord record;
  DWORD i=0;
  while (i<dwRecords)
  {
    bSuccess3 = el.ReadNext(record);
    i++;
  }
  //bSuccess3 = el.ReadPrev(record);
  */


  //Uncomment the following code to test the 
  //CNTEventLogSource classes
  /*
  CNTEventLogSource els(NULL, _T("PJ's Demo NT Service"));
  LPCTSTR pString = _T("PJ's Demo NT Service");
  LPCTSTR* ppString = &pString;
  BOOL bSuccess4 = els.Register(NULL, pString);
  DWORD dwError = GetLastError();
  bSuccess4 = els.Report(EVENTLOG_INFORMATION_TYPE, 0, CNTS_MSG_SERVICE_STARTED, NULL, 1, 0, ppString, NULL);
  bSuccess4 = els.Deregister();
  */


  //All that is required to get the service up and running
  CNTServiceCommandLineInfo cmdInfo;
  CMyService Service;
  Service.SetAllowCommandLine(TRUE);
  Service.SetAllowNameChange(TRUE);       
  Service.SetAllowDescriptionChange(TRUE);
  Service.SetAllowDisplayNameChange(TRUE);
 
  //Service.SetControlsAccepted(0); //peut plus etre arrété/redemarrer par le ctrl panel

  //Service.m_dwServiceType = SERVICE_KERNEL_DRIVER;
// Service.m_sServiceName = "TOTOMUT";
  Service.m_dwStartType = SERVICE_AUTO_START;
  Service.m_dwErrorControl = SERVICE_ERROR_IGNORE;

  //Uncomment the following code to setup the service with different requirements
  //
  //Service.m_sDependencies.Add(_T("RPCSS"));
  //Service.m_sDependencies.Add(_T("W3SVC"));
  //Service.m_dwServiceType = SERVICE_KERNEL_DRIVER;
  //Service.m_dwStartType = SERVICE_BOOT_START;
  //Service.m_dwErrorControl = SERVICE_ERROR_NORMAL;
  //Service.m_sUserName = _T("");
 // Service.m_sPassword = _T("");
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
	m_bkillMe = FALSE;  
	m_bWantStop = FALSE;     //Simple boolean which is set to request the service to stop
	m_bPaused = FALSE;       //The boolean used to represent that the service is paused
	m_dwBeepInternal = 1000; //The default beep interval of 1 second
	m_hMutexOneInstance = ::CreateMutex( NULL, TRUE, _T("OCSINVENTORY-SERVICE-MUTEX"));
	UINT lastErr = GetLastError();
	if ( lastErr == ERROR_ALREADY_EXISTS || lastErr == ERROR_ACCESS_DENIED ) {
		m_bkillMe = TRUE;
	}
}

CMyService::~CMyService() 
{
  if ( m_hMutexOneInstance != NULL && !m_bkillMe ) {
        ::ReleaseMutex(m_hMutexOneInstance);
  }
}

void CMyService::ServiceMain(DWORD /*dwArgc*/, LPTSTR* /*lpszArgv*/)
{
	if(	m_bkillMe )
		this->TerminateService();
	//Pretend that starting up takes some time
  ReportStatus(SERVICE_START_PENDING, 1, 1100);
  Sleep(1000);
  ReportStatus(SERVICE_RUNNING);

  //Report to the event log that the service has started successfully
  m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, CNTS_MSG_SERVICE_STARTED, m_sDisplayName);

  //The tight loop which constitutes the service
  BOOL bOldPause = m_bPaused;
	while (!m_bWantStop) {	
		if (!m_bPaused) {
			MessageBeep(MB_OK);
			//RUN inventory !
			CString cmd="ocsinventory.exe /debug";AfxGetApp()->get
			//AfxMessageBox("INVENTAIRE!");
			STARTUPINFO si;
			PROCESS_INFORMATION pi;

			ZeroMemory( &si, sizeof(si) );
			si.cb = sizeof(si);
			ZeroMemory( &pi, sizeof(pi) );

			si.dwFlags=STARTF_USESHOWWINDOW;
			si.wShowWindow=SW_SHOW;
			CreateProcess( NULL, cmd.GetBuffer(0), NULL, NULL, FALSE,CREATE_DEFAULT_ERROR_MODE|IDLE_PRIORITY_CLASS, NULL, NULL, &si,&pi );
		}      

    //Wait for the specified time
	  for( int cpt=0; cpt<30 && !m_bPaused && !m_bWantStop;cpt++ )
		Sleep(/*m_dwBeepInternal*/1000);

    //SCM has requested a Pause / Continue
    if (m_bPaused != bOldPause)
    {
      if (m_bPaused)
      {
   	    ReportStatus(SERVICE_PAUSED);

        //Report to the event log that the service has paused successfully
        m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, CNTS_MSG_SERVICE_PAUSED, m_sDisplayName);
      }
      else
      {
        ReportStatus(SERVICE_RUNNING);

        //Report to the event log that the service has stopped continued
        m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, CNTS_MSG_SERVICE_CONTINUED, m_sDisplayName);
      }
    }

    bOldPause = m_bPaused;
	}

	//Pretend that closing down takes some time
  ReportStatus(SERVICE_STOP_PENDING, 1, 1100);
	Sleep(1000);

  //Report to the event log that the service has stopped successfully
  m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, CNTS_MSG_SERVICE_STOPPED, m_sDisplayName);
}

void CMyService::OnStop()
{
	//Signal the other thread to end via the boolean variable
	InterlockedExchange((LONG volatile*) &m_bWantStop, TRUE);
}

void CMyService::OnPause()
{
	//Signal the other thread via the boolean variable
  InterlockedExchange((LONG volatile*) &m_bPaused, TRUE);
}

void CMyService::OnContinue()
{
	//Signal the other thread to continue via the boolean variable
  InterlockedExchange((LONG volatile*) &m_bPaused, FALSE);
}

void CMyService::OnUserDefinedRequest(DWORD dwControl)
{
  //Any value greater than 200 increments the doubles the beep frequency
  //otherwise the frequency is halved
  if (dwControl > 200)
    m_dwBeepInternal /= 2;
  else
    m_dwBeepInternal *= 2;

  //Report to the event log that the beep interval has been changed
  CString sInterval;
  sInterval.Format(_T("%d"), m_dwBeepInternal);
  m_EventLogSource.Report(EVENTLOG_INFORMATION_TYPE, MSG_SERVICE_SET_FREQUENCY, sInterval);
}

void CMyService::ShowHelp()
{
	AfxMessageBox(_T("A demo service which just beeps the speaker\nUsage: testsrv [ -install | -uninstall | -remove | -start | -pause | -continue | -stop | -help | -? ]\n"));
}

/*
void CMyService::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
	//Register the Control Handler
	RegisterCtrlHandler();
	
	DWORD dwWin32ExitCode = NO_ERROR;
	DWORD dwServiceSpecificExitCode = 0;
	
	//Call the main C++ function
	try
	{
		ServiceMain(dwArgc, lpszArgv);
	}
	catch(CNTServiceTerminateException& e)
	{
		dwWin32ExitCode = e.m_dwWin32ExitCode;
		dwServiceSpecificExitCode = e.m_dwServiceSpecificExitCode;

	  //Report to the SCM that the service has stopped.
	  //Note that it is important that we do not access anything on the stack 
	  //after this call as the SCM could have terminated this worker thread by then
	  _ReportStatus(SERVICE_STOPPED, 0, 0, 0, dwWin32ExitCode, dwServiceSpecificExitCode);
	}
}
*/