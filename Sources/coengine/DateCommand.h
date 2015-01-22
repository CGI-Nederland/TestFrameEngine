/*****************************************************************************
 * $Workfile: DateCommand.h $
 * $Revision: 2 $
 * $Modtime: 8/13/01 4:06p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include <string>

using namespace std;

#include "ArgumentCommand.h"		// Base class

#undef BASECLASS
#define BASECLASS	ArgumentCommand

class DateTime;
class EngineSetting;
class Parser;

////////////////////////////////////////////////////////////////////////////////
// class ArgumentCommand
class DateCommand : public BASECLASS
{
// Construction and destruction
public:
	explicit DateCommand( Parser* pTheParser );			// Constructor

	~DateCommand() {};							// Destructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Initialize
	//
	// description	:	This function initializes the AnythingCommand Object
	//					by reading the EngineSetting from the ini file.
	//					
	// parameters	:	pSetting	pointer to the Settings Object to find
	//									the prefix
	//				  
	//
	// returns		:	true	initialization successful
	//					false	initialization failed
	///////////////////////////////////////////////////////////////////////////////
	bool Initialize( EngineSetting* pSetting );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EvaluateCommand
	//
	// description	:	This function evaluates the command by filling the argument
	//					value part (m_strArgumentValue) of the command string
	//
	// parameters	:	-
	//
	// returns		:	true	evaluation successful
	//					false	evaluation failed
	///////////////////////////////////////////////////////////////////////////////
	bool EvaluateCommand();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParameterString
	//
	// description	:	This function retrieves the parameter string for the
	//					Interpreter.
	//
	// parameters	:	-
	//
	// returns		:	parameter of the date-command
	///////////////////////////////////////////////////////////////////////////////
	string GetParameterString();

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretParameter
	//
	// description	:	This function interprets the command parameter.
	//					It checks for parenthesis and extracts the command argument
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void InterpretParameter();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineFormat
	//
	// description	:	This function searches for the format in the specied
	//					parameter-string; if it is found, its value is placed in
	//					the referenced format-string.
	//
	// parameters	:	strParameter	parameter in which to search for format
	//					REF strFormat	to be filled with found format-string
	//
	// returns		:	true	format found
	//					false	format not found
	///////////////////////////////////////////////////////////////////////////////
	bool DetermineFormat( const string& strParameter, string& strFormat );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineTimeToAdd
	//
	// description	:	This function searches in the specied parameter-string for
	//					values that are to be added to the current day, month, and
	//					year.
	//
	// parameters	:	strParameter	parameter in which to search for values
	//					REF nYears		to be filled with found years to add
	//					REF nMonths		to be filled with found months to add
	//					REF nDays		to be filled with found days to add
	//
	// returns		:	true	valid parameter; referenced integers filled
	//					false	invalid parameter
	///////////////////////////////////////////////////////////////////////////////
	bool DetermineTimeToAdd( const string& strParameter, int& nYears,
							 int& nMonths, int& nDays );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Format
	//
	// description	:	This function returns a string based on a specified format
	//					in which the tokens for years ("yyyy", "yy"), months ("mm",
	//					"m"), and days ("dd", "d") are replaced by the
	//					corresponding value of the specified DateTime object.
	//
	// parameters	:	strFormat	format-string
	//					pDate		pointer to DateTime object
	//
	// returns		:	date-string based on format
	///////////////////////////////////////////////////////////////////////////////
	string Format( const string& strFormat, DateTime* pDate );

// Member variables:
private:
	Parser*	m_pTheParser;		// connection to the parser
	string	m_strParameter;		// string containing the command parameter
};

#undef BASECLASS
#endif // DATECOMMAND_H
