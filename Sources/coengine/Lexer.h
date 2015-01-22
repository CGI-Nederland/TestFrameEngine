/*****************************************************************************
 * $Workfile: Lexer.h $
 * $Revision: 4 $
 * $Modtime: 1/29/01 10:39a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LEXER_H
#define LEXER_H

#include <string>

using namespace std;

class Lexer 
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
public:
	Lexer();							// Default constructor
private:
	Lexer( const Lexer& right );		// Copy constructor
public:
	virtual ~Lexer();					// Destructor

	////////////////////////////////////////////////////////////////////////////
	// ATTRIBUTES AND OPERATIONS
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: SetLine()
	//
	// description	: This function sets the contents of the line which is to be
	//				  lexically analysed. It also resets the current character
	//				  position to the beginning of the line.
	//					
	// parameters	: strLine		line to analyse
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetLine( const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLine()
	//
	// description	: This function returns the content of the currently analysed
	//				  line.
	//					
	// parameters	: None.
	//
	// returns		: reference to the current line content
	///////////////////////////////////////////////////////////////////////////////
	const string& GetLine() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetToken()
	//
	// description	: This functions returns the next token from the current line.
	//				  				
	// parameters	: None.
	//
	// returns		: integer from the TOKEN enum specifying the token type
	///////////////////////////////////////////////////////////////////////////////
	int GetToken();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCurrentTokenValue()
	//
	// description	: This function returns the value belonging to the current
	//				  token.
	//					
	// parameters	: None.
	//
	// returns		: reference to a string with the current token value
	///////////////////////////////////////////////////////////////////////////////
	const string& GetCurrentTokenValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTokenValue()
	//
	// description	: This function returns the value (i.e., the character string)
	//				  belonging to the specified token (code). Only for several
	//				  tokens can a standard value be returned (the operators and
	//				  parentheses); for the other tokens an empty string is
	//				  returned.
	//					
	// parameters	: nToken	token code
	//
	// returns		: string containing specified token's value
	///////////////////////////////////////////////////////////////////////////////
	string GetTokenValue( int nToken ) const;

	///////////////////////////////////////////////////////////////////////////////
	// IMPLEMENTATION
private:

	///////////////////////////////////////////////////////////////////////////////
	// function		: NextChar()
	//
	// description	: This function moves the current character position to the
	//				  next one.
	//					
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void NextChar();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetChar()
	//
	// description	: This function returns the current character from the analysed
	//				  line.
	//					
	// parameters	: None.
	//
	// returns		: current character
	///////////////////////////////////////////////////////////////////////////////
	char GetChar() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsEOL()
	//
	// description	: This function checks if the end of the line is reached.
	//					
	// parameters	: None.
	//
	// returns		: true		end of line reached
	//				  false		end of line not reached
	///////////////////////////////////////////////////////////////////////////////
	bool IsEOL() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsSkip()
	//
	// description	: This function checks if the specified character should be 
	//				  skipped.
	//					
	// parameters	: chChar	character to check
	//
	// returns		: true			character must be skipped
	//				  false			character must not be skipped
	///////////////////////////////////////////////////////////////////////////////
	bool IsSkip( char chChar ) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: ScanDirectToken()
	//
	// description	: This function checks if the specified character is one of
	//				  the direct tokens. If so, this token's type is returned; if
	//				  not, UNDEFINED is returned.
	//					
	// parameters	: chToken		character to check
	//
	// returns		: integer specifying direct token type
	///////////////////////////////////////////////////////////////////////////////
	int ScanDirectToken( char chToken );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Scan()
	//
	// description	: This function scans the line from the current character
	//				  position for the first token; this token's type is returned.
	//					
	// parameters	: None.
	//
	// returns		: integer specifying token type
	///////////////////////////////////////////////////////////////////////////////
	int	Scan();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ScanForString()
	//
	// description	: This function scans the line for a string constant. A string
	//				  constant is defined as a series of characters between double
	//				  quotes; two double quotes in-between are considered as one
	//				  escaped double quote. If a valid string constant is found,
	//				  STRING is returned;if an invalid one is found, ERROR is
	//				  returned; otherwise, UNDEFINED.
	//					
	// parameters	: None.
	//
	// returns		: integer specifying token type:  STRING, ERROR_STRING, or
	//				  UNDEFINED
	///////////////////////////////////////////////////////////////////////////////
	int ScanForString();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ScanForVariable()
	//
	// description	: This function scans the line for a cluster variable's name.
	//				  Such a name must begin with either a letter or an underscore,
	//				  optionally followed by a series of characters, each of which
	//				  must be a letter, an underscore or a digit. If a variable is
	//				  found, VAR is returned; otherwise, UNDEFINED.
	//					
	// parameters	: None.
	//
	// returns		: integer specifying token type: either VAR or UNDEFINED
	///////////////////////////////////////////////////////////////////////////////
	int ScanForVariable();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ScanForNumber()
	//
	// description	: This function scans the line for a number; either an integer
	//				  or a float. An integer consists of sequence of digits. A 
	//				  float consists of an integer part, a decimal point, a
	//				  fraction part, an e or E, and an optionally signed integer 
	//				  exponent. The integer and fraction parts both consist of a
	//				  sequence of digits. Either the integer part or the fraction
	//				  part (not both) may be missing; either the decimal point or
	//				  the e and the exponent (not both) may be missing. Note that a
	//				  number here can not be preceded by a sign, since this is
	//				  considered to be one of the direct tokens. If a number is
	//				  found, NUMBER is returned; otherwise, UNDEFINED.
	//					
	// parameters	: None.
	//
	// returns		: integer specifying token type: either NUMBER, ERROR_NUM_DEC,
	//				  ERROR_NUM_EXP, or UNDEFINED
	///////////////////////////////////////////////////////////////////////////////
	int ScanForNumber();

public:
// Class constants
	enum TOKEN {	EOL,			// end of line token
					LPAR,			// opening parenthesis
					RPAR,			// closing parenthesis
					ADD,			// addition/unary plus operator
					SUB,			// subtraction/unary minus operator
					MUL,			// multiplication operator
					DIV,			// division operator
					ASSIGN,			// assignment operator
					NUMBER,			// numerical constant
					STRING,			// string constant
					VAR,			// cluster variable name
					ERROR_STRING,	// error: invalid string
					ERROR_NUM_DEC,	// error: float consisting of only a decimal point
					ERROR_NUM_EXP,	// error: float with exponential sign, but no exponent
					ERROR_INV_TOK,	// error: invalid token
					UNDEFINED
				};

// Member variables
private:
	string	m_strLine;				// String to analyse
	string	m_strTokenValue;		// Token value string
	int		m_nPosition;			// Current character position
};

#endif // !LEXER_H
