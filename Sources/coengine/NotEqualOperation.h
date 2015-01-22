/*****************************************************************************
 * $Workfile: NotEqualOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:42a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NOTEQUALOPERATION_H
#define NOTEQUALOPERATION_H

// Includes.
#include <string>

using namespace std;

#include "RelationalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS RelationalOperation

// Class definition.
// Derived from RelationalOperation.
class NotEqualOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of EqualOperation
	///////////////////////////////////////////////////////////////////////////////
	NotEqualOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of EqualOperation
	///////////////////////////////////////////////////////////////////////////////
	~NotEqualOperation();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a 'not equal to'-operation. If both
	//					values can be interpreted as numbers, true is returned if
	//					the numerical value of the left operand is different from
	//					that of the right one; if they can only be interpreted as
	//					strings, true is returned if one or more characters do not
	//					match.
	//
	// parameters	:	strLeft		value of left operand
	//					strRight	value of right operand
	//
	// returns		:	true	'not equal to' is true
	//					false	'not equal to' is false
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( const string& strLeft, const string& strRight );
};

#undef BASECLASS
#endif // !NOTEQUALOPERATION_H
