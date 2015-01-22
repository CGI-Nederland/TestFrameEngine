/*****************************************************************************
 * $Workfile: KeepCommand.h $
 * $Revision: 2 $
 * $Modtime: 12/14/00 3:32p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef KEEPCOMMAND_H
#define KEEPCOMMAND_H

#include "EngineSetting.h"			// EngineSetting definition

#include "ArgumentCommand.h"		// Base class
#include "Parser.h"

#undef BASECLASS
#define BASECLASS	ArgumentCommand

////////////////////////////////////////////////////////////////////////////////
// class KeepCommand
class KeepCommand : public BASECLASS
{
	// Construction and destruction
private:
	KeepCommand() {};	// default constructor made private

public:
	explicit KeepCommand( Parser* pTheParser );	// constructor

	~KeepCommand() {};					// Destructor


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
	// returns		: TRUE		evaluation successfull
	//				: FALSE		evaluation failed
	///////////////////////////////////////////////////////////////////////////////
	bool EvaluateCommand();

	///////////////////////////////////////////////////////////////////////////////
	// function		: InterpretParameter
	//
	// description	: This function interprets the command.
	//				  It checks for parenthesis and extracts
	//				  the command argument
	//
	// parameters	: none
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void InterpretParameter();

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

	string	m_strParameter;			// string containing the command parameter
	Parser* m_pTheParser;			// pointer to the Parser
};

#undef BASECLASS
#endif // KEEPCOMMAND_H
