/*****************************************************************************
 * $Workfile: AddExpression.cpp $
 * $Revision: 4 $
 * $Modtime: 1/29/01 3:59p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable: 4786)

#include "AddExpression.h"

//#include <string>

//using namespace std;

#include "Expression.h"
#include "ExprResult.h"
#include "StrUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						AddExpression::AddExpression
//						============================
(
	Expression* const	pOperand1,
	Expression* const	pOperand2,
	const string&		strPrecision
)
{
	m_pOperand1    = pOperand1;
	m_pOperand2	   = pOperand2;
	m_strPrecision = strPrecision;
}

// Destructor
//						=============================
						AddExpression::~AddExpression()
//						=============================
{
	delete m_pOperand1;
	delete m_pOperand2;

	m_pOperand1=0;
	m_pOperand2=0;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
ExprResult				AddExpression::Evaluate
//						======================= 
(
	Context&			context
) const
{
	// Create a result, and initialise its type as error.
	ExprResult result( m_strPrecision );
	result.SetStatus( ExprResult::UNDEF_STATUS );

	// Evaluate the two operands of the addition expression.
	ExprResult left	 = m_pOperand1->Evaluate( context );
	ExprResult right = m_pOperand2->Evaluate( context );

	// Convert any possible variable to its contents.
	left.ConvertFromVar( context );
	right.ConvertFromVar( context );

	// Check if both the operands were evaluated as OK.
	if ( left.IsOK() && right.IsOK() )
	{
		// Check if both operands have either an arithmetic type or type
		// UNSPECIFIED which can be interpreted as an arithmetic type.
		if ( ( left.IsNumber() || ( left.IsUnspecified() && left.InterpretAsNumber() ) )
			&& ( right.IsNumber() || ( right.IsUnspecified() && right.InterpretAsNumber() ) ) )
		{
			// The (numerical) values of both operands can be added.
			result = Add( left, right );
		}
		else
		{
			// The values of both operands can be concatenated.
			result = Concatenate( left, right );
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
// Implementation

//						==================
ExprResult				AddExpression::Add
//						==================
(
	ExprResult&			left,
	ExprResult&			right
) const
{
	// Create a result, and initialise its status as undefined.
	ExprResult result( m_strPrecision );
	result.SetStatus( ExprResult::UNDEF_STATUS );

	// Convert any possible UNSPECIFIED operand.
	left.ConvertFromUnspecified();
	right.ConvertFromUnspecified();

	// Both operands must now have arithmetic types; check if either
	// operand has the type FLOAT.
	if ( left.IsFloat() || right.IsFloat() )
	{
		// Convert both to FLOAT.
		left.ConvertToFloat();
		right.ConvertToFloat();
	}

	// Get the numerical values of the operands.
	double* pNumValLeft  = left.GetNumValue();
	double* pNumValRight = right.GetNumValue();

	// Check if the numerical values exist; i.e. check if no
	// null pointers were returned.
	if ( pNumValLeft != 0 && pNumValRight != 0 )
	{
		// Calculate the numerical value of the result by adding
		// the numerical values of the operands.
		double dlNumVal = (*pNumValLeft) + (*pNumValRight);

		// Since both operands now have the same type, check the type
		// of the left operand to check if both have type INT.
		if ( left.IsInt() )
		{
			// Take as value of the result the conversion of its
			// numerical value to a string; not using exponential
			// notation, and with a precision of 0. Then, set the
			// result type to INT.
			result.SetValue( DoubleAsIntToStr( dlNumVal ) );
			result.SetType( ExprResult::INT );
		}
		else
		{
			// Take as value of the result the conversion of its
			// numerical value to a string, using a precision of
			// ADDPRECISION. Then, set the result type to FLOAT.
			result.SetValue( DoubleToStr( dlNumVal, ADDPRECISION ) );
			result.SetType( ExprResult::FLOAT );
		}

		// Set the result status to OK.
		result.SetStatus( ExprResult::OK );
	}
	else
	{
		// Although the operands were of arithmetic type, no mumerical
		// value could be determined; internal error.
		result.SetStatus( ExprResult::INTERNAL_ERROR );
	}

	return result;
}


//						==========================
ExprResult				AddExpression::Concatenate
//						==========================
(
	ExprResult&			left,
	ExprResult&			right
) const
{
	// Create a result.
	ExprResult result( m_strPrecision );

	// Convert both operands to type STRING.
	left.ConvertToString();
	right.ConvertToString();

	// Set the result value to the concatenation of the string values
	// of the left and right operand.
	result.SetValue( left.GetValue() + right.GetValue() );

	// Set the result type to STRING, and its status to OK.
	result.SetType( ExprResult::STRING );
	result.SetStatus( ExprResult::OK );

	return result;
}
