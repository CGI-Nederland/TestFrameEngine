/*****************************************************************************
 * $Workfile: Thread.h $
 * $Revision: 5 $
 * $Modtime: 3/29/01 2:52p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef THREAD_H
#define THREAD_H

#ifdef	UNIX

	// Unix
	#include <pthread.h>
	
	#define MODIFIER
	typedef void*			THREADRETURN;

#else

	// Windows
	#define MODIFIER		__stdcall
	typedef unsigned int	THREADRETURN;

#endif

#include "Mutex.h"
#include "Semaphore.h"

THREADRETURN MODIFIER ThreadDispatch(void* pThread);

////////////////////////////////////////////////////////////////////////////////
// class Thread
class Thread : public Mutex, public Semaphore
{
	// Construction and destruction
public:
	Thread();							// Constructor

private:
	Thread(const Thread& right);		// Copy contructor

	// Other constructors
public:
	virtual~Thread();							// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Start()
	// description	: This method whil spawn a thread which executes the run method
	//
	// parameters	: None
	//
	// returns		: true		Thread started successful
	//				  false		Thread failure
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Start();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Stop()
	// description	: This	method signals the thread to gracefully exit.
	//
	// parameters	: None
	//
	// returns		: <void>
	//
	///////////////////////////////////////////////////////////////////////////////
	void Stop();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Run()
	//
	// description	: This is the thread method, after calling the start method this
	//				  method will be executed in a separate thread.
	//
	// parameters	: None
	//
	// returns		: Int		Your own defined thread return code
	//
	///////////////////////////////////////////////////////////////////////////////
	virtual unsigned int Run() = 0;

	///////////////////////////////////////////////////////////////////////////////
	// function		: WaitForThreadReturn
	// description	: This method wait until the thread exits.
	//
	// parameters	: None
	//
	// returns		: Int		Your own defined thread return code
	//
	///////////////////////////////////////////////////////////////////////////////
	void WaitForThreadReturn();

	// Member variables
private:

#ifdef UNIX

	// Unix
	pthread_t		m_nHandle;			// Thread handle

#else

	// Windows
	unsigned long	m_nHandle;			// Thread handle

#endif

protected:
	bool			m_bStop;			// Stop flag

public:
	
	// Thread state
	enum STATE { INITIALISED, RUNNING, TERMINATED };

	STATE	m_nState;					// Thread state
};

#endif // !THREAD_H