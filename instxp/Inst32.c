/*******************************************************************
*
*			INST32.C
*			
*			programme d'interface entre SDPC et un programme retournant
*			des codes dans un fichier log
*
*			Creation : 1.0.0	1998/08/26		BLR   
*												Version 16 et 32 bits 
*                                        
*			Modif	 : 1.0.1	1998/09/02		BLR	 
*												Version 16 bits uniquement 
*												gestion d'enchainement de process
*
*			Modif	 : 1.0.2	1998/10/13		BLR	 
*												bug code erreur ss texte 
*												bug fichier /err: pas créé
*												bug instnt dans fichier ressource
*
*			Modif	 : 1.0.3	1998/10/21		BLR	 
*												installShield renvoie code erreur negatif 
*												nombre de tache gerer passe de 10 a 20
*			Mofif	 : 2.0.0	1999/04/27		BLR
*												Version 32 bits  Windows 95 uniquement
*
*			Mofif	 : 2.2.0	2001/10/02		BLR
*												Version 32 bits  Windows Millenium 
*
*			Mofif	 : 2.3.0	2001/12/07		BLR
*												Version 32 bits  Windows XP 
*******************************************************************/
#define DEF_MODULE_WINCOM 1
#include "inst32.h"

void FinControle(void);
void CreeTimer( HWND hwnd, UINT uiID);
LONG ListConsult(void);

static HANDLE hProcess;        


/*void Trace(void)
{ 
HFILE hFile; 
OFSTRUCT of;
HANDLE         hSnapshot = NULL; 
BOOL           bRet      = FALSE; 
PROCESSENTRY32 pe32;
char by[1024];

	hFile = OpenFile( "c:\\trace.txt", &of, OF_READWRITE);
	if ( hFile == HFILE_ERROR)
		return;
	_llseek(hFile, 0L, FILE_END);
				_lwrite( hFile, "----------", 10);
	    hSnapshot = pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (hSnapshot == INVALID_HANDLE_VALUE) 
        return ; 
 
    pe32.dwSize = sizeof(PROCESSENTRY32); 

    for (	bRet = pProcess32First(hSnapshot, &pe32);
			bRet;
			bRet = pProcess32Next(hSnapshot, &pe32))
			{
				wsprintf( by, "ID %lu PID %lu %s\r\n",pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
				_lwrite( hFile, by, strlen(by));
			}
    CloseHandle (hSnapshot); 

	_lclose( hFile);
	
}*/


/*
void Trace1(void)
{ 
HFILE hFile; 
OFSTRUCT of;
HANDLE         hSnapshot = NULL; 
BOOL           bRet      = FALSE; 
PROCESSENTRY32 pe32; 
char by[1024];
LONG	lI;

	hFile = OpenFile( "c:\\trace.txt", &of, OF_READWRITE);
	if ( hFile == HFILE_ERROR)
		return;
	_llseek(hFile, 0L, FILE_END);
				wsprintf( by, "============== Max : %ld, Actif : %ld\r\n", lTabMaxProcess, ListConsult());
				_lwrite( hFile, by, strlen(by));
	for ( lI = 0; lI < lTabMaxProcess ; lI++)
	{
			if (pTabProcess[lI].ProcessID != PROCESS_NULL)
			{
				wsprintf( by, " ID %lu PID %lu %s bPresent %d\r\n",pTabProcess[lI].ProcessID, pTabProcess[lI].ParentProcessID, pTabProcess[lI].szExeFile, pTabProcess[lI].bPresent);
				_lwrite( hFile, by, strlen(by));
			}
	}
	_lclose( hFile);
	
}*/
#define printf printf
BOOL InitToolHelp(void)
{

	HANDLE hKernel = NULL; 

    if ((hKernel = GetModuleHandle("KERNEL32.DLL")) != NULL)
	{ 
        pCreateToolhelp32Snapshot =  (CREATESNAPSHOT)GetProcAddress(hKernel, "CreateToolhelp32Snapshot");
		if (pCreateToolhelp32Snapshot	== NULL)
		{
			// MessageBox( NULL, "CreateToolhelp32Snapshot not found in KERNEL32.DLL", "Inst32.exe", MB_OK);
			return FALSE;
		}
        pProcess32First = (PROCESSWALK)GetProcAddress(hKernel, "Process32First"); 
		if (pCreateToolhelp32Snapshot	== NULL)
		{
			// MessageBox( NULL, "Process32First not found in KERNEL32.DLL", "Inst32.exe", MB_OK);
			return FALSE;
		}
        pProcess32Next  = (PROCESSWALK)GetProcAddress(hKernel, "Process32Next"); 
		if (pCreateToolhelp32Snapshot	== NULL)
		{
			// MessageBox( NULL, "Process32Next not found in KERNEL32.DLL", "Inst32.exe", MB_OK);
			return FALSE;
		}
    } 
    else 
        return FALSE;
	return TRUE;
}
 

