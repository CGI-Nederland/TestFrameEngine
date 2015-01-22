/*****************************************************************************
 * $Workfile: NumExpression.h $
 * $Revision: 3 $
 * $Modtime: 1/11/01 6:43p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NUMEXPRESSION_H
#define NUMEXPRESSION_H

#undef  BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class ExprResult;
class Context;

////////////////////////////////////////////////////////////////////////////////
// class NumExpression
class NumExpression : public BASECLASS 
{
private:
	NumExpression();								// Default constructor
			
    NumExpression(const NumExpression& right);		// Copy constructor

	// Other constructors	
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of NumExpresssion
	//					
	// parameters	: strValue		string containing numerical value
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	NumExpression( const string& strValue, const string& strPrecision );

	// Destructor
	virtual ~NumExpression();	

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: Evaluate number expression.
	//					
	// parameters	: context		context used for evaluation
	//
	// returns		: ExprResult object
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

	// Member variables
private:
	string m_strValue;		// character string interpreted as number
	string m_strPrecision;	// precision format from settings
};

#undef BASECLASS
#endif //!NUMEXPRESSION
