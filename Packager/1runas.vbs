
set args=wscript.arguments
username = "Administrateur"
pass = "Password"
cmd = "instocs.exe"

'Used for testing
'wscript.echo "runas.exe /user:" & username & " """ & command & """"
set shell=wscript.createobject("Wscript.shell")
'Run runas.exe
shell.run "runas.exe /env /user:" & username & " """ & cmd & """",2
'Wait for runas.exe to load, this time could be shorter, but is set to 1000
'to be safe
wscript.sleep(1000)
'Send the password and hit enter
shell.sendkeys pass & "{ENTER}"