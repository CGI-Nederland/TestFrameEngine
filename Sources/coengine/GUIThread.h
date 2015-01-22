/*****************************************************************************
 * $Workfile: GUIThread.h $
 * $Revision: 2 $
 * $Modtime: 5/04/01 1:49p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef GUITHREAD_H
#define GUITHREAD_H

#include <string>					// STL strings

using namespace std;

#include "Thread.h"					// Thread class definition
#include <windows.h>				// Needed for DLL functions

// Function pointer type definition
typedef int (*INT_PCHAR) (char *);
typedef int (*INT_VOID)	(void);

///////////////////////////////////////////////////////////////////////////////
// Class GUIThread

class GUIThread : public Thread
{
// Construction and destruction
public:
	GUIThread();
	virtual ~GUIThread();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCommandLine
	//
	// Description:	Sets the gui commandline parameters
	//					
	// Parameters:	strCommandLine		-h host -p port
	//
	// Returns:		NULL
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetCommandLine(const string& strCommandLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Run()
	// description	: This is the thread method, after calling the start method this
	//				  method will be executed in a separate thread.
	//
	// parameters	: None
	//
	// returns		: Int		Your own defined thread return code
	//
	///////////////////////////////////////////////////////////////////////////////
	unsigned int Run();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Start
	//
	// Description:	Starts the server in a separate thread
	//					
	// Parameters:	None
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Start();
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Stop
	//
	// Description:	Stops the server and waits for all threads involved to stop
	//					
	// Parameters:	None
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Stop();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Reset
	//
	// Description:	Reset the GUI. 
	//					
	// Parameters:	None
	//
	// Returns:		True				successful
	//				False				otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Reset();

// Member variables
private:
	
	string		m_strCommandLine;			// Commandline parameters
	HMODULE		m_hModule;					// DLL handle
	INT_PCHAR	m_fpStartGUI;				// Start GUI function pointer
	INT_VOID	m_fpStopGUI;				// Stop GUI function pointer
};

///////////////////////////////////////////////////////////////////////////////

#endif //!GUITHREAD_H
