// Document modified at : Tuesday, March 28, 2006 12:50:25 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Registry.cpp: implementation of the CRegistry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SysInfo.h"
#include "../include/_common/utils.h"

// Defines for retrieving Windows registration
#define WIN_REGISTRATION_KEY					_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion")
#define WIN_REGISTRATION_PRODUCT_ID_VALUE		_T( "ProductId")
#define WIN_REGISTRATION_COMPANY_VALUE			_T( "RegisteredOrganization")
#define WIN_REGISTRATION_OWNER_VALUE			_T( "RegisteredOwner")

#define NT_REGISTRATION_KEY						_T( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion")
#define NT_REGISTRATION_PRODUCT_ID_VALUE		_T( "ProductId")
#define NT_REGISTRATION_COMPANY_VALUE			_T( "RegisteredOrganization")
#define NT_REGISTRATION_OWNER_VALUE				_T( "RegisteredOwner")

// Defines for retrieving logon username from 9X/Me registry
#define WIN_LOGON_USER_KEY						_T( "SYSTEM\\CurrentControlSet\\Control")
#define WIN_LOGON_USER_VALUE					_T( "Current User")

#define NT_LOGON_USER_KEY						_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer")
#define NT_LOGON_USER_VALUE						_T( "Logon User Name")

// Defines for retrieving last user who'd been logged in
#define NT_LASTLOGGEDUSER_USER_KEY				_T( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon")
#define NT_LASTLOGGEDUSER_USER_VALUE			_T( "DefaultUserName")

// Defines for retrieving computer description from 9X/Me registry
#define WIN_COMPUTER_DESCRIPTION_KEY			_T( "SYSTEM\\CurrentControlSet\\Services\\VxD\\VNETSUP")
#define WIN_COMPUTER_DESCRIPTION_VALUE			_T( "Comment")

// Defines for retrieving computer description from NT registry
#define NT_COMPUTER_DESCRIPTION_KEY				_T( "SYSTEM\\CurrentControlSet\\Services\\lanmanserver\\Parameters")
#define NT_COMPUTER_DESCRIPTION_VALUE			_T( "srvcomment")

// Defines for retrieving domain or workgroup from 9X/Me registry
#define WIN_DOMAIN_KEY							_T( "Security\\Provider")
#define WIN_DOMAIN_VALUE						_T( "Container")
#define WIN_WORKGROUP_KEY						_T( "SYSTEM\\CurrentControlSet\\Services\\VxD\\VNETSUP")
#define WIN_WORKGROUP_VALUE						_T( "Workgroup")

// Defines for retrieving domain or workgroup from NT registry
#define NT_DOMAIN_KEY							_T( "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon")
#define NT_DOMAIN_VALUE							_T( "DefaultDomainName")
#define NT_WORKGROUP_KEY						_T( "SYSTEM\\CurrentControlSet\\Services\\VxD\\VNETSUP")
#define NT_WORKGROUP_VALUE						_T( "Workgroup")

// Defines for retrieving BIOS from 9X/Me registry
#define WIN_BIOS_KEY							_T( "ENUM\\Root\\*PNP0C01\\0000")
#define WIN_SYSTEM_MANUFACTURER_VALUE			_T( "Mfg")
#define WIN_SYSTEM_MODEL_VALUE					_T( "Model")
#define WIN_SYSTEM_SERIAL_VALUE					_T( "Serial")
#define WIN_BIOS_MACHINE_TYPE_VALUE				_T( "MachineType")
#define WIN_BIOS_MANUFACTURER_VALUE				_T( "BIOSName")
#define WIN_BIOS_VERSION_VALUE					_T( "BIOSVersion")
#define WIN_BIOS_DATE_VALUE						_T( "BIOSDate")

// Defines for retrieving BIOS from NT registry
#define NT_BIOS_KEY								_T( "HARDWARE\\Description\\System")
#define NT_SYSTEM_MANUFACTURER_VALUE			_T( "Manufacturer")
#define NT_SYSTEM_MODEL_VALUE					_T( "Model")
#define NT_SYSTEM_SERIAL_VALUE					_T( "Serial")
#define NT_BIOS_MACHINE_TYPE_VALUE				_T( "Identifier")
#define NT_BIOS_MANUFACTURER_VALUE				_T( "BIOSName")
#define NT_BIOS_VERSION_VALUE					_T( "SystemBiosVersion")
#define NT_BIOS_DATE_VALUE						_T( "SystemBiosDate")

// Defines for retrieving BIOS from Windows Update 9X/Me registry
#define WIN_WU_KEY								_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\OemInfo")
#define WIN_WU_SYSTEM_MANUFACTURER_VALUE		_T( "SmbOem")
#define WIN_WU_SYSTEM_MODEL_VALUE				_T( "SmbProduct")
#define WIN_WU_ACPI_MANUFACTURER_VALUE			_T( "AcpiOem")
#define WIN_WU_ACPI_MODEL_VALUE					_T( "AcpiProduct")

// Defines for retrieving BIOS from Windows Update NT registry
#define NT_WU_KEY								_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\OemInfo")
#define NT_WU_SYSTEM_MANUFACTURER_VALUE			_T( "WbemOem")
#define NT_WU_SYSTEM_MODEL_VALUE				_T( "WbemProduct")
#define NT_WU_ACPI_MANUFACTURER_VALUE			_T( "AcpiOem")
#define NT_WU_ACPI_MODEL_VALUE					_T( "AcpiProduct")

// Defines for retrieving processors from 9X/Me registry
#define WIN_PROCESSOR_KEY						_T( "HARDWARE\\Description\\System\\CentralProcessor")
#define WIN_PROCESSOR_NAME_VALUE				_T( "Identifier")
#define WIN_PROCESSOR_SPEED_VALUE				_T( "~MHz")

// Defines for retrieving processors from NT registry
#define NT_PROCESSOR_KEY						_T( "HARDWARE\\Description\\System\\CentralProcessor")
#define NT_PROCESSOR_NAME_VALUE					_T( "Identifier")
#define NT_PROCESSOR_NAME_STRING_VALUE			_T( "ProcessorNameString")
#define NT_PROCESSOR_SPEED_VALUE				_T( "~MHz")

// Defines for retrieving Display from NT registry
#define NT_ENUM_KEY								_T( "SYSTEM\\CurrentControlSet\\Enum")
#define NT_ENUM_CLASS_VALUE						_T( "Class")
#define NT_ENUM_DISPLAY_VALUE					_T( "Display")
#define NT_ENUM_SERVICE_VALUE					_T( "Service")
#define NT_SERVICES_KEY							_T( "SYSTEM\\CurrentControlSet\\Services")
#define NT_SERVICE_DEVICE_KEY					_T( "Device0")
#define NT_ADAPTER_NAME_VALUE					_T( "HardwareInformation.AdapterString")
#define NT_ADAPTER_CHIP_VALUE					_T( "HardwareInformation.ChipType")
#define NT_ADAPTER_MEMORY_VALUE					_T( "HardwareInformation.MemorySize")

// Defines for retrieving Display from 9X/Me registry
#define WIN_DISPLAY_KEY							_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Display")
#define WIN_ADAPTER_NAME_VALUE					_T( "DriverDesc")
#define WIN_DEVICE_INFO_KEY						_T( "INFO")
#define WIN_ADAPTER_CHIP_VALUE					_T( "ChipType")
#define WIN_ADAPTER_MEMORY_VALUE				_T( "VideoMemory")

// Defines for retrieving Display from XP registry
#define XP_ENUM_KEY								_T( "SYSTEM\\CurrentControlSet\\Control\\Video")
#define XP_ADAPTER_NAME_VALUE					_T( "HardwareInformation.AdapterString")
#define XP_ADAPTER_CHIP_VALUE					_T( "HardwareInformation.ChipType")
#define XP_ADAPTER_MEMORY_VALUE					_T( "HardwareInformation.MemorySize")

// Defines for retrieving Printers from registry
#define PRINTERS_ENUM_KEY						_T( "SYSTEM\\CurrentControlSet\\Control\\Print\\Printers")
#define PRINTER_NAME_VALUE						_T( "Name")
#define PRINTER_DRIVER_VALUE					_T( "Printer Driver")
#define PRINTER_PORT_VALUE						_T( "Port")

// Defines for retrieving Monitors from 9X/Me registry
#define WIN_MONITOR_KEY							_T( "ENUM\\Monitor\\DEFAULT_MONITOR")
#define WIN_MONITOR_MANUFACTURER_VALUE			_T( "Mfg")
#define WIN_MONITOR_DESCRIPTION_VALUE			_T( "DeviceDesc")
#define WIN_MONITOR_CAPTION_VALUE				_T( "DeviceDesc")
#define WIN_MONITOR_TYPE_VALUE					_T( "DeviceDesc")

// Defines for retrieving Monitors from NT registry
#define NT_MONITOR_KEY							_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96E-E325-11CE-BFC1-08002BE10318}")
#define NT_MONITOR_MANUFACTURER_VALUE			_T( "ProviderName")
#define NT_MONITOR_DESCRIPTION_VALUE			_T( "DriverDesc")
#define NT_MONITOR_CAPTION_VALUE				_T( "DriverDesc")
#define NT_MONITOR_TYPE_VALUE					_T( "DriverDesc")

// Defines for retrieving input devices from 9X/Me registry
#define WIN_INPUT_KEYBOARD_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Keyboard")
#define WIN_INPUT_KEYBOARD_MANUFACTURER_VALUE	_T( "ProviderName")
#define WIN_INPUT_KEYBOARD_CAPTION_VALUE		_T( "DriverDesc")
#define WIN_INPUT_KEYBOARD_DESCRIPTION_VALUE	_T( "DriverDesc")
#define WIN_INPUT_KEYBOARD_TYPE_VALUE			_T( "")
#define WIN_INPUT_KEYBOARD_INTERFACE_VALUE		_T( "")

#define WIN_INPUT_POINTING_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Mouse")
#define WIN_INPUT_POINTING_MANUFACTURER_VALUE	_T( "ProviderName")
#define WIN_INPUT_POINTING_CAPTION_VALUE		_T( "DriverDesc")
#define WIN_INPUT_POINTING_DESCRIPTION_VALUE	_T( "DriverDesc")
#define WIN_INPUT_POINTING_TYPE_VALUE			_T( "")
#define WIN_INPUT_POINTING_INTERFACE_VALUE		_T( "")

// Defines for retrieving input devices from NT registry
#define NT_INPUT_KEYBOARD_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96B-E325-11CE-BFC1-08002BE10318}")
#define NT_INPUT_KEYBOARD_MANUFACTURER_VALUE	_T( "ProviderName")
#define NT_INPUT_KEYBOARD_CAPTION_VALUE			_T( "DriverDesc")
#define NT_INPUT_KEYBOARD_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_INPUT_KEYBOARD_TYPE_VALUE			_T( "")
#define NT_INPUT_KEYBOARD_INTERFACE_VALUE		_T( "LocationInformationOverride")

#define NT_INPUT_POINTING_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96F-E325-11CE-BFC1-08002BE10318}")
#define NT_INPUT_POINTING_MANUFACTURER_VALUE	_T( "ProviderName")
#define NT_INPUT_POINTING_CAPTION_VALUE			_T( "DriverDesc")
#define NT_INPUT_POINTING_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_INPUT_POINTING_TYPE_VALUE			_T( "")
#define NT_INPUT_POINTING_INTERFACE_VALUE		_T( "LocationInformationOverride")

// Defines for retrieving system ports from 9X/Me registry
#define WIN_SYSTEM_PORT_CLASS_PARALLEL			0
#define WIN_SYSTEM_PORT_CLASS_SERIAL			1
#define WIN_SYSTEM_PORT_KEY						_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Ports")
#define WIN_SYSTEM_PORT_NAME_VALUE				_T( "DriverDesc")
#define WIN_SYSTEM_PORT_CAPTION_VALUE			_T( "DriverDesc")
#define WIN_SYSTEM_PORT_DESCRIPTION_VALUE		_T( "DriverDesc")
#define WIN_SYSTEM_PORT_TYPE_VALUE				_T( "PortSubClass")

// Defines for retrieving system ports from NT registry
#define NT_SYSTEM_PORT_CLASS_PARALLEL			0
#define NT_SYSTEM_PORT_CLASS_SERIAL				1
#define NT_SYSTEM_PORT_KEY						_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E978-E325-11CE-BFC1-08002BE10318}")
#define NT_SYSTEM_PORT_NAME_VALUE				_T( "DriverDesc")
#define NT_SYSTEM_PORT_CAPTION_VALUE			_T( "DriverDesc")
#define NT_SYSTEM_PORT_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_SYSTEM_PORT_TYPE_VALUE				_T( "PortSubClass")

// Defines for retrieving system controlers from 9X/Me registry
#define WIN_CONTROLER_FLOPPY_KEY				_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\fdc")
#define WIN_CONTROLER_FLOPPY_MANUFACTURER_VALUE _T( "ProviderName")
#define WIN_CONTROLER_FLOPPY_NAME_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_FLOPPY_CAPTION_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_FLOPPY_DESCRIPTION_VALUE	_T( "DriverDesc")
#define WIN_CONTROLER_FLOPPY_VERSION_VALUE		_T( "DriverDate")

#define WIN_CONTROLER_IDE_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\hdc")
#define WIN_CONTROLER_IDE_MANUFACTURER_VALUE	_T( "ProviderName")
#define WIN_CONTROLER_IDE_NAME_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_IDE_CAPTION_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_IDE_DESCRIPTION_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_IDE_VERSION_VALUE			_T( "DriverDate")

#define WIN_CONTROLER_SCSI_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\SCSIAdapter")
#define WIN_CONTROLER_SCSI_MANUFACTURER_VALUE	_T( "ProviderName")
#define WIN_CONTROLER_SCSI_NAME_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_SCSI_CAPTION_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_SCSI_DESCRIPTION_VALUE	_T( "DriverDesc")
#define WIN_CONTROLER_SCSI_VERSION_VALUE		_T( "DriverDate")

#define WIN_CONTROLER_INFRARED_KEY				_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Infrared")
#define WIN_CONTROLER_INFRARED_MANUFACTURER_VALUE _T( "ProviderName")
#define WIN_CONTROLER_INFRARED_NAME_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_INFRARED_CAPTION_VALUE	_T( "DriverDesc")
#define WIN_CONTROLER_INFRARED_DESCRIPTION_VALUE _T( "DriverDesc")
#define WIN_CONTROLER_INFRARED_VERSION_VALUE	_T( "DriverDate")

#define WIN_CONTROLER_USB_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\USB")
#define WIN_CONTROLER_USB_MANUFACTURER_VALUE	_T( "ProviderName")
#define WIN_CONTROLER_USB_NAME_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_USB_CAPTION_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_USB_DESCRIPTION_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_USB_VERSION_VALUE			_T( "DriverDate")

#define WIN_CONTROLER_IEEE1394_KEY				_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\1394")
#define WIN_CONTROLER_IEEE1394_MANUFACTURER_VALUE _T( "ProviderName")
#define WIN_CONTROLER_IEEE1394_NAME_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_IEEE1394_CAPTION_VALUE	_T( "DriverDesc")
#define WIN_CONTROLER_IEEE1394_DESCRIPTION_VALUE _T( "DriverDesc")
#define WIN_CONTROLER_IEEE1394_VERSION_VALUE	_T( "DriverDate")

#define WIN_CONTROLER_PCMCIA_KEY				_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\PCMCIA")
#define WIN_CONTROLER_PCMCIA_MANUFACTURER_VALUE _T( "ProviderName")
#define WIN_CONTROLER_PCMCIA_NAME_VALUE			_T( "DriverDesc")
#define WIN_CONTROLER_PCMCIA_CAPTION_VALUE		_T( "DriverDesc")
#define WIN_CONTROLER_PCMCIA_DESCRIPTION_VALUE	_T( "DriverDesc")
#define WIN_CONTROLER_PCMCIA_VERSION_VALUE		_T( "DriverDate")

// Defines for retrieving system controlers from NT registry
#define NT_CONTROLER_FLOPPY_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E969-E325-11CE-BFC1-08002BE10318}")
#define NT_CONTROLER_FLOPPY_MANUFACTURER_VALUE	_T( "ProviderName")
#define NT_CONTROLER_FLOPPY_NAME_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_FLOPPY_CAPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_FLOPPY_DESCRIPTION_VALUE	_T( "DriverDesc")
#define NT_CONTROLER_FLOPPY_VERSION_VALUE		_T( "DriverVersion")

#define NT_CONTROLER_IDE_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96A-E325-11CE-BFC1-08002BE10318}")
#define NT_CONTROLER_IDE_MANUFACTURER_VALUE		_T( "ProviderName")
#define NT_CONTROLER_IDE_NAME_VALUE				_T( "DriverDesc")
#define NT_CONTROLER_IDE_CAPTION_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_IDE_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_IDE_VERSION_VALUE			_T( "DriverVersion")

#define NT_CONTROLER_SCSI_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E97B-E325-11CE-BFC1-08002BE10318}")
#define NT_CONTROLER_SCSI_MANUFACTURER_VALUE	_T( "ProviderName")
#define NT_CONTROLER_SCSI_NAME_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_SCSI_CAPTION_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_SCSI_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_SCSI_VERSION_VALUE			_T( "DriverVersion")

#define NT_CONTROLER_INFRARED_KEY				_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{6BDD1FC5-810F-11D0-BEC7-08002BE2092F}")
#define NT_CONTROLER_INFRARED_MANUFACTURER_VALUE _T( "ProviderName")
#define NT_CONTROLER_INFRARED_NAME_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_INFRARED_CAPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_INFRARED_DESCRIPTION_VALUE	_T( "DriverDesc")
#define NT_CONTROLER_INFRARED_VERSION_VALUE		_T( "DriverVersion")
#define NT_CONTROLER_INFRARED_CONTROLER_VALUE	_T( "Controller")

#define NT_CONTROLER_USB_KEY					_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{36FC9E60-C465-11CF-8056-444553540000}")
#define NT_CONTROLER_USB_MANUFACTURER_VALUE		_T( "ProviderName")
#define NT_CONTROLER_USB_NAME_VALUE				_T( "DriverDesc")
#define NT_CONTROLER_USB_CAPTION_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_USB_DESCRIPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_USB_VERSION_VALUE			_T( "DriverVersion")
#define NT_CONTROLER_USB_CONTROLER_VALUE		_T( "Controller")

#define NT_CONTROLER_IEEE1394_KEY				_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{6BDD1FC1-810F-11D0-BEC7-08002BE2092F}")
#define NT_CONTROLER_IEEE1394_MANUFACTURER_VALUE _T( "ProviderName")
#define NT_CONTROLER_IEEE1394_NAME_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_IEEE1394_CAPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_IEEE1394_DESCRIPTION_VALUE _T( "DriverDesc")
#define NT_CONTROLER_IEEE1394_VERSION_VALUE		_T( "DriverVersion")

#define NT_CONTROLER_PCMCIA_KEY					_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\PCMCIA")
#define NT_CONTROLER_PCMCIA_MANUFACTURER_VALUE	_T( "ProviderName")
#define NT_CONTROLER_PCMCIA_NAME_VALUE			_T( "DriverDesc")
#define NT_CONTROLER_PCMCIA_CAPTION_VALUE		_T( "DriverDesc")
#define NT_CONTROLER_PCMCIA_DESCRIPTION_VALUE	_T( "DriverDesc")
#define NT_CONTROLER_PCMCIA_VERSION_VALUE		_T( "DriverVersion")

