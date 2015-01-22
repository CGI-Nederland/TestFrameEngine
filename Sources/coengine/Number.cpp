/*****************************************************************************
 * $Workfile: Number.cpp $
 * $Revision: 1 $
 * $Modtime: 1/30/01 11:02a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable: 4786)

#include "Number.h"		// Class definition

#include <string>

using namespace std;

#include "StrUtil.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						==============
						Number::Number
//						==============							
(
	const string&		strNumber
)
{
	// Set the value of number as specified.
	m_strValue = strNumber;

	// Set the default values of the other member variables.
	m_bInt			= false;
	m_bFloat		= false;
	m_dlNumValue	= 0.0;
	m_nSignificance = -1;
	m_nPrecision	= -1;
	m_strInt		= "";
	m_strFrac		= "";
	m_strExp		= "";

	// Interpret the number.
	Interpret();
}


// Destructor
//						===============
						Number::~Number()
//						===============
{
	// Empty.						
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						================
const string&			Number::GetValue() const
//						================
{
	return m_strValue;
}


//						===================
double					Number::GetNumValue() const
//						===================
{
	return m_dlNumValue;
}


//						=============
bool					Number::IsInt() const
//						=============
{
	return m_bInt;
}


//						===============
bool					Number::IsFloat() const
//						===============
{
	return m_bFloat;
}


//						================
bool					Number::IsNumber() const
//						================
{
	return (m_bInt || m_bFloat);
}


//						=======================
int						Number::GetSignificance() const
//						=======================
{
	return m_nSignificance;
}


//						====================
int						Number::GetPrecision() const
//						====================
{
	return m_nPrecision;
}


//						======================
const string&			Number::GetIntegerPart() const
//						======================
{
	return m_strInt;
}


//						=========================
const string&			Number::GetFractionalPart() const
//						=========================
{
	return m_strFrac;
}


//						===================
const string&			Number::GetExponent() const
//						===================
{
	return m_strExp;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=================
void					Number::Interpret()
//						=================
{
	string str		     = m_strValue;	// copy of number's value
	int    nSignificance = 0;			// significance
	int    nPrecision	 = 0;			// precision
	bool   bMinus		 = false;		// whether it starts with a minus sign
	bool   bInteger	     = false;		// whether there is an integer part
	bool   bFraction	 = false;		// whether there is a fractional part
	bool   bExponent	 = false;		// whether there is an exponent
	string strInt		 = "";			// characters of integer part
	string strFrac		 = "";			// characters of fractional part
	string strExp		 = "";			// characters of exponent

	// Remove leading and trailing spaces.
	str = trim( str );

	// Check if the number string is an empty string.
	if ( str.empty() )
	{
		return;
	}

	int nPos = 0;	// posistion in the number string

	// Check if number starts with a minus sign.
	if ( str[nPos] == '-' )
	{
		// Add the minus sign to the integer part, and skip it.
		strInt = "-";
		nPos++;
	}
	// Otherwise, check if number starts with a plus sign.
	else if ( str[nPos] == '+' )
	{
		// Skip plus sign.
		nPos++;
	}

	// Check if there is an integer part; if so, go through its digits.
	for ( ; isdigit( str[nPos] ); nPos++ )
	{
		// An integer part is found.
		bInteger = true;

		// Add the digit to the integer part.
		strInt += str.substr( nPos, 1 );

		// Check if the digit is not a leading zero.
		if ( str[nPos] != '0' || nSignificance != 0 )
		{
			// Increase the significance.
			nSignificance++;
		}
	}

	// Check for a decimal point.
	if ( str[nPos] == '.' )
	{
		// A fractional part is found; skip decimal point.
		bFraction = true;
		nPos++;
	}

	// Check if there is a fractional part; if so, go through its digits.
	for ( ; isdigit( str[nPos] ); nPos++ )
	{
		// Increase significance and precision.
		nSignificance++;
		nPrecision++;

		// Add the digit to the fractional part.
		strFrac += str.substr( nPos, 1 );
	}

	// Check if at least an integer or fractional part was found.
	if ( bInteger || bFraction )
	{
		// Check if there is a exponent sign, which is either 'e' or 'E'.
		if ( str[nPos] == 'e' || str[nPos] == 'E' )
		{
			// Skip the exponent sign.
			nPos++;

			// Check if the e or E is followed by a minus sign.
			if ( str[nPos] == '-' )
			{
				// Add the minus sign to the exponent, and skip it.
				strExp = "-";
				nPos++;
			}
			// Otherwise, check if the e or E is followed by a plus sign.
			else if ( str[nPos] == '+' )
			{
				// Skip the plus sign.
				nPos++;
			}

			// Determine if there is an exponent; if so, go through its
			// digits.
			for ( ; isdigit( str[nPos] ); nPos++ )
			{
				bExponent = true;

				// Add the digit to the exponent.
				strExp += str.substr( nPos, 1 );
			}

			// Check if an exponent is not found.
			if ( !bExponent )
			{
				// Although an exponent sign was found, there was no exponent;
				// the value can not be that of a number; leave the default
				// member values.
				return;
			}
		}

		// Check if there are more characters after the last digit.
		if ( str.length() > nPos )
		{
			// Characters after the last digit mean the value is not that of
			// a number; leave the default member values.
			return;
		}

		// The value is that of a number; to determine whether an integer or
		// a float, check if there is no fractional part and no exponent.
		if ( !bFraction && !bExponent )
		{
			// The value must be an integer.
			m_bInt = true;

			// The significance of an integer must be at least 1.
			if ( nSignificance == 0 )
			{	
				nSignificance = 1;
			}
		}
		else
		{
			// The value must be a float.
			m_bFloat = true;

			// Set the float-specific members: precision, fractional part,
			// and exponent.
			m_nPrecision = nPrecision;

			// If there's a fractional part, store it.
			if ( bFraction )
			{
				m_strFrac = strFrac;
			}

			// If there's an exponent, remove its leading zeros, and store it.
			if ( bExponent )
			{
				m_strExp = RemoveLeadingZeros( strExp );
			}
		}

		// Set the integer part and the significance.
		m_strInt		= RemoveLeadingZeros( strInt );
		m_nSignificance = nSignificance;

		// To determine the numerical value, convert the value from string
		// to double.
		m_dlNumValue = StrToDouble( str );

		return;
	}
	else
	{
		// The value can not be that of a number; leave the default member values.
		return;
	}
}


//						==========================
string					Number::RemoveLeadingZeros
//						==========================
(
	const string&		strNumber
) const
{
	string strResult = "";

	// Check if the number string is not empty.
	if ( !strNumber.empty() )
	{
		// Check if the number starts with a minus sign.
		if ( strNumber[0] == '-' )
		{
			// Add the minus sign to the result.
			strResult = "-";
		}

		// Find the position of the first non-zero digit.
		int nPos = strNumber.find_first_of( "123456789" );

		// Determine if a non-zero digit has been found.
		if ( nPos != string::npos )
		{
			// Add all characters (which must be digits) after the last zero
			// to the result.
			strResult += strNumber.substr( nPos );
		}
		else
		{
			// The number must be 0; add one 0 to the result.
			strResult += "0";
		}
	}

	return strResult;
}
