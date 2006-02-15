#ifndef _DEFINES_H_
#define _DEFINES_H_
// Defines for OCS Inventory
#define VVERBOSE				FALSE
#define FORCE_DEBUG				FALSE

#define OCS_KEY					_T( "SOFTWARE\\OCS Inventory")
#define OCS_AGENT_KEY			_T( "OCS Inventory Agent")
#define OCS_MANAGER_KEY			_T( "OCS Inventory Manager")
#define OCS_DEVICE_ID_VALUE		_T( "DeviceID")

#define	OCS_IDENTIFICATION_FILE	_T( "ocsinventory.conf")
#define	OCS_ACCOUNTINFO_FILE	_T( "admininfo.conf")
#define OCS_CHECK_FILE			_T( "ocsinventory.dat")
#define VERSION_FILE			_T( "ver")
#define	LABEL_FILE				_T( "label")
#define EXE_NAME				_T( "ocsinventory.exe")

#define VER_D1					4
#define VER_D2					0
#define VER_D3					1
#define VER_D4				    3

#define NT4						_T( "NT 4.0")
#define URL_SUFFIX				_T( "/ocsinventory")
#define DEFAULT_SERVER_NAME		_T( "ocsinventory-ng")
#define PLATFORM_NAME			_T( "WINDOWS")
#define USER_AGENT				_T( "OCS-NG")
#define HTTP_HEADERS			_T( "Content-type: application/x-compress")
#define XML_HEADERS				_T( "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n<!DOCTYPE REQUEST>\r\n")

#define NB_IP_MAX				65534
#define DEFAULT_PORT			80
#define MAX_THREADS				300
#define MAX_FASTIP_THREADS		800

#endif
