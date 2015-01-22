/*****************************************************************************
 * $Workfile: SubExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/15/01 11:16a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef SUBEXPRESSION_H
#define SUBEXPRESSION_H

#undef  BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

////////////////////////////////////////////////////////////////////////////////
// class SubExpression
class SubExpression : public BASECLASS 
{
	// Construction and destruction
private:
	SubExpression(){};								// Default constructor
	
	SubExpression(SubExpression&);
	SubExpression& operator=(SubExpression&);

	SubExpression( const SubExpression& right );	// Copy constructor

	// Other constructor
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of SubExpresssion
	//					
	// parameters	: pOperand1		left operand
	//				  pOperand2		right operand
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	SubExpression( Expression* const pOperand1, Expression* const pOperand2,
					const string& strPrecision );

	virtual ~SubExpression();					// Destructor

	// Attributes and operation
	///////////////////////////////////////////////////////////////////////////////
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate subtract expression.
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
#endif // !SUBEXPRESSION
