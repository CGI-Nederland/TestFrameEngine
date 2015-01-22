/*****************************************************************************
 * $Workfile: RelationalCondition.cpp $
 * $Revision: 1 $
 * $Modtime: 3/15/01 6:26p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "RelationalCondition.h"	// Class definition.

// Includes
#include <string>
#include <vector>

using namespace std;

#include "EqualOperation.h"
#include "GreaterEqualOperation.h"
#include "GreaterOperation.h"
#include "LessEqualOperation.h"
#include "LessOperation.h"
#include "NotEqualOperation.h"
#include "RelationalOperation.h"
#include "StrUtil.h"				// Needed for trimming the operator-string.

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						========================================
						RelationalCondition::RelationalCondition()
//						========================================
{
	// Fill the vector of relational operation objects.
	m_vpOperations.push_back( new EqualOperation() );
	m_vpOperations.push_back( new NotEqualOperation() );
	m_vpOperations.push_back( new LessOperation() );
	m_vpOperations.push_back( new LessEqualOperation() );
	m_vpOperations.push_back( new GreaterOperation() );
	m_vpOperations.push_back( new GreaterEqualOperation() );
							
	// Set the current logical operation object pointer to the null pointer.
	m_pCurrentOperation = 0;
}


// Destructor
//						=========================================
						RelationalCondition::~RelationalCondition()
//						=========================================
{
	// Delete all objects placed the vector of logical operation objects, and
	// remove their pointers from the vector.
	while ( !m_vpOperations.empty() )
	{
		delete m_vpOperations.back();
		m_vpOperations.pop_back();
	}
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						================================
bool					RelationalCondition::SetOperator
//						================================
(
	const string&		strOperator
)
{
	bool bResult = false;

	// Trim the leading and trailing spaces from the specified operator value.
	string strRelationOp = trim( strOperator );

	// Set the current object pointer to the null pointer; in case the
	// specified operator turns out to be an invalid relational operator
	// value, the pointer will remain the null pointer.
	m_pCurrentOperation = 0;

	// Go passed all relational operation objects in the vector.
	bool bReady = false;
	int  i;
	for ( i = 0; i < m_vpOperations.size() && !bReady; i++ )
	{
		// Determine if the specified operator is one the operator values
		// of the relational operation object we're now looking at.
		if ( m_vpOperations[i]->IsOperator( strRelationOp ) )
		{
			// Set the current object pointer to this object, the result to
			// true, and specify that looking at other operation objects is
			// no longer necessary.
			m_pCurrentOperation = m_vpOperations[i];
			bResult = true;
			bReady  = true;
		}
	}

	return bResult;
}


//						=============================
bool					RelationalCondition::Evaluate
//						=============================
(
	const string&		strLeft,
	const string&		strRight
) const
{
	bool bResult = false;

	// Determine if a current operation object is available.
	if ( m_pCurrentOperation != 0 )
	{
		// Evaluate the logical combination of the two specified operands,
		// according to the current type of logical operation; return the
		// result of this operation.
		bResult = m_pCurrentOperation->Evaluate( strLeft, strRight );
	}

	return bResult;
}
