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
!include "FileFunc.nsh"
!insertmacro GetFileName
;!insertmacro un.GetParent
!include "TextReplace.nsh"
!include "MUI.nsh"
!include "WordFunc.nsh"
;!insertmacro WordFind2X
!insertmacro MUI_LANGUAGE "English"
!define Compile_version "1.0.1.6"

  VIProductVersion "${Compile_version}"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "OcsPackager"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "Packager script for OCS Inventory"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Ocs Inventory Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" "OcsPackager is an addon for Ocs Inventory NG."
  VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Ocs Inventory Team"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "OcsPackager.exe"
  VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "${Compile_version}"

var deployed_file
BRANDINGTEXT "OCS Packager ${Compile_version}"
Icon "logoOCS.ico"
ShowInstDetails hide
Name "OCS Packager"
OutFile "OcsPackager.exe"

Page custom donnee Validatedonnee ""
Page custom customOCSFloc ValidatecustomOCSFloc ""
Page instfiles

Function .onInit
 InitPluginsDir
 File /oname=$PLUGINSDIR\OCSFloc.ini "OCSFloc.ini"
 File /oname=$PLUGINSDIR\donnee.ini "donnee.ini"
 File /oname=$PLUGINSDIR\1runas.nsi "1runas.nsi"
 File /oname=$PLUGINSDIR\1runasUninst.nsi" "1runasUninst.nsi"
 File /oname=$PLUGINSDIR\xRCE.exe "xRCE.exe"
 File /oname=$PLUGINSDIR\pack.ico "pack.ico"
 File /oname=$PLUGINSDIR\upack.ico "upack.ico"
 File /oname=$PLUGINSDIR\instocs.exe "instocs.exe"
 File /oname=$PLUGINSDIR\uninsocs.exe "uninsocs.exe"
 File /oname=$PLUGINSDIR\1runas.vbs "1runas.vbs"
; File /oname=$PLUGINSDIR\msvcr71.dll "msvcr71.dll"
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
 InstallOptions::dialog "$PLUGINSDIR\donnee.ini"
; customOCSFloc_endprocess:
FunctionEnd

Function Validatedonnee
  ;
   ReadINIStr $R3 "$PLUGINSDIR\donnee.ini" "Field 3" "State"
   strcpy $deployed_file $R3
   ${GetFileName} "$R3" $0
   ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runas.nsi' '$PLUGINSDIR\runas.nsi' 'file_x_name' "$0" '/S=1' $0
call folder
strcmp $R7 "" chemin_defaut0 ; si pas option /D:alors fin
GOTO chemin_calcule0
chemin_defaut0:
strcpy $R7 "$PROGRAMFILES\OCS Inventory Agent"
chemin_calcule0:
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'createdir' '$R7' '/S=1' $1

   ReadINIStr $R4 "$PLUGINSDIR\donnee.ini" "Field 4" "State"
   ReadINIStr $R2 "$PLUGINSDIR\donnee.ini" "Field 5" "State"
   ReadINIStr $R0 "$PLUGINSDIR\donnee.ini" "Field 6" "State"
   ReadINIStr $R1 "$PLUGINSDIR\donnee.ini" "Field 7" "State"
   ReadINIStr $R6 "$PLUGINSDIR\donnee.ini" "Field 13" "State"
   ReadINIStr $R7 "$PLUGINSDIR\donnee.ini" "Field 15" "State"

 ;   VALIDATION................................FileOpen $1 "$PLUGINSDIR\1runas.nsi" r
;lecture:
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runas.vbs' '$PLUGINSDIR\runas.vbs' "Administrateur" "$R0" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'label.txt' '$R7' '/S=1' $1

 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.vbs' '$PLUGINSDIR\runas.vbs' 'Password' "$R1" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Administrateur' "$R0" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Password' "$R1" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'Options' "$R2" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'OcsAgentSetupTMP' "$R3" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\1runasUninst.nsi' '$PLUGINSDIR\runasUninst.nsi' 'Administrateur' "$R0" '/S=1' $0
 ${textreplace::ReplaceInFile} '$PLUGINSDIR\runasUninst.nsi' '$PLUGINSDIR\runasUninst.nsi' 'Password' "$R1" '/S=1' $0
