################################################################################
##OCSInventory Version NG RC1
##Copyleft Emmanuel GUILLORY 2005
##Web : http://ocsinventory.sourceforge.net
##
##This code is open source and may be copied and modified as long as the source
##code is always made freely available.
##Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################

!include "MUI.nsh"
;!include "WinMessages.nsh"
!insertmacro MUI_LANGUAGE "english"
!define OCSserver "ocsinventory-ng"
!define TimeOut "600000"
!define Compile_version "4.0.1.0"
 var version
 var OcsLogon_v ; to complete the debug option
 var http_port_number ;it means what it says
# /debug = debug option
# /np = No proxy use
# /pnum:[POTR NUMBER] = http port number (only for the deploy)
# /local = Local .ocs export
# /deploy:[VERSION NUMBER] force to deploy at least this version

BRANDINGTEXT "OCS Inventory NG ${Compile_version}"
Icon "ocs.ico"
;ShowInstDetails hide
Name "OcsLogon"
OutFile "OcsLogon.exe"
;$R7 became the install folder
;SilentInstall silent
; Page instfiles
Page custom customOCSFloc ValidatecustomOCSFloc ""

;--------------------------------
;Version Information
  VIProductVersion "${Compile_version}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "OcsLogon"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Logon script for OCS Inventory"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Ocs Inventory ng Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsLogon is a part of ocs Inventory NG Application. Under GNU Licence."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "OCS Inventory Team http://ocsinventory.sourceforge.net"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OcsLogon.exe"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Compile_version}"
;--------------------------------

Function Write_Log
 ClearErrors
 ;messagebox mb_ok $OcsLogon_v
 strcmp $OcsLogon_v "" done 0
 FileOpen $0 "$R7\ocs-ng\OcsLogon.log" a
 FileSeek $0 END END
 IfErrors done
 FileWrite $0 "$OcsLogon_v$\r$\n"
 strcpy $OcsLogon_v ""
 FileClose $0
done:
FunctionEnd

Function .onInit
; Prevent Multiple Instances
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "OcsLogon") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 not_running
  strcpy $OcsLogon_v "OcsLogon.exe is already running!"
  call Write_Log
  Abort
not_running:
; VRIFYING IF NOT NT
;  ClearErrors
;   ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" CurrentVersion
;   IfErrors 0 lbl_winnt
;   writeregstr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "OCS Inventory NG" "$cmdline"
; lbl_winnt:
  call test-folder
  SetOutPath "$R7\ocs-ng"
  delete "$R7\ocs-ng\OcsLogon.log"
  StrCpy $R8 ${OCSserver}
  ; test exe Name
  ; if exeName <> OcsLogon.exe then OCSserver variable = exeName
  System::Call 'kernel32::GetModuleFileNameA(i 0, t .R0, i 1024) i r1'
  ;$R0 will contain the installer filename
  pop $R0
  Strlen $0 $exedir
  intop $0 $0 + 1
  StrCpy $R0 $R0 -4 $0 ; $RO is the exeName without "\" and ".exe"
  strcmp "OcsLogon" $R0 no_server_change 0
  StrCpy $R8 $R0
no_server_change:
 ;****************************************
 ; Force deploying version number option ;*
 ;****************************************
  Push "$CMDLINE"
  Push " /deploy:"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  strcpy $1 ""
  intcmp $0 7 version_use 0 version_use
  goto version_end
version_use:
  strcpy $R6 ""
  strcpy $R5 ""
  strcpy $R4 "0"
  strcpy $1 ""
  strcpy $version "1"
;add_next:
;  intcmp $R4 $0 over 0 over
;  StrCpy $R5 $R9 7 $R4
;  IntOp $R4 $R4 + 1
;  messagebox mb_ok "VAL premier DE R9:  $R9"
;  StrCmp $R5 " /pnum:" get_number add_next
; on ajoute les 7 caractères suivants
; si = " /pnum:" alors on prend que les chiffres si pas un chiffre, on arrete
   IntOp $R4 $R4 + 9
