/*****************************************************************************
 * $Workfile: KeyDate.cpp $
 * $Revision: 1 $
 * $Modtime: 1-05-01 18:06 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <sstream>

using namespace std;

#include "KeyDate.h"		// Class definition

///////////////////////////////////////////////////////////////////////////////
// Constants

#define YEAR2000			2000


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

KeyDate::KeyDate()
{
	// EMPTY //
}

KeyDate::~KeyDate()
{
	// EMPTY //
}


///////////////////////////////////////////////////////////////////////////////
// Public methods

//						====================
bool					KeyDate::IsValidDate
//						====================
(
	const string&		strDate,
	const string&		strFormat
)
{
	// Default result is failure
	bool bResult = false;

	// Calculate the length of the format
	string::size_type nFormatLength = 0;

	///////////////////////////////////////////////////////////////////////////
	// Retrieve the day
	//
	// Valid formats: DD

	string strDay = RetrieveString(strDate, strFormat, "DD");
	if (!strDay.empty())
	{ nFormatLength += 2; }
	
	
	///////////////////////////////////////////////////////////////////////////
	// Retrieve the month
	//
	// Valid formats: MM

	string strMonth = RetrieveString(strDate, strFormat, "MM");
	if (!strMonth.empty())
	{ nFormatLength += 2; }
	

	///////////////////////////////////////////////////////////////////////////
	// Retrieve the year
	//
	// Valid formats: YYYY, YY
	
	string strYear;
	string strYearFormat;
	
	strYear = RetrieveString(strDate, strFormat, "YYYY");
	strYearFormat = "YYYY";

	if (strYear.empty())
	{
		strYear = RetrieveString(strDate, strFormat, "YY");
		strYearFormat = "YY";
	}

	if (!strYear.empty())
	{ nFormatLength += strYearFormat.length(); }

	///////////////////////////////////////////////////////////////////////////
	// Retrieve the hours
	//
	// Valid formats: HH
	
	string strHours = RetrieveString(strDate, strFormat, "HH");
	if (!strHours.empty())
	{ nFormatLength += 2; }
 
	
	///////////////////////////////////////////////////////////////////////////
	// Retrieve the minutes
	//
	// Valid formats: mm
	string strMinutes = RetrieveString(strDate, strFormat, "mm");
	if (!strMinutes.empty())
	{ nFormatLength += 2; }

	///////////////////////////////////////////////////////////////////////////
	// Retrieve the seconds
	//
	// Valid formats: ss
	string strSeconds = RetrieveString(strDate, strFormat, "ss");
	if (!strSeconds.empty())
	{ nFormatLength += 2; }

	///////////////////////////////////////////////////////////////////////////
	// Validate the day

	bool bDay = false;
	if (strDay.empty())
	{
		bDay = true;
	}
	else
	{
		bDay = IsValidDay(strDay, strMonth, strYear, strYearFormat);
	}

	///////////////////////////////////////////////////////////////////////////
	// Validate the month

	bool bMonth = false;
	if (strMonth.empty())
	{
		bMonth = true;
	}
	else
	{
		bMonth = IsValidMonth(strMonth);
	}

	///////////////////////////////////////////////////////////////////////////
	// Validate the year

	bool bYear = false;
	if (strYear.empty())
	{
		bYear = true;
	}
	else
	{
		bYear = IsValidYear(strYear, strYearFormat);
	}

	///////////////////////////////////////////////////////////////////////////
	// Validate the hours

	bool bHours = false;;
	if (strHours.empty())
	{
		bHours = true;
	}
	else
	{
		bHours = IsValidHour(strHours);
	}

	///////////////////////////////////////////////////////////////////////////
	// Validate the minutes

	bool bMinutes = false;
	if (strMinutes.empty())
	{
		bMinutes = true;
	}
	else
	{
		bMinutes = IsValidMinutes(strMinutes);
	}
	
	///////////////////////////////////////////////////////////////////////////
	// Validate the seconds

	bool bSeconds = false;
	if (strSeconds.empty())
	{
		bSeconds = true;
	}
	else
	{
		bSeconds = IsValidSeconds(strSeconds);
	}
	
	// The length of the total format should be the sum of the parts
	if (strFormat.length() == nFormatLength)
	{
		// Everything should be correct
		bResult = bDay && bMonth && bYear && bHours && bMinutes && bSeconds;
	}

	return bResult;
}

//						====================
bool					KeyDate::IsValidYear
//						====================
(
	const string&		strYear,
	const string&		strFormat
)
{
	// Default result is failure
	bool bResult = false;

	// All years should be numeric
	if (IsNumeric(strYear))
	{
		// There are two valid year formats: YY and YYYY
		if ((strFormat == "YY") || (strFormat == "YYYY"))
		{
			// Check the length
			if (strYear.length() == strFormat.length())
			{
				bResult = true;
			}
		}
	}

	return bResult;
}

//						=====================
bool					KeyDate::IsValidMonth
//						=====================
(
	const string&		strMonth
)
{
	// Default result is failure
	bool bResult = false;

	// We have twelve months
	if (CheckBoundaries(strMonth, 1, 12))
	{
		// There is only one valid month format: MM
		if (strMonth.length() == strlen("MM"))
		{
			// Month is correct
			bResult = true;
		}
	}

	return bResult;
}

//						===================
bool					KeyDate::IsValidDay
//						===================
(
	const string&		strDay,
	const string&		strMonth,
	const string&		strYear,
	const string&		strYearFormat
)
{
	// Default result is failure
	bool bResult = false;

	if (IsNumeric(strDay))
	{
		// Year and month should be valid
		if (IsValidYear(strYear, strYearFormat) && IsValidMonth(strMonth))
		{
			// Get the maximum number of days for this month
			int nMaximumDays = GetNumberOfDays(GetMonth(strMonth), GetYear(strYear, strYearFormat));
			
			// See if the given day is valid
			if (CheckBoundaries(strDay, 1, nMaximumDays))
			{
				if (strDay.length() == 2)
				{
					// Day is correct
					bResult = true;
				}
			}
		}
	}

	return bResult;
}

//						====================
bool					KeyDate::IsValidHour
//						====================
(
	const string&		strHour
)
{
	// Default result is failure
	bool bResult = false;

	if (IsNumeric(strHour))
	{
		// Hours: 00 - 23
		bResult = CheckBoundaries(strHour, 0, 23);
	}

	return bResult;
}

//						=======================
bool					KeyDate::IsValidMinutes
//						=======================
(
	const string&		strMinutes
)
{
	// Default result is failure
	bool bResult = false;

	if (IsNumeric(strMinutes))
	{
		// Minutes: 00 - 59
		bResult = CheckBoundaries(strMinutes, 0, 59);
	}

	return bResult;
}

//						=======================
bool					KeyDate::IsValidSeconds
//						=======================
(
	const string&		strSeconds
)
{
	// Default result is failure
	bool bResult = false;

	if (IsNumeric(strSeconds))
	{
		// Seconds: 00 - 59
		bResult = CheckBoundaries(strSeconds, 0, 59);
	}

	return bResult;
}

//						=====================
bool					KeyDate::RetrieveYear
//						=====================
(
	const string&		strDate,
	const string&		strFormat,
	int&				nYear
)
{
	// Default result is failure
	bool bResult = false;
	nYear = 0;

	if (IsValidDate(strDate, strFormat))
	{
		string strYear;
		string strYearFormat;
		
		// First try the long year format
		strYear = RetrieveString(strDate, strFormat, "YYYY");
		strYearFormat = "YYYY";

		if (strYear.empty())
		{
			// Long format failed, so try the short format
			strYear = RetrieveString(strDate, strFormat, "YY");
			strYearFormat = "YY";
		}

		// See if we found a year
		if (!strYear.empty())
		{
			// Convert to an integer
			nYear = StrToInt(strYear);
			if (strYear.length() == 2)
			{
				// Add 2000 years because the short format was used
				nYear = nYear + YEAR2000;
			}

			bResult = true;
		}
	}

	return bResult;
}

//						======================
bool					KeyDate::RetrieveMonth
//						======================
(
	const string&		strDate,
	const string&		strFormat,
	int&				nMonth
)
{
	// Default result is failure
	bool bResult = false;
	nMonth = 0;

	if (IsValidDate(strDate, strFormat))
	{
		string strMonth = RetrieveString(strDate, strFormat, "MM");

		// See if we found a month
		if (!strMonth.empty())
		{
			// Convert to an integer
			nMonth = StrToInt(strMonth);

			bResult = true;
		}
	}

	return bResult;
}

//						====================
bool					KeyDate::RetrieveDay
//						====================
(
	const string&		strDate,
	const string&		strFormat,
	int&				nDay
)
{
	// Default result is failure
	bool bResult = false;
	nDay = 0;

	if (IsValidDate(strDate, strFormat))
	{
		string strDay = RetrieveString(strDate, strFormat, "DD");

		// See if we found a day
		if (!strDay.empty())
		{
			// Convert to an integer
			nDay = StrToInt(strDay);

			bResult = true;
		}
	}

	return bResult;
}

/* NOT YET IMPLEMENTED
bool RetrieveHour(const string& strDate, const string& strFormat, int& nHours);
bool RetrieveMinutes(const string& strDate, const string& strFormat,  int& nMinutes);
bool RetrieveSeconds(const string& strDate, const string& strFormat, int& nSeconds);
*/

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==================
bool					KeyDate::IsNumeric
//						==================
(
	const string&		strString
)
{
	// Default result is failure
	bool bResult = false;

	// See if we can find any non-numeric characters
	if (strString.find_first_not_of("0123456789") == string::npos)
	{
		// The string is numeric
		bResult = true;
	}

	return bResult;
}