// Defines for retrieving storage peripherals from 9X/Me registry
#define WIN_STORAGE_FLOPPY_KEY					_T( "ENUM\\FLOP")
#define WIN_STORAGE_FLOPPY_MANUFACTURER_VALUE	_T( "Manufacturer")
#define WIN_STORAGE_FLOPPY_MODEL_VALUE			_T( "ProductId")
#define WIN_STORAGE_FLOPPY_NAME_VALUE			_T( "DeviceDesc")
#define WIN_STORAGE_FLOPPY_DESCRIPTION_VALUE	_T( "Mfg")
#define WIN_STORAGE_FLOPPY_TYPE_VALUE			_T( "Class")

#define WIN_STORAGE_DISK_KEY					_T( "ENUM\\ESDI")
#define WIN_STORAGE_DISK_MANUFACTURER_VALUE		_T( "Manufacturer")
#define WIN_STORAGE_DISK_MODEL_VALUE			_T( "ProductId")
#define WIN_STORAGE_DISK_NAME_VALUE				_T( "DeviceDesc")
#define WIN_STORAGE_DISK_DESCRIPTION_VALUE		_T( "Mfg")
#define WIN_STORAGE_DISK_TYPE_VALUE				_T( "Class")

#define WIN_STORAGE_OTHER_KEY					_T( "ENUM\\SCSI")
#define WIN_STORAGE_OTHER_MANUFACTURER_VALUE	_T( "Manufacturer")
#define WIN_STORAGE_OTHER_MODEL_VALUE			_T( "ProductId")
#define WIN_STORAGE_OTHER_NAME_VALUE			_T( "DeviceDesc")
#define WIN_STORAGE_OTHER_DESCRIPTION_VALUE		_T( "Mfg")
#define WIN_STORAGE_OTHER_TYPE_VALUE			_T( "Class")

// Defines for retrieving storage peripherals from NT registry
#define NT_STORAGE_FLOPPY_KEY					_T( "SYSTEM\\CurrentControlSet\\Enum\\FDC")
#define NT_STORAGE_FLOPPY_MANUFACTURER_VALUE	_T( "Mfg")
#define NT_STORAGE_FLOPPY_MODEL_VALUE			_T( "FriendlyName")
#define NT_STORAGE_FLOPPY_NAME_VALUE			_T( "DeviceDesc")
#define NT_STORAGE_FLOPPY_DESCRIPTION_VALUE		_T( "HardwareId")
#define NT_STORAGE_FLOPPY_TYPE_VALUE			_T( "Class")

#define NT_STORAGE_OTHER_KEY					_T( "HARDWARE\\DEVICEMAP\\Scsi")
#define NT_STORAGE_OTHER_MANUFACTURER_VALUE		_T( "Mfg")
#define NT_STORAGE_OTHER_MODEL_VALUE			_T( "Identifier")
#define NT_STORAGE_OTHER_NAME_VALUE				_T( "DeviceName")
#define NT_STORAGE_OTHER_DESCRIPTION_VALUE		_T( "Identifier")
#define NT_STORAGE_OTHER_TYPE_VALUE				_T( "Type")

// Defines for retrieving Sound devices from 9X/Me registry
#define WIN_SOUND_KEY							_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\MEDIA")
#define WIN_SOUND_MANUFACTURER_VALUE			_T( "ProviderName")
#define WIN_SOUND_NAME_VALUE					_T( "DriverDesc")
#define WIN_SOUND_DESCRIPTION_VALUE				_T( "DriverDesc")
#define WIN_SOUND_DRIVER						_T( "Drivers")
#define WIN_SOUND_DRIVER_CLASS					_T( "SubClasses")

// Defines for retrieving Sound devices from NT registry
#define NT_SOUND_KEY							_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96C-E325-11CE-BFC1-08002BE10318}")
#define NT_SOUND_MANUFACTURER_VALUE				_T( "ProviderName")
#define NT_SOUND_NAME_VALUE						_T( "DriverDesc")
#define NT_SOUND_DESCRIPTION_VALUE				_T( "DriverDesc")
#define NT_SOUND_DRIVER							_T( "Drivers")
#define NT_SOUND_DRIVER_CLASS					_T( "SubClasses")

// Defines for retrieving Modems from 9X/Me registry
#define WIN_MODEM_KEY							_T( "SYSTEM\\CurrentControlSet\\Services\\Class\\Modem")
#define WIN_MODEM_MODEL_VALUE					_T( "Model")
#define WIN_MODEM_NAME_VALUE					_T( "DriverDesc")
#define WIN_MODEM_DESCRIPTION_VALUE				_T( "DriverDesc")
#define WIN_MODEM_TYPE_VALUE					_T( "AttachedTo")

// Defines for retrieving Modems from NT registry
#define NT_MODEM_KEY							_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{4D36E96D-E325-11CE-BFC1-08002BE10318}")
#define NT_MODEM_MODEL_VALUE					_T( "Model")
#define NT_MODEM_NAME_VALUE						_T( "DriverDesc")
#define NT_MODEM_DESCRIPTION_VALUE				_T( "DriverDesc")
#define NT_MODEM_TYPE_VALUE						_T( "AttachedTo")

// Defines for retrieving if it is notbook from 9X/Me registry
#define WIN_NOTEBOOK_KEY						_T( "ENUM\\VPOWERD\\BATTERY")

// Defines for retrieving if it is notbook from NT registry
#define NT_NOTEBOOK_KEY							_T( "SYSTEM\\CurrentControlSet\\Control\\Class\\{72631E54-78A4-11D0-BCF7-00AA00B7B32A}")

// Defines for retrieving installed apps from 9X/Me registry
#define WIN_APPS_KEY							_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define WIN_APPS_VENDOR_VALUE					_T( "Publisher")
#define WIN_APPS_NAME_VALUE						_T( "DisplayName")
#define WIN_APPS_VERSION_VALUE					_T( "DisplayVersion")
#define WIN_APPS_FOLDER_VALUE					_T( "InstallLocation")
#define WIN_APPS_COMMENTS_VALUE					_T( "Comments")
#define WIN_APPS_UNINSTALL_VALUE				_T( "UninstallString")
#define WIN_APPS_QUIETUNINSTALL_VALUE			_T( "QuietUninstallString")
#define WIN_APPS_MODIFY_VALUE					_T( "ModifyPath")
#define WIN_APPS_LANGUAGE_VALUE					_T( "Language")

// Defines for retrieving installed apps from 9X/Me registry
#define NT_APPS_KEY								_T( "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define NT_APPS_VENDOR_VALUE					_T( "Publisher")
#define NT_APPS_NAME_VALUE						_T( "DisplayName")
#define NT_APPS_VERSION_VALUE					_T( "DisplayVersion")
#define NT_APPS_FOLDER_VALUE					_T( "InstallLocation")
#define NT_APPS_COMMENTS_VALUE					_T( "Comments")
#define NT_APPS_UNINSTALL_VALUE					_T( "UninstallString")
#define NT_APPS_QUIETUNINSTALL_VALUE			_T( "QuietUninstallString")
#define NT_APPS_MODIFY_VALUE					_T( "ModifyPath")
#define NT_APPS_LANGUAGE_VALUE					_T( "Language")

// Defines for validating detected components under HKEY_DYN_DATA for 9X/Me
#define WIN_CONFIG_MANAGER_KEY					_T( "Config Manager\\Enum")
#define WIN_CONFIG_MANAGER_COMPONENT_VALUE		_T( "HardWareKey")
#define WIN_CONFIG_MANAGER_STATUS_VALUE			_T( "Status")
#define WIN_CONFIG_MANAGER_STATUS_OK

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRegistry::CRegistry()
{
	OSVERSIONINFO	osVersion;

	osVersion.dwOSVersionInfoSize = sizeof( OSVERSIONINFO);
	if (GetVersionEx( &osVersion))
	{
		m_dwPlatformId = osVersion.dwPlatformId;
		m_bIsXP = (osVersion.dwPlatformId == VER_PLATFORM_WIN32_NT) &&
				  (((osVersion.dwMajorVersion == 5) && (osVersion.dwMinorVersion >= 1)) ||
				  (osVersion.dwMajorVersion > 5));
	}
	else
	{
		// Failed so assume NT based, but not XP or later
		m_dwPlatformId = VER_PLATFORM_WIN32_NT;
		m_bIsXP = FALSE;
	}
	m_hKey = NULL;
	m_bRemoteRegistry = FALSE;
}

CRegistry::~CRegistry()
{
	Disconnect();
}

LPCTSTR CRegistry::ParseMultiSZ(LPCTSTR lpstrCurrent)
{
	static LPCTSTR szRemainder = NULL;
	LPCTSTR szReturn = NULL;
	
	if (lpstrCurrent)
	{         
		szRemainder = lpstrCurrent;
    }
	else
		if (szRemainder == NULL)
		{
			return NULL;
	    }
	if (*szRemainder)
	{
		szReturn = szRemainder;
		while (*++szRemainder);
		szRemainder++;     
	}
	return szReturn;
}

BOOL CRegistry::Connect(LPCTSTR lpstrDevice)
{
	CString	csDevice;

	// Do not connect if already connected
	if (m_hKey != NULL)
		return TRUE;
	AddLog( _T( "Registry Connect: Trying to connect to HKEY_LOCAL_MACHINE on device <%s>..."), lpstrDevice == NULL ? _T( "Localhost") : lpstrDevice);
	if (lpstrDevice != NULL)
	{
		// Connect to remote registry
		csDevice.Format( _T( "\\\\%s"), lpstrDevice);
		if (RegConnectRegistry( csDevice, HKEY_LOCAL_MACHINE, &m_hKey) != ERROR_SUCCESS)
		{
			AddLog( _T( "Failed in call to <RegConnectRegistry> function for %s\\HKLM !\n"),
					csDevice);
			return FALSE;
		}
		m_bRemoteRegistry = TRUE;
		AddLog( "OK.\n");
		return TRUE;
	}
	// connect to local registry
	m_hKey = HKEY_LOCAL_MACHINE;
	AddLog( "OK.\n");
	return TRUE;
}

BOOL CRegistry::Disconnect()
{
	if (m_bRemoteRegistry)
	{
		AddLog( _T( "Registry Disconnect: Disconnected from HKEY_LOCAL_MACHINE.\n"));
		CUtils::trace("CREGISTRY_DISCONNECT", AfxGetApp()->m_lpCmdLine);
		RegCloseKey( m_hKey);
		CUtils::trace("CREGISTRY_DISCONNECTED", AfxGetApp()->m_lpCmdLine);
	}
	m_hKey = NULL;
	m_bRemoteRegistry = FALSE;
	return TRUE;
}

LPCTSTR CRegistry::GetDeviceID()
{
	static TCHAR szDeviceID[256];
	CString		 csKey;
	HKEY		 hKey = NULL;

	_stprintf( szDeviceID, _T( ""));
	AddLog( _T( "Registry GetDeviceID..."));
	csKey.Format( _T( "%s\\%s"), OCS_KEY, OCS_AGENT_KEY);
	LONG lResult = RegOpenKeyEx( m_hKey, csKey, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				csKey);
		return NULL;
	}

	// Get device id.
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	lResult = RegQueryValueEx( hKey, OCS_DEVICE_ID_VALUE, NULL, &dwType, (LPBYTE) szDeviceID, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				csKey,
				OCS_DEVICE_ID_VALUE);
		RegCloseKey( hKey);
		return NULL;
	}
	RegCloseKey( hKey);
	szDeviceID[dwSize]=0;
	AddLog( _T( "OK (%s).\n"), szDeviceID);
	return szDeviceID;
}

BOOL CRegistry::SetDeviceID( LPCTSTR lpstrDeviceID)
{
	CString		 csKey;
	HKEY		 hKey = NULL;
	DWORD		 dwResult;

	AddLog( _T( "Registry SetDeviceID..."));
	csKey.Format( _T( "%s\\%s"), OCS_KEY, OCS_AGENT_KEY);
	LONG lResult = RegCreateKeyEx( m_hKey, csKey, 0, _T( ""), REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, &dwResult);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegCreateKeyEx> function for HKLM\\%s !\n"),
				csKey);
		return FALSE;
	}

	// Set device id.
	DWORD dwType = REG_SZ;
	DWORD dwSize = _tcslen( lpstrDeviceID);
	lResult = RegSetValueEx( hKey, OCS_DEVICE_ID_VALUE, 0, dwType, (LPBYTE) lpstrDeviceID, dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegSetValueEx> function for HKLM\\%s\\%s !\n"),
				csKey,
				OCS_DEVICE_ID_VALUE);
		RegCloseKey( hKey);
		return FALSE;
	}
	RegCloseKey( hKey);
	AddLog( _T( "OK (%s).\n"), lpstrDeviceID);
	return TRUE;
}

BOOL CRegistry::GetBiosInfo( CBios *pMyBios)
{
	// Try to get BIOS Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetBiosInfo9X( pMyBios);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetBiosInfoNT( pMyBios);
	default:
		// Unknown
		pMyBios->Set( NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE
					  NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE);
		AddLog( _T( "Registry GetBiosInfo...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetBiosInfo9X( CBios *pMyBios)
{
	HKEY	hKey = NULL;
	TCHAR	szValue[256];
	LONG	lResult;
	DWORD	dwType;
	DWORD	dwSize;
	BOOL	bManufacturer = FALSE,
			bModel = FALSE;

	AddLog( _T( "Registry 9X/Me GetBiosInfo...\n"));
	// Windows 9X/Me
	lResult = RegOpenKeyEx( m_hKey, WIN_BIOS_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get System manufacturer
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_SYSTEM_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_SYSTEM_MANUFACTURER_VALUE);
			pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
			bManufacturer = FALSE;;
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemManufacturer( szValue);
			bManufacturer = TRUE;
		}
		// Get System model
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_SYSTEM_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_SYSTEM_MODEL_VALUE);
			pMyBios->SetSystemModel( NOT_AVAILABLE);
			bModel = FALSE;
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemModel( szValue);
			bModel = TRUE;
		}
		// Get System serial number
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_SYSTEM_SERIAL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_SYSTEM_SERIAL_VALUE);
			pMyBios->SetSystemSerialNumber( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemSerialNumber( szValue);
		}
		// Get BIOS manufacturer
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_BIOS_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_BIOS_MANUFACTURER_VALUE);
			pMyBios->SetBiosManufacturer( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetBiosManufacturer( szValue);
		}
		// Get BIOS version
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_BIOS_VERSION_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_BIOS_VERSION_VALUE);
			pMyBios->SetBiosVersion( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetBiosVersion( szValue);
		}
		// Get BIOS date
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_BIOS_DATE_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_BIOS_DATE_VALUE);
			pMyBios->SetBiosDate( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetBiosDate( szValue);
		}
		// Get machine type
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, WIN_BIOS_MACHINE_TYPE_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					WIN_BIOS_KEY, WIN_BIOS_MACHINE_TYPE_VALUE);
			pMyBios->SetMachineType( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetMachineType( szValue);
		}
		RegCloseKey( hKey);
	}
	else
	{
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_BIOS_KEY);
		pMyBios->Set( NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE
					  NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE);
	}
	if ((!bManufacturer) || (!bModel))
	{
		// Try to get System Manufacturer and Model from Windows Update Registry key
		lResult = RegOpenKeyEx( m_hKey, WIN_WU_KEY, 0, KEY_READ, &hKey);
		if (lResult != ERROR_SUCCESS)
		{
			// Get System manufacturer
			if (!bManufacturer)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, WIN_WU_SYSTEM_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							WIN_WU_KEY, WIN_WU_SYSTEM_MANUFACTURER_VALUE);
					pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
					bManufacturer = FALSE;;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemManufacturer( szValue);
					if (_tcsicmp( szValue, _T( "System Manufacturer")) == 0)
						// Default WU value when not available
						bManufacturer = FALSE;
					else
						// Not default value
						bManufacturer = TRUE;
				}
			}
			// Get System model
			if (!bModel)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, WIN_WU_SYSTEM_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							WIN_WU_KEY, WIN_WU_SYSTEM_MODEL_VALUE);
					pMyBios->SetSystemModel( NOT_AVAILABLE);
					bModel = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemModel( szValue);
					if (_tcsicmp( szValue, _T( "System Name")) == 0)
						// Default WU value when not available
						bModel = FALSE;
					else
						// Not default value
						bModel = TRUE;
				}
			}
			// Get ACPI manufacturer
			if (!bManufacturer)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, WIN_WU_ACPI_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							WIN_WU_KEY, WIN_WU_ACPI_MANUFACTURER_VALUE);
					pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
					bManufacturer = FALSE;;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemManufacturer( szValue);
					bManufacturer = TRUE;
				}
			}
			// Get ACPI model
			if (!bModel)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, WIN_WU_ACPI_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							WIN_WU_KEY, WIN_WU_ACPI_MODEL_VALUE);
					pMyBios->SetSystemModel( NOT_AVAILABLE);
					bModel = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemModel( szValue);
					bModel = TRUE;
				}
			}
			RegCloseKey( hKey);
		}
		else
		{
			AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
					WIN_WU_KEY);
		}
	}
	AddLog( _T( "Registry 9X/Me GetBiosInfo: OK.\n"));
	return TRUE;
}