get_versionnumber:
  StrCpy $R6 $R9 1 $R4
  strcmp $R6 "0" ADD_versionNUM
  strcmp $R6 "1" ADD_versionNUM
  strcmp $R6 "2" ADD_versionNUM
  strcmp $R6 "3" ADD_versionNUM
  strcmp $R6 "4" ADD_versionNUM
  strcmp $R6 "5" ADD_versionNUM
  strcmp $R6 "6" ADD_versionNUM
  strcmp $R6 "7" ADD_versionNUM
  strcmp $R6 "8" ADD_versionNUM
  strcmp $R6 "9" ADD_versionNUM version_end
  goto version_end
ADD_versionNUM:
  strcpy $1 "$1$R6"
  IntOp $R4 $R4 + 1
  goto get_versionnumber
version_end:
  strcpy $version $1
; FORCER LA VERSION 4010
; strcpy $version "4010"


 ;**********************
 ;  Port Number option ;*
 ;**********************
  Push "$CMDLINE"
  Push " /pnum:"
  Call StrStr
  Pop $R9
  ;MESSAGEBOX MB_ok "port:$R9"
  Strlen $0 $R9
  strcpy $1 ""
  intcmp $0 5 port_use 0 port_use
  goto port_end
port_use:
  strcpy $R6 ""
  strcpy $R5 ""
  strcpy $R4 "0"
  strcpy $1 ":"
  strcpy $http_port_number ""
;add_next:
;  intcmp $R4 $0 over 0 over
;  StrCpy $R5 $R9 7 $R4
;  IntOp $R4 $R4 + 1
;  messagebox mb_ok "VAL premier DE R9:  $R9"
;  StrCmp $R5 " /pnum:" get_number add_next
; on ajoute les 7 caractères suivants
; si = " /pnum:" alors on prend que les chiffres si pas un chiffre, on arrete
   IntOp $R4 $R4 + 7
get_number:
  StrCpy $R6 $R9 1 $R4
  strcmp $R6 "0" ADD_NUM
  strcmp $R6 "1" ADD_NUM
  strcmp $R6 "2" ADD_NUM
  strcmp $R6 "3" ADD_NUM
  strcmp $R6 "4" ADD_NUM
  strcmp $R6 "5" ADD_NUM
  strcmp $R6 "6" ADD_NUM
  strcmp $R6 "7" ADD_NUM
  strcmp $R6 "8" ADD_NUM
  strcmp $R6 "9" ADD_NUM port_end
  goto port_end
ADD_NUM:
  strcpy $1 "$1$R6"
  IntOp $R4 $R4 + 1
  goto get_number
port_end:
  strcpy $http_port_number $1
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nOCS server port number $1"
  strcmp $http_port_number "" 0 +2
  strcpy $OcsLogon_v  "$OcsLogon_v: Default (80)"
  ;messagebox mb_ok "port $OcsLogon_v"
   ;********************************************************************************
   ;          write install folder, server and version in log if /debug           ;*
   ; *******************************************************************************
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  ;messagebox mb_ok $0
  intcmp $0 6 verbose_server 0 verbose_server
  goto verbose_server_end
verbose_server:
  call Write_Log
  strcpy $OcsLogon_v "Install folder : $R7\Ocs-ng"
  call Write_Log
  strcpy $OcsLogon_v "OCSserver is set to:  $R8"
  call Write_Log
  strcpy $OcsLogon_v "Internal Ocslogon version: ${Compile_version}"
  call Write_Log
verbose_server_end:
 InitPluginsDir
 call test-install
  ;**********************
  ;  No proxy option   ;*
  ;**********************
  Push "$CMDLINE"
  Push " /np"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 3 0 proxy_use 0
  StrCpy $OcsLogon_v "$OcsLogon_v $\r$\nNo proxy use."
  goto proxy_end
proxy_use:
  StrCpy $OcsLogon_v "$OcsLogon_v$\r$\nProxy use."
proxy_end:

  File /oname=$PLUGINSDIR\OCSFloc.ini "OCSFloc.ini"
  Push "$CMDLINE"
  Push " /local"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 local_ok 0 local_ok
