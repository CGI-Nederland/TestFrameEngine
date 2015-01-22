/*****************************************************************************
 *$Workfile: MessageCentreApi.h $
 *$Revision: 1 $
 *$Modtime: 3-05-01 9:56 $ 24-11-2000 (QT version)
 *$Author: Etb $ DSedney reused for QT version
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MESSAGECENTREAPI_H
#define MESSAGECENTREAPI_H

/////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */
	
	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	emc_Start
	// Description: starts the engine message centre, and blocks until connection
	//				is terminated or GUI is closed.
	//
	// Parameters:	pszCmdLine	parameters
	//
	// Returns:		TRUE		When finished
	/////////////////////////////////////////////////////////////////////////////*/
	int emc_Start( const char *lpCmdLine );

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	emc_Stop
	// Description: signals the GUI to terminate.
	//
	// Parameters:	-
	//
	// Returns:		TRUE		When finished
	/////////////////////////////////////////////////////////////////////////////*/
	int emc_Stop();

#ifdef __cplusplus
}
#endif

#endif MESSAGECENTREAPI_H

