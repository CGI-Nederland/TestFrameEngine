/*****************************************************************************
 * $Workfile: VarExpression.h $
 * $Revision: 4 $
 * $Modtime: 1/12/01 5:48p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef VAREXPRESSION_H
#define VAREXPRESSION_H

#undef  BASECLASS
#define BASECLASS Expression

#include <string>

using namespace std;

#include "Expression.h"

// Forward declarations
class Context;
class ExprResult;

////////////////////////////////////////////////////////////////////////////////
// class NumExpression
class VarExpression : public BASECLASS 
{
	// Construction and destruction
private:
	VarExpression();								// Default constructor

    VarExpression(const VarExpression& right);		// Copy constructor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// Contructor of VarExpresssion
	//					
	// parameters	: strValue		string containing variable name
	//				  strPrecision	precision format from settings
	///////////////////////////////////////////////////////////////////////////////
	VarExpression( const string& strValue, const string& strPrecision );

	virtual ~VarExpression();						// Destructor

	// Attributes and operations
	///////////////////////////////////////////////////////////////////////////////
	// function		: Evaluate
	//
	// description	: This function evaluates a variable expression.
	//					
	// parameters	: context		context used for evaluation.
	//
	// returns		: ExprResult object
	///////////////////////////////////////////////////////////////////////////////
	virtual ExprResult Evaluate( Context& context ) const;

	// Member variables
private:
	string m_strValue;		// string interpreted as variable name
	string m_strPrecision;	// precision format from settings
};

#undef BASECLASS
#endif //!VAREXPRESSION_H
