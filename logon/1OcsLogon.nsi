################################################################################
##OCSInventory Version NG 1.0 Production
##Copyleft Emmanuel GUILLORY 2006
##Web : http://ocsinventory.sourceforge.net
##
##This code is open source and may be copied and modified as long as the source
##code is always made freely available.
##Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################
;
;                             ###############
;                             #  CHANGELOG  #
;                             ###############

;4028
;
; wright in c:\ocs-ng folder issue patched
;4027 /folder popup issue patched
;/UNINSTALL added
; /URL:added
; /install option added (so try downloading OcsPackage.exe) ---> Fait
; no longer label download-------------------------------------> Fait
;4026
;added /folder: ---------------------------------------------> Fait
;/RegRun option eventually ----------------------------------> Reported
;added /
;replaced "NSISdl::download" by "NSISdl::download_quiet" ----> Fait
;4004-4014
;Normal roadmapped improvments
;
;###############################################################################
!include "MUI.nsh"
;!include "WinMessages.nsh"
!insertmacro MUI_LANGUAGE "english"
!define OCSserver "ocsinventory-ng"
!define TimeOut "600000"
!define Compile_version "4.0.2.7"
!define hard_option "/debug " 
 var url
 var version
 var OcsLogon_v ; to complete the debug option
 var http_port_number ;it means what it says
# /debug = debug option
# /np = No proxy use
# /pnum:[POTR NUMBER] = http port number (only for the deploy)
# /local = Local .ocs export
# /deploy:[VERSION NUMBER] force to deploy at least this version
# /tag:[Value or !systemvarable] force tag taking defined value

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
 FileOpen $0 "$R7\OcsLogon.log" a
 FileSeek $0 END END
 IfErrors done
 FileWrite $0 "$OcsLogon_v"
 strcpy $OcsLogon_v ""
 FileClose $0
done:
FunctionEnd

Function .onInit
 InitPluginsDir
 File /oname=$PLUGINSDIR\OCSFloc.ini "OCSFloc.ini"
; File /oname=$PLUGINSDIR\SetACL.exe "SetACL.exe"

 strcpy $CMDLINE "$CMDLINE ${hard_option}"
; Prevent Multiple Instances
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "OcsLogonNG") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 not_running
  strcpy $OcsLogon_v "OcsLogon.exe is already running!$\r$\n"
  call Write_Log
  Abort
not_running:
; :url option ICI!!!!
  Push "$CMDLINE"
  Push " /URL:"
  Call StrStr
  Pop $R9
  ;messagebox mb_ok $R9
  Strlen $0 $R9
  intcmp $0 5 url_use 0 url_use
  goto url_end
url_use:
 strcpy $R8 $R9 "" 6
; repérer la séquence {blanc slash}
  Push "$R8"
  Push " /"
  Call StrStr
  Pop $R9
  Strlen $2 $R8
  Strlen $4 $R9
  intop $3 $2 - $4
  strcpy $R8 $R8 $3 0
  strcpy $URL $R8
  ;messagebox mb_ok "url:$URL"
url_end:


; VRIFYING IF NOT NT
;  ClearErrors
;   ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" CurrentVersion
;   IfErrors 0 lbl_winnt
;   writeregstr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Run" "OCS Inventory NG" "$cmdline"
; lbl_winnt:
  call test-folder
  SetOutPath "$R7"
  delete "$R7\OcsLogon.log"
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
  strcmp "ocslocal" $R0  0 no_add_local_option
  StrCpy $cmdline '$cmdline /local'
no_add_local_option:
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
;si = " /pnum:" alors on prend que les chiffres si pas un chiffre, on arrete
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
  strcpy $OcsLogon_v  "$OcsLogon_vCmd Line: $CMDLINE $\r$\n"
  strcpy $http_port_number $1
  strcpy $OcsLogon_v  "$OcsLogon_vOCS server port number: $1"
  strcmp $http_port_number "" 0 +2
  strcpy $OcsLogon_v  "$OcsLogon_v Default (80)$\r$\n"
;*******************************
;. Construction de la string URL
;*******************************
 strcpy $OcsLogon_v  "$OcsLogon_v$\r$\n"
