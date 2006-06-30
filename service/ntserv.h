/*
Module : NTSERV.H
Purpose: Defines the interface for an MFC class framework which encapsulate the whole area of services on NT, 2000, XP, and Server 2003
Created: PJN / 14-07-1998

Copyright (c) 1997 - 2005 by PJ Naughter.  (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __NTSERV_H__
#define __NTSERV_H__

#ifndef CNTSERVICE_EXT_CLASS
#define CNTSERVICE_EXT_CLASS
#endif



//////////////////////// Includes /////////////////////////////////////////////

#include "ntservCmdLineInfo.h"
#include "ntservEventLogSource.h"
#include "ntservDefines.h"



//////////////////////// Classes //////////////////////////////////////////////

//Class which carries the exit code information when you call CNTService::TerminateService
class CNTSERVICE_EXT_CLASS CNTServiceTerminateException
{
public:
//Constructors / Destructors
	CNTServiceTerminateException(DWORD dwWin32ExitCode, DWORD dwServiceSpecificExitCode);
  
//member variables
	DWORD m_dwWin32ExitCode;
	DWORD m_dwServiceSpecificExitCode;
};


//An MFC framework encapsulation of an NT service. You are meant to derive your 
//own class from this and override its functions to implement your own service 
//specific functionality.
class CNTSERVICE_EXT_CLASS CNTService
{
public:
//Defines
  #define STATE_NO_CHANGE 0xffffffff

  //Used in SetServiceToStatus
  enum ServiceAction 
  {
    ActionStartService,
    ActionPauseService,
    ActionContinueService,
    ActionStopService
  };

  enum UIErrorLoggingDetail
  {
    UI_ErrorCode,
    UI_ErrorCodeAndErrorDescription,
    UI_ErrorDescription,
    UI_StringAndErrorCode,
    UI_StringAndErrorCodeAndErrorDescription,
    UI_StringAndErrorDescription
  };

  enum ELErrorLoggingDetail
  {
    EL_ErrorCode,
    EL_ErrorCodeAndErrorDescription,
    EL_ErrorDescription,
  };

//Constructors / Destructors
  CNTService();
	CNTService(LPCTSTR lpszServiceName, LPCTSTR lpszDisplayName, DWORD dwControlsAccepted, LPCTSTR lpszDescription = NULL); 
	virtual ~CNTService();

//Accessors / Mutators
  CString GetServiceName() const { return m_sServiceName; };
  CString GetInstanceServiceName() const { return m_sServiceName; };
  CString GetMasterServiceName() const { return m_sMasterServiceName; }
  void    SetServiceName(const CString& sServiceName);
  void    SetInstanceServiceName(const CString& sServiceName) { m_sServiceName = sServiceName; };
  void    SetMasterServiceName(const CString sServiceName) { m_sMasterServiceName = sServiceName; };
  CString GetDisplayName() const { return m_sDisplayName; };
  CString GetInstanceDisplayName() const { return m_sDisplayName; };
  CString GetMasterDisplayName() const { return m_sMasterDisplayName; };
  void    SetDisplayName(const CString& sDisplayName);
  void    SetInstanceDisplayName(const CString& sDisplayName) { m_sDisplayName = sDisplayName; };
  void    SetMasterDisplayName(const CString& sDisplayName) { m_sMasterDisplayName = sDisplayName; };
  CString GetDescription() const { return m_sDescription; };
  CString GetInstanceDescription() const { return m_sDescription; };
  CString GetMasterDescription() const { return m_sMasterDescription; };
  void    SetDescription(const CString& sDescription);
  void    SetInstanceDescription(const CString& sDescription) { m_sDescription = sDescription; };
  void    SetMasterDescription(const CString& sDescription) { m_sMasterDescription = sDescription; };
	void    SetAllowCommandLine(BOOL bCommandLine) { m_bAllowCommandLine = bCommandLine; };
	BOOL    GetAllowCommandLine() const { return m_bAllowCommandLine; };
	void    SetAllowNameChange(BOOL bNameChange) { m_bAllowNameChange = bNameChange; };
	BOOL    GetAllowNameChange() const { return m_bAllowNameChange; };
	void    SetAllowDescriptionChange(BOOL bDescriptionChange) { m_bAllowDescriptionChange = bDescriptionChange; };
	BOOL    GetAllowDescriptionChange() const { return m_bAllowDescriptionChange; };
	void    SetAllowDisplayNameChange(BOOL bDisplayNameChange) { m_bAllowDisplayNameChange = bDisplayNameChange; };
	BOOL    GetAllowDisplayNameChange() const { return m_bAllowDisplayNameChange; };
  void    SetUseConsole(BOOL bUseConsole) { m_bUseConsole = bUseConsole; };
  BOOL    GetUseConsole() const { return m_bUseConsole; };
  void    SetControlsAccepted(DWORD dwControlsAccepted) { m_dwControlsAccepted = dwControlsAccepted; };
  DWORD   GetControlsAccepted() const { return m_dwControlsAccepted; };

//Persistance support
	//Allows saving and restoring of a services settings to the 
	//"HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\ServiceName\Parameters"
  //location in the registry
	virtual BOOL    WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue);
	virtual BOOL    WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue);
  virtual BOOL    WriteProfileStringArray(LPCTSTR lpszSection, LPCTSTR lpszEntry, const CStringArray& array);
	virtual BOOL    WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes);

	virtual CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL, DWORD* pLastError = NULL);
	virtual UINT    GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault, DWORD* pLastError = NULL);
  virtual BOOL    GetProfileStringArray(LPCTSTR lpszSection, LPCTSTR lpszEntry, CStringArray& array); 
	virtual BOOL    GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE* ppData, UINT* pBytes);

  //These versions of the persistence allow control over the "ServiceName" to write to as described above aswell
  //as control over the bFlush value 
  static BOOL     WriteProfileString(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue, BOOL bFlush, DWORD* pLastError = NULL);
  static BOOL     WriteProfileInt(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue, BOOL bFlush, DWORD* pLastError = NULL);
  static BOOL     WriteProfileStringArray(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, const CStringArray& array, BOOL bFlush, DWORD* pLastError = NULL);
  static BOOL     WriteProfileBinary(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes, BOOL bFlush, DWORD* pLastError = NULL);
  static CString  GetProfileString(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault = NULL, DWORD* pLastError = NULL);
  static UINT     GetProfileInt(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault, DWORD* pLastError = NULL);
  static BOOL     GetProfileStringArray(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, CStringArray& array, DWORD* pLastError = NULL);
  static BOOL     GetProfileBinary(LPCTSTR lpszService, LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE* ppData, UINT* pBytes, DWORD* pLastError = NULL);

	//Allows client apps to decide if the above settings should be flushed to the registry
	//or allow them to be written to the registry in a lazy fashion
	void SetProfileWriteFlush(BOOL bFlush) { m_bProfileWriteFlush = bFlush; };
	BOOL GetProfileWriteFlush() const { return m_bProfileWriteFlush; };

//Other Methods
  //Helpful functions to parse the command line and execute the results
	virtual void ParseCommandLine(CNTServiceCommandLineInfo& rCmdInfo);
	virtual DWORD ProcessShellCommand(CNTServiceCommandLineInfo& rCmdInfo);

	//Reports the status of this service back to the SCM
	virtual BOOL ReportStatus();
	virtual BOOL ReportStatus(DWORD dwCurrentState, DWORD dwCheckPoint = STATE_NO_CHANGE,
                            DWORD dwWaitHint = STATE_NO_CHANGE, DWORD dwControlsAccepted = STATE_NO_CHANGE);

	//Installs the callback funtion by calling RegisterServiceCtrlHandler
	virtual BOOL RegisterCtrlHandler();

	//Member function which does the job of responding to SCM requests
  virtual DWORD WINAPI ServiceCtrlHandler(DWORD dwControl, DWORD dwEventType, LPVOID lpEventData);

	//The ServiceMain function for this service
	virtual void WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);

	//Called in reponse to a shutdown request
	virtual void OnStop();

	//Called in reponse to a pause request
	virtual void OnPause();

	//Called in reponse to a continue request
	virtual void OnContinue();

	//Called in reponse to a Interrogate request
	virtual void OnInterrogate();

	//Called in reponse to a Shutdown request
	virtual void OnShutdown();

  //Called in response to a "param change" (Win2k only)
  virtual void OnParamChange();

  //Called in response to a "hardware profile change" (Win2k only)
  virtual DWORD OnHardwareProfileChange(DWORD dwEventType, LPVOID lpEventData);

  //Called in response to a "power event" (Win2k only)
  virtual DWORD OnPowerEvent(DWORD dwEventType, LPVOID lpEventData);

  //Called in response to a something being added to the services network binding (Win2k only)
  virtual void OnNetBindAdd();

  //Called in response to a something being removed from the services network binding (Win2k only)
  virtual void OnNetBindRemove();

  //Called in response to a something being enabled in a services network binding (Win2k only)
  virtual void OnNetBindEnable();

  //Called in response to a something being disabled in a services network binding (Win2k only)
  virtual void OnNetBindDisable();

  //Called in response to a SERVICE_CONTROL_DEVICEEVENT control request (Win2k only)
  virtual DWORD OnDeviceEvent(DWORD dwEventType, LPVOID lpEventData);

	//Called in reponse to a user defined request
	virtual void OnUserDefinedRequest(DWORD dwControl);

	//Kicks off the Service. You would normally call this
	//some where in your main/wmain or InitInstance
	//a standard process rather than as a service. If you are
  //using the CNTServiceCommandLineInfo class, then internally
  //it will call this function for you.
	virtual BOOL Run();

  //Puts a service to a certain status
  virtual BOOL SetServiceToStatus(CNTService::ServiceAction esaStatusWanted);

	//Installs the service
	virtual BOOL Install(CString& sErrorMsg, DWORD& dwError);

	//Uninstalls the service
	virtual BOOL Uninstall(CString& sErrorMsg, DWORD& dwError, DWORD dwTimeToWaitForStop = 5000);

	//Runs the service as a normal function as opposed
	//to a service
	virtual void Debug();

	//Displays help for this service
	virtual void ShowHelp();

  //Enumerate all instances of this service installed on the local machine
  virtual BOOL EnumerateInstances(CStringArray& ServiceNames, DWORD& dwError);

public:
//Variables used to control the call to CreateService
  DWORD                 m_dwServiceType;
  DWORD                 m_dwStartType;
  DWORD                 m_dwErrorControl;
  CString               m_sLoadOrderGroup;
  CString               m_sUserName;
  CString               m_sPassword;
  CString               m_sMessageDll;
  UIErrorLoggingDetail  m_UILoggingDetail;
  ELErrorLoggingDetail  m_ELLoggingDetail;
  CStringArray          m_sDependencies;
  BOOL                  m_bRegisterEventLogSource;

//Implementation, Does use these variables unless you really need. Instead use
//the public methods and data above
  SERVICE_STATUS_HANDLE m_hStatus;
  DWORD                 m_dwControlsAccepted;      //What Control requests will this service repond to
  DWORD                 m_dwCheckPoint;            
  DWORD                 m_dwWaitHint;              
  DWORD                 m_dwCurrentState;          //Current Status of the service
  DWORD                 m_dwRequestedControl;      //The most recent value sent into ServiceCtrlHandler
  CString               m_sServiceName;            //Name of the service
  CString               m_sMasterServiceName;      //The name of the service (unaffected by calls to change it via /SN)
  CString               m_sDisplayName;            //Display name for the service
  CString               m_sMasterDisplayName;      //The display name of the service (unaffected by calls to change it via /SDN)
  CString               m_sDescription;            //The description text for the service
  CString               m_sMasterDescription;      //THe description text for the service (unaffected by calls to change it via /SD)
  CNTEventLogSource     m_EventLogSource;          //For reporting to the event log
	static CNTService*    sm_lpService;						   //Static which contains the this pointer
  CCriticalSection      m_CritSect;                //Protects changes to any member variables from multiple threads
  BOOL                  m_bProfileWriteFlush;      //Should calls to WriteProfile... be synchronous or left to be written by the lazy writer
  BOOL                  m_bAllowCommandLine;       //Should /SCL command line settings be observed
  BOOL                  m_bAllowNameChange;        //Should /SN command line settings be observed 
  BOOL                  m_bAllowDescriptionChange; //Should /SD command line settings be observed
  BOOL                  m_bAllowDisplayNameChange; //Should /SDN command line settings be observed
  BOOL                  m_bUseConsole;             //TRUE if console output should be used, FALSE for GUI
  CString               m_sBinaryPathName;         //The binary path we use for installing

protected:
//Methods
  //These three static functions are used internally to
  //go from the SDK functions to the C++ member functions
	static void WINAPI _ServiceCtrlHandler(DWORD dwControl);	
  static DWORD WINAPI _ServiceCtrlHandlerEx(DWORD dwControl, DWORD dwEventType,  
                                            LPVOID lpEventData, LPVOID lpContext);
	static void WINAPI _SDKServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);

  //Actual C++ implementation of ServiceMain
  virtual void _ServiceMain(DWORD dwArgv, LPTSTR* lpszArgv);

  //Function used by constructors to set the initial state of our variables;
  virtual void Initialize(LPCTSTR lpszServiceName, LPCTSTR lpszDisplayName, DWORD dwControlsAccepted, LPCTSTR lpszDescription);

  //Helper function to covert a Win32 Error code to a string
  virtual CString Win32ErrorToString(UINT nStringID, DWORD dwError, BOOL bEventLog);

	//Used internally by the persistance functions
  static HKEY GetSectionKey(LPCTSTR lpszServiceName, LPCTSTR lpszSection, BOOL bReadOnly = FALSE, DWORD* pLastError = NULL);
  static HKEY GetServiceRegistryKey(LPCTSTR lpszServiceName, BOOL bReadOnly = FALSE, DWORD* pLastError = NULL);

  //Actual implementation of the function to report status to the SCM
  virtual BOOL _ReportStatus(DWORD dwCurrentState, DWORD dwCheckPoint = STATE_NO_CHANGE,
                             DWORD dwWaitHint = STATE_NO_CHANGE, DWORD dwControlsAccepted = STATE_NO_CHANGE,
                             DWORD dwWin32ExitCode = NO_ERROR, DWORD dwServiceSpecificExitCode = 0);

  //Used during the Install procedure
  virtual LPTSTR GetDependencies();

  //Used by EnumerateInstances
  static BOOL CALLBACK _EnumerateInstances(void* pData, ENUM_SERVICE_STATUS& ss);

  //Terminate the service
  void TerminateService(DWORD dwWin32ExitCode = NO_ERROR, DWORD dwServiceSpecificExitCode = 0);

  //Console Control handler
  static BOOL WINAPI _ConsoleCtrlHandler(DWORD dwCtrlType);
  virtual BOOL ConsoleCtrlHandler(DWORD dwCtrlType);
};

#endif //__NTSERV_H__
