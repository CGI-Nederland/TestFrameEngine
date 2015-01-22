/*****************************************************************************
 * $Workfile: ExpressionCommand.h $
 * $Revision: 1 $
 * $Modtime: 18/04/13 3:35p $
 * $Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef REFERCOMMAND_H
#define REFERCOMMAND_H

#include "EngineSetting.h"			// EngineSetting definition
#include "Parser.h"					// Parser definition
#include "ArgumentCommand.h"		// Base class

#undef BASECLASS
#define BASECLASS	ArgumentCommand

////////////////////////////////////////////////////////////////////////////////
// class ExpressionCommand
class ReferCommand  : public BASECLASS
{
	// Construction and destruction

public:
	explicit ReferCommand(Parser* pTheParser);		// Constructor

	~ReferCommand() {};					// Destructor

	// Implementation

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialize
	//
	// description	: This function initializes the AnythingCommand Object
	//				  by reading the EngineSetting from the ini file.
	//					
	// parameters	: EngineSetting*	pointer to the Settings Object to find the prefix
	//				  
	//
	// returns		: TRUE			initialization successful
	//				  FALSE			initialization failed
	///////////////////////////////////////////////////////////////////////////////
	bool Initialize(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// function		: EvaluateCommand
	//
	// description	: This function evaluates the command by filling the argument
	//				  value part of the command string
	//
	// parameters	: none
	//
	// returns		: TRUE		evaluation successful
	//				  FALSE		evaluation failed
	///////////////////////////////////////////////////////////////////////////////
	bool EvaluateCommand();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameterString
	//
	// description	: This function retrieves the parameter string for the Interpreter
	//
	// parameters	: none
	//
	// returns		: m_strParameter
	///////////////////////////////////////////////////////////////////////////////
	string GetParameterString();

private:

	///////////////////////////////////////////////////////////////////////////////
	// function		: InterpretParameter
	//
	// description	: This function interprets the command parameter.
	//				  It checks for parenthesis and extracts
	//				  the command argument
	//
	// parameters	: none
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void InterpretParameter();

	string	m_strParameter;			// string containing the command parameter
	Parser*	m_pTheParser;			// connection to the parser
};
#undef BASECLASS
#endif // REFERCOMMAND_H