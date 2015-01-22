/*****************************************************************************
 * $Workfile: LogicalCondition.cpp $
 * $Revision: 1 $
 * $Modtime: 3/15/01 6:27p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "LogicalCondition.h"	// Class definition.
#include "AndOperation.h"
#include "LogicalOperation.h"
#include "OrOperation.h"
#include "StrUtil.h"			// Needed for trimming the operator-string.

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// default constructor
//						==================================
						LogicalCondition::LogicalCondition()
//						==================================
{
	// Fill the vector of logical operation objects.
	m_vpOperations.push_back( new AndOperation() );
	m_vpOperations.push_back( new OrOperation() );
							
	// Set the current logical operation object pointer to the null pointer.
	m_pCurrentOperation = 0;
}


// Destructor
//						===================================
						LogicalCondition::~LogicalCondition()
//						===================================
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

//						=============================
bool					LogicalCondition::SetOperator
//						=============================
(
	const string&		strOperator
)
{
	bool bResult = false;

	// Trim the leading and trailing spaces from the specified operator value.
	string strLogicOp = trim( strOperator );

	// Set the current object pointer to the null pointer; in case the
	// specified operator turns out to be an invalid logical operator
	// value, the pointer will remain the null pointer.
	m_pCurrentOperation = 0;

	// Go passed all logical operation objects in the vector.
	bool bReady = false;
	int  i;
	for ( i = 0; i < m_vpOperations.size() && !bReady; i++ )
	{
		// Determine if the specified operator is one the operator values
		// of the logical operation object we're now looking at.
		if ( m_vpOperations[i]->IsOperator( strLogicOp ) )
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


//						==========================
bool					LogicalCondition::Evaluate
//						==========================
(
	bool				bLeft,
	bool				bRight
) const
{
	bool bResult = false;

	// Determine if a current operation object is available.
	if ( m_pCurrentOperation != 0 )
	{
		// Evaluate the logical combination of the two specified operands,
		// according to the current type of logical operation; return the
		// result of this operation.
		bResult = m_pCurrentOperation->Evaluate( bLeft, bRight );
	}

	return bResult;
}