//						========================
bool					KeyDate::CheckBoundaries
//						========================
(
	const string&		strString,
	int					nMinimum,
	int					nMaximum
)
{
	// Default result is failure
	bool bResult = false;

	// The passed string should be numeric
	if (IsNumeric(strString))
	{
		// Convert the string to a number
		int nNumber = StrToInt(strString);	

		// Check the boundaries
		if ((nNumber >= nMinimum) && (nNumber <= nMaximum))
		{
			// Result is ok
			bResult = true;
		}
	}

	return bResult;
}

//						=================
int						KeyDate::StrToInt
//						=================
(
	const string&		s
)
{
	int n;

	istringstream iss(s);

	// Get integer from the stream
	iss >> n;

	return n;
}

//						=================
string					KeyDate::IntToStr
//						=================
(
	int					n
)
{
	ostringstream oss;
	
	// Put the integer in the stream
	oss << n;
	
	return oss.str();
}

//						================
int						KeyDate::GetYear
//						================
(
	const string&		strYear,
	const string&		strFormat
)
{
	// Default result is failure
	int nYear = 0;

	if (IsValidYear(strYear, strFormat))
	{
		// Convert the string to an integer
		nYear = StrToInt(strYear);

		// Add 2000 for the small format "YY"
		if (strFormat == "YY")
		{
			nYear = YEAR2000 + nYear;
		}
	}

	return nYear;
}

