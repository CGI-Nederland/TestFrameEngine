/*****************************************************************************
 * $Workfile: DateTime.h $
 * $Revision: 1 $
 * $Modtime: 8/22/01 11:54a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef DATETIME_H
#define DATETIME_H

// Includes
#include <map>
#include <string>

using namespace std;

// Forward declarations
class Duration;

////////////////////////////////////////////////////////////////////////////////
// class DateTime

class DateTime
{
// Constants
public:
	// enum of integers specifying months of the year (January to December)
	enum MONTH	{	JAN = 1, FEB, MAR, APR, MAY, JUN,
					JUL, AUG, SEP, OCT, NOV, DEC };

	// enum of integers specifying days of the week (Sunday to Saturday).
	enum WEEKDAY { SUN = 0, MON, TUE, WED, THU, FRI, SAT };

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor
	// date and time members are set to the current machine values
	///////////////////////////////////////////////////////////////////////////////
	DateTime();

	///////////////////////////////////////////////////////////////////////////////
	// constructor
	//
	// parameters	:	nYear		year
	//					nMonth		month
	//					nDay		day
	//					nHour		hour
	//					nMin		minute
	//					nSec		second
	//					nMillisec	millisecond
	///////////////////////////////////////////////////////////////////////////////
	DateTime( int nYear, int nMonth, int nDay, int nHour, int nMin, int nSec, int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// destructor
	///////////////////////////////////////////////////////////////////////////////
	~DateTime();

	// N.B. the copy constructor is allowed and its default implementation is used.

// Operators
public:
	///////////////////////////////////////////////////////////////////////////////
	// operator		:	-
	//
	// description	:	This operator subtracts two DateTime objects. The result
	//					is a Duration object specifying the time difference between
	//					the two.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	Duration object specifying time difference
	///////////////////////////////////////////////////////////////////////////////		
	Duration operator -( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	==
	//
	// description	:	This is the equality operator of two DateTime objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of both object are the same
	//					false	date/time of both object are not the same
	///////////////////////////////////////////////////////////////////////////////		
	bool operator ==( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	!=
	//
	// description	:	This is the inequality operator of two DateTime objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of both object are not the same
	//					false	date/time of both object are the same
	///////////////////////////////////////////////////////////////////////////////		
	bool operator !=( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	<
	//
	// description	:	This is the 'less than' operator of two DateTime objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of left operand is before that of the
	//							right operand
	//					false	date/time of left operand is not before that of
	//							the right operand
	///////////////////////////////////////////////////////////////////////////////		
	bool operator <( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	<=
	//
	// description	:	This is the 'less than or equal to' operator of two
	//					DateTime objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of left operand is before or the same as
	//							that of the right operand
	//					false	date/time of left operand is not before and not the
	//							same as that of the right operand
	///////////////////////////////////////////////////////////////////////////////		
	bool operator <=( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	>
	//
	// description	:	This is the 'greater than' operator of two DateTime
	//					objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of left operand is after that of the
	//							right operand
	//					false	date/time of left operand is not after that of
	//							the right operand
	///////////////////////////////////////////////////////////////////////////////		
	bool operator >( const DateTime& dtRight );

	///////////////////////////////////////////////////////////////////////////////
	// operator		:	>=
	//
	// description	:	This is the 'greater than or equal to' operator of two
	//					DateTime objects.
	//
	// parameters	:	dtRight		right operand DateTime object
	//
	// returns		:	true	date/time of left operand is after or the same as
	//							that of the right operand
	//					false	date/time of left operand is not after and not the
	//							same as that of the right operand
	///////////////////////////////////////////////////////////////////////////////		
	bool operator >=( const DateTime& dtRight );

// Public interface
public: 
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Set()
	//
	// description	:	This function sets the date/time members to the current
	//					machine values.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void Set();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Set()
	//
	// description	:	This function sets the date/time members to the values
	//					specified; only if all of them are valid.
	//
	// parameters	:	nYear		year
	//					nMonth		month
	//					nDay		day
	//					nHour		hour
	//					nMin		minute
	//					nSec		second
	//					nMillisec	millisecond
	//
	// returns		:	true	values set
	//					false	values not set; one or more specified are invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool Set( int nYear, int nMonth, int nDay,
			  int nHour, int nMin, int nSec, int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeDate()
	//
	// description	:	This function changes the values of the year, month and day
	//					to the value specified, if their combination make a valid
	//					date.
	//
	// parameters	:	nYear		year
	//					nMonth		month
	//					nDay		day
	//
	// returns		:	true	values of year, month, and day set
	//					false	values of year, month, and day not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeDate( int nYear, int nMonth, int nDay );
	
	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeYear()
	//
	// description	:	This function changes the value of the year to the value
	//					specified, if it is valid.
	//
	// parameters	:	nYear		year
	//
	// returns		:	true	value of year set
	//					false	value of year not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeYear( int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeMonth()
	//
	// description	:	This function changes the value of the month to the value
	//					specified, if it is valid.
	//
	// parameters	:	nMonth		month
	//
	// returns		:	true	value of month set
	//					false	value of month not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeMonth( int nMonth );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeDay()
	//
	// description	:	This function changes the value of the day to the value
	//					specified, if it is valid.
	//
	// parameters	:	nDay		day
	//
	// returns		:	true	value of day set
	//					false	value of day not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeDay( int nDay );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeHour()
	//
	// description	:	This function changes the value of the hour to the value
	//					specified, if it is valid.
	//
	// parameters	:	nHour		hour
	//
	// returns		:	true	value of hour set
	//					false	value of hour not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeHour( int nHour );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeMin()
	//
	// description	:	This function changes the value of the minute to the value
	//					specified, if it is valid.
	//
	// parameters	:	nMin		minute
	//
	// returns		:	true	value of minute set
	//					false	value of minute not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeMin( int nMin );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeSec()
	//
	// description	:	This function changes the value of the second to the value
	//					specified, if it is valid.
	//
	// parameters	:	nSec		second
	//
	// returns		:	true	value of second set
	//					false	value of second not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeSec( int nSec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	ChangeMillisec()
	//
	// description	:	This function changes the value of the millisecond to the
	//					value specified, if it is valid.
	//
	// parameters	:	nMillisec		millisecond
	//
	// returns		:	true	value of millisecond set
	//					false	value of millisecond not set
	///////////////////////////////////////////////////////////////////////////////		
	bool ChangeMillisec( int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetYear()
	//
	// description	:	This function returns the value of the year.
	//
	// parameters	:	-
	//
	// returns		:	value of the year
	///////////////////////////////////////////////////////////////////////////////		
	int GetYear() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetMonth()
	//
	// description	:	This function returns the value of the month.
	//
	// parameters	:	-
	//
	// returns		:	value of the month
	///////////////////////////////////////////////////////////////////////////////		
	int GetMonth() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetDay()
	//
	// description	:	This function returns the value of the day.
	//
	// parameters	:	-
	//
	// returns		:	value of the day
	///////////////////////////////////////////////////////////////////////////////		
	int GetDay() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetHour()
	//
	// description	:	This function returns the value of the hour.
	//
	// parameters	:	-
	//
	// returns		:	value of the hour
	///////////////////////////////////////////////////////////////////////////////		
	int GetHour() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetMin()
	//
	// description	:	This function returns the value of the minute.
	//
	// parameters	:	-
	//
	// returns		:	value of the minute
	///////////////////////////////////////////////////////////////////////////////		
	int GetMin() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetSec()
	//
	// description	:	This function returns the value of the second.
	//
	// parameters	:	-
	//
	// returns		:	value of the second
	///////////////////////////////////////////////////////////////////////////////		
	int GetSec() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetMillisec()
	//
	// description	:	This function returns the value of the millisecond.
	//
	// parameters	:	-
	//
	// returns		:	value of the millisecond
	///////////////////////////////////////////////////////////////////////////////		
	int GetMillisec() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Get()
	//
	// description	:	This function returns the date/time as a string in the
	//					format as given by the asctime() function from <time>.
	//					An example: Fri Aug 03 14:25:08 2001.
	//					Should the date be out of range for asctime(), an empty
	//					string i sreturned.
	//
	// parameters	:	-
	//
	// returns		:	date/time string
	///////////////////////////////////////////////////////////////////////////////		
	string Get();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Get()
	//
	// description	:	This function returns the date/time as a string in the
	//					specified format; the following tokens can be used in this
	//					format:
	//						YYYY	year in four digits
	//						YY		year in two digits (no century)
	//						M		month without leading zero
	//						MM		month in two digits
	//						D		day without leading zero
	//						DD		day in two digits
	//						h		hour without leading zero
	//						hh		hour in two digits
	//						m		minute without leading zero
	//						mm		minute in two digits
	//						s		second without leading zero
	//						ss		second in two digits
	//						n		millisecond without leading zero
	//						nnn		millisecond in three digits
	//
	// parameters	:	-
	//
	// returns		:	date/time string in specified format
	///////////////////////////////////////////////////////////////////////////////		
	string Get( const string& strFormat );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Add()
	//
	// description	:	This function adds years, months, days, hours, minutes,
	//					seconds, and milliseconds to the object; each of specified
	//					values may be positive, zero, or negative (negative being
	//					subtraction).
	//
	// parameters	:	nYear		years
	//					nMonth		months
	//					nDay		days
	//					nHour		hours
	//					nMin		minutes
	//					nSec		seconds
	//					nMillisec	milliseconds
	//
	// returns		:	true	values added
	//					false	values could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool Add( int nYear, int nMonth, int nDay,
			  int nHour, int nMin, int nSec, int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddYear()
	//
	// description	:	This function adds years to the object; this value may be
	//					positive, zero, or negative (negative being	subtraction).
	//
	// parameters	:	nYear		years
	//
	// returns		:	true	years added
	//					false	years could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddYear( int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddMonth()
	//
	// description	:	This function adds months to the object; this value may be
	//					positive, zero, or negative (negative being	subtraction).
	//
	// parameters	:	nMonth		months
	//
	// returns		:	true	months added
	//					false	months could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddMonth( int nMonth );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddDay()
	//
	// description	:	This function adds days to the object; this value may be
	//					positive, zero, or negative (negative being	subtraction).
	//
	// parameters	:	nDay		days
	//
	// returns		:	true	days added
	//					false	days could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddDay( int nDay );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddHour()
	//
	// description	:	This function adds hours to the object; this value may be
	//					positive, zero, or negative (negative being subtraction).
	//
	// parameters	:	nHour		hours
	//
	// returns		:	true	hours added
	//					false	hours could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddHour( int nHour );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddMin()
	//
	// description	:	This function adds minutes to the object; this value may be
	//					positive, zero, or negative (negative being	subtraction).
	//
	// parameters	:	nMin		minutes
	//
	// returns		:	true	minutes added
	//					false	minutes could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddMin( int nMin );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddSec()
	//
	// description	:	This function adds seconds to the object; this value may be
	//					positive, zero, or negative (negative being subtraction).
	//
	// parameters	:	nSec		seconds
	//
	// returns		:	true	seconds added
	//					false	seconds could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddSec( int nSec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	AddMillisec()
	//
	// description	:	This function adds milliseconds to the object; this value
	//					may be positive, zero, or negative (negative being
	//					subtraction).
	//
	// parameters	:	nMillisec		milliseconds
	//
	// returns		:	true	milliseconds added
	//					false	milliseconds could not be added
	///////////////////////////////////////////////////////////////////////////////		
	bool AddMillisec( int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetDayOfWeek()
	//
	// description	:	This function returns the day of the week which is
	//					specified by this object's date.
	//
	// parameters	:	-
	//
	// returns		:	enum WEEKDAY integer specifying day of the week
	///////////////////////////////////////////////////////////////////////////////		
	WEEKDAY GetDayOfWeek();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DaylightSavingTime()
	//
	// description	:	This function specifies whether or not the date/time lies
	//					within daylight saving time.
	//
	// parameters	:	-
	//
	// returns		:	true	lies in daylight saving time
	//					false	does not lie in daylight saving time
	///////////////////////////////////////////////////////////////////////////////		
	bool DaylightSavingTime();

// Implementation		
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	InstantiateDaysInMonth()
	//
	// description	:	This function fills the map with the number of days in
	//					each month.
	//
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////		
	void InstantiateDaysInMonth();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckYear()
	//
	// description	:	This function checks whether the specified number is a
	//					valid year; i.e. whether it is greater than 0.
	//
	// parameters	:	nYear	year to check
	//
	// returns		:	true	year valid
	//					false	year invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckYear( int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckMonth()
	//
	// description	:	This function checks whether the specified number is a
	//					valid month; i.e. whether it is lies within JAN to DEC.
	//
	// parameters	:	nMonth	month to check
	//
	// returns		:	true	month valid
	//					false	month invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckMonth( int nMonth );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckDay()
	//
	// description	:	This function checks whether the specified number is a
	//					valid day, given its month and year; i.e. whether it is
	//					greater than 0 and no greater than the maximum days of its
	//					month; the year is taken into account, because in leap
	//					years 29 FEB is allowed.
	//
	// parameters	:	nDay		day to check
	//					nMonth		month
	//					nYear		year
	//
	// returns		:	true	day valid
	//					false	day invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckDay( int nDay, int nMonth, int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckHour()
	//
	// description	:	This function checks whether the specified number is a
	//					valid hour; i.e. whether it lies in the range [0..23].
	//
	// parameters	:	nHour	hour to check
	//
	// returns		:	true	hour valid
	//					false	hour invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckHour( int nHour );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckMin()
	//
	// description	:	This function checks whether the specified number is a
	//					valid minute; i.e. whether it lies in the range [0..59].
	//
	// parameters	:	nMin	minute to check
	//
	// returns		:	true	minute valid
	//					false	minute invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckMin( int nMin );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckSec()
	//
	// description	:	This function checks whether the specified number is a
	//					valid second; i.e. whether it lies in the range [0..59].
	//
	// parameters	:	nSec	second to check
	//
	// returns		:	true	second valid
	//					false	second invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckSec( int nSec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	CheckMillisec()
	//
	// description	:	This function checks whether the specified number is a
	//					valid millisecond; i.e. whether it lies in the range
	//					[0..999].
	//
	// parameters	:	nMillisec	millisecond to check
	//
	// returns		:	true	millisecond valid
	//					false	millisecond invalid
	///////////////////////////////////////////////////////////////////////////////		
	bool CheckMillisec( int nMillisec );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	LeapYear()
	//
	// description	:	This function checks whether the specified year is a
	//					leap year.
	//
	// parameters	:	nYear	year to check for leap year
	//
	// returns		:	true	is a leap year
	//					false	is not a leap year
	///////////////////////////////////////////////////////////////////////////////		
	bool LeapYear( int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DateToDays()
	//
	// description	:	This function converts a date (year/month/day) to a number
	//					of days (taken from 01-01-0001).
	//
	// parameters	:	nYear		year
	//					nMonth		month
	//					nDay		day
	//
	// returns		:	number of days
	///////////////////////////////////////////////////////////////////////////////		
	long DateToDays( int nYear, int nMonth, int nDay );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	DaysToDate()
	//
	// description	:	This function converts a number of days (taken from
	//					01-01-0001) to a date; this date (year, month, and day) is
	//					placed in the referenced parameters.
	//
	// parameters	:	lDays			number of days
	//					REF nYear		year
	//					REF nMonth		month
	//					REF nDay		day
	//
	// returns		:	true	days are converted to date
	//					false	days could not be converted to date
	///////////////////////////////////////////////////////////////////////////////		
	bool DaysToDate( long lDays, int& nYear, int& nMonth, int& nDay );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	StartOfDST()
	//
	// description	:	This function returns a DateTime object which represents
	//					the start of daylight saving time for the specified year.
	//
	// parameters	:	nYear		year for which to determine start of DST
	//
	// returns		:	DateTime object giving start of DST
	///////////////////////////////////////////////////////////////////////////////		
	DateTime StartOfDST( int nYear );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	EndOfDST()
	//
	// description	:	This function returns a DateTime object which represents
	//					the end of daylight saving time for the specified year.
	//
	// parameters	:	nYear		year for which to determine end of DST
	//
	// returns		:	DateTime object giving end of DST
	///////////////////////////////////////////////////////////////////////////////		
	DateTime EndOfDST( int nYear );

// Member variables
private:
	int m_nYear;		// Year ( > 0 )
	int m_nMonth;		// Month (1 - 12)
	int m_nDay;			// Day (1 - 31)
	int m_nHour;		// Hour (0 - 23)
	int m_nMin;			// Minute (0 - 59)
	int m_nSec;			// Second (0 - 59)
	int m_nMillisec;	// Millisecond (0 - 999)

	static map<int, int> m_mDaysInMonth;	// Map of number of days in each month
};

////////////////////////////////////////////////////////////////////////////////

#endif // !DATETIME_H
 