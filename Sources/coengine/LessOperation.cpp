/*****************************************************************************
 * $Workfile: LessOperation.cpp $
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

#include "LessOperation.h"		// Class definition.

// Includes.
#include <string>

using namespace std;

#include "Number.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						============================
						LessOperation::LessOperation()
//						============================
{
	// Fill the set of operator values with the allowed values of
	// the 'less than'-operator.
	m_sstrOperators.insert( "<" );
	m_sstrOperators.insert( "lt" );
	m_sstrOperators.insert( "less than" );
	m_sstrOperators.insert( "kleiner als" );
	m_sstrOperators.insert( "inférieur à" );
	m_sstrOperators.insert( "inferieur a" );
	m_sstrOperators.insert( "kleiner dan" );
}


// destructor
//						=============================
						LessOperation::~LessOperation()
//						=============================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=======================
bool					LessOperation::Evaluate
//						=======================
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
		// Determine if the numerical value of the left operand is less than
		// that of the right operand.
		if ( numLeft.GetNumValue() < numRight.GetNumValue() )
		{
			// The 'less than'-relation is positive.
			bResult = true;
		}
	}
	else
	{
		// The strings can not be interpreted as numbers; determine if the
		// left operand comes alphabetically before the right operand.
		if ( strLeft < strRight )
		{
			// The 'less than'-relation is positive.
			bResult = true;
		}
	}

	return bResult;
}
