// Document modified at : Friday, March 31, 2006 4:27:50 PM , by user : didier , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Pirerre LEMMET 2005
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

#ifndef _DEFINES_H_
#define _DEFINES_H_
// Defines for OCS Inventory
#define VVERBOSE				FALSE
#define FORCE_DEBUG				FALSE

#define OCS_KEY					_T( "SOFTWARE\\OCS Inventory")
#define OCS_AGENT_KEY			_T( "OCS Inventory Agent")
#define OCS_MANAGER_KEY			_T( "OCS Inventory Manager")
#define OCS_DEVICE_ID_VALUE		_T( "DeviceID")
#define	OCS_SERVICE				_T( "OCS_SERVICE")

#define	OCS_IDENTIFICATION_FILE	_T( "ocsinventory.conf")
#define	OCS_ACCOUNTINFO_FILE	_T( "admininfo.conf")
#define OCS_CHECK_FILE			_T( "ocsinventory.dat")
#define VERSION_FILE			_T( "ver")
#define	LABEL_FILE				_T( "label")
#define EXE_NAME				_T( "ocsinventory.exe")

#define VER_D1					4
#define VER_D2					0
#define VER_D3					3
#define VER_D4				    4

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

#define	SERVICE_INI				"service.ini"

#define CHECKSUM_COMPUTING_BUFFER 1024
/*
#define IDS_NTSERV_INSTALL_FAIL_OPEN_SCM "CNTService::Install, Failed call to open SCM, Error:%1"
    #define IDS_NTSERV_INSTALL_FAIL_LOCK_SCM "CNTService::Install, Failed call to lock SCM, Error:%1"
    #define IDS_NTSERV_INSTALL_FAIL_CREATESERVICE "CNTService::Install, Failed call to CreateService, Error:%1"
    #define IDS_NTSERV_INSTALL_FAIL_INSTALL_AS_EVENT_LOG_SOURCE "CNTService::Install, Failed call to install service as an event log source, Error:%1"
    #define IDS_NTSERV_UNINSTALL_FAIL_OPEN_SCM "CNTService::Uninstall, Failed call to open SCM, Error:%1"
    #define IDS_NTSERV_UNINSTALL_FAIL_OPEN_SERVICE "CNTService::Uninstall, Failed call to OpenService, Error:%1"
    #define IDS_NTSERV_UNINSTALL_FAIL_WAIT_FOR_STOP "CNTService::Uninstall, Failed call to WaitForStop, Error:%1"
    #define IDS_NTSERV_UNINSTALL_FAIL_DELETE_SERVICE "CNTService::Uninstall, Failed call to DeleteService, Error:%1"
    #define IDS_NTSERV_UNINSTALL_FAIL_UNINSTALL_EVENTLOG_SOURCE "CNTService::Uninstall, Failed call to remove service as an event log source, Error:%1"
    #define IDS_NTSERV_FAIL_START_SERVICE "Failed to start the service, Error:%1"
    #define IDS_NTSERV_FAIL_STOP_SERVICE "Failed to stop the service, Error:%1"
    #define IDS_NTSERV_FAIL_CONTINUE_SERVICE "Failed to continue the service, Error:%1"
    #define IDS_NTSERV_FAIL_PAUSE_SERVICE "Failed to pause the service, Error:%1"
    #define IDS_NTSERV_FAIL_START_SERVICE5 "Failed to start the service, Error:%1"
    #define IDS_NTSERV_VERBOSE_ERROR_STRING "%1, %2"
    #define IDS_NTSERV_UNINSTALL_FAIL_STOP "CNTService::Uninstall, Failed to stop service, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_OPEN_SCM "CNTService::SetServiceToStatus, Failed call to open SCM, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_OPEN_SERVICE "CNTService::SetServiceToStatus, Failed call to OpenService, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_START "CNTService::SetServiceToStatus, Failed to start the service, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_CONTINUE "CNTService::SetServiceToStatus, Failed to continue the service, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_PAUSE "CNTService::SetServiceToStatus, Failed to pause the service, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_STOP "CNTService::SetServiceToStatus, Failed to stop the service, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_WAITFORCHANGE "CNTService::SetServiceToStatus, Failed to wait for the service to change state, Error:%1"
    #define IDS_NTSERV_SETSERVICETOSTATUS_FAIL_QUERYSTATUS "CNTService::SetServiceToStatus, Failed to check the service status, Error:%1"
*/
 #endif

