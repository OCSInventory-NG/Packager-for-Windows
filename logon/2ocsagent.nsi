################################################################################
## Open Computer and Software Inventory Next Generation
## Copyleft 2007 OCS Inventory NG Team
## Web: http://www.ocsinventory-ng.org
##
## This code is open source and may be copied and modified as long as the source
## code is always made freely available.
## Please refer to the General Public Licence Version 2.0
## http://www.gnu.org/ or Licence.txt
################################################################################

;                             ###############
;                             #  CHANGELOG  #
;                             ###############
; 4050 new compressor method
; 4048 NO CHANGE
; 4046
;
; 4044
; Default folder is $exedir
;---------------------------------------------------------------
; 4037
; Complete rewrite
; Now, ocsagent is only a simple installer (without uninstall)
; /FOLDER replaced by standard NSIS /D=path_to_install_folder (must be last parameter)
; /LNK now create shortcut in users personal startup menu if creation in All users startup menu fails
;---------------------------------------------------------------
; 4035
; 4032
;---------------------------------------------------------------
; 4031
; FOLDER error if no /install
;---------------------------------------------------------------
; 4026
; added /lnkto create startup menu shorcut
;---------------------------------------------------------------
; 4004-4014
; added /local
;---------------------------------------------------------------
; Normal roadmapped improvments

; HM NIS Edit Wizard helper defines
setcompressor /SOLID lzma
!define PRODUCT_NAME "OCS Inventory NG Standalone Agent"
!define PRODUCT_VERSION "4.0.6.1"
!define PRODUCT_PUBLISHER "OCS Inventory NG Team"
!define PRODUCT_WEB_SITE "http://www.ocsinventory-ng.org"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\OCSInventory.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "english"

!include "FileFunc.nsh"
!include "WordFunc.nsh"
;!insertmacro GetOptionsS
;!insertmacro GetOptions
;!insertmacro GetTime
!insertmacro WordReplace

    BRANDINGTEXT "OCS Inventory NG ${PRODUCT_VERSION}"
    Icon "Aocs2.ico"
    SilentInstall SILENT
    ShowInstDetails HIDE
    AutoCloseWindow TRUE
    Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
    InstallDir "$exedir"
    OutFile "ocsagent.exe"

    ;--------------------------------
    ; Version Information
    VIProductVersion "${PRODUCT_VERSION}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "OcsAgent.exe command line options are:$\r$\n/LOCAL to launch a local inventory just after file extract$\r$\n/LNK to create Agent shortcut in startup menu$\r$\n/D=path_to_install_folder to extract agent files to specified folder"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "${PRODUCT_PUBLISHER}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsAgent is a part of OCS Inventory NG Application. Distributed under GNU GPL V2.0 Licence."
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "${PRODUCT_PUBLISHER} ${PRODUCT_WEB_SITE}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OCS Inventory NG Standalone Agent silent installer (no uninstall)"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${PRODUCT_VERSION}"


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


#####################################################################
# This function creates a shortcut into All users startup menu, to
# start OCS agent when user log in
#####################################################################
Function CreateStartupMenuRun
    Pop $R0             ; store the command line string in R0
    SetShellVarContext All
    ClearErrors
    CreateShortCut "$SMSTARTUP\OCS Inventory NG Agent.lnk" "$INSTDIR\OCSInventory.exe" "$R0" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Start OCS Inventory NG Agent"
    IfErrors 0 CreateStartupMenuRun_End
    ; Unable to create shortcut in all users startup menu, so try to create in user's personnal startup menu
    SetShellVarContext Current
    CreateShortCut "$SMSTARTUP\OCS Inventory NG Agent.lnk" "$INSTDIR\OCSInventory.exe" "$R0" '' 0 SW_SHOWNORMAL ALT|CONTROL|i "Start OCS Inventory NG Agent"
CreateStartupMenuRun_End:
FunctionEnd


#####################################################################
# This function creates an item into All users registry run, to
# start OCS agent when user log in
#####################################################################
Function CreateRegistryRun
    Pop $R0             ; store the command line string in R0
    SetShellVarContext All
    ClearErrors
    WriteRegStr SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Run" "OCS Inventory NG Agent" "$INSTDIR\OCSInventory.exe $R0"
    IfErrors 0 CreateRegistryRun_End
    ; Unable to create shortcut in all users startup menu, so try to create in user's personnal startup menu
    SetShellVarContext Current
    WriteRegStr SHELL_CONTEXT "Software\Microsoft\Windows\CurrentVersion\Run" "OCS Inventory NG Agent" "$INSTDIR\OCSInventory.exe $R0"
