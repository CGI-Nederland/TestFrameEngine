/*****************************************************************************
 * $Workfile: LogicalCondition.h $
 * $Revision: 1 $
 * $Modtime: 3/15/01 6:26p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGICALCONDITION_H
#define LOGICALCONDITION_H

// Includes.
#include <string>
#include <vector>

using namespace std;

// Forward declarations.
class LogicalOperation;

// Class definition.
class LogicalCondition
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of LogicalCondition
	///////////////////////////////////////////////////////////////////////////////
	LogicalCondition();

	LogicalCondition(LogicalCondition&);
	LogicalCondition& operator=(LogicalCondition&);
	///////////////////////////////////////////////////////////////////////////////
	// destructor of LogicalCondition
	///////////////////////////////////////////////////////////////////////////////
	~LogicalCondition();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetOperator()
	//
	// description	:	This function interprets the specified string as the value
	//					of a logical operator. If it is such an operator, true is
	//					returned, and the current operation object is set to the
	//					one corresponding with the specified operator; otherwise,
	//					false is returned, and no current operation object is
	//					available.
	//
	// parameters	:	strOperator		string to interpret as logical operator
	//
	// returns		:	true	string is a valid logical operator
	//					false	string is not a valid logical operator
	///////////////////////////////////////////////////////////////////////////////
	bool SetOperator( const string& strOperator );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a logical combination of the left
	//					and right operand, and returns the result of this
	//					operation. The type of logical combination depends on the
	//					current operation object; should no such current object be
	//					available, a default false is returned.
	//
	// parameters	:	bLeft	boolean value of left operand
	//					bRight	boolean value of right operand
	//
	// returns		:	true	logical combination is true
	//					false	logical combination is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( bool bLeft, bool bRight ) const;

// member variables
private:
	vector<LogicalOperation*> m_vpOperations;		// Vector containing pointers to
													// the different types of logical
													// operations objects.
	LogicalOperation*		  m_pCurrentOperation;	// Pointer to the current logical
													// operation object; this is one
													// of m_vpOperations.
};

#endif // !LOGICALCONDITION_H
