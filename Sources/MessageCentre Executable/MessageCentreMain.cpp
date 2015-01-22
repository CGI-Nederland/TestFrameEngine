/*****************************************************************************
 * $Workfile: MessageCentreMain.cpp $
 * $Revision: 1 $
 * $Modtime: 3-05-01 13:33 $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <windows.h>

#include "MessageCentreApi.h"		// MessageCentre interface

//				=======
int APIENTRY	WinMain
//				=======
( 
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow
)
{
	// Start engine message centre
 	emc_Start(lpCmdLine);

	return 0;
}