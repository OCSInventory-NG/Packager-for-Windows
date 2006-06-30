# Microsoft Developer Studio Generated NMAKE File, Based on SysInfo.dsp
!IF "$(CFG)" == ""
CFG=SysInfo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SysInfo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SysInfo - Win32 Release" && "$(CFG)" != "SysInfo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SysInfo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Release\SysInfo.dll" "$(OUTDIR)\SysInfo.pch" "$(OUTDIR)\SysInfo.bsc"

!ELSE 

ALL : "OcsWmi - Win32 Release" "..\Release\SysInfo.dll" "$(OUTDIR)\SysInfo.pch" "$(OUTDIR)\SysInfo.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"OcsWmi - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AccessLog.obj"
	-@erase "$(INTDIR)\AccessLog.sbr"
	-@erase "$(INTDIR)\AccountInfo.obj"
	-@erase "$(INTDIR)\AccountInfo.sbr"
	-@erase "$(INTDIR)\BIOS.obj"
	-@erase "$(INTDIR)\BIOS.sbr"
	-@erase "$(INTDIR)\cpu_info.obj"
	-@erase "$(INTDIR)\cpu_info.sbr"
	-@erase "$(INTDIR)\DebugLog.obj"
	-@erase "$(INTDIR)\DebugLog.sbr"
	-@erase "$(INTDIR)\DeviceComments.obj"
	-@erase "$(INTDIR)\DeviceComments.sbr"
	-@erase "$(INTDIR)\DeviceCommentsList.obj"
	-@erase "$(INTDIR)\DeviceCommentsList.sbr"
	-@erase "$(INTDIR)\DeviceInventory.obj"
	-@erase "$(INTDIR)\DeviceInventory.sbr"
	-@erase "$(INTDIR)\DeviceInventoryList.obj"
	-@erase "$(INTDIR)\DeviceInventoryList.sbr"
	-@erase "$(INTDIR)\DeviceProperties.obj"
	-@erase "$(INTDIR)\DeviceProperties.sbr"
	-@erase "$(INTDIR)\DeviceRepairs.obj"
	-@erase "$(INTDIR)\DeviceRepairs.sbr"
	-@erase "$(INTDIR)\DeviceRepairsList.obj"
	-@erase "$(INTDIR)\DeviceRepairsList.sbr"
	-@erase "$(INTDIR)\Dtwinver.obj"
	-@erase "$(INTDIR)\Dtwinver.sbr"
	-@erase "$(INTDIR)\EDID.obj"
	-@erase "$(INTDIR)\EDID.sbr"
	-@erase "$(INTDIR)\FileVersion.obj"
	-@erase "$(INTDIR)\FileVersion.sbr"
	-@erase "$(INTDIR)\InputDevice.obj"
	-@erase "$(INTDIR)\InputDevice.sbr"
	-@erase "$(INTDIR)\InputDeviceList.obj"
	-@erase "$(INTDIR)\InputDeviceList.sbr"
	-@erase "$(INTDIR)\IPHelper.obj"
	-@erase "$(INTDIR)\IPHelper.sbr"
	-@erase "$(INTDIR)\LogicalDrive.obj"
	-@erase "$(INTDIR)\LogicalDrive.sbr"
	-@erase "$(INTDIR)\LogicalDriveList.obj"
	-@erase "$(INTDIR)\LogicalDriveList.sbr"
	-@erase "$(INTDIR)\Markup.obj"
	-@erase "$(INTDIR)\Markup.sbr"
	-@erase "$(INTDIR)\Memory.obj"
	-@erase "$(INTDIR)\Memory.sbr"
	-@erase "$(INTDIR)\MemorySlot.obj"
	-@erase "$(INTDIR)\MemorySlot.sbr"
	-@erase "$(INTDIR)\MemorySlotList.obj"
	-@erase "$(INTDIR)\MemorySlotList.sbr"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\Modem.sbr"
	-@erase "$(INTDIR)\ModemList.obj"
	-@erase "$(INTDIR)\ModemList.sbr"
	-@erase "$(INTDIR)\Monitor.obj"
	-@erase "$(INTDIR)\Monitor.sbr"
	-@erase "$(INTDIR)\MonitorList.obj"
	-@erase "$(INTDIR)\MonitorList.sbr"
	-@erase "$(INTDIR)\NetworkAdapter.obj"
	-@erase "$(INTDIR)\NetworkAdapter.sbr"
	-@erase "$(INTDIR)\NetworkAdapterList.obj"
	-@erase "$(INTDIR)\NetworkAdapterList.sbr"
	-@erase "$(INTDIR)\OcsCrypto.obj"
	-@erase "$(INTDIR)\OcsCrypto.sbr"
	-@erase "$(INTDIR)\OcsProcess.obj"
	-@erase "$(INTDIR)\OcsProcess.sbr"
	-@erase "$(INTDIR)\Printer.obj"
	-@erase "$(INTDIR)\Printer.sbr"
	-@erase "$(INTDIR)\PrinterList.obj"
	-@erase "$(INTDIR)\PrinterList.sbr"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\Registry.sbr"
	-@erase "$(INTDIR)\RegistryValue.obj"
	-@erase "$(INTDIR)\RegistryValue.sbr"
	-@erase "$(INTDIR)\RegistryValueList.obj"
	-@erase "$(INTDIR)\RegistryValueList.sbr"
	-@erase "$(INTDIR)\SNMP.obj"
	-@erase "$(INTDIR)\SNMP.sbr"
	-@erase "$(INTDIR)\SnmpAPI.obj"
	-@erase "$(INTDIR)\SnmpAPI.sbr"
	-@erase "$(INTDIR)\Software.obj"
	-@erase "$(INTDIR)\Software.sbr"
	-@erase "$(INTDIR)\SoftwareList.obj"
	-@erase "$(INTDIR)\SoftwareList.sbr"
	-@erase "$(INTDIR)\SoundDevice.obj"
	-@erase "$(INTDIR)\SoundDevice.sbr"
	-@erase "$(INTDIR)\SoundDeviceList.obj"
	-@erase "$(INTDIR)\SoundDeviceList.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StoragePeripheral.obj"
	-@erase "$(INTDIR)\StoragePeripheral.sbr"
	-@erase "$(INTDIR)\StoragePeripheralList.obj"
	-@erase "$(INTDIR)\StoragePeripheralList.sbr"
	-@erase "$(INTDIR)\SysInfo.obj"
	-@erase "$(INTDIR)\SysInfo.pch"
	-@erase "$(INTDIR)\SysInfo.res"
	-@erase "$(INTDIR)\SysInfo.sbr"
	-@erase "$(INTDIR)\SystemController.obj"
	-@erase "$(INTDIR)\SystemController.sbr"
	-@erase "$(INTDIR)\SystemControllerList.obj"
	-@erase "$(INTDIR)\SystemControllerList.sbr"
	-@erase "$(INTDIR)\SystemPort.obj"
	-@erase "$(INTDIR)\SystemPort.sbr"
	-@erase "$(INTDIR)\SystemPortList.obj"
	-@erase "$(INTDIR)\SystemPortList.sbr"
	-@erase "$(INTDIR)\SystemSlot.obj"
	-@erase "$(INTDIR)\SystemSlot.sbr"
	-@erase "$(INTDIR)\SystemSlotList.obj"
	-@erase "$(INTDIR)\SystemSlotList.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VideoAdapter.obj"
	-@erase "$(INTDIR)\VideoAdapter.sbr"
	-@erase "$(INTDIR)\VideoAdapterList.obj"
	-@erase "$(INTDIR)\VideoAdapterList.sbr"
	-@erase "$(INTDIR)\WindowsSocket.obj"
	-@erase "$(INTDIR)\WindowsSocket.sbr"
	-@erase "$(INTDIR)\Wmi.obj"
	-@erase "$(INTDIR)\Wmi.sbr"
	-@erase "$(OUTDIR)\SysInfo.bsc"
	-@erase "$(OUTDIR)\SysInfo.exp"
	-@erase "$(OUTDIR)\SysInfo.lib"
	-@erase "..\Release\SysInfo.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../includes" /I "../OcsWmi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SysInfo.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\SysInfo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SysInfo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AccessLog.sbr" \
	"$(INTDIR)\AccountInfo.sbr" \
	"$(INTDIR)\BIOS.sbr" \
	"$(INTDIR)\cpu_info.sbr" \
	"$(INTDIR)\DebugLog.sbr" \
	"$(INTDIR)\DeviceComments.sbr" \
	"$(INTDIR)\DeviceCommentsList.sbr" \
	"$(INTDIR)\DeviceInventory.sbr" \
	"$(INTDIR)\DeviceInventoryList.sbr" \
	"$(INTDIR)\DeviceProperties.sbr" \
	"$(INTDIR)\DeviceRepairs.sbr" \
	"$(INTDIR)\DeviceRepairsList.sbr" \
	"$(INTDIR)\Dtwinver.sbr" \
	"$(INTDIR)\EDID.sbr" \
	"$(INTDIR)\FileVersion.sbr" \
	"$(INTDIR)\InputDevice.sbr" \
	"$(INTDIR)\InputDeviceList.sbr" \
	"$(INTDIR)\IPHelper.sbr" \
	"$(INTDIR)\LogicalDrive.sbr" \
	"$(INTDIR)\LogicalDriveList.sbr" \
	"$(INTDIR)\Markup.sbr" \
	"$(INTDIR)\Memory.sbr" \
	"$(INTDIR)\MemorySlot.sbr" \
	"$(INTDIR)\MemorySlotList.sbr" \
	"$(INTDIR)\Modem.sbr" \
	"$(INTDIR)\ModemList.sbr" \
	"$(INTDIR)\Monitor.sbr" \
	"$(INTDIR)\MonitorList.sbr" \
	"$(INTDIR)\NetworkAdapter.sbr" \
	"$(INTDIR)\NetworkAdapterList.sbr" \
	"$(INTDIR)\OcsCrypto.sbr" \
	"$(INTDIR)\OcsProcess.sbr" \
	"$(INTDIR)\Printer.sbr" \
	"$(INTDIR)\PrinterList.sbr" \
	"$(INTDIR)\Registry.sbr" \
	"$(INTDIR)\RegistryValue.sbr" \
	"$(INTDIR)\RegistryValueList.sbr" \
	"$(INTDIR)\SNMP.sbr" \
	"$(INTDIR)\SnmpAPI.sbr" \
	"$(INTDIR)\Software.sbr" \
	"$(INTDIR)\SoftwareList.sbr" \
	"$(INTDIR)\SoundDevice.sbr" \
	"$(INTDIR)\SoundDeviceList.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StoragePeripheral.sbr" \
	"$(INTDIR)\StoragePeripheralList.sbr" \
	"$(INTDIR)\SysInfo.sbr" \
	"$(INTDIR)\SystemController.sbr" \
	"$(INTDIR)\SystemControllerList.sbr" \
	"$(INTDIR)\SystemPort.sbr" \
	"$(INTDIR)\SystemPortList.sbr" \
	"$(INTDIR)\SystemSlot.sbr" \
	"$(INTDIR)\SystemSlotList.sbr" \
	"$(INTDIR)\VideoAdapter.sbr" \
	"$(INTDIR)\VideoAdapterList.sbr" \
	"$(INTDIR)\WindowsSocket.sbr" \
	"$(INTDIR)\Wmi.sbr"

