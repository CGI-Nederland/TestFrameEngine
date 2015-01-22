/*****************************************************************************
 * $Workfile: Duration.cpp $
 * $Revision: 1 $
 * $Modtime: 8/17/01 4:43p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

// Includes
#include "Duration.h"		// Class definition

#include <string>

using namespace std;

#include "StrUtil.h"

// Defines
#define MAX_MS			1000
#define MAX_SEC			60
#define MAX_MIN			60
#define MAX_HOUR		24
#define DAY_TOKEN		string( "D" )
#define HOUR_TOKEN		string( "h" )
#define HOUR_PAD_TOKEN	string( "hh" )
#define MIN_TOKEN		string( "m" )
#define MIN_PAD_TOKEN	string( "mm" )
#define SEC_TOKEN		string( "s" )
#define SEC_PAD_TOKEN	string( "ss" )
#define MS_TOKEN		string( "n" )
#define MS_PAD_TOKEN	string( "nnn" )

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==================
						Duration::Duration()
//						==================
{
	// Set all time-members to zero.
	m_lDay = 0;
	m_nHour = 0;
	m_nMin = 0;
	m_nSec = 0;
	m_nMillisec = 0;
}


//						==================
						Duration::Duration
//						==================
(
	long				lDay,
	long				lHour,
	long				lMin,
	long				lSec,
	long				lMillisec
)
{
	Set( lDay, lHour, lMin, lSec, lMillisec );
}


//						===================
						Duration::~Duration()
//						===================
{
	// Empty.
}


//						==================
						Duration::Duration
//						==================
( 
	const Duration&		src
)
{
	// Copy all members.
	m_lDay = src.GetDay();
	m_nHour = src.GetHour();
	m_nMin = src.GetMin();
	m_nSec = src.GetSec();
	m_nMillisec = src.GetMillisec();
}

///////////////////////////////////////////////////////////////////////////////
// Operators

//						====================
Duration				Duration::operator +
//						====================
( 
	const Duration&		durRight
)
{
	// Add day from left operand (this object) to day from right operand,
	// hour from left operand to hour from right operand, etc.
	long lDayNew = m_lDay + durRight.GetDay();
	int nHourNew = m_nHour + durRight.GetHour();
	int nMinNew = m_nMin + durRight.GetMin();
	int nSecNew = m_nSec + durRight.GetSec();
	int nMillisecNew = m_nMillisec + durRight.GetMillisec();

	// Make a new Duration object with the newly calculated times, and return
	// this object.
	Duration durResult( lDayNew, nHourNew, nMinNew, nSecNew, nMillisecNew );

	return durResult;
}


//						====================
Duration				Duration::operator -
//						====================
( 
	const Duration&		durRight
)
{
	// Subtract day from right operand from day from left operand (this
	// object), hour from right operand from hour from left operand, etc.
	long lDayNew = m_lDay - durRight.GetDay();
	int nHourNew = m_nHour - durRight.GetHour();
	int nMinNew = m_nMin - durRight.GetMin();
	int nSecNew = m_nSec - durRight.GetSec();
	int nMillisecNew = m_nMillisec - durRight.GetMillisec();

	// Make a new Duration object with the newly calculated times, and return
	// this object.
	Duration durResult( lDayNew, nHourNew, nMinNew, nSecNew, nMillisecNew );

	return durResult;
}


//						====================
Duration				Duration::operator *
//						====================
(
	int					nFactor
)
{
	// Multiply all time-members with the specified factor.
	long lDayNew = m_lDay * nFactor;
	long lHourNew = m_nHour * nFactor;
	long lMinNew = m_nMin * nFactor;
	long lSecNew = m_nSec * nFactor;
	long lMillisecNew = m_nMillisec * nFactor;

	// Make a new Duration object with the newly calculated times, and return
	// this object.
	Duration durResult( lDayNew, lHourNew, lMinNew, lSecNew, lMillisecNew );

	return durResult;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=============
void					Duration::Set
//						=============
(
	long				lDay,
	long				lHour,
	long				lMin,
	long				lSec,
	long				lMillisec
)
{
	// First, place all time-members in range.
	// Calculate the number of milliseconds in the range [-MAX_MS+1..MAX_MS-1],
	// and place this number in the milliseconds member; calculate the overflow.
	m_nMillisec = lMillisec % MAX_MS;
	long lOverflow = lMillisec / MAX_MS;

	// Calculate the number of seconds in the range [-MAX_SEC+1..MAX_SEC-1],
	// and place this number in the seconds member; calculate the (new) overflow.
	m_nSec = (lSec + lOverflow) % MAX_SEC;
	lOverflow = (lSec + lOverflow) / MAX_SEC;

	// Calculate the number of minutes in the range [-MAX_MIN+1..MAX_MIN-1],
	// and place this number in the minutes member; calculate the (new) overflow.
	m_nMin = (lMin + lOverflow) % MAX_MIN;
	lOverflow = (lMin + lOverflow) / MAX_MIN;

	// Calculate the number of hours in the range [-MAX_HOUR+1..MAX_HOUR-1],
	// and place this number in the hour member; calculate the (new) overflow.
	m_nHour = (lHour + lOverflow) % MAX_HOUR;
	lOverflow = (lHour + lOverflow) / MAX_HOUR;

	// Calculate the number of days, and place this number in the day member.
	m_lDay = lDay + lOverflow;

	// Second, determine if the total duration is negative.
	// Determine if the duration is negative by determining if the
	// first number from the series (day, hour, min, sec, millisec) that
	// is not zero, is negative.
	bool bNegative = false;
	long arrDur[5] = { m_lDay, m_nHour, m_nMin, m_nSec, m_nMillisec };
	bool bReady = false;
	int i;
	for ( i = 0; i < 5 && !bReady; i++ )
	{
		// Stop the search if the number is either negative or positive.
		if ( arrDur[i] < 0 )
		{
			bNegative = true;
			bReady = true;
		}
		else if ( arrDur[i] > 0 )
		{
			bReady = true;
		}
	}

	// Third, if the total duration is negative, toggle the sign of
	// all numbers.
	if ( bNegative )
	{
		ToggleSign();
	}

	// Fourth, switch negative numbers to positive.
	// Determine if the number of milliseconds is negative.
	int nOverflow = 0;
	if ( m_nMillisec < 0 )
	{
		m_nMillisec = MAX_MS + m_nMillisec;
		nOverflow = -1;
	}

	// Determine if the number of seconds is negative.
	m_nSec = m_nSec + nOverflow;
	nOverflow = 0;
	if ( m_nSec < 0 )
	{
		m_nSec = MAX_SEC + m_nSec;
		nOverflow = -1;
	}

	// Determine if the number of minutes is negative.
	m_nMin = m_nMin + nOverflow;
	nOverflow = 0;
	if ( m_nMin < 0 )
	{
		m_nMin = MAX_MIN + m_nMin;
		nOverflow = -1;
	}

	// Determine if the number of hours is negative.
	m_nHour = m_nHour + nOverflow;
	nOverflow = 0;
	if ( m_nHour < 0 )
	{
		m_nHour = MAX_HOUR + m_nHour;
		nOverflow = -1;
	}

	// Add the overflow to the number of days.
	m_lDay += nOverflow;

	// Fifth, if the total duration is negative, again toggle
	// the sign of all numbers.
	if ( bNegative )
	{
		ToggleSign();
	}
}


//						================
long					Duration::GetDay() const
//						================
{
	return m_lDay;
}


//						=================
int						Duration::GetHour() const
//						=================
{
	return m_nHour;
}


//						================
int						Duration::GetMin() const
//						================
{
	return m_nMin;
}


//						================
int						Duration::GetSec() const
//						================
{
	return m_nSec;
}


//						=====================
int						Duration::GetMillisec() const
//						=====================
{
	return m_nMillisec;
}


//						=============
string					Duration::Get
//						=============
(
	const string&		strFormat
)
{
	// Set the duration string initially to the specified format.
	string strDuration = strFormat;

	// Replace the all tokens by the corresponding numbers; note that the pad-
	// tokens are replaced before the unpadded ones.
	ReplaceToken( strDuration, DAY_TOKEN, LongToStr( m_lDay ) );
	ReplaceToken( strDuration, HOUR_PAD_TOKEN, Pad_front( IntToStr(m_nHour), 2, '0' ) );
	ReplaceToken( strDuration, HOUR_TOKEN, IntToStr( m_nHour ) );
	ReplaceToken( strDuration, MIN_PAD_TOKEN, Pad_front( IntToStr(m_nMin), 2, '0' ) );
	ReplaceToken( strDuration, MIN_TOKEN, IntToStr( m_nMin ) );
	ReplaceToken( strDuration, SEC_PAD_TOKEN, Pad_front( IntToStr(m_nSec), 2, '0' ) );
	ReplaceToken( strDuration, SEC_TOKEN, IntToStr( m_nSec ) );
	ReplaceToken( strDuration, MS_PAD_TOKEN, Pad_front( IntToStr(m_nMillisec), 3, '0' ) );
	ReplaceToken( strDuration, MS_TOKEN, IntToStr( m_nMillisec ) );

	return strDuration;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						====================
void					Duration::ToggleSign()
//						====================
{
	// Toggle the sign of all time-members.
	m_lDay *= -1;
	m_nHour *= -1;
	m_nMin *= -1;
	m_nSec *= -1;
	m_nMillisec *= -1;
}

///////////////////////////////////////////////////////////////////////////////

// Undefines
#undef MAX_MS
#undef MAX_SEC
#undef MAX_MIN
#undef MAX_HOUR
#undef DAY_TOKEN
#undef HOUR_TOKEN
#undef HOUR_PAD_TOKEN
#undef MIN_TOKEN
#undef MIN_PAD_TOKEN
#undef SEC_TOKEN
#undef SEC_PAD_TOKEN
#undef MS_TOKEN
#undef MS_PAD_TOKEN
