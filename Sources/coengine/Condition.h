/*****************************************************************************
 * $Workfile: Condition.h $
 * $Revision: 1 $
 * $Modtime: 3/14/01 2:11p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CONDITION_H
#define CONDITION_H

// Includes.
#include <string>
#include <vector>

using namespace std;

// Forward declarations.
class ErrorList;
class LogicalCondition;
class RelationalCondition;

// Class definition.
class Condition
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
private:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of Condition
	///////////////////////////////////////////////////////////////////////////////
	Condition(){};
	Condition& operator=(Condition&);

public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of Condition
	//
	// parameters	:	pErrorList			pointer to the ErrorList object which
	//										contains the texts of the error 
	//										messages
	///////////////////////////////////////////////////////////////////////////////
	explicit Condition( ErrorList* pErrorList );

	///////////////////////////////////////////////////////////////////////////////
	// destructor of Condition
	///////////////////////////////////////////////////////////////////////////////
	~Condition();

	////////////////////////////////////////////////////////////////////////////
	// PUBLIC INTERFACE

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Evaluate()
	//
	// description	:	This function evaluates the condition specified by the
	//					arguments in the parameter. This function returns true
	//					if the condition is valid.
	//
	// parameters	:	vstrArguments		vector containing the argument values
	//										which make up the condition
	//
	// returns		:	true	condition is valid
	//					false	condition is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool Evaluate( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetValue()
	//
	// description	:	This function returns of the value of the last evaluated 
	//					condition. Note that the returned value only makes sense
	//					if the evaluation was successful; if it was not, a default
	//					false is returned.
	//
	// parameters	:	None.
	//
	// returns		:	true	condition is true
	//					false	condition is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	bool GetValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetError()
	//
	// description	:	This function returns the error message found during the
	//					last condition evaluation. Note that the returned value
	//					only makes sense if the evaluation was unsuccessful; if it
	//					was succesful, a default empty string is returned.
	//
	// parameters	:	None.
	//
	// returns		:	string containing the error message
	///////////////////////////////////////////////////////////////////////////////
	const string& GetError() const;

private:
	////////////////////////////////////////////////////////////////////////////
	// IMPLEMENTATION

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretArgumentNumber()
	//
	// description	:	This function interprets the number of arguments of the
	//					condition. This number must be 3 + 4x (int x >= 0) for the
	//					condition to be valid; if it is 2 + 4x (int x >= 0), an
	//					empty string is added to the argument vector to make it
	//					valid; any other number will set the validity to false.
	//
	// parameters	:	None.
	//
	// returns		:	void
	///////////////////////////////////////////////////////////////////////////////
	void InterpretArgumentNumber();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Parse()
	//
	// description	:	This function parses a (sub)condition consisting of the
	//					arguments from nFirst to nLast.
	//
	// parameters	:	nFirst		first element of the argument list
	//					nLast		last element of the argument list
	//
	// returns		:	string containig the error message
	///////////////////////////////////////////////////////////////////////////////
	bool Parse( unsigned int nFirst, unsigned int nLast );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ParseRelation()
	//
	// description	:	This function parses a relational operation. The first
	//					parameter specifies the argument position of the relational
	//					operator; the second and third those of the left and right
	//					operand of the relation, respectively. If the relation is
	//					invalid, the validity of the condition is set to false, and
	//					a default false is returned
	//
	// parameters	:	nOperator	position of relational operator
	//					nLeft		position of left operand
	//					nRight		position of right operand
	//
	// returns		:	true	relation is true
	//					false	relation is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	bool ParseRelation( unsigned int nOperator, unsigned int nLeft, unsigned int nRight );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ParseCombination()
	//
	// description	:	This function parses a logical combination operation; i.e.,
	//					an AND- or an OR-operation. The first parameter specifies
	//					the argument position of the logical operator; the second
	//					and third contain the values (true or false) of the left
	//					and right operand, respectively. If the combination is
	//					invalid, the validity of the condition is set to false, and
	//					a default false is returned
	//
	// parameters	:	nOperator	position of logical operator
	//					bLeft		value of left operand
	//					bRight		value of right operand
	//
	// returns		:	true	relation is true
	//					false	relation is false (or invalid)
	///////////////////////////////////////////////////////////////////////////////
	bool ParseCombination( unsigned int nOperator, bool bLeft, bool bRight );

// member variables
private:
	ErrorList*				m_pErrorList;		// Pointer to the ErrorList object.
	LogicalCondition*		m_pLogical;			// Pointer to the LogicalCondition
												// object.
	RelationalCondition*	m_pRelational;		// Pointer to the RelationalCondition
												// object.
	vector<string>			m_vstrArguments;	// Vector of arguments which make
												// up the condition.
	bool					m_bValue;			// Value of the condition.
	bool					m_bValidity;		// Validity of the condition.
	string					m_strError;			// Error message for invalid condition.
};

#endif // !CONDITION_H
