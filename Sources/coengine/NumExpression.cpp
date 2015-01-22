/*****************************************************************************
 * $Workfile: NumExpression.cpp $
 * $Revision: 3 $
 * $Modtime: 1/29/01 12:53p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "NumExpression.h"	// Class definition

#include <string>

using namespace std;

#include "Context.h"
#include "Expression.h"
#include "ExprResult.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						NumExpression::NumExpression
//						============================
(
	const string&		strValue,		// string containing numerical value
	const string&		strPrecision	// precision format from settings
)
{
	// Set member variables.
	m_strValue	   = strValue;
	m_strPrecision = strPrecision;
}

// Destructor
//						=============================
						NumExpression::~NumExpression()
//						=============================
{}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
ExprResult				NumExpression::Evaluate
//						======================= 
(
	Context&			context
) const
{
	// Create a result; initialise status as error, and type as UNDEFINED.
	ExprResult result( m_strPrecision );
	result.SetStatus( ExprResult::UNDEF_STATUS );
	result.SetType( ExprResult::UNSPECIFIED );

	// Set the value of result.
	result.SetValue( m_strValue );

	// First try to convert the result from UNSPECIFIED to INT, and check if
	// this succeeds.
	if ( result.ConvertToInt() )
	{
		// The type has been set to INT; set the status to OK.
		result.SetStatus( ExprResult::OK );
	}
	// The result's value is not that of an INT; try to convert it from
	// UNSPECIFIED to FLOAT, and check if this succeeds.
	else if ( result.ConvertToFloat() )
	{
		// The type has been set to FLOAT; set the status to OK.
		result.SetStatus( ExprResult::OK );
	}
	else
	{
		// The lexer found the value to be that of a number, but it can't be
		// converted to one; internal error.
		result.SetStatus( ExprResult::INTERNAL_ERROR );
	}

	return result;
}
