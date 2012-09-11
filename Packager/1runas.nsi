################################################################################
##OCSInventory Version
##Copyleft Emmanuel GUILLORY 
##Web http://ocsinventory.sourceforge.net
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
;
; propager le TAG de $CMDLINE
;
; Setup log file
!define SETUP_LOG_FILE "$exedir\ocspackage.log"
!define COL_FILE "col.txt"
!define Time_out "10"
!define appname "ocspackage.exe"
!include "FileFunc.nsh"
!include "TextFunc.nsh"
!insertmacro GetTime
!insertmacro FileJoin
var /GLOBAL OcsLogon_v ; To complete the setup log file
silentinstall silent
OutFile ${appname}
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
  ;;;;;;;;;;;;;;;
  ; Option overload if /tag:
  Push "/TAG="           ; push the search string onto the stack
  Push ""                ; push a default value onto the stack
  Call GetParameterValue
  Pop $R0
  StrCmp "$R0" "" no_option_overload
  strcpy $R0 '/TAG=$R0 '
  StrCpy $OcsLogon_v '${appname}_:_Parameters value is overloaded with: /TAG=$R0$\r$\n'
  Call Write_Log

no_option_overload:
  ;;;;;;;;;;;;;;;
  setshellvarcontext all
  strcpy $r2  '$R0Options' ;$R0 is user to overload options
  SetOutPath "$PLUGINSDIR\"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf a $r2
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf z "$PLUGINSDIR\"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf e "createdir"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf r "othern.filen"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf t "No certificate"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf V "label.txt"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf W "No_FILE_COLLECTION"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf x "${SETUP_LOG_FILE}"
  sleep 500
  StrCpy $OcsLogon_v '${appname}_:_Parameters: $r2 $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v '${appname}_:_Install folder: createdir $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v '${appname}_:_Certificate: No certificate $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v '${appname}_:_File collection: No_FILE_COLLECTION $\r$\n'
  Call Write_Log
  StrCpy $OcsLogon_v "${appname}_:_Testing current user IsUserAdmin:$\r$\n"
  Call Write_Log
  Call IsUserAdmin
  Pop "$R0"
  strcmp $R0 "true" Okadmin 0
  StrCpy $OcsLogon_v "${appname}_:_Current user is not admin:$\r$\n"
  Call Write_Log
  Call get_computer_name
  pop $9
  ; bug Psexec*********************************
  strcpy $9 "localhost"
  ; bug Psexec*********************************
  
  StrCpy $OcsLogon_v "${appname}_:_Launching setup by Psexec.exe...$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "${appname}_:_Psexec options: /accepteula -u $r4 -p ********$\r$\n"
  Call Write_Log
  sleep 1000
  ; Now usign Psexec if needed
  ;messagebox mb_ok "'cmd /c psexec /accepteula -u $r4 -p $r1 instocs.exe > Psexec.log 2>&1'"
  nsexec::ExecToStack 'cmd /c psexec /accepteula -u $r4 -p $r1 instocs.exe > Psexec.log 2>&1'
  sleep 1000
 ; pop $1
 ; FileOpen $0 Psexec.log a
 ; IfErrors done
 ; messagebox mb_ok "'cmd /c psexec /accepteula -h -u $r4 -p $r1 instocs.exe > Psexec.log 2>&1'"
 ; fileseek $0 END END
 ; FileWrite $0 "some text"
 ; FileClose $0
;done:
  
  ;messagebox mb_ok "$1"

  ;nsexec::exec 'cmd /c Psexec.exe \\$9 /user:$r4 /pwd:$r1 "$PLUGINSDIR\instocs.exe" > Psexec.log 2>&1'
  ;sleep 4000
  StrCpy $OcsLogon_v "${appname}_:_Waiting for Psexec.exe log:"
  Call Write_Log
wait_for_log:
  intop $9 $9 + 1
  StrCpy $OcsLogon_v ".$9"
  Call Write_Log
  strcmp $9 ${time_out} 0 no_timeout
  StrCpy $OcsLogon_v "$\r$\n${appname}_:_Timeout: ${time_out} Reached."
  Call Write_Log
  abort
