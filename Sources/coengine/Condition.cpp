/*****************************************************************************
 * $Workfile: Condition.cpp $
 * $Revision: 1 $
 * $Modtime: 3/14/01 2:14p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning( disable:4786 )

#include "Condition.h"		// Class definition

// Includes
#include <string>
#include <vector>

using namespace std;

#include "ErrorList.h"
#include "LogicalCondition.h"
#include "RelationalCondition.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// constructor
//						====================
						Condition::Condition
//						====================
(
	ErrorList*			pErrorList
)
{
	// Store the pointer to the ErrorList object.
	m_pErrorList = pErrorList;

	// Create a LogicalCondition and a RelationalCondition object.
	m_pLogical	  = new LogicalCondition();
	m_pRelational = new RelationalCondition();

	// Add default values to member variables.
	m_bValue	= false;
	m_bValidity	= false;
	m_strError	= "";
}


// Destructor
//						=====================
						Condition::~Condition()
//						=====================
{
	// Delete the LogicalCondition and the RelationalCondition objects.
	delete m_pLogical;
	delete m_pRelational;

	m_pLogical=0;
	m_pRelational=0;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						===================
bool					Condition::Evaluate
//						===================
(
  const vector<string>&	vstrArguments
)
{
	bool bResult = false;

	// Fill the member vector of condition arguments with the one passed by
	// the function's parameter.
	m_vstrArguments = vstrArguments;

	// Reset the condition's value and error text to their default values.
	m_bValue   = false;
	m_strError = "";

	// Set the validity of the condition initially to true; during parsing,
	// any inconsistency will set this validity to false.
	m_bValidity = true;

	// Interpret the number of arguments; an incorrect number will set the
	// condition's validity to false.
	InterpretArgumentNumber();

	// Determine if the number of arguments are valid.
	if ( m_bValidity )
	{
		// Parse the entire argument vector; its result is the condition's
		// value.
		bool bValue = Parse( 0, m_vstrArguments.size() - 1 );

		// Determine if no errors were found during parsing by checking the
		// condition's validity.
		if ( m_bValidity )
		{
			// Only when the condition is valid, it is useful to store its value.
			m_bValue = bValue;
		}
	}

	// Set the evaluation result to the condition's validity.
	bResult = m_bValidity;

	return bResult;
}


//						===================
bool					Condition::GetValue() const
//						===================
{
	// Return the value of the member containing the condition's value.
	return m_bValue;
}


//						===================
const string&			Condition::GetError() const
//						===================
{
	// Return the value of the member containing the error text.
	return m_strError;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==================================
void					Condition::InterpretArgumentNumber()
//						==================================
{
	// Determine the number of arguments.
	int nArguments = m_vstrArguments.size();

	// A valid condition must contain 3 + 4x (int x >= 0) arguments;
	// i.e., a number which is one of: 3, 7, 11, 15, etc.
	// Divide the number of arguments by 4, and take action upon the
	// value of this operation's remainder.
	switch ( nArguments % 4 )
	{
		case 3:
		{
			// The number of arguments is 3 + 4x; this means the number
			// is valid.
			break;
		}

		case 2:
		{
			// The number of arguments is 2 + 4x; this means that one argument
			// is missing; assume that this is the last argument, and that its
			// value is an empty string, so that it was omitted from the
			// argument list, because no distinction could be made between it
			// and no argument at all. Add an empty string to the end of the
			// argument vector to correct this, and state that the number is
			// (now) valid.
			m_vstrArguments.push_back( "" );
			break;
		}

		default:
		{
			// The number of arguments is invalid to form a correct condition.
			// Set the condition's validity to false, and fill the error text
			// with a message stating this problem.
			m_bValidity = false;
			m_strError  = m_pErrorList->GetText( ErrorList::ID_ERR_COND_NUM_ARG );
			break;
		}
	}
}


//						================
bool					Condition::Parse
//						================
(
	unsigned int		nFirst,
	unsigned int		nLast
)
{
	bool bResult = false;

	// Determine if the first element is greater than the last element,
	// or if the last element is less than 2.
	if ( nFirst > nLast || nLast < 2 )
	{
		// This is an invalid situation; set the condition's validity to false,
		// and fill the error text with an internal error.
		m_bValidity = false;
		m_strError  = m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR );
	}

	// It is only useful to parse the arguments if no errors have been found;
	// to determine this, check the condition's validity.
	if ( m_bValidity )
	{
		// Assumed at this point is that an earlier check has made sure that
		// the number of arguments is 3 + 4x (int x >= 0).

		// Take the last three arguments of the argument vector to parse, and
		// consider these as a relational condition; the middle argument of
		// this group is the relational operator, and the outer two are its
		// operands. Parse this relational operation (stating the element
		// numbers of the operator, left and right operand), and determine its
		// value.
		bool bRelation = ParseRelation( nLast - 1, nLast - 2, nLast );

		// Determine if the relational operation did not reveal errors in the
		// condition.
		if ( m_bValidity )
		{
			// Determine the number of arguments to parse.
			int nArguments = nLast - nFirst + 1;

			// Determine if this number is three.
			if ( nArguments == 3 )
			{
				// There are no other arguments than the three already
				// interpreted as a relational operation. Set the parse result
				// to the value of this operation.
				bResult = bRelation;
			}
			else
			{
				// There are more than three parameters, 3 + 4x (int x >= 1).
				// This means that there is at least one logical combination
				// of relational conditions, with its logical operator in the
				// fourth argument from the end, its right operand the relation
				// operation just interpreted, and its left operand a condition
				// consisting of all the arguments before the logical operator.
				// Parse this (sub)condition and store its value as the left
				// operator value.
				bool bLeft = Parse( nFirst, nLast - 4 );

				// Determine if the parsing of the subcondition yielded no
				// errors.
				if ( m_bValidity )
				{
					// Get the argument position of the logical operator.
					int nLogicOperator = nLast - 3;

					// Parse the logical combination, stating the position of
					// the logical operator, and the values of the left operand
					// (subcondition) and the right operand (relational
					// operation); determine its value.
					bool bCombination = ParseCombination( nLogicOperator, bLeft, bRelation );

					// Determine if the logical operation found no errors.
					if ( m_bValidity )
					{
						// Set the parse result to the value of the logical
						// combination operation.
						bResult = bCombination;
					}
				}
			}
		}
	}

	return bResult;
}


//						========================
bool					Condition::ParseRelation
//						========================
(
	unsigned int		nOperator,
	unsigned int		nLeft,
	unsigned int		nRight
)
{
	bool bResult = false;	

	// Get the values of the relational operator as specified by its
	// argument position.
	string strOperator = m_vstrArguments[nOperator];

	// Set the found operator value in the RelationalCondition object, and
	// determine if this operator is really a relational operator.
	if ( m_pRelational->SetOperator( strOperator ) )
	{
		// Get the values of the left and right operands, as specified by
		// their argument positions.
		string strLeft  = m_vstrArguments[nLeft];
		string strRight	= m_vstrArguments[nRight];
		
		// Determine the value of the relational operation, and return this.
		bResult = m_pRelational->Evaluate( strLeft, strRight );
	}
	else
	{
		// Set the condition's validity to false, and fill the error with the
		// message that an invalid relational operator is found.
		m_bValidity = false;
		m_strError  = m_pErrorList->GetText( ErrorList::ID_ERR_COND_INVALID_OP, strOperator );
	}

	return bResult;
}


//						===========================
bool					Condition::ParseCombination
//						===========================
(
	unsigned int		nOperator,
	bool				bLeft,
	bool				bRight
)
{
	bool bResult = false;

	// Get the value of the logical operator as specified by its argument
	// position.
	string strOperator = m_vstrArguments[nOperator];

	// Set the found operator value in the LogicalCondition object, and
	// determine if this operator is really a logical operator.
	if ( m_pLogical->SetOperator( strOperator ) )
	{
		// Determine the value of the logical operation, and return this.
		bResult = m_pLogical->Evaluate( bLeft, bRight );
	}
	else
	{
		// Set the condition's validity to false, and fill the error with the
		// message that an invalid logical operator is found.
		m_bValidity = false;
		m_strError  = m_pErrorList->GetText( ErrorList::ID_ERR_COND_INVALID_OP, strOperator );
	}

	return bResult;
}
