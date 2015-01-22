/*****************************************************************************
 * $Workfile: StrExpression.cpp $
 * $Revision: 3 $
 * $Modtime: 1/30/01 2:00p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "StrExpression.h"		// Class definition

#include <string>

using namespace std;

#include "Context.h"
#include "Expression.h"
#include "ExprResult.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						StrExpression::StrExpression
//						============================
(
	const string&		strValue,
	const string&		strPrecision
)
{
	// Set the members.
	m_strValue	   = strValue;
	m_strPrecision = strPrecision;
}


// Destructor
//						=============================
						StrExpression::~StrExpression()
//						=============================
{
	// Empty.						
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
ExprResult				StrExpression::Evaluate
//						======================= 
(
	Context&			context
) const
{
	// Create a result.
	ExprResult result( m_strPrecision );

	// Every value can be the value of a string constant, so set the status
	// to OK. Then, set the value of result to the member value, and the type
	// to STRING.
	result.SetStatus( ExprResult::OK );
	result.SetValue( m_strValue );
	result.SetType( ExprResult::STRING );

	return result;
}
