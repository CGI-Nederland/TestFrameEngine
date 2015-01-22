/*****************************************************************************
 *$Workfile: EngGuiApi.h $
 *$Revision: 5 $
 *$Modtime: 21-12-99 13:58 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_messagecenter
	// Description: This function shows the Engine Message Center dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_messagecenter();

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_progress
	// Description: This function sets the progress in the Message Center dialogue
	//
	// Parameters:	nExecuted	Number of executed action words
	//				nTotal		Total number of action words to be executed
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_progress(int nExecuted, int nTotal);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_cluster
	// Description: This function shows the name of the current cluster in the 
	//				Message Center dialogue
	//
	// Parameters:	pszCluster	Pointer to a zero terminated char string containing
	//							the name of the cluster
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_cluster(const char* pszCluster);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_actionword
	// Description: This function shows the name of the current action word in the 
	//				Message Center dialogue
	//
	// Parameters:	pszActionWord	Pointer to a zero terminated char string 
	//								containing the name of the action word
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_actionword(const char* pszActionWord);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_checks
	// Description: This function sets the number of passed and failed checks in
	//				the Message Center dialogue
	//
	// Parameters:	nPassed		Number of passed checks
	//				nFailed		Number of failed checks
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_checks(int nPassed, int nFailed);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_message
	// Description: This function pops up a message box to show a message
	//
	// Parameters:	pszMessage	Pointer to a zero terminated char string 
	//							containing the message
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_message(const char* pszMessage);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	show_error
	// Description: This function shows the last error and the number of errors
	//
	// Parameters:	pszError	Pointer to a zero terminated char string 
	//							containing the error
	//				nErrors		Number of errors
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int show_error(const char* pszError, int nErrors);
	
	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	engine_paused
	// Description: Engine has paused, pause the GUI
	//
	// Parameters:	none
	//
	// Returns:		<void>
	/////////////////////////////////////////////////////////////////////////////*/
	void engine_paused();

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	engine_resumed
	// Description: Engine has resumed, resume the GUI
	//
	// Parameters:	none
	//
	// Returns:		<void>
	/////////////////////////////////////////////////////////////////////////////*/
	void engine_resumed();

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	register_stop
	// Description: Registers the callback pointer to the engine stop function.
	//
	// Parameters:	pStop		Pointer to the stop function in the calling
	//							program or dll
	//
	// Returns:		<void>
	/////////////////////////////////////////////////////////////////////////////*/
	void register_stop(void (*pStop)(void));

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	register_pause
	// Description: Registers the callback pointer to the engine pause function.
	//
	// Parameters:	pPause		Pointer to the pause function in the calling
	//							program or dll
	//
	// Returns:		<void>
	/////////////////////////////////////////////////////////////////////////////*/
	void register_pause(void (*pPause)(void));

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	register_resume
	// Description: Registers the callback pointer to the engine resume function.
	//
	// Parameters:	pResume		Pointer to the resume function in the calling
	//							program or dll
	//
	// Returns:		<void>
	/////////////////////////////////////////////////////////////////////////////*/
	void register_resume(void (*pResume)(void));

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	enggui_init
	// Description: Initialises the GUI dll
	//
	// Parameters:	nDetail		Start in detailed state? TRUE/FALSE
	//				pszLang		Language
	//				nOnTop		Start always on top? TRUE/FALSE
	//				nPause		Start in paused state? TRUE/FALSE
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int enggui_init(int nDetail, const char* pszLang, int nOnTop, int nPause);

	/*/////////////////////////////////////////////////////////////////////////////
	// Function:	enggui_exit
	// Description: Exits the GUI dll
	//
	// Parameters:	<none>
	//
	// Returns:		TRUE		When successful
	//				FALSE		When not successful
	/////////////////////////////////////////////////////////////////////////////*/
	int enggui_exit();

#ifdef __cplusplus
}
#endif