BOOL CRegistry::GetBiosInfoNT( CBios *pMyBios)
{
	HKEY	hKey = NULL;
	TCHAR	szValue[256];
	LONG	lResult;
	DWORD	dwType;
	DWORD	dwSize;
	CString	csResult;
	LPCTSTR	pSZ;
	BOOL	bManufacturer = FALSE,
			bModel = FALSE;

	AddLog( _T( "Registry NT GetBiosInfo...\n"));
	// Windows NT
	lResult = RegOpenKeyEx( m_hKey, NT_BIOS_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get System manufacturer
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_SYSTEM_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_SYSTEM_MANUFACTURER_VALUE);
			pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
			bManufacturer = FALSE;
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemManufacturer( szValue);
			bManufacturer = TRUE;
		}
		// Get System model
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_SYSTEM_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_SYSTEM_MODEL_VALUE);
			pMyBios->SetSystemModel( NOT_AVAILABLE);
			bModel = FALSE;
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemModel( szValue);
			bModel = TRUE;
		}
		// Get System serial number
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_SYSTEM_SERIAL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_SYSTEM_SERIAL_VALUE);
			pMyBios->SetSystemSerialNumber( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetSystemSerialNumber( szValue);
		}
		// Get BIOS manufacturer
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_BIOS_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_BIOS_MANUFACTURER_VALUE);
			pMyBios->SetBiosManufacturer( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetBiosManufacturer( szValue);
		}
		// Get BIOS version
		dwType = REG_MULTI_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_BIOS_VERSION_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_BIOS_VERSION_VALUE);
			pMyBios->SetBiosVersion( NOT_AVAILABLE);
		}
		else
		{
			// Parse multistring registry value
			pSZ = ParseMultiSZ( szValue);
			while (pSZ != NULL)
			{
				csResult += pSZ;
				csResult += _T( " ");
				pSZ = ParseMultiSZ();
			}
			pMyBios->SetBiosVersion( csResult);
		}
		// Get BIOS date
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_BIOS_DATE_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_BIOS_DATE_VALUE);
			pMyBios->SetBiosDate( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetBiosDate( szValue);
		}
		// Get machine type
		dwType = REG_SZ;
		dwSize = 255;
		lResult = RegQueryValueEx( hKey, NT_BIOS_MACHINE_TYPE_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
		dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
		if (lResult != ERROR_SUCCESS)
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
					NT_BIOS_KEY, NT_BIOS_MACHINE_TYPE_VALUE);
			pMyBios->SetMachineType( NOT_AVAILABLE);
		}
		else
		{
			szValue[dwSize]=0;
			pMyBios->SetMachineType( szValue);
		}
		RegCloseKey( hKey);
	}
	else
	{
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_BIOS_KEY);
		pMyBios->Set( NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE
					  NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE, NOT_AVAILABLE);
	}
	if ((!bManufacturer) || (!bModel))
	{
		// Try to get System Manufacturer and Model from Windows Update Registry key
		lResult = RegOpenKeyEx( m_hKey, NT_WU_KEY, 0, KEY_READ, &hKey);
		if (lResult == ERROR_SUCCESS)
		{
			// Get System manufacturer
			if (!bManufacturer)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, NT_WU_SYSTEM_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							NT_WU_KEY, NT_WU_SYSTEM_MANUFACTURER_VALUE);
					pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
					bManufacturer = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemManufacturer( szValue);
					if (_tcsicmp( szValue, _T( "System Manufacturer")) == 0)
						// Default WU value when not available
						bManufacturer = FALSE;
					else
						// Not default value
						bManufacturer = TRUE;
				}
			}
			// Get System model
			if (!bModel)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, NT_WU_SYSTEM_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							NT_WU_KEY, NT_WU_SYSTEM_MODEL_VALUE);
					pMyBios->SetSystemModel( NOT_AVAILABLE);
					bModel = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemModel( szValue);
					if (_tcsicmp( szValue, _T( "System Name")) == 0)
						// Default WU value when not available
						bModel = FALSE;
					else
						// Not default value
						bModel = TRUE;
				}
			}
			// Get ACPI manufacturer
			if (!bManufacturer)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, NT_WU_ACPI_MANUFACTURER_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							NT_WU_KEY, NT_WU_ACPI_MANUFACTURER_VALUE);
					pMyBios->SetSystemManufacturer( NOT_AVAILABLE);
					bManufacturer = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemManufacturer( szValue);
					bManufacturer = TRUE;
				}
			}
			// Get ACPI model
			if (!bModel)
			{
				dwType = REG_SZ;
				dwSize = 255;
				lResult = RegQueryValueEx( hKey, NT_WU_ACPI_MODEL_VALUE, NULL, &dwType, (LPBYTE) szValue, &dwSize);
				dwSize < 256 ? szValue[dwSize] = 0 : szValue[255]=0;
				if (lResult != ERROR_SUCCESS)
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							NT_WU_KEY, NT_WU_ACPI_MODEL_VALUE);
					pMyBios->SetSystemModel( NOT_AVAILABLE);
					bModel = FALSE;
				}
				else
				{
					szValue[dwSize]=0;
					pMyBios->SetSystemModel( szValue);
					bModel = TRUE;
				}
			}
			RegCloseKey( hKey);
		}
		else
		{
			AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
					NT_WU_KEY);
		}
	}
	AddLog( _T( "Registry NT GetBiosInfo: OK.\n"));
	return TRUE;
}

BOOL CRegistry::IsNotebook()
{
	// Try to get Battery Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return IsNotebook9X();
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return IsNotebookNT();
	default:
		// Unknown
		AddLog( _T( "Registry IsNotebook...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::IsNotebook9X()
{
	HKEY			hKeyEnum;
	TCHAR			szDeviceName[256];
	DWORD			dwLength,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;

	AddLog( _T( "Registry 9X/Me IsNotebook...\n"));
	// Windows 9X/Me => Open the battery key
	if (RegOpenKeyEx( m_hKey, WIN_NOTEBOOK_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// There is at least one sub key
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me IsNotebook: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_NOTEBOOK_KEY);
		else
			AddLog( _T( "Registry 9X/Me IsNotebook: OK (%lu objects).\n"), dwIndexEnum);
	}
	else
		AddLog( _T( "Registry 9X/Me IsNotebook: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_NOTEBOOK_KEY);
	return (dwIndexEnum > 0);
}

BOOL CRegistry::IsNotebookNT()
{
	HKEY			hKeyEnum;
	TCHAR			szDeviceName[256];
	DWORD			dwLength,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;

	AddLog( _T( "Registry NT IsNotebook...\n"));
	// Windows NT => Open the battery key
	if (RegOpenKeyEx( m_hKey, NT_NOTEBOOK_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// There is at least one sub key
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT IsNotebook: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_NOTEBOOK_KEY);
		else
			AddLog( _T( "Registry NT IsNotebook: OK (%lu objects).\n"), dwIndexEnum);
	}
	else
		AddLog( _T( "Registry NT IsNotebook: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_NOTEBOOK_KEY);
	return (dwIndexEnum > 0);
}

DWORD CRegistry::GetProcessors(CString &csProcType, CString &csProcSpeed)
{
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetProcessors9X( csProcType, csProcSpeed);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetProcessorsNT( csProcType, csProcSpeed);
	default:
		// Unknown
		csProcType = NOT_AVAILABLE;
		csProcSpeed = NOT_AVAILABLE;
		AddLog( _T( "Registry GetProcessors...Failed because unsupported or unrecognized OS !\n"));
		return 0;
	}
	return 0;
}

DWORD CRegistry::GetProcessors9X(CString &csProcType, CString &csProcSpeed)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szDeviceName[256],
					szSpeed[256];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0,
					dwIndex = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	BOOL			bHaveToStore;

	AddLog( _T( "Registry 9X/Me GetProcessors...\n"));
	// Windows 9X => Open the processor key
	if (RegOpenKeyEx( m_hKey, WIN_PROCESSOR_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_PROCESSOR_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szSpeed, NOT_AVAILABLE);
				// Read the processor name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_PROCESSOR_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_PROCESSOR_NAME_VALUE);
					_tcscpy( szDeviceName, NOT_AVAILABLE);
				}
				// Read the speed
				dwLength = 255;
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, WIN_PROCESSOR_SPEED_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
					_stprintf( szSpeed, _T( "%u"), dwValue); // MHz
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_PROCESSOR_SPEED_VALUE);
					_tcscpy( szSpeed, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					csProcType = szDeviceName;
					StrForSQL( csProcType);
					csProcSpeed = szSpeed;
					StrForSQL( csProcSpeed);
					dwIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetProcessors: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_PROCESSOR_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetProcessors: OK (%s %s MHz, %lu objects).\n"),
					csProcType, csProcSpeed, dwIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetProcessors: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_PROCESSOR_KEY);
	AddLog( _T( "Registry 9X/Me GetProcessors: %lu processor(s) found.\n"), dwIndex);
	return dwIndex;
}

DWORD CRegistry::GetProcessorsNT(CString &csProcType, CString &csProcSpeed)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szDeviceName[256],
					szSpeed[256];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0,
					dwIndex = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	BOOL			bHaveToStore;

	AddLog( _T( "Registry NT GetProcessors...\n"));
	// Windows NT => Open the processor key
	if (RegOpenKeyEx( m_hKey, NT_PROCESSOR_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_PROCESSOR_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szSpeed, NOT_AVAILABLE);
				// Read the processor name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_PROCESSOR_NAME_STRING_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_PROCESSOR_NAME_STRING_VALUE);
					dwLength = 255;
					if (RegQueryValueEx( hKeyObject, NT_PROCESSOR_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
					{
						szDeviceName[dwLength]=0;
						bHaveToStore = TRUE;
					}
					else
					{
						if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
										   csSubKey, NT_PROCESSOR_NAME_VALUE);
						_tcscpy( szDeviceName, NOT_AVAILABLE);
					}
				}
				// Read the speed
				dwLength = 255;
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, NT_PROCESSOR_SPEED_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
					_stprintf( szSpeed, _T( "%u"), dwValue);//MHz
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_PROCESSOR_SPEED_VALUE);
					_tcscpy( szSpeed, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					csProcType = szDeviceName;
					StrForSQL( csProcType);
					csProcSpeed = szSpeed;
					StrForSQL( csProcSpeed);
					dwIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetProcessors: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_PROCESSOR_KEY);
		else
			AddLog( _T( "Registry NT GetProcessors: OK (%s %s MHz, %lu objects).\n"),
					csProcType, csProcSpeed, dwIndex);
	}
	else
		AddLog( _T( "Registry NT GetProcessors: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_PROCESSOR_KEY);
	AddLog( _T( "Registry NT GetProcessors: %lu processor(s) found.\n"), dwIndex);
	return dwIndex;
}

BOOL CRegistry::GetPrinters(CPrinterList *pList)
{
	HKEY			hKeyEnum,
					hKeyDevice;
	CString			csSubKey;
	TCHAR			szPrinterName[256],
					szDriver[256],
					szPort[256],
					szDeviceName[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry GetPrinters...\n"));
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Open the Printer key
	if (RegOpenKeyEx( m_hKey, PRINTERS_ENUM_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find printers
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			CPrinter	cPrinter;

			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), PRINTERS_ENUM_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyDevice) == ERROR_SUCCESS)
			{

				// OK => Read the Printer description
				dwLength = 255;
				if (RegQueryValueEx( hKeyDevice, PRINTER_NAME_VALUE, 0, &dwType, (LPBYTE) szPrinterName, &dwLength) == ERROR_SUCCESS)
				{
					szPrinterName[dwLength]=0;
					// Store the printer
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, PRINTER_NAME_VALUE);
					_tcscpy( szPrinterName, NOT_AVAILABLE);
				}
				// Read the Printer Driver
				dwLength = 255;
				if (RegQueryValueEx( hKeyDevice, PRINTER_DRIVER_VALUE, 0, &dwType, (LPBYTE) szDriver, &dwLength) == ERROR_SUCCESS)
				{
					szDriver[dwLength]=0;
					// Store the printer
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, PRINTER_DRIVER_VALUE);
					_tcscpy( szDriver, NOT_AVAILABLE); 
				}
				// Read the Printer Port
				dwLength = 255;
				if (RegQueryValueEx( hKeyDevice, PRINTER_PORT_VALUE, 0, &dwType, (LPBYTE) szPort, &dwLength) == ERROR_SUCCESS)
					szPort[dwLength]=0;
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, PRINTER_PORT_VALUE);
					_tcscpy( szPort, NOT_AVAILABLE); 
				}
				RegCloseKey( hKeyDevice);
				cPrinter.Set( szPrinterName, szDriver, szPort);
				// Add the device to the printer list if needed
				if (bHaveToStore)
				{
					pList->AddTail( cPrinter);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwIndexEnum++;
			dwLength = 255;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry GetPrinters: Failed in call to <RegEnumKeyEx> function to find Printer subkey.\n"));
		else
			AddLog( _T( "Registry GetPrinters: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry GetPrinters: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"), PRINTERS_ENUM_KEY);
	return TRUE;
}

BOOL CRegistry::GetVideoAdapters(CVideoAdapterList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get Display Adapter info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetVideoAdapters9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		if (m_bIsXP)
			return GetVideoAdaptersXP( pList);
		return GetVideoAdaptersNT_2K( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetVideoAdapters...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetVideoAdapters9X(CVideoAdapterList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject,
					hKeyProperty;
	CString			csSubKey,
					csResolution;
	TCHAR			szAdapterName[256],
					szAdapterChip[256],
					szDeviceName[256];
	DWORD			dwLength,
					dwType,
					dwMemory,
					dwIndexEnum = 0;
	LONG			lResult,
					lAdapterMemory;
	FILETIME		MyFileTime;
	CVideoAdapter	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry 9X/Me GetVideoAdapters...\n"));
	// Windows 9X => Open the Display key
	if (RegOpenKeyEx( m_hKey, WIN_DISPLAY_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices (have an INFO value)
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_DISPLAY_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szAdapterName, NOT_AVAILABLE);
				_tcscpy( szAdapterChip, NOT_AVAILABLE); 
				lAdapterMemory = -1;
				// OK => Read the Graphic Adapter description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_ADAPTER_NAME_VALUE, 0, &dwType, (LPBYTE) szAdapterName, &dwLength) == ERROR_SUCCESS)
				{
					szAdapterName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_ADAPTER_NAME_VALUE);
					_tcscpy( szAdapterName, NOT_AVAILABLE);
				}
				// Open the INFO key from Display Device
				csSubKey.Format( _T( "%s\\%s\\%s"), WIN_DISPLAY_KEY, szDeviceName, WIN_DEVICE_INFO_KEY);
				if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyProperty) == ERROR_SUCCESS)
				{
					// Read the Graphic Adapter Chipset
					dwLength = 255;
					if (RegQueryValueEx( hKeyProperty, WIN_ADAPTER_CHIP_VALUE, 0, &dwType, (LPBYTE) szAdapterChip, &dwLength) == ERROR_SUCCESS)
					{
						szAdapterChip[dwLength]=0;
						bHaveToStore = TRUE;
					}
					else
					{
						if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
										   csSubKey, WIN_ADAPTER_CHIP_VALUE);
						_tcscpy( szAdapterChip, NOT_AVAILABLE);
					}
					// Read the Graphic Adapter Memory size
					dwLength = sizeof( DWORD);
					dwType = REG_DWORD;
					if (RegQueryValueEx( hKeyProperty, WIN_ADAPTER_MEMORY_VALUE, 0, &dwType, (LPBYTE) &dwMemory, &dwLength) == ERROR_SUCCESS)
						lAdapterMemory = dwMemory/ONE_MEGABYTE;
					else
					{
						if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
										   csSubKey, WIN_ADAPTER_MEMORY_VALUE);
						lAdapterMemory = -1;
					}
					RegCloseKey( hKeyProperty);
				}
				else
					AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
									   csSubKey);
				RegCloseKey( hKeyObject);
				// Get screen resolution
				if (!GetScreenResolution( csResolution))
					AddLog( _T( "\tFailed in call to <GetSystemMetrics> function for SM_CXSCREEN and SM_CYSCREEN !\n"));
				myObject.Set( szAdapterName, szAdapterChip, lAdapterMemory, csResolution);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetVideoAdapters: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_DISPLAY_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetVideoAdapters: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetVideoAdapters: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_DISPLAY_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetVideoAdaptersNT_2K(CVideoAdapterList *pList)
{
	HKEY			hKeyEnum,
					hKeyGroup,
					hKeyObject,
					hKeyProperty;
	CString			csSubKey,
					csResolution;
	TCHAR			szAdapterName[256],
					szAdapterChip[256],
					szGroupName[256],
					szDeviceName[256],
					szPropertyName[256],
					szClassName[256],
					szServiceName[256];
	DWORD			dwLength,
					dwType,
					dwMemory,
					dwIndexEnum = 0,
					dwIndexGroup = 0,
					dwIndexProperties = 0;
	LONG			lResult,
					lAdapterMemory;
	FILETIME		MyFileTime;
	CVideoAdapter	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry NT GetVideoAdapters...\n"));
	// Windows NT =>  Browse the active service keys to find the Display service
	// Enumerate service groups under HKLM\System\CurrentControlSet\Enum
	if (RegOpenKeyEx( m_hKey, NT_ENUM_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szGroupName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each group, enumerate service keys
			szGroupName[dwLength] = 0;
			csSubKey.Format( _T( "%s\\%s"), NT_ENUM_KEY, szGroupName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyGroup) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexGroup = 0;
				while ((lResult = RegEnumKeyEx( hKeyGroup, dwIndexGroup, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each service, enumerate propertie keys
					szDeviceName[dwLength] = 0;
					csSubKey.Format( _T( "%s\\%s\\%s"), NT_ENUM_KEY, szGroupName, szDeviceName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
					{
						dwLength = 255;
						dwIndexProperties = 0;
						while ((lResult = RegEnumKeyEx( hKeyObject, dwIndexProperties, szPropertyName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
						{
							// If a display class key, read the associated service
							szPropertyName[dwLength] = 0;
							csSubKey.Format( _T( "%s\\%s\\%s\\%s"), NT_ENUM_KEY, szGroupName, szDeviceName, szPropertyName);
							if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyProperty) == ERROR_SUCCESS)
							{
								// Read the class
								dwLength = 255;
								if (RegQueryValueEx( hKeyProperty, NT_ENUM_CLASS_VALUE, 0, &dwType, (LPBYTE) szClassName, &dwLength) != ERROR_SUCCESS)
								{
									// Cannot read the class name
									RegCloseKey( hKeyProperty);
									dwIndexProperties ++;
									dwLength = 255;
									continue;
								}
								else
									if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													   csSubKey, NT_ENUM_CLASS_VALUE);
								szClassName[dwLength] = 0;
								if (_tcsicmp( szClassName, NT_ENUM_DISPLAY_VALUE) != 0)
								{
									// Not a display service
									dwIndexProperties ++;
									dwLength = 255;
									continue;
								}
								// We have found the display service => get the service name
								dwLength = 255;
								if (RegQueryValueEx( hKeyProperty, NT_ENUM_SERVICE_VALUE, 0, &dwType, (LPBYTE) szServiceName, &dwLength) != ERROR_SUCCESS)
								{
									// Cannot read the associated service name
									RegCloseKey( hKeyProperty);
									dwIndexProperties ++;
									dwLength = 255;
									continue;
								}
								else
									if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													   csSubKey, NT_ENUM_SERVICE_VALUE);
								// We know the service name => get the Graphic Adapter infos
								szServiceName[dwLength] = 0;
								RegCloseKey( hKeyProperty);
								csSubKey.Format( _T( "%s\\%s\\%s"), NT_SERVICES_KEY, szServiceName, NT_SERVICE_DEVICE_KEY);
								_tcscpy( szAdapterName, NOT_AVAILABLE);
								_tcscpy( szAdapterChip, NOT_AVAILABLE);
								lAdapterMemory = -1;
								bHaveToStore = FALSE;
								if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyProperty) == ERROR_SUCCESS)
								{
									dwLength = 255;
									// Get the Graphic Adapter name
									if (RegQueryValueEx( hKeyProperty, NT_ADAPTER_NAME_VALUE, 0, &dwType, (LPBYTE) szAdapterName, &dwLength) == ERROR_SUCCESS)
									{
										szAdapterName[dwLength]=0;
										// The value is an array of string, each string only containing one character
										// Build a real string by copying each string to one
										CString csAdapter;
										csAdapter.Format( _T( "%S"), szAdapterName);
										_tcscpy( szAdapterName, csAdapter);
										bHaveToStore = TRUE;
									}
									else
									{
										if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
														   csSubKey, NT_ADAPTER_NAME_VALUE);
										_tcscpy( szAdapterName, NOT_AVAILABLE);
									}
									// Get the Graphic Adapter Chipset
									dwLength = 255;
									if (RegQueryValueEx( hKeyProperty, NT_ADAPTER_CHIP_VALUE, 0, &dwType, (LPBYTE) szAdapterChip, &dwLength) == ERROR_SUCCESS)
									{
										szAdapterChip[dwLength]=0;
										// The value is an array of string, each string only containing one character
										// Build a real string by copying each string to one
										CString csChip;
										csChip.Format( _T( "%S"), szAdapterChip);
										_tcscpy( szAdapterChip, csChip);
										bHaveToStore = TRUE;
									}
									else
									{
										if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
														   csSubKey, NT_ADAPTER_CHIP_VALUE);
										_tcscpy( szAdapterName, NOT_AVAILABLE);
									}
									// Get the Graphic Adapter Memory size
									dwLength = sizeof( DWORD);
									dwType = REG_DWORD;
									if (RegQueryValueEx( hKeyProperty, NT_ADAPTER_MEMORY_VALUE, 0, &dwType, (LPBYTE) &dwMemory, &dwLength) == ERROR_SUCCESS)
										lAdapterMemory = dwMemory/ONE_MEGABYTE;
									else
									{
										if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
														   csSubKey, NT_ADAPTER_MEMORY_VALUE);
										lAdapterMemory = -1;
									}
									// Get screen resolution
									GetScreenResolution( csResolution);
									myObject.Set( szAdapterName, szAdapterChip, lAdapterMemory, csResolution);
									// Add the device to the adapter lis
									if (bHaveToStore)
									{
										pList->AddTail( myObject);
										uIndex ++;
									}
									RegCloseKey( hKeyProperty);
								} // if RegOpenKey NT_SERVICE_KEY
								else
									AddLog( _T( "\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
													   csSubKey);
							} // if RegOpenKey Property Key
							else
								AddLog( _T( "\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
												   csSubKey);
							dwIndexProperties++;
							dwLength = 255;
						} // while RegEnumKey Properties
						RegCloseKey( hKeyObject);
						if (dwIndexProperties == 0)
							// No key found
							AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
											   csSubKey);
					} // if RegOpenKey Object Key
					else
						AddLog( _T( "\t\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
										   csSubKey);
					dwIndexGroup ++;
					dwLength = 255;
				} // while RegEnumKey Group
				RegCloseKey( hKeyGroup);
				if (dwIndexGroup == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
									   csSubKey);
			} // if RegOpenKey Group Key
			else
				AddLog( _T( "\t\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
								   csSubKey);
			dwIndexEnum++;
			dwLength = 255;
		} // while RegEnumKey Enum
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetVideoAdapters: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
				    NT_ENUM_KEY);
		else
			AddLog( _T( "Registry NT GetVideoAdapters: OK (%u objects).\n"), uIndex);
	} // if RegOpenKey enum Key
	else
		AddLog( _T( "Registry NT GetVideoAdapters: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_ENUM_KEY);
	return TRUE;
}

BOOL CRegistry::GetVideoAdaptersXP(CVideoAdapterList *pList)
{
	HKEY			hKeyEnum,
					hKeyGroup,
					hKeyProperty;
	CString			csSubKey,
					csResolution;
	TCHAR			szAdapterName[256],
					szAdapterChip[256],
					szGroupName[256],
					szDeviceName[256];
	DWORD			dwLength,
					dwType,
					dwMemory,
					dwIndexEnum = 0,
					dwIndexGroup = 0;
	LONG			lResult,
					lAdapterMemory;
	FILETIME		MyFileTime;
	CVideoAdapter	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry XP GetVideoAdapters...\n"));
	// Windows XP =>  Browse the active service keys to find the Display service
	// Enumerate device groups under HKLM\System\CurrentControlSet\Control\Video
	if (RegOpenKeyEx( m_hKey, XP_ENUM_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szGroupName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each group, enumerate device keys
			szGroupName[dwLength] = 0;
			csSubKey.Format( _T( "%s\\%s"), XP_ENUM_KEY, szGroupName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyGroup) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexGroup = 0;
				while ((lResult = RegEnumKeyEx( hKeyGroup, dwIndexGroup, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each device, get propertie keys
					szDeviceName[dwLength] = 0;
					csSubKey.Format( _T( "%s\\%s\\%s"), XP_ENUM_KEY, szGroupName, szDeviceName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyProperty) == ERROR_SUCCESS)
					{
						dwLength = 255;
						bHaveToStore = FALSE;
						// Get the Graphic Adapter name
						if (RegQueryValueEx( hKeyProperty, XP_ADAPTER_NAME_VALUE, 0, &dwType, (LPBYTE) szAdapterName, &dwLength) == ERROR_SUCCESS)
						{
							szAdapterName[dwLength]=0;
							// The value is an array of string, each string only containing one character
							// Build a real string by copying each string to one
							CString csAdapter;

							csAdapter.Format( _T( "%S"), szAdapterName);
							_tcscpy( szAdapterName, csAdapter);
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
											   csSubKey, XP_ADAPTER_NAME_VALUE);
							_tcscpy( szAdapterName, NOT_AVAILABLE);
						}
						// Get the Graphic Adapter Chipset
						dwLength = 255;
						if (RegQueryValueEx( hKeyProperty, XP_ADAPTER_CHIP_VALUE, 0, &dwType, (LPBYTE) szAdapterChip, &dwLength) == ERROR_SUCCESS)
						{
							szAdapterChip[dwLength]=0;
							// The value is an array of string, each string only containing one character
							// Build a real string by copying each string to one
							CString csChip;

							csChip.Format( _T( "%S"), szAdapterChip);
							_tcscpy( szAdapterChip, csChip);
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
											   csSubKey, XP_ADAPTER_CHIP_VALUE);
							_tcscpy( szAdapterName, NOT_AVAILABLE);
						}
						// Get the Graphic Adapter Memory size
						dwLength = sizeof( DWORD);
						dwType = REG_DWORD;
						if (RegQueryValueEx( hKeyProperty, XP_ADAPTER_MEMORY_VALUE, 0, &dwType, (LPBYTE) &dwMemory, &dwLength) == ERROR_SUCCESS)
							lAdapterMemory = dwMemory/ONE_MEGABYTE;
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
											   csSubKey, XP_ADAPTER_MEMORY_VALUE);
							lAdapterMemory = -1;
						}
						// Get screen resolution
						GetScreenResolution( csResolution);
						myObject.Set( szAdapterName, szAdapterChip, lAdapterMemory, csResolution);
						// Add the device to the adapter lis
						if (bHaveToStore)
						{
							pList->AddTail( myObject);
							uIndex ++;
						}
						RegCloseKey( hKeyProperty);
					} // if RegOpenKey Object Key
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
										   csSubKey);
					dwIndexGroup ++;
					dwLength = 255;
				} // while RegEnumKey Group
				RegCloseKey( hKeyGroup);
				if (dwIndexGroup == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKey);
			} // if RegOpenKey Group Key
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> for HKLM\\%s !\n"),
						csSubKey);
			dwIndexEnum++;
			dwLength = 255;
		} // while RegEnumKey Enum
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
		{
			// No key found
			AddLog( _T( "Registry XP GetVideoAdapters: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
				   NT_ENUM_KEY);
			return FALSE;
		}
		AddLog( _T( "Registry XP GetVideoAdapters: OK (%u objects).\n"), uIndex);
		return TRUE;
	} // if RegOpenKey enum Key
	AddLog( _T( "Registry XP GetVideoAdapters: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"), NT_ENUM_KEY);
	return FALSE;
}

