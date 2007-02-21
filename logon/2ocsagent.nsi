################################################################################
##OCSInventory Version 1.0
##Copyleft Emmanuel GUILLORY 2006
##Web : http://ocsinventory.sourceforge.net
##
##This code is open source and may be copied and modified as long as the source
##code is always made freely available.
##Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################

;                             ###############
;                             #  CHANGELOG  #
;                             ###############
;4031
; FOLDER error if not /install
;
;4026
;added /lnk  ---------------------------------------------> fait
;4004-4014
; added /local
;Normal roadmapped improvments
!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "english"
!define Compile_version "4.0.3.1"
BRANDINGTEXT "OCS Inventory NG ${Compile_version}"
Icon "Aocs2.ico"
ShowInstDetails hide
Name "OcsAgent"
OutFile "ocsagent.exe"
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
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "OcsAgentNG") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 not_running
;  MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
  Abort
not_running:
   InitPluginsDir
   File /oname=$PLUGINSDIR\OcsWmi.dll "OcsWmi.dll"
   File /oname=$PLUGINSDIR\OcsLogon.exe "OcsLogon.exe"
   File /oname=$PLUGINSDIR\download.exe "download.exe"
   File /oname=$PLUGINSDIR\BIOSINFO.EXE "BIOSINFO.EXE"
   File /oname=$PLUGINSDIR\OCSInventory.exe "OCSInventory.exe"
   File /oname=$PLUGINSDIR\SysInfo.dll "SysInfo.dll"
   File /oname=$PLUGINSDIR\OcsLogon.exe "OcsLogon.exe"
   File /oname=$PLUGINSDIR\MFC42.DLL "MFC42.DLL"
   File /oname=$PLUGINSDIR\zlib.dll "zlib.dll"
   File /oname=$PLUGINSDIR\ssleay32.dll "ssleay32.dll"
   File /oname=$PLUGINSDIR\PSAPI.DLL "PSAPI.DLL"
   File /oname=$PLUGINSDIR\libeay32.dll "libeay32.dll"
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
  exec "$R7\OcsLogon.exe $1"
local_ko:
   
   
FunctionEnd
  
Function install
 copyfiles "$PLUGINSDIR\*.exe"     "$R7\"
 copyfiles "$PLUGINSDIR\*.dll"       "$R7\"
 ;copyfiles "$PLUGINSDIR\OCSInventory.exe" "$R7\OCSInventory.exe"
 ;copyfiles "$PLUGINSDIR\OcsWmi.dll"       "$R7\OcsWmi.dll"
 ;copyfiles "$PLUGINSDIR\SysInfo.dll"      "$R7\SysInfo.dll"
 ;copyfiles "$PLUGINSDIR\OcsLogon.exe"     "$R7\OcsLogon.exe"
 ;copyfiles "$PLUGINSDIR\MFC42.DLL"        "$R7\MFC42.DLL"
 ; preserve Old files
 ;IfFileExists "$R7\OCSInventory.conf" no_change_deviceID
 ;copyfiles "$R7\OCSInventory.conf" "$exedir\OCSInventory.conf"
 ;no_change_deviceID:
FunctionEnd

Function lnk
  SetShellVarContext all
  CreateShortCut "$SMSTARTUP\OCS.lnk" "$R7\OcsLogon.exe" \
  "" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Lancement de OCS"
Functionend


Function test-folder
 ; *****************************
 ;  giving the good directory  *
 ; *****************************
 strcpy $R7 $WINDIR 2
 strcpy $R7 "$R7\ocs-ng"
 ; testing /folder: option
  Push "$CMDLINE"
  Push " /folder:"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 9 folder_use 0 folder_use
  goto folder_end
folder_use:

 strcpy $R7 $R9 "" 9
; repérer la séquence {blanc slash}
  Push "$R7"
  Push " /"
  Call StrStr
  Pop $R9
  Strlen $2 $R7
  Strlen $1 $R9
  intop $3 $2 - $1
  strcpy $R7 $R7 $3 0
  ;messagebox mb_ok "install dans le dossier :$R7"
  createdirectory "$R7"
  goto suite
folder_end:
  ; end testing /folder option
  createdirectory "$R7"

 FileOpen $1 "$R7\file.dat" w
  FileWrite $1 "OCS_NG"
  Fileclose $1
  FileOpen $0 "$R7\file.dat" r
  FileRead $0 $1
 ; Tested the entered vallue
  FileClose $0
  strcmp $1 "OCS_NG"  0    PB
 ; Writing OK so $R7 = c:\ocs-ng
  SetFileAttributes "$R7\file.dat" NORMAL
  delete "$R7\file.dat"
;  goto suite
;PB: ; Can not Write so giving $R7 the user temp value
;***************** NEVER TEST OCSAGENT HERE....
;****************
;IfFileExists "$R7\ocsagent.exe" 0 et1
;delete "$R7\ocsagent.new"
;IfFileExists "$R7\ocsagent.new" PB 0
;rename "$R7\ocsagent.exe" "$R7\ocsagent.old"
;IfFileExists "$R7\ocsagent.old" 0 PB
;delete "$R7\ocsagent.old"
;et1:
IfFileExists "$R7\ocsinventory.exe" 0 suite
rename "$R7\ocsinventory.exe" "$R7\ocsinventory.old"
IfFileExists "$R7\ocsinventory.old" 0 PB
IfFileExists "$R7\ocsinventory.exe" PB 0
rename "$R7\ocsinventory.old" "$R7\ocsinventory.exe"
goto suite
PB:
  strcpy $R7 "$TEMP"
  ;messagebox mb_ok $R7
  createdirectory "$R7\ocs-ng"
  strcpy $R7 "$R7\ocs-ng"
  FileOpen $1 "$R7\file.dat" w
  FileWrite $1 "OCS_NG"
  Fileclose $1
  FileOpen $0 "$R7\file.dat" r
  FileRead $0 $1
  ; Tested the entered vallue
  ; messagebox mb_ok 3--$1
  FileClose  $0
  strcmp $1 "OCS_NG"  PASPBt PBt
PASPBt:  ; Can Write so temp user
  ;messagebox mb_ok "$1  ok sur temp"
  delete "$R7\file.dat"
  goto suite
PBt: ; Can not Write so exit and try to alert server
 ; messagebox mb_ok "$R8"
  NSISdl::download_quiet /TIMEOUT=600000 /NOIEPROXY "http://$R8/ocsinventory/deploy/nodeploy" "$R7\nodeploy"
  abort
suite:
;messagebox mb_ok "$r7"
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
   Push "$CMDLINE"
   Push " /lnk"
   Call StrStr
   Pop $R9
   Strlen $0 $R9
   intcmp $0 4 lnk_ok 0 lnk_ok
   goto lnk_ko
lnk_ok:
 call lnk
lnk_ko:
SectionEnd
