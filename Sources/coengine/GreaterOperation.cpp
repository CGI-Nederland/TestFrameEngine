/*****************************************************************************
 * $Workfile: GreaterOperation.cpp $
 * $Revision: 3 $
 * $Modtime: 5/09/01 5:57p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "GreaterOperation.h"	// Class definition.

// Includes.
#include <string>

using namespace std;

#include "Number.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						==================================
						GreaterOperation::GreaterOperation()
//						==================================
{
	// Fill the set of operator values with the allowed values of
	// the 'greater than'-operator.
	m_sstrOperators.insert( ">" );
	m_sstrOperators.insert( "gt" );
	m_sstrOperators.insert( "greater than" );
	m_sstrOperators.insert( "größer als" );
	m_sstrOperators.insert( "groesser als" );
	m_sstrOperators.insert( "supérieur à" );
	m_sstrOperators.insert( "superieur a" );
	m_sstrOperators.insert( "groter dan" );
}


// destructor
//						===================================
						GreaterOperation::~GreaterOperation()
//						===================================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						==========================
bool					GreaterOperation::Evaluate
//						==========================
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
		// that of the right operand.
		if ( numLeft.GetNumValue() > numRight.GetNumValue() )
		{
			// The 'greater than'-relation is positive.
			bResult = true;
		}
	}
	else
	{
		// The strings can not be interpreted as numbers; determine if the
		// left operand comes alphabetically after the right operand.
		if ( strLeft > strRight )
		{
			// The 'greater than'-relation is positive.
			bResult = true;
		}
	}

	return bResult;
}
