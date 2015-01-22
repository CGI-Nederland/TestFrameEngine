/*****************************************************************************
 * $Workfile: GreaterEqualOperation.cpp $
 * $Revision: 3 $
 * $Modtime: 5/09/01 6:00p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "GreaterEqualOperation.h"	// Class definition.

// Includes.
#include <string>

using namespace std;

#include "Number.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						============================================
						GreaterEqualOperation::GreaterEqualOperation()
//						============================================
{
	// Fill the set of operator values with the allowed values of
	// the 'greater than or equal to'-operator.
	m_sstrOperators.insert( ">=" );
	m_sstrOperators.insert( "ge" );
	m_sstrOperators.insert( "greater or equal" );
	m_sstrOperators.insert( "größer oder gleich" );
	m_sstrOperators.insert( "groesser oder gleich" );
	m_sstrOperators.insert( "supérieur ou égal à" );
	m_sstrOperators.insert( "superieur ou egal a" );
	m_sstrOperators.insert( "groter of gelijk" );
}


// destructor
//						=============================================
						GreaterEqualOperation::~GreaterEqualOperation()
//						=============================================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						===============================
bool					GreaterEqualOperation::Evaluate
//						===============================
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
		// Determine if the numerical value of the left operand is greater than
		// or equal to that of the right operand.
		if ( numLeft.GetNumValue() >= numRight.GetNumValue() )
		{
			// The 'greater than or equal to'-relation is positive.
			bResult = true;
		}
	}
	else
	{
		// The strings can not be interpreted as numbers; determine if the
		// left operand comes alphabetically after or is identical to the
		// right operand.
		if ( strLeft >= strRight )
		{
			// The 'greater than or equal to'-relation is positive.
			bResult = true;
		}
	}

	return bResult;
}