"$(OUTDIR)\SysInfo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib ws2_32.lib libeay32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\SysInfo.pdb" /machine:I386 /out:"..\Release\SysInfo.dll" /implib:"$(OUTDIR)\SysInfo.lib" /libpath:"C:\Program Files\Microsoft SDK\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\AccessLog.obj" \
	"$(INTDIR)\AccountInfo.obj" \
	"$(INTDIR)\BIOS.obj" \
	"$(INTDIR)\cpu_info.obj" \
	"$(INTDIR)\DebugLog.obj" \
	"$(INTDIR)\DeviceComments.obj" \
	"$(INTDIR)\DeviceCommentsList.obj" \
	"$(INTDIR)\DeviceInventory.obj" \
	"$(INTDIR)\DeviceInventoryList.obj" \
	"$(INTDIR)\DeviceProperties.obj" \
	"$(INTDIR)\DeviceRepairs.obj" \
	"$(INTDIR)\DeviceRepairsList.obj" \
	"$(INTDIR)\Dtwinver.obj" \
	"$(INTDIR)\EDID.obj" \
	"$(INTDIR)\FileVersion.obj" \
	"$(INTDIR)\InputDevice.obj" \
	"$(INTDIR)\InputDeviceList.obj" \
	"$(INTDIR)\IPHelper.obj" \
	"$(INTDIR)\LogicalDrive.obj" \
	"$(INTDIR)\LogicalDriveList.obj" \
	"$(INTDIR)\Markup.obj" \
	"$(INTDIR)\Memory.obj" \
	"$(INTDIR)\MemorySlot.obj" \
	"$(INTDIR)\MemorySlotList.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\ModemList.obj" \
	"$(INTDIR)\Monitor.obj" \
	"$(INTDIR)\MonitorList.obj" \
	"$(INTDIR)\NetworkAdapter.obj" \
	"$(INTDIR)\NetworkAdapterList.obj" \
	"$(INTDIR)\OcsCrypto.obj" \
	"$(INTDIR)\OcsProcess.obj" \
	"$(INTDIR)\Printer.obj" \
	"$(INTDIR)\PrinterList.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RegistryValue.obj" \
	"$(INTDIR)\RegistryValueList.obj" \
	"$(INTDIR)\SNMP.obj" \
	"$(INTDIR)\SnmpAPI.obj" \
	"$(INTDIR)\Software.obj" \
	"$(INTDIR)\SoftwareList.obj" \
	"$(INTDIR)\SoundDevice.obj" \
	"$(INTDIR)\SoundDeviceList.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StoragePeripheral.obj" \
	"$(INTDIR)\StoragePeripheralList.obj" \
	"$(INTDIR)\SysInfo.obj" \
	"$(INTDIR)\SystemController.obj" \
	"$(INTDIR)\SystemControllerList.obj" \
	"$(INTDIR)\SystemPort.obj" \
	"$(INTDIR)\SystemPortList.obj" \
	"$(INTDIR)\SystemSlot.obj" \
	"$(INTDIR)\SystemSlotList.obj" \
	"$(INTDIR)\VideoAdapter.obj" \
	"$(INTDIR)\VideoAdapterList.obj" \
	"$(INTDIR)\WindowsSocket.obj" \
	"$(INTDIR)\Wmi.obj" \
	"$(INTDIR)\SysInfo.res" \
	"..\OcsWmi\Release\OcsWmi.lib"

