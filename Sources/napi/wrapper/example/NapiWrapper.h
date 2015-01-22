/*****************************************************************************
 * $Workfile: NapiWrapper.h $
 * $Revision: 1 $
 * $Modtime: 01/16/06 12:17p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2006 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NAPIWRAPPER_H
#define NAPIWRAPPER_H

///////////////////////////////////////////////////////////////////////////////
// NAPI FUNCTIONS

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_LoadLibrary
// Description:		This function loads a NAPI library and registers all
//					its associated action words
//
// Parameters:		pszLibraryName		Zero terminated library name
//
// Returns:			1					NAPI library loaded
//					0					NAPI library not loaded
///////////////////////////////////////////////////////////////////////////////
extern "C" int _stdcall napi_LoadLibrary(const char* pszLibraryName);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_FreeLibrary
// Description:		This function frees a NAPI library after unregistering all
//					its associated action words
//
// Parameters:		pszLibraryName		Zero terminated library name
//
// Returns:			1					NAPI library freed
//					0					NAPI library not freed
///////////////////////////////////////////////////////////////////////////////
extern "C" int _stdcall napi_FreeLibrary(const char* pszLibraryName);

///////////////////////////////////////////////////////////////////////////////
// Function:		napi_ExecuteActionWord
// Description:		This function dispatches the execution of an action word
//					to the loaded NAPI libraries
//
// Parameters:		pszActionWord		Zero terminated name of the action word
//
// Returns:			1					Action word executed
//					0					Action word not executed
///////////////////////////////////////////////////////////////////////////////
extern "C" int _stdcall napi_ExecuteActionWord(const char* pszActionWord);


///////////////////////////////////////////////////////////////////////////////

#endif // !NAPIWRAPPER_H
