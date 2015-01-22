/*****************************************************************************
 * $Workfile: TimeCommand.h $
 * $Revision: 1 $
 * $Modtime: 5/6/02 11:48a $
 * $Author: MdJ $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2002 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#ifndef TIMECOMMAND_H
#define TIMECOMMAND_H

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
class TimeCommand : public BASECLASS
{
// Construction and destruction
public:
	explicit TimeCommand( Parser* pTheParser );			// Constructor

	~TimeCommand() {};							// Destructor

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
	//					REF nHours		to be filled with found hours to add
	//					REF nMinutes	to be filled with found minutes to add
	//					REF nSeconds	to be filled with found seconds to add
	//					REF nMils		to be filled with found milli seconds to add
	//
	// returns		:	true	valid parameter; referenced integers filled
	//					false	invalid parameter
	///////////////////////////////////////////////////////////////////////////////
	bool DetermineTimeToAdd( const string& strParameter, int& nYearsAdd, int& nMonthsAdd, 
							 int& nDaysAdd, int& nHours, int& nMinutes, int& nSeconds, 
							 int& nMils );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Format
	//
	// description	:	This function returns a string based on a specified format
	//					in which the tokens for hours ("hh", "h"), minutes ("mm",
	//					"m"), seconds ("ss", "s") and milli seconds ("nnn", "n")
	//					are replaced by the	corresponding value of the specified
	//					DateTime object.
	//
	// parameters	:	strFormat	format-string
	//					pTime		pointer to DateTime object
	//
	// returns		:	time-string based on format
	///////////////////////////////////////////////////////////////////////////////
	string Format( const string& strFormat, DateTime* pTime );

// Member variables:
private:
	Parser*	m_pTheParser;		// connection to the parser
	string	m_strParameter;		// string containing the command parameter
};

#undef BASECLASS
#endif // TIMECOMMAND_H
