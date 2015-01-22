/*****************************************************************************
 * $Workfile: LogicalOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:38a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGICALOPERATION_H
#define LOGICALOPERATION_H

// Includes.
#include "ConditionalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS ConditionalOperation

// Class definition.
// Abstract class, derived from ConditionalOperation.
class LogicalOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of LogicalOperation
	///////////////////////////////////////////////////////////////////////////////
	LogicalOperation() {};

	///////////////////////////////////////////////////////////////////////////////
	// destructor of LogicalOperation
	///////////////////////////////////////////////////////////////////////////////
	virtual ~LogicalOperation() {};

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a logical combination of the left
	//					and right operand, and returns the result of this
	//					operation.
	//					This function is pure virtual, which makes it necessary
	//					for classes derived from this abstract class to implement
	//					the function Evaluate().
	//
	// parameters	:	bLeft	boolean value of left operand
	//					bRight	boolean value of right operand
	//
	// returns		:	true	logical combination is true
	//					false	logical combination is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Evaluate( bool bLeft, bool bRight ) = 0;
};

#undef BASECLASS
#endif // !LOGICALOPERATION_H