/*******************************************************************
*
*			ListInit											 *
*
*			initialise le table des taches
*
*		
*			parametre(s):   
*					aucun					
*
*			retour:
*					rien
*
*******************************************************************/
BOOL ListInit(void) 
{ 

LONG	lI;
	
	lTabMaxProcess = TAB_AJOUT;
	pTabProcess =(SPROCESS_ID *)AllocPtr( sizeof(SPROCESS_ID)*lTabMaxProcess);

	if (pTabProcess == NULL)
		return FALSE;
	for ( lI = 0; lI < lTabMaxProcess; lI++)
	{
		pTabProcess[lI].ProcessID = PROCESS_NULL;
	}
    return TRUE;
} 

/*******************************************************************
*
*			ListPrepare 										 *
*
*			initialise le table des taches
*
*		
*			parametre(s):   
*					aucun					
*
*			retour:
*					rien
*
*******************************************************************/
void ListPrepare(void)
{

	LONG	lI;			
	
	for ( lI = 0; lI < lTabMaxProcess ; lI++)
	{
		pTabProcess[lI].bPresent = FALSE;
	}
}


/*******************************************************************
*
*			ListDel											 *
*
*			retire les taches non trouve de la table des taches
*
*		
*			parametre(s):   
*					aucun					
*
*			retour:
*					Nbre de process restant dans la table
*
*******************************************************************/
LONG ListDel(void)
{

	LONG	lI;		
	LONG	lNb = 0;	
	
	for ( lI = 0; lI < lTabMaxProcess ; lI++)
	{
		if ( pTabProcess[lI].bPresent && strcmp(pTabProcess[lI].szExeFile, "")!= 0)
		{
			lNb++;
		}
	}
return lNb;
}


/*******************************************************************
*
*			ListProcessExist											 *
*
*			process existe dans la table 
*
*		
*			parametre(s):   
*					ProcessID			numero de process
*
*			retour:
*					retourne l'index
*					-1 non trouve
*
*******************************************************************/
LONG ListProcessExist( DWORD processID)
{

LONG	lI;			
	
	for ( lI = 0; lI < lTabMaxProcess ; lI++)
	{
		if (pTabProcess[lI].ProcessID == processID)
		{
			pTabProcess[lI].bPresent = TRUE;
			return lI;
		}
	}
return -1;
}

LONG ListProcessExistNom(char *NomProcess)
{

	LONG lI;			
	
	for (lI = 0; lI < lTabMaxProcess ; lI++)
	{
		if (!strcmp(pTabProcess[lI].szExeFile, NomProcess))
		{
			pTabProcess[lI].bPresent = TRUE;
			return lI;
		}
	}
return -1;
}


/*******************************************************************
*
*			ListParentProcessExist											 *
*
*			le process parent existe dans la table 
*
*		
*			parametre(s):   
*					ProcessID			numero de process parent
*
*			retour:
*					retourne l'index
*					-1 non trouve
*
*******************************************************************/
LONG ListParentProcessExist( DWORD ParentProcessID)
{

	LONG	lI;			
	
	for ( lI = 0; lI < lTabMaxProcess ; lI++)
	{
		if (pTabProcess[lI].ProcessID == ParentProcessID)
		{
			return lI;
		}
	}
return -1;
}

