
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pierre LEMMET/Pascal DANEK 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// ModuleDownload.h: interface for the CModuleDownload class.
//
//////////////////////////////////////////////////////////////////////

#ifndef DOWNLOAD_INCLUDE
#define DOWNLOAD_INCLUDE

#define FRAG_LATENCY_DEFAULT	"10"
#define PERIOD_LATENCY_DEFAULT	"0"
#define CYCLE_LATENCY_DEFAULT	"10"
#define MAX_ERROR_COUNT			"30"
#define PERIOD_LENGTH_DEFAULT	"10"
#define TIMEOUT_DEFAULT			"30"

#define CODE_SUCCESS			"SUCCESS"
#define ERR_BAD_ID				"ERR_BAD_ID"
#define ERR_DOWNLOAD_INFO		"ERR_DOWNLOAD_INFO"
#define ERR_BAD_DIGEST			"ERR_BAD_DIGEST"
#define ERR_DOWNLOAD_PACK		"ERR_DOWNLOAD_PACK"
#define ERR_BUILD				"ERR_BUILD"
#define ERR_EXECUTE				"ERR_EXECUTE"
#define ERR_CLEAN				"ERR_CLEAN"
#define ERR_TIMEOUT				"ERR_TIMEOUT"
#define ERR_ABORTED				"ERR_ABORTED"
#define ERR_EXECUTE_PACK		"ERR_EXECUTE_PACK"
#define ERR_ALREADY_SETUP		"ERR_ALREADY_SETUP"
#define	VERIFY_DEPTH			10
#define	SSL_PORT				"443"

//#include "stdafx.h"
#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/x509v3.h>

int init_OpenSSL(void);
void seed_prng(void);
int fileExists(LPCSTR file, LPCSTR Id=NULL, LPCSTR dir=NULL);

#endif // !DOWNLOAD_INCLUDE
