/*****************************************************************************
 * $Workfile: NapiWrapper.cpp $
 * $Revision: 1 $
 * $Modtime: 10/16/00 12:23p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <string>
#include <vector>

using namespace std;

#include "NapiWrapper.h"		// Exported function prototypes

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// Internal function prototypes

char*	napi_GetNAPIVersion(HMODULE hModule);

int		napi_GetNAPIBuildNumber(HMODULE hModule);

int		napi_GetNumberOfActionWords(HMODULE hModule);

int		napi_ExecuteActionWord(HMODULE hModule, const char* pszActionWord);

char*	napi_GetLibraryName(HMODULE hModule);

char*	napi_GetLibraryVersion(HMODULE hModule);

int		napi_GetLibraryBuildNumber(HMODULE hModule);

char*	napi_GetLibraryInfo(HMODULE hModule);

char*	napi_GetLibraryAuthor(HMODULE hModule);

int		napi_RegisterActionWords(HMODULE hModule);

int		napi_UnregisterActionWords(HMODULE hModule);

struct Library
{
	HMODULE hModule;
	string strName;
};

///////////////////////////////////////////////////////////////////////////////
// Globals

vector<Library> g_vLibraries;

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
			
			break;
		}
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Exported functions

//						================
extern "C" int _stdcall napi_LoadLibrary
//						================
(
	const char*			pszLibraryName
)
{
	int nResult = 0;

	// Load the dll
	HMODULE hModule = LoadLibrary(pszLibraryName);
	
	// See if the library was loaded successfully
	if (hModule != 0)
	{
		// Create a new library structure to store library information
		Library library;

		// Store the windows handle
		library.hModule = hModule;

		// Register the action words
		napi_RegisterActionWords(hModule);

		// Store the name used to load the library
		library.strName = string(pszLibraryName);

		// Store the library in our list of libraries
		g_vLibraries.push_back(library);

		// Successfull
		nResult = 1;
	}

	return nResult;
}

//						================
extern "C" int _stdcall napi_FreeLibrary
//						================
(
	const char*			pszLibraryName
)
{
	int nResult = 0;

	if(pszLibraryName)
	{
		string strName = string(pszLibraryName);

		vector<Library>::iterator Iterator = g_vLibraries.begin();

		// Free all libraries
		while (Iterator != g_vLibraries.end())
		{
			if (Iterator->strName == strName)
			{
				// Unregister the action words
				napi_UnregisterActionWords(Iterator->hModule);

				// Free the library
				if (FreeLibrary(Iterator->hModule))
				{
					// Library freed, so remove it from the vector
					g_vLibraries.erase(Iterator);

					// Successfull, so stop iterating
					nResult = 1;
					break;
				}
			}

			// Next library
			Iterator++;
		}
	}

	return nResult;
}

//						======================
extern "C" int _stdcall napi_ExecuteActionWord
//						======================
(
	const char*			pszActionWord
)
{
	int nResult = 0;

	vector<Library>::iterator Iterator = g_vLibraries.begin();

	// See if one of the libraries in our list knows how to execute
	// this action word
	while (Iterator != g_vLibraries.end())
	{
		if (napi_ExecuteActionWord(Iterator->hModule, pszActionWord) == 1)
		{
			// Action word was executed successfully, so stop
			nResult = 1;
			break;
		}

		// Next library
		Iterator++;
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
// Internal functions

//						===================
char*					napi_GetNAPIVersion
//						===================
(
	HMODULE				hModule
)
{
	typedef char* (*NAPI_STRING) (void);
	char* pResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_STRING pProc = (NAPI_STRING) GetProcAddress(hModule, "napi_GetNAPIVersion");
		
		// Execute the function in the library
		if (pProc != 0)
		{ pResult = pProc(); }
	}

	return pResult;
}

//						=======================
int						napi_GetNAPIBuildNumber
//						=======================
(
	HMODULE				hModule
)
{
	typedef int (*NAPI_INTEGER) (void);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INTEGER pProc = (NAPI_INTEGER) GetProcAddress(hModule, "napi_GetNAPIBuildNumber");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(); }
	}

	return nResult;
}

//						===========================
int						napi_GetNumberOfActionWords
//						===========================
(
	HMODULE				hModule
)
{
	typedef int (*NAPI_INTEGER) (void);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INTEGER pProc = (NAPI_INTEGER) GetProcAddress(hModule, "napi_GetNumberOfActionWords");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(); }
	}

	return nResult;
}
	
//						======================
int						napi_ExecuteActionWord
//						======================
(
	HMODULE				hModule,
	const char*			pszActionWord
)
{
	typedef int (*NAPI_INTEGER) (const char*);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INTEGER pProc = (NAPI_INTEGER) GetProcAddress(hModule, "napi_ExecuteActionWord");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(pszActionWord); }
	}

	return nResult;
}

//						===================
char*					napi_GetLibraryName
//						===================
(
	HMODULE				hModule
)
{
	typedef char* (*NAPI_STRING) (void);
	char* pResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_STRING pProc = (NAPI_STRING) GetProcAddress(hModule, "napi_GetLibraryName");
		
		// Execute the function in the library
		if (pProc != 0)
		{ pResult = pProc(); }
	}

	return pResult;
}

//						======================
char*					napi_GetLibraryVersion
//						======================
(
	HMODULE				hModule
)
{
	typedef char* (*NAPI_STRING) (void);
	char* pResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_STRING pProc = (NAPI_STRING) GetProcAddress(hModule, "napi_GetLibraryVersion");
		
		// Execute the function in the library
		if (pProc != 0)
		{ pResult = pProc(); }
	}

	return pResult;
}

//						==========================
int						napi_GetLibraryBuildNumber
//						==========================
(
	HMODULE				hModule
)
{
	typedef int (*NAPI_INTEGER) (void);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INTEGER pProc = (NAPI_INTEGER) GetProcAddress(hModule, "napi_GetLibraryBuildNumber");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(); }
	}

	return nResult;
}

//						===================
char*					napi_GetLibraryInfo
//						===================
(
	HMODULE				hModule
)
{
	typedef char* (*NAPI_STRING) (void);
	char* pResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_STRING pProc = (NAPI_STRING) GetProcAddress(hModule, "napi_GetLibraryInfo");
		
		// Execute the function in the library
		if (pProc != 0)
		{ pResult = pProc(); }
	}

	return pResult;
}

//						=====================
char*					napi_GetLibraryAuthor
//						=====================
(
	HMODULE				hModule
)
{
	typedef char* (*NAPI_STRING) (void);
	char* pResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_STRING pProc = (NAPI_STRING) GetProcAddress(hModule, "napi_GetLibraryAuthor");
		
		// Execute the function in the library
		if (pProc != 0)
		{ pResult = pProc(); }
	}

	return pResult;
}

//						========================
int						napi_RegisterActionWords
//						========================
(
	HMODULE				hModule
)
{
	typedef int (*NAPI_INT) (void);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INT pProc = (NAPI_INT) GetProcAddress(hModule, "napi_RegisterActionWords");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(); }
	}

	return nResult;
}

//						==========================
int						napi_UnregisterActionWords
//						==========================
(
	HMODULE				hModule
)
{
	typedef int (*NAPI_INT) (void);
	int nResult = 0;

	// Only proceed when the DLL was loaded successfully
	if (hModule != 0)
	{
		// Find the exported function call in the library
		NAPI_INT pProc = (NAPI_INT) GetProcAddress(hModule, "napi_UnregisterActionWords");
		
		// Execute the function in the library
		if (pProc != 0)
		{ nResult = pProc(); }
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
