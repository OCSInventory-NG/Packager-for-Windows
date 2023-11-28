################################################################################
## OCS Inventory NG
## Copyleft OCS Inventory NG Team
## Web : http://www.ocsinventory-ng.org
##
## This code is open source and may be copied and modified as long as the source
## code is always made freely available.
## Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
################################################################################

!include "MUI.nsh"
!include "WordFunc.nsh"
!include "FileFunc.nsh"
!insertmacro GetFileName
!insertmacro WordFind
!include "TextReplace.nsh"
!insertmacro MUI_LANGUAGE "English"
!define Compile_version "2.8.1.0"
; Do not forget to change the following line in both Ocspackager and 1runas.nsi files...
!define COL_FILE "Plugins.lst"
; Path to NSIS compiler
; UPDATE IF NEEDED !!!
; To build on Windows 64 bits, you must set "C:\Program Files (x86)\NSIS"
; To build on Windows 32 bits, you must set "C:\Program Files\NSIS"
!define NSIS_PATH "C:\Program Files (x86)\NSIS"

################################################################################
# Version information
################################################################################
    VIProductVersion "${Compile_version}"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "OCS Inventory NG Packager for Windows"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "OCS Inventory NG Packager script for Windows"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "OCS Inventory NG Team"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OcsPackager.exe"
    VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Compile_version}"

Var /GLOBAL hWnd                   ; Window handle for modifying properties
var /GLOBAL Dest_Folder            ; Folder where to create ocspackage.exe
var /GLOBAL Use_PsExec             ; Contain "Yes" if PsExec available to launch setup under admin account
var /GLOBAL Agent_Cmd_Line_Options ; Agent setup command line
Var /GLOBAL SilentMode             ; Initialize global variable
Var /GLOBAL AgentSourceBinaryPath
Var /GLOBAL CmdLineOptions
Var /GLOBAL CACertificateFilePath
Var /GLOBAL Label
Var /GLOBAL OcsPluginsFiles
Var /GLOBAL AdminId
Var /GLOBAL AdminPwd

BRANDINGTEXT "OCS Inventory NG Packager ${Compile_version}"
Icon "OCSInventory.ico"
ShowInstDetails Show
Name "OCS Inventory NG Packager"
OutFile "OcsPackager.exe"

;Request application privileges for Windows Vista or higher ('user' or 'admin')
RequestExecutionLevel admin

# Custom page for configuration
Page custom DonneeConfigPage ValidateDonnee ""
# Custom page for output path
Page custom OCSFlocPage ValidateOCSFloc ""
# Installation page where sections are executed
Page instfiles

#####################################################################
# Try to find /D="Install folder"
# input, top of stack contains string where to search
# output, top of stack (replaces, with e.g. whatever)
# modifies no other variables.
#####################################################################
Function GetInstallFolder
	; Save used registers
	Exch $R0
	Push $R1
	ClearErrors
    ${GetOptions} '$R0' '/D=' $R1
    IfErrors 0 InstallFolder_Use
    ; No switch in command line, use default location
    StrCpy $R0 "$$PROGRAMFILES64\OCS Inventory Agent"
    Goto InstallFolder_End
InstallFolder_Use:
    StrCpy $R0 "$R1"
InstallFolder_End:
	; Restore used registers
	Pop $R1
	Exch $R0
FunctionEnd

#####################################################################
# Try to find /work_dir="Data folder"
# input, top of stack contains string where to search
# output, top of stack (replaces, with e.g. whatever)
# modifies no other variables.
#####################################################################
Function GetDataFolder
	; Save used registers
	Exch $R0
	Push $R1
	ClearErrors
    ${GetOptions} '$R0' '/work_dir=' $R1
    IfErrors 0 DataFolder_Use
    ; No switch in command line, use default location
    SetShellVarContext All
    StrCpy $R0 "$$APPDATA\OCS Inventory NG\Agent"
    Goto DataFolder_End
DataFolder_Use:
    StrCpy $R0 "$R1"
DataFolder_End:
	; Restore used registers
	Pop $R1
	Exch $R0
FunctionEnd

#####################################################################
# Check if PsExec provided, and use it
#####################################################################
Function CheckPsExec
    StrCmp $SilentMode "Yes" CheckPsExec_silent CheckPsExec_Start