BOOL CRegistry::GetScreenResolution(CString &csResolution)
{
	int nScreenWidth,
		nScreenHeight;

	csResolution = NOT_AVAILABLE;
	if ((nScreenWidth = GetSystemMetrics(SM_CXSCREEN)) == 0)
		return FALSE;
	if ((nScreenHeight = GetSystemMetrics(SM_CYSCREEN)) == 0)
		return FALSE;
	csResolution.Format( _T( "%d x %d"), nScreenWidth, nScreenHeight);
	return TRUE;
}

BOOL CRegistry::GetSoundDevices(CSoundDeviceList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get Sound Devices Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetSoundDevices9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetSoundDevicesNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetSoundDevices...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetSoundDevices9X(CSoundDeviceList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject,
					hKeyDriver;
	CString			csSubKey;
	TCHAR			szProviderName[256],
					szDescription[256],
					szDeviceName[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSoundDevice	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry 9X/Me GetSoundDevices...\n"));
	// Windows 9X => Open the sound key
	if (RegOpenKeyEx( m_hKey, WIN_SOUND_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_SOUND_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szProviderName, NOT_AVAILABLE);
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// OK => Read the provider
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SOUND_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szProviderName, &dwLength) == ERROR_SUCCESS)
				{
					szProviderName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SOUND_MANUFACTURER_VALUE);
					_tcscpy( szProviderName, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SOUND_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SOUND_NAME_VALUE);
					_tcscpy( szDeviceName, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SOUND_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SOUND_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szProviderName, szDeviceName, szDescription);
				// Check if there is a Drivers sub key to validate
				csSubKey += _T( "\\");
				csSubKey += WIN_SOUND_DRIVER;
				if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyDriver) == ERROR_SUCCESS)
				{
					// OK => Try to read the SubClasses value
					dwLength = 255;
					if (RegQueryValueEx( hKeyDriver, WIN_SOUND_DRIVER_CLASS, 0, &dwType, (LPBYTE) szProviderName, &dwLength) != ERROR_SUCCESS)
						// No value => skip
						bHaveToStore = FALSE;
					RegCloseKey( hKeyDriver);
				}
				else
					// No Driver sub key => skip
					bHaveToStore = FALSE;
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetSoundDevices: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_SOUND_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetSoundDevices: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSoundDevices: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_SOUND_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetSoundDevicesNT(CSoundDeviceList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject,
					hKeyDriver;
	CString			csSubKey;
	TCHAR			szProviderName[256],
					szDescription[256],
					szDeviceName[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSoundDevice	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry NT GetSoundDevices...\n"));
	// Windows NT => Open the sound key
	if (RegOpenKeyEx( m_hKey, NT_SOUND_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_SOUND_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szProviderName, NOT_AVAILABLE);
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// OK => Read the provider
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SOUND_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szProviderName, &dwLength) == ERROR_SUCCESS)
				{
					szProviderName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SOUND_MANUFACTURER_VALUE);
					_tcscpy( szProviderName, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SOUND_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SOUND_NAME_VALUE);
					_tcscpy( szDeviceName, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SOUND_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SOUND_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szProviderName, szDeviceName, szDescription);
				// Check if there is a Drivers sub key to validate
				csSubKey += _T( "\\");
				csSubKey += NT_SOUND_DRIVER;
				if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyDriver) == ERROR_SUCCESS)
				{
					// OK => Try to read the SubClasses value
					dwLength = 255;
					if (RegQueryValueEx( hKeyDriver, NT_SOUND_DRIVER_CLASS, 0, &dwType, (LPBYTE) szProviderName, &dwLength) != ERROR_SUCCESS)
						// No value => skip
						bHaveToStore = FALSE;
					RegCloseKey( hKeyDriver);
				}
				else
					// No Driver sub key => skip
					bHaveToStore = FALSE;
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetSoundDevices: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_SOUND_KEY);
		else
			AddLog( _T( "Registry NT GetSoundDevices: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSoundDevices: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_SOUND_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetModems(CModemList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get Modems Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetModems9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetModemsNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetModems...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetModems9X(CModemList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szModel[256],
					szDescription[256],
					szDeviceName[256],
					szType[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CModem			myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry 9X/Me GetModems...\n"));
	// Windows 9X => Open the modem key
	if (RegOpenKeyEx( m_hKey, WIN_MODEM_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_MODEM_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szType, NOT_AVAILABLE); 
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szModel, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the type, i.e the COM port attached to
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MODEM_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
				{
					szType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MODEM_TYPE_VALUE);
					_tcscpy( szType, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MODEM_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MODEM_NAME_VALUE);
					_tcscpy( szDeviceName, NOT_AVAILABLE);
				}
				// Read the model
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MODEM_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
				{
					szModel[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MODEM_MODEL_VALUE);
					_tcscpy( szModel, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MODEM_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MODEM_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szType, szDeviceName, szModel, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetModems: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_MODEM_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetModems: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetModems: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_MODEM_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetModemsNT(CModemList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szModel[256],
					szDescription[256],
					szDeviceName[256],
					szType[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CModem			myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry NT GetModems...\n"));
	// Windows NT => Open the modem key
	if (RegOpenKeyEx( m_hKey, NT_MODEM_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szDeviceName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szDeviceName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_MODEM_KEY, szDeviceName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szType, NOT_AVAILABLE); 
				_tcscpy( szDeviceName, NOT_AVAILABLE); 
				_tcscpy( szModel, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the type, i.e the COM port attached to
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MODEM_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
				{
					szType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MODEM_TYPE_VALUE);
					_tcscpy( szType, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MODEM_NAME_VALUE, 0, &dwType, (LPBYTE) szDeviceName, &dwLength) == ERROR_SUCCESS)
				{
					szDeviceName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MODEM_NAME_VALUE);
					_tcscpy( szDeviceName, NOT_AVAILABLE);
				}
				// Read the model
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MODEM_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
				{
					szModel[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MODEM_MODEL_VALUE);
					_tcscpy( szModel, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MODEM_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MODEM_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szType, szDeviceName, szModel, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetModems: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_MODEM_KEY);
		else
			AddLog( _T( "Registry NT GetModems: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetModems: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_MODEM_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetMonitors(CMonitorList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get Monitors Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetMonitors9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetMonitorsNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetMonitors...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetMonitors9X(CMonitorList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szModel[256],
					szDescription[256],
					szManufacturer[256],
					szCaption[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CMonitor		myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry 9X/Me GetMonitors...\n"));
	// Windows 9X => Open the monitor key
	if (RegOpenKeyEx( m_hKey, WIN_MONITOR_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szModel, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szModel[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_MONITOR_KEY, szModel);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szModel, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MONITOR_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MONITOR_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the model
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MONITOR_TYPE_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
				{
					szModel[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MONITOR_TYPE_VALUE);
					_tcscpy( szModel, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MONITOR_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MONITOR_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_MONITOR_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_MONITOR_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szManufacturer, szModel, szCaption, szDescription, "");
				// Add the device to the adapter list
				// ValidateComponent9X( csSubKey);
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetMonitors: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_MONITOR_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetMonitors: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetMonitors: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_MONITOR_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetMonitorsNT(CMonitorList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szModel[256],
					szDescription[256],
					szManufacturer[256],
					szCaption[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CMonitor		myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry NT GetMonitors...\n"));
	// Windows 9X => Open the monitor key
	if (RegOpenKeyEx( m_hKey, NT_MONITOR_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szModel, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szModel[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_MONITOR_KEY, szModel);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szModel, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MONITOR_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MONITOR_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the model
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MONITOR_TYPE_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
				{
					szModel[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MONITOR_TYPE_VALUE);
					_tcscpy( szModel, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MONITOR_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MONITOR_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_MONITOR_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_MONITOR_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szManufacturer, szModel, szCaption, szDescription, "");
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetMonitors: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_MONITOR_KEY);
		else
			AddLog( _T( "Registry NT GetMonitors: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetMonitors: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_MONITOR_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetSystemControllers(CSystemControllerList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get system Controllers Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetSystemControllers9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetSystemControllersNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetSystemControllers...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetSystemControllers9X(CSystemControllerList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szManufacturer[256],
					szName[256],
					szCaption[256],
					szDescription[256],
					szVersion[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSystemController myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find Floppy Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_FLOPPY_KEY);
	// Windows 9X => Open the floppy controler key
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_FLOPPY_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_FLOPPY_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_FLOPPY_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_FLOPPY_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_FLOPPY_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_FLOPPY_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_FLOPPY_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_FLOPPY_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_FLOPPY_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_FLOPPY_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_FLOPPY_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_FLOPPY_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_FLOPPY, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_FLOPPY_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_FLOPPY_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find Floppy Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find Floppy Controllers failed because no valid object !\n"));
	// Windows 9X => Open the IDE controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find IDE Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_IDE_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_IDE_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_IDE_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IDE_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IDE_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IDE_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IDE_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IDE_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IDE_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IDE_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IDE_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IDE_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IDE_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_IDE, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_IDE_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_IDE_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find IDE Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find IDE Controllers failed because no valid object !\n"));
	// Windows 9X => Open the SCSI controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find SCSI Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_SCSI_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_SCSI_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_SCSI_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_SCSI_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_SCSI_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_SCSI_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_SCSI_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_SCSI_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_SCSI_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_SCSI_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_SCSI_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_SCSI_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_SCSI_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_SCSI, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_SCSI_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_SCSI_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find SCSI Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find SCSI Controllers failed because no valid object !\n"));
	// Windows 9X => Open the INFRARED controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find InfraRed Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_INFRARED_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_INFRARED_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_INFRARED_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_INFRARED_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_INFRARED_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_INFRARED_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_INFRARED_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_INFRARED_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_INFRARED_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_INFRARED_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_INFRARED_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_INFRARED_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_INFRARED_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_INFRARED, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_INFRARED_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_INFRARED_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find InfraRed Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find InfraRed Controllers failed because no valid object !\n"));
	// Windows 9X => Open the USB controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find USB Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_USB_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_USB_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_USB_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_USB_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_USB_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_USB_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_USB_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_USB_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_USB_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_USB_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_USB_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_USB_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_USB_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_USB, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_USB_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_USB_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find USB Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find USB Controllers failed because no valid object !\n"));
	// Windows 9X => Open the IEEE1394 controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find IEEE1394 Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_IEEE1394_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_IEEE1394_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_IEEE1394_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IEEE1394_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IEEE1394_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IEEE1394_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IEEE1394_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IEEE1394_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IEEE1394_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IEEE1394_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IEEE1394_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_IEEE1394_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_IEEE1394_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_IEEE1394, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_IEEE1394_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_IEEE1394_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find IEEE1394 Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find IEEE1394 Controllers failed because no valid object !\n"));
	// Windows 9X => Open the PCMCIA controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Trying to find PCMCIA Controllers in HKLM\\%s...\n"),
			WIN_CONTROLER_PCMCIA_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_CONTROLER_PCMCIA_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONTROLER_PCMCIA_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_PCMCIA_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_PCMCIA_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_PCMCIA_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_PCMCIA_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_PCMCIA_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_PCMCIA_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_PCMCIA_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_PCMCIA_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONTROLER_PCMCIA_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_CONTROLER_PCMCIA_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_PCMCIA, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_CONTROLER_PCMCIA_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONTROLER_PCMCIA_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find PCMCIA Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemControllers: Find PCMCIA Controllers failed because no valid object !\n"));
	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry 9X/Me GetSystemControllers: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry 9X/Me GetSystemControllers: Failed because no controler found.\n"));
	return FALSE;
}

BOOL CRegistry::GetSystemControllersNT(CSystemControllerList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szManufacturer[256],
					szName[256],
					szCaption[256],
					szDescription[256],
					szVersion[256],
					szValue[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSystemController myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	AddLog( _T( "Registry NT GetSystemControllers: Trying to find Floppy Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_FLOPPY_KEY);
	// Windows NT => Open the floppy controler key
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_FLOPPY_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_FLOPPY_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_FLOPPY_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_FLOPPY_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_FLOPPY_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_FLOPPY_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_FLOPPY_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_FLOPPY_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_FLOPPY_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_FLOPPY_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_FLOPPY_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_FLOPPY_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_FLOPPY, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_FLOPPY_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_FLOPPY_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find Floppy Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find Floppy Controllers failed because no valid object !\n"));
	// Windows NT => Open the IDE controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find IDE Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_IDE_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_IDE_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_IDE_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IDE_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IDE_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IDE_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IDE_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IDE_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IDE_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IDE_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IDE_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IDE_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IDE_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_IDE, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_IDE_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_IDE_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find IDE Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find IDE Controllers failed because no valid object !\n"));
	// Windows NT => Open the SCSI controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find SCSI Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_SCSI_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_SCSI_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_SCSI_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_SCSI_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_SCSI_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_SCSI_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_SCSI_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_SCSI_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_SCSI_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_SCSI_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_SCSI_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_SCSI_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_SCSI_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_SCSI, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_SCSI_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_SCSI_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find SCSI Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find SCSI Controllers failed because no valid object !\n"));
	// Windows NT => Open the InfraRed controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find InfraRed Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_INFRARED_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_INFRARED_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_INFRARED_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				// Ensure it is a controler
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_INFRARED_CONTROLER_VALUE, 0, &dwType, (LPBYTE) szValue, &dwLength) == ERROR_SUCCESS)
				{
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_INFRARED_CONTROLER_VALUE);
					bHaveToStore = FALSE;
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_INFRARED, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_INFRARED_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_INFRARED_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find InfraRed Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find InfraRed Controllers failed because no valid object !\n"));
	// Windows NT => Open the USB controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find USB Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_USB_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_USB_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_USB_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				// Ensure it is a controler
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_USB_CONTROLER_VALUE, 0, &dwType, (LPBYTE) szValue, &dwLength) == ERROR_SUCCESS)
				{
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_USB_CONTROLER_VALUE);
					bHaveToStore = FALSE;
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_USB, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_USB_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_USB_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find USB Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find USB Controllers failed because no valid object !\n"));
	// Windows NT => Open the IEEE1394 controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find IEEE1394 Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_IEEE1394_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_IEEE1394_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_IEEE1394_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IEEE1394_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IEEE1394_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IEEE1394_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IEEE1394_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IEEE1394_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IEEE1394_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IEEE1394_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IEEE1394_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_IEEE1394_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_IEEE1394_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_IEEE1394, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_IEEE1394_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_IEEE1394_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find IEEE1394 Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find IEEE1394 Controllers failed because no valid object !\n"));
	// Windows NT => Open the PCMCIA controler key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetSystemControllers: Trying to find PCMCIA Controllers in HKLM\\%s...\n"),
			NT_CONTROLER_PCMCIA_KEY);
	if (RegOpenKeyEx( m_hKey, NT_CONTROLER_PCMCIA_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_CONTROLER_PCMCIA_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE);
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_PCMCIA_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_PCMCIA_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_PCMCIA_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_PCMCIA_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_PCMCIA_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_PCMCIA_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_PCMCIA_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_PCMCIA_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the verion
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_CONTROLER_PCMCIA_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_CONTROLER_PCMCIA_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( SYSTEM_CONTROLER_PCMCIA, szManufacturer, szName, szVersion, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_CONTROLER_PCMCIA_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_CONTROLER_PCMCIA_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetSystemControllers: Find PCMCIA Controllers OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemControllers: Find PCMCIA Controllers failed because no valid object !\n"));
	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry NT GetSystemControllers: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry NT GetSystemControllers: Failed because no controler found.\n"));
	return FALSE;
}

BOOL CRegistry::GetStoragePeripherals(CStoragePeripheralList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get Storage Peripherals Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetStoragePeripherals9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetStoragePeripheralsNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetStoragePeripherals...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetStoragePeripherals9X(CStoragePeripheralList *pList)
{
	HKEY			hKeyEnum,
					hKeySubEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szManufacturer[256],
					szModel[256],
					szName[256],
					szDescription[256],
					szType[256],
					szItem[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0,
					dwIndexSubEnum;
	LONG			lResult;
	FILETIME		MyFileTime;
	CStoragePeripheral	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Trying to find Floppy Drives in HKLM\\%s...\n"),
			WIN_STORAGE_FLOPPY_KEY);
	// Windows 9X => Open the floppy drive key
	if (RegOpenKeyEx( m_hKey, WIN_STORAGE_FLOPPY_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szItem, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szItem[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_STORAGE_FLOPPY_KEY, szItem);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeySubEnum) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexSubEnum = 0;
				while ((lResult = RegEnumKeyEx( hKeySubEnum, dwIndexSubEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each object, Try to open the device key
					szName[dwLength] = 0;
					bHaveToStore = FALSE;
					csSubKey.Format( _T( "%s\\%s\\%s"), WIN_STORAGE_FLOPPY_KEY, szItem, szName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
					{
						_tcscpy( szManufacturer, NOT_AVAILABLE); 
						_tcscpy( szModel, NOT_AVAILABLE);
						_tcscpy( szName, NOT_AVAILABLE); 
						_tcscpy( szDescription, NOT_AVAILABLE); 
						_tcscpy( szType, NOT_AVAILABLE); 
						// Read the manufactuer
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_FLOPPY_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
						{
							szManufacturer[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_FLOPPY_MANUFACTURER_VALUE);
							_tcscpy( szManufacturer, NOT_AVAILABLE);
						}
						// Read the model
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_FLOPPY_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
						{
							szModel[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_FLOPPY_MODEL_VALUE);
							_tcscpy( szModel, NOT_AVAILABLE);
						}
						// Read the name
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_FLOPPY_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
						{
							szName[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_FLOPPY_NAME_VALUE);
							_tcscpy( szName, NOT_AVAILABLE);
						}
						// Read the description
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_FLOPPY_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
						{
							szDescription[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_FLOPPY_DESCRIPTION_VALUE);
							_tcscpy( szDescription, NOT_AVAILABLE);
						}
						// Read the type
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_FLOPPY_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
						{
							szType[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_FLOPPY_TYPE_VALUE);
							_tcscpy( szType, NOT_AVAILABLE);
						}
						RegCloseKey( hKeyObject);
						myObject.Set( szType, szManufacturer, szName, szModel, szDescription);
						// Add the device to the adapter list
						// ValidateComponent9X( csSubKey);
						if (bHaveToStore)
						{
							pList->AddTail( myObject);
							uIndex ++;
						}
					}
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								csSubKey);
					// Enum the next device
					dwLength = 255;
					dwIndexSubEnum++;
				}
				RegCloseKey( hKeySubEnum);
				if (dwIndexSubEnum == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKey);
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
						csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_STORAGE_FLOPPY_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_STORAGE_FLOPPY_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Floppy Drives OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Floppy Drives failed because no valid object !\n"));
	// Windows 9X => Open the disk drive key
	AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Trying to find Disk Drives in HKLM\\%s...\n"),
			WIN_STORAGE_DISK_KEY);
	uIndex = 0;
	dwIndexEnum = 0;
	if (RegOpenKeyEx( m_hKey, WIN_STORAGE_DISK_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szItem, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szItem[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_STORAGE_DISK_KEY, szItem);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeySubEnum) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexSubEnum = 0;
				while ((lResult = RegEnumKeyEx( hKeySubEnum, dwIndexSubEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each object, Try to open the device key
					szName[dwLength] = 0;
					bHaveToStore = FALSE;
					csSubKey.Format( _T( "%s\\%s\\%s"), WIN_STORAGE_DISK_KEY, szItem, szName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
					{
						_tcscpy( szManufacturer, NOT_AVAILABLE); 
						_tcscpy( szModel, NOT_AVAILABLE);
						_tcscpy( szName, NOT_AVAILABLE); 
						_tcscpy( szDescription, NOT_AVAILABLE); 
						_tcscpy( szType, NOT_AVAILABLE); 
						// Read the manufactuer
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_DISK_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
						{
							szManufacturer[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_DISK_MANUFACTURER_VALUE);
							_tcscpy( szManufacturer, NOT_AVAILABLE);
						}
						// Read the model
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_DISK_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
						{
							szModel[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_DISK_MODEL_VALUE);
							_tcscpy( szModel, NOT_AVAILABLE);
						}
						// Read the name
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_DISK_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
						{
							szName[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_DISK_NAME_VALUE);
							_tcscpy( szName, NOT_AVAILABLE);
						}
						// Read the description
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_DISK_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
						{
							szDescription[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_DISK_DESCRIPTION_VALUE);
							_tcscpy( szDescription, NOT_AVAILABLE);
						}
						// Read the type
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_DISK_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
						{
							szType[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_DISK_TYPE_VALUE);
							_tcscpy( szType, NOT_AVAILABLE);
						}
						RegCloseKey( hKeyObject);
						myObject.Set( szType, szManufacturer, szName, szModel, szDescription);
						// Add the device to the adapter list
						// ValidateComponent9X( csSubKey);
						if (bHaveToStore)
						{
							pList->AddTail( myObject);
							uIndex ++;
						}
					}
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								csSubKey);
					// Enum the next device
					dwLength = 255;
					dwIndexSubEnum++;
				}
				RegCloseKey( hKeySubEnum);
				if (dwIndexSubEnum == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKey);
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
						csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_STORAGE_DISK_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_STORAGE_DISK_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Disk Drives OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Disk Drives failed because no valid object !\n"));
	// Windows 9X => Open the other drive key
	AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Trying to find Other Drives in HKLM\\%s...\n"),
			WIN_STORAGE_OTHER_KEY);
	uIndex = 0;
	dwIndexEnum = 0;
	if (RegOpenKeyEx( m_hKey, WIN_STORAGE_OTHER_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szItem, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szItem[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_STORAGE_OTHER_KEY, szItem);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeySubEnum) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexSubEnum = 0;
				while ((lResult = RegEnumKeyEx( hKeySubEnum, dwIndexSubEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each object, Try to open the device key
					szName[dwLength] = 0;
					bHaveToStore = FALSE;
					csSubKey.Format( _T( "%s\\%s\\%s"), WIN_STORAGE_OTHER_KEY, szItem, szName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
					{
						_tcscpy( szManufacturer, NOT_AVAILABLE); 
						_tcscpy( szModel, NOT_AVAILABLE);
						_tcscpy( szName, NOT_AVAILABLE); 
						_tcscpy( szDescription, NOT_AVAILABLE); 
						_tcscpy( szType, NOT_AVAILABLE); 
						// Read the manufactuer
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_OTHER_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
						{
							szManufacturer[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_OTHER_MANUFACTURER_VALUE);
							_tcscpy( szManufacturer, NOT_AVAILABLE);
						}
						// Read the model
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_OTHER_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
						{
							szModel[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_OTHER_MODEL_VALUE);
							_tcscpy( szModel, NOT_AVAILABLE);
						}
						// Read the name
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_OTHER_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
						{
							szName[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_OTHER_NAME_VALUE);
							_tcscpy( szName, NOT_AVAILABLE);
						}
						// Read the description
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_OTHER_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
						{
							szDescription[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_OTHER_DESCRIPTION_VALUE);
							_tcscpy( szDescription, NOT_AVAILABLE);
						}
						// Read the type
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, WIN_STORAGE_OTHER_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
						{
							szType[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, WIN_STORAGE_OTHER_TYPE_VALUE);
							_tcscpy( szType, NOT_AVAILABLE);
						}
						RegCloseKey( hKeyObject);
						myObject.Set( szType, szManufacturer, szName, szModel, szDescription);
						// Add the device to the adapter list
						// ValidateComponent9X( csSubKey);
						if (bHaveToStore)
						{
							pList->AddTail( myObject);
							uIndex ++;
						}
					}
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								csSubKey);
					// Enum the next device
					dwLength = 255;
					dwIndexSubEnum++;
				}
				RegCloseKey( hKeySubEnum);
				if (dwIndexSubEnum == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKey);
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
						csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_STORAGE_OTHER_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_STORAGE_OTHER_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Other Drives OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Find Other Drives failed because no valid object !\n"));
	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry 9X/Me GetStoragePeripherals: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry 9X/Me GetStoragePeripherals: Failed because no storage peripherals found.\n"));
	return FALSE;
}

BOOL CRegistry::GetStoragePeripheralsNT(CStoragePeripheralList *pList)
{
	HKEY			hKeyEnum,
					hKeyEnumBus,
					hKeyEnumTarget,
					hKeyEnumLogical,
					hKeyObject;
	CString			csSubKeyBus,
					csSubKeyTarget,
					csSubKeyLogical,
					csSubKey;
	TCHAR			szManufacturer[256],
					szModel[256],
					szName[256],
					szDescription[256],
					szType[256],
					szItem[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0,
					dwIndexEnumBus,
					dwIndexEnumTarget,
					dwIndexEnumLogical;
	LONG			lResult;
	FILETIME		MyFileTime;
	CStoragePeripheral	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	AddLog( _T( "Registry NT GetStoragePeripherals: Trying to find Floppy Drives in HKLM\\%s...\n"),
			NT_STORAGE_FLOPPY_KEY);
	// Windows NT => Open the floppy drive key
	if (RegOpenKeyEx( m_hKey, NT_STORAGE_FLOPPY_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szItem, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szItem[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_STORAGE_FLOPPY_KEY, szItem);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyEnumBus) == ERROR_SUCCESS)
			{
				dwLength = 255;
				dwIndexEnumBus = 0;
				while ((lResult = RegEnumKeyEx( hKeyEnumBus, dwIndexEnumBus, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each object, Try to open the device key
					szName[dwLength] = 0;
					bHaveToStore = FALSE;
					csSubKey.Format( _T( "%s\\%s\\%s"), NT_STORAGE_FLOPPY_KEY, szItem, szName);
					if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
					{
						_tcscpy( szManufacturer, NOT_AVAILABLE); 
						_tcscpy( szModel, NOT_AVAILABLE);
						_tcscpy( szName, NOT_AVAILABLE); 
						_tcscpy( szDescription, NOT_AVAILABLE); 
						_tcscpy( szType, NOT_AVAILABLE); 
						// Read the manufactuer
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, NT_STORAGE_FLOPPY_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
						{
							szManufacturer[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, NT_STORAGE_FLOPPY_MANUFACTURER_VALUE);
							_tcscpy( szManufacturer, NOT_AVAILABLE);
						}
						// Read the model
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, NT_STORAGE_FLOPPY_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
						{
							szModel[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, NT_STORAGE_FLOPPY_MODEL_VALUE);
							_tcscpy( szModel, NOT_AVAILABLE);
						}
						// Read the name
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, NT_STORAGE_FLOPPY_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
						{
							szName[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, NT_STORAGE_FLOPPY_NAME_VALUE);
							_tcscpy( szName, NOT_AVAILABLE);
						}
						// Read the description
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, NT_STORAGE_FLOPPY_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
						{
							szDescription[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, NT_STORAGE_FLOPPY_DESCRIPTION_VALUE);
							_tcscpy( szDescription, NOT_AVAILABLE);
						}
						// Read the type
						dwLength = 255;
						if (RegQueryValueEx( hKeyObject, NT_STORAGE_FLOPPY_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
						{
							szType[dwLength]=0;
							bHaveToStore = TRUE;
						}
						else
						{
							if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									csSubKey, NT_STORAGE_FLOPPY_TYPE_VALUE);
							_tcscpy( szType, NOT_AVAILABLE);
						}
						RegCloseKey( hKeyObject);
						myObject.Set( szType, szManufacturer, szName, szModel, szDescription);
						// Add the device to the adapter list
						if (bHaveToStore)
						{
							pList->AddTail( myObject);
							uIndex ++;
						}
					}
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								csSubKey);
					// Enum the next device
					dwLength = 255;
					dwIndexEnumBus++;
				}
				RegCloseKey( hKeyEnumBus);
				if (dwIndexEnumBus == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKey);
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
						csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_STORAGE_FLOPPY_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_STORAGE_FLOPPY_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetStoragePeripherals: Find Floppy Drives OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetStoragePeripherals: Find Floppy Drives failed because no valid object !\n"));

	AddLog( _T( "Registry NT GetStoragePeripherals: Trying to find Other Drives in HKLM\\%s...\n"),
			NT_STORAGE_OTHER_KEY);
	// Windows NT => Open the other drive key
	uIndex = 0;
	if (RegOpenKeyEx( m_hKey, NT_STORAGE_OTHER_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find SCSI port
		dwLength = 255;
		dwIndexEnum = 0;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szItem, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the SCSI bus key
			szItem[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKeyBus.Format( _T( "%s\\%s"), NT_STORAGE_OTHER_KEY, szItem);
			if (RegOpenKeyEx( m_hKey, csSubKeyBus, 0, KEY_READ, &hKeyEnumBus) == ERROR_SUCCESS)
			{
				// Enum the device subkeys to find SCSI target
				dwLength = 255;
				dwIndexEnumBus = 0;
				while ((lResult = RegEnumKeyEx( hKeyEnumBus, dwIndexEnumBus, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
				{
					// For each object, Try to open the SCSI traget key
					szName[dwLength] = 0;
					bHaveToStore = FALSE;
					csSubKeyTarget.Format( _T( "%s\\%s"), csSubKeyBus, szName);
					if (RegOpenKeyEx( m_hKey, csSubKeyTarget, 0, KEY_READ, &hKeyEnumTarget) == ERROR_SUCCESS)
					{
						// Enum the device subkeys to find SCSI target
						dwLength = 255;
						dwIndexEnumTarget = 0;
						while ((lResult = RegEnumKeyEx( hKeyEnumTarget, dwIndexEnumTarget, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
						{
							// For each object, Try to open the SCSI traget key
							szName[dwLength] = 0;
							bHaveToStore = FALSE;
							csSubKeyLogical.Format( _T( "%s\\%s"), csSubKeyTarget, szName);
							if (RegOpenKeyEx( m_hKey, csSubKeyLogical, 0, KEY_READ, &hKeyEnumLogical) == ERROR_SUCCESS)
							{
								// Enum the device subkeys to find SCSI logical unit
								dwLength = 255;
								dwIndexEnumLogical = 0;
								while ((lResult = RegEnumKeyEx( hKeyEnumLogical, dwIndexEnumLogical, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
								{
									// For each object, Try to open the SCSI logical unit key
									szName[dwLength] = 0;
									bHaveToStore = FALSE;
									csSubKey.Format( _T( "%s\\%s"), csSubKeyLogical, szName);
									if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
									{
										_tcscpy( szManufacturer, NOT_AVAILABLE); 
										_tcscpy( szModel, NOT_AVAILABLE);
										_tcscpy( szName, NOT_AVAILABLE); 
										_tcscpy( szDescription, NOT_AVAILABLE); 
										_tcscpy( szType, NOT_AVAILABLE); 
										// Read the manufactuer
										dwLength = 255;
										if (RegQueryValueEx( hKeyObject, NT_STORAGE_OTHER_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
										{
											szManufacturer[dwLength]=0;
											bHaveToStore = TRUE;
										}
										else
										{
											if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													csSubKey, NT_STORAGE_OTHER_MANUFACTURER_VALUE);
											_tcscpy( szManufacturer, NOT_AVAILABLE);
										}
										// Read the model
										dwLength = 255;
										if (RegQueryValueEx( hKeyObject, NT_STORAGE_OTHER_MODEL_VALUE, 0, &dwType, (LPBYTE) szModel, &dwLength) == ERROR_SUCCESS)
										{
											szModel[dwLength]=0;
											bHaveToStore = TRUE;
										}
										else
										{
											if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													csSubKey, NT_STORAGE_OTHER_MODEL_VALUE);
											_tcscpy( szModel, NOT_AVAILABLE);
										}
										// Read the name
										dwLength = 255;
										if (RegQueryValueEx( hKeyObject, NT_STORAGE_OTHER_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
										{
											szName[dwLength]=0;
											bHaveToStore = TRUE;
										}
										else
										{
											if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													csSubKey, NT_STORAGE_OTHER_NAME_VALUE);
											_tcscpy( szName, NOT_AVAILABLE);
										}
										// Read the description
										dwLength = 255;
										if (RegQueryValueEx( hKeyObject, NT_STORAGE_OTHER_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
										{
											szDescription[dwLength]=0;
											bHaveToStore = TRUE;
										}
										else
										{
											if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													csSubKey, NT_STORAGE_OTHER_DESCRIPTION_VALUE);
											_tcscpy( szDescription, NOT_AVAILABLE);
										}
										// Read the type
										dwLength = 255;
										if (RegQueryValueEx( hKeyObject, NT_STORAGE_OTHER_TYPE_VALUE, 0, &dwType, (LPBYTE) szType, &dwLength) == ERROR_SUCCESS)
										{
											szType[dwLength]=0;
											bHaveToStore = TRUE;
										}
										else
										{
											if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
													csSubKey, NT_STORAGE_OTHER_TYPE_VALUE);
											_tcscpy( szType, NOT_AVAILABLE);
										}
										RegCloseKey( hKeyObject);
										myObject.Set( szType, szManufacturer, szName, szModel, szDescription);
										// Add the device to the adapter list
										if (bHaveToStore)
										{
											pList->AddTail( myObject);
											uIndex ++;
										}
									} // If RegOpenKey Object
									else
										AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
												csSubKey);
									// Enum the next logical unit
									dwIndexEnumLogical++;
								} // While RegEnumKey Logical unit
								RegCloseKey( hKeyEnumLogical);
								if (dwIndexEnumLogical == 0)
									// No key found
									AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
											csSubKeyLogical);
							} // if RegOpenKey Logical unit
							else
								AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
										csSubKeyLogical);
							// Enum next target
							dwLength = 255;
							dwIndexEnumTarget++;
						} // While RegEnumKey Target
						RegCloseKey( hKeyEnumTarget);
						if (dwIndexEnumTarget == 0)
							// No key found
							AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
									csSubKeyTarget);
					} // If RegOpenKey Target
					else
						AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								csSubKeyTarget);
					// Enum next bux
					dwLength = 255;
					dwIndexEnumBus++;
				} // While RegEnumKey Bus
				RegCloseKey( hKeyEnumBus);
				if (dwIndexEnumBus == 0)
					// No key found
					AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
							csSubKeyBus);
			} // If RegOpenKey Bus
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
						csSubKeyBus);
			// Enum the next port
			dwLength = 255;
			dwIndexEnum++;
		} // While RegEnumKey Port
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_STORAGE_OTHER_KEY);
	} // If RegOpenKey Port
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_STORAGE_OTHER_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetStoragePeripherals: Find Other Drives OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetStoragePeripherals: Find Other Drives failed because no valid object !\n"));

	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry NT GetStoragePeripherals: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry NT GetStoragePeripherals: Failed because no storage peripherals found.\n"));
	return FALSE;
}

BOOL CRegistry::GetRegistryApplications(CSoftwareList *pList, BOOL hkcu)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get BIOS Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		if( hkcu )
			GetRegistryApplications9X( pList,HKEY_CURRENT_USER);
		return GetRegistryApplications9X( pList,HKEY_LOCAL_MACHINE);

	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		if( hkcu )
			GetRegistryApplicationsNT( pList,HKEY_CURRENT_USER);
		return GetRegistryApplicationsNT( pList,HKEY_LOCAL_MACHINE);
	default:
		// Unknown
		AddLog( _T( "Registry GetRegistryApplications...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetRegistryApplications9X(CSoftwareList *pList, HKEY__* curHive)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szPublisher[256],
					szName[256],
					szVersion[256],
					szFolder[256],
					szComments[256],
					szGUID[256],
					szLanguage[256],
					szUninstall[1000];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSoftware		cApp;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	CString csCurHive = (curHive==HKEY_LOCAL_MACHINE? "HKLM" : "HKCU") ;
	AddLog( _T( "Registry 9X GetRegistryApplications READING hive %s  ... \n"),csCurHive);
	// Windows 9X => Open the Apps key
	if (RegOpenKeyEx( curHive, WIN_APPS_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find installed apps
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szGUID, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szGUID[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_APPS_KEY, szGUID);
			if (RegOpenKeyEx( curHive, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szPublisher, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				_tcscpy( szFolder, NOT_AVAILABLE); 
				_tcscpy( szComments, NOT_AVAILABLE);
				_tcscpy( szLanguage, NOT_AVAILABLE);
				// Read the Publisher
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_VENDOR_VALUE, 0, &dwType, (LPBYTE) szPublisher, &dwLength) == ERROR_SUCCESS)
				{
					szPublisher[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_VENDOR_VALUE);
					_tcscpy( szPublisher, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the version
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				// Read the folder
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_FOLDER_VALUE, 0, &dwType, (LPBYTE) szFolder, &dwLength) == ERROR_SUCCESS)
				{
					szFolder[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_FOLDER_VALUE);
					_tcscpy( szFolder, NOT_AVAILABLE);
				}
				// Read the comment
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_COMMENTS_VALUE, 0, &dwType, (LPBYTE) szComments, &dwLength) == ERROR_SUCCESS)
				{
					szComments[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_COMMENTS_VALUE);
					_tcscpy( szComments, NOT_AVAILABLE);
				}
				// Read the language, this gives the language of the installation tool not of the application itself!
				dwLength = 255;
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, WIN_APPS_LANGUAGE_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
				    DWORD nSize = 256;
					TCHAR lpData[256];
					DWORD nResult;

					nResult = VerLanguageName(dwValue, lpData, nSize);
					if ((nResult != 0) && (nResult < nSize - 1))
						_tcscpy( szLanguage, lpData);
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_LANGUAGE_VALUE);
					_tcscpy( szLanguage, NOT_AVAILABLE);
				}
				// Read the uninstall string
				dwLength = 999;
				if ((RegQueryValueEx( hKeyObject, WIN_APPS_UNINSTALL_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS) &&
					(RegQueryValueEx( hKeyObject, WIN_APPS_QUIETUNINSTALL_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS) &&
					(RegQueryValueEx( hKeyObject, WIN_APPS_MODIFY_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS))
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, WIN_APPS_UNINSTALL_VALUE);
					bHaveToStore = FALSE;
				}
				RegCloseKey( hKeyObject);
				cApp.Clear();
				cApp.Set( szPublisher, szName, szVersion, szFolder, szComments, NOT_AVAILABLE, 0, TRUE);
				cApp.SetGUID(szGUID);
				cApp.SetLanguage(szLanguage);
				// Add the app to the apps list
				if (bHaveToStore)
				{
					pList->AddTail( cApp);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for %s\\%s !\n"),csCurHive,
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetRegistryApplications: Failed in call to <RegEnumKeyEx> function to find subkey of %s\\%s.\n"),csCurHive,
					WIN_APPS_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetRegistryApplications: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetRegistryApplications: Failed in call to <RegOpenKeyEx> function for %s\\%s !\n"),csCurHive,
				WIN_APPS_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetRegistryApplicationsNT(CSoftwareList *pList, HKEY__* curHive )
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szPublisher[256],
					szName[256],
					szVersion[256],
					szFolder[256],
					szComments[256],
 					szGUID[256],
 					szLanguage[256],
					szUninstall[1000];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSoftware		cApp;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	CString csCurHive = (curHive==HKEY_LOCAL_MACHINE? "HKLM" : "HKCU") ;
	AddLog( _T( "Registry NT GetRegistryApplications READING hive %s  ... \n"),csCurHive);	
	// Windows NT => Open the Apps key
	if (RegOpenKeyEx( curHive, NT_APPS_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find installed apps
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szGUID, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szGUID[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_APPS_KEY, szGUID);
			if (RegOpenKeyEx( curHive, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szPublisher, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE); 
				_tcscpy( szVersion, NOT_AVAILABLE);
				_tcscpy( szFolder, NOT_AVAILABLE); 
				_tcscpy( szComments, NOT_AVAILABLE);
				_tcscpy( szLanguage, NOT_AVAILABLE);
				// Read the Publisher
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_APPS_VENDOR_VALUE, 0, &dwType, (LPBYTE) szPublisher, &dwLength) == ERROR_SUCCESS)
				{
					szPublisher[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_VENDOR_VALUE);
					_tcscpy( szPublisher, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_APPS_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the version
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_APPS_VERSION_VALUE, 0, &dwType, (LPBYTE) szVersion, &dwLength) == ERROR_SUCCESS)
				{
					szVersion[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_VERSION_VALUE);
					_tcscpy( szVersion, NOT_AVAILABLE);
				}
				// Read the folder
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_APPS_FOLDER_VALUE, 0, &dwType, (LPBYTE) szFolder, &dwLength) == ERROR_SUCCESS)
				{
					szFolder[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_FOLDER_VALUE);
					_tcscpy( szFolder, NOT_AVAILABLE);
				}
				// Read the comment
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_APPS_COMMENTS_VALUE, 0, &dwType, (LPBYTE) szComments, &dwLength) == ERROR_SUCCESS)
				{
					szComments[dwLength]=0;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_COMMENTS_VALUE);
					_tcscpy( szComments, NOT_AVAILABLE);
				}
				// Read the language, this gives the language of the installation tool not of the application itself!
 				dwLength = 255;
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, NT_APPS_LANGUAGE_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
					DWORD nSize = 256;
					TCHAR lpData[256];
					DWORD nResult;

					nResult = VerLanguageName(dwValue, lpData, nSize);
					if ((nResult != 0) && (nResult < nSize - 1))
						_tcscpy( szLanguage, lpData);
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
										csSubKey, NT_APPS_LANGUAGE_VALUE);
					_tcscpy( szLanguage, NOT_AVAILABLE);
				}
				// Read the uninstall string
				dwLength = 999;
				if ((RegQueryValueEx( hKeyObject, NT_APPS_UNINSTALL_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS) &&
					(RegQueryValueEx( hKeyObject, NT_APPS_QUIETUNINSTALL_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS) &&
					(RegQueryValueEx( hKeyObject, NT_APPS_MODIFY_VALUE, 0, &dwType, (LPBYTE) szUninstall, &dwLength) != ERROR_SUCCESS))
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for %s\\%s\\%s !\n"),csCurHive,
									   csSubKey, NT_APPS_UNINSTALL_VALUE);
					bHaveToStore = FALSE;
				}
				RegCloseKey( hKeyObject);
				cApp.Clear();
				cApp.Set( szPublisher, szName, szVersion, szFolder, szComments, NOT_AVAILABLE, 0, TRUE);
				cApp.SetGUID(szGUID);
				cApp.SetLanguage(szLanguage);
				// Add the app to the apps list
				if (bHaveToStore)
				{
					pList->AddTail( cApp);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for %s\\%s !\n"),csCurHive,
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetRegistryApplications: Failed in call to <RegEnumKeyEx> function to find subkey of %s\\%s.\n"),csCurHive,
					NT_APPS_KEY);
		else
			AddLog( _T( "Registry NT GetRegistryApplications: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetRegistryApplications: Failed in call to <RegOpenKeyEx> function for %s\\%s !\n"),csCurHive,
				NT_APPS_KEY);
	return !pList->IsEmpty();
}

LPCTSTR CRegistry::GetDeviceDescription()
{
	// Try to get Modems Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetDeviceDescription9X();
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetDeviceDescriptionNT();
	default:
		// Unknown
		AddLog( _T( "Registry GetDeviceDescription...Failed because unsupported or unrecognized OS !\n"));
		return NULL;
	}
	return NULL;
}

LPCTSTR CRegistry::GetDeviceDescription9X()
{
	static TCHAR szDeviceDescription[256];
	HKEY		 hKey = NULL;

	_stprintf( szDeviceDescription, NOT_AVAILABLE);
	AddLog( _T( "Registry 9X/Me GetDeviceDescription..."));
	LONG lResult = RegOpenKeyEx( m_hKey, WIN_COMPUTER_DESCRIPTION_KEY, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				WIN_COMPUTER_DESCRIPTION_KEY);
		return szDeviceDescription;
	}

	// Get description.
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	lResult = RegQueryValueEx( hKey, WIN_COMPUTER_DESCRIPTION_VALUE, NULL, &dwType, (LPBYTE) szDeviceDescription, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				WIN_COMPUTER_DESCRIPTION_KEY,
				WIN_COMPUTER_DESCRIPTION_VALUE);
		RegCloseKey( hKey);
		return szDeviceDescription;
	}
	RegCloseKey( hKey);
	szDeviceDescription[dwSize]=0;
	AddLog( _T( "OK (%s).\n"), szDeviceDescription);
	return szDeviceDescription;
}

LPCTSTR CRegistry::GetDeviceDescriptionNT()
{
	static TCHAR szDeviceDescription[256];
	HKEY		 hKey = NULL;

	_stprintf( szDeviceDescription, NOT_AVAILABLE);
	AddLog( _T( "Registry NT GetDeviceDescription..."));
	LONG lResult = RegOpenKeyEx( m_hKey, NT_COMPUTER_DESCRIPTION_KEY, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				NT_COMPUTER_DESCRIPTION_KEY);
		return szDeviceDescription;
	}

	// Get description.
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	lResult = RegQueryValueEx( hKey, NT_COMPUTER_DESCRIPTION_VALUE, NULL, &dwType, (LPBYTE) szDeviceDescription, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				NT_COMPUTER_DESCRIPTION_KEY,
				NT_COMPUTER_DESCRIPTION_VALUE);
		RegCloseKey( hKey);
		return szDeviceDescription;
	}
	RegCloseKey( hKey);
	szDeviceDescription[dwSize]=0;
	AddLog( _T( "OK (%s).\n"), szDeviceDescription);
	return szDeviceDescription;
}

BOOL CRegistry::GetDomainOrWorkgroup(CString &csDomain)
{
	// Try to get Modems Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetDomainOrWorkgroup9X( csDomain);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetDomainOrWorkgroupNT( csDomain);
	default:
		// Unknown
		csDomain = NOT_AVAILABLE;
		AddLog( _T( "Registry GetDomainOrWorkgroup...Failed because unsupported or unrecognized OS !\n"));
		return NULL;
	}
	return NULL;
}

BOOL CRegistry::GetDomainOrWorkgroup9X(CString &csDomain)
{
	TCHAR szDomain[256];
	HKEY  hKey = NULL;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;

	csDomain = NOT_AVAILABLE;
	AddLog( _T( "Registry 9X/Me GetDomainOrWorkgroup: Trying to get Domain name..."));
	// Try to get domain name
	LONG lResult = RegOpenKeyEx( m_hKey, WIN_DOMAIN_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get domain.
		lResult = RegQueryValueEx( hKey, WIN_DOMAIN_VALUE, NULL, &dwType, (LPBYTE) szDomain, &dwSize);
		if (lResult == ERROR_SUCCESS)
		{
			szDomain[dwSize]=0;
			csDomain = szDomain;
			RegCloseKey( hKey);
			AddLog( _T( "OK (%s).\n"), csDomain);
			return TRUE;
		}
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				WIN_DOMAIN_KEY,
				WIN_DOMAIN_VALUE);
		RegCloseKey( hKey);
	}
	else
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				WIN_DOMAIN_KEY);
	// Failed to get domain name => Try to get workgroup
	AddLog( _T( "Registry 9X/Me GetDomainOrWorkgroup: Trying to get workgroup name..."));
	lResult = RegOpenKeyEx( m_hKey, WIN_WORKGROUP_KEY, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				WIN_WORKGROUP_KEY);
		return FALSE;
	}
	// Get workgroup.
	dwType = REG_SZ;
	dwSize = 255;
	lResult = RegQueryValueEx( hKey, WIN_WORKGROUP_VALUE, NULL, &dwType, (LPBYTE) szDomain, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				WIN_WORKGROUP_KEY,
				WIN_WORKGROUP_VALUE);
		RegCloseKey( hKey);
		return FALSE;
	}
	RegCloseKey( hKey);
	szDomain[dwSize]=0;
	csDomain = szDomain;
	AddLog( _T( "OK (%s).\n"), csDomain);
	return TRUE;
}

BOOL CRegistry::GetDomainOrWorkgroupNT(CString &csDomain)
{
	TCHAR szDomain[256];
	HKEY  hKey = NULL;

	csDomain = NOT_AVAILABLE;
	AddLog( _T( "Registry NT GetDomainOrWorkgroup..."));
	LONG lResult = RegOpenKeyEx( m_hKey, NT_DOMAIN_KEY, 0, KEY_READ, &hKey);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				NT_DOMAIN_KEY);
		return FALSE;
	}

	// Get domain name or workgroup.
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;
	lResult = RegQueryValueEx( hKey, NT_DOMAIN_VALUE, NULL, &dwType, (LPBYTE) szDomain, &dwSize);
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				NT_DOMAIN_KEY,
				NT_DOMAIN_VALUE);
		RegCloseKey( hKey);
		return FALSE;
	}
	RegCloseKey( hKey);
	szDomain[dwSize]=0;
	csDomain = szDomain;
	AddLog( _T( "OK (%s).\n"), csDomain);
	return TRUE;
}

BOOL CRegistry::GetWindowsRegistration(CString &csCompany, CString &csOwner, CString &csProductID)
{
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetWindowsRegistration9X( csCompany, csOwner, csProductID);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetWindowsRegistrationNT( csCompany, csOwner, csProductID);
	default:
		// Unknown
		csCompany = NOT_AVAILABLE;
		csOwner = NOT_AVAILABLE;
		csProductID = NOT_AVAILABLE;
		AddLog( _T( "Registry GetWindowsRegistration...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetWindowsRegistration9X(CString &csCompany, CString &csOwner, CString &csProductID)
{
	HKEY			hKeyObject;
	CString			csSubKey;
	TCHAR			szCompany[256],
					szOwner[256],
					szProductID[256];
	DWORD			dwLength,
					dwType;

	AddLog( _T( "Registry 9X/Me GetWindowsRegistration...\n"));
	_tcscpy( szCompany, NOT_AVAILABLE); 
	_tcscpy( szOwner, NOT_AVAILABLE);
	_tcscpy( szProductID, NOT_AVAILABLE);
	// Windows 9X => Open the registration key
	if (RegOpenKeyEx( m_hKey, WIN_REGISTRATION_KEY, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
	{
		// Read the company name
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, WIN_REGISTRATION_COMPANY_VALUE, 0, &dwType, (LPBYTE) szCompany, &dwLength) == ERROR_SUCCESS)
		{
			szCompany[dwLength]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   WIN_REGISTRATION_KEY, WIN_REGISTRATION_COMPANY_VALUE);
			_tcscpy( szCompany, NOT_AVAILABLE);
		}
		// Read the user
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, WIN_REGISTRATION_OWNER_VALUE, 0, &dwType, (LPBYTE) szOwner, &dwLength) == ERROR_SUCCESS)
		{
			szOwner[dwLength+1]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   WIN_REGISTRATION_KEY, WIN_REGISTRATION_OWNER_VALUE);
			_tcscpy( szOwner, NOT_AVAILABLE);
		}
		// Read the productID
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, WIN_REGISTRATION_PRODUCT_ID_VALUE, 0, &dwType, (LPBYTE) szProductID, &dwLength) == ERROR_SUCCESS)
		{
			szProductID[dwLength+1]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   WIN_REGISTRATION_KEY, WIN_REGISTRATION_PRODUCT_ID_VALUE);
			_tcscpy( szProductID, NOT_AVAILABLE);
		}
		RegCloseKey( hKeyObject);
		// Add the device to the adapter list
		csCompany = szCompany;
		StrForSQL( csCompany);
		csOwner = szOwner;
		StrForSQL( csOwner);
		csProductID = szProductID;
		StrForSQL( csProductID);
		AddLog( _T( "Registry 9X/Me GetWindowsRegistration: OK (%s %s %s).\n"),
				csCompany, csOwner, csProductID);
		return TRUE;
	}
	AddLog( _T( "Registry 9X/Me GetWindowsRegistration: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
			WIN_REGISTRATION_KEY);
	return FALSE;
}

BOOL CRegistry::GetWindowsProductKey(CString &productKey)
{
	char *KeyPath = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
	char *KeyValue = "DigitalProductId";

	char KeyChars[24] = {'B','C','D','F','G','H','J','K','M','P','Q','R','T','V','W','X','Y','2','3','4','6','7','8','9'};

	char Result[30];
	
	// Registry access variables
	HKEY InfoKey = NULL;
	DWORD InfoType = 0;

	// Decoding variables
	BYTE Data[0xA7];
	BYTE BinaryKey[15]; // Part of raw data contains the binary Product Key
	char DecodedKey[25]; // Decoded Product Key is placed here
	DWORD DataSize = sizeof( Data );
	UINT A;
	int i,j;

	AddLog( _T( "Registry GetWindowsProductKey..."));

	//Requete registry
	if( RegOpenKeyEx( HKEY_LOCAL_MACHINE, LPCTSTR(KeyPath), 0, KEY_READ, &InfoKey ) == ERROR_SUCCESS )
	{
		if( RegQueryValueEx(InfoKey, KeyValue, NULL, &InfoType, Data, &DataSize) == ERROR_SUCCESS )
		{
			// We need 15 bytes from $35 in BinaryKey
			memcpy( BinaryKey, &Data[0x34], sizeof(BinaryKey));

			for( i=24; i>=0; i-- ){
				A = 0;
				// decoding the current symbol
				for( j=14; j>=0; j-- ){
					A = ((A<<8) + BinaryKey[j]);
					BinaryKey[j] = int(A / 24);
					A = A % 24;
				}
				DecodedKey[i] = KeyChars[A];
			}

			
			j=0;
			for( i=0; i<25; i++ ){
				strcpy(&Result[j],&DecodedKey[i]);
				j++;
				if ( ((i + 1) % 5 == 0) && (i < 24) ){
					strcpy(&Result[j],"-");
					j++;
				}
			}

			Result[29]='\0';
			productKey = Result;

			AddLog( _T( "OK (%s).\n"),
				productKey);

			return TRUE;
		}
		else{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s !\n"), KeyValue);
		}
	}
	else{
		AddLog( _T( "Registry GetWindowsProductKey: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
			KeyPath);
	}
	return FALSE;
}

BOOL CRegistry::GetWindowsRegistrationNT(CString &csCompany, CString &csOwner, CString &csProductID)
{
	HKEY			hKeyObject;
	CString			csSubKey;
	TCHAR			szCompany[256],
					szOwner[256],
					szProductID[256];
	DWORD			dwLength,
					dwType;

	AddLog( _T( "Registry NT GetWindowsRegistration...\n"));
	_tcscpy( szCompany, NOT_AVAILABLE); 
	_tcscpy( szOwner, NOT_AVAILABLE);
	_tcscpy( szProductID, NOT_AVAILABLE);
	// Windows NT => Open the registration key
	if (RegOpenKeyEx( m_hKey, NT_REGISTRATION_KEY, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
	{
		// Read the company name
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, NT_REGISTRATION_COMPANY_VALUE, 0, &dwType, (LPBYTE) szCompany, &dwLength) == ERROR_SUCCESS)
		{
			szCompany[dwLength]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   NT_REGISTRATION_KEY, NT_REGISTRATION_COMPANY_VALUE);
			_tcscpy( szCompany, NOT_AVAILABLE);
		}
		// Read the user
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, NT_REGISTRATION_OWNER_VALUE, 0, &dwType, (LPBYTE) szOwner, &dwLength) == ERROR_SUCCESS)
		{
			szOwner[dwLength+1]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   NT_REGISTRATION_KEY, NT_REGISTRATION_OWNER_VALUE);
			_tcscpy( szOwner, NOT_AVAILABLE);
		}
		// Read the productID
		dwLength = 255;
		if (RegQueryValueEx( hKeyObject, NT_REGISTRATION_PRODUCT_ID_VALUE, 0, &dwType, (LPBYTE) szProductID, &dwLength) == ERROR_SUCCESS)
		{
			szProductID[dwLength+1]=0;
		}
		else
		{
			if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
							   NT_REGISTRATION_KEY, NT_REGISTRATION_PRODUCT_ID_VALUE);
			_tcscpy( szProductID, NOT_AVAILABLE);
		}
		RegCloseKey( hKeyObject);
		// Add the device to the adapter list
		csCompany = szCompany;
		StrForSQL( csCompany);
		csOwner = szOwner;
		StrForSQL( csOwner);
		csProductID = szProductID;
		StrForSQL( csProductID);
		AddLog( _T( "Registry NT GetWindowsRegistration: OK (%s %s %s).\n"),
				csCompany, csOwner, csProductID);
		return TRUE;
	}
	AddLog( _T( "Registry NT GetWindowsRegistration: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
			NT_REGISTRATION_KEY);
	return FALSE;
}

BOOL CRegistry::GetLoggedOnUser(CString &csUser)
{
	// Try to get Modems Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetLoggedOnUser9X( csUser);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetLoggedOnUserNT( csUser);
	default:
		// Unknown
		csUser = NOT_AVAILABLE;
		AddLog( _T( "Registry GetLoggedOnUser...Failed because unsupported or unrecognized OS !\n"));
		return NULL;
	}
	return NULL;
}

BOOL CRegistry::GetLastLoggedUser(CString &csLastLoggedUser)
{
	TCHAR szLastLoggedUser[256];
	HKEY  hKey = NULL;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;

  	AddLog( _T( "Registry NT GetLastLoggerUser: Trying to get the last user who'd been logged in..."));
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, NT_LASTLOGGEDUSER_USER_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get user name.
		lResult = RegQueryValueEx( hKey, NT_LASTLOGGEDUSER_USER_VALUE, NULL, &dwType, (LPBYTE) szLastLoggedUser, &dwSize);
		if (lResult == ERROR_SUCCESS)
		{
			szLastLoggedUser[dwSize]=0;
			csLastLoggedUser = szLastLoggedUser;
			RegCloseKey( hKey);
			AddLog( _T( "OK (%s).\n"), csLastLoggedUser);
			return TRUE;
		}
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				NT_LASTLOGGEDUSER_USER_KEY,
				NT_LASTLOGGEDUSER_USER_VALUE);
		RegCloseKey( hKey);
	}
	else
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKCU\\%s !\n"),
				NT_LASTLOGGEDUSER_USER_VALUE);
	return FALSE;
}

BOOL CRegistry::GetLoggedOnUser9X(CString &csUser)
{
	TCHAR szUser[256];
	HKEY  hKey = NULL;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;

	csUser = NOT_AVAILABLE;
	AddLog( _T( "Registry 9X/Me GetLoggedOnUser: Trying to get Logon User Name..."));
	// Try to get logged on user
	LONG lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, WIN_LOGON_USER_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get user name.
		lResult = RegQueryValueEx( hKey, WIN_LOGON_USER_VALUE, NULL, &dwType, (LPBYTE) szUser, &dwSize);
		if (lResult == ERROR_SUCCESS)
		{
			szUser[dwSize]=0;
			csUser = szUser;
			RegCloseKey( hKey);
			AddLog( _T( "OK (%s).\n"), csUser);
			return TRUE;
		}
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
				WIN_LOGON_USER_KEY,
				WIN_LOGON_USER_VALUE);
		RegCloseKey( hKey);
	}
	else
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKLM\\%s !\n"),
				WIN_LOGON_USER_KEY);
	return FALSE;
}

BOOL CRegistry::GetLoggedOnUserNT(CString &csUser)
{
	TCHAR szUser[256];
	HKEY  hKey = NULL;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 255;

	csUser = NOT_AVAILABLE;
	AddLog( _T( "Registry NT GetLoggedOnUser: Trying to get Logon User Name..."));
	// Try to get logged on user
	LONG lResult = RegOpenKeyEx( HKEY_CURRENT_USER, NT_LOGON_USER_KEY, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		// Get user name.
		lResult = RegQueryValueEx( hKey, NT_LOGON_USER_VALUE, NULL, &dwType, (LPBYTE) szUser, &dwSize);
		if (lResult == ERROR_SUCCESS)
		{
			szUser[dwSize]=0;
			csUser = szUser;
			RegCloseKey( hKey);
			AddLog( _T( "OK (%s).\n"), csUser);
			return TRUE;
		}
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for HKCU\\%s\\%s !\n"),
				NT_LOGON_USER_KEY,
				NT_LOGON_USER_VALUE);
		RegCloseKey( hKey);
	}
	else
		AddLog( _T( "Failed in call to <RegOpenKey> function for HKCU\\%s !\n"),
				NT_LOGON_USER_KEY);
	return FALSE;
}

BOOL CRegistry::GetRegistryValue( UINT uKeyTree, LPCTSTR lpstrSubKey, LPCTSTR lpstrValue, CString &csResult)
{
	BYTE	*lpValue = NULL;
	HKEY	hKey = NULL;
	LONG	lResult;
	LPCTSTR	pSZ;
	CString csSubKey = lpstrSubKey,
			csTemp;
	DWORD	dwCpt,
			dwType = REG_NONE,
			dwSize = 0,
			dwValue;
	csResult = NOT_AVAILABLE;
	
	switch (uKeyTree)
	{
	case HKCR_TREE: // HKEY_CLASSES_ROOT
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKCR"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_CLASSES_ROOT, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKCU_TREE: // HKEY_CURRENT_USER
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKCU"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_CURRENT_USER, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKLM_TREE: // HKEY_LOCAL_MACHINE
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKLM"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKU_TREE: // HKEY_USERS
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKU"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKCC_TREE: // HKEY_CURRENT_CONFIG
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKCC"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKDD_TRE: // HKEY_DYN_DATA (9X only)
		AddLog( _T( "Registry GetRegistryValue (%s\\%s\\%s)..."),
			_T( "HKDD"),
			csSubKey,
			lpstrValue);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	default: // Error
		AddLog( _T( "Registry GetRegistryValue...Failed because unrecognized Registry Tree %u !\n"), uKeyTree);
		return FALSE;
	}
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "Failed in call to <RegOpenKey> function for subkey %s of selected hive !\n"),
				csSubKey);
		return FALSE;
	}
	// Get value size and type
	if ((lResult = RegQueryValueEx( hKey, lpstrValue, NULL, &dwType, (LPBYTE) &dwValue, &dwSize)) != ERROR_MORE_DATA)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to get value size)!\n"),
				csSubKey,
				lpstrValue);
		RegCloseKey( hKey);
		return FALSE;
	}
	// Allocate value buffer
	if ((lpValue = (LPBYTE)malloc( (dwSize+1)*sizeof( BYTE))) == NULL)
	{
		AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to allocate value size)!\n"),
				csSubKey,
				lpstrValue);
		RegCloseKey( hKey);
		return FALSE;
	}
	// Get value
	switch (dwType)
	{
	case REG_DWORD:
		if ((lResult = RegQueryValueEx( hKey, lpstrValue, NULL, &dwType, (LPBYTE) &dwValue, &dwSize)) != ERROR_SUCCESS)
		{
			AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to get value)!\n"),
					csSubKey,
					lpstrValue);
			RegCloseKey( hKey);
			free( lpValue);
			return FALSE;
		}
		csResult.Format( _T( "%lu"), dwValue);
		break;
	case REG_SZ:
	case REG_EXPAND_SZ:
		if ((lResult = RegQueryValueEx( hKey, lpstrValue, NULL, &dwType, (LPBYTE) lpValue, &dwSize)) != ERROR_SUCCESS)
		{
			AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to get value)!\n"),
					csSubKey,
					lpstrValue);
			RegCloseKey( hKey);
			free( lpValue);
			return FALSE;
		}
		lpValue[dwSize]=0;
		csResult = (LPCTSTR) lpValue;
		break;
	case REG_MULTI_SZ:
		if ((lResult = RegQueryValueEx( hKey, lpstrValue, NULL, &dwType, (LPBYTE) lpValue, &dwSize)) != ERROR_SUCCESS)
		{
			AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to get value)!\n"),
					csSubKey,
					lpstrValue);
			RegCloseKey( hKey);
			free( lpValue);
			return FALSE;
		}
		lpValue[dwSize]=0;
		// Parse multistring registry value
		pSZ = ParseMultiSZ( (LPCTSTR) lpValue);
		if (pSZ != NULL)
			csResult.Empty();
		while (pSZ != NULL)
		{
			csResult += pSZ;
			csResult += _T( " ");
			pSZ = ParseMultiSZ();
		}
		break;
	case REG_BINARY:
		if ((lResult = RegQueryValueEx( hKey, lpstrValue, NULL, &dwType, (LPBYTE) lpValue, &dwSize)) != ERROR_SUCCESS)
		{
			AddLog( _T( "Failed in call to <RegQueryValueEx> function for value %s\\%s of selected hive (unable to get value)!\n"),
					csSubKey,
					lpstrValue);
			RegCloseKey( hKey);
			free( lpValue);
			return FALSE;
		}
		lpValue[dwSize]=0;
		if (dwSize > 0)
			csResult.Empty();
		for (dwCpt=0; dwCpt<dwSize; dwCpt++)
		{
			csTemp.Format( _T( "%.02X "), lpValue[ dwCpt]);
			csResult += csTemp;
		}
		break;
	default:
    	RegCloseKey( hKey);
		free( lpValue);
		AddLog( _T( "Failed because Registry type %lu unhandled !\n"), dwType);
		return FALSE;
	}
	RegCloseKey( hKey);
	free( lpValue);
	AddLog( _T( "OK (%s).\n"), csResult);
	return TRUE;
}

