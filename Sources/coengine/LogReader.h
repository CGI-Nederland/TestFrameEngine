/*****************************************************************************
 * $Workfile: LogReader.h $
 * $Revision: 1 $
 * $Modtime: 6/25/01 2:34p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGREADER_H
#define LOGREADER_H

// Includes
#include <string>
#include <vector>

using namespace std;

#undef BASECLASS
#define BASECLASS Result

#include "Result.h"			// Baseclass definition

////////////////////////////////////////////////////////////////////////////////
// class LogReader

class LogReader : public BASECLASS
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of LogReader
	//
	// parameters	:	strLogFile		log file to be read
	///////////////////////////////////////////////////////////////////////////////		
	explicit LogReader( const string& strLogFile );

	///////////////////////////////////////////////////////////////////////////////
	// destructor of LogReader
	///////////////////////////////////////////////////////////////////////////////		
	~LogReader();

private:
	LogReader( const LogReader& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function states whether or not the LogReader object is
	//					able to read its log file.
	//
	// parameters	:	-
	//
	// returns		:	true	able to read log
	//					false	unable to read log
	///////////////////////////////////////////////////////////////////////////////		
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetFileName()
	//
	// description	:	This function returns the name of the log file to read.
	//
	// parameters	:	-
	//
	// returns		:	string containing log file name
	///////////////////////////////////////////////////////////////////////////////		
	const string& GetFileName() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	NextLine()
	//
	// description	:	This function reads the next line from the log file, and
	//					fills the member variables with the new line's values. If
	//					the end of the file is reached, false is returned.
	//
	// parameters	:	-
	//
	// returns		:	true	next line read
	//					false	end of log file reached
	///////////////////////////////////////////////////////////////////////////////		
	bool NextLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLine()
	//
	// description	:	This function returns the last read line. If no line has
	//					been read yet, or if the end of file has been read, an
	//					empty string is returned.
	//
	// parameters	:	-
	//
	// returns		:	string containing last read line
	///////////////////////////////////////////////////////////////////////////////		
	const string& GetLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetArgument()
	//
	// description	:	This function returns the specified argument from the last
	//					read line. If the specified argument index is out of range,
	//					or if there is no last read line, an empty string is
	//					returned.
	//					Note that the first argument of a line has index 1.
	//
	// parameters	:	nIndex		argument index
	//
	// returns		:	string containing specified argument
	///////////////////////////////////////////////////////////////////////////////		
	string GetArgument( int nIndex ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetNumberOfArguments()
	//
	// description	:	This function returns the number of arguments that the last
	//					read line has. If there is no last read line, zero is
	//					returned.
	//
	// parameters	:	-
	//
	// returns		:	number of arguments of the last read line
	///////////////////////////////////////////////////////////////////////////////		
	int GetNumberOfArguments() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLineNumber()
	//
	// description	:	This function returns the number of the last read line; the
	//					first one has number 1.
	//					If there is no last read line, zero is returned.
	//
	// parameters	:	-
	//
	// returns		:	line number of the last read line
	///////////////////////////////////////////////////////////////////////////////		
	int GetLineNumber() const;

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClearLine()
	//
	// description	:	This function sets the last read line to an empty string
	//					and its argument-vector to an empty vector.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void ClearLine();

// Member variables
private:
	bool m_bGood;						// states whether the object is ready
	string m_strDelimiter;				// argument delimiter
	string m_strFileName;				// log file to read
	string m_strLine;					// last read line
	vector<string> m_vstrArguments;		// arguments of last read line
	int m_nLine;						// number of last read line
};


////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !LOGREADER_H
