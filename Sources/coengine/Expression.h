/*****************************************************************************
 * $Workfile: Expression.h $
 * $Revision: 3 $
 * $Modtime: 4/21/00 1:15a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef EXPRESSION_H
#define EXPRESSION_H

// Forward declarations
class Context;
class ExprResult;

////////////////////////////////////////////////////////////////////////////////
// class Expression { abstract }
class Expression 
{
	// Construction and destruction
public:
	// Abstract class
	virtual ~Expression() {}				// Destructor
	
	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate the abstract syntax tree
	//					
	// parameters	: Context&				context used for evaluation
	//
	// returns		: ExprResult			expression result
	//				  
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate(Context&) const = 0;	
	
	// Class constants
	enum STATII { OK, UNDEFINED_SYMBOL, ERROR };
};

#endif // !EXPRESSION_H

