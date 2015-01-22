/*****************************************************************************
 * $Workfile: LogParser.h $
 * $Revision: 1 $
 * $Modtime: 8/22/01 11:24a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOGPARSER_H
#define LOGPARSER_H

// Includes
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "LogTag.h"

// Forward declarations
class LogReader;

////////////////////////////////////////////////////////////////////////////////
// class LogParser

class LogParser
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of LogParser
	//
	// parameters	:	strLogFile		log file to be read
	///////////////////////////////////////////////////////////////////////////////		
	LogParser(){};
	explicit LogParser( const string& strLogFile );

	LogParser(LogParser&);
	LogParser& operator=(LogParser&);
	///////////////////////////////////////////////////////////////////////////////
	// destructor of LogParser
	///////////////////////////////////////////////////////////////////////////////		
	~LogParser();

private:
	LogParser( const LogParser& src ){};	// Copy constructor

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Good()
	//
	// description	:	This function states whether or not the LogParser object is
	//					able to parse its log file.
	//
	// parameters	:	-
	//
	// returns		:	true	able to parse log
	//					false	unable to parse log
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
	// description	:	This function gets the next line from the log, and fills
	//					the member variables with the new line's values. If the
	//					end of the file is reached, false is returned.
	//
	// parameters	:	-
	//
	// returns		:	true	next line found
	//					false	end of log reached
	///////////////////////////////////////////////////////////////////////////////		
	bool NextLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetLogLine()
	//
	// description	:	This function returns from the last read log line its log
	//					line number; note that this is different from its cluster
	//					line number.
	//					If there is no last read line, 0 is returned.
	//
	// parameters	:	-
	//
	// returns		:	log line number of last read log line
	///////////////////////////////////////////////////////////////////////////////		
	int GetLogLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetDateTime()
	//
	// description	:	This function returns the DateTime object associated with
	//					the last read log line; it contains the log line's date
	//					and time.
	//					If there is no last read line, the DateTime object is set
	//					01-01-0001 midnight.
	//
	// parameters	:	-
	//
	// returns		:	DateTime object for last read log line
	///////////////////////////////////////////////////////////////////////////////		
	DateTime GetDateTime() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetClusterLine()
	//
	// description	:	This function returns from the last read log line its
	//					cluster line number. 
	//					If there is no last read line, -1 is returned.
	//
	// parameters	:	-
	//
	// returns		:	cluster line number from last read log line
	///////////////////////////////////////////////////////////////////////////////		
	int GetClusterLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetKeyWord()
	//
	// description	:	This function returns from the last read log line the
	//					LogTag enum integer specifying its keyword. If there is no
	//					last read line, the enum int UNDEF_TAG is returned.
	//
	// parameters	:	-
	//
	// returns		:	integer specifying keyword type of last read log line
	///////////////////////////////////////////////////////////////////////////////		
	LogTag::TAG GetKeyWord() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParameters()
	//
	// description	:	This function returns from the last read log line the
	//					parameters belonging to its keyword.
	//
	// parameters	:	-
	//
	// returns		:	vector with keyword parameters of last read log line
	///////////////////////////////////////////////////////////////////////////////		
	const vector<string>& GetParameters() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetParameters()
	//
	// description	:	This function returns from the last read log line the
	//					specified parameter belonging to its keyword; the first
	//					parameter has index 1. If the index	is out of range, an
	//					empty string is returned.
	//
	// parameters	:	-
	//
	// returns		:	specified keyword parameter of last read log line
	///////////////////////////////////////////////////////////////////////////////		
	string GetParameter( int nIndex ) const;

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	ClearLine()
	//
	// description	:	This function sets all members for log line values to
	//					their defaults.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void ClearLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	IsLineValid()
	//
	// description	:	This function determines all elements of the last read log
	//					line, and checks if they are those of a valid log line.
	//
	// parameters	:	-
	//
	// returns		:	true	last read line is valid
	//					false	last read line is invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool IsLineValid();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineDate()
	//
	// description	:	This function determines if the specified string can be
	//					interpreted as a date; if so, the corresponding members for
	//					the last read line are filled.
	//
	// parameters	:	strDate		string to interpret as a date
	//
	// returns		:	true	string interpreted as a date
	//					false	string could not be interpreted as a date
	///////////////////////////////////////////////////////////////////////////////		
	bool DetermineDate( const string& strDate );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineTime()
	//
	// description	:	This function determines if the specified string can be
	//					interpreted as a time; if so, the corresponding members
	//					for the last read line are filled.
	//
	// parameters	:	strTime		string to interpret as a time
	//
	// returns		:	true	string interpreted as a time
	//					false	string could not be interpreted as a time
	///////////////////////////////////////////////////////////////////////////////		
	bool DetermineTime( const string& strTime );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineLineNumber()
	//
	// description	:	This function determines if the specified string can be
	//					interpreted as a cluster line number; if so, the
	//					corresponding member for the last read line is filled.
	//
	// parameters	:	strLine		string to interpret as cluster line number
	//
	// returns		:	true	string interpreted as cluster line number
	//					false	string could not be interpreted as cluster line
	//							number
	///////////////////////////////////////////////////////////////////////////////		
	bool DetermineLineNumber( const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineKeyWord()
	//
	// description	:	This function determines, using the LogTag object, if the
	//					specified string can be interpreted as a log-keyword; if
	//					so, the corresponding members for the last read line are
	//					filled.
	//
	// parameters	:	strKeyWord		string to interpret as log-keyword
	//
	// returns		:	true	string interpreted as log-keyword
	//					false	string could not be interpreted as log-keyword
	///////////////////////////////////////////////////////////////////////////////		
	bool DetermineKeyWord( const string& strKeyWord );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DetermineParameters()
	//
	// description	:	This function determines if the last read log line has any
	//					parameters; if so, these are stored in the corresponding
	//					member.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void DetermineParameters();

// Member variables
private:
	bool m_bGood;						// States whether the object is ready
	LogReader* m_pLogReader;			// Pointer to the LogReader object
	LogTag* m_pLogTag;					// Pointer to the LogTag object
	int m_nLogLine;						// Log line number of last read line
	DateTime m_dtNow;					// Date/time of last read line
	int m_nClusterLine;					// Cluster line number of last read line
	LogTag::TAG m_nKeyWord;				// Keyword of last read line
	vector<string> m_vstrParameters;	// Parameters of last read line
};

////////////////////////////////////////////////////////////////////////////////

#endif // !LOGPARSER_H
