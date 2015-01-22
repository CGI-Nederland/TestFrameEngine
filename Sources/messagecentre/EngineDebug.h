/*****************************************************************************
 * $Workfile: EngineDebug.h $
 * $Revision: 3 $
 * $Modtime: 4/21/00 2:06a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGINEDEBUG_H
#define ENGINEDEBUG_H

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		: EngineDebugOutput
//
// description	: Writes a debug message to the engine debug output source.
//				  
// parameters	: string	The debug message
//				  int		Debug level, CORE, INTRFACE, THREAD or OTHER
//				  caller	Pointer to calling object (this) or NULL (NYI)
//
// returns		: <void>
//
///////////////////////////////////////////////////////////////////////////////
void EngineDebugOutput(const string& strMessage, const int nLevel, const void* pCaller);

///////////////////////////////////////////////////////////////////////////////
// function		: EngineAssert
//
// description	: Asserts if the expression evaluates to true. If not a message
//				  is written to the debug output source.
//				  
// parameters	: char*		pszFilename
//				  int		nLineNumber
//
// returns		: <void>
//
///////////////////////////////////////////////////////////////////////////////
void EngineAssert(const char* pszFilename, int nLineNumber);

///////////////////////////////////////////////////////////////////////////////
// macro		: ENGINEASSERT
//
// description	: Macro which asserts if the expression evaluates to true. If not 
//				  a message is written to the debug output source.
//		  
// parameters	: bool		Expression
//
// returns		: None
//
///////////////////////////////////////////////////////////////////////////////
#define ENGINEASSERT(bExpression) if (!bExpression) EngineAssert(__FILE__, __LINE__)


// Level definition
enum DEBUGLEVEL { CORE, INTRFACE, THREAD, ASSERTION, OTHER };

////////////////////////////////////////////////////////////////////////////////

#endif	// !ENGINEDEBUG_H
