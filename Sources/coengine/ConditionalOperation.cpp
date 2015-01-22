/*****************************************************************************
 * $Workfile: ConditionalOperation.cpp $
 * $Revision: 1 $
 * $Modtime: 3/14/01 12:45p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "ConditionalOperation.h"		// Class definition.

// Includes
#include <set>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						==========================================
						ConditionalOperation::ConditionalOperation()
//						==========================================
{
	// Empty.
}


// Destructor
//						===========================================
						ConditionalOperation::~ConditionalOperation()
//						===========================================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						================================
bool					ConditionalOperation::IsOperator
//						================================
(
	const string&		strOperator
) const
{
	bool bResult = false;

	// Determine if the specified operator is present in the set of
	// operator values.
	if ( m_sstrOperators.find( strOperator ) != m_sstrOperators.end() )
	{
		bResult = true;
	}

	return bResult;
}
