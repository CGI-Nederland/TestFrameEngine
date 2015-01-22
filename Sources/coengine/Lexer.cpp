/*****************************************************************************
 * $Workfile: Lexer.cpp $
 * $Revision: 6 $
 * $Modtime: 1/29/01 2:30p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "Lexer.h"		// Class definition

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
Lexer::Lexer()
{
	// Empty.
}

// Destructor
Lexer::~Lexer()
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==============
void					Lexer::SetLine
//						==============
(
	const string&		strLine
)
{
	// Initialize lexer.
	m_strLine   = strLine; 
	m_nPosition = 0;
}


//						==============
const string&			Lexer::GetLine() const
//						==============
{
	return m_strLine;
}


//						=================
int						Lexer::GetToken()
//						================= 
{
	// Scan the current line for the next token and return its type.
	return Scan();
}


//						=============================
const string&			Lexer::GetCurrentTokenValue() const
//						=============================
{
	return m_strTokenValue;
}


//						====================
string					Lexer::GetTokenValue
//						====================
(
	int					nToken
) const
{
	// Determine the specified token, and return its corresponding value.
	switch ( nToken )
	{
		case LPAR:
			return "(";

		case RPAR:
			return ")";

		case ADD:
			return "+";

		case SUB:
			return "-";

		case MUL:
			return "*";

		case DIV:
			return "/";

		case ASSIGN:
			return "=";

		default:
			return "";
	}
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						===============
void					Lexer::NextChar()
//						===============
{
	// Increment the current character position.
	m_nPosition++; 
}


//						==============
char					Lexer::GetChar() const
//						==============
{
	// Return the current character.
	return m_strLine[m_nPosition];
}


//						============
bool					Lexer::IsEOL() const
//						============
{
	// Check if the current character position is past
	// the last character of the line.
	if ( m_nPosition == GetLine().length() ) 
	{
		return true;
	}
	else
	{
		return false;
	}
}


//						=============
bool					Lexer::IsSkip
//						=============
(
	char				chChar
) const
{
	// Determine if the specified character is a character to be skipped.
	switch ( chChar ) 
	{
		case ' ':
			return true;

		default:
			return false;
	}
}


//						======================
int						Lexer::ScanDirectToken
//						======================
(
	char				chToken
)
{
	// Check if the specified character is a direct token.
	// If it is, return its not; if not, return UNDEFINED.
	switch ( chToken )
	{
		case '(':					// opening parenthesis
		{
			m_strTokenValue = "(";
			return LPAR;
		}

		case ')':					// closing parenthesis
		{
			m_strTokenValue = ")";
			return RPAR;
		}

		case '*':					// multiplication operator
		{
			m_strTokenValue = "*";
			return MUL;
		}

		case '/':					// division operator
		{
			m_strTokenValue = "/";
			return DIV;
		}

		case '=':					// assignment operator
		{
			m_strTokenValue = "=";
			return ASSIGN;
		}

		case '-':					// subtraction/unary minus operator
		{
			m_strTokenValue = "-";
			return SUB;
		}

		case '+':					// addition/unary plus operator
		{
			m_strTokenValue = "+";
			return ADD;
		}

		default:
			return UNDEFINED;
	}
}


//			=============
int			Lexer::Scan()
//			=============
{
	// Reset the value of the current token.
	m_strTokenValue = "";
	
	// Skip uninteresting characters.
    while ( IsSkip( GetChar() ) ) 
	{
		NextChar();
	}

	// Check if the end of the line is reached.
	if ( IsEOL() ) 
	{
		return EOL;
	}

	// Check if the current token is one of the direct tokens.
	int nDirectToken = ScanDirectToken( GetChar() );
	if ( nDirectToken != UNDEFINED )
	{
		NextChar();
		return nDirectToken;
	}

	// Scan for a string constant.
	int nString = ScanForString();
	if (  nString == STRING )
	{
		// A string constant has been found.
		return STRING;
	}
	else if ( nString == ERROR_STRING )
	{
		// An invalid string constant (opened, but not closed) has been found.
		return ERROR_STRING;
	}

	// Scan for a cluster variable.
	if ( ScanForVariable() == VAR )
	{
		// A cluster variable has been found.
		return VAR;
	}

	// Scan for a number.
	int nNumber = ScanForNumber();
	if (  nNumber == NUMBER )
	{
		// A number has been found.
		return NUMBER;
	}
	else if ( nNumber == ERROR_NUM_DEC || nNumber == ERROR_NUM_EXP )
	{
		// An invalid number has been found.
		return nNumber;
	}

	// What has been found, is not is not of any valid token type,
	// so it's an error. Before returning, move on to the next
	// character to prevent looping on an error.
	NextChar(); 
	return ERROR_INV_TOK;
}


//						====================
int						Lexer::ScanForString()
//						====================
{
	int nToken		= UNDEFINED;	// return value

	// Check if the current character is a double quote.
	if ( GetChar() == '\"' )
	{
		// Skip the opening double quote.
		NextChar();

		// Read following characters until the end of the string constant,
		// or the end of the line (which is an error) is found.
		bool bEnd = false;
		while ( !bEnd )
		{
			// Check if an EOL is encountered.
			if ( IsEOL() )
			{
				// There has been no closing double quote, so there is an error.
				nToken = ERROR_STRING;
				bEnd   = true;
			}
			// Otherwise, check if a double quote is encountered.
			else if ( GetChar() == '\"' )
			{
				// Go to the next character.
				NextChar();

				// Check if this next character is anything else than a 
				// double quote.
				if ( GetChar() != '\"' )
				{
					// The found double quote was the closing double quote of the
					// string constant; the end of the string has been found.
					nToken = STRING;
					bEnd   = true;
				}
				else
				{
					// An escaped double quote has been found. Add one double
					// quote to the token value, and go to the next character.
					m_strTokenValue += '\"';
					NextChar();
				}
			}
			else
			{
				// Add the current character to the token value, and go to the
				// next character.
				m_strTokenValue += GetChar();
				NextChar();
			}
		}
	}

	return nToken;
}


//						======================
int						Lexer::ScanForVariable()
//						======================
{
	int nToken = UNDEFINED;		// return value

	// Check if the current character either a letter or an underscore.
	if ( isalpha( GetChar() ) || ( GetChar() == '_') )
	{ 
		// The following token is indeed the name of a variable.
		nToken = VAR;
		
		// Store this first character and go to the next one.
		m_strTokenValue += GetChar();
		NextChar();

		// Go through all following characters until one is found which is
		// not a letter, not an underscore or not a digit.
		while ( isalpha( GetChar() ) || ( GetChar() == '_' ) || isdigit( GetChar() ) )
		{
			// Store this character and go to the next one.
			m_strTokenValue += GetChar();
			NextChar();
		}
	}

	return nToken;
}


//						====================
int						Lexer::ScanForNumber()
//						====================
{
	int nToken = UNDEFINED;		// return value

	// Check if the first character is either a digit or a (decimal) point,
	// because, if it is not, the following can not be a number.
	if ( isdigit( GetChar() ) || GetChar() == '.' )
	{
		// The following token is a number (although it can turn out to be
		// invalid).
		nToken = NUMBER;

		// Determine if there is a integer part; if so, go through its digits.
		bool bInteger = false;
		while ( isdigit( GetChar() ) )
		{
			bInteger = true;

			// Add the digit to the token value and go to the next one.
			m_strTokenValue += GetChar();
			NextChar();
		}

		// Check for a decimal point.
		if ( GetChar() == '.' )
		{
			// Add the decimal point to the token value, and move on.
			m_strTokenValue += GetChar();
			NextChar();
		}

		// Determine if there is a fractional part; if so, go through its digits.
		bool bFraction = false;
		while ( isdigit( GetChar() ) )
		{
			bFraction = true;

			// Add the digit to the token value and go to the next one.
			m_strTokenValue += GetChar();
			NextChar();
		}

		// Check if both the integer and fractional parts are missing.
		if ( !bInteger && !bFraction )
		{
			// An invalid number, consisting of only a decimal point.
			nToken = ERROR_NUM_DEC;
		}
		else
		{
			// Check if there is a exponent sign, which is either 'e' or 'E'.
			if ( GetChar() == 'e' || GetChar() == 'E' )
			{
				// Add the exponent sign to the token value, and move on.
				m_strTokenValue += GetChar();
				NextChar();

				// Check if the e or E is followed by a sign.
				if ( GetChar() == '+' || GetChar() == '-' )
				{
					// Add the sign to the token value, and move on.
					m_strTokenValue += GetChar();
					NextChar();
				}

				// Determine if there is an exponent; if so, go through its
				// digits.
				bool bExponent = false;
				while ( isdigit( GetChar() ) )
				{
					bExponent = true;

					// Add the digit to the token value and go to the next one.
					m_strTokenValue += GetChar();
					NextChar();
				}

				// Check if an exponent was not found.
				if ( !bExponent )
				{
					// An exponent sign was found, but no exponent; this is an
					// error.
					nToken = ERROR_NUM_EXP;
				}
			}
		}
	}

	return nToken;
}
