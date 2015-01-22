/*****************************************************************************
 * $Workfile: TimeCommand.cpp $
 * $Revision: 1 $
 * $Modtime: 5/6/02 11:48a $
 * $Author: MdJ $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "TimeCommand.h"	// Class definition

#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "EngineSetting.h"
#include "Parser.h"
#include "StrUtil.h"

// Defines
#define YEAR_4_TOKEN	string( "YYYY" )
#define YEAR_2_TOKEN	string( "YY" )
#define MONTH_2_TOKEN	string( "MM" )
#define MONTH_TOKEN		string( "M" )
#define DAY_2_TOKEN		string( "DD" )
#define DAY_TOKEN		string( "D" )
#define HOUR_2_TOKEN	string( "hh" )
#define HOUR_TOKEN		string( "h" )
#define MINUTE_2_TOKEN	string( "mm" )
#define MINUTE_TOKEN	string( "m" )
#define SECOND_2_TOKEN	string( "ss" )
#define SECOND_TOKEN	string( "s" )
#define MILLI_3_TOKEN	string( "nnn" )
#define MILLI_TOKEN		string( "n" )

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						========================
						TimeCommand::TimeCommand
//						========================
(
	Parser*				pTheParser
)
{
	m_pTheParser = pTheParser;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
bool					TimeCommand::Initialize
//						=======================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "TimePrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();

	m_bHasParameter = true;
	return true;
}


//						============================
bool					TimeCommand::EvaluateCommand()
//						============================
{
	bool bResult = false;

	// Initialise the argument value as the argument's literal value.
	m_strArgumentValue = m_strArgument;

	// Interpret the date-command's parameter.
	if ( m_bHasParameter )
	{
		InterpretParameter();
	}

	// Determine if the parameter is not empty.
	if ( !m_strParameter.empty() ) 
	{
		// Determine the format, and check if this operation succeeds.
		string strFormat;
		if ( DetermineFormat( m_strParameter, strFormat ) )
		{
			// Initialise the years, months, and days to add to zero.
			int nYearsAdd = 0;
			int nMonthsAdd = 0;
			int nDaysAdd = 0;			
			int nHoursAdd = 0;
			int nMinutesAdd = 0;
			int nSecondsAdd = 0;
			int nMilliSecondsAdd = 0;

			// Determine what the values for the years, months, and days to
			// add are as specified in the parameter; check if this operation
			// succeeds.
			if ( DetermineTimeToAdd( m_strParameter, nYearsAdd, nMonthsAdd, nDaysAdd, nHoursAdd,
													 nMinutesAdd, nSecondsAdd, nMilliSecondsAdd) )
			{
				// Create a DateTime object for the current machine date.
				DateTime dtNow;

				// Add to this time the found hours, minutes, seconds and milliseconds.
				dtNow.AddYear( nYearsAdd );
				dtNow.AddMonth( nMonthsAdd );
				dtNow.AddDay( nDaysAdd );				
				dtNow.AddHour( nHoursAdd );
				dtNow.AddMin( nMinutesAdd );
				dtNow.AddSec( nSecondsAdd );
				dtNow.AddMillisec( nMilliSecondsAdd );

				// Format the time-string, and take the result as the
				// argument value.
				m_strArgumentValue = Format( strFormat, &dtNow );

				bResult = true;
			}
		}
		else
		{
			// The format is missing; notify the parser of this error.
			m_pTheParser->NotifyMissingTimeFormat();
		}
	}
	else
	{
		// The format is missing; notify the parser of this error.
		m_pTheParser->NotifyMissingTimeFormat();
	}

	return bResult;
}


//						===============================
string					TimeCommand::GetParameterString()
//						===============================
{
	return m_strParameter;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						===============================
void					TimeCommand::InterpretParameter()
//						===============================
{
	// get the characters behind the prefix and
	// store parameter of the command in m_strParameter
	m_strParameter = m_strArgument.substr(m_nPrefixLength);

	// check for parentheses
	if (m_bHasParentheses)
	{
		// Change the parameter to the string between parentheses.
		m_strParameter = GetParameterBetweenParentheses(m_strParameter);
	}
			
}


//						============================
bool					TimeCommand::DetermineFormat
//						============================
(
	const string&		strParameter,
	string&				strFormat
)
{
	bool bResult = false;

	// The format is defined as those characters of the parameter that lie
	// between the first and last quotation mark; determine the positions of
	// these quotation marks.
	string::size_type nFirst = strParameter.find_first_of( "\"" );
	string::size_type nLast = strParameter.find_last_of( "\"" );

	// Determine if there are (at least) two quotation marks found.
	if ( nFirst < nLast )
	{
		// Take as format the characters between these quotation marks.
		strFormat = strParameter.substr( nFirst + 1, nLast - nFirst - 1 );
		bResult = true;
	}

	return bResult;
}


//						===============================
bool					TimeCommand::DetermineTimeToAdd
//						===============================
(
	const string& strParameter,
	int& nYears,
	int& nMonths,
	int& nDays,
	int& nHours,
	int& nMinutes,
	int& nSeconds,
	int& nMils
)
{
	bool bResult = false;

	// Determine the end of the format by finding the last quotation mark
	// in the parameter, and check if it is present.
	string::size_type nLastQuote = strParameter.find_last_of( "\"" );
	if ( nLastQuote != string::npos )
	{
		// Take the parameter from the end of the format on, and split this
		// string taking the comma as separator.
		vector<string> vstrArgs = StrToVector( strParameter.substr( nLastQuote ), "," );

		// Since we are interested here only in the arguments after the first
		// comma, remove the first element of the vector (which are the
		// characters before the first comma, or, in case there was no comma at
		// all, all characters we're not interested in).
		vstrArgs.erase( vstrArgs.begin() );

		// The vector now contains the arguments specifying (in its fullest
		// case) the hours, minutes, seconds, and milliseconds to add;
		// however, as strings which may be expressions. So, convert the argument
		// vector to a vector of their integer values.
		bool bErrors = false;
		vector<int> vnArgs;
		if ( !vstrArgs.empty() )
		{
			vector<string>::size_type nArg = 0;
			for ( ; !bErrors && nArg < vstrArgs.size(); nArg++ )
			{
				// The argument may be an expression; evaluate it, and
				// determine if this was successful.
				if ( m_pTheParser->Parse( vstrArgs[nArg] ) )
				{
					// Get the result from the evaluation, convert it to an
					// integer value (taking 0 as default), and place this
					// value in the integer-vector.
					vnArgs.push_back( StrToInt( m_pTheParser->GetResult(), 0 ) );
				}
				else
				{
					// The expression contained an error; stop further
					// evaluation.
					bErrors = true;
				}
			}
		}

		// Only continue if all arguments were parsed without errors.
		if ( !bErrors )
		{
			// The vector of integers must be (at least) three elements long
			// (hours, minutes, seconds and milliseconds); fill any missing
			// values with 0.
			while ( vnArgs.empty() || vnArgs.size() < 4 )
			{
				vnArgs.push_back( 0 );
			}

			// Fill the referenced function parameters with hours (1st arg),
			// minutes (2nd arg), seconds (3rd arg) and milliseconds (4th arg).
			nYears		= vnArgs[0];
			nMonths		= vnArgs[1];
			nDays		= vnArgs[2];
			nHours		= vnArgs[3];
			nMinutes	= vnArgs[4];
			nSeconds	= vnArgs[5];
			nMils		= vnArgs[6];

			bResult = true;
		}
	}

	return bResult;
}


//						===================
string					TimeCommand::Format
//						===================
(
	const string&		strFormat,
	DateTime*			pTime
)
{
	string strResult = strFormat;

	// Replace in the format the tokens possible in the time-command by
	// the corresponding values from the specified DateTime object.

	ReplaceToken( strResult, YEAR_4_TOKEN, pTime->Get( "YYYY" ) );
	ReplaceToken( strResult, YEAR_2_TOKEN, pTime->Get( "YY" ) );
	ReplaceToken( strResult, MONTH_2_TOKEN, pTime->Get( "MM" ) );
	ReplaceToken( strResult, MONTH_TOKEN, pTime->Get( "M" ) );
	ReplaceToken( strResult, DAY_2_TOKEN, pTime->Get( "DD" ) );
	ReplaceToken( strResult, DAY_TOKEN, pTime->Get( "D" ) );

	ReplaceToken( strResult, HOUR_2_TOKEN, pTime->Get( "hh" ) );
	ReplaceToken( strResult, HOUR_TOKEN, pTime->Get( "h" ) );
	ReplaceToken( strResult, MINUTE_2_TOKEN, pTime->Get( "mm" ) );
	ReplaceToken( strResult, MINUTE_TOKEN, pTime->Get( "m" ) );
	ReplaceToken( strResult, SECOND_2_TOKEN, pTime->Get( "ss" ) );
	ReplaceToken( strResult, SECOND_TOKEN, pTime->Get( "s" ) );
	ReplaceToken( strResult, MILLI_3_TOKEN, pTime->Get( "nnn" ) );
	ReplaceToken( strResult, MILLI_TOKEN, pTime->Get( "n" ) );

	return strResult;
}

///////////////////////////////////////////////////////////////////////////////

// Undefines
#undef YEAR_4_TOKEN
#undef YEAR_2_TOKEN
#undef MONTH_2_TOKEN
#undef MONTH_TOKEN
#undef DAY_2_TOKEN
#undef DAY_TOKEN
#undef HOUR_2_TOKEN
#undef HOUR_TOKEN
#undef MINUTE_2_TOKEN
#undef MINUTE_TOKEN
#undef SECOND_2_TOKEN
#undef SECOND_TOKEN
#undef MILLI_3_TOKEN
#undef MILLI_TOKEN