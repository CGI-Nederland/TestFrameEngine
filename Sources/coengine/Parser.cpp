/*****************************************************************************
 * $Workfile: Parser.cpp $
 * $Revision: 7 $
 * $Modtime: 8/15/01 5:27p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "Parser.h"			// Class definition

#include <string>
#include <vector>

using namespace std;

#include "AddExpression.h"
#include "AssignExpression.h"
#include "Context.h"
#include "DivExpression.h"
#include "ErrorList.h"
#include "Expression.h"
#include "ExprResult.h"
#include "Lexer.h"
#include "MulExpression.h"
#include "NumExpression.h"
#include "Setting.h" 
#include "StrExpression.h"
#include "SubExpression.h"
#include "VarExpression.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						==============
						Parser::Parser()
//						==============
{
	// Create lexer object
	m_pTheLexer = new Lexer();

	// Create errorlist object
	m_pErrorList = new ErrorList();
}


// Destructor
//						===============
						Parser::~Parser()
//						===============
{
	delete m_pTheLexer;
	delete m_pErrorList;

	m_pTheLexer=0;
	m_pErrorList=0;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==================
void					Parser::Initialise
//						==================
(
	Setting*			pSetting
)
{
	// Get language from settings, and set it in the ErrorList.
	m_pErrorList->SetLanguage( pSetting->Get( "SYSTEM", "Language" ) );

	// Get Precision from settings.
	m_strPrecision = pSetting->Get( "SYSTEM", "Precision" );
}


//						==================
void					Parser::SetContext
//						==================
(
	Context*			pContext
)
{
	m_pContext = pContext;
}


//						=================
const string&			Parser::GetResult() const
//						=================
{
	return m_strResult;
}


//						======================
const vector<string>&	Parser::GetErrorVector() const
//						======================
{
	return m_vstrErrorVector;
}


//						=============
bool					Parser::Parse
//						=============
(
	const string&		strExpression
)
{
	bool bResult = false;

	// Clear all errors.
	ClearErrors();

	// Initialise the lexer.
	m_pTheLexer->SetLine( strExpression );

	// Let the lexer load the first token.
	Advance();

	// Start parsing the specified expression; create an abstract syntax tree
	// in which the expression is translated into an ordered group of
	// expression classes.
	Expression* ast = Start();

	// Check if during the parsing of the expression, no syntax errors
	// were found.
	if ( m_ncSyntaxError == 0 )
	{	
		// Evaluate the abstract syntax tree.
		ExprResult result = ast->Evaluate( *m_pContext );
		
		// In case the resulting expression is a variable call,
		// convert it to its contents.
		result.ConvertFromVar( *m_pContext );

		// Check the status of the resulting expression.
		switch ( result.GetStatus() )
		{
			// Expression without any errors.
			case ExprResult::OK	: 
			{
				// No semantic errors were found; convert the result to a
				// string, store it, and make the parser result true.
				result.ConvertToString();
				m_strResult = result.GetValue();
				bResult = true;
				break;
			}

			// Expression with semantic errors.
			case ExprResult::UNKNOWN_VAR_ERROR :
			{
				// A cluster variable unknown to the context has been
				// encountered; report this error.
				string strVar = result.GetValue();
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_INVALID_VAR_NAME, strVar );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			case ExprResult::ASSIGN_NO_VAR_ERROR :
			{
				// An assignment operation of which the left operand is not a
				// cluster variable, has encountered; report this error.
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_ASSIGN_NO_VAR );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			case ExprResult::SUB_NO_NUM_ERROR :
			{
				// A subtraction operation of which at least one operand is
				// not a number, has been encountered; report this error.
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_SUB_NO_NUM );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			case ExprResult::MUL_NO_NUM_ERROR :
			{
				// A multiplication operation of which at least one operand is
				// not a number, has been encountered; report this error.
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_MUL_NO_NUM );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			case ExprResult::DIV_NO_NUM_ERROR :
			{
				// A division operation of which at least one operand is
				// not a number, has been encountered; report this error.
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_DIV_NO_NUM );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			case ExprResult::DIV_BY_ZERO_ERROR :
			{
				// A division by zero has been encountered; report this error.
				string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_DIV_BY_ZERO );
				m_vstrErrorVector.push_back( strErr );
				break;
			}

			default	:
			{
				// Internal error.
				m_vstrErrorVector.push_back( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
				break;
			}
		}	
	}

	// Remove the abstract syntax tree.
	delete ast;	
	ast=0;

	return bResult;
}


//						=====================
bool					Parser::ParseVariable
//						=====================
(
	const string&		strVariable		// variable to parse
)
{
	bool bResult = false;	// Initialise the result as false.
	
	// Clear all errors.
	ClearErrors();

	// Make the Lexer determine the kind of token strVariable is.
	m_pTheLexer->SetLine( strVariable );
	int nToken = m_pTheLexer->GetToken();

	// Make the Lexer determine the token after the first one.
	int nAfter = m_pTheLexer->GetToken();

	// Check if the Lexer found strVariable to be a cluster variable
	// followed by an 'end of line' (EOL).
	if ( nToken == Lexer::VAR && nAfter == Lexer::EOL)
	{
		bResult = true;
	}
	else
	{
		bResult = false;

		// Add to the error vextor a message about the invalid 
		// variable name.
		Error( m_pErrorList->GetText( ErrorList::ID_ERR_INVALID_VAR_NAME, strVariable ) );
	}
	
	return bResult;
}


//						===================
void					Parser::ClearErrors()
//						===================
{
	// Clear all errors.
	m_ncSyntaxError = 0;
	m_vstrErrorVector.clear();
}


//						===============================
void					Parser::NotifyMissingDateFormat()
//						===============================
{
	// Report an error that the format in a date-command is missing.
	string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_DATE_NO_FORMAT );
	m_vstrErrorVector.push_back( strErr );
}

//						===============================
void					Parser::NotifyMissingTimeFormat()
//						===============================
{
	// Report an error that the format in a time-command is missing.
	string strErr = m_pErrorList->GetText( ErrorList::ID_ERR_TIME_NO_FORMAT );
	m_vstrErrorVector.push_back( strErr );
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

///////////////////////////////////////////////////////////////////////////////
// The parser is an ll(1) type parser implemented using recursive decent. 
// The parser constructs an abstract syntax tree.
//
// Parser grammar :
// 
//		E -> (E)
//		E -> E = E
//		E -> E + E
//		E -> E - E
//		E -> E * E
//		E -> E / E 
//		E -> +E
//		E -> -E
//		E -> variable
//		E -> number
//
//	Transformed grammar (to eliminate left recursion and give */ higher precedence
//  than +-) 
//
//	--------------------+-------------------+-------------------+-----------------
//  S -> S'				|					|					|
//	--------------------+-------------------+-------------------+-----------------
//	S'-> E $			|					|					|
//	--------------------+-------------------+-------------------+-----------------     
//  E -> A E'			|	A -> T A'		|	T -> F T'		|	
//	--------------------+-------------------+-------------------+-----------------	
//  E'-> "=" A E'		|	A'-> "+" T A'	|	T'-> "*" F T'	|	F -> NUM
//  E'->				|	A'-> "-" T A'	|	T'-> "/" F T'	|	F -> VAR
//						|	A'->			|	T'->			|	F -> "-" T
//						|					|					|	F -> "+" T	
//						|					|					|	F -> "(" E ")"
//						|					|					|	F -> STRING
//	--------------------+-------------------+-------------------+-----------------
//	Table 1.
//
//	Where :
//
//	S = Start			
//	S = StartPrime
//	E = Expr			A = Assign			T = Term			F = Factor
//	E'= ExprPrime		A'=	AssignPrime		T'= TermPrime		$ = EOL	
//	
//		|	NULLable	|	First						|	Follow
//  ----+---------------+-------------------------------+------------------------
//	S	|	no			|	VAR, NUM, STRING, (, -, +	|	
//	S'	|	yes			|	$							|
//	E	|	no			|	VAR, NUM, STRING, (, -, +	|	
//	E'	|	yes			|	=							|	$, (
//  A	|	no			|	VAR, NUM, STRING, (, -, +	|	
//  A'	|	yes			|	+, -						|	$, (, =, STRING
//  T	|	no			|	VAR, NUM, STRING, (, -,	+	|	
//  T'	|	yes			|	*, /						|	$, (, =, +, -, STRING
//  F	|	no			|	VAR, NUM, STRING, (, -,	+	|
//  ----+---------------+-------------------------------+------------------------
//	Table 2.
//
//  Combining table 1 & 2 results in the code below.
//
//  NB: operators that are left associative, must be implemented:
//            
//			return recurse(new Operator(left, right))
//
//      operators that are right associative, must be implemented:
//
//			return new Operator(left, recurse(right))
//
//
// The abstract syntax tree is based on the interpreter design pattern.
//      
// Parser reading material see : "Modern compiler implementation in Java", 
//							     Andrew W. Appel, Cambridge university press,
//							     , ISBN 0-521-58388-8, 1998, Chapter 2-4.
// 
//

