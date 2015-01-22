/*****************************************************************************
 * $Workfile: AssignExpression.cpp $
 * $Revision: 3 $
 * $Modtime: 1/29/01 3:59p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "AssignExpression.h"		// Class definition

//#include <string>
//using namespace std;

#include "Context.h"
#include "Expression.h"
#include "ExprResult.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						==================================
						AssignExpression::AssignExpression
//						==================================
(
	Expression*	const	pOperand1,
	Expression*	const	pOperand2,
	const string&		strPrecision
)
{
	m_pOperand1    = pOperand1;
	m_pOperand2    = pOperand2;
	m_strPrecision = strPrecision;
}

// Destructor
//						===================================
						AssignExpression::~AssignExpression()
//						===================================
{
	delete m_pOperand1;
	delete m_pOperand2;

	m_pOperand1=0;
	m_pOperand2=0;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==========================
ExprResult				AssignExpression::Evaluate
//						========================== 
(
	Context&			context
) const
{
	// Create a result, and initialise its status as undefined.
	ExprResult result( m_strPrecision );
	result.SetStatus( ExprResult::UNDEF_STATUS );

	// Evaluate the two operands of the multiplication expression.
	ExprResult left	 = m_pOperand1->Evaluate( context );
	ExprResult right = m_pOperand2->Evaluate( context );

	// In case the right operand is a variable, convert it to its contents.
	right.ConvertFromVar( context );

	// Check if both the operands were evaluated as OK.
	if ( left.IsOK() && right.IsOK() )
	{	
		// Check if the left operand is a cluster variable.
		if ( left.GetType() == ExprResult::VAR )
		{
			// Add the variable, whose name is the value of the left operand,
			// with the value and type specified by the right operand, to
			// the context.
			context.Assign( left.GetValue(), right.GetValue(), ConvertType( right.GetType() ) );
		
			// Set the result to the right operand;
			result = right;
		}
		else
		{
			// The left operand is not a cluster variable; set the result
			// status to ASSIGN_NO_VAR_ERROR.
			result.SetStatus( ExprResult::ASSIGN_NO_VAR_ERROR );
		}
	}
	else
	{
		// Check if an error was found in the left operand.
		if ( !left.IsOK() )
		{
			// Set as status and value of the result, those of the left operand.
			result.SetStatus( left.GetStatus() );
			result.SetValue( left.GetValue() );
		}
		else
		{
			// Set as status and value of the result, those of the right operand.
			result.SetStatus( right.GetStatus() );
			result.SetValue( right.GetValue() );
		}
	}
	
	return result;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============================
int						AssignExpression::ConvertType
//						=============================
(
	int					nResultType
) const
{
	// Return the context value corresponding with the specified result type.

	switch (nResultType)
	{
		case ExprResult::INT:
			return Context::INT;

		case ExprResult::FLOAT:
			return Context::FLOAT;

		case ExprResult::STRING:
			return Context::STRING;

		case ExprResult::UNSPECIFIED:
		default:
			return Context::UNSPECIFIED;
	}
}
