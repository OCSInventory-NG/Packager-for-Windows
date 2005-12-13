################################################################################
##OCSInventory Version NG Beta
##Copyleft Emmanuel GUILLORY 2005
##Web : http://ocsinventory.sourceforge.net
##
##This code is open source and may be copied and modified as long as the source
##code is always made freely available.
##Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################
!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "english"
!define Compile_version "4.0.1.0"
BRANDINGTEXT "OCS Inventory NG ${Compile_version}"
Icon "OcsAgent.ico"
ShowInstDetails hide
Name "OcsAgent"
OutFile "OcsAgent.exe"
;--------------------------------
;Version Information

  VIProductVersion "${Compile_version}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "OcsAgent"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Self extracting file for OCS Inventory NG. Available option: /local"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Ocs Inventory NG Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsAgent is a part of ocs Inventory NG Application. Under GNU Licence."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "OCS Inventory Team http://ocsinventory.sourceforge.net"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OcsAgent.exe"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Compile_version}"

Function .onInit
; Prevent Multiple Instances
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "OcsAgent") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 not_running
;  MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
  Abort
not_running:
   InitPluginsDir
   File /oname=$PLUGINSDIR\OcsWmi.dll "OcsWmi.dll"
   File /oname=$PLUGINSDIR\OcsLogon.exe "OcsLogon.exe"
   File /oname=$PLUGINSDIR\update.exe "update.exe"
   File /oname=$PLUGINSDIR\BIOSINFO.EXE "BIOSINFO.EXE"
   File /oname=$PLUGINSDIR\OCSInventory.exe "OCSInventory.exe"
   File /oname=$PLUGINSDIR\SysInfo.dll "SysInfo.dll"
   File /oname=$PLUGINSDIR\OcsLogon.exe "OcsLogon.exe"
   File /oname=$PLUGINSDIR\MFC42.DLL "MFC42.DLL"
   call test-folder
   call install
   Push "$CMDLINE"
   Push " /local"
   Call StrStr
   Pop $R9
   Strlen $0 $R9
   intcmp $0 6 local_ok 0 local_ok
   goto local_ko
local_ok:
  Push "$CMDLINE"
  Push "/"
  Call StrStr
  Pop $1
  exec "$R7\ocs-ng\OcsLogon.exe $1"
local_ko:
   
   
FunctionEnd
  
Function install
 copyfiles "$PLUGINSDIR\BIOSINFO.EXE"     "$R7\ocs-ng\BIOSINFO.EXE"
 copyfiles "$PLUGINSDIR\update.exe"       "$R7\ocs-ng\update.exe"
 copyfiles "$PLUGINSDIR\OCSInventory.exe" "$R7\ocs-ng\OCSInventory.exe"
 copyfiles "$PLUGINSDIR\OcsWmi.dll"       "$R7\ocs-ng\OcsWmi.dll"
 copyfiles "$PLUGINSDIR\SysInfo.dll"      "$R7\ocs-ng\SysInfo.dll"
 copyfiles "$PLUGINSDIR\OcsLogon.exe"     "$R7\ocs-ng\OcsLogon.exe"
 copyfiles "$PLUGINSDIR\MFC42.DLL"        "$R7\ocs-ng\MFC42.DLL"
 ; preserve Old files
 ;IfFileExists "$R7\ocs-ng\OCSInventory.conf" no_change_deviceID
 ;copyfiles "$R7\ocs-ng\OCSInventory.conf" "$exedir\OCSInventory.conf"
 ;no_change_deviceID:
FunctionEnd

Function test-folder
 ; *****************************
 ;  giving the good directory  *
 ; *****************************
  strcpy $R7 $WINDIR 2
  createdirectory "$R7\ocs-ng"
  FileOpen $1 "$R7\ocs-ng\file.dat" w
  FileWrite $1 "OCS_NG"
  Fileclose $1
  FileOpen $0 "$R7\ocs-ng\file.dat" r
  FileRead $0 $1
  ; Tested the entered vallue
  FileClose $0
  strcmp $1 "OCS_NG"  PASPB    PB
PASPB:  ; Writing OK so $R7 = c:\ocs-ng
  SetFileAttributes "$R7\ocs-ng\file.dat" NORMAL
  delete "$R7\ocs-ng\file.dat"
  goto suite
PB: ; Can not Write so giving $R7 the user temp value
  strcpy $R7 "$TEMP"
  ;messagebox mb_ok $R7
  createdirectory "$R7\ocs-ng"
  FileOpen $1 "$R7\ocs-ng\file.dat" w
  FileWrite $1 "OCS_NG"
  Fileclose $1
  FileOpen $0 "$R7\ocs-ng\file.dat" r
  FileRead $0 $1
  ; Tested the entered vallue
  ; messagebox mb_ok 3--$1
  FileClose $0
  strcmp $1 "OCS_NG"  PASPBt PBt
PASPBt:  ; Can Write so temp user
  ;messagebox mb_ok "$1  ok sur temp"
  delete "$R7\ocs-ng\file.dat"
  goto suite
PBt: ; Cannot Write anywhere so exit
  abort
suite:
FunctionEnd
Function StrStr
  Exch $R1 ; st=haystack,old$R1, $R1=needle
  Exch    ; st=old$R1,haystack
  Exch $R2 ; st=old$R1,old$R2, $R2=haystack
  Push $R3
  Push $R4
  Push $R5
  StrLen $R3 $R1
  StrCpy $R4 0
  ; $R1=needle
  ; $R2=haystack
  ; $R3=len(needle)
  ; $R4=cnt
  ; $R5=tmp
loop:
  StrCpy $R5 $R2 $R3 $R4
  StrCmp $R5 $R1 done
  StrCmp $R5 "" done
  IntOp $R4 $R4 + 1
  Goto loop
done:
  StrCpy $R1 $R2 "" $R4
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Exch $R1
FunctionEnd

Section
   hidewindow
   setautoclose true
SectionEnd