"..\Release\SysInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug\SysInfo.dll" "$(OUTDIR)\SysInfo.pch"

!ELSE 

ALL : "OcsWmi - Win32 Debug" "..\Debug\SysInfo.dll" "$(OUTDIR)\SysInfo.pch"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"OcsWmi - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AccessLog.obj"
	-@erase "$(INTDIR)\AccountInfo.obj"
	-@erase "$(INTDIR)\BIOS.obj"
	-@erase "$(INTDIR)\cpu_info.obj"
	-@erase "$(INTDIR)\DebugLog.obj"
	-@erase "$(INTDIR)\DeviceComments.obj"
	-@erase "$(INTDIR)\DeviceCommentsList.obj"
	-@erase "$(INTDIR)\DeviceInventory.obj"
	-@erase "$(INTDIR)\DeviceInventoryList.obj"
	-@erase "$(INTDIR)\DeviceProperties.obj"
	-@erase "$(INTDIR)\DeviceRepairs.obj"
	-@erase "$(INTDIR)\DeviceRepairsList.obj"
	-@erase "$(INTDIR)\Dtwinver.obj"
	-@erase "$(INTDIR)\EDID.obj"
	-@erase "$(INTDIR)\FileVersion.obj"
	-@erase "$(INTDIR)\InputDevice.obj"
	-@erase "$(INTDIR)\InputDeviceList.obj"
	-@erase "$(INTDIR)\IPHelper.obj"
	-@erase "$(INTDIR)\LogicalDrive.obj"
	-@erase "$(INTDIR)\LogicalDriveList.obj"
	-@erase "$(INTDIR)\Markup.obj"
	-@erase "$(INTDIR)\Memory.obj"
	-@erase "$(INTDIR)\MemorySlot.obj"
	-@erase "$(INTDIR)\MemorySlotList.obj"
	-@erase "$(INTDIR)\Modem.obj"
	-@erase "$(INTDIR)\ModemList.obj"
	-@erase "$(INTDIR)\Monitor.obj"
	-@erase "$(INTDIR)\MonitorList.obj"
	-@erase "$(INTDIR)\NetworkAdapter.obj"
	-@erase "$(INTDIR)\NetworkAdapterList.obj"
	-@erase "$(INTDIR)\OcsCrypto.obj"
	-@erase "$(INTDIR)\OcsProcess.obj"
	-@erase "$(INTDIR)\Printer.obj"
	-@erase "$(INTDIR)\PrinterList.obj"
	-@erase "$(INTDIR)\Registry.obj"
	-@erase "$(INTDIR)\RegistryValue.obj"
	-@erase "$(INTDIR)\RegistryValueList.obj"
	-@erase "$(INTDIR)\SNMP.obj"
	-@erase "$(INTDIR)\SnmpAPI.obj"
	-@erase "$(INTDIR)\Software.obj"
	-@erase "$(INTDIR)\SoftwareList.obj"
	-@erase "$(INTDIR)\SoundDevice.obj"
	-@erase "$(INTDIR)\SoundDeviceList.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StoragePeripheral.obj"
	-@erase "$(INTDIR)\StoragePeripheralList.obj"
	-@erase "$(INTDIR)\SysInfo.obj"
	-@erase "$(INTDIR)\SysInfo.pch"
	-@erase "$(INTDIR)\SysInfo.res"
	-@erase "$(INTDIR)\SystemController.obj"
	-@erase "$(INTDIR)\SystemControllerList.obj"
	-@erase "$(INTDIR)\SystemPort.obj"
	-@erase "$(INTDIR)\SystemPortList.obj"
	-@erase "$(INTDIR)\SystemSlot.obj"
	-@erase "$(INTDIR)\SystemSlotList.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VideoAdapter.obj"
	-@erase "$(INTDIR)\VideoAdapterList.obj"
	-@erase "$(INTDIR)\WindowsSocket.obj"
	-@erase "$(INTDIR)\Wmi.obj"
	-@erase "$(OUTDIR)\SysInfo.exp"
	-@erase "$(OUTDIR)\SysInfo.lib"
	-@erase "$(OUTDIR)\SysInfo.pdb"
	-@erase "..\Debug\SysInfo.dll"
	-@erase "..\Debug\SysInfo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../includes" /I "../OcsWmi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\SysInfo.pch" /YX"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\SysInfo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SysInfo.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib ws2_32.lib  libeay32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\SysInfo.pdb" /debug /machine:I386 /out:"..\Debug\SysInfo.dll" /implib:"$(OUTDIR)\SysInfo.lib" /pdbtype:sept /libpath:"C:\Program Files\Microsoft platform SDK\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\AccessLog.obj" \
	"$(INTDIR)\AccountInfo.obj" \
	"$(INTDIR)\BIOS.obj" \
	"$(INTDIR)\cpu_info.obj" \
	"$(INTDIR)\DebugLog.obj" \
	"$(INTDIR)\DeviceComments.obj" \
	"$(INTDIR)\DeviceCommentsList.obj" \
	"$(INTDIR)\DeviceInventory.obj" \
	"$(INTDIR)\DeviceInventoryList.obj" \
	"$(INTDIR)\DeviceProperties.obj" \
	"$(INTDIR)\DeviceRepairs.obj" \
	"$(INTDIR)\DeviceRepairsList.obj" \
	"$(INTDIR)\Dtwinver.obj" \
	"$(INTDIR)\EDID.obj" \
	"$(INTDIR)\FileVersion.obj" \
	"$(INTDIR)\InputDevice.obj" \
	"$(INTDIR)\InputDeviceList.obj" \
	"$(INTDIR)\IPHelper.obj" \
	"$(INTDIR)\LogicalDrive.obj" \
	"$(INTDIR)\LogicalDriveList.obj" \
	"$(INTDIR)\Markup.obj" \
	"$(INTDIR)\Memory.obj" \
	"$(INTDIR)\MemorySlot.obj" \
	"$(INTDIR)\MemorySlotList.obj" \
	"$(INTDIR)\Modem.obj" \
	"$(INTDIR)\ModemList.obj" \
	"$(INTDIR)\Monitor.obj" \
	"$(INTDIR)\MonitorList.obj" \
	"$(INTDIR)\NetworkAdapter.obj" \
	"$(INTDIR)\NetworkAdapterList.obj" \
	"$(INTDIR)\OcsCrypto.obj" \
	"$(INTDIR)\OcsProcess.obj" \
	"$(INTDIR)\Printer.obj" \
	"$(INTDIR)\PrinterList.obj" \
	"$(INTDIR)\Registry.obj" \
	"$(INTDIR)\RegistryValue.obj" \
	"$(INTDIR)\RegistryValueList.obj" \
	"$(INTDIR)\SNMP.obj" \
	"$(INTDIR)\SnmpAPI.obj" \
	"$(INTDIR)\Software.obj" \
	"$(INTDIR)\SoftwareList.obj" \
	"$(INTDIR)\SoundDevice.obj" \
	"$(INTDIR)\SoundDeviceList.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StoragePeripheral.obj" \
	"$(INTDIR)\StoragePeripheralList.obj" \
	"$(INTDIR)\SysInfo.obj" \
	"$(INTDIR)\SystemController.obj" \
	"$(INTDIR)\SystemControllerList.obj" \
	"$(INTDIR)\SystemPort.obj" \
	"$(INTDIR)\SystemPortList.obj" \
	"$(INTDIR)\SystemSlot.obj" \
	"$(INTDIR)\SystemSlotList.obj" \
	"$(INTDIR)\VideoAdapter.obj" \
	"$(INTDIR)\VideoAdapterList.obj" \
	"$(INTDIR)\WindowsSocket.obj" \
	"$(INTDIR)\Wmi.obj" \
	"$(INTDIR)\SysInfo.res" \
	"..\OcsWmi\Debug\OcsWmi.lib"

