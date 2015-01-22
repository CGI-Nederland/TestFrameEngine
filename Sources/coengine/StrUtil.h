/*****************************************************************************
 * $Workfile: StrUtil.h $
 * $Revision: 6 $
 * $Modtime: 8/15/01 5:32p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef STRUTIL_H
#define STRUTIL_H

#include <set>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

// Trim chars at the back of a string
string trim_back(const string& s, char c = ' ');

// Trim chars in front of a string
string trim_front(const string& s, char c = ' ');

// Trim chars at both ends of a string
string trim(const string& s, char c = ' ');

////////////////////////////////////////////////////////////////////////////////

// Pad chars in front of a string until its length is as specified
string Pad_front( const string& s, string::size_type nLen, char c = ' ' );

////////////////////////////////////////////////////////////////////////////////

// Removes from the back of a vector of strings those elements with
// the specified value.
vector<string> TrimVector_back( const vector<string>& vstrVec, const string& strEl = "" );

// Removes from the front of a vector of strings those elements with
// the specified value.
vector<string> TrimVector_front( const vector<string>& vstrVec, const string& strEl = "" );

// Removes from both front and back of a vector of strings those elements
// with the specified value.
vector<string> TrimVector( const vector<string>& vstrVec, const string& strEl = "" );

////////////////////////////////////////////////////////////////////////////////

// Convert char to string
string CharToStr( char c );

// Convert string to integer
int StrToInt( const string& s, int nDefault = 0 );

// Convert string to double
double StrToDouble( const string& s );

// Convert int to string
string IntToStr( int n );

// Convert long to string
string LongToStr( long l );

// Convert double to string with a specified significance
string DoubleToStr( double d, int nPrec );

// Convert double to string with a default significance of 6
string DoubleToStr( double d );

// Convert double as an integer to string; i.e., without exponential
// notation and a precision of 0.
string DoubleAsIntToStr( double d );

////////////////////////////////////////////////////////////////////////////////

// Split a string on a specified delimiter, and place the elements in a vector
// of strings.
vector<string> StrToVector( const string& strS, const string& strDel );

// Concatenate the elements of vector to one string, placing a specified
// delimiter in-between.
string VectorToStr( const vector<string>& vstrArgs, const string& strDel );

////////////////////////////////////////////////////////////////////////////////

// Convert a vector of strings to a set of strings.
set<string> VectorToSet( const vector<string>& vstrArgs );

////////////////////////////////////////////////////////////////////////////////

// Return iterator to a certain string-value in a vector of strings;
// if the value is not present, vector.end() is returned.
// Note that the parameterised vector-reference is not given as 'const';
// this is because using an iterator causes changes to the object.
vector<string>::iterator FindInVector( vector<string>& vstrArgs, const string& strVal );

////////////////////////////////////////////////////////////////////////////////

// Return the length of the longest string in a specified set.
// Note that the parameterised set-reference is not given as 'const'; this is
// because using an iterator causes changes to the object.
string::size_type MaxLength( set<string>& sstrArgs );

////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// function		:	ReplaceToken()
//
// description	:	This function replaces in a specified format string all
//					tokens of the specified form by a specified replacement
//					string.
//
// parameters	:	REF strFormat	format string which is to be changed
//					strToken		token to replace
//					strRepl			string to replace token with
//
// returns		:	true	one or more token replaced
//					false	no token replaced
///////////////////////////////////////////////////////////////////////////////
bool ReplaceToken( string& strFormat, const string& strToken,
				   const string& strRepl );




#endif	// !STRUTIL_H
