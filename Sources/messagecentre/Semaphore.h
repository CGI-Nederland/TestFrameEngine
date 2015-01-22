/*****************************************************************************
 * $Workfile: Semaphore.h $
 * $Revision: 1 $
 * $Modtime: 3/21/01 3:28p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <windows.h>

class Semaphore 
{

public:
	// Construction
	Semaphore();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Semaphore
	//
	// description	: Creates a semaphore with initial count nAvailable
	//					
	// parameters	: nAvailable	initial semaphore count
	//
	// returns		: string containing value of number
	///////////////////////////////////////////////////////////////////////////////
	explicit Semaphore(int nAvailable);

	// Destruction
	~Semaphore();

	////////////////////////////////////////////////////////////////////////////
	// ATTRIBUTES AND OPERATIONS

	///////////////////////////////////////////////////////////////////////////////
	// function		: Wait
	//
	// description	: This function blocks when the semaphore count is equal to 0 
	//					
	// parameters	: None
	//
	// returns		: None
	///////////////////////////////////////////////////////////////////////////////
	void Wait();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Post
	//
	// description	: This function increments the semaphore count by one, notifying
	//				  wait calls to stop blocking.
	//					
	// parameters	: None
	//
	// returns		: None.
	///////////////////////////////////////////////////////////////////////////////
	void Post(); 

	///////////////////////////////////////////////////////////////////////////////
	// function		: Post
	//
	// description	: This function increments the semaphore count by nHowMany, 
	//				  notifying wait calls to stop blocking.
	//
	// parameters	: None
	//
	// returns		: None.
	///////////////////////////////////////////////////////////////////////////////
	void Post(int nHowMany);

private:
	HANDLE m_semaphore;				// The actual semaphore
};

////////////////////////////////////////////////////////////////////////////////

#endif // !SEMAPHORE_H