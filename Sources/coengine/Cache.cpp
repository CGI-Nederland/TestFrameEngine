/*****************************************************************************
 * $Workfile: Cache.cpp $
 * $Revision: 1 $
 * $Modtime: 4/13/01 12:11p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "Cache.h"				// Class definition

// Includes
#include <deque>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						============
						Cache::Cache()
//						============
{
	// Initialise a new cache out recording state.
	m_bRecording = false;
}


// Destructor
//						=============
						Cache::~Cache()
//						=============
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=====================
void					Cache::StartRecording()
//						=====================
{
	// Set the cache in the recording state.
	m_bRecording = true;
}


//						====================
void					Cache::StopRecording()
//						====================
{
	// Set the cache out of the recording state.
	m_bRecording = false;
}


//						==========
bool					Cache::Add
//						==========
(
	int					nLineNumber,
	const string&		strLine
)
{
	// Determine if the cache is in recording state.
	if ( m_bRecording )
	{
		// Make a pair of the specified line number and line contents,
		// and add it to the back of the line queue.
		m_LineQueue.push_back( make_pair( nLineNumber, strLine ) );
	}
	
	return m_bRecording;
}


//						=================
bool					Cache::RemoveLast()
//						=================
{
	bool bResult = false;

	// Determine if the cache is not empty.
	if ( !Empty() )
	{
		// Remove the latest addition from the line queue.
		m_LineQueue.pop_back();
		bResult = true;
	}

	return bResult;
}


//						============
void					Cache::Clear()
//						============
{
	// Remove all the elements from the line queue.
	m_LineQueue.clear();
}


//						===========
int						Cache::Size() const
//						===========
{
	// Get the line queue's size, and return it.
	return m_LineQueue.size();
}


//						============
bool					Cache::Empty() const
//						============
{
	// Determine if the size of the cache is zero,
	// and return the boolean result.
	return ( Size() == 0 );
}


//						==============
string					Cache::GetLine
//						==============
(
	int					nElement
) const
{
	// Initialise the line to return as an empty string.
	string strLine = "";

	// Determine if the specified element is valid for the line queue.
	if ( ( nElement >= 0 ) && ( nElement < Size() ) )
	{
		// Get the contents of the line stored at the specified element of the
		// line queue.
		strLine = m_LineQueue[nElement].second;
	}

	return strLine;
}


//						====================
int						Cache::GetLineNumber
//						====================
(
	int					nElement
) const
{
	// Initialise the line number to return as zero.
	int nLine = 0;

	// Determine if the specified element is valid for the line queue.
	if ( ( nElement >= 0 ) && ( nElement < Size() ) )
	{
		// Get the number of the line stored at the specified element of the
		// line queue.
		nLine = m_LineQueue[nElement].first;
	}

	return nLine;
}
