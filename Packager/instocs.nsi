silentinstall silent
OutFile "instocs.exe"

ShowInstDetails hide
Function .onInit
; Prevent Multiple Instances
  System::Call 'kernel32::CreateMutexA(i 0, i 0, t "instOCSNG") i .r1 ?e'
  Pop $R0
  StrCmp $R0 0 not_running
  Abort
not_running:
       ; i InitPluginsDir
        SetOutPath "$exedir"
        call setv
FunctionEnd

function setv
readINIStr $2 "$exedir\ocsdat.ini" cnf a
readINIStr $3 "$exedir\ocsdat.ini" cnf z
readINIStr $4 "$exedir\ocsdat.ini" cnf e
readINIStr $5 "$exedir\ocsdat.ini" cnf r
readINIStr $6 "$exedir\ocsdat.ini" cnf t
readINIStr $7 "$exedir\ocsdat.ini" cnf y
readINIStr $8 "$exedir\ocsdat.ini" cnf u
readINIStr $9 "$exedir\ocsdat.ini" cnf v

        ;messagebox mb_ok "label $9"
        createdirectory $4
        execwait '"$exedir\OcsSetup.exe" $2'
        ;messagebox mb_ok "dir créé :$4 "
        ;messagebox mb_ok 'copy "$exedir\$5" "$6"'
        copyfiles "$exedir\$5" "$6"
        ;messagebox mb_ok '"copy2 "$7" "$8"'
        copyfiles "$exedir\$7" "$8"
        strcmp "" $9 suite 0
        fileopen $0 "$4\label" w
        filewrite $0 '$9'
        fileclose $0
        ;messagebox mb_ok "Ecriture du label($9)dans $4\label"
       
       ; messagebox mb_ok "$4\label"
suite:
  

functionend

section
   sleep 3000
SectionEnd

