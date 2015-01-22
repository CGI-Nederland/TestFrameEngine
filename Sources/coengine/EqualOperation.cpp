/*****************************************************************************
 * $Workfile: EqualOperation.cpp $
 * $Revision: 3 $
 * $Modtime: 5/09/01 5:58p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "EqualOperation.h"		// Class definition.

// Includes.
#include <string>

using namespace std;

#include "Number.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						==============================
						EqualOperation::EqualOperation()
//						==============================
{
	// Fill the set of operator values with the allowed values of
	// the 'equal to'-operator.
	m_sstrOperators.insert( "==" );
	m_sstrOperators.insert( "=" );
	m_sstrOperators.insert( "eq" );
	m_sstrOperators.insert( "is" );
	m_sstrOperators.insert( "ist" );
	m_sstrOperators.insert( "est" );
	m_sstrOperators.insert( "equal to" );
	m_sstrOperators.insert( "ist gleich" );
	m_sstrOperators.insert( "égal à" );
	m_sstrOperators.insert( "egal a" );
	m_sstrOperators.insert( "gelijk aan" );
}


// destructor
//						===============================
						EqualOperation::~EqualOperation()
//						===============================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						========================
bool					EqualOperation::Evaluate
//						========================
(
	const string&		strLeft,
	const string&		strRight
)
{
	bool bResult = false;
	
	// Create Number objects for both operands.
	Number numLeft( strLeft );
	Number numRight( strRight );

	// Determine if both operand values can be interpreted as numbers.
	if ( numLeft.IsNumber() && numRight.IsNumber() )
	{
		// Determine if the numerical value of the left operand is equal to
		// that of the right operand.
		if ( numLeft.GetNumValue() == numRight.GetNumValue() )
		{
			// The 'equal to'-relation is positive.
			bResult = true;
		}
	}
	else
	{
		// The strings can not be interpreted as numbers; determine if the
		// characters of both strings match exactly.
		if ( strLeft == strRight )
		{
			// The 'equal to'-relation is positive.
			bResult = true;
		}
	}

	return bResult;
}
