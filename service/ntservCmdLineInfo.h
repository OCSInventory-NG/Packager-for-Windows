/*
Module : NTSERVCMDLINEINFO.H
Purpose: Defines the interface for the class CTNServiceCommandLineInfo. 
Created: PJN / 14-07-1998

Copyright (c) 1997 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __NTSERVCMDLINEINFO_H__
#define __NTSERVCMDLINEINFO_H__

#ifndef CNTSERVICE_EXT_CLASS
#define CNTSERVICE_EXT_CLASS
#endif



////////////////////////////// Classes ///////////////////////////////////////////////

//The CNTServiceCommandLineInfo class aids in parsing the 
//command line at application startup of an NT Service. The 
//structure is styled upon the MFC class CCommandLineInfo
class CNTSERVICE_EXT_CLASS CNTServiceCommandLineInfo
{
public:
//Constructors / Destructors
	CNTServiceCommandLineInfo();

//Methods
	virtual void ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast);

//Data
  enum
  {
    RunAsService,
    StartTheService,
    PauseService,
    ContinueService,
    StopService,
    InstallService,
    UninstallService,
    DebugService,
    ShowServiceHelp
  } m_nShellCommand;

  DWORD   m_dwTimeout;
  BOOL    m_bSilent;
  CString m_sServiceCommandLine;
  CString m_sServiceName;
  CString m_sServiceDisplayName;
  CString m_sServiceDescription;
  CString m_sUserName;
  CString m_sPassword;
  BOOL    m_bAutoStart;
};

#endif //__NTSERVCMDLINEINFO_H__
