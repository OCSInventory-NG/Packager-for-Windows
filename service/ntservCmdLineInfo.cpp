/*  
Module : NTSERVCMDLINEINFO.CPP
Purpose: Implementation for the class CNTServiceCommandLineInfo 
Created: PJN / 14-07-1997
History: PJN / 11-01-2006 1. Command line which the service uses to start with can now be specified via a new /SCL command line option.
                          This value is parsed into CNTServiceCommandLineInfo::m_sServiceCommandLine. This value is used when the service
                          is being installed.
                          2. Optimized code in CNTServiceCommandLineInfo::CNTServiceCommandLineInfo.
                          3. Removed unnecessary CNTServiceCommandLineInfo destructor
                          4. Addition of a new /SD command line option which allows the description of the service to be used for 
                          registration to be customized at runtime. This value is parsed into CNTServiceCommandLineInfo::m_sServiceDescription.
                          5. Addition of a new /SN command line option which allows the service name to be used for registration to be 
                          customized at runtime. This value is parsed into CNTServiceCommandLineInfo::m_sServiceDescription.
                          5. Addition of a new /SDN command line option which allows the service display name to be used for registration 
                          to be customized at runtime. This value is parsed into CNTServiceCommandLineInfo::m_sServiceDisplayName.
                          6. Addition of 2 new command line options namely "/App" or "/Application". These behave the same way as the 
                          existing "/Debug" command line option.
                          7. Addition of a new /U command line option which allows the user account which the service runs under to be 
                          configured.
                          8. Addition of a new /P command line option which allows the password which the service is to run with to be 
                          configured.
         PJN / 13-01-2006 1. Addition of a new /AUTO command line option which allows you to specify that the service should be started
                          automatically.

Copyright (c) 1996 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


/////////////////////////////////  Includes  //////////////////////////////////

#include "stdafx.h"
#include "ntservCmdLineInfo.h"



/////////////////////////////////  Macros /////////////////////////////////////

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



///////////////////////////////// Implementation //////////////////////////////

CNTServiceCommandLineInfo::CNTServiceCommandLineInfo() : m_nShellCommand(RunAsService),
                                                         m_dwTimeout(5000),
                                                         m_bSilent(FALSE),
                                                         m_bAutoStart(FALSE)
{
}

void CNTServiceCommandLineInfo::ParseParam(LPCTSTR pszParam, BOOL bFlag, BOOL bLast)
{
	if (bFlag)
	{
    CString sParam(pszParam);
    CString sParamUpper(sParam);
    sParamUpper.MakeUpper();
    int nParamLength = sParam.GetLength();

    if (lstrcmpi(pszParam, _T("install")) == 0)
      m_nShellCommand = InstallService;
    else if (lstrcmpi(pszParam, _T("silent")) == 0)
      m_bSilent = TRUE;
    else if (lstrcmpi(pszParam, _T("start")) == 0)
      m_nShellCommand = StartTheService;
    else if (lstrcmpi(pszParam, _T("pause")) == 0)
      m_nShellCommand = PauseService;
    else if (lstrcmpi(pszParam, _T("continue")) == 0)
      m_nShellCommand = ContinueService;
    else if (lstrcmpi(pszParam, _T("stop")) == 0)
      m_nShellCommand = StopService;
    else if (lstrcmpi(pszParam, _T("auto")) == 0)
      m_bAutoStart = TRUE;
    else if ((lstrcmpi(pszParam, _T("remove")) == 0) ||
             (lstrcmpi(pszParam, _T("uninstall")) == 0) )
      m_nShellCommand = UninstallService;
    else if ((lstrcmpi(pszParam, _T("debug")) == 0) || (lstrcmpi(pszParam, _T("app")) == 0) || (lstrcmpi(pszParam, _T("application")) == 0))
      m_nShellCommand = DebugService;
    else if ((lstrcmpi(pszParam, _T("help")) == 0) ||
             (lstrcmpi(pszParam, _T("?")) == 0) )
      m_nShellCommand = ShowServiceHelp;
    else if (sParamUpper.Find(_T("T:")) == 0 && nParamLength > 2)
      m_dwTimeout = _ttoi(sParam.Right(nParamLength - 2));
    else if (sParamUpper.Find(_T("SCL:")) == 0 && nParamLength > 4)
      m_sServiceCommandLine = sParam.Right(nParamLength - 4);
    else if (sParamUpper.Find(_T("SD:")) == 0 && nParamLength > 3)
      m_sServiceDescription = sParam.Right(nParamLength - 3);
    else if (sParamUpper.Find(_T("SN:")) == 0 && nParamLength > 3)
      m_sServiceName = sParam.Right(nParamLength - 3);
    else if (sParamUpper.Find(_T("SDN:")) == 0 && nParamLength > 4)
      m_sServiceDisplayName = sParam.Right(nParamLength - 4);
    else if (sParamUpper.Find(_T("P:")) == 0 && nParamLength > 2)
      m_sPassword = sParam.Right(nParamLength - 2);
    else if (sParamUpper.Find(_T("U:")) == 0 && nParamLength > 2)
      m_sUserName = sParam.Right(nParamLength - 2);
	}
	else
	{
		//Currently don't support parsing anything from
		//the command line except flags
	}

	if (bLast)
	{
		//Again the we don't support anything for the
		//last parameter
	}
}



