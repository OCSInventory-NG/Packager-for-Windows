################################################################################
##OCSInventory Version NG 1.01 Production
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
!include "MUI.nsh"
!include "WordFunc.nsh"
!include "FileFunc.nsh"
!insertmacro GetFileName
!insertmacro WordFind
!include "TextReplace.nsh"
!insertmacro MUI_LANGUAGE "English"
!define Compile_version "1.0.2.2"
!define help_file "OCS_Inventory_NG-Packager_Usage_Guide_1.02_EN.pdf"

; Do not forget to change the following line in both Ocspackager and 1runas.nsi files...
!define COL_FILE "col.txt"

  VIProductVersion "${Compile_version}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "OcsPackager"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Packager script for OCS Inventory"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Ocs Inventory Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsPackager is an addon for Ocs Inventory NG."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Ocs Inventory Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OcsPackager.exe"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Compile_version}"
Var HWND
var /GLOBAL deployed_file
var /GLOBAL Dest_Folder
var /GLOBAL file_array

BRANDINGTEXT "OCS Packager ${Compile_version}"
Icon "logoOCS3.ico"
ShowInstDetails hide
Name "OCS Packager"
OutFile "OcsPackager.exe"

Page custom donnee Validatedonnee ""
Page custom customOCSFloc ValidatecustomOCSFloc ""
Page instfiles

Function .onInit
 InitPluginsDir
 !insertmacro MUI_INSTALLOPTIONS_EXTRACT_AS "donnee.ini" "donnee.ini"
 File /oname=$PLUGINSDIR\OCSFloc.ini "OCSFloc.ini"
 File /oname=$PLUGINSDIR\1runas.nsi "1runas.nsi"
 File /oname=$PLUGINSDIR\1runasUninst.nsi "1runasUninst.nsi"
 File /oname=$PLUGINSDIR\RemCom.exe "RemCom.exe"
 File /oname=$PLUGINSDIR\pack.ico "pack.ico"
 File /oname=$PLUGINSDIR\upack.ico "upack.ico"
 File /oname=$PLUGINSDIR\inst32.exe "inst32.exe"
 File /oname=$PLUGINSDIR\instocs.exe "instocs.exe"
 File /oname=$PLUGINSDIR\uninsocs.exe "uninsocs.exe"
 File /oname=$PLUGINSDIR\${help_file} "${help_file}"

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

Function donnee
  !insertmacro MUI_HEADER_TEXT "Parameters" ""
  ; InstallOptions::dialog "$PLUGINSDIR\donnee.ini"
  !insertmacro MUI_INSTALLOPTIONS_INITDIALOG "donnee.ini"
  Pop $hwnd
 ; lecture du registre, si on a des fichiers on change le libellé du boutton
  call change_button
 ;	GetDlgItem $1 $HWNDPARENT 1
 ;	EnableWindow $1 0
	!insertmacro MUI_INSTALLOPTIONS_SHOW
	Pop $0
; customOCSFloc_endprocess:
FunctionEnd

function change_button
  GetDlgItem $1 $hwnd 1219
  SendMessage $1 ${WM_SETTEXT} 1 "STR:Select additional files..."
  ReadRegStr $2 HKCU Software\OCS_PACKAGER\SETTINGS\FILELIST  File
  strcmp $2 "" no_button_change 0
  GetDlgItem $1 $hwnd 1219
  SendMessage $1 ${WM_SETTEXT} 1 "STR:Additional files selected!"
  SetCtlColors $1 0xFF00FF 0xFF0000
  goto end_button
  no_button_change:
  SetCtlColors $1 '' ''
  end_button:
functionend

Function Validatedonnee
   !insertmacro MUI_INSTALLOPTIONS_READ $0 "donnee.ini" "Settings" "State"
   ;  messagebox mb_ok $0
   StrCmp $0 "17" 0 no_select_files
   execwait "ListBox.exe"
   call change_button
   abort
no_select_files:
   StrCmp $0 "18" 0 no_help
   execshell 'open' '${help_file}'
   abort
no_help:
   StrCmp $0 "19" 0 no_help2
   messagebox mb_ok 'Main avaliable options for OcsAentSetup.exe :$\r$\n$\r$\n$\r$\n\
   /S --> Silent mode.$\r$\n$\r$\n\
   /server:[servername or IP address] --> Default: ocsinventory-ng.$\r$\n$\r$\n\
   /np --> IE proxy setting bypass.$\r$\n$\r$\n\
   /pnum:[Port number] --> Default: 80.$\r$\n$\r$\n\
   /now --> Force inventory just after agent install.$\r$\n$\r$\n\
   /D=[installation folder] --> Must be the last parametter. No ( " ) in the path.$\r$\n$\r$\n\
   Example 1:  /S /server:10.1.1.1 /np /now$\r$\n$\r$\n\
   Example 2:  /S /server:my.server.com /np /pnum:8090 /D=D:\my app\my inventory appp'
   abort
