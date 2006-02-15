// Document modified at : Sunday, November 23, 2003 9:38:14 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================



# ifndef _OCSWMIDLL_HEADER_
#define _OCSWMIDLL_HEADER_

BOOL WINAPI WMIConnect( LPCTSTR lpstrNameSpace);
BOOL WINAPI WMIDisconnect();

BOOL WINAPI WMIBeginEnumClassObject( LPCTSTR lpstrObject);
BOOL WINAPI WMIMoveNextEnumClassObject();
BOOL WINAPI WMICloseEnumClassObject();

LPCTSTR WINAPI WMIGetClassObjectStringValue( LPCTSTR lpstrProperty);
LPCTSTR WINAPI WMIGetRefElementClassObjectStringValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);

DWORD WINAPI WMIGetClassObjectDwordValue( LPCTSTR lpstrProperty);
DWORD WINAPI WMIGetRefElementClassObjectDwordValue( LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty);

HRESULT WINAPI WMIGetLastError();

#endif // _OCSWMIDLL_HEADER_