BOOL CRegistry::GetInputDevices(CInputDeviceList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get system Controllers Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetInputDevices9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetInputDevicesNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetInputDevices...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetInputDevices9X(CInputDeviceList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szManufacturer[256],
					szCaption[256],
					szDescription[256],
					szPointingType[256],
					szPointingInterface[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CInputDevice	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	// Windows 9X => Open the keyboard key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetInputDevices: Trying to find Keyboards in HKLM\\%s...\n"),
			WIN_INPUT_KEYBOARD_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_INPUT_KEYBOARD_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szManufacturer, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szManufacturer[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_INPUT_KEYBOARD_KEY, szManufacturer);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szPointingType, NOT_AVAILABLE);
				_tcscpy( szPointingInterface, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the pointing type
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_TYPE_VALUE, 0, &dwType, (LPBYTE) szPointingType, &dwLength) == ERROR_SUCCESS)
				{
					szPointingType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_TYPE_VALUE);
					_tcscpy( szPointingType, NOT_AVAILABLE);
				}
				// Read the pointing interface
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_INTERFACE_VALUE, 0, &dwType, (LPBYTE) szPointingInterface, &dwLength) == ERROR_SUCCESS)
				{
					szPointingInterface[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_INTERFACE_VALUE);
					_tcscpy( szPointingInterface, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( INPUT_DEVICE_KEYBOARD, szManufacturer, szCaption, szDescription, szPointingType, szPointingInterface);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_INPUT_KEYBOARD_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_INPUT_KEYBOARD_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetInputDevices: Find Keyboards OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetInputDevices: Find Keyboards failed because no valid object !\n"));
	// Windows 9X => Open the Pointing Devices key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry 9X/Me GetInputDevices: Trying to find Pointing Devices in HKLM\\%s...\n"),
			WIN_INPUT_POINTING_KEY);
	if (RegOpenKeyEx( m_hKey, WIN_INPUT_POINTING_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szManufacturer, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szManufacturer[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_INPUT_POINTING_KEY, szManufacturer);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szPointingType, NOT_AVAILABLE);
				_tcscpy( szPointingInterface, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the pointing type
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_TYPE_VALUE, 0, &dwType, (LPBYTE) szPointingType, &dwLength) == ERROR_SUCCESS)
				{
					szPointingType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_TYPE_VALUE);
					_tcscpy( szPointingType, NOT_AVAILABLE);
				}
				// Read the pointing interface
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_INPUT_KEYBOARD_INTERFACE_VALUE, 0, &dwType, (LPBYTE) szPointingInterface, &dwLength) == ERROR_SUCCESS)
				{
					szPointingInterface[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_INPUT_KEYBOARD_INTERFACE_VALUE);
					_tcscpy( szPointingInterface, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( INPUT_DEVICE_POINTING, szManufacturer, szCaption, szDescription, szPointingType, szPointingInterface);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_INPUT_POINTING_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_INPUT_POINTING_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry 9X/Me GetInputDevices: Find Pointing Devices OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetInputDevices: Find Pointing Devices failed because no valid object !\n"));
	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry 9X/Me GetInputDevices: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry 9X/Me GetInputDevices: Failed because no controler found.\n"));
	return FALSE;
}

BOOL CRegistry::GetInputDevicesNT(CInputDeviceList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szManufacturer[256],
					szCaption[256],
					szDescription[256],
					szPointingType[256],
					szPointingInterface[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CInputDevice	myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0,
					uTotalIndex = 0;

	// Windows NT => Open the keyboard key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetInputDevices: Trying to find Keyboards in HKLM\\%s...\n"),
			NT_INPUT_KEYBOARD_KEY);
	if (RegOpenKeyEx( m_hKey, NT_INPUT_KEYBOARD_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szManufacturer, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szManufacturer[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_INPUT_KEYBOARD_KEY, szManufacturer);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szPointingType, NOT_AVAILABLE);
				_tcscpy( szPointingInterface, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the pointing type
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_TYPE_VALUE, 0, &dwType, (LPBYTE) szPointingType, &dwLength) == ERROR_SUCCESS)
				{
					szPointingType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_TYPE_VALUE);
					_tcscpy( szPointingType, NOT_AVAILABLE);
				}
				// Read the pointing interface
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_INTERFACE_VALUE, 0, &dwType, (LPBYTE) szPointingInterface, &dwLength) == ERROR_SUCCESS)
				{
					szPointingInterface[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_INTERFACE_VALUE);
					_tcscpy( szPointingInterface, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( INPUT_DEVICE_KEYBOARD, szManufacturer, szCaption, szDescription, szPointingType, szPointingInterface);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_INPUT_KEYBOARD_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_INPUT_KEYBOARD_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetInputDevices: Find Keyboards OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetInputDevices: Find Keyboards failed because no valid object !\n"));
	// Windows NT => Open the Pointing Devices key
	uIndex = 0;
	dwIndexEnum = 0;
	AddLog( _T( "Registry NT GetInputDevices: Trying to find Pointing Devices in HKLM\\%s...\n"),
			NT_INPUT_POINTING_KEY);
	if (RegOpenKeyEx( m_hKey, NT_INPUT_POINTING_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szManufacturer, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szManufacturer[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_INPUT_POINTING_KEY, szManufacturer);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szManufacturer, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE); 
				_tcscpy( szDescription, NOT_AVAILABLE); 
				_tcscpy( szPointingType, NOT_AVAILABLE);
				_tcscpy( szPointingInterface, NOT_AVAILABLE);
				// Read the manufactuer
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_MANUFACTURER_VALUE, 0, &dwType, (LPBYTE) szManufacturer, &dwLength) == ERROR_SUCCESS)
				{
					szManufacturer[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_MANUFACTURER_VALUE);
					_tcscpy( szManufacturer, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				// Read the pointing type
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_TYPE_VALUE, 0, &dwType, (LPBYTE) szPointingType, &dwLength) == ERROR_SUCCESS)
				{
					szPointingType[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_TYPE_VALUE);
					_tcscpy( szPointingType, NOT_AVAILABLE);
				}
				// Read the pointing interface
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_INPUT_KEYBOARD_INTERFACE_VALUE, 0, &dwType, (LPBYTE) szPointingInterface, &dwLength) == ERROR_SUCCESS)
				{
					szPointingInterface[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_INPUT_KEYBOARD_INTERFACE_VALUE);
					_tcscpy( szPointingInterface, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( INPUT_DEVICE_POINTING, szManufacturer, szCaption, szDescription, szPointingType, szPointingInterface);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tFailed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_INPUT_POINTING_KEY);
	}
	else
		AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_INPUT_POINTING_KEY);
	if (uIndex > 0)
	{
		uTotalIndex += uIndex;
		AddLog( _T( "Registry NT GetInputDevices: Find Pointing Devices OK (%u objects)\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetInputDevices: Find Pointing Devices failed because no valid object !\n"));
	if (uTotalIndex > 0)
	{
		AddLog( _T( "Registry NT GetInputDevices: OK (%u objects).\n"), uTotalIndex);
		return TRUE;
	}
	AddLog( _T( "Registry NT GetInputDevices: Failed because no controler found.\n"));
	return FALSE;
}

