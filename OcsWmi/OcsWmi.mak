# Microsoft Developer Studio Generated NMAKE File, Based on OcsWmi.dsp
!IF "$(CFG)" == ""
CFG=OcsWmi - Win32 Debug
!MESSAGE No configuration specified. Defaulting to OcsWmi - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "OcsWmi - Win32 Release" && "$(CFG)" != "OcsWmi - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "OcsWmi.mak" CFG="OcsWmi - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "OcsWmi - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "OcsWmi - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
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

!IF  "$(CFG)" == "OcsWmi - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release

ALL : "..\Release\OcsWmi.dll"


CLEAN :
	-@erase "$(INTDIR)\OcsWmi.obj"
	-@erase "$(INTDIR)\OcsWmi.pch"
	-@erase "$(INTDIR)\OcsWmi.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\OcsWmi.exp"
	-@erase "$(OUTDIR)\OcsWmi.lib"
	-@erase "..\Release\OcsWmi.dll"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OCSWMI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D "_WIN32_DCOM" /Fp"$(INTDIR)\OcsWmi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\OcsWmi.res" /i "C:\Program Files\Microsoft SDK\Lib" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OcsWmi.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\OcsWmi.pdb" /machine:I386 /out:"..\Release\OcsWmi.dll" /implib:"$(OUTDIR)\OcsWmi.lib" /libpath:"C:\Program Files\Microsoft SDK\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\OcsWmi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OcsWmi.res"

"..\Release\OcsWmi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "OcsWmi - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "..\Debug\OcsWmi.dll" "$(OUTDIR)\OcsWmi.bsc"


CLEAN :
	-@erase "$(INTDIR)\OcsWmi.obj"
	-@erase "$(INTDIR)\OcsWmi.pch"
	-@erase "$(INTDIR)\OcsWmi.res"
	-@erase "$(INTDIR)\OcsWmi.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\OcsWmi.bsc"
	-@erase "$(OUTDIR)\OcsWmi.exp"
	-@erase "$(OUTDIR)\OcsWmi.lib"
	-@erase "$(OUTDIR)\OcsWmi.pdb"
	-@erase "..\Debug\OcsWmi.dll"
	-@erase "..\Debug\OcsWmi.ilk"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OCSWMI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D "_WIN32_DCOM" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OcsWmi.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\OcsWmi.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\OcsWmi.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\OcsWmi.sbr" \
	"$(INTDIR)\StdAfx.sbr"

"$(OUTDIR)\OcsWmi.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=wbemuuid.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\OcsWmi.pdb" /debug /machine:I386 /out:"..\Debug\OcsWmi.dll" /implib:"$(OUTDIR)\OcsWmi.lib" /pdbtype:sept /libpath:"C:\Program Files\Microsoft SDK\Lib" 
LINK32_OBJS= \
	"$(INTDIR)\OcsWmi.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\OcsWmi.res"

"..\Debug\OcsWmi.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
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
!IF EXISTS("OcsWmi.dep")
!INCLUDE "OcsWmi.dep"
!ELSE 
!MESSAGE Warning: cannot find "OcsWmi.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "OcsWmi - Win32 Release" || "$(CFG)" == "OcsWmi - Win32 Debug"
SOURCE=.\OcsWmi.cpp

!IF  "$(CFG)" == "OcsWmi - Win32 Release"


"$(INTDIR)\OcsWmi.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OcsWmi.pch"


!ELSEIF  "$(CFG)" == "OcsWmi - Win32 Debug"


"$(INTDIR)\OcsWmi.obj"	"$(INTDIR)\OcsWmi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\OcsWmi.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "OcsWmi - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OCSWMI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D "_WIN32_DCOM" /Fp"$(INTDIR)\OcsWmi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\OcsWmi.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "OcsWmi - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "OCSWMI_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /D "_WIN32_DCOM" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\OcsWmi.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\OcsWmi.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\OcsWmi.rc

"$(INTDIR)\OcsWmi.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)



!ENDIF 

