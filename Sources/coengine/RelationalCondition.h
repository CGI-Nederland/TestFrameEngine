/*****************************************************************************
 * $Workfile: RelationalCondition.h $
 * $Revision: 1 $
 * $Modtime: 3/15/01 6:24p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef RELATIONALCONDITION_H
#define RELATIONALCONDITION_H

// Includes.
#include <string>
#include <vector>

using namespace std;

// Forward declarations.
class RelationalOperation;

// Class definition.
class RelationalCondition
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of RelationalCondition
	///////////////////////////////////////////////////////////////////////////////
	RelationalCondition();

	RelationalCondition(RelationalCondition&);
	RelationalCondition& operator=(RelationalCondition&);

	///////////////////////////////////////////////////////////////////////////////
	// destructor of RelationalCondition
	///////////////////////////////////////////////////////////////////////////////
	~RelationalCondition();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	SetOperator()
	//
	// description	:	This function interprets the specified string as the value
	//					of a relational operator. If it is such an operator, true
	//					is returned, and the current operation object is set to the
	//					one corresponding with the specified operator; otherwise,
	//					false is returned, and no current operation object is
	//					available.
	//
	// parameters	:	strOperator		string to interpret as relational operator
	//
	// returns		:	true	string is a valid relational operator
	//					false	string is not a valid relational operator
	///////////////////////////////////////////////////////////////////////////////
	bool SetOperator( const string& strOperator );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates a relation between the left and
	//					right operand, and returns the result of this operation.
	//					The type of relational operation depends on the	current
	//					operation object; should no such current object be
	//					available, a default false is returned.
	//
	// parameters	:	strLeft		value of left operand
	//					strRight	value of right operand
	//
	// returns		:	true	relation is true
	//					false	relation is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( const string& strLeft, const string& strRight ) const;

// member variables
private:
	vector<RelationalOperation*> m_vpOperations;		// Vector containing pointers to
														// the different types of relational
														// operations objects.
	RelationalOperation*		 m_pCurrentOperation;	// Pointer to the current relational
														// operation object; this is one of
														// m_vpOperations.
};

#endif // !RELATIONALCONDITION_H
