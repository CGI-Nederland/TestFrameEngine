/*****************************************************************************
 * $Workfile: EngineInterface.h $
 * $Revision: 4 $
 * $Modtime: 4/19/00 1:17a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGINEINTERFACE_H
#define ENGINEINTERFACE_H


// Forward declaration
class TcpIpConnection;

////////////////////////////////////////////////////////////////////////////////
// class EngineInterface

class EngineInterface
{
// Construction and destruction
public:
	explicit EngineInterface(TcpIpConnection* pClient);		// Constructor
	~EngineInterface();								// Destructor

private:
	EngineInterface(const EngineInterface& right);	// Copy contructor


// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessagecenter
	//
	// Description:	Shows the engine message center
	//					
	// Parameters:	none
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int ShowMessagecenter(bool bDetail,	const string& strLanguage, bool bOnTop, bool bPause);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowProgress
	//
	// Description:	Updates the progress bar
	//					
	// Parameters:	nExecuted			Number of executed action words
	//				nTotal				Total number of action words
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int ShowProgress(int nExecuted,int nTotal);
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowCluster
	// Description: This function shows the name of the current cluster in the 
	//				Message Center dialogue
	//
	// Parameters:	pszCluster			Pointer to a zero terminated char string
	//									containing the name of the cluster
	//
	// Returns:		true				successful
	//				false				otherwise
	///////////////////////////////////////////////////////////////////////////////
	int ShowCluster(const char*	pszCluster);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowActionword
	// Description: This function shows the name of the current action word in the 
	//				Message Center dialogue
	//
	// Parameters:	pszActionWord		Pointer to a zero terminated char string 
	//									containing the name of the action word
	//
	// Returns:		true				successful
	//				false				otherwise
	///////////////////////////////////////////////////////////////////////////////
	int	ShowActionword(const char* pszActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowError
	// Description: This function shows the last error and the number of errors
	//
	// Parameters:	pszError			Pointer to a zero terminated char string 
	//									containing the error
	//				nErrors				Number of errors
	//
	// Returns:		true				successful
	//				false				otherwise
	///////////////////////////////////////////////////////////////////////////////
	int	ShowError(const char* pszError,	int	nErrors);
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowChecks
	// Description: This function sets the number of passed and failed checks in
	//				the Message Center dialogue
	//
	// Parameters:	nPassed				Number of passed checks
	//				nFailed				Number of failed checks
	//
	// Returns:		true				successful
	//				false				otherwise
	///////////////////////////////////////////////////////////////////////////////
	int	ShowChecks(int nPassed,	int nFailed);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessage
	// Description: This function pops up a message box to show a message
	//
	// Parameters:	pszMessage			Pointer to a zero terminated char string 
	//									containing the message
	//
	// Returns:		true				successful
	//				false				otherwise
	///////////////////////////////////////////////////////////////////////////////
	int	ShowMessage(const char*	pszMessage);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	EnginePaused
	// Description: Engine has paused, so notify GUI
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void EnginePaused();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	EngineResumed
	// Description: Engine has resumed, so notify GUI
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void EngineResumed();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Stop
	// Description: This function sends a stop message to the engine
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void Stop();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Pause
	// Description: This function sends a pause message to the engine
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void Pause();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Resume
	// Description: This function sends a resume message to the engine
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void Resume();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Register
	// Description: This function sends a register message to the engine
	//
	// Parameters:	none
	//
	// Returns:		nothing
	///////////////////////////////////////////////////////////////////////////////
	void Register();

// Member variables
private:
	TcpIpConnection* m_pClient;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !ENGINEINTERFACE_H