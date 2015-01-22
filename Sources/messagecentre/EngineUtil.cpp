/*****************************************************************************
 * $Workfile: EngineUtil.cpp $
 * $Revision: 4 $
 * $Modtime: 22-05-01 21:51 $
 * $Author: Ehu $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "EngineUtil.h"

/*#ifdef	UNIX

	// Unix
	#include	<unistd.h>
	#include	<sys/time.h>

#else
*/
	// Windows
	#include <windows.h>

//#endif

////////////////////////////////////////////////////////////////////////////////

//						===========
void					EngineSleep
//						===========
(
	const DWORD	nMiliseconds
)
{
	if(nMiliseconds != NULL)
	{
		Sleep(nMiliseconds);
	}
}

///////////////////////////////////////////////////////////////////////////////