no_timeout:
  sleep 1000
  IfFileExists "Psexec.log" 0 wait_for_log
  StrCpy $OcsLogon_v '$\r$\n${appname}_:_============== Start of Psexec.exe log =============$\r$\n'
  Call Write_Log
  ${FileJoin} ${SETUP_LOG_FILE} 'Psexec.log' ${SETUP_LOG_FILE}
  StrCpy $OcsLogon_v "$\r$\n${appname}_:_============== End of Psexec.exe log ==============$\r$\n"
  Call Write_Log
  goto NOkadmin
Okadmin:
  StrCpy $OcsLogon_v "${appname}_:_User is Admin:$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "${appname}_:_Launching setup directly...$\r$\n"
  Call Write_Log
  execwait 'instocs.exe'

NOkadmin:
functionend

section
  ;setoutpath "$PLUGINSDIR"
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
 StrCpy $OcsLogon_v '${appname}_:_User= "$R1"  AccountType= "$R2"  IsUserAdmin= "$R0"$\r$\n'
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

Function get_computer_name
  ReadRegStr $0 HKLM "System\CurrentControlSet\Control\ComputerName\ActiveComputerName" "ComputerName"
  StrCmp $0 "" win9x
  StrCpy $1 $0 4 3
;  MessageBox MB_OK "Your ComputerName : $0"
  Goto done
win9x:
  ReadRegStr $0 HKLM "System\CurrentControlSet\Control\ComputerName\ComputerName" "ComputerName"
  StrCpy $1 $0 4 3
;  MessageBox MB_OK "Your ComputerName : $0"
done:
 push $0 
FunctionEnd

function .onInstSuccess
  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
  StrCpy $OcsLogon_v "${appname}_:_End of ${appname} on $0/$1/$2 at $4:$5:$6$\r$\n"
  Call Write_Log
functionend
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; ajout du 15 3 2008
; BUT: TESTER LE TAG ET LE PASSER AU SETUP
#####################################################################
# GetParameters
# input, none
# output, top of stack (replaces, with e.g. whatever)
# modifies no other variables.
#####################################################################
Function GetParameters
  Push $R0
  Push $R1
  Push $R2
  Push $R3
  StrCpy $R2 1
  StrLen $R3 $CMDLINE
  ;Check for quote or space
  StrCpy $R0 $CMDLINE $R2
  StrCmp $R0 '"' 0 +3
  StrCpy $R1 '"'
  Goto loop
  StrCpy $R1 " "
loop:
  IntOp $R2 $R2 + 1
  StrCpy $R0 $CMDLINE 1 $R2
  StrCmp $R0 $R1 get
  StrCmp $R2 $R3 get
  Goto loop
get:
  IntOp $R2 $R2 + 1
  StrCpy $R0 $CMDLINE 1 $R2
  StrCmp $R0 " " get
  StrCpy $R0 $CMDLINE "" $R2
  Pop $R3
  Pop $R2
  Pop $R1
  Exch $R0
FunctionEnd

#####################################################################
# GetParameterValue
# Chris Morgan<cmorgan@alum.wpi.edu> 5/10/2004
# -Updated 4/7/2005 to add support for retrieving a command line switch
#  and additional documentation
#
# Searches the command line input, retrieved using GetParameters, for the
# value of an option given the option name.  If no option is found the
# default value is placed on the top of the stack upon function return.
#
# This function can also be used to detect the existence of just a
# command line switch like /OUTPUT  Pass the default and "/OUTPUT"
# on the stack like normal.  An empty return string "" will indicate
# that the switch was found, the default value indicates that
# neither a parameter or switch was found.
#
# Inputs - Top of stack is default if parameter isn't found,
#  second in stack is parameter to search for, ex. "/OUTPUT:"
# Outputs - Top of the stack contains the value of this parameter
#  So if the command line contained /OUTPUT:somedirectory, "somedirectory"
#  will be on the top of the stack when this function returns
#
# USAGE:
#  Push "/OUTPUT:"       ; push the search string onto the stack
#  Push "DefaultValue"   ; push a default value onto the stack
#  Call GetParameterValue
#  Pop $2
#  MessageBox MB_OK "Value of OUTPUT parameter is '$2'"
#####################################################################
Function GetParameterValue
  Exch $R0  ; get the top of the stack(default parameter) into R0
  Exch      ; exchange the top of the stack(default) with
            ; the second in the stack(parameter to search for)
  Exch $R1  ; get the top of the stack(search parameter) into $R1

  ;Preserve on the stack the registers used in this function
  Push $R2
  Push $R3
  Push $R4
  Push $R5

  Strlen $R2 $R1      ; store the length of the search string into R2

  Call GetParameters  ; get the command line parameters
  Pop $R3             ; store the command line string in R3

  # search for quoted search string
  StrCpy $R5 '"'      ; later on we want to search for a open quote
  Push $R3            ; push the 'search in' string onto the stack
  Push '"$R1'         ; push the 'search for'
  Call StrStr         ; search for the quoted parameter value
  Pop $R4
  StrCpy $R4 $R4 "" 1   ; skip over open quote character, "" means no maxlen
  StrCmp $R4 "" "" next ; if we didn't find an empty string go to next

  # search for non-quoted search string
  StrCpy $R5 ' '      ; later on we want to search for a space since we
                      ; didn't start with an open quote '"' we shouldn't
                      ; look for a close quote '"'
  Push $R3            ; push the command line back on the stack for searching
  Push '$R1'          ; search for the non-quoted search string
  Call StrStr
  Pop $R4

  ; $R4 now contains the parameter string starting at the search string,
  ; if it was found
