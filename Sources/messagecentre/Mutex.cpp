/*****************************************************************************
 * $Workfile: Mutex.cpp $
 * $Revision: 1 $
 * $Modtime: 3/29/01 3:24p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "Mutex.h"		// Class definition

//#include <windows.h>

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============
						Mutex::Mutex()
//						============							
{
	InitializeCriticalSection(&m_critsect);
}


// Destructor
//						=============
						Mutex::~Mutex()
//						=============
{
	DeleteCriticalSection(&m_critsect);						
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===========
void					Mutex::Lock()
//						===========
{ 
	EnterCriticalSection(&m_critsect); 
}

//						=============
void					Mutex::Unlock()
//						=============
{ 
	LeaveCriticalSection(&m_critsect); 
}

////////////////////////////////////////////////////////////////////////////////
