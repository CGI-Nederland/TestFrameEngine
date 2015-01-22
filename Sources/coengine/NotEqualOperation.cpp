/*****************************************************************************
 * $Workfile: NotEqualOperation.cpp $
 * $Revision: 3 $
 * $Modtime: 5/09/01 5:59p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "NotEqualOperation.h"		// Class definition.

// Includes.
#include <string>

using namespace std;

#include "Number.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						====================================
						NotEqualOperation::NotEqualOperation()
//						====================================
{
	// Fill the set of operator values with the allowed values of
	// the 'not equal to'-operator.
	m_sstrOperators.insert( "!=" );
	m_sstrOperators.insert( "<>" );
	m_sstrOperators.insert( "ne" );
	m_sstrOperators.insert( "is not" );
	m_sstrOperators.insert( "ist nicht" );
	m_sstrOperators.insert( "n'est pas" );
	m_sstrOperators.insert( "is niet" );
	m_sstrOperators.insert( "not equal to" );
	m_sstrOperators.insert( "ist ungleich" );
	m_sstrOperators.insert( "différent de" );
	m_sstrOperators.insert( "different de" );
	m_sstrOperators.insert( "ongelijk aan" );
}


// destructor
//						=====================================
						NotEqualOperation::~NotEqualOperation()
//						=====================================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						===========================
bool					NotEqualOperation::Evaluate
//						===========================
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
		// Determine if the numerical value of the left operand is different
		// from that of the right operand.
		if ( numLeft.GetNumValue() != numRight.GetNumValue() )
		{
			// The 'not equal to'-relation is positive.
			bResult = true;
		}
	}
	else
	{
		// The strings can not be interpreted as numbers; determine if not
		// all characters of both strings match exactly.
		if ( strLeft != strRight )
		{
			// The 'not equal to'-relation is positive.
			bResult = true;
		}
	}

	return bResult;
}
