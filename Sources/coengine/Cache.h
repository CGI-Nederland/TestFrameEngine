/*****************************************************************************
 * $Workfile: Cache.h $
 * $Revision: 1 $
 * $Modtime: 4/13/01 12:05p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CACHE_H
#define CACHE_H

// Includes
#include <deque>
#include <string>

using namespace std;

// Forward declarations

class Cache
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of Cache
	///////////////////////////////////////////////////////////////////////////////
	Cache();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of Cache
	///////////////////////////////////////////////////////////////////////////////
	~Cache();

	///////////////////////////////////////////////////////////////////////////////
	// function		: StartRecording()
	//
	// description	: This function sets the cache in the recording state.
	//
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void StartRecording();

	///////////////////////////////////////////////////////////////////////////////
	// function		: StopRecording()
	//
	// description	: This function sets the cache out of the recording state.
	//
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void StopRecording();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Add()
	//
	// description	: This function adds the number and contents of a cluster line
	//				  to the cache; this can only be done if the cache is set in
	//				  recording state.
	//
	// parameters	: nLineNumber	line number of line to add to the cache
	//				  strLine		contents of line to add to the cache
	//
	// returns		: true		line has been added to the cache
	//				  false		line could not be added to the cache
	///////////////////////////////////////////////////////////////////////////////
	bool Add( int nLineNumber, const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		: RemoveLast()
	//
	// description	: This function remove the latest addition from the cache; this
	//				  can only be done if the cache is not empty.
	//
	// parameters	: None.
	//
	// returns		: true		latest line has been removed from the cache
	//				  false		no line could be removed from the cache
	///////////////////////////////////////////////////////////////////////////////
	bool RemoveLast();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Clear()
	//
	// description	: This function completely empties the cache.
	//
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void Clear();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Size()
	//
	// description	: This function returns the current size of the cache.
	//
	// parameters	: None.
	//
	// returns		: integer specifying current size of the cache
	///////////////////////////////////////////////////////////////////////////////
	int Size() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Empty()
	//
	// description	: This function states whether or not the cache is empty, i.e.,
	//				  its size is zero.
	//
	// parameters	: None.
	//
	// returns		: true		the cache is empty
	//				  false		the cache is not empty
	///////////////////////////////////////////////////////////////////////////////
	bool Empty() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLine()
	//
	// description	: This function returns the (contents of) the line stored as
	//				  the specified element of the cache. Should this element not
	//				  exist, an empty string is returned.
	//
	// parameters	: int nElement		element in the cache
	//
	// returns		: contents of the specified line
	///////////////////////////////////////////////////////////////////////////////
	string GetLine( int nElement ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLineNumber
	//
	// description	: This function returns the number of the line stored as the
	//				  specified element of the cache. Should this element not
	//				  exist, zero is returned.
	//
	// parameters	: int nElement		element in the cache
	//
	// returns		: number of the specified line
	///////////////////////////////////////////////////////////////////////////////
	int GetLineNumber( int nElement ) const;

// member variables
private:
	deque< pair<int, string> > m_LineQueue;	// Queue containing the cached
											// cluster lines.
	bool m_bRecording;						// States whether new lines may be
											// placed in the cache.
};

#endif // !CACHE_H
