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
#define VERSION_FILE			_T( "ver")
#define	LABEL_FILE				_T( "label")

#define NT4_WORKSTATION			_T( "NT 4.0 Workstation")
#define URL_SUFFIX				_T( "ocsinventory")
#define DEFAULT_SERVER_NAME		_T( "ocsinventory-ng")
#define PLATFORM_NAME			_T( "WINDOWS")
#define USER_AGENT				_T( "OCS-NG")
#define HTTP_HEADERS			_T( "Content-type: application/x-compress")
#define XML_HEADERS				_T( "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\r\n<!DOCTYPE REQUEST>\r\n")

#define NB_IP_MAX				5000
#define NB_IP_BY_SESSION		NB_IP_MAX
#define NB_FAST_IP_BY_SESSION	5

#endif