;*************************
;  BUG WITH /LOCAL not the right place for the 2 folowing lines
;  call test-install
;  SetOutPath "$R7\ocs-ng"
; ***********************
  Push "$CMDLINE"
  Push "/"
  Call StrStr
  Pop $1
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  ;messagebox mb_ok $0
  intcmp $0 6 0 no_verbose_start 0
  call Write_Log
  strcpy $OcsLogon_v "Launching : $R7\ocs-ng\OCSInventory.exe $1 /server:$R8"
  call Write_Log
no_verbose_start:
  Exec "$R7\ocs-ng\OCSInventory.exe $1 /server:$R8"
local_ok:
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  ;messagebox mb_ok $0
  intcmp $0 6 0 oninit_end 0
  call Write_Log
  strcpy $OcsLogon_v "Cmdline option is :$cmdline$\r$\n$OcsLogon_v"
  call Write_Log
oninit_end:
ClearErrors
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

Function donwnload
  pop $1
  pop $2
  NSISdl::download /TIMEOUT=600000 "$2" "$1.new"
  pop $0
  strcmp $0 "success" 0 snorm
  delete "$1"
  rename "$1.new" "$1"
 snorm:
  strcpy $OcsLogon_v "$OcsLogon_v$\r$\n$2 : $0"
FunctionEnd

Function donwnloadnp
  pop $1
  pop $2
  NSISdl::download /TIMEOUT=600000 /NOIEPROXY "$2" "$1.new"
  pop $0
  strcmp $0 "success" 0 snormnp
  delete "$1"
  rename "$1.new" "$1"
 snormnp:
  strcpy $OcsLogon_v "$OcsLogon_v$\r$\n$2 : $0"
FunctionEnd

Function install
;messagebox mb_ok "Install!"
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 0 no_verbose_start_install 0
  call Write_Log
  strcpy $OcsLogon_v "Ocs Inventory NG ($version) was not previously installed.$\r$\nStart deploying OCS"
  call Write_Log
no_verbose_start_install:
  SetOutPath "$R7\ocs-ng"
  ;SetFileAttributes "$R7\ocs-ng\ver" NORMAL
  SetFileAttributes "$R7\ocs-ng\BIOSINFO.EXE" NORMAL
  SetFileAttributes "$R7\ocs-ng\update.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OCSInventory.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OcsWmi.dll" NORMAL
  SetFileAttributes "$R7\ocs-ng\SysInfo.dll" NORMAL
  SetFileAttributes "$R7\ocs-ng\OCSInventory.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OcsLogon.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\MFC42.DLL" NORMAL
  ;strcpy $OcsLogon_v "$OcsLogon_v$\r$\nOCS server         : $R8$http_port_number"


Push "$CMDLINE"
  Push " /np"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 3 0 download_withProxy 0
  push "http://$R8$http_port_number/ocsinventory/deploy/ocsagent.exe"
  push "$R7\ocs-ng\ocsagent.exe"
  call donwnloadnp
  push "http://$R8$http_port_number/ocsinventory/deploy/label"
  push "$R7\ocs-ng\label"
  call donwnloadnp
  goto download_end
download_withProxy:
  push "http://$R8$http_port_number/ocsinventory/deploy/ocsagent.exe"
  push "$R7\ocs-ng\ocsagent.exe"
  call donwnload
  push "http://$R8$http_port_number/ocsinventory/deploy/label"
  push "$R7\ocs-ng\label"
  call donwnload
  
download_end:
  ;strcpy $R6 "$R6$\r$\n$OcsLogon_v"
  ;*****************************************************************
  ;       install success if verbose option (/debug) ;*
  ;*****************************************************************
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 verbose_install 0 verbose_install
  goto no_verbose_install
verbose_install:
  call Write_Log
  strcpy $OcsLogon_v "End Deploying"
  call Write_Log