CheckPsExec_Start:
    IfFileExists "psexec.exe" CheckPsExec_ok
    MessageBox MB_ICONEXCLAMATION|MB_YESNO "Using alternate account to launch setup requires Microsoft SysInternals <PsExec.exe> tool.$\r$\n$\r$\nPlease, put it in the same directory as OCS Inventory NG Packager and click <Yes> to try again.$\r$\n$\r$\nClick <No> to disable installing under alternate account." IDYES CheckPsExec_Start IDNO CheckPsExec_No
CheckPsExec_silent:
    ; in silent mode, we check for psexec in current dir and disable credentials fields if not present
    IfFileExists "psexec.exe" CheckPsExec_ok
    Goto CheckPsExec_No
CheckPsExec_No:
    ; PsExec not available, disable credential fields
    StrCpy $Use_PsExec "No"
    WriteINIStr "$PLUGINSDIR\Donnee.ini" "Field 10" "Flags" "DISABLED"
    WriteINIStr "$PLUGINSDIR\Donnee.ini" "Field 11" "Flags" "DISABLED"
    WriteINIStr "$PLUGINSDIR\Donnee.ini" "Field 13" "Flags" "DISABLED"
    WriteINIStr "$PLUGINSDIR\Donnee.ini" "Field 14" "Flags" "DISABLED"
    Return
CheckPsExec_ok:
    ; PsExec available, enable credential fields and include it into package
    StrCpy $Use_PsExec "Yes"
    CopyFiles "psexec.exe" "$PLUGINSDIR\"
FunctionEnd

#####################################################################
# Installer script startup
#####################################################################
Function .onInit
    ; Default value
    StrCpy $SilentMode "No"
    ; Check for Silent Mode
    IfSilent 0 +3
        StrCpy $SilentMode "Yes"
    ; Read parameters from params.ini if in silent mode
    Call ReadParamsIni
     InitPluginsDir
     ; Page resources for agent setup parameters
     !insertmacro MUI_INSTALLOPTIONS_EXTRACT_AS "donnee.ini" "donnee.ini"
     ; Page resources for package export location
     File /oname=$PLUGINSDIR\OCSFloc.ini "OCSFloc.ini"
     ; Script to launch agent setup under admin account
     File /oname=$PLUGINSDIR\1runas.nsi "1runas.nsi"
     ; Icons files
     File /oname=$PLUGINSDIR\OCSInventory.ico "OCSInventory.ico"
     ; Privilegied agent installer with plugins and certificate (launched by 1runas.nsi script)
     File /oname=$PLUGINSDIR\instOCS.exe "instOCS.exe"
     ; Tool to select plugin files
     File /oname=$PLUGINSDIR\ListBox.exe "ListBox.exe"
        ; By default, export created package on Desktop folder
    WriteINIStr "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State" $DESKTOP
    ; Check if PsExec available, to enable or not credential fields
     Call CheckPsExec
    ; Ensure plugins selection always launched at leat one time to create required fields, even if empty
    ExecWait "$PLUGINSDIR\ListBox.exe /S"
FunctionEnd

#####################################################################
# Display window to select package configuration
#####################################################################
Function DonneeConfigPage
    !insertmacro MUI_HEADER_TEXT "OCS Inventory NG Agent for Windows Setup" "Please, provide parameters used by All-In-One Installer to setup OCS Inventory Agent for Windows..."
    !insertmacro MUI_INSTALLOPTIONS_INITDIALOG "donnee.ini"
    Pop $hWnd
    ; Read registry and change button text if additional files provided
    Call ChangeButtonText
    !insertmacro MUI_INSTALLOPTIONS_SHOW
    Pop $0
FunctionEnd

#####################################################################
# Change Addional Files button text to indicate there is files
#####################################################################
Function ChangeButtonText
	; Save used registers
	Push $R0
	Push $R1
    GetDlgItem $R0 $hWnd 1207
    SendMessage $R0 ${WM_SETTEXT} 1 "STR:Add Plugins..."
    ReadRegStr $R1 HKCU Software\OCS_PACKAGER\SETTINGS\FILELIST  File
    StrCmp $R1 "" ChangeButtonText_No_Change
    ; There is selected plugins, change button text
    GetDlgItem $R0 $hwnd 1207
    SendMessage $R0 ${WM_SETTEXT} 1 "STR:View/modify Plugins..."
    Goto ChangeButtonText_End
