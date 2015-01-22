/*****************************************************************************
 * $Workfile: DivExpression.cpp $
 * $Revision: 3 $
 * $Modtime: 1/29/01 3:59p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable: 4786)

#include "DivExpression.h"	// Class definition

#include <string>
#include <Math.h>			// Needed for fmod()

using namespace std;

#include "Expression.h"
#include "ExprResult.h"
#include "StrUtil.h"		// Needed for conversions of double to string

// Definitions
#define DIVDELTA		1.0e-12	// Taken as the difference less than which the
								//   division of two numbers may be for them to
								//   be considered multiples
#define DIVPRECISION	30		// Taken as the precision of a division result

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						============================
						DivExpression::DivExpression
//						============================
(
	Expression* const	pOperand1,
	Expression* const	pOperand2,
	const string&		strPrecision
)
{
	m_pOperand1    = pOperand1;
	m_pOperand2    = pOperand2;
	m_strPrecision = strPrecision;
}

// Destructor
//						=============================
						DivExpression::~DivExpression()
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
ExprResult				DivExpression::Evaluate
//						=======================
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

	// In case either of the operands is a variable, convert these
	// to their contents.
	left.ConvertFromVar( context );
	right.ConvertFromVar( context );

	// Check if both the operands were evaluated as OK.
	if ( left.IsOK() && right.IsOK() )
	{
		// Convert any possible UNSPECIFIED operand.
		left.ConvertFromUnspecified();
		right.ConvertFromUnspecified();

		// Check if both operands have arithmetic types.
		if ( left.IsNumber() && right.IsNumber() )
		{
			// Check if either operand has the type FLOAT.
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
				// Check if the numerical value of the right operand isn't zero.
				if ( (*pNumValRight) != 0 )
				{
					// Calculate the numerical value of the result by dividing
					// the numerical value of the left operand by that of the
					// right operand.
					double dlNumVal = (*pNumValLeft) / (*pNumValRight);

					// Since both operands now have the same type, check the type
					// of the left operand to check if both have type INT. 
					// Furthermore, check if the right operand is a multiple of the
					// left one.
					if ( left.IsInt() && (*pNumValLeft) >= (*pNumValRight)
						&& fmod( (*pNumValLeft), (*pNumValRight) ) < DIVDELTA )
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
						// DIVPRECISION. Then, set the result type to FLOAT.
						result.SetValue( DoubleToStr( dlNumVal, DIVPRECISION ) );
						result.SetType( ExprResult::FLOAT );
					}

					// Set the result status to OK.
					result.SetStatus( ExprResult::OK );
				}
				else
				{
					// Division by zero; set the result status correspongingly.
					result.SetStatus( ExprResult::DIV_BY_ZERO_ERROR );
				}
			}
			else
			{
				// Although the operands were of arithmetic type, no mumerical
				// value could be determined; internal error.
				result.SetStatus( ExprResult::INTERNAL_ERROR );
			}
		}
		else
		{
			// Either or both operands is not a number; set the status of the
			// result to DIV_NO_NUM_ERROR.
			result.SetStatus( ExprResult::DIV_NO_NUM_ERROR );
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