no_verbose_install:
  ClearErrors
  ; SetShellVarContext all
  ; createdirectory "$SMPROGRAMS\ocs-ng"
  ; CreateShortCut "$SMPROGRAMS\OCS-NG\OCS-NG.lnk" "$PROGRAMFILES\ocs-ng\OcsLogon.exe" \
  ; "/local" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Lancement de OCS-NG en local."
  SetShellVarContext current
  ; SetShellVarContext all
  ; createdirectory "$SMPROGRAMS\ocs-ng"
  ; CreateShortCut "$R7\OCS-NG\OCS-NG local.lnk" "$R7\ocs-ng\OcsLogon.exe" \
  "/local" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Lancement de OCS-NG en local."
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
  FileClose  $0
  strcmp $1 "OCS_NG"  PASPBt PBt
PASPBt:  ; Can Write so temp user
  ;messagebox mb_ok "$1  ok sur temp"
  delete "$R7\ocs-ng\file.dat"
  goto suite
PBt: ; Can not Write so exit and try to alert server
 ; messagebox mb_ok "$R8"
  NSISdl::download "http://$R8$http_port_number/ocsinventory/deploy/nodeploy" "$R7\ocs-ng\nodeploy"
  abort
suite:
FunctionEnd

Function test-install
 ; set attributes.... Because sometimes, somebody...
;SetFileAttributes "$R7\ocs-ng\ver" NORMAL
  SetFileAttributes "$R7\ocs-ng\BIOSINFO.EXE" NORMAL
  SetFileAttributes "$R7\ocs-ng\update.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OCSInventory.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OcsWmi.dll" NORMAL
  SetFileAttributes "$R7\ocs-ng\SysInfo.dll" NORMAL
  SetFileAttributes "$R7\ocs-ng\OCSInventory.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\OcsLogon.exe" NORMAL
  SetFileAttributes "$R7\ocs-ng\MFC42.DLL" NORMAL
  ; Tested all files.
  ; if one is missing then dowload all
  ;strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTested file: $R7\ocs-ng\ver"
  ;IfFileExists "$R7\ocs-ng\ver" 0 set_install
;
;Crypto::HashData "MD5" "todo"
;pop $0

; messagebox MB_ok $0
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\BIOSINFO.EXE"
  IfFileExists "$R7\ocs-ng\BIOSINFO.EXE" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\update.exe"
  IfFileExists "$R7\ocs-ng\update.exe" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\OCSInventory.exe"
  IfFileExists "$R7\ocs-ng\OCSInventory.exe" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\OcsWmi.dll"
  IfFileExists "$R7\ocs-ng\OcsWmi.dll" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\SysInfo.dll"
  IfFileExists "$R7\ocs-ng\SysInfo.dll" 0 set_install
  ;strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\OCSInventory.conf"
  ;IfFileExists "$R7\ocs-ng\OCSInventory.conf" 0 set_install
  ;strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\OcsLogon.exe"
  ;IfFileExists "$R7\ocs-ng\OcsLogon.exe" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting: $R7\ocs-ng\MFC42.DLL"
  IfFileExists "$R7\ocs-ng\MFC42.DLL" 0 set_install
  ; veriying potenial corrupted dll
  GetDllVersion "$R7\ocs-ng\MFC42.DLL" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting MFC42.DLL version ($0)"
  strcmp "$R0$R1" "" set_install 0
  GetDllVersion "$R7\ocs-ng\OCSInventory.exe" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting OCSInventory.exe version ($0)"
  intcmp  $0 $version no_install  set_install  no_install
 ; strcmp "$R0$R1" "" set_install 0
 ; strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTested SysInfo.dll"
 ; GetDllVersion "$R7\ocs-ng\SysInfo.dll" $R0 $R1
 ; strcmp "$R0$R1" "" set_install no_install
set_install:
  call install
  GetDllVersion "$R7\ocs-ng\ocsagent.exe" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTesting ocsagent.exe version:$0"
  ; Crypto::HashFile "MD5" "$R7\ocs-ng\ocsagent.exe"
  ; pop $0
  ; strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nocsagent.exe HSAH MD5 is: $0"
  ; strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nExpected HASH MD5 is     : ${DeployOCS_hash} for the (${Compile_version}) version"
  Execwait "$R7\ocs-ng\ocsagent.exe"
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 verbose_startinstall 0 verbose_startinstall
  goto no_verbose_startinstall
