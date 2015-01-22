/*****************************************************************************
 * $Workfile: ArgumentCommand.h $
 * $Revision: 2 $
 * $Modtime: 12/13/00 5:11p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ARGUMENTCOMMAND_H
#define ARGUMENTCOMMAND_H

#include <string>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////
// class ArgumentCommand (abstract class)
//
// Class ArgumentCommand is the base class for the command classes: AnythingCommand,
// EmptyCommand, NotEmptyCommand, DateCommand, TimeCommand, ExpressionCommand,
// KeepCommand, SnapCommand and SpacesCommand.
// The Command classes have a prefix (&prefix) and can have (1 or more) parameters,
// with or without parentheses.
// The parameters can have a transformation before logging.
// The class might call the parser for evaluation of the parameters and might need
// the interpreter.
// The following table shows the derived classes and their (default) settings.
//
//////////////////////////////////////////////////////////////////////////////////
//
//	derived class		prefix			transform.	param.	eval.	interpr.	parenth.
//	-------------------------------------------------------------------------------------
//	AnythingCommand		&Anything					0							
//												
//	EmptyCommand		&Empty			x			0				
//
//	NotEmptyCommand		&NotEmpty					0				
//
//	DateCommand			&Date			x			1-4		x		x			x
//
//  Time Command		&Time			x			1-		x		x			x
//
//	ExpressionCommand	&Expression		x			1		x		x			
//
//	KeepCommand			&Keep						1				x			x
//
//	SnapCommand			&Snap						0-1				x			x
//
//	SpacesCommand		&Spaces			x			1		x					x
//
//////////////////////////////////////////////////////////////////////////////////
class ArgumentCommand 
{
	// Construction and destruction
	
public:
	ArgumentCommand()	{}					// Default constructor
	virtual ~ArgumentCommand() {}			// Destructor

protected:
	// Implementation

public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsCommand
	//
	// description	: This function checks if strArgument is a command of the overloaded
	//				  command type.
	//					
	// parameters	: strArgument	the string which the IsCommand has to check
	//
	// returns		: TRUE			strArgument is a Command of the derived class type
	//				  FALSE			strArgument is not a Command
	///////////////////////////////////////////////////////////////////////////////
	bool IsCommand(const string& strArgument);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetPrefix
	//
	// description	: This function returns the prefix of the strArgument
	//					
	// parameters	: none
	//
	// returns		: string		m_strPrefix: the prefix, as retrieved in Initialize
	//				  
	///////////////////////////////////////////////////////////////////////////////
	string GetPrefix();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetPrefixLength
	//
	// description	: This function returns the length (m_nPrefixLength) of the prefix
	//					
	// parameters	: none
	//
	// returns		: int		the length of the prefix, as retrieved in Initialize
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetPrefixLength();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret
	//
	// description	: This function interprets the Argument string, uses
	//			      DetermineCommand to check if it a command;
	//					
	// parameters	: strArgument	command argument string to be interpreted
	//
	// returns		: TRUE			interpretation successful
	//				  FALSE			interpretation failed
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret(const string& strArgument);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgumentValue
	//
	// description	: This function retrieves the evaluated argument value string
	//
	// parameters	: none
	//
	// returns		: m_strArgumentValue
	///////////////////////////////////////////////////////////////////////////////
	string GetArgumentValue();

protected:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialize
	//
	// description	: This function (which must be overloaded) initializes the
	//				  command object by reading the EngineSetting from the ini file.
	//				  It fills m_strPrefix, m_bHasParentheses, m_bHasParameter,
	//				  m_bNeedsTransformation, m_bNeedsEvaluation, m_bNeedsInterpretation
	//					
	// parameters	: depending on the command type EngineSetting* and/or Parser*
	//				  
	//
	// returns		: TRUE			initialization successful
	//				  FALSE			initialization failed
	///////////////////////////////////////////////////////////////////////////////
	virtual bool Initialize() {return true;}

	///////////////////////////////////////////////////////////////////////////////
	// function		: EvaluateCommand
	//
	// description	: This function evaluates the parameters of the command
	//
	// parameters	: none
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	virtual bool EvaluateCommand() {return true;}

	///////////////////////////////////////////////////////////////////////////////
	// function		: HasParentheses
	//
	// description	: This function checks if a specified text has opening and
	//				  closing parentheses. As (opening) parentheses are regarded
	//				  the characters (, {, [ and <.
	//					
	// parameters	: strText		string to check for parentheses
	//
	// returns		: TRUE			text has parentheses
	//				  FALSE			text has no parentheses
	///////////////////////////////////////////////////////////////////////////////
	bool HasParentheses(const string& strText);

	///////////////////////////////////////////////////////////////////////////////
	// function		: RemoveParentheses
	//
	// description	: This function removes the outer opening and closing
	//				  parentheses of a specified text.
	//
	// parameters	: strText		string to remove parentheses from
	//
	// returns		: string containing the value of strText without parentheses
	///////////////////////////////////////////////////////////////////////////////
	string RemoveParentheses(const string& strText);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameterBetweenParentheses
	//
	// description	: This function returns the parameter, placed between 
	//				  parentheses. If no parentheses are present, an empty string
	//				  is returned.
	//
	// parameters	: strText		string to get parameter from
	//
	// returns		: string containing parameter between parentheses
	///////////////////////////////////////////////////////////////////////////////
	string GetParameterBetweenParentheses(const string& strText);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GeneralInitializing
	//
	// description	: This function uses HasParentheses to check for parentheses in
	//			      m_strPrefix	and when needed removes these parentheses.
	//				  It sets m_bHasParentheses to true or false.
	//				  It calculates the length of the prefix string.
	//
	// parameters	: none
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void GeneralInitializing();

///////////////////////////////////////////////////////////////////////////////////
//	member variables set at initialisation

	string	m_strPrefix;			// the prefix from the ini file
	int		m_nPrefixLength;		// length of the prefix string
	bool	m_bHasParentheses;		// true when command has parenthesis, else false
	bool	m_bHasParameter;		// true when command has parameter, else false

///////////////////////////////////////////////////////////////////////////////////
//	member variables set at interpretation

	string	m_strArgument;			// the input string to be interpreted as command
	bool	m_bIsCommand;			// true when the interpretion as command is true
	string	m_strArgumentValue;		// the result string of the evaluation/transformation
									// or the m_strParameter in case no evaluation/transformation
};

////////////////////////////////////////////////////////////////////////////////

#endif // ARGUMENTCOMMAND_H