strcmp $url "" 0 c_url
strcpy $url "http://$R8$http_port_number/ocsinventory/deploy/"
goto d_url
c_url:
strcpy $OcsLogon_v  "$OcsLogon_v URL used : $url$\r$\n"
d_url:
;messagebox mb_ok "crul: $url"
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
  strcpy $OcsLogon_v "Deploy folder : $R7$\r$\n"
  call Write_Log
  strcpy $OcsLogon_v "OCSserver is set to:  $R8$\r$\n"
  call Write_Log
  strcpy $OcsLogon_v "Internal Ocslogon version: ${Compile_version}$\r$\n"
  call Write_Log
verbose_server_end:



  ;**********************
  ;  UNINSTALL option    ;*
  ;**********************
 Push "$CMDLINE"
 Push " /UNinstall"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
 intcmp $0 10 0 noUNinstall_requested 0
 strcpy $OcsLogon_v "$OcsLogon_vUNinstall Requested.$\r$\n"
 call UNinstall
 ABORT
noUNinstall_requested:


  ;**********************
  ;  Install option     ;*
  ;**********************
; call test_installed_service
; Push "$CMDLINE"
; Push " /install"
;  Call StrStr
;  Pop $R9
;  Strlen $0 $R9
; intcmp $0 8 0 noinstall_requested 0
; call install
 ; Messagebox mb_ok "deuxième test"
; Si le servce est installé on quitte sinon on lance l'agent come d'hab
; call test_installed_service
;noinstall_requested:
 call test_install

  ;**********************
  ;  No proxy option   ;*
  ;**********************
  Push "$CMDLINE"
  Push " /np"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 3 0 proxy_use 0
  StrCpy $OcsLogon_v "$OcsLogon_v No proxy use.$\r$\n"
  goto proxy_end
proxy_use:
  StrCpy $OcsLogon_v "$OcsLogon_v Proxy use.$\r$\n"
proxy_end:
 call Write_Log
 Push "$CMDLINE"
  Push " /local"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 local_ok 0 local_ok
  call test_installed_service
;*************************
;  BUG WITH /LOCAL not the right place for the 2 folowing lines
;  call test_install
;  SetOutPath "$R7"
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
  strcpy $OcsLogon_v "Launching : $R7\OCSInventory.exe $1 /server:$R8$\r$\n"
  call Write_Log
no_verbose_start:
  Exec "$R7\OCSInventory.exe $1 /server:$R8"
local_ok:
  Push "$CMDLINE"
  Push " /debug"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  ;messagebox mb_ok $0
  intcmp $0 6 0 oninit_end 0
  call Write_Log
  strcpy $OcsLogon_v "Cmdline option is :$cmdline$\r$\n$OcsLogon_v $\r$\n"
  call Write_Log
oninit_end:
ClearErrors
FunctionEnd

function test_installed_service
; Si /install ok alors abort
;tESTER SI LE service est, si oui, on quitte

 strcpy $OcsLogon_v "$OcsLogon_vTesting Service... "
 ReadRegStr $R0 HKLM "SYSTEM\CurrentControlSet\Services\OCS INVENTORY" "start"
 strcmp $R0 "2" 0 lbl_fintestservice
 strcpy $OcsLogon_v "$OcsLogon_vService installed.$\r$\nExiting OcsLogon.$\r$\n"
 call Write_Log
 abort
 ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\RunServices" "OCS Inventory NG"
 strcmp $R0 "2" 0 lbl_fintestservice
 strcpy $OcsLogon_v "$OcsLogon_vService installed on Widows 9x.$\r$\nExiting OcsLogon.$\r$\n"
 call Write_Log
 abort
 
lbl_fintestservice:
 strcpy $OcsLogon_v "$OcsLogon_vService missing "
 call Write_Log
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
  NSISdl::download_quiet /TIMEOUT=600000 "$2" "$1.new"
  pop $0
  strcmp $0 "success" 0 snorm
  delete "$1"
  rename "$1.new" "$1"
 snorm:
  strcpy $OcsLogon_v "$OcsLogon_v$2 : $0$\r$\n"
FunctionEnd

Function donwnloadnp
  pop $1
  pop $2
  NSISdl::download_quiet /TIMEOUT=600000 /NOIEPROXY "$2" "$1.new"
  pop $0
  strcmp $0 "success" 0 snormnp
  delete "$1"
  rename "$1.new" "$1"
 snormnp:
  strcpy $OcsLogon_v "$OcsLogon_v$2 : $0$\r$\n"
