# Microsoft Developer Studio Generated NMAKE File, Based on TestSysInfo.dsp
!IF "$(CFG)" == ""
CFG=TestSysInfo - Win32 Debug
!MESSAGE No configuration specified. Defaulting to TestSysInfo - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "TestSysInfo - Win32 Release" && "$(CFG)" != "TestSysInfo - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "TestSysInfo.mak" CFG="TestSysInfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "TestSysInfo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "TestSysInfo - Win32 Debug" (based on "Win32 (x86) Application")
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

!IF  "$(CFG)" == "TestSysInfo - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Release\TestSysInfo.exe" "$(OUTDIR)\TestSysInfo.bsc"

!ELSE 

ALL : "SysInfo - Win32 Release" "OcsWmi - Win32 Release" "..\Release\TestSysInfo.exe" "$(OUTDIR)\TestSysInfo.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"OcsWmi - Win32 ReleaseCLEAN" "SysInfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestSysInfo.obj"
	-@erase "$(INTDIR)\TestSysInfo.pch"
	-@erase "$(INTDIR)\TestSysInfo.res"
	-@erase "$(INTDIR)\TestSysInfo.sbr"
	-@erase "$(INTDIR)\TestSysInfoDlg.obj"
	-@erase "$(INTDIR)\TestSysInfoDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\TestSysInfo.bsc"
	-@erase "..\Release\TestSysInfo.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "../SysInfo" /I "../OcsWmi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestSysInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TestSysInfo.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestSysInfo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestSysInfo.sbr" \
	"$(INTDIR)\TestSysInfoDlg.sbr"

"$(OUTDIR)\TestSysInfo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\TestSysInfo.pdb" /machine:I386 /out:"..\Release\TestSysInfo.exe" 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestSysInfo.obj" \
	"$(INTDIR)\TestSysInfoDlg.obj" \
	"$(INTDIR)\TestSysInfo.res" \
	"..\OcsWmi\Release\OcsWmi.lib" \
	"..\SysInfo\Release\SysInfo.lib"

"..\Release\TestSysInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "TestSysInfo - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug\TestSysInfo.exe" "$(OUTDIR)\TestSysInfo.bsc"

!ELSE 

ALL : "SysInfo - Win32 Debug" "OcsWmi - Win32 Debug" "..\Debug\TestSysInfo.exe" "$(OUTDIR)\TestSysInfo.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"OcsWmi - Win32 DebugCLEAN" "SysInfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestSysInfo.obj"
	-@erase "$(INTDIR)\TestSysInfo.pch"
	-@erase "$(INTDIR)\TestSysInfo.res"
	-@erase "$(INTDIR)\TestSysInfo.sbr"
	-@erase "$(INTDIR)\TestSysInfoDlg.obj"
	-@erase "$(INTDIR)\TestSysInfoDlg.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\TestSysInfo.bsc"
	-@erase "$(OUTDIR)\TestSysInfo.pdb"
	-@erase "..\Debug\TestSysInfo.exe"
	-@erase "..\Debug\TestSysInfo.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../SysInfo" /I "../OcsWmi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestSysInfo.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\TestSysInfo.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\TestSysInfo.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestSysInfo.sbr" \
	"$(INTDIR)\TestSysInfoDlg.sbr"

"$(OUTDIR)\TestSysInfo.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\TestSysInfo.pdb" /debug /machine:I386 /out:"..\Debug\TestSysInfo.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestSysInfo.obj" \
	"$(INTDIR)\TestSysInfoDlg.obj" \
	"$(INTDIR)\TestSysInfo.res" \
	"..\OcsWmi\Debug\OcsWmi.lib" \
	"..\SysInfo\Debug\SysInfo.lib"

"..\Debug\TestSysInfo.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("TestSysInfo.dep")
!INCLUDE "TestSysInfo.dep"
!ELSE 
!MESSAGE Warning: cannot find "TestSysInfo.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "TestSysInfo - Win32 Release" || "$(CFG)" == "TestSysInfo - Win32 Debug"
SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "TestSysInfo - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "../SysInfo" /I "../OcsWmi" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestSysInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\TestSysInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "TestSysInfo - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "../SysInfo" /I "../OcsWmi" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\TestSysInfo.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\TestSysInfo.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TestSysInfo.cpp

"$(INTDIR)\TestSysInfo.obj"	"$(INTDIR)\TestSysInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestSysInfo.pch"


SOURCE=.\TestSysInfo.rc

"$(INTDIR)\TestSysInfo.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\TestSysInfoDlg.cpp

"$(INTDIR)\TestSysInfoDlg.obj"	"$(INTDIR)\TestSysInfoDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\TestSysInfo.pch"


!IF  "$(CFG)" == "TestSysInfo - Win32 Release"

"OcsWmi - Win32 Release" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Release" 
   cd "..\TestSysInfo"

"OcsWmi - Win32 ReleaseCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Release" RECURSE=1 CLEAN 
   cd "..\TestSysInfo"

!ELSEIF  "$(CFG)" == "TestSysInfo - Win32 Debug"

"OcsWmi - Win32 Debug" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Debug" 
   cd "..\TestSysInfo"

"OcsWmi - Win32 DebugCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\OcsWmi"
   $(MAKE) /$(MAKEFLAGS) /F ".\OcsWmi.mak" CFG="OcsWmi - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\TestSysInfo"

!ENDIF 

!IF  "$(CFG)" == "TestSysInfo - Win32 Release"

"SysInfo - Win32 Release" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Release" 
   cd "..\TestSysInfo"

"SysInfo - Win32 ReleaseCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\TestSysInfo"

!ELSEIF  "$(CFG)" == "TestSysInfo - Win32 Debug"

"SysInfo - Win32 Debug" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Debug" 
   cd "..\TestSysInfo"

"SysInfo - Win32 DebugCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\TestSysInfo"

!ENDIF 


!ENDIF 

