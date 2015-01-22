/*****************************************************************************
 * $Workfile: Parser.h $
 * $Revision: 6 $
 * $Modtime: 8/15/01 5:27p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef PARSER_H
#define PARSER_H

//Includes
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class Context;
class ErrorList;
class Expression;
class Lexer;
class Setting;

////////////////////////////////////////////////////////////////////////////////
// class Parser
class Parser 
{
// Construction and destruction
public:
	Parser();							// Default constructor
private:
	Parser( const Parser& right );		// Copy constructor
	Parser& operator=(Parser&);
public:
	virtual ~Parser();					// Destructor

	///////////////////////////////////////////////////////////////////////////////
	// Attributes and operations

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialise()
	//
	// description	: Initialises the parser with values from the
	//				  setting object;
	//					
	// parameters	: Setting*					association to setting
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Initialise( Setting* pSetting );

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetContext(Context*)
	//
	// description	: Sets the parser context which is used for evaluating the ast.
	//					
	// parameters	: Context*			pointer to a context object.
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetContext( Context* pContext );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetResult()
	//
	// description	: Returns the parse-evaluate result.
	//				  Only valid after succesfull parse.
	//					
	// parameters	: None.
	//
	// returns		: string&			parse-evaluate result.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const string& GetResult() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetErrorVector()
	//
	// description	: Return a reference to the the error vector
	//					
	// parameters	: none
	//
	// returns		: vector&			error vector.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const vector<string>& GetErrorVector() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Parse()
	//
	// description	: Parses and evaluates an expression.
	//					
	// parameters	: strExpression				expression string
	//
	// returns		: true		succesfull parse
	//				  false		an error occured
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Parse( const string& strExpression );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ParseVariable()
	//
	// description	: This function parses the specified string as a name of a
	//				  cluster variable. If it is not valid as a cluster variable's
	//				  name, an error is added to the error vector.
	//					
	// parameters	: strVariable	name of the cluster variable to parse
	//
	// returns		: true		specified name is a valid variable name
	//				  false		specified name is not a valid variable name
	///////////////////////////////////////////////////////////////////////////////
	bool ParseVariable( const string& strVariable );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearErrors()
	//
	// description	: This function clears the error vector, and resets the number
	//				  of errors to zero.
	//					
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void ClearErrors();

	///////////////////////////////////////////////////////////////////////////////
	// function		: NotifyMissingDateFormat()
	//
	// description	: This function offers the possibility to notify the parser
	//				  that a the date-format is missing or in an evaluated date-
	//				  command.
	//					
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void NotifyMissingDateFormat();

	///////////////////////////////////////////////////////////////////////////////
	// function		: NotifyMissingTimeFormat()
	//
	// description	: This function offers the possibility to notify the parser
	//				  that a the time-format is missing or in an evaluated time-
	//				  command.
	//					
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void NotifyMissingTimeFormat();

	///////////////////////////////////////////////////////////////////////////////
	// Implementation
private:
	// Parser functions

	///////////////////////////////////////////////////////////////////////////////
	// function		: Start
	//
	// description	: Parser S -> E $ production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			Abstract syntax tree root
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* Start();

	///////////////////////////////////////////////////////////////////////////////
	// function		: StartPrime()
	//
	// description	: 
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* StartPrime( Expression* );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Expr()
	//
	// description	: Parser E -> A E'		production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* Expr();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ExprPrime()
	//
	// description	: Parser E' -> '=' A E' 
	//				  Parser E' ->			production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* ExprPrime( Expression* );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Assign()
	//
	// description	: Parser A' -> T A'		production 
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* Assign();

	///////////////////////////////////////////////////////////////////////////////
	// function		: AssignPrime()
	//
	// description	: Parser A' -> '+' T A' 
	//				  Parser A' -> '-' T A'
	//				  Parser A' ->			production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* AssignPrime( Expression* );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Term()
	//
	// description	: Parser T -> F T'		production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* Term();

	///////////////////////////////////////////////////////////////////////////////
	// function		: TermPrime()
	//
	// description	: Parser T' -> '*' F T' 
	//				  Parser T' -> '/' F T'
	//				  Parser T' ->			production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* TermPrime( Expression* );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Factor()
	//
	// description	: Parser F -> VAR 
	//				  Parser F -> NUM
	//				  Parser F -> STRING
	//				  Parser F -> '-' T
	//				  Parser F -> '+' T
	//				  Parser F -> '(' E ')'	production
	//					
	// parameters	: none.
	//
	// returns		: Expression*			A subclass of expression
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Expression* Factor();

	// Parser support functions

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetToken(nToken)
	//
	// description	: Set the current token
	//
	// parameters	: nToken				Lexer::TOKEN
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetToken( int nToken );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetToken()
	//
	// description	: Get the current token
	//					
	// parameters	: None.
	//
	// returns		: nToken				Lexer::TOKEN
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetToken() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Advance()
	//
	// description	: Advances to the next token.
	//					
	// parameters	: None.
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Advance();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Swallow(nToken)
	//
	// description	: Swallows the current token and advanced to the next. If the
	//				  current token differs from the which must be swallowed an
	//				  internal error is generated.
	//					
	// parameters	: nToken				Lexer::TOKEN
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Swallow( int nToken );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Error(strMessage)
	//
	// description	: Adds the first syntax error to the error vector.
	//					
	// parameters	: strMessage			Error message
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Error( const string& strMessage );

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleLexerError()
	//
	// description	: This function reports an error found by the lexer, specified
	//				  by a code.
	//					
	// parameters	: nErrorCode	error code returned by the lexer
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void HandleLexerError( int nErrorCode );

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleExpVarNumError()
	//
	// description	: This function reports an error about an encountered token,
	//				  specified by the parameter, instead of a constant or a
	//				  variable.
	//					
	// parameters	: nToken		token code
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void HandleExpVarNumError( int nToken );

	///////////////////////////////////////////////////////////////////////////////
	// function		: HandleExpOpError()
	//
	// description	: This function reports an error about an unexpectedly
	//				  encountered token, the current one, instead of one of the
	//				  tokens specified by the parameter.
	//					
	// parameters	: vnExpTokens	vector of expected token codes
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void HandleExpOpError( vector<int> vnExpTokens );

	// Member variables
private:
	Lexer*			m_pTheLexer;				// Lexer asscociation
	int				m_nToken;					// Current token
	vector<string>	m_vstrErrorVector;			// Error vector
	string			m_strResult;				// Parser + evaluate result string
	int				m_ncSyntaxError;			// Syntax error counter
	ErrorList*		m_pErrorList;				// Multilanguage error string producer
	Context*		m_pContext;					// Current evaluation context
	string			m_strPrecision;				// Precision format from settings
};

#endif // !PARSER_H