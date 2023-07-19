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
; This is the All-In-One installer for OCS Inventory agent
; It is the script compiled to include agent, plugins, certificate, and to launch privilegied installer under Admin Account
; It requires that pacckger:
;      - put agent setup file named OcsSetup.exe into same folder
;      - put PsExec.exe file into same folder, or comment line including PsExec
;      - put plugins into subfolder OcsPlugins
;      - put Certificate and Label file into subfolder OcsData
;      - modify some values of this script, especially
;           - OcsAgentSetupFilePathToReplace = full path to Agent setup file
;           - OcsAgentSetupFileTitleToReplace = Agent setup filename without path
;           - OcsAgentSetupVersionToReplace = Agent setup version
;           - OcsCmdLineToReplace = Command line options to use
;           - OcsInstallFolderToReplace = Agent install folder (if modified with /D=)
;           - OcsDataFolderToReplace =  (Agent data folder (if modified with /work_dir=)
;           - OcsIncludeDataFolderToReplace = Folder containing certificate and label file
;           - AdminIdToReplace = Administrative login
;           - AdminPwdToReplace = Administrative passwd
;           - OcsIncludePluginsFolderToReplace = Folder containing plugin files
;

!include "MUI.nsh"
!insertmacro MUI_LANGUAGE "English"
!include "FileFunc.nsh"
!include "TextFunc.nsh"
!insertmacro GetTime
!insertmacro FileJoin

!define PRODUCT_NAME "OCS Inventory NG Packager (All-In-One Agent Installer)"
!define PRODUCT_VERSION "2.8.1.0"
!define TIME_OUT "300" ; seconds

Name "${PRODUCT_NAME}"
Icon "OCSInventory.ico"
OutFile "OcsPackage.exe"

SilentInstall Silent
ShowInstDetails Hide

;Request application privileges for Windows Vista or higher ('user' or 'admin')
RequestExecutionLevel user

var /GLOBAL logBuffer      ; To complete the setup log file
var /GLOBAL Admin_ID       ; Administrative ID to use
var /GLOBAL Admin_Pwd      ; Administrarive password
var /GLOBAL Setup_Log_File ; File where to store logs

################################################################################
# Version information
################################################################################
    VIProductVersion "OcsAgentSetupVersionToReplace"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "${PRODUCT_NAME}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "${PRODUCT_NAME} ${PRODUCT_VERSION} for installing OCS Inventory NG Agent, Certificate and Plugins from an unprivilegied account"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "Package includes <OcsAgentSetupFileTitleToReplace> version <OcsAgentSetupVersionToReplace>"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "OcsAgentSetupVersionToReplace"

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
    FileOpen $R0 $Setup_Log_File a
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
# This function try to find if logged in user has admin rights
#####################################################################
Function IsUserAdmin
	Push $R0
	Push $R1
	Push $R2
	ClearErrors
	UserInfo::GetName
	IfErrors IsUserAdmin_Win9x
	; Assuming Windows NT
	Pop $R1
	UserInfo::GetAccountType
	Pop $R2
	StrCmp $R2 "Admin" 0 IsUserAdmin_Continue
	; Observation: I get here when running Win98SE. (Lilla)
	; The functions UserInfo.dll looks for are there on Win98 too,
	; but just don't work. So UserInfo.dll, knowing that admin isn't required
	; on Win98, returns admin anyway. (per kichik)
	; MessageBox MB_OK 'User "$R1" is in the Administrators group'
	StrCpy $R0 "true"
	Goto IsUserAdmin_end
IsUserAdmin_Continue:
	; You should still check for an empty string because the functions
	; UserInfo.dll looks for may not be present on Windows 95. (per kichik)
	StrCmp $R2 "" IsUserAdmin_Win9x
	StrCpy $R0 "false"
	;MessageBox MB_OK 'User "$R1" is in the "$R2" group'
	Goto IsUserAdmin_end
IsUserAdmin_Win9x:
	; comment/message below is by UserInfo.nsi author:
	; This one means you don't need to care about admin or
	; not admin because Windows 9x doesn't either
	;MessageBox MB_OK "Error! This DLL can't run under Windows 9x!"
	StrCpy $R0 "true"
IsUserAdmin_end:
	;MessageBox MB_OK 'User= "$R1"  AccountType= "$R2"  IsUserAdmin= "$R0"'
	Pop $R2
	Pop $R1
	Exch $R0
FunctionEnd

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
# Init script
#####################################################################
Function .onInit
    InitPluginsDir
    ; Init debug log$
    StrCpy $Setup_Log_File "$TEMP\ocspackage.log"
    Delete "$Setup_Log_File"
    StrCpy $logBuffer "${PRODUCT_NAME} : ********************************************************$\r$\n"
    Call Write_Log
    ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
    StrCpy $logBuffer "${PRODUCT_NAME} : Starting ${PRODUCT_NAME} on $0/$1/$2 at $4:$5:$6$\r$\n"
    Call Write_Log
    StrCpy $logBuffer "${PRODUCT_NAME} : Installing <OcsAgentSetupFileTitleToReplace> version <OcsAgentSetupVersionToReplace>$\r$\n"
    Call Write_Log
    StrCpy $logBuffer "${PRODUCT_NAME} : Installing from <$PLUGINSDIR>\$\r$\n"
    Call Write_Log
FunctionEnd


#####################################################################
# Main section - Extract files and start privilegied installer
#####################################################################
Section "Run Setup"
    ; Run installer for all users
    SetShellVarContext All
    ; First extract files to temp directory
    SetOutPath "$PLUGINSDIR"
    ; Privilegied installer
    StrCpy $logBuffer '${PRODUCT_NAME} : Extracting privilegied installer$\r$\n'
    Call Write_Log
    File "instocs.exe"
    ; Agent setup file
    StrCpy $logBuffer '${PRODUCT_NAME} : Extracting Agent setup file$\r$\n'
    Call Write_Log
    File /ONAME=OcsSetup.exe "OcsAgentSetupFilePathToReplace"
    ; Agent data files
    StrCpy $logBuffer '${PRODUCT_NAME} : Extracting Agent configuration files$\r$\n'
    Call Write_Log
    SetOutPath "$PLUGINSDIR\OcsData"
    File /R "OcsIncludeDataFolderToReplace\*"
    ; Agent plugins files
    StrCpy $logBuffer '${PRODUCT_NAME} : Extracting Agent plugin files$\r$\n'
    Call Write_Log
    SetOutPath "$PLUGINSDIR\OcsPlugins"
    File /R "OcsIncludePluginsFolderToReplace\*"
    ; Generate parameter file
    SetOutPath "$PLUGINSDIR"
    Delete "$PLUGINSDIR\ocsdat.ini"
    StrCpy $logBuffer '${PRODUCT_NAME} : Installing Agent to folder <OcsInstallFolderToReplace>$\r$\n'
    Call Write_Log
    WriteINIStr "$PLUGINSDIR\ocsdat.ini" "Config" "InstallFolder" "OcsInstallFolderToReplace"
    StrCpy $logBuffer '${PRODUCT_NAME} : Configuring Agent from folder <OcsDataFolderToReplace>$\r$\n'
    Call Write_Log
    WriteINIStr "$PLUGINSDIR\ocsdat.ini" "Config" "DataFolder" "OcsDataFolderToReplace"
    StrCpy $logBuffer '${PRODUCT_NAME} : Loging privilegied installer to <$Setup_Log_File>$\r$\n'
    Call Write_Log
    WriteINIStr "$PLUGINSDIR\ocsdat.ini" "Config" "LogFile" "$Setup_Log_File"
    ; Get overloaded command line options from this tool command line
    StrCpy $R0 ""
    Call GetParameters
    Pop $R0
    StrCmp "$R0" "" No_Option_Overload
    StrCpy $logBuffer '${PRODUCT_NAME} : Command line options to overload are <$R0>$\r$\n'
    Call Write_Log
No_Option_Overload:
    ; Write agent setup command line to parameter file
    WriteINIStr "$PLUGINSDIR\ocsdat.ini" "Config" "CmdLine" '$R0 OcsCmdLineToReplace'
    ; Intialize Admin credentials
    StrCpy $Admin_ID "AdminIdToReplace"
    StrCpy $Admin_Pwd "AdminPwdToReplace"
    ; Check if Current User is Administrator
    Call IsUserAdmin
    Pop "$R0"
    StrCmp $R0 "true" Run_No_PsExec 0
    StrCpy $logBuffer "${PRODUCT_NAME} : Current user does not have Administrator privileges$\r$\n"
    Call Write_Log
    ; Check if AdminID provided
    StrCmp "$Admin_ID" "" 0 Run_PsExec
    ; No PsExec or No Admin ID
    StrCpy $logBuffer "${PRODUCT_NAME} : ABORT because PsExec not used or empty Account credentials !$\r$\n"
    Call Write_Log
    Abort

Run_PsExec:
    StrCpy $logBuffer '${PRODUCT_NAME} : Extracting Microsoft SysInternals PsExec.exe$\r$\n'
    Call Write_Log
    ; The following line willbe commented by OcsPackager if no PsExec use, so do not modify
    File "PsExec.exe"
    StrCpy $logBuffer "${PRODUCT_NAME} : Launching Privilegied Installer with command <PsExec.exe /accepteula -u $Admin_ID -p ******** instOCS.exe>$\r$\n"
    Call Write_Log
    Sleep 1000
    ; Now usign Psexec if needed
    nsexec::ExecToStack 'cmd /c PsExec.exe /accepteula -u $Admin_ID -p $Admin_Pwd instocs.exe > Psexec.log 2>&1'
    Sleep 1000
Wait_For_Log:
    IntOp $9 $9 + 1
    StrCpy $logBuffer "${PRODUCT_NAME} : Waiting for Psexec.exe ending (.$9 seconds)$\r$\n"
    Call Write_Log
    StrCmp $9 ${TIME_OUT} 0 No_Timeout
    StrCpy $logBuffer "$\r$\n${PRODUCT_NAME} : ABORT because timeout <${TIME_OUT} seconds> reached !$\r$\n"
    Call Write_Log
    Abort

No_Timeout:
    sleep 1000
    IfFileExists "Psexec.log" 0 Wait_For_Log
    StrCpy $logBuffer '$\r$\n${PRODUCT_NAME} : ============== Start of Psexec.exe log =============$\r$\n'
    Call Write_Log
    ${FileJoin} $Setup_Log_File 'Psexec.log' $Setup_Log_File
    StrCpy $logBuffer "$\r$\n${PRODUCT_NAME} : ============== End of Psexec.exe log ==============$\r$\n"
    Call Write_Log
    Goto EndExec
  
Run_No_PsExec:
    StrCpy $logBuffer "${PRODUCT_NAME} : Current user has Administrator privileges$\r$\n"
    Call Write_Log
    StrCpy $logBuffer "${PRODUCT_NAME} : Launching Privilegied Installer directly...$\r$\n"
    Call Write_Log
    ExecWait 'instocs.exe'

EndExec:
SectionEnd

Function .onInstFailed
    ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
    StrCpy $logBuffer "${PRODUCT_NAME} : Failed end of ${PRODUCT_NAME} on $0/$1/$2 at $4:$5:$6$\r$\n"
    Call Write_Log
FunctionEnd

Function .onInstSuccess
    ${GetTime} "" "L" $0 $1 $2 $3 $4 $5 $6
    StrCpy $logBuffer "${PRODUCT_NAME} : Successfull end of ${PRODUCT_NAME} on $0/$1/$2 at $4:$5:$6$\r$\n"
    Call Write_Log
FunctionEnd

