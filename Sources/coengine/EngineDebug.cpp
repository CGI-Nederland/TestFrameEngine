/*****************************************************************************
 * $Workfile: EngineDebug.cpp $
 * $Revision: 4 $
 * $Modtime: 4/20/00 4:58a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "EngineDebug.h"

#ifdef	UNIX

	// Unix
	#include <stdio.h>
#else

	// Windows
	#include <windows.h>
	// Visual C++
	#undef  INTERFACE
#endif

#include <string>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

//						=================
void					EngineDebugOutput
//						=================
(
	const string&		strMessage,
	const int			nLevel, 
	const void*			pCaller
)
{
	string strComposedMessage;

	// Compose message
	strComposedMessage += "[TFE6] ";

	switch (nLevel)
	{
		case CORE:
		{
			strComposedMessage += "[Core]";
			break;
		}
		case INTERFACE:
		{
			strComposedMessage += "[Interface]"; 
			break;
		}
		case THREAD:
		{
			strComposedMessage += "[Thread]";
			break;
		}
		case OTHER:
		{
			strComposedMessage += "[Other]";
			break;
		}
		case ASSERTION:
		{
			strComposedMessage += "[Assertion]";
			break;
		}
		default:
		{
			strComposedMessage += "[Invalid debug level]";
		}
	}
		
	strComposedMessage += " " + strMessage + "\n";

	// Write debug message

#ifdef	UNIX
	// Unix
	printf("%s", strComposedMessage.c_str());
#else
	OutputDebugString(strComposedMessage.c_str());
#endif
}

//						============
void					EngineAssert
//						============
(
	const char*			pszFileName,
	const int			nLineNumber
)
{
	string			strComposedMessage;
	ostringstream	ossLineNumber;
	
	ossLineNumber << nLineNumber ;

	// Compose message
	strComposedMessage += string(pszFileName);
	strComposedMessage += " : " + ossLineNumber.str() + " : Assertion failed";

	EngineDebugOutput(strComposedMessage, ASSERTION, 0);
}


///////////////////////////////////////////////////////////////////////////////
