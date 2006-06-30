// Document modified at : Wednesday, March 29, 2006 1:46:54 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2006
// Web: http://ocsinventory.sourceforge.net

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

// Wmi.h: interface for the CWmi class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WMI_H__73831499_4F80_4168_AB5B_6CB71A878DE1__INCLUDED_)
#define AFX_WMI_H__73831499_4F80_4168_AB5B_6CB71A878DE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SysInfoClasses.h"


class DLL_CLASS CWmi  
{
public: // Methods
	//////////////////////////////////
	// Standard contructor/destructor
	//////////////////////////////////
	CWmi();
	virtual ~CWmi();

	//////////////////////////////////
	// Connection methods
	//////////////////////////////////

	BOOL Connect( LPCTSTR lpstrDevice = NULL);
	BOOL IsWmiConnected();
	BOOL Disconnect();

	//////////////////////////////////
	// Get attributes values
	//////////////////////////////////

	BOOL GetBiosInfo( CBios *pMyBios);
	BOOL GetDomainOrWorkgroup(CString &csDomain);
	BOOL GetInputDevices( CInputDeviceList *pMyList);
	UINT GetOS( CString &csName, CString &csVersion, CString &csComment, CString &csDescription);
	BOOL GetSystemPorts( CSystemPortList *pMyList);
	BOOL GetPrinters( CPrinterList *pMyList);
	DWORD GetProcessors( CString &csProcType, CString &csProcSpeed);
	BOOL GetMemorySlots( CMemorySlotList *pMyList);
	BOOL GetModems( CModemList *pMyList);
	BOOL GetMonitors( CMonitorList *pMyList);
	BOOL GetNetworkAdapters( CNetworkAdapterList *pMyList);
	BOOL GetSoundDevices( CSoundDeviceList *pMyList);
	BOOL GetStoragePeripherals( CStoragePeripheralList *pMyList);
	BOOL GetSystemControllers( CSystemControllerList *pMyList);
	BOOL GetSystemSlots( CSystemSlotList *pMyList);
	BOOL GetVideoAdapters( CVideoAdapterList *pMyList);
	BOOL GetWindowsRegistration( CString &csCompany, CString &csUser, CString &csSN);
	BOOL IsNotebook();

protected: // Methods
	BOOL ParseChassisType( CString &csType);

protected: // Attributes
	COcsWmi m_dllWMI;	// Class to access WMI
	BOOL m_bConnected;	// Do we are already connected to WMI namespace
};
#endif // !defined(AFX_WMI_H__73831499_4F80_4168_AB5B_6CB71A878DE1__INCLUDED_)

