// Document modified at : Tuesday, March 28, 2006 12:50:28 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Modified by Pierre LEMMET
// Web: http://ocsinventory.sourceforge.net
// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================
// Wmi.cpp: implementation of the CWmi class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DebugLog.h"
#include "../include/_common/utils.h"
#include "SysInfo.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWmi::CWmi()
{
	m_bConnected = FALSE;
}

CWmi::~CWmi()
{
	Disconnect();
}

BOOL CWmi::Connect( LPCTSTR lpstrDevice)
{
	try
	{
		CString	csCimRoot;

		// Do not connect if already connected
		if (m_bConnected)
			return TRUE;
		// Load OcsWmi wrapper library
		AddLog( _T( "WMI Connect: Trying to connect to WMI namespace root\\cimv2 on device <%s>..."), 
			(lpstrDevice == NULL ? _T( "Localhost") : lpstrDevice));
		if (lpstrDevice == NULL)
			csCimRoot.Format( _T( "root\\cimv2"));
		else
			csCimRoot.Format( _T( "\\\\%s\\root\\cimv2"), lpstrDevice);
		if (!m_dllWMI.ConnectWMI( csCimRoot))
		{
			// Unable to connect to WMI => no WMI support
			AddLog( _T( "Failed because unable to connect to WMI namespace (0x%lX) !\n"), m_dllWMI.GetLastErrorWMI());
			return FALSE;
		}
		m_bConnected = TRUE;
		AddLog( _T( "OK.\n"));
		return TRUE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception.\n"));
		return FALSE;
	}
}

BOOL CWmi::Disconnect()
{
	if (m_bConnected)
	{
		CUtils::trace("CWMI_DISCONNECT", AfxGetApp()->m_lpCmdLine);
		m_dllWMI.DisconnectWMI();
		CUtils::trace("CWMI_DISCONNECTED", AfxGetApp()->m_lpCmdLine);
		AddLog( _T( "WMI Disconnect: Disconnected from WMI namespace.\n"));
	}
	m_bConnected = FALSE;
	return TRUE;
}

BOOL CWmi::IsWmiConnected()
{
	return m_bConnected;
}

BOOL CWmi::IsNotebook()
{
	CString csBuffer;
	UINT	uIndex = 0;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI IsNotebook: Trying to find Win32_PortableBattery WMI objects..."));
	// Try to use PortableBattery object
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PortableBattery")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "EstimatedRunTime"));
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects). Is a Notebook.\n"), uIndex);
			return TRUE;
		}
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception!\n"));
	}
	AddLog( _T( "No Win32_PortableBattery => not a Notebook\n"));
	return FALSE;
/*********************************************
	Not used to detect Notebook. Battery object is UPS
	// Try to use Battery object
	uIndex = 0;
	AddLog( _T( "No Win32_PortableBattery.\n\t\tTrying to find Win32_Battery WMI objects..."));
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_Battery")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "EstimatedRunTime"));
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "No Win32_Battery => not a Notebook\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
*****************************************************/
}

