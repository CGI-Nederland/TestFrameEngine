/*****************************************************************************
 * $Workfile: VarExpression.cpp $
 * $Revision: 4 $
 * $Modtime: 1/29/01 12:55p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "VarExpression.h"		// Class definition

#include <string>

using namespace std;

#include "Context.h"
#include "Expression.h"
#include "ExprResult.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						VarExpression::VarExpression
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
						VarExpression::~VarExpression()
//						=============================
{}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations


//						=======================
ExprResult				VarExpression::Evaluate
//						======================= 
(
	Context&			context
) const
{
	// Create a result.
	ExprResult result( m_strPrecision );

	// Set its type to VAR, its value to the specified variable name,
	// and its status to OK.
	result.SetType( ExprResult::VAR );
	result.SetValue( m_strValue );
	result.SetStatus( ExprResult::OK );

	return result;
}