BOOL CRegistry::GetSystemPorts(CSystemPortList *pList)
{
	// Reset object list content
	while (!(pList->GetCount() == 0))
		pList->RemoveHead();
	// Try to get system ports Informations info from the registry
	switch( m_dwPlatformId)
	{
	case VER_PLATFORM_WIN32_WINDOWS:
		// Windows 9X/Me
		return GetSystemPorts9X( pList);
	case VER_PLATFORM_WIN32_NT:
		// Windows NT/2000/XP/2003
		return GetSystemPortsNT( pList);
	default:
		// Unknown
		AddLog( _T( "Registry GetSystemPorts...Failed because unsupported or unrecognized OS !\n"));
		return FALSE;
	}
	return FALSE;
}

BOOL CRegistry::GetSystemPorts9X(CSystemPortList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szType[256],
					szName[256],
					szDescription[256],
					szCaption[256];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSystemPort		myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry 9X/Me GetSystemPorts...\n"));
	// Windows 9X => Open the modem key
	if (RegOpenKeyEx( m_hKey, WIN_SYSTEM_PORT_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), WIN_SYSTEM_PORT_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szType, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the type, i.e the serial or parallel
				dwLength = sizeof( DWORD);
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, WIN_SYSTEM_PORT_TYPE_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
					switch (dwType)
					{
					case WIN_SYSTEM_PORT_CLASS_SERIAL:
						_tcscpy( szType, SYSTEM_PORT_SERIAL);
						break;
					case WIN_SYSTEM_PORT_CLASS_PARALLEL:
						_tcscpy( szType, SYSTEM_PORT_PARALLEL);
						break;
					default:
						_tcscpy( szType, NOT_AVAILABLE);
						break;
					}
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SYSTEM_PORT_TYPE_VALUE);
					_tcscpy( szType, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SYSTEM_PORT_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SYSTEM_PORT_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SYSTEM_PORT_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SYSTEM_PORT_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_SYSTEM_PORT_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, WIN_SYSTEM_PORT_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szType, szName, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry 9X/Me GetSystemPorts: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					WIN_SYSTEM_PORT_KEY);
		else
			AddLog( _T( "Registry 9X/Me GetSystemPorts: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry 9X/Me GetSystemPorts: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_SYSTEM_PORT_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::GetSystemPortsNT(CSystemPortList *pList)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey;
	TCHAR			szType[256],
					szName[256],
					szDescription[256],
					szCaption[256];
	DWORD			dwLength,
					dwType,
					dwValue,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;
	CSystemPort		myObject;
	BOOL			bHaveToStore;
	UINT			uIndex = 0;

	AddLog( _T( "Registry NT GetSystemPorts...\n"));
	// Windows 9X => Open the modem key
	if (RegOpenKeyEx( m_hKey, NT_SYSTEM_PORT_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find devices
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the device key
			szName[dwLength] = 0;
			bHaveToStore = FALSE;
			csSubKey.Format( _T( "%s\\%s"), NT_SYSTEM_PORT_KEY, szName);
			if (RegOpenKeyEx( m_hKey, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				_tcscpy( szType, NOT_AVAILABLE); 
				_tcscpy( szName, NOT_AVAILABLE); 
				_tcscpy( szCaption, NOT_AVAILABLE);
				_tcscpy( szDescription, NOT_AVAILABLE); 
				// Read the type, i.e the serial or parallel
				dwLength = sizeof( DWORD);
				dwType = REG_DWORD;
				if (RegQueryValueEx( hKeyObject, NT_SYSTEM_PORT_TYPE_VALUE, 0, &dwType, (LPBYTE) &dwValue, &dwLength) == ERROR_SUCCESS)
				{
					switch (dwType)
					{
					case NT_SYSTEM_PORT_CLASS_SERIAL:
						_tcscpy( szType, SYSTEM_PORT_SERIAL);
						break;
					case NT_SYSTEM_PORT_CLASS_PARALLEL:
						_tcscpy( szType, SYSTEM_PORT_PARALLEL);
						break;
					default:
						_tcscpy( szType, NOT_AVAILABLE);
						break;
					}
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SYSTEM_PORT_TYPE_VALUE);
					_tcscpy( szType, NOT_AVAILABLE);
				}
				// Read the name
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SYSTEM_PORT_NAME_VALUE, 0, &dwType, (LPBYTE) szName, &dwLength) == ERROR_SUCCESS)
				{
					szName[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SYSTEM_PORT_NAME_VALUE);
					_tcscpy( szName, NOT_AVAILABLE);
				}
				// Read the caption
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SYSTEM_PORT_CAPTION_VALUE, 0, &dwType, (LPBYTE) szCaption, &dwLength) == ERROR_SUCCESS)
				{
					szCaption[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SYSTEM_PORT_CAPTION_VALUE);
					_tcscpy( szCaption, NOT_AVAILABLE);
				}
				// Read the description
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, NT_SYSTEM_PORT_DESCRIPTION_VALUE, 0, &dwType, (LPBYTE) szDescription, &dwLength) == ERROR_SUCCESS)
				{
					szDescription[dwLength]=0;
					bHaveToStore = TRUE;
				}
				else
				{
					if(VVERBOSE) AddLog( _T( "\tFailed in call to <RegQueryValueEx> function for HKLM\\%s\\%s !\n"),
									   csSubKey, NT_SYSTEM_PORT_DESCRIPTION_VALUE);
					_tcscpy( szDescription, NOT_AVAILABLE);
				}
				RegCloseKey( hKeyObject);
				myObject.Set( szType, szName, szCaption, szDescription);
				// Add the device to the adapter list
				if (bHaveToStore)
				{
					pList->AddTail( myObject);
					uIndex ++;
				}
			}
			else
				AddLog( _T( "\tFailed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "Registry NT GetSystemPorts: Failed in call to <RegEnumKeyEx> function to find subkey of HKLM\\%s.\n"),
					NT_SYSTEM_PORT_KEY);
		else
			AddLog( _T( "Registry NT GetSystemPorts: OK (%u objects).\n"), uIndex);
	}
	else
		AddLog( _T( "Registry NT GetSystemPorts: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				NT_SYSTEM_PORT_KEY);
	return !pList->IsEmpty();
}

BOOL CRegistry::ValidateComponent9X(LPCTSTR lpstrComponentKey)
{
	HKEY			hKeyEnum,
					hKeyObject;
	CString			csSubKey,
					csComponentKey = lpstrComponentKey;
	TCHAR			szValue[256],
					szComponentName[256];
	DWORD			dwLength,
					dwType,
					dwIndexEnum = 0;
	LONG			lResult;
	FILETIME		MyFileTime;

	AddLog( _T( "\tRegistry 9X/Me ValidateComponent...\n"));
	// Windows 9X => Open the Config Manager key
	if (RegOpenKeyEx( HKEY_DYN_DATA, WIN_CONFIG_MANAGER_KEY, 0, KEY_READ, &hKeyEnum) == ERROR_SUCCESS)
	{
		// Enum the devices subkeys to find components
		dwLength = 255;
		while ((lResult = RegEnumKeyEx( hKeyEnum, dwIndexEnum, szComponentName, &dwLength, 0, NULL, 0, &MyFileTime)) == ERROR_SUCCESS)
		{
			// For each object, Try to open the component key
			szComponentName[dwLength] = 0;
			csSubKey.Format( _T( "%s\\%s"), WIN_CONFIG_MANAGER_KEY, szComponentName);
			if (RegOpenKeyEx( HKEY_DYN_DATA, csSubKey, 0, KEY_READ, &hKeyObject) == ERROR_SUCCESS)
			{
				// OK => Read the component key
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONFIG_MANAGER_COMPONENT_VALUE, 0, &dwType, (LPBYTE) szValue, &dwLength) != ERROR_SUCCESS)
				{
					AddLog( _T( "\t\tFailed in call to <RegQueryValueEx> function for HKDD\\%s\\%s !\n"),
									   csSubKey, WIN_CONFIG_MANAGER_COMPONENT_VALUE);
					RegCloseKey( hKeyObject);
					// Enum the next device
					dwLength = 255;
					dwIndexEnum++;
					continue;
				}
				// OK => check this the component we want
				if (csComponentKey.Find( szValue) == -1)
				{
					// Not the component
					RegCloseKey( hKeyObject);
					// Enum the next device
					dwLength = 255;
					dwIndexEnum++;
					continue;
				}
				// Read the status
				dwLength = 255;
				if (RegQueryValueEx( hKeyObject, WIN_CONFIG_MANAGER_STATUS_VALUE, 0, &dwType, (LPBYTE) szValue, &dwLength) != ERROR_SUCCESS)
				{
					AddLog( _T( "\t\tFailed in call to <RegQueryValueEx> function for HKDD\\%s\\%s !\n"),
									   csSubKey, WIN_CONFIG_MANAGER_STATUS_VALUE);
					RegCloseKey( hKeyObject);
					// Enum the next device
					dwLength = 255;
					dwIndexEnum++;
					continue;
				}
				AddLog( _T( "\t\tStatus %s: %.04X\n"), csSubKey, *szValue);
				RegCloseKey( hKeyObject);
			}
			else
				AddLog( _T( "\t\tFailed in call to <RegOpenKeyEx> function for HKDD\\%s !\n"),
								   csSubKey);
			// Enum the next device
			dwLength = 255;
			dwIndexEnum++;
		}
		RegCloseKey( hKeyEnum);
		if (dwIndexEnum == 0)
			// No key found
			AddLog( _T( "\tRegistry 9X/Me ValidateComponent: Failed in call to <RegEnumKeyEx> function to find subkey of HKDD\\%s.\n"),
					WIN_CONFIG_MANAGER_KEY);
		else
			AddLog( _T( "\tRegistry 9X/Me ValidateComponent: OK.\n"));
	}
	else
		AddLog( _T( "\tRegistry 9X/Me ValidateComponent: Failed in call to <RegOpenKeyEx> function for HKLM\\%s !\n"),
				WIN_CONFIG_MANAGER_KEY);
	return FALSE;
}

