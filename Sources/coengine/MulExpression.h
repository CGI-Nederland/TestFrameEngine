/*****************************************************************************
 * $Workfile: MulExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/15/01 10:16a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MULEXPRESSION_H
#define MULEXPRESSION_H

#undef  BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class ExprResult;
class Context;

////////////////////////////////////////////////////////////////////////////////
// class MulExpression
class MulExpression : public BASECLASS
{
	// Construction and destruction
private:
	MulExpression();							// Default constructor

	MulExpression& operator=(MulExpression&);

	MulExpression(const MulExpression& right);	// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of MulExpresssion
	//
	// parameters	: pOperand1		left operand
	//				  pOperand2		right operand
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	MulExpression(Expression* const pOperand1, Expression* const pOperand2,
					const string& strPrecision);

	virtual ~MulExpression();					// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate multiply expression.
	//					
	// parameters	: Context&					context used for evaluation.
	//
	// returns		: ExprResult				expression result.
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

	// Member variables
private:
	Expression* m_pOperand1;		// Left operand
	Expression* m_pOperand2;		// Right operand
	string		m_strPrecision;		// Precision format
};

#undef BASECLASS
#endif //!MULEXPRESSION