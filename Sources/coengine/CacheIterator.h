/*****************************************************************************
 * $Workfile: CacheIterator.h $
 * $Revision: 1 $
 * $Modtime: 4/13/01 3:34p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CACHEITERATOR_H
#define CACHEITERATOR_H

// Includes
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class Cache;

class CacheIterator
{
private:
	// default constructor of CacheIterator
	CacheIterator() {};

public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of CacheIterator
	//
	// parameters:	pTheCache		Pointer to the cache.
	//				nType			Type of loop which this iterator handles.
	//				nFirst			Cache element number at which the iterator
	//								starts.
	//				nLoopsToGo		Number of loops to go.
	///////////////////////////////////////////////////////////////////////////////
	CacheIterator( Cache* pTheCache, int nType, int nFirst, int nLoopsToGo );

	///////////////////////////////////////////////////////////////////////////////
	// destructor of CacheIterator
	///////////////////////////////////////////////////////////////////////////////
	~CacheIterator();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetType()
	//
	// description	:	This function returns the type of the iterator.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying iterator type
	///////////////////////////////////////////////////////////////////////////////
	int GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLine()
	//
	// description	:	This function returns the contents of the current line from
	//					the cache, that this iterator is pointing to.
	//
	// parameters	:	None.
	//
	// returns		:	string containing current line
	///////////////////////////////////////////////////////////////////////////////
	string GetLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLineNumber()
	//
	// description	:	This function returns the number of the current line from
	//					the cache, that this iterator is pointing to.
	//
	// parameters	:	None.
	//
	// returns		:	integer containing current line number
	///////////////////////////////////////////////////////////////////////////////
	int GetLineNumber() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetPosition()
	//
	// description	:	This function sets the current position to the specified
	//					parameter.
	//
	// parameters	:	nPos		new current position
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void SetPosition( int nPos );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetPosition()
	//
	// description	:	This function returns the current position of the cache
	//					element this iterator is pointing to.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying current cache position
	///////////////////////////////////////////////////////////////////////////////
	int GetPosition() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Next()
	//
	// description	:	This function sets the iterator to the next element in the
	//					cache. 
	//
	// parameters	:	None.
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void Next();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	IsOpen()
	//
	// description	:	This function returns whether the iterator is still open.
	//
	// parameters	:	None.
	//
	// returns		:	bool stating whether the iterator is open
	///////////////////////////////////////////////////////////////////////////////
	bool IsOpen() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Close()
	//
	// description	:	This function tells the iterator that the end of the loop
	//					has been encountered. If the iterator has already been
	//					closed, this function will have no effect.
	//
	// parameters	:	None.
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void Close();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLoopsToGo()
	//
	// description	:	This function returns the number of loops to go.
	//
	// parameters	:	None.
	//
	// returns		:	integer containing number of loops to go
	///////////////////////////////////////////////////////////////////////////////
	int GetLoopsToGo() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetLoopsToGo()
	//
	// description	:	This function (re)sets the number of loops to go.
	//
	// parameters	:	None.
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void SetLoopsToGo( int nLoopsToGo );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DecrementLoopsToGo()
	//
	// description	:	This function decrements the number of loops to go with 1,
	//					and returns the new number. This will only work if the
	//					type is UNCONDITIONAL; otherwise, -1 is returned.
	//
	// parameters	:	None.
	//
	// returns		:	new number of loops to go
	///////////////////////////////////////////////////////////////////////////////
	int DecrementLoopsToGo();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetToBeginning()
	//
	// description	:	This function sets the current position to the one before
	//					the	iterator's start position.
	//
	// parameters	:	None.
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void SetToBeginning();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetEnd()
	//
	// description	:	This function returns the iterator's end position.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying the iterator's end position
	///////////////////////////////////////////////////////////////////////////////
	int GetEnd() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetBegin()
	//
	// description	:	This function returns the iterator's start position.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying the iterator's start position
	///////////////////////////////////////////////////////////////////////////////
	int GetBegin() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetCounter()
	//
	// description	:	This function returns the iterator's counter, i.e., the
	//					current number of iterations.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying the iterator's counter
	///////////////////////////////////////////////////////////////////////////////
	int GetCounter() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetTotalLoops()
	//
	// description	:	This function returns the iterator's total number of
	//					iterations it is to perform; note that the returned value
	//					is only meaningful for unconditional iterators.
	//
	// parameters	:	None.
	//
	// returns		:	integer specifying the iterator's total number of
	//					iterations it is to perform
	///////////////////////////////////////////////////////////////////////////////
	int GetTotalLoops() const;

// enumeration
public:
	enum	TYPE	{	CONDITIONAL,
						UNCONDITIONAL
					};

// member variables
private:
	Cache*			m_pTheCache;	// Pointer to the cache.
	int				m_nType;		// Type of iterator.
	int				m_nTotalLoops;	// Total number of loops to repeat the
									// (unconditional) iterator.
	int				m_nLoopsToGo;	// Number of times to still repeat the
									// unconditional iterator.
	int				m_nFirst;		// First element of the cache for this iterator.
	int				m_nLast;		// Last element of the cache for this iterator.
	int				m_nPos;			// Current element in the cache.
	int				m_nCounter;		// Counter stating the current number of
									// iterations
	bool			m_bOpen;		// States whether the iterator is open.
};

#endif // !CACHEITERATOR_H

