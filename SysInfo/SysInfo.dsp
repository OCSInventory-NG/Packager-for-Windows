# Microsoft Developer Studio Project File - Name="SysInfo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=SysInfo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SysInfo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SysInfo.mak" CFG="SysInfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SysInfo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "SysInfo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SysInfo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /WX /GX /O2 /I "../includes" /I "../OcsWmi" /I "C:\Program Files\SDK2003R2\Lib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /YX"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 wbemuuid.lib ws2_32.lib libeay32.lib setupapi.lib /nologo /dll /machine:I386 /out:"..\_Release\SysInfo.dll" /libpath:"C:\Program Files\SDK\Fev2003\Lib" /libpath:"..\include\Zip\Release" /libpath:"..\include\openssl\lib\VC" /libpath:"..\include\zlib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GX /ZI /Od /I "../includes" /I "../OcsWmi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wbemuuid.lib ws2_32.lib libeay32.lib setupapi.lib /nologo /dll /debug /machine:I386 /out:"..\_Debug\SysInfo.dll" /pdbtype:sept /libpath:"C:\Program Files\vieux_sdk\Lib" /libpath:"..\include\Zip\Release" /libpath:"..\include\openssl\lib\VC" /libpath:"..\include\zlib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SysInfo - Win32 Release"
# Name "SysInfo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AccessLog.cpp
# End Source File
# Begin Source File

SOURCE=.\AccountInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\BIOS.cpp
# End Source File
# Begin Source File

SOURCE=.\cpu_info.cpp
# End Source File
# Begin Source File

SOURCE=.\DebugLog.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceComments.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceCommentsList.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceInventoryList.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceRepairs.cpp
# End Source File
# Begin Source File

SOURCE=.\DeviceRepairsList.cpp
# End Source File
# Begin Source File

SOURCE=.\Dtwinver.cpp
# End Source File
# Begin Source File

SOURCE=.\EDID.cpp
# End Source File
# Begin Source File

SOURCE=.\FileVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\InputDeviceList.cpp
# End Source File
# Begin Source File

SOURCE=.\IPHelper.cpp
# End Source File
# Begin Source File

SOURCE=.\LogicalDrive.cpp
# End Source File
# Begin Source File

SOURCE=.\LogicalDriveList.cpp
# End Source File
# Begin Source File

SOURCE=..\include\xml\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\Memory.cpp
# End Source File
# Begin Source File

SOURCE=.\MemorySlot.cpp
# End Source File
# Begin Source File

SOURCE=.\MemorySlotList.cpp
# End Source File
# Begin Source File

SOURCE=.\Modem.cpp
# End Source File
# Begin Source File

SOURCE=.\ModemList.cpp
# End Source File
# Begin Source File

SOURCE=.\Monitor.cpp
# End Source File
# Begin Source File

SOURCE=.\MonitorList.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkAdapter.cpp
# End Source File
# Begin Source File

SOURCE=.\NetworkAdapterList.cpp
# End Source File
# Begin Source File

SOURCE=.\OcsCrypto.cpp
# End Source File
# Begin Source File

SOURCE=.\OcsProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\Printer.cpp
# End Source File
# Begin Source File

SOURCE=.\PrinterList.cpp
# End Source File
# Begin Source File

SOURCE=.\Registry.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryValue.cpp
# End Source File
# Begin Source File

SOURCE=.\RegistryValueList.cpp
# End Source File
# Begin Source File

SOURCE=.\SNMP.cpp
# End Source File
# Begin Source File

SOURCE=.\SnmpAPI.cpp
# End Source File
# Begin Source File

SOURCE=.\Software.cpp
# End Source File
# Begin Source File

SOURCE=.\SoftwareList.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundDeviceList.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StoragePeripheral.cpp
# End Source File
# Begin Source File

SOURCE=.\StoragePeripheralList.cpp
# End Source File
# Begin Source File

SOURCE=.\SysInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemController.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemControllerList.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemPort.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemPortList.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemSlot.cpp
# End Source File
# Begin Source File

SOURCE=.\SystemSlotList.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoAdapter.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoAdapterList.cpp
# End Source File
# Begin Source File

SOURCE=.\WindowsSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\Wmi.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AccessLog.h
# End Source File
# Begin Source File