FunctionEnd


Function UNinstall
  strcpy $1 "ocsuninstall.exe"
  Push "$CMDLINE"
  Push " /np"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 3 0 Udownload_withProxy 0
  ;push "http://$R8$http_port_number/ocsinventory/deploy/$1"
  push "$url$1"
  push "$R7\ocsuninstall.exe"
  call donwnloadnp
  goto Udownload_end
Udownload_withProxy:
  ;push "http://$R8$http_port_number/ocsinventory/deploy/$1"
  push "$url$1"
  push "$R7\ocsuninstall.exe"
  call donwnload
Udownload_end:
  call Write_Log
  execwait "$R7\ocsuninstall.exe"
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
  strcpy $OcsLogon_v "Ocs Inventory NG ($version) was not previously installed.$\r$\nStart deploying OCS$\r$\n"
  call Write_Log
no_verbose_start_install:
  SetOutPath "$R7"

;:::::::::::/install option

  Push "$CMDLINE"
  Push " /install"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 8 0 set_install 0
  strcpy $1 "ocspackage.exe"
  goto telech
  set_install:
  strcpy $1 "ocsagent.exe"
  telech:
 ; messagebox mb_ok $R9

;:::::::::::::::::::::::: End /install option
Push "$CMDLINE"
  Push " /np"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 3 0 download_withProxy 0
  push "$url$1"
  push "$R7\ocsagent.exe"
  call donwnloadnp
 ; push "http://$R8$http_port_number/ocsinventory/deploy/label"
  ;push "$R7\label"
  ;call donwnloadnp
  goto download_end
download_withProxy:
  push "$url$1"
  push "$R7\ocsagent.exe"
  call donwnload
 ; push "http://$R8$http_port_number/ocsinventory/deploy/label"
 ; push "$R7\label"
 ; call donwnload
download_end:
;::::::::::::::::::::::::::::::::::::*

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
  strcpy $OcsLogon_v "End Deploying$\r$\n"
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
  ; CreateShortCut "$R7 local.lnk" "$R7\OcsLogon.exe" \
  "/local" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Lancement de OCS-NG en local."
FunctionEnd

Function test-folder
 ; *************************************
 ;  if /local do not calculate exedir  *
 ; *************************************
  Push "$CMDLINE"
  Push " /local"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 6 0 no_local 0
  strcpy $R7 $exedir
goto suite
no_local:
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
IfFileExists "$R7\ocsagent.exe" 0 et1
delete "$R7\ocsagent.new"
IfFileExists "$R7\ocsagent.new" PB 0
rename "$R7\ocsagent.exe" "$R7\ocsagent.old"
IfFileExists "$R7\ocsagent.old" 0 PB
delete "$R7\ocsagent.old"
et1:
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
  NSISdl::download_quiet /TIMEOUT=600000 /NOIEPROXY "http://$R8$http_port_number/ocsinventory/deploy/nodeploy" "$R7\nodeploy"
  abort
suite:
;messagebox mb_ok "$r7"
FunctionEnd

Function test_install
  ; Test all files.
  ; if one is missing then dowload all
  ;strcpy $OcsLogon_v  "$OcsLogon_v$\r$\nTested file: $R7\ver"
  ;IfFileExists "$R7\ver" 0 set_install
;pop $0
push $R7
 ReadRegStr $0 HKLM "SYSTEM\CurrentControlSet\Services\OCS INVENTORY" "imagepath"
 strlen $1 $0
 intop $1 $1 - 17
 strcpy $0 $0 $1 1
 ;messagebox MB_ok $0
 strcmp $0 "" normalop 0
 strcpy $OcsLogon_v  "$OcsLogon_v Sevice is installed on: $0$\r$\n"
 strcpy $R7 $0