next:
  StrCmp $R4 "" check_for_switch ; if we didn't find anything then look for
                                 ; usage as a command line switch
  # copy the value after $R1 by using StrCpy with an offset of $R2,
  # the length of 'OUTPUT'
  StrCpy $R0 $R4 "" $R2  ; copy commandline text beyond parameter into $R0
  # search for the next parameter so we can trim this extra text off
  Push $R0
  Push $R5            ; search for either the first space ' ', or the first
                      ; quote '"'
                      ; if we found '"/output' then we want to find the
                      ; ending ", as in '"/output=somevalue"'
                      ; if we found '/output' then we want to find the first
                      ; space after '/output=somevalue'
  Call StrStr         ; search for the next parameter
  Pop $R4
  StrCmp $R4 "" done  ; if 'somevalue' is missing, we are done
  StrLen $R4 $R4      ; get the length of 'somevalue' so we can copy this
                      ; text into our output buffer
  StrCpy $R0 $R0 -$R4 ; using the length of the string beyond the value,
                      ; copy only the value into $R0
  goto done           ; if we are in the parameter retrieval path skip over
                      ; the check for a command line switch

; See if the parameter was specified as a command line switch, like '/output'
check_for_switch:
  Push $R3            ; push the command line back on the stack for searching
  Push '$R1'         ; search for the non-quoted search string
  Call StrStr
  Pop $R4
  StrCmp $R4 "" done  ; if we didn't find anything then use the default
  StrCpy $R0 ""       ; otherwise copy in an empty string since we found the
                      ; parameter, just didn't find a value

done:
  Pop $R5
  Pop $R4
  Pop $R3
  Pop $R2
  Pop $R1
  Exch $R0 ; put the value in $R0 at the top of the stack
FunctionEnd


#####################################################################
# This function try to find a string in another one
# Case insensitive
#####################################################################
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

; FIN AJOUT DU 15
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Function .onInit
  InitPluginsDir
  ; Init debug log$
  Delete "${SETUP_LOG_FILE}"
  StrCpy $OcsLogon_v "${appname}_:_********************************************************$\r$\n"
  Call Write_Log
  ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
  StrCpy $OcsLogon_v "${appname}_:_Starting Ocspackager on $0/$1/$2 at $4:$5:$6$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "${appname}_:_Contents: file_x_name vCompile_version$\r$\n"
  Call Write_Log
  StrCpy $OcsLogon_v "${appname}_:_Temp dir: $PLUGINSDIR\$\r$\n"
  Call Write_Log
  ; definir si on souhaite psexec et le gérer....
  ; File /oname=$PLUGINSDIR\Psexec.exe "Psexec.exe"
  ;other-psex.rem File /oname=$PLUGINSDIR\psexec.exe "psexec.exe"
  File /oname=$PLUGINSDIR\OcsSetup.exe "OcsAgentSetupTMP"
  File /oname=$PLUGINSDIR\pack.ico "pack.ico"
  File /oname=$PLUGINSDIR\instocs.exe "instocs.exe"
  ;other.rem File /oname=$PLUGINSDIR\other.file.def
  ;other1.rem File /oname=$PLUGINSDIR\other1.file.def
;**********************************
;** ATUOCOMPLETED BY INSTELLER ! **
;**********************************

