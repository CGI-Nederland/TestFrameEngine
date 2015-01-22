/*****************************************************************************
 * $Workfile: KeyDate.h $
 * $Revision: 1 $
 * $Modtime: 1-05-01 17:42 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef KEYDATE_H
#define KEYDATE_H

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class Date

class KeyDate
{
// Construction and destruction
public:
	KeyDate();
	~KeyDate();

	enum MONTH { JAN, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC, ILLEGAL };

// Public methods
public:
	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidDate
	// Description: This function checks the format of the passed date, 
	//				compared to the supplied format. (YYMMDD etc.)
	//
	// Parameters:	strDate		Date to check
	//				strFormat	Date format
	//
	// Returns:		true	Date correct
	//				false	Date incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidDate(const string& strDate, const string& strFormat);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidYear
	// Description: This function checks the format of the passed year, 
	//				compared to the supplied format. (YYMMDD etc.)
	//
	// Parameters:	strYear		Year to check
	//				strFormat	Date format
	//
	// Returns:		true	Year correct
	//				false	Year incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidYear(const string& strYear, const string& strFormat);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidMonth
	// Description: This function checks the format of the passed month. 
	//
	// Parameters:	strMonth	Month to check
	//
	// Returns:		true	Month correct
	//				false	Month incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidMonth(const string& strMonth);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidDay
	// Description: This function checks the format of the passed day, 
	//				in relation to the supplied month and year(format).
	//
	// Parameters:	strDay			Day to check
	//				strMonth		Month to check day in
	//				strYear			Year to check day in
	//				strYearFormat	Date format
	//
	// Returns:		true	Day correct
	//				false	Day incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidDay(const string& strDay, const string& strMonth, const string& strYear, const string& strYearFormat);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidHour
	// Description: This function checks the format of the passed hour.
	//
	// Parameters:	strHour		Hour to check
	//
	// Returns:		true	Hour correct
	//				false	Hour incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidHour(const string& strHour);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidMinutes
	// Description: This function checks the format of the passed minutes.
	//
	// Parameters:	strMinutes	Minutes to check
	//
	// Returns:		true	Minutes correct
	//				false	Minutes incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidMinutes(const string& strMinutes);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsValidSeconds
	// Description: This function checks the format of the passed seconds.
	//
	// Parameters:	strSeconds	Seconds to check
	//
	// Returns:		true	Seconds correct
	//				false	Seconds incorrect
	///////////////////////////////////////////////////////////////////////////
	static bool IsValidSeconds(const string& strSeconds);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveYear
	// Description: This function retrieves the numerical value of the 
	//				year from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nYear		Year value				(Out)
	//
	// Returns:		true	Year retrieved
	//				false	Year not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveYear(const string& strDate, const string& strFormat, int& nYear);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveMonth
	// Description: This function retrieves the numerical value of the 
	//				month from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nMonth		Month value				(Out)
	//
	// Returns:		true	Month retrieved
	//				false	Month not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveMonth(const string& strDate, const string& strFormat, int& nMonth);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveDay
	// Description: This function retrieves the numerical value of the 
	//				day from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nDay		Day value				(Out)
	//
	// Returns:		true	Day retrieved
	//				false	Day not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveDay(const string& strDate, const string& strFormat, int& nDay);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveHour
	// Description: This function retrieves the numerical value of the 
	//				hour from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nHour		Hour value				(Out)
	//
	// Returns:		true	Hour retrieved
	//				false	Hour not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveHour(const string& strDate, const string& strFormat, int& nHours);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveMinutes
	// Description: This function retrieves the numerical value of the 
	//				minutes from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nMinutes	Minutes value			(Out)
	//
	// Returns:		true	Minutes retrieved
	//				false	Minutes not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveMinutes(const string& strDate, const string& strFormat, int& nMinutes);

	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveSeconds
	// Description: This function retrieves the numerical value of the 
	//				seconds from the given date string, using the format string.
	//
	// Parameters:	strDate		Date string				(In)
	//				strFormat	Date format				(In)
	//				nSeconds	Seconds value			(Out)
	//
	// Returns:		true	Seconds retrieved
	//				false	Seconds not retrieved
	///////////////////////////////////////////////////////////////////////////
	static bool RetrieveSeconds(const string& strDate, const string& strFormat, int& nSeconds);


// Implementation
private:
	///////////////////////////////////////////////////////////////////////////
	// Function:	GetMonth
	// Description: This function retrieves the numerical value of the 
	//				month that is passed a string.
	//
	// Parameters:	strMonth	Month string			(In)
	//
	// Returns:		Number of the month
	///////////////////////////////////////////////////////////////////////////
	static enum MONTH GetMonth(const string& strMonth);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetYear
	// Description: This function retrieves the numerical value of the 
	//				year that is passed a string. The year format is also 
	//				passed as a string (YY or YYYY);
	//
	// Parameters:	strYear		Year string				(In)
	//				strFormat	Year format				(In)
	//
	// Returns:		Numerical year
	///////////////////////////////////////////////////////////////////////////
	static int GetYear(const string& strYear, const string& strFormat);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetNumberOfDays
	// Description: This function retrieves the number of days in the given 
	//				month (specified by a month and a year).
	//
	// Parameters:	mMonth		Month					(In)
	//				nYear		Year					(In)
	//
	// Returns:		Number of days in the given month
	///////////////////////////////////////////////////////////////////////////
	static int GetNumberOfDays(MONTH mMonth, int nYear);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	IsLeapYear
	// Description: This function returns whether or not the given year is 
	//				a leap year.
	//
	// Parameters:	nYear		Year					(In)
	//
	// Returns:		true		Year is a leap year
	//				false		Year is not a leap year
	///////////////////////////////////////////////////////////////////////////
	static bool IsLeapYear(int nYear);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IsNumeric
	// Description: This function returns whether or not the given string 
	//				represents a numerical value.
	//
	// Parameters:	strString	String to evaluate		(In)
	//
	// Returns:		true		String is numerical
	//				false		String is not numerical
	///////////////////////////////////////////////////////////////////////////
	static bool IsNumeric(const string& strString);

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckBoundaries
	// Description: This function returns whether or not the given numerical 
	//				string lies in the specified interval [nMinimum, nMaximum].
	//
	// Parameters:	strString	String to evaluate			(In)
	//				nMinimum	Lower boundary of interval	(In)
	//				nMaximum	Upper boundary of interval	(In)
	//
	// Returns:		true		String is numerical and lies in interval
	//				false		String is not numerical or not in interval
	///////////////////////////////////////////////////////////////////////////
	static bool CheckBoundaries(const string& strString, int nMinimum,	int nMaximum);

	///////////////////////////////////////////////////////////////////////////
	// Function:	StrToInt
	// Description: This function converts the given string to an integer 
	//				if this is possible.
	//
	// Parameters:	s			String to convert			(In)
	//
	// Returns:		Numerical value of the string (if conversion is 
	//				possible, otherwise zero is returned)
	///////////////////////////////////////////////////////////////////////////
	static int StrToInt(const string& s);

	///////////////////////////////////////////////////////////////////////////
	// Function:	IntToStr
	// Description: This function converts the given integer to a string 
	//
	// Parameters:	n			Integer to convert			(In)
	//
	// Returns:		String conversion of the integer
	///////////////////////////////////////////////////////////////////////////
	static string IntToStr(int n);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	RetrieveString
	// Description: This function retrieves the equivalent substring of the 
	//				given date string compared to the given format and partial 
	//				format.
	//
	// Parameters:	strDate				String to retrieve substring from	(In)
	//				strFormat			Format to use						(In)
	//				strPartialFormat	Partial format to use				(In)
	//
	// Returns:		Substring
	///////////////////////////////////////////////////////////////////////////
	static string RetrieveString(const string& strDate, const string& strFormat, const string& strPartialFormat);
};

///////////////////////////////////////////////////////////////////////////////

#endif	// !KEYDATE_H
