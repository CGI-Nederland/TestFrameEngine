/*****************************************************************************
 * $Workfile: Example.cpp $
 * $Revision: 3 $
 * $Modtime: 01-16-06 12:56 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2007 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>			// Windows API

#include "Coengine.h"			// Engine exports
#include "Napi.h"				// Include the NAPI DLL interface
///////////////////////////////////////////////////////////////////////////////
//
//		HOW TO ADD AN ACTION WORD TO THIS EXAMLPE NAVIGATION LIBRARY
//
//
// Step 1:	Add the action word function prototype to the list of prototypes.
//			An action word function should always return void and should not
//			have any parameters.
//	
// Step 2:	Add the action word to the action word list by calling the NAPI
//			function napi_AddActionWord in InitialiseNAPI.
//
// Step 3:	Write the implementation of the action word function.
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Example action word function prototypes. Replace them with your own action
// word function prototypes.

void PrintSomeNumbers();
void PerformACheck();
void PrintAnError();
void GetTestCondition();

///////////////////////////////////////////////////////////////////////////////
// NAPI Functions

//						==============
void					InitialiseNAPI()
//						==============
{
	///////////////////////////////////////////////////////////////////////////
	// Create a navigation library.
	
	napi_CreateLibrary();

	///////////////////////////////////////////////////////////////////////////
	// Now we set the information (name, author etc.) for this navigation 
	// library. Of course you can replace the information with your own.

	napi_SetLibraryName("TestFrame Example DLL");
	napi_SetLibraryVersion("Version 1.0");
	napi_SetLibraryBuildNumber(1);
	napi_SetLibraryAuthor("Engine Team");
	napi_SetLibraryInfo("For more information: engine5@CGI.nl");

	///////////////////////////////////////////////////////////////////////////
	// Export the example action words by calling napi_AddActionWord. Replace
	// these examples with your own action words.

	napi_AddActionWord("print some numbers",	"PrintSomeNumbers", &PrintSomeNumbers);
	napi_AddActionWord("perform a check",		"PerformACheck",	&PerformACheck);
	napi_AddActionWord("print an error",		"PrintAnError",		&PrintAnError);
	napi_AddActionWord("tfe_GetTestCondition",  "GetTestCondition",  &GetTestCondition);
}

//						===========
void					CleanUpNAPI()
//						===========
{
	// Destroy the NAPI library
	napi_DestroyLibrary();
}

///////////////////////////////////////////////////////////////////////////////
// Example action word functions. Replace them with your own action words.

//						================
void					PrintSomeNumbers()
//						================
{
	// Report parameters 1, 2, and 3
	tfe_ReportComment(tfe_GetParameter(1));
	tfe_ReportComment(tfe_GetParameter(2));
	tfe_ReportComment(tfe_GetParameter(3));
}


//						=============
void					PerformACheck()
//						=============
{
	// Compare parameter 1 and 2
	tfe_CheckParameter(1, tfe_GetParameter(2));
}


//						============
void					PrintAnError()
//						============
{
	tfe_ReportError(tfe_GetParameter(1), TFE_ERROR);
}

void GetTestCondition()
{
	tfe_ReportComment(tfe_GetTestCondition());
}

///////////////////////////////////////////////////////////////////////////////
// Main function for the DLL

//						=======
BOOL APIENTRY			DllMain
//						=======
(
	HANDLE				hModule,
	DWORD				ul_reason_for_call, 
	LPVOID				lpReserved
)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			///////////////////////////////////////
			// A new proces is attached to this DLL
			
			InitialiseNAPI();
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			///////////////////////////////////////
			// A new thread is atached to this DLL

			break;
		}
		case DLL_THREAD_DETACH:
		{
			///////////////////////////////////////
			// A thread is detached from this DLL
			
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			///////////////////////////////////////
			// A process is detached from this DLL
			
			CleanUpNAPI();
			break;
		}
    }
    return TRUE;
}
///////////////////////////////////////////////////////////////////////////////