normalop:
 strcmp $0 "" 0 normalop1
 Push "$CMDLINE"
 Push " /install"
 Call StrStr
 Pop $R9
 ;messagebox mb_ok x$R9
 Strlen $0 $R9
 ;messagebox mb_ok $0
 intcmp $0 8 set_install normalop1 set_install
 normalop1:
  strcpy $OcsLogon_v  "$OcsLogon_vTesting: $R7\BIOSINFO.EXE$\r$\n"
  IfFileExists "$R7\BIOSINFO.EXE" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_vTesting: $R7\OCSInventory.exe$\r$\n"
  IfFileExists "$R7\OCSInventory.exe" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_vTesting: $R7\OcsWmi.dll$\r$\n"
  IfFileExists "$R7\OcsWmi.dll" 0 set_install
  strcpy $OcsLogon_v  "$OcsLogon_vTesting: $R7\SysInfo.dll$\r$\n"
  IfFileExists "$R7\SysInfo.dll" 0 set_install
   strcpy $OcsLogon_v  "$OcsLogon_vTesting: $R7\MFC42.DLL$\r$\n"
  IfFileExists "$R7\MFC42.DLL" 0 set_install
  ; veriying potenial corrupted dll
  GetDllVersion "$R7\MFC42.DLL" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_vTesting MFC42.DLL version ($0)$\r$\n"
  strcmp "$R0$R1" "" set_install 0
  GetDllVersion "$R7\OCSInventory.exe" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_vTesting OCSInventory.exe version ($0)$\r$\n"
  intcmp  $0 $version no_install  set_install  no_install
 
set_install:

pop $R7
push $r7
  call install
  GetDllVersion "$R7\ocsagent.exe" $R0 $R1
  IntOp $R2 $R0 / 0x00010000
  IntOp $R3 $R0 & 0x0000FFFF
  IntOp $R4 $R1 / 0x00010000
  IntOp $R5 $R1 & 0x0000FFFF
  StrCpy $0 "$R2$R3$R4$R5"
  strcpy $OcsLogon_v  "$OcsLogon_vTesting ocsagent.exe version:$0$\r$\n"

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
  intcmp $0 6 0 no_verbose_deploy 0
  call Write_Log
  strcpy $OcsLogon_v "Launching : $R7\ocsagent.exe $1$\r$\n"
   call Write_Log
  ExecWAIT "$R7\ocsagent.exe $1"
  ; strcpy $OcsLogon_v "$OcsLogon_vResult: $2$\r$\n"
  ;call Write_Log
  ;*****************************
  ;:::::::::::/install option
  ;***************************
  Push "$CMDLINE"
  Push " /install"
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  intcmp $0 8 0 NOlaunchinstaller 0
  ;exec "$R7\ocsagent.exe"
 ; strcpy $OcsLogon_v "$OcsLogon_vStarting OCS Installer: $R7\ocsagent.exe$\r$\n"
  ;*********************
  ; TEST install pending
  ;********************
strcpy $R9 "1"
start_install:
intcmp $R9 120 OcsSetupNG_Failed 0
sleep 900
 call test_installed_service
 IntOp $R9 $R9 + 1
 strcpy $OcsLogon_v  "$OcsLogon_v Install pending $R9$\r$\n"
 ; messagebox mb_ok $R0
 strcmp $R0 "2" 0 start_install
 ;messagebox mb_ok "Must never arrive here!"
OcsSetupNG_Failed:
 strcpy $OcsLogon_v  "$OcsLogon_v Failed to install Service. Try Classic process...$\r$\n"
call write_log
; end test install pending

  nolaunchinstaller:
;::::::::::::::::::::::::::::::::::::*

  goto no_install
no_verbose_deploy:
    Execwait "$R7\ocsagent.exe $1"
no_install:
  ClearErrors
pop $R7



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
   ;*************************
   ;* For local option only *
   ;*************************
   ;messagebox mb_iconexclamation "EXPORT ..."
   # read  DESTINATION in the ini file
   ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
   Strlen $0 $R0
   intcmp $0 3 0 0 +2
   StrCpy $R0 $R0 2
   SetOutPath "$R7"
   delete "$R7\*.ocs"
  Push "$CMDLINE"
  Push "/"
  Call StrStr
  Pop $1
  Execwait "$R7\OCSInventory.exe $1"
   ClearErrors
   CopyFiles "*.ocs" "$R0\"
   IfErrors bad_copy good_copy
bad_copy:
   MessageBox MB_iconexclamation "Error writing output file on:$\r$\n$R0"
   abort
good_copy:
   MessageBox MB_OK "Inventory export on :$\r$\n$R0$\r$\ndone."
FunctionEnd

Section
   hidewindow
   setautoclose true
SectionEnd