ChangeButtonText_No_Change:
    ; No plugin added
ChangeButtonText_End:
	; Restore used registers
	Pop $R1
	Pop $R0
FunctionEnd

#####################################################################
# Validate and save configuration
#####################################################################
Function ValidateDonnee
    !insertmacro MUI_INSTALLOPTIONS_READ $0 "donnee.ini" "Settings" "State"
    ; Check if Add/view/modify plugin button clicked
    StrCmp $0 "6" 0 ValidateDonnee_No_Plugins
    ExecWait "$PLUGINSDIR\ListBox.exe"
    Call ChangeButtonTExt
    Abort
ValidateDonnee_No_Plugins:
    ; Check if packager help clicked
    StrCmp $0 "4" 0 ValidateDonnee_No_Help
    ExecShell 'open' 'http://wiki.ocsinventory-ng.org/07.OCS-Tools/OCS-Windows-Packager/'
    Abort
ValidateDonnee_No_Help:
    ; Check if agent command line help clicked
    StrCmp $0 "8" 0 ValidateDonnee_No_Cmd_Help
    ExecShell 'open' 'http://wiki.ocsinventory-ng.org/03.Basic-documentation/Setting-up-the-Windows-Agent-2.x-on-client-computers/#ocs-inventory-ng-agent-for-windows-command-line-options'
    ; Example 3:  /S /server=http://my.server.com/ocsinventory /D='D:\my app\my inventory appp'
    Abort
ValidateDonnee_No_Cmd_Help:
FunctionEnd

#####################################################################
# Display window to select output folder
#####################################################################
Function OCSFlocPage
    !insertmacro MUI_HEADER_TEXT "OCS Inventory NG Agent Setup" "Please, provide target directory to save All-In-One Installer package created..."
    InstallOptions::dialog "$PLUGINSDIR\OCSFloc.ini"
    ;customOCSFloc_endprocess:
FunctionEnd

#####################################################################
# Validate and save output folder
###########################################0##########################
Function ValidateOCSFloc
    ; Read destination choice
    ; If silent mode is enabled, use global variable $Dest_Folder
    ; if silent mode if disabled, use user choice
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $0 $Dest_Folder
        Goto ValidateOCSFloc_done
    ReadINIStr $0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
ValidateOCSFloc_done:
    ; Try to create a file into directory
    FileOpen $1 "$0\file.dat" w
    FileWrite $1 "OK$\r$\n"
    Fileclose $1
    ;  MessageBox MB_ICONEXCLAMATION "$R0\file.dat"
    IfFileExists "$0\file.dat" ValidateOCSFloc_ok ValidateOCSFloc_err
ValidateOCSFloc_err:
    MessageBox MB_ICONSTOP "Target directory not writable !"
    Abort
ValidateOCSFloc_ok:
    Delete "$0\file.dat"
    StrCpy $Dest_Folder "$0"
FunctionEnd

#####################################################################
# Read parameters from params.ini file in silent mode
#####################################################################
Function ReadParamsIni
    ; Only proceed if in Silent Mode
    StrCmp $SilentMode "Yes" +3
        DetailPrint "Not in silent mode, skipping params.ini"
        Return

    ; Check if params.ini exists
    IfFileExists "$EXEDIR\params.ini" +3 0
        DetailPrint "params.ini not found, skipping"
        Return
    
    ; Read parameters from params.ini
    ReadINIStr $R0 "$EXEDIR\params.ini" "Variables" "DestinationFolder"
    ReadINIStr $R1 "$EXEDIR\params.ini" "Variables" "AgentSourceBinaryPath"
    ReadINIStr $R2 "$EXEDIR\params.ini" "Variables" "CmdLineOptions"
    ReadINIStr $R3 "$EXEDIR\params.ini" "Variables" "CACertificateFilePath"
    ReadINIStr $R4 "$EXEDIR\params.ini" "Variables" "Label"
    ReadINIStr $R5 "$EXEDIR\params.ini" "Variables" "OcsPluginsFiles"
    ReadINIStr $R6 "$EXEDIR\params.ini" "Variables" "PsExecAdminId"
    ReadINIStr $R7 "$EXEDIR\params.ini" "Variables" "PsExecAdminPwd"

    ; Store these in global variables
    StrCpy $Dest_Folder $R0
    StrCpy $AgentSourceBinaryPath $R1
    StrCpy $CmdLineOptions $R2
    StrCpy $CACertificateFilePath $R3
    StrCpy $Label $R4
    StrCpy $OcsPluginsFiles $R5
    StrCpy $AdminId $R6
    StrCpy $AdminPwd $R7