;messagebox mb_ok "Le label est $R7 dans: $PLUGINSDIR\runas.nsi"
;TEST PASSWORD
;  StrCpy $1 $R0
;  StrCpy $2 $R1
;  StrCpy $3 "$R3"
;  StrCpy $4 0
;  System::Call 'RunAs::RunAsW(w r1, w r2, w r3, *w .r4) i .r0 ? u'
;  IntCmp $0 1 success
;  MESSAGEBOX MB_OK "$0  echec"
;  abort
;success:
;MESSAGEBOX MB_OK "$0   OK"
 ;FIN TEST PASSWORD
; chercher si other file
;call folder
;MESSAGEBOX MB_OK "$r4   cert"
  StrCpy $R1 ""
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
call folder
strcmp $R7 "" chemin_defaut ; si pas option alors fin
GOTO chemin_calcule
chemin_defaut:
strcpy $R7 "$PROGRAMFILES\OCS Inventory Agent"
chemin_calcule:
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other.file.def' '$R3 "$R4"' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'createdir' '$R7' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other.file' '$R7\$R3' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'othern.filen' '$R3' '/S=1' $1

${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' ';other.rem' '' '/S=1' $1

rien:
; chercher si other1 file
;call folder
;MESSAGEBOX MB_OK "$r6   other..."
  StrCpy $R4 $R6
  StrCpy $R1 ""
  strcmp $R4 "" rien1 ; si pas option alors fin
  Strlen $0 $R4
get_char1:
  IntOp $R1 $R1 + 1
  StrCpy $R5 $R4 1 $R1
  strcmp $R5 "\" 0 suite1
  strcpy $R5 ""
  strcpy $R3 ""
suite1:
  strcpy $R3 "$R3$R5"
  intcmp $R1 $0 0 get_char1
;////////$R3 = FICHIER $R4= CHEMIN COMPLET source///////////////
call folder
strcmp $R7 "" chemin_defaut1 ; si pas option alors fin
GOTO chemin_calcule1
chemin_defaut1:
strcpy $R7 "$PROGRAMFILES\OCS Inventory Agent"
chemin_calcule1:
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other1.file.def' '$R3 "$R4"' '/S=1' $1
;${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'createdir' 'createdirectory "$R7"' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other1.file' '$R7\$R3' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' 'other1n.filen' '$R3' '/S=1' $1
${textreplace::ReplaceInFile} '$PLUGINSDIR\runas.nsi' '$PLUGINSDIR\runas.nsi' ';other1.rem' '' '/S=1' $1

rien1:
${textreplace::Unload}

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
   Execwait "$PLUGINSDIR\nsis\makensis.exe runas.nsi"
   Execwait "$PLUGINSDIR\nsis\makensis.exe runasuninst.nsi"

  ClearErrors
   ; Readinistr $4 "$R7\ocs-ng\OCSInventory.conf" "OCS Inventory Agent" "DeviceID"
   ; ${GetFileExt}  "$R7\ocs-ng\*.ocs" $filename
   ; messagebox mb_ok $filename

   CopyFiles "OcsPackage.exe" "$R0\"
  ; CopyFiles "OcsUninstall.exe" "$R0\"
   IfErrors bad_copy good_copy
   ;IfFileExists "$R0\$4.ocs" good_copy bad_copy

bad_copy:
   MessageBox MB_iconexclamation "Error writing output files on:$\r$\n$R0"
 abort
good_copy:
   MessageBox MB_OK "Files created on:$\r$\n$R0\.$\r$\n"

SectionEnd


Function folder
 strcpy $R7 ""
; testing /folder: option
  Push "$R2"
  Push " /D="
  Call StrStr
  Pop $R9
  Strlen $0 $R9
  ;messagebox mb_ok $0
  intcmp $0 4 folder_use 0 folder_use
  goto folder_end
folder_use:

 strcpy $R7 $R9 "" 4
; repérer la séquence {blanc slash}
  Push "$R7"
  Push " /"
  Call StrStr
  Pop $R9
  Strlen $2 $R7
  Strlen $1 $R9
  intop $3 $2 - $1
  strcpy $R7 $R7 $3 0

 ; createdirectory "$R7"
folder_end:
 ;messagebox mb_ok "install dans le dossier :$R7"
FunctionEnd

