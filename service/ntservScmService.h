/*
Module : NTSERVSCMSERVICE.H
Purpose: Defines the interface for the class CNTScmService.
Created: PJN / 14-07-1998

Copyright (c) 1997 - 2006 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/

#ifndef __NTSERVSCMSERVICE_H__
#define __NTSERVSCMSERVICE_H__

#ifndef CNTSERVICE_EXT_CLASS
#define CNTSERVICE_EXT_CLASS
#endif



////////////////////////////// Includes //////////////////////////////////////////////

#include "ntservDefines.h"



////////////////////////////// Forward declaration ///////////////////////////////////

class CNTServiceControlManager;



////////////////////////////// Classes ///////////////////////////////////////////////

//An encapsulation of a service as returned from querying the SCM (i.e. an SC_HANDLE)
class CNTSERVICE_EXT_CLASS CNTScmService
{
public:
//typedefs
  typedef BOOL (CALLBACK* ENUM_SERVICES_PROC)(DWORD dwData, ENUM_SERVICE_STATUS& ss);

//Constructors / Destructors
	CNTScmService();
	~CNTScmService();

//Methods
  //Releases the underlying SC_HANDLE
  void Close();

	//Allows access to the underlying SC_HANDLE representing the service
	operator SC_HANDLE() const;

	//Attach / Detach support from an SDK SC_HANDLE
	BOOL Attach(SC_HANDLE hService);
	SC_HANDLE Detach();

	//Changes the configuration of this service
	BOOL ChangeConfig(DWORD dwServiceType,	      // type of service 
									  DWORD dwStartType,	        // when to start service 
 									  DWORD dwErrorControl,	      // severity if service fails to start 
 									  LPCTSTR lpBinaryPathName,	  // pointer to service binary file name 
									  LPCTSTR lpLoadOrderGroup,	  // pointer to load ordering group name 
									  LPDWORD lpdwTagId,	        // pointer to variable to get tag identifier 
 									  LPCTSTR lpDependencies,	    // pointer to array of dependency names 
 									  LPCTSTR lpServiceStartName, // pointer to account name of service 
 									  LPCTSTR lpPassword,	        // pointer to password for service account  
 									  LPCTSTR lpDisplayName 	    // pointer to display name 
                    ) const;

	//Send a defined control code to the service
	BOOL Control(DWORD dwControl);

	//These functions call Control() with the 
	//standard predefined control codes
	BOOL Stop() const;			 //Ask the service to stop
	BOOL Pause() const;			 //Ask the service to pause
	BOOL Continue() const;	 //Ask the service to continue
	BOOL Interrogate() const; //Ask the service to update its status to the SCM

  //Waits for a service to stop with a configurable timeout
  BOOL WaitForStop(DWORD dwTimeout);

  //Waits for a service to have a certain status (with a configurable timeout)
  BOOL WaitForServiceStatus(DWORD dwTimeout, DWORD dwWaitForStatus, DWORD dwPollingInterval = 250);

	//Start the execution of the service
	BOOL Start(DWORD dwNumServiceArgs,	      // number of arguments 
			       LPCTSTR* lpServiceArgVectors 	// address of array of argument string pointers  
		         ) const;	

	//Determines what Control codes this service supports
	BOOL AcceptStop(BOOL& bStop);                   //Ask the service can it stop
	BOOL AcceptPauseContinue(BOOL& bPauseContinue);	//Ask the service can it pause continue
	BOOL AcceptShutdown(BOOL& bShutdown);           //Ask the service if it is notified of shutdowns

	//Get the most return status of the service reported to the SCM by this service
	BOOL QueryStatus(SERVICE_STATUS& ServiceStatus) const;

	//Get the configuration parameters of this service from the SCM
	BOOL QueryConfig(LPQUERY_SERVICE_CONFIG& lpServiceConfig) const;

	//Add a new service to the SCM database
	BOOL Create(CNTServiceControlManager& Manager, // handle to service control manager database  
 						  LPCTSTR lpServiceName,	         // pointer to name of service to start 
						  LPCTSTR lpDisplayName,	         // pointer to display name 
						  DWORD dwDesiredAccess,	         // type of access to service 
						  DWORD dwServiceType,	           // type of service 
						  DWORD dwStartType,	             // when to start service 
						  DWORD dwErrorControl,	           // severity if service fails to start 
						  LPCTSTR lpBinaryPathName,	       // pointer to name of binary file 
						  LPCTSTR lpLoadOrderGroup,	       // pointer to name of load ordering group 
						  LPDWORD lpdwTagId,	             // pointer to variable to get tag identifier 
						  LPCTSTR lpDependencies,	         // pointer to array of dependency names 
						  LPCTSTR lpServiceStartName,	     // pointer to account name of service 
						  LPCTSTR lpPassword 	             // pointer to password for service account 
              );

	//Mark this service as to be deleted from the SCM.
	BOOL Delete() const;

	//Enumerate the services that this service depends upon
	BOOL EnumDependents(DWORD dwServiceState,	                // state of services to enumerate 
                      DWORD dwUserData,                     // User defined data
 										  ENUM_SERVICES_PROC lpEnumServicesFunc // The callback function to use
                      ) const;

	//Get the security information associated with this service
	BOOL QueryObjectSecurity(SECURITY_INFORMATION dwSecurityInformation,	// type of security information requested  
			                     PSECURITY_DESCRIPTOR& lpSecurityDescriptor	  // address of security descriptor 
						   					   ) const;

	//Set the security descriptor associated with this service
	BOOL SetObjectSecurity(SECURITY_INFORMATION dwSecurityInformation,	// type of security information requested  
			                   PSECURITY_DESCRIPTOR lpSecurityDescriptor 	// address of security descriptor 
		                     ) const;

  //Windows 2000 specific functions
  BOOL QueryDescription(CString& sDescription) const;
  BOOL QueryFailureActions(LPSERVICE_FAILURE_ACTIONS& lpActions) const;
  BOOL ChangeDescription(const CString& sDescription);
  BOOL ChangeFailureActions(SERVICE_FAILURE_ACTIONS& Actions);
  BOOL QueryStatus(SERVICE_STATUS_PROCESS& ssp) const;

protected:
  SC_HANDLE m_hService;
};

#endif //__NTSERVSCMSERVICE_H__
