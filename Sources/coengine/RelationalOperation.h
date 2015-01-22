/*****************************************************************************
 * $Workfile: RelationalOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:38a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef RELATIONALOPERATION_H
#define RELATIONALOPERATION_H

// Includes.
#include "ConditionalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS ConditionalOperation

// Class definition.
// Abstract class, derived from ConditionalOperation.
class RelationalOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of RelationalOperation
	///////////////////////////////////////////////////////////////////////////////
	RelationalOperation() {};

	///////////////////////////////////////////////////////////////////////////////
	// destructor of RelationalOperation
	///////////////////////////////////////////////////////////////////////////////
	virtual ~RelationalOperation() {};

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a relation between the left and
	//					right operand, and returns the result of this operation.
	//					This function is pure virtual, which makes it necessary
	//					for classes derived from this abstract class to implement
	//					the function Evaluate().
	//
	// parameters	:	strLeft		value of left operand
	//					strRight	value of right operand
	//
	// returns		:	true	relation is true
	//					false	relation is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Evaluate( const string& strLeft, const string& strRight ) = 0;
};

#undef BASECLASS
#endif // !RELATIONALOPERATION_H
