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
OutFile "ocsuninstall.exe"
ShowInstDetails hide
Icon "upack.ico"
Function .onInit
         InitPluginsDir
         File /oname=$PLUGINSDIR\xRCE.exe "xRCE.exe"
         File /oname=$PLUGINSDIR\upack.ico "upack.ico"
         File /oname=$PLUGINSDIR\uninsocs.exe "uninsocs.exe"
         call setv
FunctionEnd

function setv
   strcpy $0  "Administrateur"
   strcpy $1  "Password"
   SetOutPath "$PLUGINSDIR\"
;detect admin right
   Call IsUserAdmin ; Bug In domain mode
;xtInfoPlugin::IsAdministrator
   Pop "$R0"
   strcmp $R0 "true" Okadmin 0
   execshell '' 'xRCE.exe' '\\localhost /user:$0 /pwd:$1 uninsocs.exe' sw_hide
   goto NOkadmin
Okadmin:
  execwait 'uninsocs.exe'
NOkadmin:
functionend

section
    setoutpath "$PLUGINSDIR"
    sleep 7000
    ;createdir
    ;other.rem copyfiles "$PLUGINSDIR\;other.file
    ;other1.rem copyfiles "$PLUGINSDIR\;other1.file
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
; MessageBox MB_OK 'User= "$R1"  AccountType= "$R2"  IsUserAdmin= "$R0"'

Pop $R2
Pop $R1
Exch $R0
FunctionEnd