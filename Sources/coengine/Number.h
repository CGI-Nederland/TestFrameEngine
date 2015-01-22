/*****************************************************************************
 * $Workfile: Number.h $
 * $Revision: 1 $
 * $Modtime: 1/18/01 3:25p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NUMBER_H
#define NUMBER_H

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class Number
class Number
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
public:

	///////////////////////////////////////////////////////////////////////////////
	// constructor of Number
	//
	// parameters	: strNumber		string whose value is considered as a number
	///////////////////////////////////////////////////////////////////////////////
	explicit Number( const string& strNumber );

private:
	Number();						// Default constructor
	Number( const Number& right );	// Copy constructor

public:
	~Number();						// Destructor

	////////////////////////////////////////////////////////////////////////////
	// ATTRIBUTES AND OPERATIONS

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetValue()
	//
	// description	: This function returns the value of number.
	//					
	// parameters	: None
	//
	// returns		: string containing value of number
	///////////////////////////////////////////////////////////////////////////////
	const string& GetValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsInt()
	//
	// description	: This function determines whether the number's content
	//				  belongs to the set of integer values.
	//					
	// parameters	: None
	//
	// returns		: true		number is an integer
	//				  false		number is not an integer
	///////////////////////////////////////////////////////////////////////////////
	bool IsInt() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsFloat()
	//
	// description	: This function determines whether the number's content
	//				  belongs to the set of float values.
	//					
	// parameters	: None
	//
	// returns		: true		string content is a float
	//				  false		string content is not a float
	///////////////////////////////////////////////////////////////////////////////
	bool IsFloat() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsNumber()
	//
	// description	: This function determines whether the number's content is
	//				  really a number; i.e. if it is either an integer or a float.
	//					
	// parameters	: None
	//
	// returns		: true		number is really a number
	//				  false		number is not really a number
	///////////////////////////////////////////////////////////////////////////////
	bool IsNumber() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumValue()
	//
	// description	: This function returns the numerical value of number as a
	//				  double. If the number is not considered as a real number, as
	//				  numerical value the default 0.0 will be returned.
	//					
	// parameters	: None
	//
	// returns		: double containing numerical value of number
	///////////////////////////////////////////////////////////////////////////////
	double GetNumValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSignificance()
	//
	// description	: This function returns the significant number of digits of
	//				  number. If the number is not considered as a real number, as
	//				  significance the default -1 will be returned.
	//					
	// parameters	: None
	//
	// returns		: integer specifying significance
	///////////////////////////////////////////////////////////////////////////////
	int GetSignificance() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetPrecision()
	//
	// description	: This function returns the precision of number; i.e. the
	//				  number of digits after the decimal point. If the number is
	//				  not a float, as precision the default -1 will be returned.
	//					
	// parameters	: None
	//
	// returns		: integer specifying precision
	///////////////////////////////////////////////////////////////////////////////
	int GetPrecision() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetIntegerPart()
	//
	// description	: This function returns a string containing the characters of
	//				  the integer part. If there is no integer part, an empty
	//				  string is returned.
	//					
	// parameters	: None
	//
	// returns		: string containing integer part
	///////////////////////////////////////////////////////////////////////////////
	const string& GetIntegerPart() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFractionalPart()
	//
	// description	: This function returns a string containing the characters of
	//				  the fractional part. If there is no fractional part, an empty
	//				  string is returned.
	//					
	// parameters	: None
	//
	// returns		: string containing fractional part
	///////////////////////////////////////////////////////////////////////////////
	const string& GetFractionalPart() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetExponent()
	//
	// description	: This function returns a string containing the characters of
	//				  the exponent. If there is no exponent, an empty string is
	//				  returned.
	//					
	// parameters	: None
	//
	// returns		: string containing exponent
	///////////////////////////////////////////////////////////////////////////////
	const string& GetExponent() const;

private:
	////////////////////////////////////////////////////////////////////////////
	// IMPLEMENTATION

	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret()
	//
	// description	: This function interprets the number. It scans through its
	//				  characters, and determines if its value belongs to those of
	//				  integers, or those of floats, or to those of neither. If it
	//				  is an integer or a float, its numerical value is calculated.
	//				  An integer consists of an optionally signed sequence of digits.
	//				  A float consists of an optionally signed integer part, a
	//				  decimal point, a fraction part, an e or E, and an optionally
	//				  signed integer exponent. The integer and fraction parts both
	//				  consist of a sequence of digits. Either the integer part or
	//				  the fraction part (not both) may be missing; either the
	//				  decimal point or the e and the exponent (not both) may be
	//				  missing.
	//
	// parameters	: None
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void Interpret();

	///////////////////////////////////////////////////////////////////////////////
	// function		: RemoveLeadingZeros()
	//
	// description	: This function removes leading zeros from a specified string;
	//				  a minus sign in front is not removed.
	//					
	// parameters	: strNumber		string from which to remove leading zeros
	//
	// returns		: string from which leading zeros are removed
	///////////////////////////////////////////////////////////////////////////////
	string RemoveLeadingZeros( const string& strNumber ) const;

// Member variables
private:
	string	m_strValue;			// value of number; i.e. the array of characters
	bool	m_bInt;				// whether number is a integer
	bool	m_bFloat;			// whether number is a float
	double	m_dlNumValue;		// numerical value of number
	int		m_nSignificance;	// significance
	int		m_nPrecision;		// precision
	string	m_strInt;			// integer part
	string	m_strFrac;			// fractional part
	string	m_strExp;			// exponent
};

#endif // !EXPRRESULT_H