BOOL CRegistry::GetRegistryMultipleValues(LPCTSTR lpstrDeviceID, LPCTSTR lpstrName, UINT uKeyTree, LPCTSTR lpstrSubKey, CRegistryValueList *pMyList)
{
	TCHAR	szName[256];
    BYTE	*lpValue = NULL;
	HKEY	hKey = NULL;
	LONG	lResult;
	LPCTSTR	pSZ;
	CString csSubKey = lpstrSubKey,
			csResult,
			csTemp;
	DWORD	dwIndex = 0,
			dwType = REG_NONE,
			dwSizeName = 255,
			dwSizeValue = 0,
			dwValue,
			dwCpt;
	CRegistryValue myRegistry;

	myRegistry.SetDeviceID( lpstrDeviceID);
	
	switch (uKeyTree)
	{
	case HKCR_TREE: // HKEY_CLASSES_ROOT
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKCR"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_CLASSES_ROOT, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKCU_TREE: // HKEY_CURRENT_USER
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKCU"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_CURRENT_USER, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKLM_TREE: // HKEY_LOCAL_MACHINE
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKLM"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKU_TREE: // HKEY_USERS
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKU"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKCC_TREE: // HKEY_CURRENT_CONFIG
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKCC"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	case HKDD_TRE: // HKEY_DYN_DATA (9X only)
		AddLog( _T( "Registry GetRegistryMultipleValues (%s\\%s)...\n"),
			_T( "HKDD"),
			csSubKey);
		lResult = RegOpenKeyEx( HKEY_LOCAL_MACHINE, csSubKey, 0, KEY_READ, &hKey);
		break;
	default: // Error
		AddLog( _T( "Registry GetRegistryMultipleValues...Failed because unrecognized Registry Tree %u !\n"), uKeyTree);
		return FALSE;
	}
	if (lResult != ERROR_SUCCESS)
	{
		AddLog( _T( "\tFailed in call to <RegOpenKey> function for subkey %s of selected hive !\n"),
				csSubKey);
		return FALSE;
	}
	while ((lResult = RegEnumValue( hKey, dwIndex, szName, &dwSizeName, NULL, &dwType, (LPBYTE) &dwValue, &dwSizeValue)) != ERROR_NO_MORE_ITEMS)
	{
		if ((lResult != ERROR_SUCCESS) && (lResult != ERROR_MORE_DATA) && (lResult != ERROR_NO_MORE_ITEMS))
		{
			// Error while reading the value
			AddLog( _T( "\tFailed in call to <RegEnumKey> function for value %lu in key %s of selected hive (unable to get value size) !\n"),
					dwIndex,
					csSubKey);
		}
		else
		{
			csResult = NOT_AVAILABLE;
			szName[dwSizeName]=0;
			// Allocate value buffer
			if ((lpValue = (LPBYTE)malloc( (dwSizeValue+1)*sizeof( BYTE))) == NULL)
			{
				AddLog( _T( "\tFailed in call to <RegEnumKey> function for value %lu in key %s of selected hive (unable to allocate value size) !\n"),
						dwIndex,
						csSubKey);
			}
			else
			{
				// Get value
				switch (dwType)
				{
				case REG_DWORD:
					if ((lResult = RegEnumValue( hKey, dwIndex, szName, &dwSizeName, NULL, &dwType, (LPBYTE) &dwValue, &dwSizeValue)) != ERROR_SUCCESS)
					{
						AddLog( _T( "Failed in call to <RegEnumKey> function for value % lu in key %s of selected hive (unable to get value)!\n"),
								dwIndex,
								csSubKey);
					}
					else
					{
						csResult.Format( _T( "%s=%lu"), szName, dwValue);
						AddLog( _T("\tValue %lu: %s\n"), dwIndex, csResult);
						myRegistry.Set( lpstrName, csResult);
						pMyList->AddTail( myRegistry);
					}
					break;
				case REG_SZ:
				case REG_EXPAND_SZ:
					if ((lResult = RegEnumValue( hKey, dwIndex, szName, &dwSizeName, NULL, &dwType, (LPBYTE) lpValue, &dwSizeValue)) != ERROR_SUCCESS)
					{
						AddLog( _T( "Failed in call to <RegEnumKey> function for value % lu in key %s of selected hive (unable to get value)!\n"),
								dwIndex,
								csSubKey);
					}
					else
					{
						lpValue[dwSizeValue]=0;
						csResult.Format( _T( "%s=%s"), szName, (LPCTSTR) lpValue);
						AddLog( _T("\tValue %lu: %s\n"), dwIndex, csResult);
						myRegistry.Set( lpstrName, csResult);
						pMyList->AddTail( myRegistry);
					}
					break;
				case REG_MULTI_SZ:
					if ((lResult = RegEnumValue( hKey, dwIndex, szName, &dwSizeName, NULL, &dwType, (LPBYTE) lpValue, &dwSizeValue)) != ERROR_SUCCESS)
					{
						AddLog( _T( "Failed in call to <RegEnumKey> function for value % lu in key %s of selected hive (unable to get value)!\n"),
								dwIndex,
								csSubKey);
					}
					else
					{
						lpValue[dwSizeValue]=0;
						csResult.Format( _T( "%s="), szName); 
						// Parse multistring registry value
						pSZ = ParseMultiSZ( (LPCTSTR) lpValue);
						while (pSZ != NULL)
						{
							csResult += pSZ;
							csResult += _T( " ");
							pSZ = ParseMultiSZ();
						}
						AddLog( _T("\tValue %lu: %s\n"), dwIndex, csResult);
						myRegistry.Set( lpstrName, csResult);
						pMyList->AddTail( myRegistry);
					}
					break;
				case REG_BINARY:
					if ((lResult = RegEnumValue( hKey, dwIndex, szName, &dwSizeName, NULL, &dwType, (LPBYTE) lpValue, &dwSizeValue)) != ERROR_SUCCESS)
					{
						AddLog( _T( "Failed in call to <RegEnumKey> function for value % lu in key %s of selected hive (unable to get value)!\n"),
								dwIndex,
								csSubKey);
					}
					else
					{
						lpValue[dwSizeValue]=0;
						csResult.Format( _T( "%s="), szName);
						for (dwCpt=0; dwCpt<dwSizeValue; dwCpt++)
						{
							csTemp.Format( _T( "%.02X "), lpValue[ dwCpt]);
							csResult += csTemp;
						}
						AddLog( _T("\tValue %lu: %s\n"), dwIndex, csResult);
						myRegistry.Set( lpstrName, csResult);
						pMyList->AddTail( myRegistry);
					}
					break;
				default:
					AddLog( _T( "\tFailed in call to <RegEnumKey> function for value %lu in key %s of selected hive because unhandled Registry type %u !\n"),
							dwIndex,
							csSubKey,
							dwType);
				}
				free( lpValue);
			}
		}
		// Next
		dwSizeName=255;
		dwSizeValue=0;
		dwType=REG_NONE;
		dwIndex++;
	}
	RegCloseKey( hKey);
	AddLog( _T( "Registry GetRegistryMultipleValues...OK (%u values read).\n"), dwIndex);
	return TRUE;
}