BOOL CWmi::GetBiosInfo(CBios *pMyBios)
{
	CString	csManufacturer = NOT_AVAILABLE,
			csModel = NOT_AVAILABLE,
			csSN = NOT_AVAILABLE,
			csRdate = NOT_AVAILABLE,
			csBiosVer = NOT_AVAILABLE,
			csBiosBiosVer = NOT_AVAILABLE,
			csBiosSMBiosVer = NOT_AVAILABLE,
			csChassisType = NOT_AVAILABLE;
	UINT	uIndex = 0;
	BOOL	bResult = FALSE;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return bResult;
	
	// Try to use win32 computer system object to get System Manufacturer, Model
	AddLog( _T( "WMI GetBiosInfo: Trying to find Win32_ComputerSystem WMI objects..."));
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_ComputerSystem")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csManufacturer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				csModel = m_dllWMI.GetClassObjectStringValue( _T( "Model"));

			}
			m_dllWMI.CloseEnumClassObject();
			AddLog( _T( "OK (%s %s)\n"), csManufacturer, csModel);
		}
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Try to use system enclosure object to get System Manufacturer, Model, S/N and chassis type
	AddLog( _T( "WMI GetBiosInfo: Trying to find Win32_SystemEnclosure WMI objects..."));
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_SystemEnclosure")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				if (csManufacturer.IsEmpty())
					csManufacturer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				if (csModel.IsEmpty())
					csModel = m_dllWMI.GetClassObjectStringValue( _T( "Model"));
				csSN = m_dllWMI.GetClassObjectStringValue( _T( "SerialNumber"));
				csChassisType = m_dllWMI.GetClassObjectStringValue( _T( "ChassisTypes"));			
			}
			m_dllWMI.CloseEnumClassObject();
			AddLog( _T( "OK (%s %s %s %s)\n"), csManufacturer, csModel, csSN, csChassisType);
		}
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	if (csManufacturer.IsEmpty() || csModel.IsEmpty() || csSN.IsEmpty())
	{
		// System enclosure not available => use mother board object
		AddLog( _T( "Manufacturer or Model or Serial Number property not available. Trying to find Win32_BaseBoard WMI objects..."));
		try
		{
			if (m_dllWMI.BeginEnumClassObject( _T( "Win32_BaseBoard")))
			{
				while (m_dllWMI.MoveNextEnumClassObject())
				{
					if (csManufacturer.IsEmpty())
						// Get Manufacturer from mother board only if not available
						csManufacturer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
					if (csModel.IsEmpty())
						// Get Model from mother board only if not available
						csModel = m_dllWMI.GetClassObjectStringValue( _T( "Product"));
					if (csSN.IsEmpty())
						// Get S/N from mother board only if not available
						csSN = m_dllWMI.GetClassObjectStringValue( _T( "SerialNumber"));				
				}
				m_dllWMI.CloseEnumClassObject();
				AddLog( _T( "OK (%s %s %s)\n"), csManufacturer, csModel, csSN);
			}
		}
		catch (CException *pEx)
		{
			pEx->Delete();
			AddLog( _T( "Failed because unknown exception !\n"));
		}
	}
	pMyBios->SetSystemManufacturer( csManufacturer);
	pMyBios->SetSystemModel( csModel);
	pMyBios->SetSystemSerialNumber( csSN);
	ParseChassisType( csChassisType);
	pMyBios->SetMachineType( csChassisType);
	// GET BIOS Informations
	AddLog( _T( "WMI GetBiosInfo: Trying to find Win32_Bios WMI objects..."));
	csManufacturer = NOT_AVAILABLE;
	csModel = NOT_AVAILABLE;
	csSN = NOT_AVAILABLE;
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_Bios")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csManufacturer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				csBiosBiosVer = m_dllWMI.GetClassObjectStringValue( _T( "BIOSVersion"));
				if (csBiosBiosVer.IsEmpty())
					csBiosBiosVer = m_dllWMI.GetClassObjectStringValue( _T( "Version"));
				csBiosSMBiosVer= m_dllWMI.GetClassObjectStringValue( _T( "SMBIOSBIOSVersion"));
				csBiosVer.Format( _T( "%s- SMBiosVersion: %s"),
								csBiosBiosVer, csBiosSMBiosVer);
				csSN = m_dllWMI.GetClassObjectStringValue( _T( "SerialNumber"));
				// TODO:EXCEPTION
				//csRdate = m_dllWMI.GetClassObjectStringValue( _T( "ReleaseDate"));
				//csRdate=csRdate.Left(8);
				uIndex ++;
			}
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%s %s %s)\n"), csManufacturer, csModel, csSN);
			bResult = TRUE;
		}
		else
		{
			AddLog( _T( "Failed because no Win32_Bios object !\n"));
			bResult = FALSE;
		}

		pMyBios->SetBiosManufacturer( csManufacturer);
		pMyBios->SetSystemSerialNumber( csSN);
		pMyBios->SetBiosDate( csRdate);
		pMyBios->SetBiosVersion( csBiosVer);
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		bResult = FALSE;
	}

	return bResult;
}

