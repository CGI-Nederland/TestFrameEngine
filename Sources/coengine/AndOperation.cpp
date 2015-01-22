/*****************************************************************************
 * $Workfile: AndOperation.cpp $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:39a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "AndOperation.h"		// Class definition.

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						==========================
						AndOperation::AndOperation()
//						==========================
{
	// Fill the set of operator values with the allowed values of
	// the 'and'-operator.
	m_sstrOperators.insert( "and" );
	m_sstrOperators.insert( "und" );
	m_sstrOperators.insert( "et" );
	m_sstrOperators.insert( "en" );
}


// destructor
//						===========================
						AndOperation::~AndOperation()
//						===========================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						======================
bool					AndOperation::Evaluate
//						======================
(
	bool				bLeft,
	bool				bRight
)
{
	// Determine the logical 'and' of both operators, and return its result.
	return ( bLeft && bRight );
}
