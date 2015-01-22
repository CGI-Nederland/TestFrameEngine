/*****************************************************************************
 * $Workfile: LogParser.cpp $
 * $Revision: 1 $
 * $Modtime: 8/22/01 12:02p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "LogParser.h"		// Class definition
#include "DateTime.h"
#include "LogReader.h"
#include "LogTag.h"
#include "StrUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						====================
						LogParser::LogParser
//						====================
(
	const string& strFileName
)
{
	m_pLogReader = new LogReader( strFileName );
	m_bGood = m_pLogReader->Good();
	m_pLogTag = new LogTag();
	ClearLine();
}


//						=====================
						LogParser::~LogParser()
//						=====================
{
	delete m_pLogReader;
	delete m_pLogTag;

	m_pLogReader=0;
	m_pLogTag=0;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						===============
bool					LogParser::Good() const
//						===============
{
	return m_bGood;
}


//						======================
const string&			LogParser::GetFileName() const
//						======================
{
	return m_pLogReader->GetFileName();
}


//						===================
bool					LogParser::NextLine()
//						===================
{
	bool bResult = false;

	// Go through log lines until a valid one or the end of file is found.
	bool bGetAnother = true;
	while ( bGetAnother )
	{
		// Set beforehand that no other line needs to be read.
		bGetAnother = false;

		// Clear the last line.
		ClearLine();

		// Let the LogReader get the next line from the log.
		if ( m_pLogReader->NextLine() )
		{
			// Get the line number of new log line.
			m_nLogLine = m_pLogReader->GetLineNumber();

			// A new line has been read from the log; determine if it makes up
			// a valid log line
			if ( IsLineValid() )
			{
				bResult = true;
			}
			else
			{
				// Only when a read has been read and it is found to be
				// invalid, specify that another line needs to be read.
				bGetAnother = true;
			}
		}
	}

	return bResult;
}


//						=====================
int						LogParser::GetLogLine() const
//						=====================
{
	return m_nLogLine;
}


//						======================
DateTime				LogParser::GetDateTime() const
//						======================
{
	return m_dtNow;
}


//						=========================
int						LogParser::GetClusterLine() const
//						=========================
{
	return m_nClusterLine;
}


//						=====================
LogTag::TAG				LogParser::GetKeyWord() const
//						=====================
{
	return m_nKeyWord;
}


//						========================
const vector<string>&	LogParser::GetParameters() const
//						========================
{
	return m_vstrParameters;
}


//						=======================
string					LogParser::GetParameter
//						=======================
(
	int					nIndex
) const
{
	string strParameter;

	// Determine if the index is in range.
	if ( nIndex > 0 && nIndex <= m_vstrParameters.size() )
	{
		// Get the specified parameter; note that the first parameter
		// has index 1.
		strParameter = m_vstrParameters[nIndex - 1];
	}

	return strParameter;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						====================
void					LogParser::ClearLine()
//						====================
{
	// Set all members for log line values to their defaults.
	m_nLogLine = 0;
	m_dtNow.Set( 1, 1, 1, 0, 0, 0, 0 );
	m_nClusterLine = -1;
	m_nKeyWord = LogTag::UNDEF_TAG;
	m_vstrParameters.clear();
}


//						======================
bool					LogParser::IsLineValid()
//						======================
{
	bool bResult = false;

	// Determine if the line, as read by LogReader, has at least four
	// arguments: (1) date; (2) time; (3) cluster line number; (4) keyword.
	if ( m_pLogReader->GetNumberOfArguments() >= 4 )
	{
		bool bDate = DetermineDate( m_pLogReader->GetArgument( 1 ) );
		bool bTime = DetermineTime( m_pLogReader->GetArgument( 2 ) );
		bool bLine = DetermineLineNumber( m_pLogReader->GetArgument( 3 ) );
		bool bKey = DetermineKeyWord( m_pLogReader->GetArgument( 4 ) );

		// Only if all four arguments are valid, is result true.
		bResult = bDate && bTime && bLine && bKey;

		// Get the keyword parameters, but only if the line is valid.
		if ( bResult )
		{
			DetermineParameters();
		}
	}

	return bResult;
}


//						========================
bool					LogParser::DetermineDate
//						========================
(
	const string&		strDate
)
{
	bool bResult = false;

	// A correct date string must have the following format: YYYY-MM-DD, where
	// YYYY is the year in four digits, MM the month in two digits, and DD the
	// day in two digits.
	// Convert the specified date string to a vector, splitting the arguments
	// on the minus sign.
	vector<string> vstrDate = StrToVector( strDate, "-" );

	// Determine if there are three elements in this vector; if not, the date
	// string is invalid.
	if ( vstrDate.size() == 3 )
	{
		// Take the elements of the vector; the the first as the year, the
		// second as the month, and the third as the day.
		int nYear = StrToInt( vstrDate[0], 0 );
		int nMonth = StrToInt( vstrDate[1], 0 );
		int nDay = StrToInt( vstrDate[2], 0 );

		// Change the date into those values found; determine if
		// this succeeded.
		bResult = m_dtNow.ChangeDate( nYear, nMonth, nDay );
	}

	return bResult;
}


//						========================
bool					LogParser::DetermineTime
//						========================
(
	const string&		strTime
)
{
	bool bResult = false;

	// A correct time string must have the following format: HH:MM:SS.mmm,
	// where HH is the hour, MM the minutes, SS the seconds, and mmm the
	// milliseconds.
	// First, convert the specified time string to a vector, splitting the
	// arguments on the colon sign.
	vector<string> vstrTime = StrToVector( strTime, ":" );

	// Determine if there are three elements in this vector; if not, the time
	// string is invalid.
	if ( vstrTime.size() == 3 )
	{
		// The third element of the time-vector should contain the seconds and
		// milliseconds; convert thelement to a vector itself, this time
		// splitting the arguments on the dot sign.
		vector<string> vstrSecs = StrToVector( vstrTime[2], "." );

		// Determine if this vector has two elements; if not, the time string
		// is invalid.
		if ( vstrSecs.size() == 2 )
		{
			// Take the first two elements of the time-vector, and determine
			// if (1) is an hour, and (2) minutes; take the elements of the
			// seconds-vector and determine if (1) are seconds, (2) are
			// milliseconds.
			bool bHour = m_dtNow.ChangeHour( StrToInt( vstrTime[0], -1 ) );
			bool bMin = m_dtNow.ChangeMin( StrToInt( vstrTime[1], -1 ) );
			bool bSec = m_dtNow.ChangeSec( StrToInt( vstrSecs[0], -1 ) );
			bool bMillisec = m_dtNow.ChangeMillisec( StrToInt( vstrSecs[1], -1 ) );

			// Only if all four are valid integers, result is true.
			bResult = bHour && bMin && bSec && bMillisec;
		}
	}

	return bResult;
}


//						==============================
bool					LogParser::DetermineLineNumber
//						==============================
(
	const string&		strLine
)
{
	bool bResult = false;
	
	// Convert the specified string to an integer; take -1 as default.
	int nLine = StrToInt( strLine, -1 );

	// Determine if the found integer is greater than or equal to 0.
	if ( nLine >= 0 )
	{
		// Set the member to the found line number.
		m_nClusterLine = nLine;
		bResult = true;
	}

	return bResult;
}


//						===========================
bool					LogParser::DetermineKeyWord
//						===========================
(
	const string&		strKeyWord
)
{
	bool bResult = false;

	// Get the ID belonging to the specified keyword.
	LogTag::TAG nKeyWord = m_pLogTag->GetTagID( strKeyWord );

	// Determine if the keyword is a valid one.
	if ( nKeyWord != LogTag::UNDEF_TAG )
	{
		// Set the member to the found keyword.
		m_nKeyWord = nKeyWord;
		bResult = true;
	}

	return bResult;
}


//						==============================
void					LogParser::DetermineParameters()
//						==============================
{
	// Get the number of arguments of the last read line, and determine if
	// it contains any keyword parameters by determining if there are more
	// than four arguments.
	int nMaxArgs = m_pLogReader->GetNumberOfArguments();
	if ( nMaxArgs > 4 )
	{
		// Go through all keyword parameters (i.e. all arguments beyond
		// index 4) and add them to the parameter-vector.
		int nArg;
		for ( nArg = 5; nArg <= nMaxArgs; nArg++ )
		{
			m_vstrParameters.push_back( m_pLogReader->GetArgument( nArg ) );
		}
	}
}
