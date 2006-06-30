
//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================


#ifndef __OCSWMI_H_
#define __OCSWMI_H_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the OCSWMI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// OCSWMI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef OCSWMI_EXPORTS
#define OCSWMI_API __declspec(dllexport)
#else
#define OCSWMI_API __declspec(dllimport)
#endif

#include "wbemcli.h"        // WMI interface declarations

// This class is exported from the OcsWmi.dll
class OCSWMI_API COcsWmi
{
public:
	COcsWmi();
	virtual ~COcsWmi();

	BOOL ConnectWMI( LPCTSTR lpstrNameSpace);
	BOOL DisconnectWMI();

	BOOL BeginEnumClassObject( LPCTSTR lpstrObject);
	BOOL MoveNextEnumClassObject();
	BOOL CloseEnumClassObject();

	LPCTSTR GetClassObjectStringValue( LPCTSTR lpstrProperty);
	LPCTSTR GetRefElementClassObjectStringValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);

	DWORD GetClassObjectDwordValue( LPCTSTR lpstrProperty);
	DWORD GetRefElementClassObjectDwordValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);

	__int64 GetClassObjectI64Value( LPCTSTR lpstrProperty);
	__int64 GetRefElementClassObjectI64Value( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);
	
	unsigned __int64 GetClassObjectU64Value( LPCTSTR lpstrProperty);
	unsigned __int64 GetRefElementClassObjectU64Value( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);

	HRESULT GetLastErrorWMI();

protected: // Methods
	LPCTSTR strVariant( VARIANT pVal);
	LPCTSTR strVariantArray( VARIANT pVal);
	LPCTSTR strCimArrayValue( VARIANT &pVal, CIMTYPE &pType);
	LPCTSTR strCimValue( VARIANT &pVal, CIMTYPE &pType);
	DWORD dwCimValue( VARIANT &pVal, CIMTYPE &pType);
	__int64 i64CimValue( VARIANT &pVal, CIMTYPE &pType);
	unsigned __int64 u64CimValue( VARIANT &pVal, CIMTYPE &pType);

protected: // Attributes
	IWbemServices *m_pIWbemServices;
	IEnumWbemClassObject *m_pEnumClassObject;
	IWbemClassObject *m_pClassObject;
	HRESULT m_hResult;
	CString m_csResult;
};

#endif //__OCSWMI_H_