//						=============
Expression*				Parser::Start()
//						=============
{
	// Read the current token; this token must be an opening parenthesis,
	// a unary plus, a unary minus, a numerical constant, a string, or
	// a cluster variable's name.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::LPAR	:	// opening parenthesis
		case Lexer::ADD		:	// unary plus operator
		case Lexer::SUB		:	// unary minus operator
		case Lexer::NUMBER	:	// numerical constant
		case Lexer::STRING	:	// string constant
		case Lexer::VAR		:	// cluster variable name
		{
			Expression* left = Expr();
			return StartPrime( left );
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::EOL:
		case Lexer::RPAR:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::ASSIGN:
		{
			// An expected token has been found, creating a syntax error;
			// report the appropriate error, and return the null pointer.
			HandleExpVarNumError( GetToken() );
			return 0;
		}

		default : 
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						==================
Expression*				Parser::StartPrime
//						==================
(
	Expression*			left
)
{
	// Read the current token; this token must be one which may follow the kind
	// of token Expr() handled; this means: an end of line.
	switch ( GetToken() )
	{
		// Valid case.
		case Lexer::EOL	 :		// end of line token
		{
			Swallow ( Lexer::EOL );
			return left;		
		}

		// Invalid case; unexpected closing parenthesis.
		case Lexer::RPAR:
		{
			// An unexpected closing parenthesis has been found, creating
			// a syntax error; Report the appropriate error, and return the
			// null pointer.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_TOKEN, ")" ) );
			return 0;
		}

		default :
		{
			// An undefined or unexpected token has been found; report 
			// an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						============
Expression*				Parser::Expr()
//						============
{
	// Read the current token; this token must be an opening parenthesis,
	// a unary plus, a unary minus, a numerical constant, a string, or
	// a cluster variable's name.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::LPAR	:	// opening parenthesis
		case Lexer::ADD		:	// unary plus operator
		case Lexer::SUB		:	// unary minus operator
		case Lexer::NUMBER	:	// numerical constant
		case Lexer::STRING	:	// string constant
		case Lexer::VAR		:	// cluster variable name
		{
			Expression* left = Assign();
			return ExprPrime( left );
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::EOL:
		case Lexer::RPAR:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::ASSIGN:
		{
			// An expected token has been found, creating a syntax error;
			// report the appropriate error, and return the null pointer.
			HandleExpVarNumError( GetToken() );
			return 0;
		}

		default : 
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						=================
Expression*				Parser::ExprPrime
//						=================
(
	Expression*			left
)
{
	// Read the current token; this token must be one which may follow the kind
	// of token Assign() handled; this means: an assignment operator, a closing
	// parenthesis, or an end of line.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::ASSIGN :	// assign operator
		{
			Swallow( Lexer::ASSIGN );
			Expression* right = Assign();
			return new AssignExpression( left, ExprPrime( right ), m_strPrecision );
		}

		case Lexer::EOL	 :		// end of line token
		case Lexer::RPAR:
		{
			// Let Start() handle the 'end of line' token.
			return left;
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::LPAR:
		case Lexer::ADD:
		case Lexer::SUB:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::NUMBER:
		case Lexer::STRING:
		case Lexer::VAR:
		{
			// An unexpected token has been found, creating a syntax error.
			// Create a vector of expected tokens.
			vector<int> vnExpTokens;
			vnExpTokens.push_back( Lexer::ASSIGN );

			// Report the appropriate error, and return the null pointer.
			HandleExpOpError( vnExpTokens );
			return 0;
		}

		default :
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						==============
Expression*				Parser::Assign()
//						==============
{
	// Read the current token; this token must be an opening parenthesis,
	// a unary plus, a unary minus, a numerical constant, a string, or
	// a cluster variable's name.
	switch( GetToken() )
	{
		// Valid cases.
		case Lexer::LPAR	:	// opening parenthesis
		case Lexer::ADD		:	// unary plus operator
		case Lexer::SUB		:	// unary minus operator
		case Lexer::NUMBER	:	// numerical constant
		case Lexer::STRING	:	// string constant
		case Lexer::VAR		:	// cluster variable name
		{
			Expression* left = Term();
			return AssignPrime( left );
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::EOL:
		case Lexer::RPAR:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::ASSIGN:
		{
			// An expected token has been found, creating a syntax error;
			// report the appropriate error, and return the null pointer.
			HandleExpVarNumError( GetToken() );
			return 0;
		}

		default : 
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						===================
Expression*				Parser::AssignPrime
//						===================
(
	Expression*			left
)
{
	// Read the current token; this token must be one which may follow the kind
	// of token Term() handled; this means: an addition, subtraction or
	// assignment operator, a closing parenthesis, or an end of line.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::ADD :	// addition operator
		{
			Swallow( Lexer::ADD );
			return AssignPrime( new AddExpression( left, Term(), m_strPrecision ) );
		}

		case Lexer::SUB :	// subtraction operator
		{
			Swallow( Lexer::SUB );
			return AssignPrime( new SubExpression( left, Term(), m_strPrecision ) );
		}

		case Lexer::EOL		:	// end of line token
		case Lexer::RPAR	:	// closing parenthesis
		case Lexer::ASSIGN	:	// assignment operator
		{
			// Let ExprPrime() handle these tokens.
			return left;
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::LPAR:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::NUMBER:
		case Lexer::STRING:
		case Lexer::VAR:
		{
			// An unexpected token has been found, creating a syntax error.
			// Create a vector of expected tokens.
			vector<int> vnExpTokens;
			vnExpTokens.push_back( Lexer::ADD );
			vnExpTokens.push_back( Lexer::SUB );
			vnExpTokens.push_back( Lexer::ASSIGN );

			// Report the appropriate error, and return the null pointer.
			HandleExpOpError( vnExpTokens );
			return 0;
		}

		default : 
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						============
Expression*				Parser::Term()
//						============
{
	// Read the current token; this token must be an opening parenthesis,
	// a unary plus, a unary minus, a numerical constant, a string, or
	// a cluster variable's name.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::LPAR	:	// opening parenthesis
		case Lexer::ADD		:	// unary plus operator
		case Lexer::SUB		:	// unary minus operator
		case Lexer::NUMBER	:	// numerical constant
		case Lexer::STRING	:	// string constant
		case Lexer::VAR		:	// cluster variable name
		{
			Expression* left = Factor();
			return TermPrime( left );
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::EOL:
		case Lexer::RPAR:
		case Lexer::MUL:
		case Lexer::DIV:
		case Lexer::ASSIGN:
		{
			// An expected token has been found, creating a syntax error;
			// report the appropriate error, and return the null pointer.
			HandleExpVarNumError( GetToken() );
			return 0;
		}

		default : 
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						=================
Expression*				Parser::TermPrime
//						=================
(
	Expression*			left
)
{
	// Read the current token; this token must be one which may follow the kind
	// of token Factor() handled; this means: an operator, or an end of line.
	switch ( GetToken() )
	{
		// Valid cases.
		case Lexer::MUL :		// multiplication operator
		{
			Swallow( Lexer::MUL );
			return TermPrime( new MulExpression( left, Factor(), m_strPrecision ) );
		}

		case Lexer::DIV	:		// division operator
		{
			Swallow( Lexer::DIV );
			return TermPrime( new DivExpression( left, Factor(), m_strPrecision ) );
		}

		case Lexer::EOL		:	// end of line token
		case Lexer::RPAR	:	// closing parenthesis
		case Lexer::ADD		:	// addition operator
		case Lexer::SUB		:	// subtraction operator
		case Lexer::ASSIGN	:	// assignment operator
		{
			// Let AssignPrime() handle these tokens.
			return left;
		}

		// Invalid cases; lexical errors.
		case Lexer::ERROR_STRING:
		case Lexer::ERROR_NUM_DEC:
		case Lexer::ERROR_NUM_EXP:
		case Lexer::ERROR_INV_TOK:
		{
			// A lexical error has been found (invalid string, number or
			// other token); report the appropriate error, and return the
			// null pointer.
			HandleLexerError( GetToken() );
			return 0;
		}

		// Invalid cases; unexpected tokens.
		case Lexer::LPAR:
		case Lexer::NUMBER:
		case Lexer::STRING:
		case Lexer::VAR:
		{
			// An unexpected token has been found, creating a syntax error.
			// Create a vector of expected tokens.
			vector<int> vnExpTokens;
			vnExpTokens.push_back( Lexer::MUL );
			vnExpTokens.push_back( Lexer::DIV );
			vnExpTokens.push_back( Lexer::ADD );
			vnExpTokens.push_back( Lexer::SUB );
			vnExpTokens.push_back( Lexer::ASSIGN );

			// Report the appropriate error, and return the null pointer.
			HandleExpOpError( vnExpTokens );
			return 0;
		}

		default :
		{
			// An undefined token has been found; report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}


//						==============
Expression*				Parser::Factor()
//						==============
{
	// Read the current token; this token must be an opening parenthesis,
	// a unary plus, a unary minus, a numerical constant, a string, or
	// a cluster variable's name.
	switch( GetToken() )
	{
		case Lexer::LPAR :		// opening parenthesis
		{
			Swallow( Lexer::LPAR );
			Expression* right = Expr();
			Swallow( Lexer::RPAR );
			return right;
		}

		case Lexer::ADD :		// unary plus
		{
			Swallow(Lexer::ADD);
			return new MulExpression(new NumExpression("1", m_strPrecision), Term(), m_strPrecision);
		}

		case Lexer::SUB :		// unary minus
		{
			Swallow(Lexer::SUB);
			return new MulExpression(new NumExpression("-1", m_strPrecision), Term(), m_strPrecision);
		}

		case Lexer::NUMBER :	// numerical constant
		{
			string strNumber = m_pTheLexer->GetCurrentTokenValue();
			Swallow( Lexer::NUMBER );
			return new NumExpression( strNumber, m_strPrecision );			
		}

		case Lexer::STRING :	// string constant
		{
			string strString = m_pTheLexer->GetCurrentTokenValue();
			Swallow( Lexer::STRING );
			return new StrExpression( strString, m_strPrecision );
		}

		case Lexer::VAR :		// cluster variable name
		{
			string strVariableName = m_pTheLexer->GetCurrentTokenValue();
			Swallow( Lexer::VAR );
			return new VarExpression( strVariableName, m_strPrecision );
		}

		default :
		{
			// An undefined or unexpected token has been found; report an
			// internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			return 0;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// Parser support methods

//						================
void					Parser::SetToken
//						================
(
	int					nToken
)
{
	m_nToken = nToken;
}


//						================
int						Parser::GetToken() const
//						================
{
	return m_nToken;
}


//						===============
void					Parser::Advance()
//						===============
{
	SetToken( m_pTheLexer->GetToken() );
}


//						===============
void					Parser::Swallow
//						===============
(
	int nToken
)
{
	// Current token equal swallow it, else error
	if ( GetToken() == nToken ) 
	{
		Advance(); 
	}
	else 
	{
		Error(m_pErrorList->GetText(ErrorList::ID_ERR_INTERNAL_ERROR));
	}
}

//						=============
void					Parser::Error
//						=============
(
	const string&		strMessage
)
{	
	// Log the syntax error message in the right language, only once
	if ( m_ncSyntaxError == 0 )
	{
		m_vstrErrorVector.push_back( strMessage );
	}

	// Increase error counter
	m_ncSyntaxError++;
}


//						========================
void					Parser::HandleLexerError
//						========================
(
	int					nErrorCode
)
{
	// Determine the specified error code.
	switch ( nErrorCode )
	{
		case Lexer::ERROR_STRING:
		{
			// A string has been found for which no closing double quote
			// has been stated in the expression.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INVALID_STRING ) );
			break;
		}

		case Lexer::ERROR_NUM_DEC:
		{
			// A numerical constant consisting of only a decimal point has
			// been found; i.e., no integer and no fractional part.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_NUM_ONLY_DEC ) );
			break;
		}
		
		case Lexer::ERROR_NUM_EXP:
		{
			// A numerical constant has been found for which an exponent sign
			// (E or e) has been stated, but no exponent.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_NUM_NO_EXP ) );
			break;
		}
		
		case Lexer::ERROR_INV_TOK:
		{
			// A numerical constant has been found for which an exponent sign
			// (E or e) has been stated, but no exponent.
			string strToken = m_pTheLexer->GetCurrentTokenValue();
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INVALID_TOKEN, strToken ) );
			break;
		}

		default:
		{
			// This function may not be called with an error code other than
			// returned by the lexer; so report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			break;
		}
	}
}


//						============================
void					Parser::HandleExpVarNumError
//						============================
(
	int					nToken
)
{
	// Determine the specified token.
	switch ( nToken )
	{
		case Lexer::EOL:
		{
			// An unexpected end of the expression was found, while a constant
			// or variable was expected.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_EOL ) );
			break;
		}

		case Lexer::RPAR:		// closing parenthesis
		case Lexer::MUL:		// multiplication operator
		case Lexer::DIV:		// division operator
		case Lexer::ASSIGN:		// assignment operator
		{
			// An unexpected operator was found, while a constant or variable
			// was expected.
			string strToken = m_pTheLexer->GetCurrentTokenValue();
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_ISO_NUMVAR, strToken ) );
			break;
		}

		default:
		{
			// This function may not be called with an code other than the
			// specified operator token; so report an internal error.
			Error( m_pErrorList->GetText( ErrorList::ID_ERR_INTERNAL_ERROR ) );
			break;
		}
	}
}


//						========================
void					Parser::HandleExpOpError
//						========================
(
	vector<int>			vnExpTokens
)
{
	// Create a string out of the vector with expected token codes.
	string strExpTokens;

	// Go through all expected tokens.
	int i;
	for ( i = 0; i < vnExpTokens.size(); ++i )
	{
		// Add the token's value to the string.
		strExpTokens += m_pTheLexer->GetTokenValue( vnExpTokens[i] );

		// If the token is not the last one, add a comma and a blank
		// to the string.
		if ( i < vnExpTokens.size() - 1 )
		{
			strExpTokens += ", ";
		}
	}

	// Get the value of the unexpected token, i.e., of the current token.
	string strToken = m_pTheLexer->GetCurrentTokenValue();

	// Report an error about the expected token.
	Error( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_ISO_OP, strToken, strExpTokens ) );
}
