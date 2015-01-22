/*****************************************************************************
 * $Workfile: TestLine.h $
 * $Revision: 2 $
 * $Modtime: 19-11-99 12:59 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TESTLINE_H
#define TESTLINE_H

#include <string>
#include <vector>

using namespace std;

class TestLine
{
public:
	TestLine() {}	// Default constuctor

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestLine()
	// description	: This function returns the test line.
	//
	// parameters	: <none>
	//
	// returns		: string containing the entire test line
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTestLine() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordFunction()
	// description	: This function returns the name of action word function.
	//
	// parameters	: <none>
	//
	// returns		: name of the action word function
	///////////////////////////////////////////////////////////////////////////////
	const string& GetActionWordFunction() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSlaveName()
	// description	: This function returns the slave name.
	//
	// parameters	: <none>
	//
	// returns		: name of the slave
	///////////////////////////////////////////////////////////////////////////////
	const string& GetSlaveName() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgument()
	// description	: This function returns the n-th argument of the action word.
	//
	// parameters	: n		index of arguments
	//
	// returns		: n-th argument of action word
	///////////////////////////////////////////////////////////////////////////////
	string GetArgument(int n);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordValidity()
	// description	: This function returns whether or not the action word is valid.
	//
	// parameters	: <none>
	//
	// returns		: bool expressing validity of the action word
	///////////////////////////////////////////////////////////////////////////////
	bool GetActionWordValidity() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetMasterSlaveValidity()
	// description	: This function returns whether or not the Master/Slave part
	//					is valid.
	//
	// parameters	: <none>
	//
	// returns		: bool expressing validity of the Master/Slave part
	///////////////////////////////////////////////////////////////////////////////
	bool GetMasterSlaveValidity() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetMasterSlaveValidity()
	// description	: This function returns whether or not all arguments are valid.
	//
	// parameters	: <none>
	//
	// returns		: bool expressing validity of the arguments
	///////////////////////////////////////////////////////////////////////////////
	bool GetArgumentsValidity() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionType()
	// description	: This function returns action word type.
	//
	// parameters	: <none>
	//
	// returns		: action word type
	///////////////////////////////////////////////////////////////////////////////
	int GetActionType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgumentErrors()
	// description	: This function returns the errors Interpreter found in the
	//					arguments.
	//
	// parameters	: <none>
	//
	// returns		: vector containing strings with error messages
	///////////////////////////////////////////////////////////////////////////////
	const vector<string>& GetArgumentErrors() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetInterpretResult()
	// description	: This function returns the result of the interpreter.
	//
	// parameters	: <none>
	//
	// returns		: result of interpreter
	///////////////////////////////////////////////////////////////////////////////	
	bool GetInterpretResult() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: ArgumentCount()
	// description	: This function returns the number of arguments of the ation
	//					word.
	//
	// parameters	: <none>
	//
	// returns		: number of arguments
	///////////////////////////////////////////////////////////////////////////////
	int	ArgumentCount() const;

protected:
	// member variables
	string			m_strTestLine;			// complete test line
	string			m_strAction;			// name of the action word function
	string			m_strSlaveName;			// name of the slave
	vector<string>	m_vstrArguments;		// vector of arguments of the action word
	bool			m_bActionValid;			// valid action word
	bool			m_bMasterSlaveValid;	// valid slave name
	bool			m_bArgumentsValid;		// valid arguments
	vector<string>	m_vstrArgumentErrors;	// vector of errors in arguments
	int				m_nActionType;			// action type
	bool			m_bInterpretResult;		// states the result of the interpreter
};

#endif	// !TESTLINE_H