/*******************************************************************
*
*			ListAdd											 *
*
*			Ajoute dans la table des taches le numero de tache
*
*		
*			parametre(s):   
*					ProcessID			numero de process
*					ParentProcessID		numero du process parent			
*
*			retour:
*					TRUE	reussi
*					FALSE	echec
*
*******************************************************************/
BOOL ListAdd( DWORD ProcessID, DWORD ParentProcessID, char *pNom)
{

	LONG	lI;	
	
	for ( lI=0; lI < lTabMaxProcess ; lI++)
	{
		if ( pTabProcess[lI].ProcessID == PROCESS_NULL)
		{
			pTabProcess[lI].ProcessID = ProcessID;
			pTabProcess[lI].ParentProcessID = ParentProcessID;
			Strcpy(pTabProcess[lI].szExeFile, pNom);; 
			pTabProcess[lI].bPresent = TRUE;
			return TRUE;
		}
	}

	lTabMaxProcess += TAB_AJOUT;
	pTabProcess =(SPROCESS_ID *)ReAllocPtr( pTabProcess, sizeof(SPROCESS_ID)*lTabMaxProcess);
	if (pTabProcess == NULL)
		return FALSE;
	pTabProcess[lTabMaxProcess - TAB_AJOUT -1].ProcessID = ProcessID;
	pTabProcess[lTabMaxProcess - TAB_AJOUT -1].ParentProcessID = ParentProcessID;
	pTabProcess[lTabMaxProcess - TAB_AJOUT -1].bPresent = TRUE;
	return TRUE;

}


LONG ListConsult(void)
{

    HANDLE         hSnapshot = NULL; 
    BOOL           bRet      = FALSE; 
    PROCESSENTRY32 pe32; 
	
    hSnapshot = pCreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); 
    if (hSnapshot == INVALID_HANDLE_VALUE) 
        return 0; 
 
    pe32.dwSize = sizeof(PROCESSENTRY32); 

	ListPrepare();
    for (	bRet = pProcess32First(hSnapshot, &pe32);
			bRet;
			bRet = pProcess32Next(hSnapshot, &pe32))
			{
				if ( ListProcessExist( pe32.th32ProcessID) == -1)
				{
					if ( ListParentProcessExist( pe32.th32ParentProcessID) != -1)
					{
						ListAdd( pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
					}
				}
			}
    CloseHandle (hSnapshot); 
	return ListDel();
}


