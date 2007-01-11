#ifndef _UTILS_H_
#define _UTILS_H_

#define CHECKSUM_COMPUTING_BUFFER 1024

#include "stdafx.h"

void OpenLog( LPCTSTR lpstrFolder, LPCTSTR lpstrCommandLine);
void AddLog(LPCTSTR lpstrLog,...);
void CloseLog();
age( CString id ) ;
CString getFilePath( LPCSTR file, LPCSTR id) ;
CString getFileContent( LPCSTR file, LPCSTR id ) ;
void createRestorePoint( CString nme ) ;
void cleanPackage( CString id );
int simple_digest (char *alg, CString fName, UINT *olen, UCHAR **) ;
CString print_hex (unsigned char *bs, unsigned int n);
/* A helper function for base64 encoding */
CString base64_encode (unsigned char *buf, unsigned int len);
int unzip(CString file, CString path);



#endif // _UTILS_H_