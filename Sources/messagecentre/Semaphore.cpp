/*****************************************************************************
 * $Workfile: Semaphore.cpp $
 * $Revision: 1 $
 * $Modtime: 3/29/01 3:24p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "Semaphore.h"		// Class definition

//#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						====================
						Semaphore::Semaphore()
//						====================							
{
	// Create semaphore
	m_semaphore = CreateSemaphore((LPSECURITY_ATTRIBUTES)0, 0, 0x7ffffff, (const char*)0);
}

//						====================
						Semaphore::Semaphore
//						====================
(
	int nAvailable=1
)
{
	// Create semaphore						{
    m_semaphore = CreateSemaphore((LPSECURITY_ATTRIBUTES)0, nAvailable, 0x7ffffff, (const char*)0);
}

// Destructor
//						=====================
						Semaphore::~Semaphore()
//						=====================
{
	// Close semaphore
	CloseHandle(m_semaphore);					
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===============
void					Semaphore::Wait()
//						===============
{ 
	// Wait infinite
	WaitForSingleObject(m_semaphore, INFINITE);
}

//						===============
void					Semaphore::Post()
//						===============
{ 
	// Post message notifying a wait call
	ReleaseSemaphore(m_semaphore, 1, (long*)0);
}


//						===============
void					Semaphore::Post
//						===============
(
	int nHowMany
)
{ 
	// Post message notifying N waiting calls
	ReleaseSemaphore(m_semaphore, nHowMany, (long*)0);
}

////////////////////////////////////////////////////////////////////////////////
