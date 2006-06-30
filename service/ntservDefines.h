/*
Module : NTSERVDEFINES.H
Purpose: Various defines which the MFC class framework which encapsulate the whole area of services on NT, 2000, XP, and Server 2003 require
Created: PJN / 08-09-2003

Copyright (c) 1997 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __NTSERVDEFINES_H__
#define __NTSERVDEFINES_H__



//////////////////////// Enums / Defines //////////////////////////////////////

//Define some values if the "NTSERV_DO_NEW_WINSVC_DEFINES" define is present. This means that the class will 
//at least compile even when you do not have the latest and greatest Platform SDK installed such as when using
//the code with VC 5 or VC 6 on their own. 

#ifdef NTSERV_DO_NEW_WINSVC_DEFINES

//The following defines are taken from the Platform SDK header file "WinSvc.h"

typedef struct _SERVICE_STATUS_PROCESS 
{
  DWORD dwServiceType;
  DWORD dwCurrentState;
  DWORD dwControlsAccepted;
  DWORD dwWin32ExitCode;
  DWORD dwServiceSpecificExitCode;
  DWORD dwCheckPoint;
  DWORD dwWaitHint;
  DWORD dwProcessId;
  DWORD dwServiceFlags;
} 
SERVICE_STATUS_PROCESS, *LPSERVICE_STATUS_PROCESS;

typedef struct _ENUM_SERVICE_STATUS_PROCESSA 
{
  LPSTR                  lpServiceName;
  LPSTR                  lpDisplayName;
  SERVICE_STATUS_PROCESS ServiceStatusProcess;
} 
ENUM_SERVICE_STATUS_PROCESSA, *LPENUM_SERVICE_STATUS_PROCESSA;

typedef struct _ENUM_SERVICE_STATUS_PROCESSW 
{
  LPWSTR                 lpServiceName;
  LPWSTR                 lpDisplayName;
  SERVICE_STATUS_PROCESS ServiceStatusProcess;
} 
ENUM_SERVICE_STATUS_PROCESSW, *LPENUM_SERVICE_STATUS_PROCESSW;

#ifdef UNICODE
typedef ENUM_SERVICE_STATUS_PROCESSW ENUM_SERVICE_STATUS_PROCESS;
typedef LPENUM_SERVICE_STATUS_PROCESSW LPENUM_SERVICE_STATUS_PROCESS;
#else
typedef ENUM_SERVICE_STATUS_PROCESSA ENUM_SERVICE_STATUS_PROCESS;
typedef LPENUM_SERVICE_STATUS_PROCESSA LPENUM_SERVICE_STATUS_PROCESS;
#endif // UNICODE

typedef DWORD (WINAPI *LPHANDLER_FUNCTION_EX)(DWORD, DWORD, LPVOID, LPVOID);

typedef enum _SC_STATUS_TYPE 
{
  SC_STATUS_PROCESS_INFO = 0
} SC_STATUS_TYPE;

typedef enum _SC_ENUM_TYPE 
{
  SC_ENUM_PROCESS_INFO = 0
} SC_ENUM_TYPE;


#define SERVICE_CONFIG_DESCRIPTION     1
#define SERVICE_CONFIG_FAILURE_ACTIONS 2

#define SERVICE_CONTROL_PARAMCHANGE            0x00000006
#define SERVICE_CONTROL_NETBINDADD             0x00000007
#define SERVICE_CONTROL_NETBINDREMOVE          0x00000008
#define SERVICE_CONTROL_NETBINDENABLE          0x00000009
#define SERVICE_CONTROL_NETBINDDISABLE         0x0000000A
#define SERVICE_CONTROL_DEVICEEVENT            0x0000000B
#define SERVICE_CONTROL_HARDWAREPROFILECHANGE  0x0000000C
#define SERVICE_CONTROL_POWEREVENT             0x0000000D

#ifndef NTSERV_EXCLUDE_VC6_WINSVC_DEFINES

typedef enum _SC_ACTION_TYPE 
{
  SC_ACTION_NONE        = 0,
  SC_ACTION_RESTART     = 1,
  SC_ACTION_REBOOT      = 2,
  SC_ACTION_RUN_COMMAND = 3
} SC_ACTION_TYPE;

typedef struct _SC_ACTION 
{
  SC_ACTION_TYPE  Type;
  DWORD           Delay;
} SC_ACTION, *LPSC_ACTION;

typedef struct _SERVICE_FAILURE_ACTIONSA 
{
  DWORD       dwResetPeriod;
  LPSTR       lpRebootMsg;
  LPSTR       lpCommand;
  DWORD       cActions;
#ifdef MIDL_PASS
  [size_is(cActions)]
#endif
  SC_ACTION* lpsaActions;
} 
SERVICE_FAILURE_ACTIONSA, *LPSERVICE_FAILURE_ACTIONSA;

typedef struct _SERVICE_FAILURE_ACTIONSW 
{
  DWORD       dwResetPeriod;
  LPWSTR      lpRebootMsg;
  LPWSTR      lpCommand;
  DWORD       cActions;
#ifdef MIDL_PASS
  [size_is(cActions)]
#endif
  SC_ACTION* lpsaActions;
} 
SERVICE_FAILURE_ACTIONSW, *LPSERVICE_FAILURE_ACTIONSW;

#ifdef UNICODE
typedef SERVICE_FAILURE_ACTIONSW SERVICE_FAILURE_ACTIONS;
typedef LPSERVICE_FAILURE_ACTIONSW LPSERVICE_FAILURE_ACTIONS;
#else
typedef SERVICE_FAILURE_ACTIONSA SERVICE_FAILURE_ACTIONS;
typedef LPSERVICE_FAILURE_ACTIONSA LPSERVICE_FAILURE_ACTIONS;
#endif // UNICODE

//
// Info levels for ChangeServiceConfig2 and QueryServiceConfig2
//
#define SERVICE_CONFIG_DESCRIPTION     1
#define SERVICE_CONFIG_FAILURE_ACTIONS 2

//
// Service description string
//
typedef struct _SERVICE_DESCRIPTIONA 
{
  LPSTR lpDescription;
} 
SERVICE_DESCRIPTIONA, *LPSERVICE_DESCRIPTIONA;
//
// Service description string
//
typedef struct _SERVICE_DESCRIPTIONW 
{
  LPWSTR      lpDescription;
} 
SERVICE_DESCRIPTIONW, *LPSERVICE_DESCRIPTIONW;

#ifdef UNICODE
typedef SERVICE_DESCRIPTIONW SERVICE_DESCRIPTION;
typedef LPSERVICE_DESCRIPTIONW LPSERVICE_DESCRIPTION;
#else
typedef SERVICE_DESCRIPTIONA SERVICE_DESCRIPTION;
typedef LPSERVICE_DESCRIPTIONA LPSERVICE_DESCRIPTION;
#endif // UNICODE

#endif //#ifndef NTSERV_EXCLUDE_VC6_WINSVC_DEFINES


#endif //NTSERV_DO_NEW_WINSVC_DEFINES


#endif //__NTSERVDEFINES_H__
