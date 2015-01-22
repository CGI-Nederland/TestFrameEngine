/*****************************************************************************
 * $Workfile: DateCommand.cpp $
 * $Revision: 3 $
 * $Modtime: 8/17/01 11:48a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "DateCommand.h"	// Class definition

#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "EngineSetting.h"
#include "Parser.h"
#include "StrUtil.h"

// Defines
#define YEAR_4_TOKEN	string( "yyyy" )
#define YEAR_2_TOKEN	string( "yy" )
#define MONTH_2_TOKEN	string( "mm" )
#define MONTH_TOKEN		string( "m" )
#define DAY_2_TOKEN		string( "dd" )
#define DAY_TOKEN		string( "d" )

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						========================
						DateCommand::DateCommand
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
bool					DateCommand::Initialize
//						=======================
(
	EngineSetting*		pSetting
)
{
	// get the prefix out of the settings
	m_strPrefix	= pSetting->Get("SYSTEM", "DatePrefix");

	// check for parentheses and calculate the length
	GeneralInitializing();

	m_bHasParameter = true;
	return true;
}


//						============================
bool					DateCommand::EvaluateCommand()
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

			// Determine what the values for the years, months, and days to
			// add are as specified in the parameter; check if this operation
			// succeeds.
			if ( DetermineTimeToAdd( m_strParameter, nYearsAdd, nMonthsAdd, nDaysAdd ) )
			{
				// Create a DateTime object for the current machine date.
				DateTime dtNow;

				// Add to this date the found years, months, and days.
				dtNow.AddYear( nYearsAdd );
				dtNow.AddMonth( nMonthsAdd );
				dtNow.AddDay( nDaysAdd );

				// Format the date-string, and take the result as the
				// argument value.
				m_strArgumentValue = Format( strFormat, &dtNow );

				bResult = true;
			}
		}
		else
		{
			// The format is missing; notify the parser of this error.
			m_pTheParser->NotifyMissingDateFormat();
		}
	}
	else
	{
		// The format is missing; notify the parser of this error.
		m_pTheParser->NotifyMissingDateFormat();
	}

	return bResult;
}


//						===============================
string					DateCommand::GetParameterString()
//						===============================
{

	return m_strParameter;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						===============================
void					DateCommand::InterpretParameter()
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
bool					DateCommand::DetermineFormat
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
bool					DateCommand::DetermineTimeToAdd
//						===============================
(
	const string&		strParameter,
	int&				nYears,
	int&				nMonths,
	int&				nDays
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
		// case) the years, months, and days to add; however, as strings which
		// may be expressions. So, convert the argument vector to a vector of
		// their integer values.
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
			// (year, month, and day); fill any missing values with 0.
			while ( vnArgs.empty() || vnArgs.size() < 3 )
			{
				vnArgs.push_back( 0 );
			}

			// Fill the referenced function parameters with days (1st arg),
			// months (2nd arg), and years (3rd arg).
			nDays = vnArgs[0];
			nMonths = vnArgs[1];
			nYears = vnArgs[2];

			bResult = true;
		}
	}

	return bResult;
}


//						===================
string					DateCommand::Format
//						===================
(
	const string&		strFormat,
	DateTime*			pDate
)
{
	string strResult = strFormat;

	// Replace in the format the tokens possible in the date-command by
	// the corresponding values from the specified DateTime object.
	ReplaceToken( strResult, YEAR_4_TOKEN, pDate->Get( "YYYY" ) );
	ReplaceToken( strResult, YEAR_2_TOKEN, pDate->Get( "YY" ) );
	ReplaceToken( strResult, MONTH_2_TOKEN, pDate->Get( "MM" ) );
	ReplaceToken( strResult, MONTH_TOKEN, pDate->Get( "M" ) );
	ReplaceToken( strResult, DAY_2_TOKEN, pDate->Get( "DD" ) );
	ReplaceToken( strResult, DAY_TOKEN, pDate->Get( "D" ) );

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
