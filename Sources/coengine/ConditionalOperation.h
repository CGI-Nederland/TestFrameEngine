/*****************************************************************************
 * $Workfile: ConditionalOperation.h $
 * $Revision: 1 $
 * $Modtime: 3/14/01 12:51p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CONDITIONALOPERATION_H
#define CONDITIONALOPERATION_H

// Includes.
#include <set>
#include <string>

using namespace std;

// Class definition.
class ConditionalOperation
{
protected:
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION

	///////////////////////////////////////////////////////////////////////////////
	// default constructor of ConditionalOperation
	//
	// The constructor is protected, so ConditionalOperation can only serve as
	// a base-class.
	///////////////////////////////////////////////////////////////////////////////
	ConditionalOperation();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of ConditionalOperation
	///////////////////////////////////////////////////////////////////////////////
	~ConditionalOperation();

public:
	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	IsOperator()
	//
	// description	:	This function determines if a specified string contains one
	//					of this operation's operator values; if it does, true is
	//					returned.
	//
	// parameters	:	strOperator		string to interpret as operator value
	//
	// returns		:	true	string contains a valid operator value
	//					false	string does not contains a valid operator value
	///////////////////////////////////////////////////////////////////////////////
	bool IsOperator( const string& strOperator ) const;

// member variables
protected:
	set<string>	m_sstrOperators;	// Set of operator values.
};

#endif // !CONDITIONALOPERATION_H
