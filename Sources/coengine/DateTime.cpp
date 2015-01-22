/*****************************************************************************
 * $Workfile: DateTime.cpp $
 * $Revision: 1 $
 * $Modtime: 8/22/01 11:57a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

// Includes
#include "DateTime.h"		// Class definition

#include <map>
#include <string>
#include <sys/timeb.h>
#include <time.h>

using namespace std;

#include "Duration.h"
#include "StrUtil.h"

// Defines
#define EARLIEST_YEAR		1
#define DAYS_IN_YEAR		365
#define MONTHS_IN_YEAR		12
#define LEAP_YEAR			4
#define CENTURY				100
#define LEAP_CENTURY		400
#define MAX_MS				1000
#define MAX_SEC				60
#define MAX_MIN				60
#define MAX_HOUR			24
#define DAYS_IN_WEEK		7
#define WEEKDAY_CALIBRATION	1
#define YEAR_4_TOKEN		string( "YYYY" )
#define YEAR_2_TOKEN		string( "YY" )
#define MONTH_TOKEN			string( "M" )
#define MONTH_PAD_TOKEN		string( "MM" )
#define DAY_TOKEN			string( "D" )
#define DAY_PAD_TOKEN		string( "DD" )
#define HOUR_TOKEN			string( "h" )
#define HOUR_PAD_TOKEN		string( "hh" )
#define MIN_TOKEN			string( "m" )
#define MIN_PAD_TOKEN		string( "mm" )
#define SEC_TOKEN			string( "s" )
#define SEC_PAD_TOKEN		string( "ss" )
#define MS_TOKEN			string( "n" )
#define MS_PAD_TOKEN		string( "nnn" )

///////////////////////////////////////////////////////////////////////////////

// Instantiate static member
map<int, int> DateTime::m_mDaysInMonth;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==================
						DateTime::DateTime()
//						==================
{
	// Fill the map with the number of days in each month.
	InstantiateDaysInMonth();
	
	// Set the date and time members to the current machine values.
	Set();
}


//						==================
						DateTime::DateTime
//						==================
(
	int					nYear,
	int					nMonth,
	int					nDay,
	int					nHour,
	int					nMin,
	int					nSec,
	int					nMillisec
)
{
	// Fill the map with the number of days in each month.
	InstantiateDaysInMonth();

	// Set the date and time members to the values specified; determine
	// if this failed.
	if ( !Set( nYear, nMonth, nDay, nHour, nMin, nSec, nMillisec ) )
	{
		// Set the date and time members to the current machine values.
		Set();
	}
}


//						===================
						DateTime::~DateTime()
//						===================
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Operators

//						====================
Duration				DateTime::operator -
//						====================
(
	const DateTime&		dtRight
)
{
	// Copy the right operand.
	DateTime dt = dtRight;
	
	// Make Duration objects for the left operand (this DateTime object)
	// and the right operand; first, get the total number of days for the
	// dates (year/month/day).
	long lDaysLeft = DateToDays( m_nYear, m_nMonth, m_nDay );
	long lDaysRight = DateToDays( dt.GetYear(), dt.GetMonth(), dt.GetDay() );

	// Get, besides de number of days, also the hours, minutes, seconds, and
	// milliseconds; create the Duration objects.
	Duration durLeft( lDaysLeft, m_nHour, m_nMin, m_nSec, m_nMillisec );
	Duration durRight( lDaysRight, dt.GetHour(), dt.GetMin(), dt.GetSec(), dt.GetMillisec() );

	// Subtract the right Duration from the left one.
	Duration durResult = durLeft - durRight;

	// Determine if a correction due to daylight saving time (dst) must be made.
	// First, determine for both dates whether they are in dst.
	bool bDSTLeft = DaylightSavingTime();
	bool bDSTRight = dt.DaylightSavingTime();

	// Subtract one hour of the duration if the left operand lies in DST and
	// the right one not.
	if ( bDSTLeft && !bDSTRight )
	{
		Duration durCorrection( 0, 1, 0, 0, 0 );
		durResult = durResult - durCorrection;
	}
	// Add one hour of the duration if the left operand lies not in DST and
	// the right one does.
	else if ( !bDSTLeft && bDSTRight )
	{
		Duration durCorrection( 0, 1, 0, 0, 0 );
		durResult = durResult + durCorrection;
	}

	return durResult;
}


//						=====================
bool					DateTime::operator ==
//						=====================
(
	const DateTime&		dtRight
)
{
	bool bResult = false;

	// Compare for both DateTime objects (this one and the one specified by
	// the parameter: year, month, day, hour, minute, second, and millisecond;
	// return true, only if all match.
	if ( (m_nYear == dtRight.GetYear()) && (m_nMonth == dtRight.GetMonth()) &&
		 (m_nDay == dtRight.GetDay()) && (m_nHour == dtRight.GetHour()) &&
		 (m_nMin == dtRight.GetMin()) && (m_nSec == dtRight.GetSec()) &&
		 (m_nMillisec == dtRight.GetMillisec()) )
	{
		bResult = true;
	}

	return bResult;
}


//						=====================
bool					DateTime::operator !=
//						=====================
(
	const DateTime&		dtRight
)
{
	// Return the reverse value of the == operation on this DateTime object
	// and the one specified by the parameter.
	return ( !(*this == dtRight) );
}


//						====================
bool					DateTime::operator <
//						====================
(
	const DateTime&		dtRight
)
{
	bool bResult = false;

	int nLeft[] = { m_nYear, m_nMonth, m_nDay, m_nHour, m_nMin, m_nSec, m_nMillisec };
	int nRight[] = { dtRight.GetYear(), dtRight.GetMonth(), dtRight.GetDay(), dtRight.GetHour(),
		dtRight.GetMin(), dtRight.GetSec(), dtRight.GetMillisec() };

	int nElem = 0;
	bool bFinished = false;
	for ( ; (nElem < 7) && !bFinished; nElem++ )
	{
		if ( nLeft[nElem] > nRight[nElem] )
		{
			bFinished = true;
		}
		else if ( nLeft[nElem] < nRight[nElem] )
		{
			bFinished = true;
			bResult = true;
		}
	}

	return bResult;
}


//						=====================
bool					DateTime::operator <=
//						=====================
(
	const DateTime&		dtRight
)
{
	DateTime dt = dtRight;
	return ( !(dt < *this) );
}


//						====================
bool					DateTime::operator >
//						====================
(
	const DateTime&		dtRight
)
{
	DateTime dt = dtRight;
	return ( dt < *this );
}


//						=====================
bool					DateTime::operator >=
//						=====================
(
	const DateTime&		dtRight
)
{
	return ( !(*this < dtRight) );
}


///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=============
void					DateTime::Set()
//						=============
{
	// Set the members to the current date/time.
	// Determine the current millisecond; use the struct _timeb to do this;
	// store in the millisecond member.
	struct _timeb timebuffer;   
	_ftime( &timebuffer );
	m_nMillisec = timebuffer.millitm;

	// Determine the year, month, day, hour, minute, and second; use the
	// struct tm to do this; store their values in members.
	struct tm tmTime;
	time_t aclock;
	time( &aclock );					// system time in seconds
	tmTime = *localtime( &aclock );		// convert time to tm struct
	m_nYear = tmTime.tm_year + 1900;
	m_nMonth = tmTime.tm_mon + 1;
	m_nDay = tmTime.tm_mday;
	m_nHour = tmTime.tm_hour;
	m_nMin = tmTime.tm_min;
	m_nSec = tmTime.tm_sec;
}


//						=============
bool					DateTime::Set
//						=============
(
	int					nYear,
	int					nMonth,
	int					nDay,
	int					nHour,
	int					nMin,
	int					nSec,
	int					nMillisec
)
{
	bool bResult = false;

	// Check if all specified time-parameters are valid ones.
	if ( CheckYear( nYear ) && CheckMonth( nMonth ) &&
		 CheckDay( nDay, nMonth, nYear ) && CheckHour( nHour ) &&
		 CheckMin( nMin ) && CheckSec( nSec ) && CheckMillisec( nMillisec ) )
	{
		// Set the time-members to the specified values.
		m_nYear = nYear;
		m_nMonth = nMonth;
		m_nDay = nDay;
		m_nHour = nHour;
		m_nMin = nMin;
		m_nSec = nSec;
		m_nMillisec = nMillisec;
		bResult = true;
	}

	return bResult;
}


//						====================
bool					DateTime::ChangeDate
//						====================
(
	int					nYear,
	int					nMonth,
	int					nDay
)
{
	bool bResult = false;

	// Check if the specified combination of day, month, and year is a
	// valid one.
	if ( CheckDay( nDay, nMonth, nYear ) )
	{
		// Set the values of year, month, and day to those specified.
		m_nYear = nYear;
		m_nMonth = nMonth;
		m_nDay = nDay;
		bResult = true;
	}

	return bResult;
}


//						====================
bool					DateTime::ChangeYear
//						====================
(
	int					nYear
)
{
	bool bResult = false;

	// Check if the specified year is a valid one.
	if ( CheckYear( nYear ) )
	{
		m_nYear = nYear;
		bResult = true;
	}

	return bResult;
}


//						=====================
bool					DateTime::ChangeMonth
//						=====================
(
	int					nMonth
)
{
	bool bResult = false;

	// Check if the specified month is a valid one, by checking if the old day
	// and old year go together with this new month.
	if ( CheckDay( m_nDay, nMonth, m_nYear ) )
	{
		m_nMonth = nMonth;
		bResult = true;
	}

	return bResult;
}


//						===================
bool					DateTime::ChangeDay
//						===================
(
	int					nDay
)
{
	bool bResult = false;

	// Check if the specified day is a valid one; take as the month and year
	// the already specified values
	if ( CheckDay( nDay, m_nMonth, m_nYear ) )
	{
		m_nDay = nDay;
		bResult = true;
	}

	return bResult;
}


//						====================
bool					DateTime::ChangeHour
//						====================
(
	int					nHour
)
{
	bool bResult = false;

	// Check if the specified hour is a valid one.
	if ( CheckHour( nHour ) )
	{
		m_nHour = nHour;
		bResult = true;
	}

	return bResult;
}


//						===================
bool					DateTime::ChangeMin
//						===================
(
	int					nMin
)
{
	bool bResult = false;

	// Check if the specified minute is a valid one.
	if ( CheckMin( nMin ) )
	{
		m_nMin = nMin;
		bResult = true;
	}

	return bResult;
}


//						===================
bool					DateTime::ChangeSec
//						===================
(
	int					nSec
)
{
	bool bResult = false;

	// Check if the specified second is a valid one.
	if ( CheckSec( nSec ) )
	{
		m_nSec = nSec;
		bResult = true;
	}

	return bResult;
}


//						========================
bool					DateTime::ChangeMillisec
//						========================
(
	int					nMillisec
)
{
	bool bResult = false;

	// Check if the specified millisecond is a valid one.
	if ( CheckMillisec( nMillisec ) )
	{
		m_nMillisec = nMillisec;
		bResult = true;
	}

	return bResult;
}


//						=================
int						DateTime::GetYear() const
//						=================
{
	return m_nYear;
}


//						==================
int						DateTime::GetMonth() const
//						==================
{
	return m_nMonth;
}


//						================
int						DateTime::GetDay() const
//						================
{
	return m_nDay;
}


//						=================
int						DateTime::GetHour() const
//						=================
{
	return m_nHour;
}


//						================
int						DateTime::GetMin() const
//						================
{
	return m_nMin;
}


//						================
int						DateTime::GetSec() const
//						================
{
	return m_nSec;
}


//						=====================
int						DateTime::GetMillisec() const
//						=====================
{
	return m_nMillisec;
}


//						=============
string					DateTime::Get()
//						=============
{
	string strDateTime;

	// convert time struct to a calendar value and check the result
	struct tm tmTime;
	
	tmTime.tm_year = m_nYear - 1900;
	tmTime.tm_mon = m_nMonth - 1;
	tmTime.tm_mday = m_nDay;
	tmTime.tm_hour = m_nHour;
	tmTime.tm_min = m_nMin;
	tmTime.tm_sec = m_nSec;
	tmTime.tm_isdst = -1;

	if ( mktime( &tmTime ) != (time_t) - 1 )
	{
		// convert struct to a string
		strDateTime = string( asctime( &tmTime ) );
	}

	return strDateTime;
}


//						=============
string					DateTime::Get
//						=============
(
	const string&		strFormat
)
{
	// Set the date/time string initially to the specified format.
	string strDT = strFormat;

	// Replace the all tokens by the corresponding numbers; note that the pad-
	// tokens are replaced before the unpadded ones.
	ReplaceToken( strDT, YEAR_4_TOKEN, Pad_front( IntToStr( m_nYear ), 4, '0' ) );
	ReplaceToken( strDT, YEAR_2_TOKEN, Pad_front( IntToStr( m_nYear%100 ), 2, '0' ) );
	ReplaceToken( strDT, MONTH_PAD_TOKEN, Pad_front( IntToStr(m_nMonth), 2, '0' ) );
	ReplaceToken( strDT, MONTH_TOKEN, IntToStr( m_nMonth ) );
	ReplaceToken( strDT, DAY_PAD_TOKEN, Pad_front( IntToStr(m_nDay), 2, '0' ) );
	ReplaceToken( strDT, DAY_TOKEN, IntToStr( m_nDay ) );
	ReplaceToken( strDT, HOUR_PAD_TOKEN, Pad_front( IntToStr(m_nHour), 2, '0' ) );
	ReplaceToken( strDT, HOUR_TOKEN, IntToStr( m_nHour ) );
	ReplaceToken( strDT, MIN_PAD_TOKEN, Pad_front( IntToStr(m_nMin), 2, '0' ) );
	ReplaceToken( strDT, MIN_TOKEN, IntToStr( m_nMin ) );
	ReplaceToken( strDT, SEC_PAD_TOKEN, Pad_front( IntToStr(m_nSec), 2, '0' ) );
	ReplaceToken( strDT, SEC_TOKEN, IntToStr( m_nSec ) );
	ReplaceToken( strDT, MS_PAD_TOKEN, Pad_front( IntToStr(m_nMillisec), 3, '0' ) );
	ReplaceToken( strDT, MS_TOKEN, IntToStr( m_nMillisec ) );

	return strDT;
}


//						=============
bool					DateTime::Add
//						=============
(
	int					nYear,
	int					nMonth,
	int					nDay,
	int					nHour,
	int					nMin,
	int					nSec,
	int					nMillisec
)
{
	bool bResult = true;

	// Initialise the number of days to add to be the number of days specified.
	int nExtraDays = nDay;

	// Store the old time members (hour, min, sec, and millisec).
	int nOldHour = m_nHour;
	int nOldMin = m_nMin;
	int nOldSec = m_nSec;
	int nOldMillisec = m_nMillisec;

	// Determine if either hours, minutes, seconds, and/or milliseconds
	// are to be added or subtracted.
	if ( nHour != 0 || nMin != 0 || nSec != 0 || nMillisec != 0 )
	{
		// Create Duration objects for the specified time of day, and for
		// the number of hours, minutes, seconds, and milliseconds to add.
		Duration durToday( 0, m_nHour, m_nMin, m_nSec, m_nMillisec );
		Duration durHour( 0, nHour, nMin, nSec, nMillisec );

		// Add the two Duration objects.
		Duration durNew = durToday + durHour;

		// Get the new number of hours, minutes, seconds, and milliseconds,
		// and store this in the  corresponding members.
		m_nHour = durNew.GetHour();
		m_nMin = durNew.GetMin();
		m_nSec = durNew.GetSec();
		m_nMillisec = durNew.GetMillisec();

		// Determine if the adding of time went over the day-edge, and, if so,
		// update the number of days to add.
		nExtraDays += durNew.GetDay();
	}

	// Determine if either years, months, and/or days are to be added
	// or subtracted.
	if ( nYear != 0 || nMonth != 0 || nExtraDays != 0 )
	{
		// Determine the total number of days for the new year, month, and day.
		long lDays = DateToDays( m_nYear + nYear, m_nMonth + nMonth, m_nDay + nExtraDays );
		
		// Translate the total number of days back to a date, store this date
		// in the members (if translation was successful), and return the
		// result of the translation.
		bResult = DaysToDate( lDays, m_nYear, m_nMonth, m_nDay );

		// Determine if the date could not be calculated; in that case,
		// restore the old time members, so the state of this object is
		// unchanged if this operation fails.
		if ( !bResult )
		{
			m_nHour = nOldHour;
			m_nMin = nOldMin;
			m_nSec = nOldSec;
			m_nMillisec = nOldMillisec;
		}
	}

	return bResult;
}


//						=================
bool					DateTime::AddYear
//						=================
(
	int					nYear
)
{
	bool bResult = true;

	// Determine if there are any years to add (or subtract).
	if ( nYear != 0 )
	{
		// Add the number of years; set all other values to zero.
		bResult = Add( nYear, 0, 0, 0, 0, 0, 0 );
	}

	return bResult;
}


//						==================
bool					DateTime::AddMonth
//						==================
(
	int					nMonth
)
{
	bool bResult = true;

	// Determine if there are any months to add (or subtract).
	if ( nMonth != 0 )
	{
		// Add the number of months; set all other values to zero.
		bResult = Add( 0, nMonth, 0, 0, 0, 0, 0 );
	}

	return bResult;
}


//						================
bool					DateTime::AddDay
//						================
(
	int					nDay
)
{
	bool bResult = true;

	// Determine if there are any days to add (or subtract).
	if ( nDay != 0 )
	{
		// Add the number of days; set all other values to zero.
		bResult = Add( 0, 0, nDay, 0, 0, 0, 0 );
	}

	return bResult;
}


//						=================
bool					DateTime::AddHour
//						=================
(
	int					nHour
)
{
	bool bResult = true;
	
	// Determine if there are any hours to add (or subtract).
	if ( nHour != 0 )
	{
		// Add the number of hours; set all other values to zero.
		bResult = Add( 0, 0, 0, nHour, 0, 0, 0 );
	}

	return bResult;
}


//						================
bool					DateTime::AddMin
//						================
(
	int					nMin
)
{
	bool bResult = true;
	
	// Determine if there are any minutes to add (or subtract).
	if ( nMin != 0 )
	{
		// Add the number of minutes; set all other values to zero.
		bResult = Add( 0, 0, 0, 0, nMin, 0, 0 );
	}

	return bResult;
}


//						================
bool					DateTime::AddSec
//						================
(
	int					nSec
)
{
	bool bResult = true;
	
	// Determine if there are any seconds to add (or subtract).
	if ( nSec != 0 )
	{
		// Add the number of seconds; set all other values to zero.
		bResult = Add( 0, 0, 0, 0, 0, nSec, 0 );
	}

	return bResult;
}


//						=====================
bool					DateTime::AddMillisec
//						=====================
(
	int					nMillisec
)
{
	bool bResult = true;
	
	// Determine if there are any milliseconds to add (or subtract).
	if ( nMillisec != 0 )
	{
		// Add the number of milliseconds; set all other values to zero.
		bResult = Add( 0, 0, 0, 0, 0, 0, nMillisec );
	}

	return bResult;
}


//						======================
DateTime::WEEKDAY		DateTime::GetDayOfWeek()
//						======================
{
	// Turn the date into days.
	long lTotal = DateToDays( m_nYear, m_nMonth, m_nDay );

	// Calculate the day of the week by taking the  the total number of days
	// modulo the number of days in a week; note that a constant is added to
	// the number of days to calibrate the day of the week.
	WEEKDAY nWeekDay = (WEEKDAY) ((lTotal + WEEKDAY_CALIBRATION) % DAYS_IN_WEEK);

	return nWeekDay;
}


//						============================
bool					DateTime::DaylightSavingTime()
//						============================
{
	bool bResult = false;

	// Determine the start- and end-date of daylight saving time for this
	// DateTime's year.
	DateTime dtStart = StartOfDST( m_nYear );
	DateTime dtEnd = EndOfDST( m_nYear );

	// Determine if this DateTime object lies between these dates.
	if ( (*this > dtStart) && (*this < dtEnd) )
	{
		bResult = true;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						================================
void					DateTime::InstantiateDaysInMonth()
//						================================
{
	// Fill the (static) map of days for each month,
	// if hasn't been filled already.
	if ( m_mDaysInMonth.empty() )
	{
		m_mDaysInMonth[JAN] = 31;
		m_mDaysInMonth[FEB] = 28;
		m_mDaysInMonth[MAR] = 31;
		m_mDaysInMonth[APR] = 30;
		m_mDaysInMonth[MAY] = 31;
		m_mDaysInMonth[JUN] = 30;
		m_mDaysInMonth[JUL] = 31;
		m_mDaysInMonth[AUG] = 31;
		m_mDaysInMonth[SEP] = 30;
		m_mDaysInMonth[OCT] = 31;
		m_mDaysInMonth[NOV] = 30;
		m_mDaysInMonth[DEC] = 31;
	}
}


//						===================
bool					DateTime::CheckYear
//						===================
(
	int					nYear
)
{
	bool bResult = false;

	// Determine if the year is after or equal to the earliest allowed year.
	if ( nYear >= EARLIEST_YEAR )
	{
		bResult = true;
	}

	return bResult;
}


//						====================
bool					DateTime::CheckMonth
//						====================
(
	int					nMonth
)
{
	bool bResult = false;

	// Determine if the specified month is a valid one.
	if ( nMonth >= JAN && nMonth <= DEC )
	{
		bResult = true;
	}

	return bResult;
}


//						==================
bool					DateTime::CheckDay
//						==================
(
	int					nDay,
	int					nMonth,
	int					nYear
)
{
	bool bResult = false;

	// Determine if the specified month and year are valid.
	if ( CheckMonth( nMonth ) && CheckYear( nYear ) )
	{
		// Determine the upper-limit of the possible day,
		// which depends on the month.
		int nMaxDay = m_mDaysInMonth[nMonth];

		// Determine if the month is february and the year is a leap year.
		if ( nMonth == FEB && LeapYear( nYear ) )
		{
			// The upper-limit of days is one higher.
			nMaxDay += 1;
		}

		// Determine if the specified day falls within the limits.
		if ( nDay >= 1 && nDay <= nMaxDay )
		{
			bResult = true;
		}
	}

	return bResult;
}


//						===================
bool					DateTime::CheckHour
//						===================
(
	int					nHour
)
{
	bool bResult = false;

	// Determine if the specified hour is a valid one.
	if ( nHour >= 0 && nHour < MAX_HOUR )
	{
		bResult = true;
	}

	return bResult;
}


//						==================
bool					DateTime::CheckMin
//						==================
(
	int					nMin
)
{
	bool bResult = false;

	// Determine if the specified minute is a valid one.
	if ( nMin >= 0 && nMin < MAX_MIN )
	{
		bResult = true;
	}

	return bResult;
}


//						==================
bool					DateTime::CheckSec
//						==================
(
	int					nSec
)
{
	bool bResult = false;

	// Determine if the specified second is a valid one.
	if ( nSec >= 0 && nSec < MAX_SEC )
	{
		bResult = true;
	}

	return bResult;
}


//						=======================
bool					DateTime::CheckMillisec
//						=======================
(
	int					nMillisec
)
{
	bool bResult = false;

	// Determine if the specified millisecond is a valid one.
	if ( nMillisec >= 0 && nMillisec < MAX_MS )
	{
		bResult = true;
	}

	return bResult;
}


//						==================
bool					DateTime::LeapYear
//						==================
(
	int					nYear
)
{
	bool bResult = false;

	// Determine if the specified year is a leap year. A year is a leap year
	// when: it is a multiple of 4 (LEAP_YEAR); excepting ones that are also
	// multiples of 100 (CENTURY), but not of 400 (LEAP_CENTURY).
	if ( (nYear % LEAP_YEAR == 0) && ((nYear % CENTURY != 0) || (nYear % LEAP_CENTURY == 0)) )
	{
		bResult = true;
	}

	return bResult;
}


//						====================
long					DateTime::DateToDays
//						====================
(
	int					nYear,
	int					nMonth,
	int					nDay
)
{
	// Initialise the total number of days to zero.
	long lTotal = 0;

	// Add the number of days (excluding the current one) to the total.
	lTotal = nDay - 1;

	// Normalise the month to the range [JAN - DEC, DEC], and add (or subtract)
	// the extra years to the number specified..
	int nNormMonth = ((nMonth - JAN) % MONTHS_IN_YEAR) + JAN;
	int nNormYear = nYear + ( (nMonth - JAN) / MONTHS_IN_YEAR );

	// Determine if the normalised month actually lies in a previous year; if
	// so, bring the month in the range [JAN, DEC] and subtract a year from
	// its number.
	if ( nNormMonth < JAN )
	{
		nNormMonth += MONTHS_IN_YEAR;
		nNormYear--;
	}

	// Now calculate the number of days in the previous months of the
	// normalised year; first determine if their are any (i.e. if the month
	// is not January).
	if ( nNormMonth > JAN )
	{
		// Go passed all previous months.
		int nM;
		for ( nM = JAN; nM < nNormMonth; nM++ )
		{
			// Add the number of days of that month.
			lTotal += m_mDaysInMonth[nM];

			// Determine if the month is February and the year is a leap year.
			if ( nM == FEB && LeapYear( nNormYear ) )
			{
				// Add an extra day.
				lTotal++;
			}
		}
	}

	// To determine the number of days in all the years up to the specified
	// one. first determine the number of previous years.
	int nPrevYr = nNormYear - 1;

	// Calculate the number of days in the previous years; take 365 days (at
	// least) for each year. 
	lTotal += nPrevYr * DAYS_IN_YEAR;

	// Add an extra for each leap year; determine this number as follows:
	// take the number of years that are multiples of 4 (LEAP_YEAR), and add
	// one for each; take the number of years that are multiples of 100
	// (CENTURY), and subtract one for each; take the number of years that are
	// multiples of 400 (LEAP_CENTURY), and add one for each.
	lTotal += (nPrevYr / LEAP_YEAR) - (nPrevYr / CENTURY) + (nPrevYr / LEAP_CENTURY);

	// Determine if the total number of days is positive; if not,
	// set it to its minimum: zero.
	if ( lTotal < 0 )
	{
		lTotal = 0;
	}

	return lTotal;
}


//						====================
bool					DateTime::DaysToDate
//						====================
(
	long				lTotalDays,
	int&				nYear,
	int&				nMonth,
	int&				nDay
)
{
	bool bResult = false;

	// Copy the total number of days.
	long lDays = lTotalDays;

	// Determine if the total number of days is not negative.
	if ( lDays >= 0 )
	{
		bResult = true;

		// Initialise year, month, and day.
		nYear = 1;
		nMonth = JAN;
		nDay = 1;

		// Update the number of years as long as 'leap century' blocks
		// (400 years) can be taken from the number of days.
		long lRange = DAYS_IN_YEAR * LEAP_CENTURY + ( LEAP_CENTURY / LEAP_YEAR ) - ( LEAP_CENTURY / CENTURY - 1 );
		for ( ; lDays >= lRange; lDays -= lRange )
		{ nYear += LEAP_CENTURY; }

		// Update the number of years as long as 'century' blocks
		// (100 years) can be taken from the number of days.
		lRange = DAYS_IN_YEAR * CENTURY + ( CENTURY / LEAP_YEAR ) - 1;
		for ( ; lDays >= lRange; lDays -= lRange )
		{ nYear += CENTURY; }

		// Update the number of years as long as 'leap year' blocks
		// (4 years) can be taken from the number of days.
		lRange = DAYS_IN_YEAR * LEAP_YEAR + 1;
		for ( ; lDays >= lRange; lDays -= lRange )
		{ nYear += LEAP_YEAR; }

		// Update the number of years as long as 'year' blocks
		// (365 days) can be taken from the number of days.
		for ( ; lDays >= DAYS_IN_YEAR; lDays -= DAYS_IN_YEAR )
		{ nYear++; }

		// Update the number of months.
		bool bReady = false;
		while ( !bReady )
		{
			// Determine the number of days in the specific month; correct for
			// february in leap years.
			int nD = m_mDaysInMonth[nMonth];
			if ( nMonth == FEB && LeapYear( nYear ) )
			{ nD++; }

			// Determine if the remaining number of days don't fit in the
			// specific month.
			if ( lDays >= nD )
			{
				// Update the month.
				lDays -= nD;
				nMonth++;
			}
			else
			{
				// This month is the correct one.
				bReady = true;
			}
		}

		// Take as day (of the month) the remaining days plus 1 (since the
		// first day of the month has number 1, not 0).
		nDay = lDays + 1;
	}

	return bResult;
}


//						====================
DateTime				DateTime::StartOfDST
//						====================
(
	int					nYear
)
{
	// The start of daylight saving time (in the European Union) is the last
	// sunday of March at 2 a.m.
	// Initialise a DateTime object to the last day of March for the specified
	// year, 2 a.m.
	DateTime dtStart( nYear, MAR, m_mDaysInMonth[MAR], 2, 0, 0, 0 );

	// Determine if this day is a sunday; if not, go back one day at a time
	// until the day is a sunday.
	for ( ; dtStart.GetDayOfWeek() != SUN; dtStart.AddDay(-1) )
	{}

	// N.B. The start of daylight saving time in North America is the first
	// sunday of April at 2 a.m.; to obtain this date, one week ought to be
	// added to dtStart: dtStart.AddDay( DAYS_IN_WEEK );

	return dtStart;
}


//						==================
DateTime				DateTime::EndOfDST
//						==================
(
	int					nYear
)
{
	// The end of daylight saving time (in the European Union and North
	// America) is the last sunday of October at 2 a.m.
	// Initialise a DateTime object to the last day of October for the
	// specified year, 2 a.m.
	DateTime dtEnd( nYear, OCT, m_mDaysInMonth[OCT], 2, 0, 0, 0 );

	// Determine if this day is a sunday; if not, go back one day at a time
	// until the day is a sunday.
	for ( ; dtEnd.GetDayOfWeek() != SUN; dtEnd.AddDay(-1) )
	{}

	return dtEnd;
}

///////////////////////////////////////////////////////////////////////////////

// Undefines
#undef EARLIEST_YEAR
#undef DAYS_IN_YEAR
#undef MONTHS_IN_YEAR
#undef LEAP_YEAR
#undef CENTURY
#undef LEAP_CENTURY
#undef MAX_MS
#undef MAX_SEC
#undef MAX_MIN
#undef MAX_HOUR
#undef DAYS_IN_WEEK
#undef WEEKDAY_CALIBRATION
#undef YEAR_4_TOKEN
#undef YEAR_2_TOKEN
#undef MONTH_TOKEN
#undef MONTH_PAD_TOKEN
#undef DAY_TOKEN
#undef DAY_PAD_TOKEN
#undef HOUR_TOKEN
#undef HOUR_PAD_TOKEN
#undef MIN_TOKEN
#undef MIN_PAD_TOKEN
#undef SEC_TOKEN
#undef SEC_PAD_TOKEN
#undef MS_TOKEN
#undef MS_PAD_TOKEN

///////////////////////////////////////////////////////////////////////////////
