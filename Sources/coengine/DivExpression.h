/*****************************************************************************
 * $Workfile: DivExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/15/01 12:01p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef DIVEXPRESSION_H
#define DIVEXPRESSION_H

#undef BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

class DivExpression : public BASECLASS 
{
	// Construction and destruction
private:
	DivExpression();							// Default constructor
	DivExpression& operator=(DivExpression&);

	DivExpression(const DivExpression& right);	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of DivExpresssion
	//
	// parameters	: pOperand1		left operand
	//				  pOperand2		right operand
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	DivExpression( Expression* const pOperand1, Expression* const pOperand2,
					const string& strPrecision );

	virtual ~DivExpression();					// Destructor

	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate divide expression.
	//					
	// parameters	: Context&					context used for evaluation.
	//
	// returns		: ExprResult				expression result.
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

	// Member variables
private:
	Expression* m_pOperand1;	// Left operand
	Expression* m_pOperand2;	// Right operand
	string m_strPrecision;		// Precision format from settings
};

#undef BASECLASS
#endif //!DIVEXPRESSION_H
