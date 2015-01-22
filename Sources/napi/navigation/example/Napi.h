/*****************************************************************************
 * $Workfile: Napi.h $
 * $Revision: 1 $
 * $Modtime: 01/16/06 10:05a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2006 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NAPI_H
#define NAPI_H

// Define a type for function pointers
typedef void (*tFunction)(void);


///////////////////////////////////////////////////////////////////////////////
// Function:		napi_CreateLibrary
// Description:		This function initialises the navigation library
//
// Parameters:		None
//
// Returns:			1					Creation successful
//					0					Creation not successful
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_CreateLibrary();

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_DestroyLibrary
// Description:		This function destroys the navigation library
//
// Parameters:		None
//
// Returns:			1					Destruction successful
//					0					Destruction not successful
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_DestroyLibrary();

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_AddActionWord
// Description:		This function adds an action word to the navigation library
//
// Parameters:		pszName				Zero terminated name of the action word
//					pszFunctionName		Zero terminated name of the action word
//										function
//					pFunction			Pointer to action word function
//
// Returns:			1					Action word added
//					0					Action word not added
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_AddActionWord(const char* pszName, const char* pszFunctionName, tFunction pFunction);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_SetLibraryName
// Description:		This function sets the name of the navigation library
//
// Parameters:		pszName				Zero terminated name of the library
//
// Returns:			1					Library name set
//					0					Library name not set
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_SetLibraryName(const char* pszName);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_SetLibraryVersion
// Description:		This function sets the version of the navigation library
//
// Parameters:		pszVersion			Zero terminated version of the library
//
// Returns:			1					Library version set
//					0					Library version not set
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_SetLibraryVersion(const char* pszVersion);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_SetLibraryBuildNumber
// Description:		This function sets the build number of the navigation
//					library
//
// Parameters:		nBuildNumber		Build number of the library
//
// Returns:			1					Library build number set
//					0					Library build number not set
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_SetLibraryBuildNumber(int nBuildNumber);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_SetLibraryInfo
// Description:		This function sets the name of the navigation library
//
// Parameters:		pszInfo				Zero terminated info string
//
// Returns:			1					Library info set
//					0					Library info not set
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_SetLibraryInfo(const char* pszInfo);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_SetLibraryAuthor
// Description:		This function sets the author of the navigation library
//
// Parameters:		pszAuthor			Zero terminated author
//
// Returns:			1					Library author set
//					0					Library author not set
///////////////////////////////////////////////////////////////////////////////
extern "C" int napi_SetLibraryAuthor(const char* pszAuthor);


#endif  // !NAPI_H
