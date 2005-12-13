// Document modified at : Sunday, November 23, 2003 9:37:14 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================


#include "stdafx.h"
#include "OcsWmi.h"
#include "OcsWmiDll.h"

/////////////////////////////////////////////////////////////////////////////
// The one and only COcsWmiApp object

COcsWmiApp theApp;

BOOL WINAPI WMIConnect( LPCTSTR lpstrNameSpace)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.ConnectWMI( lpstrNameSpace);
}

BOOL WINAPI WMIDisconnect()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.DisconnectWMI();
}

BOOL WINAPI WMIBeginEnumClassObject( LPCTSTR lpstrObject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.BeginEnumClassObject( lpstrObject);
}

BOOL WINAPI WMIMoveNextEnumClassObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.MoveNextEnumClassObject();
}

BOOL WINAPI WMICloseEnumClassObject()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.CloseEnumClassObject();
}

LPCTSTR WINAPI WMIGetClassObjectStringValue( LPCTSTR lpstrProperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.GetClassObjectStringValue( lpstrProperty);
}

LPCTSTR WINAPI WMIGetRefElementClassObjectStringValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.GetRefElementClassObjectStringValue( lpstrRefElement, lpstrProperty);
}

DWORD WINAPI WMIGetClassObjectDwordValue( LPCTSTR lpstrProperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.GetClassObjectDwordValue( lpstrProperty);
}

DWORD WINAPI WMIGetRefElementClassObjectDwordValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.GetRefElementClassObjectDwordValue( lpstrRefElement, lpstrProperty);
}

HRESULT WINAPI WMIGetLastError()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	// normal function body here
	return theApp.GetLastErrorWMI();
}



