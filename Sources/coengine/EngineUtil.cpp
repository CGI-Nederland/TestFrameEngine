/*****************************************************************************
 * $Workfile: EngineUtil.cpp $
 * $Revision: 3 $
 * $Modtime: 4/21/00 4:34p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "EngineUtil.h"

#ifdef	UNIX

	// Unix
	#include	<unistd.h>

#else

	// Windows
	#include <windows.h>

#endif

////////////////////////////////////////////////////////////////////////////////

//						===========
void					EngineSleep
//						===========
(
	const unsigned long	nMiliseconds
)
{
	// Take a nap

#ifdef	UNIX

	// Initialise time structure
	timeval	timeToSleep;

	if (nMiliseconds != 0)
	{
		timeToSleep.tv_sec = nMiliseconds / 1000;
		timeToSleep.tv_usec = (nMiliseconds % 1000) * 1000;
	}

	// Abuse select to sleep with milisecond resolution
	select(0, 0, 0, 0, (nMiliseconds ? &timeToSleep : 0));

#else

	// Windows
	Sleep(nMiliseconds);

#endif

}

///////////////////////////////////////////////////////////////////////////////
