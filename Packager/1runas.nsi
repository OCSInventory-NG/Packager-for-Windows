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
;

; Setup log file
!define SETUP_LOG_FILE "$exedir\ocspackage.log"
!define COL_FILE "col.txt"
!define Time_out "10"
!include "FileFunc.nsh"
!include "TextFunc.nsh"
!insertmacro GetTime
!insertmacro FileJoin
var /GLOBAL OcsLogon_v ; To complete the setup log file
silentinstall silent
OutFile "ocspackage.exe"
ShowInstDetails hide
Icon "pack.ico"
VIProductVersion "Compile_version"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "Package made by OcsPackager"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "file_x_name vCompile_version for OCS Inventory NG"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Ocs Inventory Team"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsPackager is an addon for Ocs Inventory NG."
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Ocs Inventory Team"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "file_x_name vCompile_version for OCS Inventory NG"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "Compile_version"

function setv
  strcpy $r4  "Administrateur"
  strcpy $r1  "Password"
  strcpy $r2  'Options'
  SetOutPath "$PLUGINSDIR\"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf a $r2
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf z "$PLUGINSDIR\"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf e "createdir"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf r "othern.filen"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf t "No certificate"
;  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf y "other1n.filen"
;  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf u "other1.file"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf V "label.txt"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf W "No_FILE_COLLECTION"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf x "${SETUP_LOG_FILE}"

  ;messagebox mb_ok "label du runas : label.txt  chemin $exedir"
  ;messagebox mb_ok "dir créé : createdir"
  sleep 500
  StrCpy $OcsLogon_v 'Parameters: $r2 $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v 'Install folder: createdir $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v 'Certificate: No certificate $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v 'File collection: No_FILE_COLLECTION $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v "Testing current user IsUserAdmin:$\r$\n"
  Call Write_Log
  Call IsUserAdmin
  Pop "$R0"
  strcmp $R0 "true" Okadmin 0
  StrCpy $OcsLogon_v "Current user is not admin:$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "Launching setup by remcom.exe...$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "With /user:$r4 /pwd:********$\r$\n"
  Call Write_Log
  ;messagebox mb_ok "--->$r4 /pwd:$r1"
  nsExec::Exec 'cmd /c RemCom.exe \\localhost /user:$r4 /pwd:$r1 instocs.exe >remcom.log 2>&1'
  StrCpy $OcsLogon_v "Waiting for RemCom.exe log:"
  Call Write_Log
wait_for_log:
  intop $9 $9 + 1
  StrCpy $OcsLogon_v ".$9"
  Call Write_Log
  strcmp $9 ${time_out} 0 no_timeout
  StrCpy $OcsLogon_v "$\r$\nTimeout: ${time_out} Reached."
  Call Write_Log
  abort
no_timeout:
  sleep 1000
  IfFileExists "remcom.log" 0 wait_for_log
  sleep 3000
  StrCpy $OcsLogon_v "$\r$\nStart Remcom log:$\r$\n"
  Call Write_Log
  ${FileJoin} ${SETUP_LOG_FILE} 'remcom.log' ${SETUP_LOG_FILE}
  StrCpy $OcsLogon_v "$\r$\nEnd Remcom log$\r$\n"
  Call Write_Log
  goto NOkadmin
Okadmin:
  StrCpy $OcsLogon_v "User is Admin:$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "Launching setup directly...$\r$\n"
  Call Write_Log
  execshell '' 'instocs.exe' '' sw_hide
NOkadmin:
functionend

section
  ;wait because execshell dont
  setoutpath "$PLUGINSDIR"
  sleep 60000
SectionEnd

Function IsUserAdmin
 Push $R0
 Push $R1
 Push $R2

 ClearErrors
 UserInfo::GetName
 IfErrors Win9x
 Pop $R1
 UserInfo::GetAccountType
 Pop $R2

 StrCmp $R2 "Admin" 0 Continue
 ; Observation: I get here when running Win98SE. (Lilla)
 ; The functions UserInfo.dll looks for are there on Win98 too,
 ; but just don't work. So UserInfo.dll, knowing that admin isn't required
 ; on Win98, returns admin anyway. (per kichik)
 ; MessageBox MB_OK 'User "$R1" is in the Administrators group'
 StrCpy $R0 "true"
 Goto Done

Continue:
 ; You should still check for an empty string because the functions
 ; UserInfo.dll looks for may not be present on Windows 95. (per kichik)
 StrCmp $R2 "" Win9x
 StrCpy $R0 "false"
 ;MessageBox MB_OK 'User "$R1" is in the "$R2" group'
 Goto Done

Win9x:
 ; comment/message below is by UserInfo.nsi author:
 ; This one means you don't need to care about admin or
 ; not admin because Windows 9x doesn't either
 ;MessageBox MB_OK "Error! This DLL can't run under Windows 9x!"
 StrCpy $R0 "true"

Done:
 StrCpy $OcsLogon_v 'User= "$R1"  AccountType= "$R2"  IsUserAdmin= "$R0"$\r$\n'
 Call Write_Log
 Pop $R2
 Pop $R1
 Exch $R0
FunctionEnd

#####################################################################
# This function write content of OcsLogon_v variable in log file in
# a log file OcsAgentSetup.log located in install directory
#####################################################################
Function Write_Log
  ; Save used register
  Push $R0
  ClearErrors
  ; Is there something to write ?
  StrCmp $OcsLogon_v "" WriteLog_end
  ; Open log file
  FileOpen $R0 ${SETUP_LOG_FILE} a
  ; Seek to end
  FileSeek $R0 END END
  IfErrors WriteLog_end
  ; Write
  FileWrite $R0 "$OcsLogon_v"
  StrCpy $OcsLogon_v ""
  ; Close file
  FileClose $R0
WriteLog_end:
  ; Restore used register
  Pop $R0
FunctionEnd


Function .onInit
  InitPluginsDir

  ; Init debug log
  Delete ${SETUP_LOG_FILE}
  StrCpy $OcsLogon_v "********************************************************$\r$\n"
  Call Write_Log
  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
  StrCpy $OcsLogon_v "Starting Ocspackager on $0/$1/$2 at $4:$5:$6$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "Contents: file_x_name vCompile_version$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "Temp dir: $PLUGINSDIR\$\r$\n"
  Call Write_Log
  File /oname=$PLUGINSDIR\RemCom.exe "RemCom.exe"
  File /oname=$PLUGINSDIR\OcsSetup.exe "OcsAgentSetupTMP"
  File /oname=$PLUGINSDIR\pack.ico "pack.ico"
  File /oname=$PLUGINSDIR\instocs.exe "instocs.exe"
 ;other.rem File /oname=$PLUGINSDIR\other.file.def
 ;other1.rem File /oname=$PLUGINSDIR\other1.file.def
;**********************************
;** ATUOCOMPLETED BY INSTELLER ! **
;**********************************
