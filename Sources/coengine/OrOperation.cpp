/*****************************************************************************
 * $Workfile: OrOperation.cpp $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:40a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "OrOperation.h"		// Class definition.

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						========================
						OrOperation::OrOperation()
//						========================
{
	// Fill the set of operator values with the allowed values of
	// the 'or'-operator.
	m_sstrOperators.insert( "or" );
	m_sstrOperators.insert( "oder" );
	m_sstrOperators.insert( "ou" );
	m_sstrOperators.insert( "of" );
}


// destructor
//						=========================
						OrOperation::~OrOperation()
//						=========================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=====================
bool					OrOperation::Evaluate
//						=====================
(
	bool				bLeft,
	bool				bRight
)
{
	// Determine the logical 'or' of both operators, and return its result.
	return ( bLeft || bRight );
}
