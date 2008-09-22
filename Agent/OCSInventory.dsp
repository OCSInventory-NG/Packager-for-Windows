# Microsoft Developer Studio Project File - Name="OCSInventory Agent" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=OCSInventory Agent - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "OCSInventory.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OCSInventory.mak" CFG="OCSInventory Agent - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OCSInventory Agent - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "OCSInventory Agent - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "OCSInventory Agent - Win32 Release"

# PROP BASE Use_MFC 5
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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "..\OcsDB" /I "..\SysInfo" /I "..\OcsWmi" /I "../include/openssl/include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_OCS_AGENT" /D "_AFXDLL" /FR /YX"StdAfx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x409 /i "C:\Program Files\SDK2003R2\Lib" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wbemuuid.lib zlibstat.lib libeay32.lib ssleay32.lib Ws2_32.lib wininet.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /out:"..\_Release\OCSInventory.exe" /libpath:"C:\Program Files\Microsoft Platform SDK\Lib" /libpath:"..\include\zlib" /libpath:"..\include\openssl\lib\VC"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "OCSInventory Agent - Win32 Debug"

# PROP BASE Use_MFC 5
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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /I "..\OcsDB" /I "..\SysInfo" /I "..\OcsWmi" /I "../include/openssl/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_OCS_AGENT" /D "_AFXDLL" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wbemuuid.lib zlibstat.lib libeay32.lib ssleay32.lib zlib.lib Ws2_32.lib wininet.lib /nologo /subsystem:windows /pdb:"Debug/de.pdb" /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"..\_Debug\OCSInventory.exe" /pdbtype:sept /libpath:"C:\Program Files\Vieux Microsoft SDK\Lib" /libpath:"..\include\zlib" /libpath:"..\include\openssl\lib\VC" /nodefaultlib:"libc.lib"/out:"..\Debug\OCSInventory.exe"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "OCSInventory Agent - Win32 Release"
# Name "OCSInventory Agent - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\include\_common\commonDownload.cpp
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

SOURCE=.\modules\ModuleDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleIpdiscover.cpp
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\OCSInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\OCSInventoryCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\OCSInventoryState.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\StoreInteract.cpp
# End Source File
# Begin Source File

SOURCE=.\XMLInteract.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\Program Files\Microsoft Visual Studio\VC98\MFC\Include\AFX.INL"
# End Source File
# Begin Source File

SOURCE="..\..\..\Program Files\Microsoft Visual Studio\VC98\MFC\Include\AFXCOLL.INL"
# End Source File
# Begin Source File

SOURCE="..\..\..\Program Files\Microsoft Visual Studio\VC98\MFC\Include\AFXWIN1.INL"
# End Source File
# Begin Source File

SOURCE=..\include\_common\defines.h
# End Source File
# Begin Source File

SOURCE=..\include\_common\FilePackageHistory.h
# End Source File
# Begin Source File

SOURCE=..\include\xml\Markup.h
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleApi.h
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleDownload.h
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleIpdiscover.h
# End Source File
# Begin Source File

SOURCE=.\modules\ModuleRegistry.h
# End Source File
# Begin Source File

SOURCE=..\include\_common\net_utils.h
# End Source File
# Begin Source File

SOURCE=.\OCSInventory.h
# End Source File
# Begin Source File

SOURCE=.\OCSInventoryState.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StoreInteract.h
# End Source File
# Begin Source File

SOURCE=..\SysInfo\SysInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\_common\utils.h
# End Source File
# Begin Source File

SOURCE=.\XMLInteract.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CSV_KO.ICO
# End Source File
# Begin Source File

SOURCE=.\res\CSV_OK.ICO
# End Source File
# Begin Source File

SOURCE=.\res\DAO_KO.ICO
# End Source File
# Begin Source File

SOURCE=.\res\DAO_OK.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\idr_main.ico
# End Source File
# Begin Source File

SOURCE=".\logo OCS-ng-16.ico"
# End Source File
# Begin Source File

SOURCE=".\logo OCS-ng-48.ico"
# End Source File
# Begin Source File

SOURCE=.\ocs.ico
# End Source File
# Begin Source File

SOURCE=.\res\OCSInventory.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OCSInventory.ico
# End Source File
# Begin Source File

SOURCE=.\OCSInventory.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\zipstream.ipp
# End Source File
# End Target
# End Project
