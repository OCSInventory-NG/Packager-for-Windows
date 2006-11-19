silentinstall silent
OutFile "uninsocs.exe"
ShowInstDetails hide
Function .onInit
         InitPluginsDir
         ;Verifying path
         ReadRegStr $R0 HKLM "SYSTEM\CurrentControlSet\Services\OCS INVENTORY" "ImagePath"
         strcpy $R1 $R0 -15 #
         strcpy $R7 $R1 "" 1 #
         strcmp $R7 "" end
         call setv
         
end:
FunctionEnd
;
function setv
         strcmp $R7 "" +2
         execshell '' '"$R7uninst.exe"' '/S' sw_hide

functionend

section
   sleep 2000
  ;messagebox mb_ok $R7
SectionEnd

