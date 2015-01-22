/*****************************************************************************
 * $Workfile: AndOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/16/01 10:41a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ANDOPERATION_H
#define ANDOPERATION_H

// Includes.
#include "LogicalOperation.h"	// Base-class definition.

// Define base-class.
#undef BASECLASS
#define BASECLASS LogicalOperation

// Class definition.
// Derived from LogicalOperation.
class AndOperation : public BASECLASS
{
public:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of AndOperation
	///////////////////////////////////////////////////////////////////////////////
	AndOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of AndOperation
	///////////////////////////////////////////////////////////////////////////////
	~AndOperation();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a logical 'and'-operation. True is
	//					returned only if both left and right operand contain the
	//					value true; otherwise, false is returned.
	//
	// parameters	:	bLeft	boolean value of left operand
	//					bRight	boolean value of right operand
	//
	// returns		:	true	logical 'and' is true
	//					false	logical 'and' is false
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( bool bLeft, bool bRight );
};

#undef BASECLASS
#endif // !ANDOPERATION_H
