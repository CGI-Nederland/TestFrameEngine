/*****************************************************************************
 * $Workfile: StrUtil.cpp $
 * $Revision: 5 $
 * $Modtime: 8/15/01 5:36p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "StrUtil.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

////////////////////////////////////////////////////////////////////////////////

// Trim chars at the back of a string
string trim_back(const string& s, char c)
{ return s.substr(0, s.find_last_not_of(c) + 1); }

// Trim chars in front of a string
string trim_front(const string& s, char c)
{
	int start = s.find_first_not_of(c);
	if (start < s.size()) { return s.substr(s.find_first_not_of(c)); }
	else { return string(); }
}

// Trim chars at both ends of a string
string trim(const string& s, char c)
{
	int start = s.find_first_not_of(c);
	if (start < s.size()) { return s.substr(start, s.find_last_not_of(c) + 1 - start); }
	else { return trim_back(s); }
}

string Pad_front( const string& s, string::size_type nLen, char c )
{
	string strRes = s;
	string strPad = CharToStr( c );
	while ( strRes.length() < nLen )
	{
		strRes = strPad + strRes;
	}
	return strRes;
}

vector<string> TrimVector_back( const vector<string>& vstrVec, const string& strEl )
{
	vector<string> vstrV = vstrVec;
	while ( !vstrV.empty() && vstrV.back() == strEl )
	{
		vstrV.pop_back();
	}
	return vstrV;
}

vector<string> TrimVector_front( const vector<string>& vstrVec, const string& strEl )
{
	vector<string> vstrV = vstrVec;
	while ( !vstrV.empty() && vstrV.front() == strEl )
	{
		vstrV.erase( vstrV.begin() );
	}
	return vstrV;
}

vector<string> TrimVector( const vector<string>& vstrVec, const string& strEl )
{
	vector<string> vstrV = TrimVector_back( vstrVec, strEl );
	vstrV = TrimVector_front( vstrV, strEl );
	return vstrV;
}

string CharToStr( char c )
{
	ostringstream oss;
	oss << c;
	return oss.str();
}

int StrToInt( const string& s, int nDefault )
{
	int n;
	istringstream iss( s );
	iss >> n;
	if ( iss.fail() )
	{ n = nDefault; }
	return n;
}

double StrToDouble( const string& s )
{
	double d;
	istringstream iss( s );
	iss >> d;
	return d;
}

string IntToStr( int n )
{
	ostringstream oss;
	oss << n;
	return oss.str();
}

string LongToStr( long l )
{
	ostringstream oss;
	oss << l;
	return oss.str();
}

string DoubleToStr( double d, int nPrec )
{
	ostringstream oss;
	oss << scientific << setprecision( nPrec ) << d;
	return oss.str();
}

string DoubleToStr( double d )
{
	// Take a default significance of 6.
	return DoubleToStr( d, 6 );
}

string DoubleAsIntToStr( double d )
{
	ostringstream oss;
	oss << fixed << setprecision( 0 ) << d;
	return oss.str();
}

vector<string> StrToVector( const string& strS, const string& strDel )
{
	vector<string> vstrArguments;

	// Go passed all delimiters in the string.
	string::size_type nStart = 0;
	string::size_type nDel   = strS.find_first_of( strDel, nStart );
	while ( nDel != string::npos )
	{
		// Get the argument.
		string strArg = strS.substr( nStart, nDel - nStart );

		// Place the argument in the vector.
		vstrArguments.push_back( strArg );

		// Update the start position.
		nStart = nDel + 1;

		// Find the next delimiter.
		nDel = strS.find_first_of( strDel, nStart );
	}

	// Add the last argument to the vector.
	vstrArguments.push_back( strS.substr( nStart ) );

	return vstrArguments;
}

string VectorToStr( const vector<string>& vstrArgs, const string& strDel )
{
	string strS = "";

	// Determine if the vector has any elements.
	if ( !vstrArgs.empty() )
	{
		// Go passed all arguments except the last one.
		vector<string>::size_type nArg;
		for ( nArg = 0; nArg < vstrArgs.size() - 1; nArg++ )
		{
			// Add the argument and a delimiter to the string.
			strS += ( vstrArgs[nArg] + strDel );
		}

		// Add the last argument to the string.
		strS += vstrArgs[nArg];
	}

	return strS;
}

set<string> VectorToSet( const vector<string>& vstrArgs )
{
	set<string> sstrArgs;

	// Determine if the vector has any elements.
	if ( !vstrArgs.empty() )
	{
		// Go passed all arguments.
		vector<string>::size_type nArg;
		for ( nArg = 0; nArg < vstrArgs.size(); nArg++ )
		{
			// Add the vector element to the set.
			sstrArgs.insert( vstrArgs[nArg] );
		}
	}

	return sstrArgs;
}

vector<string>::iterator FindInVector( vector<string>& vstrArgs, const string& strVal )
{
	return find( vstrArgs.begin(), vstrArgs.end(), strVal );
}

string::size_type MaxLength( set<string>& sstrArgs )
{
	string::size_type nMax = 0;

	// Go passed all arguments.
	set<string>::iterator itr = sstrArgs.begin();
	for ( ; itr != sstrArgs.end(); itr++ )
	{
		// Determine if the length of this argument is longer than the
		// previously found longest string; if so, set new maximum.
		if ( itr->length() > nMax )
		{
			nMax = itr->length();
		}
	}

	return nMax;
}

bool ReplaceToken
(
	string&				strFormat,
	const string&		strToken,
	const string&		strRepl
)
{
	bool bResult = false;

	string::size_type nToken = -1 * ( strRepl.size() );
	while ( ( nToken = strFormat.find( strToken, nToken + strRepl.size() ) ) != string::npos )
	{
		strFormat.replace( nToken, strToken.size(), strRepl );
		bResult = true;
	}

	return bResult;
}
