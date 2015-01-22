/*****************************************************************************
 * $Workfile: Library.cpp $
 * $Revision: 3 $
 * $Modtime: 4/27/00 3:28p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <string>
using namespace std;

#include <string.h>
#include "NavigationLibrary.h"


// Global library
NavigationLibrary* g_pLibrary = 0;

// Global character buffers
char g_pszGetNAPIVersion[MAX_STRING_LENGTH+1];
char g_pszGetLibraryName[MAX_STRING_LENGTH+1];
char g_pszGetLibraryVersion[MAX_STRING_LENGTH+1];
char g_pszGetLibraryInfo[MAX_STRING_LENGTH+1];
char g_pszGetLibraryAuthor[MAX_STRING_LENGTH+1];

// Buffer functionality
void ClearBuffer(char* pszBuffer);

// NAPI version and build number
int g_nBuildNumber = 1;
char* g_pszVersion = "NAPI V1.0";


///////////////////////////////////////////////////////////////////////////////
// Lib functions

//						===================
extern "C" char*		napi_GetNAPIVersion()
//						===================
{
	// Clear the character buffer
	ClearBuffer(g_pszGetNAPIVersion);

	// Copy NAPI version string to global buffer
	if(g_pszVersion)
	{
		strcpy(g_pszGetNAPIVersion, g_pszVersion);
		return g_pszGetNAPIVersion;
	}
	else
	{
		return "";
	}

}

//						=======================
extern "C" int			napi_GetNAPIBuildNumber()
//						=======================
{
	// Return the build number
	return g_nBuildNumber;
}

//						==================
extern "C" int			napi_CreateLibrary()
//						==================
{
	int nResult = 0;

	// Only create a library is we do not have one already
	if (g_pLibrary == 0)
	{
		g_pLibrary = new NavigationLibrary();
		
		// Check if the creation was successful
		if (g_pLibrary != 0)
		{ nResult = 1; }
	}
	
	return nResult;
}

//						===================
extern "C" int			napi_DestroyLibrary()
//						===================
{
	int nResult = 0;
	
	// Only destroy the library if it has been created
	if (g_pLibrary != 0)
	{
		delete g_pLibrary;
		g_pLibrary = 0;
		
		nResult = 1;
	}
	
	return nResult;
}

//						===================
extern "C" int			napi_SetLibraryName
//						===================
(
	const char*			pszName
)
{
	int nResult = 0;

	// Only set the library name if the pointers are valid
	if ((g_pLibrary != 0) && (pszName != 0))
	{ nResult = g_pLibrary->SetName(string(pszName)); }
	
	return nResult;
}

//						===================
extern "C" char*		napi_GetLibraryName()
//						===================
{
	// Clear the character buffer
	ClearBuffer(g_pszGetLibraryName);

	// Only return the library name if there is a library
	if (g_pLibrary != 0)
	{ strcpy(g_pszGetLibraryName, g_pLibrary->GetName().c_str()); }
	
	return g_pszGetLibraryName;
}

//						======================
extern "C" int			napi_SetLibraryVersion
//						======================
(
	const char*			pszVersion
)
{
	int nResult = 0;

	// Only set the library name if the pointers are valid
	if ((g_pLibrary != 0) && (pszVersion != 0))
	{ nResult = g_pLibrary->SetVersion(string(pszVersion)); }
	

	return nResult;
}

//						======================
extern "C" char*		napi_GetLibraryVersion()
//						======================
{
	// Clear the character buffer
	ClearBuffer(g_pszGetLibraryVersion);

	// Only return the library name if there is a library
	if (g_pLibrary != 0)
	{ strcpy(g_pszGetLibraryVersion, g_pLibrary->GetVersion().c_str()); }
	
	return g_pszGetLibraryVersion;
}

//						==========================
extern "C" int			napi_SetLibraryBuildNumber
//						==========================
(
	int					nBuildNumber
)
{
	int nResult = 0;

	// Only set the build number if there is a library
	if (g_pLibrary != 0)
	{
		g_pLibrary->SetBuildNumber(nBuildNumber);
		nResult = 1;
	}

	return nResult;
}

//						==========================
extern "C" int			napi_GetLibraryBuildNumber()
//						==========================
{
	int nResult = 0;

	// Only return the build number if there is a library
	if (g_pLibrary != 0)
	{ nResult = g_pLibrary->GetBuildNumber(); }

	return nResult;
}

//						===================
extern "C" int			napi_SetLibraryInfo
//						===================
(
	const char* pszInfo
)
{
	int nResult = 0;

	// Only set the library info if the pointers are valid
	if ((g_pLibrary != 0) && (pszInfo != 0))
	{ nResult = g_pLibrary->SetInfo(string(pszInfo)); }
	
	return nResult;
}

//						===================
extern "C" char*		napi_GetLibraryInfo()
//						===================
{
	// Clear the character buffer
	ClearBuffer(g_pszGetLibraryInfo);

	// Only return the library info if there is a library
	if (g_pLibrary != 0)
	{ strcpy(g_pszGetLibraryInfo, g_pLibrary->GetInfo().c_str()); }
	
	return g_pszGetLibraryInfo;
}

//						=====================
extern "C" int			napi_SetLibraryAuthor
//						=====================
(
	const char*			pszAuthor
)
{
	int nResult = 0;

	// Only set the library info if the pointers are valid
	if ((g_pLibrary != 0) && (pszAuthor != 0))
	{ nResult = g_pLibrary->SetAuthor(string(pszAuthor)); }
	
	return nResult;
}

//						=====================
extern "C" char*		napi_GetLibraryAuthor()
//						=====================
{
	// Clear the character buffer
	ClearBuffer(g_pszGetLibraryAuthor);

	// Only return the library name if there is a library
	if (g_pLibrary != 0)
	{ strcpy(g_pszGetLibraryAuthor, g_pLibrary->GetAuthor().c_str()); }
	
	return g_pszGetLibraryAuthor;
}

//						==================
extern "C" int			napi_AddActionWord
//						==================
(
	const char*			pszName,
	const char*			pszFunctionName,
	tFunction			pFunction
)
{
	int nResult = 0;
	
	// Only add the action word if a library is available
	if (g_pLibrary != 0)
	{
		g_pLibrary->AddActionWord(string(pszName), string(pszFunctionName), pFunction);
		
		nResult = 1;
	}
	
	return nResult;
}

//						===========================
extern "C" int			napi_GetNumberOfActionWords()
//						===========================
{
	int nResult = 0;
	
	// Only calculate the number of action words if a library is available
	if (g_pLibrary != 0)
	{ nResult = g_pLibrary->GetNumberOfActionWords(); }
	
	return nResult;
}

//						========================
extern "C" int			napi_RegisterActionWords()
//						========================
{
	int nResult = 0;
	
	// Only register the action words if a library is available
	if (g_pLibrary != 0)
	{ nResult = g_pLibrary->RegisterActionWords(); }
	
	return nResult;
}

//						==========================
extern "C" int			napi_UnregisterActionWords()
//						==========================
{
	int nResult = 0;
	
	// Only unregister the action words if a library is available
	if (g_pLibrary != 0)
	{ nResult = g_pLibrary->UnregisterActionWords(); }
	
	return nResult;
}

//						======================
extern "C" int			napi_ExecuteActionWord
//						======================
(
	const char*			pszActionWord
)
{
	int nResult = 0;
	
	// Only execute an action word if a library is available
	if (g_pLibrary != 0)
	{ nResult = g_pLibrary->ExecuteActionWord(string(pszActionWord)); }
	
	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
// Buffer functionality

//						===========
void					ClearBuffer
//						===========
(
	char*				pszBuffer
)
{
	// Fill the buffer with zeros
	if(pszBuffer)
	{
		memset(pszBuffer, 0, MAX_STRING_LENGTH);
	}
}

///////////////////////////////////////////////////////////////////////////////
