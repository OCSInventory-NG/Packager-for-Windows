// Document modified at : Sunday, January 04, 2004 8:05:06 PM , by user : Didier LIROULET , from computer : SNOOPY-XP-PRO

//====================================================================================
// Open Computer and Software Inventory
// Copyleft Didier LIROULET 2003
// Web: http://ocsinventory.sourceforge.net
// E-mail: ocsinventory@tiscali.fr

// This code is open source and may be copied and modified as long as the source
// code is always made freely available.
// Please refer to the General Public Licence http://www.gnu.org/ or Licence.txt
//====================================================================================

//  OCSInventory.cpp : Defines the class behaviors for the application.
//

#include "StdAfx.h"
#include "Resource.h"		// main symbols

#include "SysInfo.h"
#include "StoreInteract.h"
#include "XMLInteract.h"
#include "OCSInventory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COCSInventoryApp

// For XML support in the agent
BOOL COCSInventoryApp::ConnectDB(LPCTSTR lpstrExecutionFolder)
{	
	AddLog( _T( "Creating CXMLInteract object..."));
	m_pTheDB = new CXMLInteract();
	m_pTheDB->SetCmdL(this->m_lpCmdLine);
	AddLog( _T( "OK\nTrying to open database on folder <%s> with XML..."),
   lpstrExecutionFolder);
	m_pTheDB->OpenDB( lpstrExecutionFolder);
	AddLog( _T( "OK.\n"));
	// Load settings from XML
	return m_pTheDB->GetSettings();	
}