CreateRegistryRun_End:
FunctionEnd


#####################################################################
# This function launch OCS agent in local inventory mode, and prompt
# user for output destintaion directory
#####################################################################
Function RunLocalInventory
    Pop $R0             ; store the command line string in R0
    exec "$INSTDIR\OcsLogon.exe /LOCAL $R0"
FunctionEnd


#####################################################################
# This function checks if no multiple setup launched, if setup
# launched as silent and without spash screen
#####################################################################
Function .onInit
    ; Prevent Multiple Instances
    System::Call 'kernel32::CreateMutexA(i 0, i 0, t "OCS-INVENTORY-NG-STANDALONE-AGENT-SETUP") i .r1 ?e'
    Pop $R0
    StrCmp $R0 0 onInit_NotRunning
    Abort "OCS Inventory NG Agent Stand Alone installer is already running."
onInit_NotRunning:
FunctionEnd


#####################################################################
# When install successfull, this function launch agent in local mode
# or create all users startup menu shortcut if required
#####################################################################
Function .onInstSuccess
    ; By default, do not create startup menu run
    StrCpy $1 "NO"
    ; By default, do not create startup menu run
    StrCpy $2 "NO"
    ; Get command line paramaters
    Call GetParameters
    Pop $9
    ; Check if create startup menu launch required
    Push "/LNK"            ; push the search string onto the stack
    Push "1"               ; push a default value onto the stack
    Call GetParameterValue
    Pop $R0
    StrCmp "$R0" "1" Skip_CreateStartupMenu
    ; Remove /LNK from command line
    ${WordReplace} "$9" "/LNK" "" "+" $R1
    StrCpy $9 $R1
    ; Create startup menu shortcut required
    StrCpy $1 "YES"
Skip_CreateStartupMenu:
    ; Check if create registry launch required
    Push "/REG"            ; push the search string onto the stack
    Push "1"               ; push a default value onto the stack
    Call GetParameterValue
    Pop $R0
    StrCmp "$R0" "1" Skip_CreateRegistry
    ; Remove /REG from command line
    ${WordReplace} "$9" "/REG" "" "+" $R1
    StrCpy $9 $R1
    ; Create registry key required
    StrCpy $2 "YES"
Skip_CreateRegistry:
    ; Check if local inventory required
    Push "/LOCAL"          ; push the search string onto the stack
    Push "1"               ; push a default value onto the stack
    Call GetParameterValue
    Pop $R0
    StrCmp "$R0" "1" Skip_LocalInventory
    ; Remove /LOCAL from command line
    ${WordReplace} "$9" "/LOCAL" "" "+" $R1
    StrCpy $9 $R1
    ; Local inventory required
    StrCpy $R0 $9
    Call RunLocalInventory
Skip_LocalInventory:
    StrCmp "$1" "YES" onInstSuccess_CreateStartupMenu
    StrCmp "$2" "YES" onInstSuccess_CreateRegistry onInstSuccess_End
onInstSuccess_CreateStartupMenu:
    StrCpy $R0 $9
    Call CreateStartupMenuRun
    Goto onInstSuccess_End
onInstSuccess_CreateRegistry:
    StrCpy $R0 $9
    Call CreateRegistryRun
onInstSuccess_End:
FunctionEnd

#####################################################################
# This function writes install status into log file when install
# failed
#####################################################################
Function .onInstFailed
    Abort "Installation of ${PRODUCT_NAME} ${PRODUCT_VERSION} failed"
FunctionEnd


#####################################################################
# This function writes install status into log file when install
# failed
#####################################################################
Section "OCS Inventory NG Standalone Agent" SEC01
    SetOutPath "$INSTDIR"
    SetOverwrite ON
    File "..\_Release\BIOSINFO.EXE"
    File "..\_Release\zlib.dll"
    File "..\_Release\OcsWmi.dll"
    File "..\_Release\PSAPI.DLL"
    File "..\_Release\SysInfo.dll"
    File "..\_Release\OCSInventory.exe"
    File "..\_Release\download.exe"
    File "..\_Release\MFC42.DLL"
    File "..\_Release\ssleay32.dll"
    File "..\_Release\libeay32.dll"
    File "OcsLogon.exe"
SectionEnd