BOOL CWmi::GetStoragePeripherals(CStoragePeripheralList *pMyList)
{
	UINT				uIndex = 0,
						uTotalIndex = 0;
	CStoragePeripheral	myObject;
	CString				csBuffer;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	// Get Floppy drives
	AddLog( _T( "WMI GetStoragePeripherals: Trying to find Win32_FloppyDrive WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_FloppyDrive")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetModel( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MediaType"));
				myObject.SetType( csBuffer);
				myObject.SetSize( m_dllWMI.GetClassObjectU64Value( _T( "Size")) / ONE_MEGABYTE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_FloppyDrive object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get Disk drives
	AddLog( _T( "WMI GetStoragePeripherals: Trying to find Win32_DiskDrive WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_DiskDrive")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Model"));
				myObject.SetModel( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MediaType"));
				myObject.SetType( csBuffer);
				myObject.SetSize( m_dllWMI.GetClassObjectU64Value( _T( "Size")) / ONE_MEGABYTE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_DiskDrive object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get CD-Rom drives
	AddLog( _T( "WMI GetStoragePeripherals: Trying to find Win32_CDROMDrive WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_CDROMDrive")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetModel( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MediaType"));
				myObject.SetType( csBuffer);
				myObject.SetSize( m_dllWMI.GetClassObjectU64Value( _T( "Size")) / ONE_MEGABYTE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_CDROMDrive object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get tape drives
	AddLog( _T( "WMI GetStoragePeripherals: Trying to find Win32_TapeDrive WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_TapeDrive")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetModel( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MediaType"));
				myObject.SetType( csBuffer);
				myObject.SetSize( m_dllWMI.GetClassObjectU64Value( _T( "Size")) / ONE_MEGABYTE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_TapeDrive object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	if (uTotalIndex > 0)
	{
		AddLog( _T( "WMI GetStoragePeripherals: OK\n"));
		return TRUE;
	}
	AddLog( _T( "WMI GetStoragePeripherals: Failed because no storage peripherals found !\n"));
	return FALSE;
}

BOOL CWmi::GetSystemControllers(CSystemControllerList *pMyList)
{
	UINT			uIndex = 0,
					uTotalIndex = 0;
	CSystemController myObject;
	CString			csBuffer;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	// Get Floppy controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_FloppyController WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_FloppyController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_FLOPPY);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_FloppyController object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get IDE controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_IDEController WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_IDEController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_IDE);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_IDEController object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get SCSI controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_SCSIController WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_SCSIController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_SCSI);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "HardwareVersion"));
				myObject.SetHardwareVersion( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_SCSIController object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get USB controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_InfraredDevice WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_InfraredDevice")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_INFRARED);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_InfraredDevice object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get USB controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_USBController WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_USBController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_USB);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_USBController object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get IEEE1394 controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_1394Controller WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_1394Controller")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_IEEE1394);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_1394Controller object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get PCMCIA controller
	AddLog( _T( "WMI GetSystemControllers: Trying to find Win32_PCMCIAController WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PCMCIAController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_CONTROLER_PCMCIA);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				myObject.SetHardwareVersion( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotalIndex += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_PCMCIAController object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	if (uTotalIndex > 0)
	{
		AddLog( _T( "WMI GetSystemControllers: OK\n"));
		return TRUE;
	}
	AddLog( _T( "WMI GetSystemControllers: Failed because no system controler found !\n"));
	return FALSE;
}

BOOL CWmi::GetVideoAdapters(CVideoAdapterList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetVideoAdapters: Trying to find Win32_VideoController WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		UINT			uIndex = 0;
		CVideoAdapter	myObject;
		CString			csBuffer;
		unsigned __int64 u64HorzRes,
						 u64VertRes;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_VideoController")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "VideoProcessor"));
				myObject.SetChipset( csBuffer);
				csBuffer.Format( _T( "%lu"), m_dllWMI.GetClassObjectDwordValue( _T( "AdapterRAM")) / ONE_MEGABYTE);
				myObject.SetMemory( csBuffer);
				u64HorzRes = m_dllWMI.GetClassObjectU64Value( _T( "CurrentHorizontalResolution"));
				u64VertRes = m_dllWMI.GetClassObjectU64Value( _T( "CurrentVerticalResolution"));
				csBuffer.Format( _T("%I64u x %I64u"), u64HorzRes, u64VertRes);
				myObject.SetScreenResolution( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_VideoController object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetNetworkAdapters(CNetworkAdapterList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetNetworkAdapters: Trying to find Win32_NetworkAdapterSetting WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		CString			csBuffer,
						csMacAddress;
		UINT			uIndex = 0,
						uTotalIndex = 0;
		CNetworkAdapter	myObject;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_NetworkAdapterSetting")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Element"), _T( "AdapterType"));
				myObject.SetType( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Element"), _T( "ProductName"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Speed"));
				myObject.SetSpeed( csBuffer);
				csMacAddress = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "MACAddress"));
				myObject.SetMACAddress( csMacAddress);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "IPAddress"));
				myObject.SetIPAddress( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Setting"), _T( "IPSubnet"));
				myObject.SetIPNetMask( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Element"), _T( "Status"));
				myObject.SetStatus( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Element"), _T( "AdapterType"));
				myObject.SetTypeMIB( csBuffer);
				if (!csMacAddress.IsEmpty())
				{
					// Skip adapters without MAC Address
					pMyList->AddTail( myObject);
					uIndex ++;
				}
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_NetworkAdapterSetting object with valid MAC Address !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetMonitors(CMonitorList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetMonitors: Trying to find Win32_DesktopMonitor WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		UINT		uIndex = 0;
		CMonitor	myObject;
		CString		csBuffer;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_DesktopMonitor")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MonitorManufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "MonitorType"));
				myObject.SetType( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_DesktopMonitor object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetModems(CModemList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetModems: Trying to find Win32_POTSModem WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		UINT	uIndex = 0;
		CModem	myObject;
		CString	csBuffer;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_POTSModem")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "DeviceType"));
				myObject.SetType( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Model"));
				myObject.SetModel( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_POTSModem object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetSoundDevices(CSoundDeviceList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetSoundDevices: Trying to find Win32_SoundDevice WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		CSoundDevice	myObject;
		UINT			uIndex = 0;
		CString			csBuffer;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_SoundDevice")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "ProductName"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_SoundDevice object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetPrinters(CPrinterList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetPrinters: Trying to find Win32_Printer WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		UINT		uIndex = 0;
		CPrinter	myObject;
		CString		csBuffer;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_Printer")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "DriverName"));
				myObject.SetDriver( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "PortName"));
				myObject.SetPort( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_Printer object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetSystemPorts(CSystemPortList *pMyList)
{
	UINT		uIndex,
				uTotal = 0;
	CSystemPort	myObject;
	CString		csBuffer;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	// Get serial ports
	AddLog( _T( "WMI GetSystemPorts: Trying to find Win32_SerialPort WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_SerialPort")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_PORT_SERIAL);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotal += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_SerialPort object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get parallel ports
	AddLog( _T( "WMI GetSystemPorts: Trying to find Win32_ParallelPort WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_ParallelPort")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( SYSTEM_PORT_PARALLEL);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotal += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_ParallelPort object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	if (uTotal > 0)
	{
		AddLog( _T( "WMI GetSystemPorts: OK\n"));
		return TRUE;
	}
	AddLog( _T( "WMI GetSystemPorts: Failed because no system port found !\n"));
	return FALSE;
}

DWORD CWmi::GetProcessors(CString &csProcType, CString &csProcSpeed)
{
	AddLog( _T( "WMI GetProcessors: Trying to find Win32_Processor WMI objects..."));
	try
	{
		static DWORD	dwNumber = 0;
		CString csDescription;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_Processor")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csProcType = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				StrForSQL(csProcType);
				csProcSpeed = m_dllWMI.GetClassObjectStringValue( _T( "MaxClockSpeed"));
				StrForSQL( csProcSpeed);
			//	csProcSpeed += _T( " MHz");
				csDescription = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				StrForSQL( csDescription);
				dwNumber ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (dwNumber > 0)
		{
			AddLog( _T( "%s %s (%s). OK\n"), csProcType, csProcSpeed, csDescription);
			return dwNumber;
		}
		AddLog( _T( "Failed because no Win32_Processor object !\n"));
		return 0;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return 0;
	}
}

UINT CWmi::GetOS(CString &csName, CString &csVersion, CString &csComment, CString &csDescription)
{
	AddLog( _T( "WMI GetOS: Trying to find Win32_OperatingSystem WMI objects..."));
	try
	{
		UINT	uIndex = 0,
				uType = WINDOWS_WORKSTATION;
		CString csType;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_OperatingSystem")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csName = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				csName = csName.Left(csName.Find("|",0));
				StrForSQL( csName);
				csVersion = m_dllWMI.GetClassObjectStringValue( _T( "Version"));
				StrForSQL( csVersion);
				csComment = m_dllWMI.GetClassObjectStringValue( _T( "CSDVersion"));
				StrForSQL( csComment);
				csType = m_dllWMI.GetClassObjectStringValue( _T( "ProductType"));
				if (!csType.IsEmpty())
				{
					// If this key exists, it can be a workstation (1), a domain controler (2) or a server (3)
					uType = _tcstoul( csType, NULL, 10);
					uType = (uType > 1 ? WINDOWS_SERVER : WINDOWS_WORKSTATION);
				}
				else
				{
					csType = m_dllWMI.GetClassObjectStringValue( _T( "OSProductSuite"));
					if (!csType.IsEmpty())
						// If this key exists, this is a server
						uType = WINDOWS_SERVER;
				}
				csDescription = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				StrForSQL( csDescription);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%s %s %s %s %s).\n"), csName, csVersion, csComment, csType, csDescription);
			return uType;
		}
		AddLog( _T( "Failed because no Win32_OperatingSystem object !\n"));
		return UNKNOWN_DEVICE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return UNKNOWN_DEVICE;
	}
}

BOOL CWmi::GetWindowsRegistration( CString &csCompany, CString &csUser, CString &csSN)
{
	AddLog( _T( "WMI GetWindowsRegistration: Trying to find Win32_OperatingSystem WMI objects..."));
	try
	{
		UINT	uIndex = 0;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_OperatingSystem")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csCompany = m_dllWMI.GetClassObjectStringValue( _T( "Organization"));
				StrForSQL( csCompany);
				csUser = m_dllWMI.GetClassObjectStringValue( _T( "RegisteredUser"));
				StrForSQL( csUser);
				csSN = m_dllWMI.GetClassObjectStringValue( _T( "SerialNumber"));
				StrForSQL( csSN);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%s %s %s).\n"), csCompany, csUser, csSN);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_OperatingSystem object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::ParseChassisType(CString &csType)
{
	int		nPos = 0;
	CString csResult,
			csTemp,
			csData;

	if (csType.IsEmpty())
	{
		csType = NOT_AVAILABLE;
		return FALSE;
	}
	csData = csType;
	while ((nPos = csData.Find( _T( ";"))) != -1)
	{
		csTemp = csData.Left( nPos);
		if (!csTemp.IsEmpty())
		{
			switch (_ttoi( csTemp))
			{
			case 1: 
				csResult += _T( "Other;");
				break;
			case 2:  
				csResult += _T( "Unknown;");
				break;
			case 3:  
				csResult += _T( "Desktop;");
				break;
			case 4:  
				csResult += _T( "Low Profile Desktop;");
				break;
			case 5:  
				csResult += _T( "Pizza Box;");
				break;
			case 6:  
				csResult += _T( "Mini Tower;");
				break;
			case 7:  
				csResult += _T( "Tower;");
				break;
			case 8:  
				csResult += _T( "Portable;");
				break;
			case 9:  
				csResult += _T( "Laptop;");
				break;
			case 10:  
				csResult += _T( "Notebook;");
				break;
			case 11:  
				csResult += _T( "Hand Held;");
				break;
			case 12:  
				csResult += _T( "Docking Station;");
				break;
			case 13:  
				csResult += _T( "All in One;");
				break;
			case 14:  
				csResult += _T( "Sub Notebook;");
				break;
			case 15:  
				csResult += _T( "Space-Saving;");
				break;
			case 16:  
				csResult += _T( "Lunch Box;");
				break;
			case 17:  
				csResult += _T( "Main System Chassis;");
				break;
			case 18:  
				csResult += _T( "Expansion Chassis;");
				break;
			case 19:  
				csResult += _T( "SubChassis;");
				break;
			case 20:  
				csResult += _T( "Bus Expansion Chassis;");
				break;
			case 21:  
				csResult += _T( "Peripheral Chassis;");
				break;
			case 22:  
				csResult += _T( "Storage Chassis;");
				break;
			case 23:  
				csResult += _T( "Rack Mount Chassis;");
				break;
			case 24:  
				csResult += _T( "Sealed-Case PC;");
				break;
			default:
				csResult += _T( "Unknown (");
				csResult += csTemp;
				csResult += _T( ");");
				break;
			}
		}
		csTemp = csData.Right( nPos+1);
		csData = csTemp;
	}
	if (!csData.IsEmpty())
	{
		switch (_ttoi( csData))
		{
		case 1: 
			csResult += _T( "Other");
			break;
		case 2:  
			csResult += _T( "Unknown");
			break;
		case 3:  
			csResult += _T( "Desktop");
			break;
		case 4:  
			csResult += _T( "Low Profile Desktop");
			break;
		case 5:  
			csResult += _T( "Pizza Box");
			break;
		case 6:  
			csResult += _T( "Mini Tower");
			break;
		case 7:  
			csResult += _T( "Tower");
			break;
		case 8:  
			csResult += _T( "Portable");
			break;
		case 9:  
			csResult += _T( "Laptop");
			break;
		case 10:  
			csResult += _T( "Notebook");
			break;
		case 11:  
			csResult += _T( "Hand Held");
			break;
		case 12:  
			csResult += _T( "Docking Station");
			break;
		case 13:  
			csResult += _T( "All in One");
			break;
		case 14:  
			csResult += _T( "Sub Notebook");
			break;
		case 15:  
			csResult += _T( "Space-Saving");
			break;
		case 16:  
			csResult += _T( "Lunch Box");
			break;
		case 17:  
			csResult += _T( "Main System Chassis");
			break;
		case 18:  
			csResult += _T( "Expansion Chassis");
			break;
		case 19:  
			csResult += _T( "SubChassis");
			break;
		case 20:  
			csResult += _T( "Bus Expansion Chassis");
			break;
		case 21:  
			csResult += _T( "Peripheral Chassis");
			break;
		case 22:  
			csResult += _T( "Storage Chassis");
			break;
		case 23:  
			csResult += _T( "Rack Mount Chassis");
			break;
		case 24:  
			csResult += _T( "Sealed-Case PC");
			break;
		default:
			csResult += _T( "Unknown (");
			csResult += csData;
			csResult += _T( ");");
		}
	}
	csType = csResult;
	return TRUE;
}

BOOL CWmi::GetDomainOrWorkgroup( CString &csDomain)
{
	BOOL	bResult = FALSE;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return bResult;

	// Try to use win32 computer system object to get System Manufacturer, Model
	AddLog( _T( "WMI GetDomainOrWorkgroup: Trying to find Win32_ComputerSystem WMI objects..."));
	try
	{
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_ComputerSystem")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csDomain = m_dllWMI.GetClassObjectStringValue( _T( "Domain"));
			}
			m_dllWMI.CloseEnumClassObject();
			AddLog( _T( "OK (%s)\n"), csDomain);
			bResult = TRUE;
		}
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	return bResult;
}

BOOL CWmi::GetSystemSlots(CSystemSlotList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	AddLog( _T( "WMI GetSystemSlots: Trying to find Win32_SystemSlot WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		CSystemSlot	myObject;
		UINT		uIndex = 0;
		CString		csBuffer;
		DWORD		dwValue;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_SystemSlot")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Name"));
				myObject.SetName( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "SlotDesignation"));
				myObject.SetSlotDesignation( csBuffer);
			//	dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "CurrentUsage"));
			//	myObject.SetUsage( dwValue);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Status"));
				myObject.SetStatus( csBuffer);
				dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "Shared"));
				myObject.SetShared( dwValue);
				// Device is OK
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_SystemSlot object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetMemorySlots(CMemorySlotList *pMyList)
{
	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

/* BECAUSE object Win32_PhysicalMemoryLocation bogus with some computer

	AddLog( _T( "WMI GetMemorySlots: Trying to find Win32_PhysicalMemoryLocation WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		CMemorySlot	myObject;
		UINT		uIndex = 0;
		CString		csBuffer;
		DWORD		dwValue;

		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PhysicalMemoryLocation")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Win32_PhysicalMemoryArray"), _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Win32_PhysicalMemoryArray"), _T( "Description"));
				myObject.SetDescription( csBuffer);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Win32_PhysicalMemoryArray"), _T( "MaxCapacity"));
				myObject.SetCapacity( csBuffer);
				dwValue = m_dllWMI.GetRefElementClassObjectDwordValue( _T( "Win32_PhysicalMemoryArray"), _T( "Use"));
				myObject.SetUsage( dwValue);
				dwValue = m_dllWMI.GetRefElementClassObjectDwordValue( _T( "Win32_PhysicalMemoryArray"), _T( "MemoryDevices"));
				myObject.SetSlotNumber( dwValue);
				csBuffer = m_dllWMI.GetRefElementClassObjectStringValue( _T( "Win32_PhysicalMemory"),  _T( "Speed"));
				myObject.SetSpeed( csBuffer);
				dwValue = m_dllWMI.GetRefElementClassObjectDwordValue( _T( "Win32_PhysicalMemory"),  _T( "MemoryType"));
				myObject.SetType( dwValue);
				// Device is OK
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			AddLog( _T( "OK (%u objects)\n"), uIndex);
			return TRUE;
		}
		AddLog( _T( "Failed because no Win32_PhysicalMemoryLocation object !\n"));
		return FALSE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
*/
	AddLog( _T( "WMI GetMemorySlots: Trying to find Win32_PhysicalMemory WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		CMemorySlot			myObject;
		UINT				uIndex = 0;
		CString				csBuffer, csCaption;
		DWORD				dwValue,
							dwUse,
							dwECC;
		unsigned __int64	u64Value;
		POSITION			pPosCur,
							pPosNext;

		// Checking Physical Memory objects for properties
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PhysicalMemory")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				if (csBuffer.IsEmpty())
					csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "DeviceLocator"));
				if (csBuffer.IsEmpty())
					csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "BankLabel"));
				myObject.SetDescription( csBuffer);
				u64Value = m_dllWMI.GetClassObjectU64Value(  _T( "Capacity"));
				csBuffer.Format( _T( "%I64u"), u64Value / ONE_MEGABYTE);
				myObject.SetCapacity( csBuffer);
				myObject.SetSlotNumber( uIndex+1);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Speed"));
				myObject.SetSpeed( csBuffer);
				dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "MemoryType"));
				myObject.SetType( dwValue);
				// Device is OK
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex == 0)
		{
			AddLog( _T( "Failed because no Win32_PhysicalMemory object !\n"));
			return FALSE;
		}
		AddLog( _T( "OK (%u objects)\n"), uIndex);
		// Checking Physical Memory Array objects for completing properties
		AddLog( _T( "WMI GetMemorySlots: Trying to find Win32_PhysicalMemoryArray WMI objects..."));
		pPosNext = pMyList->GetHeadPosition();
		pPosCur = pMyList->GetHeadPosition();
		UINT nbFilled = uIndex;
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PhysicalMemoryArray")))
		{
			// One Physical Memory Array object may include one or more Physical Memory objects
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				// The value MemoryDevices indicates the number of Physical Memory object in the array
				dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "MemoryDevices"));
				while( nbFilled < dwValue ) {
					myObject.SetCaption("");
					myObject.SetDescription("");
					myObject.SetCapacity( "0");
					myObject.SetSlotNumber( nbFilled+1 );
					myObject.SetSpeed( "N/A");
					myObject.SetType( "Empty slot");
					pMyList->AddTail( myObject);
					nbFilled++;
				}
				dwUse = m_dllWMI.GetClassObjectDwordValue( _T( "Use"));
				dwECC = m_dllWMI.GetClassObjectDwordValue( _T( "MemoryErrorCorrection"));
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				csCaption = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));

				// Each properties of Physical Memory Array have to be set in MemorySlot object 
				// corresponding to current array
				if (pPosNext != NULL)
					myObject = pMyList->GetNext( pPosNext);
				while ((pPosCur != NULL) && (myObject.GetSlotNumber() <= (uIndex+dwValue)))
				{
					if (_tcslen( myObject.GetCaption()) == 0)
						myObject.SetCaption( csCaption);
					if (_tcslen( myObject.GetDescription()) == 0)
						myObject.SetDescription( csBuffer );					
					
					if (_tcslen( myObject.GetCaption()) == 0)
						myObject.SetCaption( csBuffer );
					if (_tcslen( myObject.GetDescription()) == 0)
						myObject.SetDescription( csCaption );

					myObject.SetUsage( dwUse);
					if( strcmp(myObject.GetType(),"Empty slot") != 0 )
						myObject.SetTypeECC( dwECC);
					pMyList->SetAt( pPosCur, myObject);
					pPosCur = pPosNext;
					if (pPosNext != NULL)
						myObject = pMyList->GetNext( pPosNext);
				}
				uIndex += dwValue;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		AddLog( _T( "OK (%u objects updated)\n"), uIndex);
		return TRUE;
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
		return FALSE;
	}
}

BOOL CWmi::GetInputDevices(CInputDeviceList *pMyList)
{
	UINT		uIndex,
				uTotal = 0;
	CInputDevice myObject;
	CString		csBuffer;
	DWORD		dwValue;

	// If not WMI connected => cannot do this
	if (!m_bConnected)
		return FALSE;

	// Get keyboard
	AddLog( _T( "WMI GetInputDevices: Trying to find Win32_Keyboard WMI objects..."));
	// Reset object list content
	while (!(pMyList->GetCount() == 0))
		pMyList->RemoveHead();
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_Keyboard")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( INPUT_DEVICE_KEYBOARD);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				myObject.SetPointingType( NOT_AVAILABLE);
				myObject.SetPointingInterface( NOT_AVAILABLE);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotal += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_Keyboard object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	// Get pointing devices
	AddLog( _T( "WMI GetInputDevices: Trying to find Win32_PointingDevice WMI objects..."));
	try
	{
		uIndex = 0;
		if (m_dllWMI.BeginEnumClassObject( _T( "Win32_PointingDevice")))
		{
			while (m_dllWMI.MoveNextEnumClassObject())
			{
				myObject.SetType( INPUT_DEVICE_POINTING);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Manufacturer"));
				myObject.SetManufacturer( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Caption"));
				myObject.SetCaption( csBuffer);
				csBuffer = m_dllWMI.GetClassObjectStringValue( _T( "Description"));
				myObject.SetDescription( csBuffer);
				dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "PointingType"));
				myObject.SetPointingType( dwValue);
				dwValue = m_dllWMI.GetClassObjectDwordValue( _T( "DeviceInterface"));
				myObject.SetPointingInterface( dwValue);
				pMyList->AddTail( myObject);
				uIndex ++;
			}
			m_dllWMI.CloseEnumClassObject();
		}
		if (uIndex > 0)
		{
			uTotal += uIndex;
			AddLog( _T( "OK (%u objects)\n"), uIndex);
		}
		else
			AddLog( _T( "Failed because no Win32_PointingDevice object !\n"));
	}
	catch (CException *pEx)
	{
		pEx->Delete();
		AddLog( _T( "Failed because unknown exception !\n"));
	}
	if (uTotal > 0)
	{
		AddLog( _T( "WMI GetInputDevices: OK\n"));
		return TRUE;
	}
	AddLog( _T( "WMI GetInputDevices: Failed because no input device found !\n"));
	return FALSE;
}