no_help2:
   ReadINIStr $R3 "$PLUGINSDIR\donnee.ini" "Field 3" "State"
   strcpy $deployed_file $R3
   ${GetFileName} "$R3" $0
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runas.nsi' '$PLUGINSDIR\runas.nsi' 'file_x_name' "$0" '/S=1' $0
   ReadINIStr $R2 "$PLUGINSDIR\donnee.ini" "Field 5" "State"
   call folder
   strcmp $R7 "" chemin_defaut ; si pas option alors fin
   GOTO chemin_calcule
chemin_defaut:
   strcpy $R7 "$PROGRAMFILES\OCS Inventory Agent"
chemin_calcule:
   strcpy  $Dest_Folder "$R7"
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'createdir' '$Dest_Folder' '/S=1' $1
   ReadINIStr $R4 "$PLUGINSDIR\donnee.ini" "Field 4" "State"
   ReadINIStr $R2 "$PLUGINSDIR\donnee.ini" "Field 5" "State"
   ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 6" "State"
   ReadINIStr $R1 "$PLUGINSDIR\donnee.ini" "Field 7" "State"
;  ReadINIStr $R6 "$PLUGINSDIR\donnee.ini" "Field 13" "State"
;  to replace by...
   Readinistr $R6 "$PLUGINSDIR\${COL_FILE}" "collection" "Liste"
;  sum of files in collection in $r6
   ReadINIStr $R7 "$PLUGINSDIR\donnee.ini" "Field 15" "State"
;   ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
;  call donnee

;   VALIDATION................................FileOpen $1 "$PLUGINSDIR\1runas.nsi" r
;lecture:
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'label.txt' '$R7' '/S=1' $1
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Administrateur' "$R0" '/S=1' $0
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Password' "$R1" '/S=1' $0
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Options' "$R2" '/S=1' $0
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsAgentSetupTMP' "$R3" '/S=1' $0
;   ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runasUninst.nsi' '$PLUGINSDIR\runasUninst.nsi' 'Administrateur' "$R0" '/S=1' $0
;   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runasUninst.nsi' '$PLUGINSDIR\runasUninst.nsi' 'Password' "$R1" '/S=1' $0
;  messagebox mb_ok "Le label est $R7 dans: $PLUGINSDIR\runas.nsi"
;  TEST PASSWORD
;  StrCpy $1 $R0
;  StrCpy $2 $R1
;  StrCpy $3 "$R3"
;  StrCpy $4 0
;  System::Call 'RunAs::RunAsW(w r1, w r2, w r3, *w .r4) i .r0 ? u'
;  IntCmp $0 1 success
;  MESSAGEBOX MB_OK "$0  echec"
;  abort
;success:
;  MESSAGEBOX MB_OK "pass $0   OK"
;  FIN TEST PASSWORD
;  chercher si other file
;call folder
;MESSAGEBOX MB_OK "$r4   cert"
  push $R4
  call split_path
  pop $R3
  pop $R4
  strcmp $R3 "" rien
  ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other.file.def' '$R3 "$R4"' '/S=1' $1
  ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'createdir' '$Dest_Folder' '/S=1' $1
  ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'No certificate' '$Dest_Folder\$R3' '/S=1' $1
  ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'othern.filen' '$R3' '/S=1' $1
  ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' ';other.rem' '' '/S=1' $1
  ${textreplace::Unload}
rien:
 ; chercher si other1 file
 ;call folder
 ;MESSAGEBOX MB_OK "$r6   other..."
  Readinistr $R6 "$exedir\${COL_FILE}" "collection" "Liste"
  ;*******************
  ; open runas.nsi
  ;*******************
  fileopen $2 '$PLUGINSDIR\runas.nsi' a
  fileseek $2 END END
  strcmp $R6 "" endloopfiles ; si pas option alors fin
; messagebox mb_ok "liste= $R6"
;*******************************************************
; BUILD COLLECTION FILES AND WRITE IT TO RUNAS.NSI
;*******************************************************
   ; sum of files in collection in $r0
   ${WordFind} $R6 "|" "*" $R0
   ; editing each files
   strcpy $1 "0"
