/*****************************************************************************
 * $Workfile: mutex.h $
 * $Revision: 2 $
 * $Modtime: 3/21/01 2:55p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MUTEX_H
#define MUTEX_H

#include <windows.h>


////////////////////////////////////////////////////////////////////////////////
// class mutex

class Mutex {
public:
	
	// Construction
	Mutex();

	// Destruction
	 ~Mutex();

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Lock
	//
	// description	: Lock the mutex
	//					
	// parameters	: none.
	//
	// returns		: none.
	///////////////////////////////////////////////////////////////////////////////
	void Lock();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Unlock
	//
	// description	: Unlock the mutex
	//					
	// parameters	: none.
	//
	// returns		: none.
	///////////////////////////////////////////////////////////////////////////////
	void Unlock();

	// Member variables
private:
	CRITICAL_SECTION m_critsect;
};


#endif // !MUTEX_H
