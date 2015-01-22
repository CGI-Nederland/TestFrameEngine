/*****************************************************************************
 * $Workfile: AssignExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/15/01 1:31p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ASSIGNEXPRESSION_H
#define ASSIGNEXPRESSION_H

#undef BASECLASS
#define BASECLASS Expression

#include <string>

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// class Interpreter
class AssignExpression : public BASECLASS 
{
	// Construction and destruction
private:
	AssignExpression();									// Default constructor
	AssignExpression(const AssignExpression& right);	// Copy constructor

	///// AH /////
	AssignExpression& operator=(AssignExpression&); 
	///// AH /////

	// Other constructors
public:
	virtual ~AssignExpression();						// Destructor
	
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of AssignExpresssion
	//					
	// parameters	: pOperand1		left operand
	//				  pOperand2		right operand
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	AssignExpression( Expression* const pOperand1, Expression* const pOperand2,
						const string& strPrecision );		

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate assign expression.
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
	// function		: ConvertType
	//
	// description	: This function convert a result type to a context type.
	//					
	// parameters	: nResultType	result type
	//
	// returns		: int containig a context type
	///////////////////////////////////////////////////////////////////////////////
	int ConvertType( int nResultType ) const;

	// Member variables
private:
	Expression* m_pOperand1;	// Left operand
	Expression* m_pOperand2;	// Right operand
	string m_strPrecision;		// Precision format from settings
};

#undef BASECLASS
#endif // !ASSIGNEXPRESSION_H