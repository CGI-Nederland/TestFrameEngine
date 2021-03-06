/*****************************************************************************
 *$Workfile: MessageCentre.h $
 *$Revision: 5 $
 *$Modtime: 21-12-99 14:20 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MESSAGECENTRE_H
#define MESSAGECENTRE_H

#include <string>

using namespace std;

#include "Dialog.h"

// Forward declarations
class CMessageCentre;

#undef BASECLASS
#define BASECLASS Dialog

////////////////////////////////////////////////////////////////////////////////
// class MessageCentre

class MessageCentre : public BASECLASS
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Destructor of MessageCentre
	///////////////////////////////////////////////////////////////////////////
	virtual	~MessageCentre()
	{};


// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetProgress (Abstract)
	// Description: This function sets the progress indicator to represent the 
	//				percentage of completed action words.
	//
	// Parameters:	nExecuted		Number of completed action words
	//				nTotal			Total number of action words to complete
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetProgress(int nExecuted, int nTotal) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetChecks (Abstract)
	// Description: This function sets the number of passed and failed checks
	//
	// Parameters:	nPassed		Number of passed checks
	//				nFailed		Number of failed checks
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void SetChecks(int nPassed, int nFailed) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetError (Abstract)
	// Description: This function sets the last error and number of errors
	//
	// Parameters:	strError		Last error message
	//				nErrors			Number of errors
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetError(const string& strError, int nErrors) = 0;
    
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentCluster (Abstract)
	// Description: This function sets the name of the current cluster
	//
	// Parameters:	strCluster		Name of the current cluster
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetCurrentCluster(const string& strCluster) = 0;
    
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentActionWord (Abstract)
	// Description: This function sets the current action word
	//
	// Parameters:	strActionWord	Current action word
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetCurrentActionWord(const string& strActionWord) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessage (Abstract)
	// Description: This function pops up a message box to show a message
	//
	// Parameters:	strMessage		Message string
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void ShowMessage(const string& strMessage) = 0;

	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	DoModeless (Abstract)
	// Description: This function starts a separate thread to show the dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void DoModeless() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Exit (Abstract)
	// Description: Exit the dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Exit() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnStop (Abstract)
	// Description: This function is called by the MFC dialogue when the user
	//				presses the stop button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnStop() = 0;
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnPause (Abstract)
	// Description: This function is called by the MFC dialogue when the user
	//				presses the pause button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnPause() = 0;
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Pause (Abstract)
	// Description: This function is called by the Engine when it has paused
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Pause() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Resume (Abstract)
	// Description: This function is called by the Engine when it has resumed again
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Resume() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnDetail (Abstract)
	// Description: This function is called by the MFC dialogue when the user
	//				presses the More Detail or Less Detail button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnDetail() = 0;
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterStop (Abstract)
	// Description: Registers the callback pointer for the stop function.
	//
	// Parameters:	pStop			Callback pointer
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterStop(void (*pStop)(void)) = 0;
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterPause (Abstract)
	// Description: Registers the callback pointer for the pause function.
	//
	// Parameters:	pPause			Callback pointer
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterPause(void (*pPause)(void)) = 0;

	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterResume (Abstract)
	// Description: Registers the callback pointer for the resume function.
	//
	// Parameters:	pResume			Callback pointer
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterResume(void (*pResume)(void)) = 0;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !MESSAGECENTRE_H
