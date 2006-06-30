# Microsoft Developer Studio Generated NMAKE File, Based on OCSInventory.dsp
!IF "$(CFG)" == ""
CFG=OCSInventory Agent - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OCSInventory Agent - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OCSInventory Agent - Win32 Release" && "$(CFG)" != "OCSInventory Agent - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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

!IF  "$(CFG)" == "OCSInventory Agent - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Release\OCSInventory.exe" "$(OUTDIR)\OCSInventory.bsc"

!ELSE 

ALL : "SysInfo - Win32 Release" "..\Release\OCSInventory.exe" "$(OUTDIR)\OCSInventory.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SysInfo - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\flate.obj"
	-@erase "$(INTDIR)\flate.sbr"
	-@erase "$(INTDIR)\Markup.obj"
	-@erase "$(INTDIR)\Markup.sbr"
	-@erase "$(INTDIR)\OCSInventory.obj"
	-@erase "$(INTDIR)\OCSInventory.res"
	-@erase "$(INTDIR)\OCSInventory.sbr"
	-@erase "$(INTDIR)\OCSInventoryCommon.obj"
	-@erase "$(INTDIR)\OCSInventoryCommon.sbr"
	-@erase "$(INTDIR)\OCSInventoryState.obj"
	-@erase "$(INTDIR)\OCSInventoryState.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StoreInteract.obj"
	-@erase "$(INTDIR)\StoreInteract.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XMLInteract.obj"
	-@erase "$(INTDIR)\XMLInteract.sbr"
	-@erase "$(OUTDIR)\OCSInventory.bsc"
	-@erase "..\Release\OCSInventory.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /WX /GX /O2 /I "..\OcsDB" /I "..\SysInfo" /I "..\OcsWmi" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_OCS_AGENT" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OCSInventory.pch" /YX"StdAfx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OCSInventory.res" /i "C:\Program Files\Microsoft SDK\Lib" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OCSInventory.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\flate.sbr" \
	"$(INTDIR)\Markup.sbr" \
	"$(INTDIR)\OCSInventory.sbr" \
	"$(INTDIR)\OCSInventoryCommon.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StoreInteract.sbr" \
	"$(INTDIR)\XMLInteract.sbr" \
	"$(INTDIR)\OCSInventoryState.sbr"

"$(OUTDIR)\OCSInventory.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib Zlib\zlibstat.lib msvcrt.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\OCSInventory.pdb" /machine:I386 /nodefaultlib:"libc" /out:"..\Release\OCSInventory.exe" /libpath:"C:\Program Files\Microsoft SDK\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\flate.obj" \
	"$(INTDIR)\Markup.obj" \
	"$(INTDIR)\OCSInventory.obj" \
	"$(INTDIR)\OCSInventoryCommon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StoreInteract.obj" \
	"$(INTDIR)\XMLInteract.obj" \
	"$(INTDIR)\OCSInventory.res" \
	"$(INTDIR)\OCSInventoryState.obj" \
	"..\SysInfo\Release\SysInfo.lib"

"..\Release\OCSInventory.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OCSInventory Agent - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "..\Debug\OCSInventory.exe" "$(OUTDIR)\OCSInventory.bsc"

!ELSE 