FunctionEnd

#####################################################################
# Main section where to build package
#####################################################################
Section
;    SetAutoClose true
    SetOutPath "$PLUGINSDIR\"
    ; Read agent setup filename, and replace value "OcsAgentSetupFilePathToReplace" and "OcsAgentSetupFileTitleToReplace" into script runas.nsi
    ; either from params.ini file if in silent mode, or from donnee.ini file if in interactive mode
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $AgentSourceBinaryPath
        Goto done_reading_agent_setup_filename
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 3" "State"

    done_reading_agent_setup_filename:
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsAgentSetupFilePathToReplace' "$R0" '/S=1' $0
    DetailPrint "Using file <$R0> as OCS Inventory NG Agent Setup file"
    ${GetFileName} "$R0" $0
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsAgentSetupFileTitleToReplace' "$0" '/S=1' $0
    ; Read agent setup version, and replace value "OcsAgentSetupVersionToReplace" into script runas.nsi
    GetDllVersion "$R0" $1 $2
    IntOp $3 $1 / 0x00010000
    IntOp $4 $1 & 0x0000FFFF
    IntOp $5 $2 / 0x00010000
    IntOp $6 $2 & 0x0000FFFF
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsAgentSetupVersionToReplace' '$3.$4.$5.$6' '/S=1' $0
    DetailPrint "OCS Inventory NG Agent for Windows version is <$3.$4.$5.$6>"
    ; Read agent setup command line options
    ; silent mode : use global variable $CmdLineOptions or no silent mode : use donnee.ini file
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $CmdLineOptions
        Goto done_reading_cmd_line_options
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 7" "State"

    done_reading_cmd_line_options:
    StrCpy $Agent_Cmd_Line_Options "$R0"
    DetailPrint "Using <$R0> as OCS Inventory NG Agent setup command line options"
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsCmdLineToReplace' '$Agent_Cmd_Line_Options' '/S=1' $1
    ; Determine agent installation folder from command line
    Push $Agent_Cmd_Line_Options
    Call GetInstallFolder
    Pop $R0
    DetailPrint "Using <$R0> as OCS Inventory NG Agent installation Folder"
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsInstallFolderToReplace' '$R0' '/S=1' $1
    ; Determine agent data folder
    Push $Agent_Cmd_Line_Options
    Call GetDataFolder
    Pop $R0
    DetailPrint "Using <$R0> as OCS Inventory NG agent data folder"
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsDataFolderToReplace' '$R0' '/S=1' $1
    ; Read certificate file and copy it to data folder to include into installer
    ; silent mode : use global variable $CACertificateFilePath or no silent mode : use donnee.ini file
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $CACertificateFilePath
        Goto done_reading_certificate_file
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 5" "State"

    done_reading_certificate_file:
    DetailPrint "Using <$R0> as certificate file to include"
    CreateDirectory "$PLUGINSDIR\OcsData"
    CopyFiles /Silent "$R0" "$PLUGINSDIR\OcsData"
    ; Read label and create file to data folder to include into installer
    ; silent mode : use global variable $Label or no silent mode : use donnee.ini file
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $Label
        Goto done_reading_label
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 9" "State"

    done_reading_label:
    DetailPrint "Using <$R0> as Label text"
    FileOpen $R1 "$PLUGINSDIR\OcsData\Label" w
    FileWrite $R1 "$R0"
    FileClose $R1
    ; Replace data folder to include
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsIncludeDataFolderToReplace' "$PLUGINSDIR\OcsData" '/S=1' $0
    ; use Psexec?
    StrCmp $Use_PsExec "Yes" 0 No_Psexec
    ; Yes, so read user and password and replace them into installer
    DetailPrint "Using Microsoft SysInternals PsExec.exe tool"

    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $AdminId
        Goto done_psexec_id
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 10" "State"
    
    done_psexec_id:
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'AdminIdToReplace' "$R0" '/S=1' $0
    DetailPrint "Using <$R0> as Administrator account"

    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $AdminPwd
        Goto done_psexec_pwd
    ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 11" "State"
    
    done_psexec_pwd:
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'AdminPwdToReplace' "$R0" '/S=1' $0
    DetailPrint "Using <$R0> as Administrator password"
    Goto Include_Plugins
    