verbose_startinstall:
  call write_log
no_verbose_startinstall:
no_install:
  ClearErrors
  ; verifying severname in OCSInventory.conf
  ; must be 'ocsinventory-ng' if OcsLogon is not renamed
  ; or get the new server name
 ; Readinistr $0 "$R7\ocs-ng\OCSInventory.conf" "OCS Inventory Agent" "Server"
  ;strcmp $0 $R8 no_change_conf_file 0
  ;writeinistr "$R7\ocs-ng\OCSInventory.conf" "OCS Inventory Agent" "Server" $R8
;no_change_conf_file:
FunctionEnd

Function customOCSFloc
   ;****************************************************
   ;          popup to export the .ocs file           ;*
   ; ***************************************************
 Push "$CMDLINE"
 Push " /local"
 Call StrStr
 Pop $R9
 ;strcmp " /local" $R9 local_ok 0
 Strlen $0 $R9
 ;messagebox mb_ok $0
 intcmp $0 6 0 customOCSFloc_endprocess 0
   !insertmacro MUI_HEADER_TEXT "Local inventory" "Inventory target:"
 InstallOptions::dialog "$PLUGINSDIR\OCSFloc.ini"
 customOCSFloc_endprocess:
FunctionEnd

Function ValidatecustomOCSFloc
  ; destination choice and control
   ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
   StrCmp $R0 "" 0 ValidatecustomOCSFloc_done
   MessageBox MB_ICONEXCLAMATION "Select a target directory."
   abort
ValidatecustomOCSFloc_done:
   ;****************************************************
   ;          destination  test                       ;*
   ;        Verify if string R0 has got 2 "\"         ;*
   Strlen $0 $R0                                      ;*
   intcmp $0 3 0 0 +2                                 ;*
   StrCpy $R0 $R0 2                                   ;*
   ; Si oui en supprimer un                           ;*
   ;****************************************************
   FileOpen $1 "$R0\file.dat" w
   FileWrite $1 "OK$\r$\n"
   Fileclose $1
;MessageBox MB_ICONEXCLAMATION "$R0\file.dat"
   IfFileExists "$R0\file.dat" ValidatecustomOCSFloc_ok ValidatecustomOCSFloc_err
ValidatecustomOCSFloc_err:
   MessageBox MB_iconstop "Target directory not writable!"
   abort
ValidatecustomOCSFloc_ok:
   delete "$R0\file.dat"
   Readinistr $4 "$R7\ocs-ng\OCSInventory.conf" "OCS Inventory Agent" "DeviceID"
   ;*************************
   ;* For local option only *
   ;*************************
   ;messagebox mb_iconexclamation "EXPORT ..."
   # read  DESTINATION in the ini file
   ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
   Strlen $0 $R0
   intcmp $0 3 0 0 +2
   StrCpy $R0 $R0 2
   SetOutPath "$R7\ocs-ng"
   delete "$R7\ocs-ng\*.ocs"
  Push "$CMDLINE"
  Push "/"
  Call StrStr
  Pop $1
  Execwait "$R7\ocs-ng\OCSInventory.exe $1"
   ClearErrors
   ; Readinistr $4 "$R7\ocs-ng\OCSInventory.conf" "OCS Inventory Agent" "DeviceID"
   ; ${GetFileExt}  "$R7\ocs-ng\*.ocs" $filename
   ; messagebox mb_ok $filename

   CopyFiles "*.ocs" "$R0\"
   IfErrors bad_copy good_copy
   ;IfFileExists "$R0\$4.ocs" good_copy bad_copy
bad_copy:
   MessageBox MB_iconexclamation "Error writing output file on:$\r$\n$R0"
   abort
good_copy:
   MessageBox MB_OK "Inventory export on :$\r$\n$R0$\r$\ndone."
FunctionEnd

Section
   hidewindow
   ;file "ocs.ico"
   setautoclose true
SectionEnd
