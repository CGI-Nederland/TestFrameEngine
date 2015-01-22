/*****************************************************************************
 * $Workfile: LessEqualOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:41a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LESSEQUALOPERATION_H
#define LESSEQUALOPERATION_H

// Includes.
#include <string>

using namespace std;

#include "RelationalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS RelationalOperation

// Class definition.
// Derived from RelationalOperation.
class LessEqualOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of LessEqualOperation
	///////////////////////////////////////////////////////////////////////////////
	LessEqualOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of LessEqualOperation
	///////////////////////////////////////////////////////////////////////////////
	~LessEqualOperation();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a 'less than or equal to'-operation.
	//					If both values can be interpreted as numbers, true is
	//					returned if	the numerical value of the left operand is less
	//					than or equal to that of the right one; if they can only be
	//					interpreted as strings, true is returned if the string
	//					value of the left operand comes alphabetically before or is
	//					identical to that of the right one.
	//
	// parameters	:	strLeft		value of left operand
	//					strRight	value of right operand
	//
	// returns		:	true	'less than or equal to' is true
	//					false	'less than or equal to' is false
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( const string& strLeft, const string& strRight );
};

#undef BASECLASS
#endif // !LESSEQUALOPERATION_H
