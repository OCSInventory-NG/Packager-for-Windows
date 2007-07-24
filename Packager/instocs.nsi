;!include "MUI.nsh"
!include "WordFunc.nsh"
!insertmacro WordFind
!include "FileFunc.nsh"
!include "TextFunc.nsh"
!insertmacro GetTime
!insertmacro FileJoin
!define appname "instocs.exe"
silentinstall silent
OutFile ${appname}
var FILE_COLLECTION
var SETUP_LOG_FILE
var OcsLogon_v
ShowInstDetails hide
Function .onInit
; Prevent Multiple Instances
   System::Call 'kernel32::CreateMutexA(i 0, i 0, t "instOCSNG") i .r1 ?e'
   Pop $R0
   StrCmp $R0 0 not_running
   Abort
not_running:
  ;InitPluginsDir
   SetOutPath "$exedir"
   call setv
FunctionEnd

function setv
   readINIStr $2 "$exedir\ocsdat.ini" cnf a
   readINIStr $3 "$exedir\ocsdat.ini" cnf z
   readINIStr $4 "$exedir\ocsdat.ini" cnf e
   readINIStr $5 "$exedir\ocsdat.ini" cnf r
   readINIStr $6 "$exedir\ocsdat.ini" cnf t
  ; readINIStr $7 "$exedir\ocsdat.ini" cnf y
  ; readINIStr $8 "$exedir\ocsdat.ini" cnf u
   readINIStr $9 "$exedir\ocsdat.ini" cnf v
   readINIStr $FILE_COLLECTION "$exedir\ocsdat.ini" cnf W
   readINIStr $SETUP_LOG_FILE "$exedir\ocsdat.ini" cnf x

;   strcpy  $FILE_COLLECTION "aaa|bbb"
;   messagebox mb_ok "COLLEC $FILE_COLLECTION"
   clearerrors
   createdirectory $4
   StrCpy $OcsLogon_v '${appname}_:_Attempt to create "$4" dir...$\r$\n'
   Call Write_Log
;   execwait '"$exedir\OcsSetup.exe" $2'
;   messagebox mb_ok "dir créé :$4 "
;   messagebox mb_ok 'copy "$exedir\$5" "$4\$5"'
   clearerrors
   strcmp $5 "othern.filen" no_cert 0
   copyfiles "$exedir\$5" "$4\$5"
   StrCpy $OcsLogon_v '${appname}_:_Copying certificate:$5 to "$4\"...$\r$\n'
   Call Write_Log
no_cert:
   ;messagebox mb_ok '"copy2 "$7" "$8"'
  ; clearerrors
  ; copyfiles "$exedir\$7" "$4\$8"
  ; StrCpy $OcsLogon_v 'Copying "$exedir\$7" to "$4\$8"...$\r$\n'
  ; Call Write_Log
   clearerrors
   strcmp "" $9 suite 0
   fileopen $0 "$4\label" w
   filewrite $0 '$9'
   fileclose $0
   StrCpy $OcsLogon_v '${appname}_:_Writing label $9 to "$4\label"$\r$\n'
   Call Write_Log
   
suite:
   strcmp $FILE_COLLECTION "" endloopfiles
   ;;;
;   messagebox mb_ok "collect= $FILE_COLLECTION"
   ;********************************************
   ; TRAITEMENT DE LA COLLECTION DE FICHIERS
   ;********************************************
   ${WordFind} $FILE_COLLECTION "|" "*" $R0
   strcpy $1 "0"
loopfiles:
   intcmp $R0 $1 0 endloopfiles
   intop $1 $1 + 1
   ; retrieve current indexed_file
   ${WordFind} $FILE_COLLECTION "|" "+$1" $R1
   strcmp $R1 "" endloopfiles
   clearerrors
   copyfiles "$exedir\$R1" "$4\$R1"
   StrCpy $OcsLogon_v '${appname}_:_Copying "$exedir\$R1" to "$4\$R1"...$\r$\n'
   Call Write_Log
   goto loopfiles
endloopfiles:
  ;fin de traitement de la collection
  clearerrors
  execwait '"$exedir\OcsSetup.exe" $2'
  StrCpy $OcsLogon_v '${appname}_:_Lauching OcsSetup.exe (see Contents)...$\r$\n'
  Call Write_Log
  ;insérer log de ocsagentsetup
  StrCpy $OcsLogon_v '${appname}_:_============== Start of OcsSetup.exe log =============$\r$\n'
  Call Write_Log
  ${FileJoin} $SETUP_LOG_FILE '$exedir\OcsAgentSetup.log' $SETUP_LOG_FILE
  StrCpy $OcsLogon_v '${appname}_:_============== End of OcsSetup.exe log =============$\r$\n'
  Call Write_Log
functionend

function .onInstSuccess
  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
  StrCpy $OcsLogon_v "${appname}_:_End of ${appname} on $0/$1/$2 at $4:$5:$6$\r$\n"
  Call Write_Log
functionend

section
SectionEnd


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
  FileOpen $R0 $SETUP_LOG_FILE a
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