//						=================
KeyDate::MONTH			KeyDate::GetMonth
//						=================
(
	const string&		strMonth
)
{
	// Default result is failure
	MONTH mMonth = ILLEGAL;

	if (IsValidMonth(strMonth))
	{
		// Calculate the offset between the enumeration and the
		// month numbers
		int nOffset = JAN - 1;

		// Retrieve the month number
		int nMonth = StrToInt(strMonth);
		
		// Convert the month number to the enumaration value
		mMonth = (MONTH) (nMonth + nOffset);
	}

	return mMonth;
}

//						========================
int						KeyDate::GetNumberOfDays
//						========================
(
	MONTH				mMonth,
	int					nYear
)
{
	// Default result is failure
	int nDays = 0;

	switch(mMonth)
	{
		case JAN:
		case MAR:
		case MAY:
		case JUL:
		case AUG:
		case OCT:
		case DEC:
		{
			// January, March, May, July, August, October and December all
			// have 31 days
			nDays = 31;
			break;
		}
		case FEB:
		{
			// February is a special case
			if (IsLeapYear(nYear))
			{
				// Leap year: February has 29 days
				nDays = 29;
			}
			else
			{
				// Leap year: February has 28 days
				nDays = 28;
			}
			break;
		}
		case APR:
		case JUN:
		case SEP:
		case NOV:
		{
			// April, June, September and November all have 30 days
			nDays = 30;
			break;
		}
		case ILLEGAL:
		default:
		{
			// Error, return 0
			break;
		}
	}

	return nDays;
}

//						===================
bool					KeyDate::IsLeapYear
//						===================
(
	int					nYear
)
{
	///////////////////////////////////////////////////////////////////////////
	// Leap years
	//
	// Every 4th year is a leap year
	//
	// Exceptions
	// - Every 100th year IS NOT a leap year
	// - Every 400th year IS a leap year
	///////////////////////////////////////////////////////////////////////////

	// Default result is failure
	bool bResult = false;

	if (nYear > 0)
	{
		if ((nYear % 400) == 0)
		{
			// Multiple of 400
			bResult = true;
		}
		else if (((nYear % 4) == 0) && ((nYear % 100) != 0))
		{
			// Multiple of 4 and not a multiple of 100
			bResult = true;
		}
	}

	return bResult;
}

//						=======================
string					KeyDate::RetrieveString
//						=======================
(
	const string&		strDate,
	const string&		strFormat,
	const string&		strPartialFormat
)
{
	string strResult;

	// Only search if the lengths are equal
	if (strDate.length() == strFormat.length())
	{
		// Look for the partial format in the format
		string::size_type nPos = strFormat.find(strPartialFormat);

		if (nPos != string::npos)
		{
			// Copy the part of the date
			strResult = strDate.substr(nPos, strPartialFormat.length());
		}
	}

	return strResult;
}

///////////////////////////////////////////////////////////////////////////////
