/*******************************************************************
*
*			COMWIN
*			
*			declarations generales
*
*			Creation : 1998/08/26		BLR
*
*			Modif    : 1999/04/26		BLR
*										adaptation 32 bits
*
*******************************************************************/
#ifdef DEF_MODULE_COMWIN
	#define EXTERN 
#else
	#define EXTERN  extern
#endif


#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <ctype.h> 
#include <tlhelp32.h>
#include "process.h"
	
	
#define Strlen(x) 			strlen((LPSTR)(x))
#define Strcpy(x,y)         strcpy((LPSTR)(x),(LPSTR)(y))
#define Strcat(x,y)			strcat((LPSTR)(x),(LPSTR)(y))
#define Strtok(x,y)			strtok((LPSTR)(x),(LPSTR)(y))
#define Strcmp(x,y)			strcmp((LPSTR)(x),(LPSTR)(y))
#define Strchr(x,y)			strchr((LPSTR)(x),y)
#define Strrchr(x,y)		strrchr((LPSTR)(x),y)
	
#define Memset(x,y,z)		memset((LPSTR)(x),(y),(int)(z))
#define Memcpy(x,y,z)		memcpy((LPSTR)(x),(LPSTR)(y),(int)(z))
#define Memcmp(x,y,z)		memcmp((LPSTR)(x),(LPSTR)(y),(int)(z))
#define Memchr(x,y)			memchr((LPSTR)(x),(y))1
	

    
	

#define	AllocPtr(s)		GlobalAllocPtr(GHND, (DWORD)(s))
#define	FreePtr(p)		GlobalFreePtr((p))
#define ReAllocPtr(p,s) GlobalReAllocPtr((p), (DWORD)(s), GHND)

typedef BOOL (WINAPI *PROCESSWALK)(HANDLE hSnapshot, LPPROCESSENTRY32 lppe); 
typedef HANDLE (WINAPI *CREATESNAPSHOT)(DWORD dwFlags, DWORD th32ProcessID); 
 

