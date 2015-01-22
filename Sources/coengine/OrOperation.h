/*****************************************************************************
 * $Workfile: OrOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:43a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef OROPERATION_H
#define OROPERATION_H

// Includes.
#include "LogicalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS LogicalOperation

// Class definition.
// Derived from LogicalOperation.
class OrOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of OrOperation
	///////////////////////////////////////////////////////////////////////////////
	OrOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of OrOperation
	///////////////////////////////////////////////////////////////////////////////
	~OrOperation();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a logical 'or'-operation. False is
	//					returned only if both left and right operand contain the
	//					value false; otherwise, true is returned.
	//
	// parameters	:	bLeft	boolean value of left operand
	//					bRight	boolean value of right operand
	//
	// returns		:	true	logical 'or' is true
	//					false	logical 'or' is false
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( bool bLeft, bool bRight );
};

#undef BASECLASS
#endif // !OROPERATION_H