ALL : "SysInfo - Win32 Debug" "..\Debug\OCSInventory.exe" "$(OUTDIR)\OCSInventory.bsc"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"SysInfo - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\flate.obj"
	-@erase "$(INTDIR)\flate.sbr"
	-@erase "$(INTDIR)\Markup.obj"
	-@erase "$(INTDIR)\Markup.sbr"
	-@erase "$(INTDIR)\OCSInventory.obj"
	-@erase "$(INTDIR)\OCSInventory.res"
	-@erase "$(INTDIR)\OCSInventory.sbr"
	-@erase "$(INTDIR)\OCSInventoryCommon.obj"
	-@erase "$(INTDIR)\OCSInventoryCommon.sbr"
	-@erase "$(INTDIR)\OCSInventoryState.obj"
	-@erase "$(INTDIR)\OCSInventoryState.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\StoreInteract.obj"
	-@erase "$(INTDIR)\StoreInteract.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XMLInteract.obj"
	-@erase "$(INTDIR)\XMLInteract.sbr"
	-@erase "$(OUTDIR)\de.pdb"
	-@erase "$(OUTDIR)\OCSInventory.bsc"
	-@erase "..\Debug\OCSInventory.exe"
	-@erase "..\Debug\OCSInventory.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /WX /Gm /GX /ZI /Od /I "..\OcsDB" /I "..\SysInfo" /I "..\OcsWmi" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_OCS_AGENT" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\OCSInventory.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OCSInventory.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\flate.sbr" \
	"$(INTDIR)\Markup.sbr" \
	"$(INTDIR)\OCSInventory.sbr" \
	"$(INTDIR)\OCSInventoryCommon.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\StoreInteract.sbr" \
	"$(INTDIR)\XMLInteract.sbr" \
	"$(INTDIR)\OCSInventoryState.sbr"

"$(OUTDIR)\OCSInventory.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib Zlib\zlibstat.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\de.pdb" /debug /machine:I386 /nodefaultlib:"libc.lib" /out:"../Debug/OCSInventory.exe" /pdbtype:sept /libpath:"C:\Program Files\Microsoft platform SDK\Lib" /nodefaultlib:"libc.lib"/out:"..\Debug\OCSInventory.exe" 
LINK32_OBJS= \
	"$(INTDIR)\flate.obj" \
	"$(INTDIR)\Markup.obj" \
	"$(INTDIR)\OCSInventory.obj" \
	"$(INTDIR)\OCSInventoryCommon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\StoreInteract.obj" \
	"$(INTDIR)\XMLInteract.obj" \
	"$(INTDIR)\OCSInventory.res" \
	"$(INTDIR)\OCSInventoryState.obj" \
	"..\SysInfo\Debug\SysInfo.lib"

"..\Debug\OCSInventory.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("OCSInventory.dep")
!INCLUDE "OCSInventory.dep"
!ELSE 
!MESSAGE Warning: cannot find "OCSInventory.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OCSInventory Agent - Win32 Release" || "$(CFG)" == "OCSInventory Agent - Win32 Debug"
SOURCE=.\zlib\flate.cpp

"$(INTDIR)\flate.obj"	"$(INTDIR)\flate.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\SysInfo\Markup.cpp

"$(INTDIR)\Markup.obj"	"$(INTDIR)\Markup.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\OCSInventory.cpp

"$(INTDIR)\OCSInventory.obj"	"$(INTDIR)\OCSInventory.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OCSInventoryCommon.cpp

"$(INTDIR)\OCSInventoryCommon.obj"	"$(INTDIR)\OCSInventoryCommon.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OCSInventoryState.cpp

"$(INTDIR)\OCSInventoryState.obj"	"$(INTDIR)\OCSInventoryState.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StoreInteract.cpp

"$(INTDIR)\StoreInteract.obj"	"$(INTDIR)\StoreInteract.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\XMLInteract.cpp

"$(INTDIR)\XMLInteract.obj"	"$(INTDIR)\XMLInteract.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\OCSInventory.rc

"$(INTDIR)\OCSInventory.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


!IF  "$(CFG)" == "OCSInventory Agent - Win32 Release"

"SysInfo - Win32 Release" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Release" 
   cd "..\Agent"

"SysInfo - Win32 ReleaseCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Release" RECURSE=1 CLEAN 
   cd "..\Agent"

!ELSEIF  "$(CFG)" == "OCSInventory Agent - Win32 Debug"

"SysInfo - Win32 Debug" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Debug" 
   cd "..\Agent"

"SysInfo - Win32 DebugCLEAN" : 
   cd "\Developp\OCS Inventory NG\sources\tmp\win32_agent\agent\SysInfo"
   $(MAKE) /$(MAKEFLAGS) /F ".\SysInfo.mak" CFG="SysInfo - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\Agent"

!ENDIF 


!ENDIF 