/*******************************************************************
*
*			FichierErr									 *
*
*			Ecriture dans le fichier d'erreur dont 
*			le nom est passe en parametre /err:
*
*		
*			parametre(s):
*					dwErr			numero d'erreur
*
*			retour:
*					rien
*
*******************************************************************/
void FichierErr( DWORD dwErr)
{ 

	HANDLE 		hFile; 
	BYTE	    byText[30];
	
	hFile = CreateFile( pErr,  GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ( hFile == INVALID_HANDLE_VALUE)
		return;        
	wsprintf( byText, "%lu\r\n", dwErr);
	SetEndOfFile ( hFile);
	WriteFile( hFile, byText, strlen(byText), NULL,  NULL);
	CloseHandle( hFile);
}

/*******************************************************************
*
*			LibereMem									 *
*
*			libere la memoire et met NULL dans le pointeur
*
*		
*			parametre(s):
*					pMem			memoire a liberer
*
*			retour:
*					rien
*
*******************************************************************/
void LibereMem( LPVOID * pMem)
{
	if ( *pMem != NULL)
	{
		FreePtr( *pMem);
		*pMem = NULL;
	}
}


/*******************************************************************
*
*			LibereArgument
*
*			libere la table pArgv
*
*		
*			parametre(s):
*						aucun
*
*			retour:
*						rien
*
*******************************************************************/
void LibereArgument(void)
{       

	int		iI;

	if ( pArgv == NULL)
		return;
	for ( iI = 0; iI < iArgc; iI++)
	{
		if ( pArgv[iI] != NULL);
			LibereMem( &pArgv[iI]);
	}                              
	FreePtr( pArgv);
	pArgv = NULL;
}       


 /*******************************************************************
*
*			FichierExist
*
*			permet de savoir si un fichier existe
*
*		
*			parametre(s):
*					pNom			nom du fichier
*
*			retour:
*					TRUE existe, FALSE n'existe pas
*
*******************************************************************/
BOOL FichierExist( LPSTR pNom)
{

	WIN32_FIND_DATA fd;
	HANDLE			hff;
	BOOL			bRet = FALSE;
	
	if ( ( hff = FindFirstFile( pNom, &fd)) != INVALID_HANDLE_VALUE)
	{
		bRet = TRUE;
		FindClose( hff);
	}
return bRet;
}        


/*******************************************************************
*
*			FichierEfface
*
*			efface un fichier
*
*		
*			parametre(s):
*					pNom			nom du fichier
*
*			retour:
*					TRUE operation reussi, FALSE echec
*
*******************************************************************/
BOOL FichierEfface( LPSTR pNom)
{         
	if ( !FichierExist( pNom))
		return TRUE;
		
	if ( !DeleteFile( pNom))
		return FALSE;
	if ( FichierExist( pNom))
		return FALSE;
	else
		return TRUE;	

}                                

/*******************************************************************
*
*			FichierFermeture
*
*			ferme un fichier et met dans le handle la valeur HFILE_ERROR
*
*		
*			parametre(s):
*					phFile			handle du fichier
*
*			retour:
*					rien
*
*******************************************************************/
void FichierFermeture( HANDLE *phFile)
{
	if ( *phFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle( *phFile);
		*phFile = INVALID_HANDLE_VALUE;
	}
}                   


int Arret( int iCodErr, int iRetour)
{                 

	if ( iRet == ERR_INIT)
		iRet = iCodErr;
	FichierFermeture( &hFile);
	LibereMem(  &pExec);
	LibereMem( &pLog); 
	LibereMem( &pErr); 
	LibereArgument();
	return iRetour;
}
        

                    
/*******************************************************************
*
*			ChercheNoSpace
*
*			recherche le premier caractere different de espace ou tabulation
*			dans une chaine
*		
*			parametre(s):
*					pDebut			debut de la recherche
*
*			retour:
*					pointeur sur le caractere different de espace ou tabulation
*
*******************************************************************/
char *ChercheNoSpace( char *pDebut)
{    
	if ( pDebut == NULL)
		return NULL;
	for( ; *pDebut != '\0' && isspace(*pDebut); pDebut++);
	return pDebut;
}

/*******************************************************************
*
*			ChercheFinChaine
*
*			recherche le caractere "
*
*		
*			parametre(s):
*					pDebut			debut de la recherche
*
*			retour:
*					pointeur sur le caractere "
*
*******************************************************************/
char *ChercheFinChaine( char *pDebut)
{    
	if ( pDebut == NULL)
		return NULL;
	for( pDebut++; *pDebut != '\0' && *pDebut != '"'; pDebut++);
	return pDebut;
}

/*******************************************************************
*
*			ChercheFinArgument
*
*			recherche un argument sur une ligne de commande
*
*		
*			parametre(s):
*					pDebut			debut de la recherche
*
*			retour:
*					pointeur la fin de l'argument
*
*******************************************************************/
char *ChercheFinArgument( char *pDebut)
{   
	if ( pDebut == NULL)
		return NULL;
	for( ; *pDebut != '\0' && !isspace(*pDebut); pDebut++)
		if ( *pDebut == PARAM_EXEC_LIMIT)
			pDebut = ChercheFinChaine( pDebut);
	return pDebut;
}
                   

/*******************************************************************
*
*			SetArgument
*
*			met une argument dans pArgv
*
*		
*			parametre(s):
*					pDeb			debut de l'argument
*					dwLen			longueur de l'argument
*
*			retour:
*					TRUE Ok, FALSE echec
*
*******************************************************************/
BOOL SetArgument( LPSTR pDeb, DWORD dwLen)
{
	if (( pArgv[iArgc] = AllocPtr( dwLen+1)) == NULL)		
		return FALSE;                                               
	Memcpy(pArgv[iArgc], pDeb, dwLen);
	return TRUE;
}


/*******************************************************************
*
*			GetLigneCommand
*
*			permet d'obtenir une analyse de la commande (cf UNIX)
*			Le resultat est mis dans pArgv et iArgc
*
*		
*			parametre(s):
*					hInst				instance en du programme
*					pCmd				ligne de commande
*
*			retour:
*					0 echec, 1 Ok
*
*******************************************************************/
int GetLigneCommand( HINSTANCE hInst, LPSTR pCmd)
{                                 
	DWORD	dwLen;
	LPSTR	pDeb;
	LPSTR   pFin;
	LPSTR   pFinCmd;

    pFinCmd = pCmd + Strlen( pCmd);
	pArgv = NULL;                               
	iArgc = 0;
	if ((dwLen = GetModuleFileName( hInst, byNomModule, sizeof(byNomModule))) <= 0)
		return 0;                                               
	if (( pArgv = (LPSTR*)AllocPtr(sizeof(LPSTR)*MAX_ARG))  == NULL)		
		return 0;                                               
	                                  
	if ( !SetArgument( byNomModule, dwLen))
		return 0;                                  
	iArgc = 1; 
	if ( pCmd != NULL)
		{
			for ( pDeb = pCmd; *pDeb != '\0' && pDeb < pFinCmd && iErr == ERR_OK; pDeb = pFin + 1)
			{                               
				pDeb = ChercheNoSpace( pDeb);
            	pFin = ChercheFinArgument( pDeb);
            	if ( iArgc < MAX_ARG)
            	{    
					if ( !SetArgument( pDeb, pFin-pDeb))
						return 0;
            		iArgc++;
            	}
			}			
		}	
	return iArgc;		
}



/*******************************************************************
*
*			GetIndexParam
*
*			retour un index selon le argument connu ou non
*
*		
*			parametre(s):
*					pCmd			argument
*					iLenParam		longueur du l'argument
*
*			retour:
*					index ou PARAM_ERR_INDEX erreur
*
*******************************************************************/
int GetIndexParam( char *pCmd, int iLenParam)
{   
	if ( pCmd != NULL)
	{                                                        
		if ( Memcmp(pCmd,PARAM_EXEC,min(sizeof(PARAM_EXEC)-1,iLenParam))==0)
			return PARAM_EXEC_INDEX;
		if ( Memcmp( pCmd, PARAM_LOG, min(sizeof(PARAM_LOG)-1,iLenParam))==0)
			return PARAM_LOG_INDEX;
		if ( Memcmp( pCmd, PARAM_ERR, min(sizeof(PARAM_ERR)-1,iLenParam))==0)
			return PARAM_ERROR_INDEX;
	}
	return PARAM_ERR_INDEX;
}


/*******************************************************************
*
*			TraiteUneLigne
*
*			analyse une ligne du fichier log afin de retrouver un code retour
*
*		
*			parametre(s):
*					pLigne			une ligne du fichier log
*
*			retour:
*					rien
*
*******************************************************************/
int TraiteUneLigne( LPSTR pLigne)
{       

int iNewErr;          
int iNb;      
LPSTR pFin;
         	     
	if (Memcmp( pLigne, DEBUT_CODE_ERR, sizeof(DEBUT_CODE_ERR)-1) != 0)
		return 1;
	for ( pLigne += sizeof(DEBUT_CODE_ERR)-1, pFin = pLigne ; isspace(*pFin); pFin++);
	for ( iNb = 0; isdigit(*pFin) || *pFin == '-'; pFin++, iNb++);
	if ( iNb == 0)
		return Arret( iRet = ERR_LIGNE_SS_CODE, 0);
	if ( *pFin != ' ' && *pFin != '\0')
		return Arret( ERR_LIGNE_FORMAT, 0);
	*pFin = '\0';
	iNewErr = atoi( pLigne);

	if (iNewErr < 0)
		return Arret( ERR_SHIELD, 0);
			
	if ( (iNewErr == 0) || (iNewErr >= ERR_MIN_INSTALL && iNewErr <= ERR_MAX_INSTALL))
	{
		if ( iNewErr > iRet)
			iRet = iNewErr;
		return 1;	
	}
	else
	{
		if ( iNewErr >= ERR_MIN_BULL && iNewErr <= ERR_MAX_BULL)
			return Arret( ERR_NUM_BULL, 0);
		if ( iNewErr >= ERR_MIN_PRG && iNewErr <= ERR_MAX_PRG)
			return Arret( ERR_NUM_PRG, 0);
	}
	return Arret( ERR_NUM_MAX, 0);
}
        
/*******************************************************************
*
*			AnalyseLog
*
*			analyse du fichier log
*
*		
*			parametre(s):
*					pNom			nom du fichier log
*
*			retour:
*					0 echec, 1 Ok
*
*******************************************************************/
int AnalyseLog( LPSTR pNom)
{
	char		byLu[2];                               
	int			iIndex;                                                              
	BOOL		bReadOk;
	int			iRetour;
	HANDLE		hFile;
	DWORD		dwErr;
	DWORD		dwParam;

	if ( (hFile = CreateFile(  pNom,  GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
		return Arret( ERR_OUVERT_LOG, 0);
	      
	Memset( byLigne, '\0', sizeof(byLigne));
	bReadOk = ReadFile( hFile, &byLu,1, &dwParam, NULL);
	dwErr = GetLastError();
	for ( iRetour = 1, iIndex = 0; bReadOk && iRetour == 1 && dwParam == 1; dwParam = 0, bReadOk = ReadFile( hFile, &byLu,1, &dwParam, NULL))
	{
		switch( byLu[0])
		{
		case '\r':
			break;
		case '\n':
			iRetour = TraiteUneLigne( byLigne);
			Memset( byLigne, '\0', sizeof(byLigne));
			iIndex = 0;
			break;
		default:    
			if ( iIndex < MAX_LIGNE)
			{
				byLigne[iIndex] = byLu[0];
				iIndex++;		
			}
			else
				return Arret( ERR_LONG_LIGNE, 0);
		}
	}               
	FichierFermeture( &hFile);
	if ( iIndex > 0 && iRetour == 1)
		TraiteUneLigne( byLigne);
	
	return 1;
}                                                       

/*******************************************************************
*
*			SetExeLog
*
*			affectation de pExe et pLog
*
*		
*			parametre(s):
*					aucun
*
*			retour:
*					1 Ok, 0 echec
*
*******************************************************************/
int SetExeLog(void) 
{           

	LPSTR 	pTmp;                                           
	int		iI;
	
	for ( iI = 1; iI < iArgc; iI++)
	{ 
		pTmp = pArgv[iI];
		switch( GetIndexParam( pTmp, Strlen(pTmp)))
		{
		case -1: 
			return Arret( ERR_PARAM_INCONNU, 0);
			break;  
			
		case 0:                                 
	        pTmp += (sizeof(PARAM_EXEC)-sizeof(char));
	        if ( *pTmp == PARAM_EXEC_LIMIT )
	        {
	        	pTmp++;
	        	pTmp[Strlen(pTmp)-1] = '\0';
	        }
			if ( (pExec = AllocPtr( Strlen(pTmp)+1)) == NULL)
				return Arret( ERR_ALLOC, 0); 
			Strcpy( pExec, pTmp);
			break;
			
		case 1:
	        pTmp += (sizeof(PARAM_LOG)-sizeof(char));
			if ( (pLog = AllocPtr( Strlen(pTmp)+1)) == NULL)
				return Arret( ERR_ALLOC, 0); 
			Strcpy( pLog, pTmp);	
			break;
			
		case 2:
	        pTmp += (sizeof(PARAM_ERR)-sizeof(char));
			if ( (pErr = AllocPtr( Strlen(pTmp)+1)) == NULL)
				return Arret( ERR_ALLOC, 0); 
			Strcpy( pErr, pTmp);	
			break;
		}         
	}	
	return 1;
}



//////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************
*
*			LanceProcess											 *
*
*			lance du process de telediffusion
*
*		
*			parametre(s):   
*					nom du process et ses parametres					
*
*			retour:
*					0	echec
*					1	Ok
*
*******************************************************************/
LONG LanceProcess( LPSTR pNom)
{               

	PROCESS_INFORMATION pi;
	STARTUPINFO			si;
	LONG				lRet = 1;
	
	bProcessExec = FALSE;
	memset( &si, '\0', sizeof(STARTUPINFO));
	memset( &pi, '\0', sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	if ( !CreateProcess( NULL, pNom, NULL, NULL, TRUE, CREATE_SEPARATE_WOW_VDM, NULL, NULL, &si, &pi))
	{
		if ( pErr != NULL)
			FichierErr( GetLastError());
		return 0;
	}
	hProcess = pi.hProcess;

	if ( !ListAdd( pi.dwProcessId , GetCurrentProcessId(), pNom))
		lRet = 0;
	CloseHandle( pi.hThread);
	CloseHandle( pi.hProcess);
	if ( lRet == 1)
		bProcessExec = TRUE;
	return lRet;
}



//////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************
*
*			Fonction des messages
*
*
*******************************************************************/


LRESULT		wmPaint( HWND hwnd)
{

	PAINTSTRUCT ps;
	HDC  hDC;   
 	
 	hDC = BeginPaint( hwnd, &ps);
 	EndPaint( hwnd, &ps); 
 	return 0;  
}

#define ISWIN95(x) (x.dwMajorVersion == 4 && x.dwMinorVersion == 0 && x.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
#define ISWIN98(x) (x.dwMajorVersion == 4 && x.dwMinorVersion == 10 && x.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
#define ISWINME(x) (x.dwMajorVersion == 4 && x.dwMinorVersion == 90 && x.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
#define ISWINXP(x) (x.dwMajorVersion == 5 && x.dwMinorVersion == 1 && x.dwPlatformId == VER_PLATFORM_WIN32_NT)
#define ISWIN2000(x) (x.dwMajorVersion == 5 && x.dwMinorVersion == 0 && x.dwPlatformId == VER_PLATFORM_WIN32_NT)
#define ISWIN2003(x) (x.dwMajorVersion == 5 && x.dwMinorVersion == 2 && x.dwPlatformId == VER_PLATFORM_WIN32_NT)

LRESULT 	wmCreate( HWND hwnd)
{

OSVERSIONINFO osversion;
	
	 osversion.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	 GetVersionEx( &osversion);
	 /* avant adaptation pour XP
	 if (	(osversion.dwMajorVersion	!= 4 || 
			(osversion.dwMinorVersion	!= 0 &&
			osversion.dwMinorVersion	!= 10 &&
			osversion.dwMinorVersion	!= 90) ||
			osversion.dwPlatformId		!= VER_PLATFORM_WIN32_WINDOWS)
			(osversion.dwMajorVersion	!= 5 ||
			(osversion.dwMinorVersion	!= 1 )
			)
	 	return Arret( ERR_OS, 0);
    */

/* Remove OS check
	if ( !(ISWIN95(osversion) || ISWIN98(osversion) || ISWINME(osversion) || ISWINXP(osversion) || ISWIN2000(osversion) ))
	 	return Arret( ERR_OS, 0);
*/

	if ( !InitToolHelp())
		return Arret(ERR_FONC_TOOL, 0); 
    
	if ( !ListInit())
		return Arret(ERR_INITIALISATION, 0); 

	 SetExeLog(); 
	 if ( pExec == NULL)
	 	return Arret( ERR_PARAM_ABSENT_EXE, 0);

	 if ( pLog == NULL)
	 	return Arret( ERR_PARAM_ABSENT_LOG, 0);
  		            
	 if ( !FichierEfface( pLog))
	 	return Arret( ERR_EFFACE_LOG, 0);

   	 if ( LanceProcess( pExec) == 0)
   		return Arret( ERR_RUN_EXEC, 0);

	 SetTimer( hwnd, 1, 50,NULL);
	return 1;
}
     

LRESULT		wmFinApplic( HWND hwnd)
{
	
	if ( ListConsult() == 0)
	{
	AnalyseLog( pLog);
	if ( iRet == ERR_INIT)
		iRet = ERR_NO_COD;	
	DestroyWindow( hwnd);
	}
	return 0;   
}

LRESULT	    wmDestroy(void)
{
	PostQuitMessage( iRet);
 	return 1;     

}     

LRESULT wmTimer( HWND hwnd)
{

	long llc;
//Trace1();
	llc = ListConsult();
	
	if ( llc == 0)
//	if ( ListConsult() == 0)
	{
		Sleep(1000);
		if ( ListConsult() == 0)
		{
			KillTimer( hwnd, 1);
			PostMessage( hwnd, WM_FIN_APPLIC, 0, 0);
		}
	}

	return 1;
}

/*******************************************************************
*
*			DlgProc
*
*			fonction des mesages de la fenetre
*
*		
*			parametre(s):
*					voir doc Microsoft
*
*			retour:
*					voir doc Microsoft
*
*******************************************************************/
LRESULT CALLBACK DlgProc( HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{        

 switch( uiMsg)
 	{
	case WM_CREATE: 
		return wmCreate( hwnd);		
	           
 	case WM_PAINT:
 		return wmPaint( hwnd);

   	case WM_TIMER:
		return wmTimer( hwnd);

	case WM_FIN_APPLIC:
		return wmFinApplic( hwnd);

 	case WM_DESTROY:                  
		return wmDestroy();
		
 	default:     
	 	return DefWindowProc( hwnd, uiMsg, wParam, lParam);     
 	}
}


/*******************************************************************
*
*			FoncInit
*
*			fonction initialisation du programme
*
*		
*			parametre(s):
*					hInst		instance du programme
*					lpCmd		ligne de commande
*					pClass		nom de la classe
*					pCaption	titre de la fenetre
*
*			retour:
*					TRUE Ok, FALSE echec
*
*******************************************************************/
BOOL FoncInit(HINSTANCE hInst,LPSTR lpCmd, LPSTR pClass, LPSTR pCaption)
{

WNDCLASS 	wc;                          
LPSTR 		pCaptionLocal;
	
	if (GetLigneCommand( hInst, lpCmd) <= 0)
		return 0;        

	SetPriorityClass( GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	hinstCurrent = hInst;	
	wc.lpszMenuName = NULL;
	wc.lpszClassName = pClass;
    wc.hIcon = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
    wc.hCursor = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
    wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND); 
	wc.hInstance = hInst;            
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DlgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	RegisterClass( &wc);
	                                        
	if ( pCaption == NULL)
		pCaptionLocal = "";
	else
		pCaptionLocal = pCaption;	                                        
	hwndMain = CreateWindow( pClass, pCaptionLocal,
			WS_CAPTION | WS_SYSMENU, 0, 0, 100, 100, NULL, NULL, hInst, NULL);
	ShowWindow( hwndMain, SW_HIDE);
	UpdateWindow( hwndMain);	    
		    
	return IsWindow( hwndMain);		

}

/*******************************************************************
*
*			FoncBody
*
*			fonction de traitement du programme
*
*		
*			parametre(s):
*					aucun
*
*			retour:
*					rien
*
*******************************************************************/
void FoncBody(void)
{
	                            
   if ( IsWindow( hwndMain) )
   		{

		while ( GetMessage( &msg, NULL, 0, 0))
			{
			TranslateMessage( &msg);
			DispatchMessage( &msg);
			}      
		}
}
 

/*******************************************************************
*
*			WinMain
*
*			fonction principal
*
*		
*			parametre(s):
*					voir doc Microsoft
*
*			retour:
*					void doc Microsoft
*
*******************************************************************/
int WINAPI WinMain( HINSTANCE hinst, HINSTANCE hinstPrevious, LPSTR pCmdLine, int iCmdShow)
{
	
	if ( FoncInit(hinst, pCmdLine, "ADMISYSINSTPC", NULL) && iRet == ERR_INIT)
	{
		FoncBody();
	}
	ExitProcess( iRet);
return 0;
}