"..\Debug\SysInfo.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SysInfo.dep")
!INCLUDE "SysInfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "SysInfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SysInfo - Win32 Release" || "$(CFG)" == "SysInfo - Win32 Debug"
SOURCE=.\AccessLog.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\AccessLog.obj"	"$(INTDIR)\AccessLog.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\AccessLog.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\AccountInfo.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\AccountInfo.obj"	"$(INTDIR)\AccountInfo.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\AccountInfo.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\BIOS.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\BIOS.obj"	"$(INTDIR)\BIOS.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\BIOS.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\cpu_info.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\cpu_info.obj"	"$(INTDIR)\cpu_info.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\cpu_info.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DebugLog.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DebugLog.obj"	"$(INTDIR)\DebugLog.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DebugLog.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceComments.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceComments.obj"	"$(INTDIR)\DeviceComments.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceComments.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceCommentsList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceCommentsList.obj"	"$(INTDIR)\DeviceCommentsList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceCommentsList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceInventory.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceInventory.obj"	"$(INTDIR)\DeviceInventory.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceInventory.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceInventoryList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceInventoryList.obj"	"$(INTDIR)\DeviceInventoryList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceInventoryList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceProperties.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceProperties.obj"	"$(INTDIR)\DeviceProperties.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceProperties.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceRepairs.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceRepairs.obj"	"$(INTDIR)\DeviceRepairs.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceRepairs.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\DeviceRepairsList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\DeviceRepairsList.obj"	"$(INTDIR)\DeviceRepairsList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\DeviceRepairsList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Dtwinver.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Dtwinver.obj"	"$(INTDIR)\Dtwinver.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Dtwinver.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\EDID.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\EDID.obj"	"$(INTDIR)\EDID.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\EDID.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\FileVersion.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\FileVersion.obj"	"$(INTDIR)\FileVersion.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\FileVersion.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\InputDevice.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\InputDevice.obj"	"$(INTDIR)\InputDevice.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\InputDevice.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\InputDeviceList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\InputDeviceList.obj"	"$(INTDIR)\InputDeviceList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\InputDeviceList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\IPHelper.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\IPHelper.obj"	"$(INTDIR)\IPHelper.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\IPHelper.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\LogicalDrive.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\LogicalDrive.obj"	"$(INTDIR)\LogicalDrive.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\LogicalDrive.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\LogicalDriveList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\LogicalDriveList.obj"	"$(INTDIR)\LogicalDriveList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\LogicalDriveList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Markup.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Markup.obj"	"$(INTDIR)\Markup.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Markup.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Memory.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Memory.obj"	"$(INTDIR)\Memory.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Memory.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MemorySlot.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\MemorySlot.obj"	"$(INTDIR)\MemorySlot.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\MemorySlot.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MemorySlotList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\MemorySlotList.obj"	"$(INTDIR)\MemorySlotList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\MemorySlotList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Modem.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Modem.obj"	"$(INTDIR)\Modem.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Modem.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\ModemList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\ModemList.obj"	"$(INTDIR)\ModemList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\ModemList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Monitor.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Monitor.obj"	"$(INTDIR)\Monitor.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Monitor.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\MonitorList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\MonitorList.obj"	"$(INTDIR)\MonitorList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\MonitorList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\NetworkAdapter.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\NetworkAdapter.obj"	"$(INTDIR)\NetworkAdapter.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\NetworkAdapter.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\NetworkAdapterList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\NetworkAdapterList.obj"	"$(INTDIR)\NetworkAdapterList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\NetworkAdapterList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\OcsCrypto.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\OcsCrypto.obj"	"$(INTDIR)\OcsCrypto.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\OcsCrypto.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\OcsProcess.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\OcsProcess.obj"	"$(INTDIR)\OcsProcess.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\OcsProcess.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Printer.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Printer.obj"	"$(INTDIR)\Printer.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Printer.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\PrinterList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\PrinterList.obj"	"$(INTDIR)\PrinterList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\PrinterList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Registry.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Registry.obj"	"$(INTDIR)\Registry.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Registry.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RegistryValue.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\RegistryValue.obj"	"$(INTDIR)\RegistryValue.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\RegistryValue.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\RegistryValueList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\RegistryValueList.obj"	"$(INTDIR)\RegistryValueList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\RegistryValueList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SNMP.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SNMP.obj"	"$(INTDIR)\SNMP.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SNMP.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SnmpAPI.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SnmpAPI.obj"	"$(INTDIR)\SnmpAPI.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SnmpAPI.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Software.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Software.obj"	"$(INTDIR)\Software.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Software.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SoftwareList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SoftwareList.obj"	"$(INTDIR)\SoftwareList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SoftwareList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SoundDevice.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SoundDevice.obj"	"$(INTDIR)\SoundDevice.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SoundDevice.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SoundDeviceList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SoundDeviceList.obj"	"$(INTDIR)\SoundDeviceList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SoundDeviceList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../includes" /I "../OcsWmi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\SysInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\SysInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../includes" /I "../OcsWmi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SYSINFO_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /Fp"$(INTDIR)\SysInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SysInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\StoragePeripheral.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\StoragePeripheral.obj"	"$(INTDIR)\StoragePeripheral.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\StoragePeripheral.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StoragePeripheralList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\StoragePeripheralList.obj"	"$(INTDIR)\StoragePeripheralList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\StoragePeripheralList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SysInfo.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SysInfo.obj"	"$(INTDIR)\SysInfo.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SysInfo.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemController.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemController.obj"	"$(INTDIR)\SystemController.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemController.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemControllerList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemControllerList.obj"	"$(INTDIR)\SystemControllerList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemControllerList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemPort.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemPort.obj"	"$(INTDIR)\SystemPort.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemPort.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemPortList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemPortList.obj"	"$(INTDIR)\SystemPortList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemPortList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemSlot.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemSlot.obj"	"$(INTDIR)\SystemSlot.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemSlot.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SystemSlotList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\SystemSlotList.obj"	"$(INTDIR)\SystemSlotList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\SystemSlotList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\VideoAdapter.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\VideoAdapter.obj"	"$(INTDIR)\VideoAdapter.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\VideoAdapter.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\VideoAdapterList.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\VideoAdapterList.obj"	"$(INTDIR)\VideoAdapterList.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\VideoAdapterList.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\WindowsSocket.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\WindowsSocket.obj"	"$(INTDIR)\WindowsSocket.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\WindowsSocket.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\Wmi.cpp

!IF  "$(CFG)" == "SysInfo - Win32 Release"


"$(INTDIR)\Wmi.obj"	"$(INTDIR)\Wmi.sbr" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"


"$(INTDIR)\Wmi.obj" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\SysInfo.rc

"$(INTDIR)\SysInfo.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "SysInfo - Win32 Release"

"OcsWmi - Win32 Release" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Release" 
   cd "..\SysInfo"

"OcsWmi - Win32 ReleaseCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\SysInfo"

!ELSEIF  "$(CFG)" == "SysInfo - Win32 Debug"

"OcsWmi - Win32 Debug" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Debug" 
   cd "..\SysInfo"

"OcsWmi - Win32 DebugCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\SysInfo"

!ENDIF 


!ENDIF 

