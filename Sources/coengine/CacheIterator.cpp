/*****************************************************************************
 * $Workfile: CacheIterator.cpp $
 * $Revision: 1 $
 * $Modtime: 4/13/01 3:35p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "Cache.h"
#include "CacheIterator.h"			// Class definition

// Includes
//#include <string>
//using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						CacheIterator::CacheIterator
//						============================
(
	Cache*				pTheCache,
	int					nType,
	int					nFirst,
	int					nIterations
)
{
	// Initialise the pointer to the cache, the type of iterator, the starting
	// element number. the number of iterations it is to do, and the counter.
	m_pTheCache	  = pTheCache;
	m_nType		  = nType;
	m_nFirst	  = nFirst;
	m_nTotalLoops = nIterations;
	m_nLoopsToGo  = nIterations;
	m_nCounter	  = 1;

	// Set the current position to its starting position.
	m_nPos = m_nFirst;

	// Set the end position to a default invalid value.
	m_nLast = -1;

	m_bOpen = true;
}


// Destructor
//						=============================
						CacheIterator::~CacheIterator()
//						=============================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						======================
int						CacheIterator::GetType() const
//						======================
{
	// Return the iterator's type.
	return m_nType;
}


//						======================
string					CacheIterator::GetLine() const
//						======================
{
	// Get from the cache the line corresponding with the iterator's current
	// position, and return it.
	return m_pTheCache->GetLine( m_nPos );
}


//						============================
int						CacheIterator::GetLineNumber() const
//						============================
{
	// Get from the cache the line number corresponding with the iterator's
	// current position, and return it.
	return m_pTheCache->GetLineNumber( m_nPos );
}


//						==========================
void					CacheIterator::SetPosition
//						==========================
(
	int					nPos
)
{
	// Set the current position.
	m_nPos = nPos;
}


//						==========================
int						CacheIterator::GetPosition() const
//						==========================
{
	// Return the current position of the iterator.
	return m_nPos;
}


//						===================
void					CacheIterator::Next()
//						===================
{
	// Increment the current position with one.
	m_nPos++;
}


//						=====================
bool					CacheIterator::IsOpen() const
//						=====================
{
	// Return true if the iterator is open.
	return m_bOpen;
}


//						====================
void					CacheIterator::Close()
//						====================
{
	// Determine if the iterator is open.
	if ( IsOpen() )
	{
		// Set the iterator state to closed.
		m_bOpen = false;

		// Set the position of the last element to be the current one.
		m_nLast = m_nPos;
	}
}


//					===========================
int					CacheIterator::GetLoopsToGo() const
//					===========================
{
	// Return the number of loops to go.
	return m_nLoopsToGo;
}


//					===========================
void				CacheIterator::SetLoopsToGo
//					===========================
(
	int				nLoopsToGo
)
{
	// Set the number of loops to go.
	m_nLoopsToGo  = nLoopsToGo;
	m_nTotalLoops = nLoopsToGo;
}


//						=================================
int						CacheIterator::DecrementLoopsToGo()
//						=================================
{
	int nLoops = -1;

	// Determine if the iterator's type is UNCONDITIONAL.
	if ( m_nType == UNCONDITIONAL )
	{
		// Decrement the number of loops with 1.
		m_nLoopsToGo--;
		nLoops = m_nLoopsToGo;
	}

	return nLoops;
}


//						=============================
void					CacheIterator::SetToBeginning()
//						=============================
{
	// Set the current position to the position before the
	// iterator's beginning, and increment the counter.
	m_nPos = m_nFirst -1;
	m_nCounter++;
}


//						=====================
int						CacheIterator::GetEnd() const
//						=====================
{
	// Return the position of the last element.
	return m_nLast;
}


//						=======================
int						CacheIterator::GetBegin() const
//						=======================
{
	// Return the position of the first element.
	return m_nFirst;
}


//						=========================
int						CacheIterator::GetCounter() const
//						=========================
{
	// Return the counter's value.
	return m_nCounter;
}


//						============================
int						CacheIterator::GetTotalLoops() const
//						============================
{
	// Return the total number of loops, as set during construction.
	return m_nTotalLoops;
}