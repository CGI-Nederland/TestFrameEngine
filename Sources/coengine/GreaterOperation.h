/*****************************************************************************
 * $Workfile: GreaterOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:41a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef GREATEROPERATION_H
#define GREATEROPERATION_H

// Includes.
#include <string>

using namespace std;

#include "RelationalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS RelationalOperation

// Class definition.
// Derived from RelationalOperation.
class GreaterOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of GreaterOperation
	///////////////////////////////////////////////////////////////////////////////
	GreaterOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of GreaterOperation
	///////////////////////////////////////////////////////////////////////////////
	~GreaterOperation();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a 'greater than'-operation. If both
	//					values can be interpreted as numbers, true is returned if
	//					the numerical value of the left operand is greater than that
	//					of the right one; if they can only be interpreted as
	//					strings, true is returned if the string value of the left
	//					operand comes alphabetically after that of the right one.
	//
	// parameters	:	strLeft		value of left operand
	//					strRight	value of right operand
	//
	// returns		:	true	'greater than' is true
	//					false	'greater than' is false
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( const string& strLeft, const string& strRight );
};

#undef BASECLASS
#endif // !GREATEROPERATION_H