No_Psexec:
    ; No PsExec use, so set empty Admin credentials into installer
    DetailPrint "Not using Microsoft SysInternals PsExec.exe tool"
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'AdminIdToReplace' '' '/S=1' $0
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'AdminPwdToReplace' '' '/S=1' $0
    ; Comment PsExec inclusion into installer
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'File "PsExec.exe"' ';File "PsExec.exe"' '/S=1' $0
    
Include_Plugins:
    ; Initialize non empty directory
    CreateDirectory "$PLUGINSDIR\OcsPlugins"
    FileOpen $R0 "$PLUGINSDIR\OcsPlugins\DO_NOT_REMOVE.txt" w
    FileClose $R0

    ; Check for Silent Mode
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R6 $OcsPluginsFiles
        Goto Copy_Plugin_Files

    ; Normal mode - get plugin files from list
    Readinistr $R6 "$PLUGINSDIR\${COL_FILE}" "collection" "Liste"

Copy_Plugin_Files:
    StrCmp $R6 "" End_Loop_Plugins ; No plugins to include
    ; Find number of files in collection
    ${WordFind} $R6 "|" "*" $R0
    ; Copy each file
    StrCpy $1 "0"

Loop_Plugin_File:
    IntCmp $R0 $1 0 End_Loop_Plugins
    IntOp $1 $1 + 1
    ; Retrieve current indexed_file
    ${WordFind} $R6 "|" "+$1" $R1
    StrCmp $R1 "" End_Loop_Plugins
    DetailPrint "Including <$R1> plugin file"
    CopyFiles /Silent $R1 "$PLUGINSDIR\OcsPlugins"
    Goto Loop_Plugin_File
End_Loop_Plugins:
    ; Replace data folder to include
    ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsIncludePluginsFolderToReplace' "$PLUGINSDIR\OcsPlugins" '/S=1' $0
    ; Unload plugin to allow emptying temp folder
    ${textreplace::Unload}
    ; Include NSIS compiler files
    DetailPrint "Extracting NSIS compiler"
    File /R "${NSIS_PATH}"
    ; Read export folder location
    ; silent mode : use global variable $Dest_Folder or no silent mode : use OCSFloc.ini file
    StrCmp $SilentMode "Yes" 0 +3
        StrCpy $R0 $Dest_Folder
        Goto done_reading_export_folder
    ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
    
    done_reading_export_folder:
    Sleep 1000
    DetailPrint "Executing NSIS compiler for custom All-In-One Installer"
    nsExec::ExecToLog "$PLUGINSDIR\nsis\makensis.exe runas.nsi"
    IfFileExists "OcsPackage.exe" 0 Bad_Compile
    ClearErrors
    DetailPrint "Custom All-In-One Installer successfully built"
    DetailPrint "Copying  All-In-One Installer package to <$R0\OcsPackage.exe>"
    CopyFiles /Silent "OcsPackage.exe" "$R0\OcsPackage.exe"
;    IfErrors Bad_Copy Success_End
     Goto Success_End
Bad_Compile:
    DetailPrint "Error compiling All-In-One Installer package !"
    MessageBox MB_ICONSTOP "Error compiling All-In-One Installer package !"
    Abort
;Bad_Copy:
;    DetailPrint "Error writing All-In-One Installer package into folder <$R0> !"
;    MessageBox MB_ICONSTOP "Error writing All-In-One Installer package into folder$\r$\n$R0 !"
;    Abort
Success_End:
    DetailPrint "All-In-One Installer package saved to file <$R0\OcsPackage.exe>"
;    MessageBox MB_OK|MB_ICONINFORMATION "All-In-One Installer package saved to file$\r$\n$R0\OcsPackage.exe"
SectionEnd