SOURCE=.\AccountInfo.h
# End Source File
# Begin Source File

SOURCE=.\BIOS.h
# End Source File
# Begin Source File

SOURCE=.\cpu_info.h
# End Source File
# Begin Source File

SOURCE=.\DebugLog.h
# End Source File
# Begin Source File

SOURCE=.\DeviceComments.h
# End Source File
# Begin Source File

SOURCE=.\DeviceCommentsList.h
# End Source File
# Begin Source File

SOURCE=.\DeviceInventory.h
# End Source File
# Begin Source File

SOURCE=.\DeviceInventoryList.h
# End Source File
# Begin Source File

SOURCE=.\DeviceProperties.h
# End Source File
# Begin Source File

SOURCE=.\DeviceRepairs.h
# End Source File
# Begin Source File

SOURCE=.\DeviceRepairsList.h
# End Source File
# Begin Source File

SOURCE=.\Dtwinver.h
# End Source File
# Begin Source File

SOURCE=.\EDID.h
# End Source File
# Begin Source File

SOURCE=.\FileVersion.h
# End Source File
# Begin Source File

SOURCE=.\InputDevice.h
# End Source File
# Begin Source File

SOURCE=.\InputDeviceList.h
# End Source File
# Begin Source File

SOURCE=.\IPHelper.h
# End Source File
# Begin Source File

SOURCE=.\LogicalDrive.h
# End Source File
# Begin Source File

SOURCE=.\LogicalDriveList.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\Memory.h
# End Source File
# Begin Source File

SOURCE=.\MemorySlot.h
# End Source File
# Begin Source File

SOURCE=.\MemorySlotList.h
# End Source File
# Begin Source File

SOURCE=.\Modem.h
# End Source File
# Begin Source File

SOURCE=.\ModemList.h
# End Source File
# Begin Source File

SOURCE=.\Monitor.h
# End Source File
# Begin Source File

SOURCE=.\MonitorList.h
# End Source File
# Begin Source File

SOURCE=.\NetworkAdapter.h
# End Source File
# Begin Source File

SOURCE=.\NetworkAdapterList.h
# End Source File
# Begin Source File

SOURCE=.\OcsCrypto.h
# End Source File
# Begin Source File

SOURCE=.\OcsProcess.h
# End Source File
# Begin Source File

SOURCE=.\Printer.h
# End Source File
# Begin Source File

SOURCE=.\PrinterList.h
# End Source File
# Begin Source File

SOURCE=.\Registry.h
# End Source File
# Begin Source File

SOURCE=.\RegistryValue.h
# End Source File
# Begin Source File

SOURCE=.\RegistryValueList.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\SNMP.h
# End Source File
# Begin Source File

SOURCE=.\SnmpAPI.h
# End Source File
# Begin Source File

SOURCE=.\Software.h
# End Source File
# Begin Source File

SOURCE=.\SoftwareList.h
# End Source File
# Begin Source File

SOURCE=.\SoundDevice.h
# End Source File
# Begin Source File

SOURCE=.\SoundDeviceList.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StoragePeripheral.h
# End Source File
# Begin Source File

SOURCE=.\StoragePeripheralList.h
# End Source File
# Begin Source File

SOURCE=.\SysInfo.h
# End Source File
# Begin Source File

SOURCE=.\SysInfoClasses.h
# End Source File
# Begin Source File

SOURCE=.\SystemController.h
# End Source File
# Begin Source File

SOURCE=.\SystemControllerList.h
# End Source File
# Begin Source File

SOURCE=.\SystemPort.h
# End Source File
# Begin Source File

SOURCE=.\SystemPortList.h
# End Source File
# Begin Source File

SOURCE=.\SystemSlot.h
# End Source File
# Begin Source File

SOURCE=.\SystemSlotList.h
# End Source File
# Begin Source File

SOURCE=.\VideoAdapter.h
# End Source File
# Begin Source File

SOURCE=.\VideoAdapterList.h
# End Source File
# Begin Source File

SOURCE=.\WindowsSocket.h
# End Source File
# Begin Source File

SOURCE=.\Wmi.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\SysInfo.rc
# End Source File
# End Group
# Begin Group "External Libraries"

# PROP Default_Filter "lib"
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
