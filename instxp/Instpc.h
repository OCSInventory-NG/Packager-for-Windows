/*******************************************************************
*
*			INST32.H
*			
*			declaration pour INSTPC.C			
*
*			Creation : 1.0.0	1998/08/26		BLR
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
*
*			Mofif	 : 2.0.0	1999/04/27		BLR
*												Version 32 bits  Windows 95 uniquement
*
*
*******************************************************************/
#include "comwin.h"

#define MAX_ARG			64									/* nomnre maximum d'arguments */
#define MAX_LIGNE       512									/* taille maximum d'une ligne dans le fichier log */


#define MAX_TIMER		2									/* nombre maximum de timer lances */
#define ID_TIMER_RUN    0
#define ID_TIMER_ARRET  1

#define	PARAM_EXEC			"/exe:"              			/* argument contenant le nom du programme a lancer */
#define	PARAM_EXEC_INDEX	0                           	/* index pour l'argument exe */
#define	PARAM_LOG			"/log:"                     	/* argument contenant le nom du fichier log */
#define	PARAM_LOG_INDEX		1                           	/* index pour l'argument log */ 
#define PARAM_EXEC_LIMIT	'"'                         	/* caractere de limit dans l'argument exe */
#define	PARAM_ERR			"/err:"                     	/* argument contenant le nom du fichier err */
#define	PARAM_ERROR_INDEX		2	                          	/* index pour l'argument err */ 
#define	PARAM_ERR_INDEX		-1  							/* argument inconnu */
                                
#define DEBUT_CODE_ERR		"***"							/* signal une ligne contenant un code d'erreur */                                

    
#define ERR_MAX_ERREUR			255                         /* numero de code erreur maximum autorise */
#define ERR_MIN_INSTALL			1							/* numero de code erreur minimum pour installation */
#define ERR_MAX_INSTALL			100							/* numero de code erreur maximum pour installation */
#define ERR_MIN_BULL			101							/* numero de code erreur minimum pour BULL */
#define ERR_MAX_BULL			120							/* numero de code erreur maximum pour BULL */
#define ERR_MIN_PRG				121							/* numero de code erreur minimum pour le programme */
#define ERR_MAX_PRG				ERR_MAX_ERREUR				/* numero de code erreur maximum pour le programme */

               
/* description des erreurs gerees par le programme */        
#define ERR_INIT				-1							/* valeur initialisation de iRet */
#define ERR_PARAM_ABSENT_EXE	ERR_MIN_PRG            		/* argument /exe absent */
#define ERR_PARAM_ABSENT_LOG	ERR_MIN_PRG+1              	/* argument /log absent */
#define ERR_FONC_NOTIFY			ERR_MIN_PRG+2              	/* impossible d'avoir l'adresse de la fonction de notification */
#define ERR_RUN_EXEC			ERR_MIN_PRG+3				/* lancement impossible de l'executable */
#define ERR_REC_NOTIFY			ERR_MIN_PRG+4				/* echec de la fonction NotifyRegister */
#define ERR_EFFACE_LOG			ERR_MIN_PRG+5              	/* effacement du fichier log impossible */
#define ERR_OUVERT_LOG			ERR_MIN_PRG+6				/* impossible d'ouvrir le fichier log en lecture */
#define ERR_PARAM_INCONNU		ERR_MIN_PRG+7				/* argument inconnu */
#define ERR_ALLOC				ERR_MIN_PRG+8				/* allocation de memoire impossible */
#define ERR_NO_COD				ERR_MIN_PRG+9				/* pas de code retour dans le fichier log */
#define ERR_LONG_LIGNE			ERR_MIN_PRG+10				/* ligne trop longue dans le fichier log */
#define ERR_LIGNE_SS_CODE		ERR_MIN_PRG+11				/* ligne d'erreur sans code */  
#define ERR_LIGNE_FORMAT		ERR_MIN_PRG+12				/* mauvais format de la ligne */  
#define ERR_NUM_BULL			ERR_MIN_PRG+13				/* numero de code d'erreur reserve a BULL */
#define ERR_NUM_PRG				ERR_MIN_PRG+14				/* numero de code d'erreur reserve au programme */
#define ERR_NUM_MAX				ERR_MIN_PRG+15				/* depassement numero de code d'erreur autorise */
#define ERR_SHIELD				ERR_MIN_PRG+16				/* code d'erreur negatif installShield ??? */


#define STATUS_ERR(x)		iErr = (x)                          
#define ERR_OK			0                         
#define ERR_NOPARAM		1                    

static	int 				iArgc;							/* nombre d'arguments sur la ligne de commande */
static	LPSTR * 			pArgv;                          /* table des arguments */
static 	char				*pLog; 							/* parametre log */      
static 	char				*pExec;                         /* parametre exe */
static 	char				*pErr;                         /* parametre err */
static 	MSG					msg;                            /* message */
static 	HWND				hwndMain;                       /* fenetre principale */
static 	FARPROC				pProc;                          /* fonction de la fenetre principale */
static	int					iErr = 0;						/* gestion des codes d'erreur */
static 	int					iRet = ERR_INIT;				/* code retour */
static	int					iFirstPaint = 0;                /* premier WM_PAINT */
static	HINSTANCE			hinstCurrent;					/* instance du programme */ 
static	UINT				uiRetWinExec;					/* valeur de retour de WinExec */
static  HINSTANCE			hinstWinExec;					/* instance du programme lance */
static  char				byNomModule[_MAX_PATH+1];       /* nom du module en cours */
static	char				byLigne[MAX_LIGNE+1];			/* ligne du fichier log */ 
static  HFILE				hFile = HFILE_ERROR;			/* handle sur le fichier log */
static  BOOL				bProcessExec = FALSE;			/* indique si le process est en cours */
#define MAX_TACHE 20


static  int			        iNbTask;
static  BOOL				bTabTimer[MAX_TIMER];			/* TRUE timer lance */
                                           
#define WM_FIRSTMSG  	WM_USER+1
#define WM_SECONDMSG  	WM_USER+2

