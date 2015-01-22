/*****************************************************************************
 * $Workfile: Thread.cpp $
 * $Revision: 7 $
 * $Modtime: 3/21/01 2:27p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable:4786)

#include "Thread.h"

#ifdef	UNIX

	// Unix 
	#include <pthread.h>

#else

	// Windows
	#include <windows.h>
	#include <process.h>
	#include <string>

#endif

using namespace std;

#include "EngineDebug.h" 

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
Thread::Thread()
{
	m_bStop		= false;		// Initialise stop flag 
	m_nHandle	= 0;			// Initialise thread handle
	m_nState	= INITIALISED;	// Set thread state
}

// Destructor
Thread::~Thread()
{
	Stop();

	WaitForThreadReturn();
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//				===============
bool			Thread::Start()
//				===============
{
	bool		  bResult = false;

#ifdef	UNIX

	// Unix
	unsigned int  nResult;

	// Start client thread
	nResult = pthread_create(&m_nHandle, 0, &ThreadDispatch, this);

	// Evaluate result
	if (nResult == 0) bResult = true;

#else
	// Windows

	// Start client thread
	unsigned int nThreadID = 0;
    m_nHandle = _beginthreadex(0, 0, &ThreadDispatch, this, 0, &nThreadID);

	// Evaluate result
	if (m_nHandle != 0) bResult = true;

#endif

	return bResult;
}

//				==============
void			Thread::Stop()
//				==============
{
	// Set the stop flag
	m_bStop = true;	
}

//				=============================
void			Thread::WaitForThreadReturn()
//				=============================
{
	// Wait for the thread to terminate
#ifdef UNIX

	// Unix
	pthread_join(m_nHandle, 0);

#else

	EngineDebugOutput("WaitForThreadReturn pre", THREAD, 0);
	
	// If thread is not closed, close it
	if (m_nHandle != 0)
	{
		// Wait for semaphore to thread end notification
		Wait();

		// Clean up the resources
		CloseHandle((void *)m_nHandle);

		// Eliminate multiple cleanups
		m_nHandle = 0;
	}

	EngineDebugOutput("WaitForThreadReturn post", THREAD, 0);

#endif

}


//						==============
THREADRETURN MODIFIER	ThreadDispatch
//						==============
(
	void*				pThread
)
{
	unsigned int nResult;

	// Lock thread state
	((Thread*) pThread)->Lock();

	// Switch to running state
	((Thread*) pThread)->m_nState = Thread::RUNNING;

	// Unlock thread state
	((Thread*) pThread)->Unlock();

	// Call thread function
	nResult = ((Thread*) pThread)->Run();

	// Lock thread state
	((Thread*) pThread)->Lock();

	// Switch to terminated state
	((Thread*) pThread)->m_nState = Thread::TERMINATED;

	// Unlock thread state
	((Thread*) pThread)->Unlock();

	// Signal thread end notification
	((Thread*) pThread)->Post();

	return (THREADRETURN) nResult;
}