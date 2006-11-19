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


Function .onInit
  InitPluginsDir
  File /oname=$PLUGINSDIR\xRCE.exe "xRCE.exe"
 ; File /oname=$PLUGINSDIR\msvcr71.dll "msvcr71.dll"
  File /oname=$PLUGINSDIR\OcsSetup.exe "OcsAgentSetupTMP"
  File /oname=$PLUGINSDIR\pack.ico "pack.ico"
  File /oname=$PLUGINSDIR\instocs.exe "instocs.exe"
;  File /oname=$PLUGINSDIR\runas.vbs "runas.vbs"
 ;other.rem File /oname=$PLUGINSDIR\other.file.def
 ;other1.rem File /oname=$PLUGINSDIR\other1.file.def

  call setv
FunctionEnd

function setv
  strcpy $0  "Administrateur"
  strcpy $1  "Password"
  strcpy $2  "Options"
  SetOutPath "$PLUGINSDIR"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf a $2
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf z "$PLUGINSDIR\"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf e "createdir"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf r "othern.filen"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf t "other.file"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf y "other1n.filen"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf u "other1.file"
  WriteINIStr "$PLUGINSDIR\ocsdat.ini" cnf V "label.txt"
  ;messagebox mb_ok "label du runas : label.txt  chemin $exedir"
  ;messagebox mb_ok "dir créé : createdir"
  sleep 500
  Call IsUserAdmin ; Bug In domain mode
  Pop "$R0"
  strcmp $R0 "true" Okadmin 0
 ; messagebox mb_ok "xrce /user:$0 /pwd:$1"
  execshell '' 'xRCE.exe' '\\localhost /user:$0 /pwd:$1 instocs.exe' sw_hide
  sleep 1000
  ;removed because too much dangerous
  ;execshell '' 'cscript' '/B runas.vbs' sw_hide
  goto NOkadmin
Okadmin:
  ;MESSAGEBOX MB_OK "admin"
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
;  MessageBox MB_OK 'User= "$R1"  AccountType= "$R2"  IsUserAdmin= "$R0"'

 Pop $R2
 Pop $R1
 Exch $R0
FunctionEnd