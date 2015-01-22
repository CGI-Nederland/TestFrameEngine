/*****************************************************************************
 * $Workfile: AddExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/19/01 5:05p $
 * $Author: Lw, AH $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ADDEXPRESSION_H
#define ADDEXPRESSION_H

#undef BASECLASS
#define BASECLASS Expression

// Definitions
#define ADDPRECISION	30	// Taken as the precision of a addition result

#include <string>

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// class AddExpression
class AddExpression : public BASECLASS 
{
	// Construction and destruction
private:
	AddExpression();								// Default constructor

	AddExpression( const AddExpression& right );	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of AddExpresssion
	//					
	// parameters	: pOperand1		left operand
	//				  pOperand2		right operand
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	AddExpression( Expression* const pOperand1, Expression* const pOperand2, 
					const string& strPrecision);

	/////////// AH //////////
	AddExpression& operator=(AddExpression&); 
	/////////// AH //////////

	virtual ~AddExpression();				// Destructor

	// Attributes and operations

	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate add expression.
	//					
	// parameters	: Context&					context used for evaluation.
	//
	// returns		: ExprResult				expression result.
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

private:
	// Implementation
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: Add
	//
	// description	: This function adds the values of the two specified ExprResult
	//				  classes, and returns the ExprResult class with the result of
	//				  this operation.
	//					
	// parameters	: left		result class for left operator
	//				  right		result class for right operator
	//
	// returns		: result class for addition
	///////////////////////////////////////////////////////////////////////////////
	ExprResult Add( ExprResult& left, ExprResult& right ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Concatenate
	//
	// description	: This function concatenates the values of the two specified 
	//				  ExprResult classes, and returns the ExprResult class with the
	//				  result of this operation.
	//					
	// parameters	: left		result class for left operator
	//				  right		result class for right operator
	//
	// returns		: result class for concatenation
	///////////////////////////////////////////////////////////////////////////////
	ExprResult Concatenate( ExprResult& left, ExprResult& right ) const;

	// Member variables
private:
	Expression* m_pOperand1;	// Left operand
	Expression* m_pOperand2;	// Right operand
	string m_strPrecision;		// Precision format from settings
};

#undef BASECLASS
#endif // !ADDEXPRESSION_H
