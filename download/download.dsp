# Microsoft Developer Studio Project File - Name="download" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=download - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "download.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "download.mak" CFG="download - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "download - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "download - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "download - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\SysInfo" /I "..\OcsWmi" /I "../include/openssl/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 libeay32.lib ssleay32.lib zip.lib zlib.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc" /out:"..\_Release\download.exe " /libpath:"..\include\Zip\Release" /libpath:"..\include\openssl\lib\VC" /libpath:"..\include\zlib" /libpath:"C:\Program Files\Microsoft Platform SDK\Lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "download - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /I "..\SysInfo" /I "..\OcsWmi" /I "../include/openssl/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 libeay32.lib ssleay32.lib zlib.lib zip.lib srclient.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\_Debug\download.exe" /pdbtype:sept /libpath:"C:\Program Files\Vieux Microsoft SDK\Lib" /libpath:"..\include\Zip\Debug" /libpath:"..\include\openssl\lib\VC" /libpath:"..\include\zlib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "download - Win32 Release"
# Name "download - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\include\_common\commonDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\download.cpp
# End Source File
# Begin Source File

SOURCE=.\download.rc
# End Source File
# Begin Source File

SOURCE=.\downloadDlg.cpp
# End Source File
# Begin Source File

SOURCE=..\include\fileoperations\FileOperations.cpp
# End Source File
# Begin Source File

SOURCE=..\include\_common\FilePackageHistory.cpp
# End Source File
# Begin Source File

SOURCE=..\include\zlib\flate.cpp
# End Source File
# Begin Source File

SOURCE=..\include\xml\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\utils.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\_common\commonDownload.h
# End Source File
# Begin Source File

SOURCE=.\download.h
# End Source File
# Begin Source File

SOURCE=.\downloadDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\_common\FilePackageHistory.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\utils.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\download.ico
# End Source File
# Begin Source File

SOURCE=.\res\download.rc2
# End Source File
# Begin Source File

SOURCE=".\logo OCS-ng-48.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\include\OpenSSL\include\openssl\asn1.h
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
