/*****************************************************************************
 * $Workfile: StrExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/15/01 2:18p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef StrExpression_H
#define StrExpression_H

#undef  BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

////////////////////////////////////////////////////////////////////////////////
// class StrExpression
class StrExpression : public BASECLASS
{
private:
	StrExpression();								// Default constructor
			
    StrExpression(const StrExpression& right);		// Copy constructor

	// Other constructors	
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of StrExpresssion
	//					
	// parameters	: strValue		string containing string constant
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	StrExpression( const string& strValue, const string& strPrecision );

	virtual ~StrExpression();						// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate string expression.
	//					
	// parameters	: Context&					context used for evaluation.
	//
	// returns		: ExprResult				expression result.
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

	// Member variables
private:
	string m_strValue;		// character string interpreted as number
	string m_strPrecision;	// precision format from settings
};

#undef BASECLASS
#endif //!StrExpression
