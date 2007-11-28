
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

#include "stdafx.h"
#include "commonDownload.h"

int init_OpenSSL(void)
{
    if (/*!THREAD_setup() || */!SSL_library_init())
    {
        //AddLog( "** OpenSSL initialization failed!\n");
		return 1;
    }
    SSL_load_error_strings();
	return 0;
}

void seed_prng(void)
{
	CString namePath;
	namePath.Format("download\\rand");
	
	RAND_write_file(namePath.GetBuffer(0));
	RAND_load_file(namePath.GetBuffer(0), 1024);

	DeleteFile( namePath );
}


int fileExists(LPCSTR file, LPCSTR Id, LPCSTR dir) {

	int err;
	CFile infFile;
	CString fName;
	if (Id == NULL)
		fName = file;
	else if( dir != NULL )
		fName.Format("%s\\%s\\%s", dir, Id, file);
	else
		fName.Format("%s\\%s", Id, file);

	if( ! infFile.Open(fName, CFile::modeRead ) ){
		err = GetLastError();
		if( err == ERROR_FILE_NOT_FOUND || err == ERROR_PATH_NOT_FOUND )
			return 0;
		else {
			return -1;
		}
	}
	else {
		return 1;
	}
}
