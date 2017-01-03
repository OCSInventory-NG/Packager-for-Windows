################################################################################
## OCS Inventory NG
## Copyleft OCS Inventory NG Team
## Web : http://www.ocsinventory-ng.org
##
## This code is open source and may be copied and modified as long as the source
## code is always made freely available.
## Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################

;
; This is the code of installer which will setup agent, plugins and certificate
; It requires Aministrator privileges
; It is launched by All-One-Installer 1runas.nsi
; It Assumes that:
;    - agent setup files is OcsSetup.exe, and is in the same folder
;    - subfolder OcsData contains files to copy to Agent data folder
;    - subfolder OcsPlugins contains files to copy to Agent plugins folder
;    - file ocsdat.ini contains various parameters for this tool. This file is created by All-In-One installer
;

!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "English"
!include "FileFunc.nsh"
!include "TextFunc.nsh"
!insertmacro GetTime
!insertmacro FileJoin

!define PRODUCT_NAME "OCS Inventory NG Packager (Privilegied Installer)"
!define PRODUCT_VERSION "2.3.0.0"
!define AGENT_LOG_FILENAME "OCS-NG-Windows-Agent-Setup.log"
!define AGENT_PLUGINS_DIR "Plugins"

Name "${PRODUCT_NAME}"
Icon "OCSInventory.ico"
OutFile "instOCS.exe"

SilentInstall Silent
ShowInstDetails Hide

var /GLOBAL SETUP_LOG_FILE       ; Setup log file to populate
var /GLOBAL logBuffer           ; Variable to write log

;Request application privileges for Windows Vista or higher ('user' or 'admin')
RequestExecutionLevel admin

################################################################################
# Version information
################################################################################
    VIProductVersion "${PRODUCT_VERSION}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Script for installing Agent, Certificate and Plugins from privilegied account"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "instOCS.exe"
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
# This function write content of logBuffer variable in log file in
# a log file OcsAgentSetup.log located in install directory
#####################################################################
Function Write_Log
    ; Save used register
    Push $R0
    ClearErrors
    ; Is there something to write ?
    StrCmp $logBuffer "" WriteLog_end
    ; Open log file
    FileOpen $R0 $SETUP_LOG_FILE a
    ; Seek to end
    FileSeek $R0 END END
    IfErrors WriteLog_end
    ; Write
    FileWrite $R0 "$logBuffer"
    StrCpy $logBuffer ""
    ; Close file
    FileClose $R0
WriteLog_end:
    ; Restore used register
    Pop $R0
FunctionEnd


#####################################################################
# Init script
#####################################################################
Function .onInit
    InitPluginsDir
    SetOutPath "$exedir"
    ; Read log file to populate from config
    readINIStr $SETUP_LOG_FILE "$exedir\ocsdat.ini" "Config" "LogFile"
	StrCpy $logBuffer "${PRODUCT_NAME} : ********************************************************$\r$\n"
	Call Write_Log
	${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
	StrCpy $logBuffer "${PRODUCT_NAME} : Starting ${PRODUCT_NAME} ${PRODUCT_VERSION} on $0/$1/$2 at $4:$5:$6$\r$\n"
	Call Write_Log
    ; Prevent Multiple Instances
    System::Call 'kernel32::CreateMutexA(i 0, i 0, t "instOCSNG") i .r1 ?e'
    Pop $R0
    StrCmp $R0 0 not_running
	StrCpy $logBuffer "${PRODUCT_NAME} : ABORT because setup already running !$\r$\n"
	Call Write_Log
    Abort
not_running:
FunctionEnd

#####################################################################
# Main section - read parameters and start setup
#####################################################################
Section "Run setup"
    SetShellVarContext all
    ; Read agent setup folder from config
    readINIStr $R0 "$exedir\ocsdat.ini" "Config" "InstallFolder"
    ; Read agent data folder from config
    readINIStr $R1 "$exedir\ocsdat.ini" "Config" "DataFolder"
    ; Create agent install and data directories
    StrCpy $logBuffer '${PRODUCT_NAME} : Creating OCS Inventort NG Agent install directory <$R0>...$\r$\n'
    Call Write_Log
    CreateDirectory "$R0"
    StrCpy $logBuffer '${PRODUCT_NAME} : Creating OCS Inventort NG Agent ${AGENT_PLUGINS_DIR} directory <$R0\${AGENT_PLUGINS_DIR}>...$\r$\n'
    Call Write_Log
    CreateDirectory "$R0\${AGENT_PLUGINS_DIR}"
    StrCpy $logBuffer '${PRODUCT_NAME} : Creating OCS Inventort NG Agent data directory <$R1>...$\r$\n'
    Call Write_Log
    CreateDirectory "$R1"
    ; Copy certificate and label file to agent data folder
    StrCpy $logBuffer '${PRODUCT_NAME} : Installing OCS Inventort NG Agent data files to <$R1>...$\r$\n'
    Call Write_Log
    CopyFiles /SILENT "$exedir\OcsData\*" "$R1"
    ; Copy plugin files to agent plugins folder
    StrCpy $logBuffer '${PRODUCT_NAME} : Installing OCS Inventort NG Agent plugin files to <$R0\${AGENT_PLUGINS_DIR}>...$\r$\n'
    Call Write_Log
    CopyFiles /SILENT "$exedir\OcsPlugins\*" "$R0\${AGENT_PLUGINS_DIR}"
    ; Launch agent setup
    StrCpy $logBuffer '${PRODUCT_NAME}: Lauching OCS Inventory NG Agent Setup...$\r$\n'
    Call Write_Log
    ; Read agent setup command line from config
    readINIStr $R0 "$exedir\ocsdat.ini" "Config" "CmdLine"
    ; Read optional parameters to overload config
    Call GetParameters
    Pop $R1
    ; Launch agent setup with overloaded parameters before config parameters
    ExecWait '"$exedir\OcsSetup.exe" $R1 $R0'
    ;********************************************
    ; read and paste OCS Agent Setup log
    StrCpy $logBuffer '${PRODUCT_NAME} : ============== Start of OCS Inventory NG Agent setup log =============$\r$\n'
    Call Write_Log
    ${FileJoin} $SETUP_LOG_FILE '$exedir\${AGENT_LOG_FILENAME}' $SETUP_LOG_FILE
    StrCpy $logBuffer '${PRODUCT_NAME} : ============== End of OCS Inventory NG Agent setup log =============$\r$\n'
    Call Write_Log
SectionEnd

#####################################################################
#
#####################################################################
Function .onInstFailed
    ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
    StrCpy $logBuffer "${PRODUCT_NAME} : Failed end of ${PRODUCT_NAME} on $0/$1/$2 at $4:$5:$6$\r$\n"
    Call Write_Log
FunctionEnd

#####################################################################
#
#####################################################################
Function .onInstSuccess
    ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
    StrCpy $logBuffer "${PRODUCT_NAME} : successfull end of ${PRODUCT_NAME} on $0/$1/$2 at $4:$5:$6$\r$\n"
    Call Write_Log
FunctionEnd