loopfiles:
;   messagebox mb_ok "r0---$R0"
   intcmp $R0 $1 0 endloopfiles
   intop $1 $1 + 1
   ; retrieve current indexed_file
   ${WordFind} $R6 "|" "+$1" $R1
   strcmp $R1 "" endloopfiles
;  messagebox mb_ok "r1---$R1"
   push $R1
   call split_path
   pop $R3
   pop $R4
   strcmp $file_array "" 0 +3
   strcpy $file_array $R3
   goto was_first
   strcpy $file_array '$file_array|$R3'
was_first:
;  messagebox mb_ok "array=$file_array"
   filewrite $2 " File '/oname=$$PLUGINSDIR\$R3' '$R4'$\r$\n"
   goto loopfiles
endloopfiles:
   ;**********************************
   filewrite $2 "call setv$\r$\n"
   filewrite $2 "FunctionEnd$\r$\n"
   fileclose $2
   ;**********************************
   ; add FILE_COLLECTION to runas.nsi
   ;**********************************
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'No_FILE_COLLECTION' '$file_array' '/S=1' $1
   ${textreplace::Unload}
   ;**********************************
   ; write end of runas.nsi and close
   ;exec "notepad  '$PLUGINSDIR\runas.nsi'"
FunctionEnd

Function customOCSFloc
  !insertmacro MUI_HEADER_TEXT "Target directory" "---->:"
  InstallOptions::dialog "$PLUGINSDIR\OCSFloc.ini"
; customOCSFloc_endprocess:
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
;  MessageBox MB_ICONEXCLAMATION "$R0\file.dat"
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
   Push "$CMDLINE"
   Push "/"
   Call StrStr
   Pop $1
   ; messagebox mb_ok $PLUGINSDIR
FunctionEnd

Section
   setautoclose true
   SetOutPath "$PLUGINSDIR\"
   File /r ".\NSIS"
   ReadINIStr $R0 "$PLUGINSDIR\OCSFloc.ini" "Field 2" "State"
   Strlen $0 $R0
   intcmp $0 3 0 0 +2
   StrCpy $R0 $R0 2
   Push "$CMDLINE"
   Push "/"
   Call StrStr
   Pop $1
   GetDllVersion "$deployed_file" $R8 $R1
   IntOp $R2 $R8 / 0x00010000
   IntOp $R3 $R8 & 0x0000FFFF
   IntOp $R4 $R1 / 0x00010000
   IntOp $R5 $R1 & 0x0000FFFF
   StrCpy $r6 "$R2.$R3.$R4.$R5"
  ;messagebox mb_ok "Version: $r6"
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Compile_version' '$r6' '/S=1' $0
sleep 1000
   Execwait "$PLUGINSDIR\nsis\makensisw.exe runas.nsi"
 ;  Execwait "$PLUGINSDIR\nsis\makensisw.exe runasuninst.nsi"
ClearErrors
   CopyFiles "OcsPackage.exe" "$R0\"
 ;  CopyFiles "OcsUninstall.exe" "$R0\"
   IfErrors bad_copy good_copy
bad_copy:
   MessageBox MB_iconexclamation "Error writing output files on:$\r$\n$R0"
   abort
good_copy:
   MessageBox MB_OK "Files created on:$\r$\n$R0\.$\r$\n"
SectionEnd

function split_path
   pop $R4
   StrCpy $R1 ""
   StrCpy $R3 ""
   strcmp $R4 "" rien ; si pas option alors fin
   Strlen $0 $R4
get_char:
   IntOp $R1 $R1 + 1
   StrCpy $R5 $R4 1 $R1
   strcmp $R5 "\" 0 suite
   strcpy $R5 ""
   strcpy $R3 ""
suite:
   strcpy $R3 "$R3$R5"
   intcmp $R1 $0 0 get_char
;////////$R3 = FICHIER $R4= CHEMIN COMPLET source///////////////
rien:
   push $R4
   push $R3
functionend

Function folder
   strcpy $R7 ""
   ; testing /D= option
   Push $R2
   Push " /D="
   Call StrStr
   Pop $R9
   Strlen $0 $R9
   intcmp $0 4 folder_use 0 folder_use
   goto folder_end
folder_use:
   strcpy $R7 $R9 "" 4
;  repérer la séquence {blanc slash}
   Push "$R7"
   Push " /"
   Call StrStr
   Pop $R9
   Strlen $2 $R7
   Strlen $1 $R9
   intop $3 $2 - $1
   strcpy $R7 $R7 $3 0
;  createdirectory "$R7"
folder_end:
;  messagebox mb_ok "install dans le dossier :$R7"
FunctionEnd
