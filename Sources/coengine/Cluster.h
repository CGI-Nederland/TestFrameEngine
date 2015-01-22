/*****************************************************************************
 * $Workfile: Cluster.h $
 * $Revision: 10 $
 * $Modtime: 8/16/01 6:28p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CLUSTER_H
#define CLUSTER_H

// Includes
#include <stack>
#include <string>

using namespace std;

#undef BASECLASS
#define BASECLASS TestLine

#include "TestLine.h"				// Baseclass definition

//*
#include "Cache.h"
#include "CacheIterator.h"
#include "ComposedInterpreter.h"
#include "Context.h"
#include "EngineSetting.h"
#include "IOInterface.h"
#include "Log.h"
//*/

/*
// Forward declarations
class Cache;
class CacheIterator;
class ComposedInterpreter;
class Context;
class EngineSetting;
class IOInterface;
class Log;
//*/

class Cluster : public TestLine
{
// Constants
public:
	enum CLUSTERTYPE	{
							TYPE_CLUSTER,
							TYPE_TEMPLATE
						};

	enum CONTROLFLOW	{	IF,
							REPEAT,
							WHILE,
							UNDEFINED
						};

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of Cluster
	// needed by ActionServer to make a vector of Clusters
	///////////////////////////////////////////////////////////////////////////////
	Cluster();
	Cluster(Cluster&);
	Cluster& operator=(Cluster&);
	///////////////////////////////////////////////////////////////////////////////
	// constructor of Cluster
	//
	// parameters	: strFilename		name of the cluster file to construct
	//									Cluster object for
	//				  pInterpreter		pointer to the Composed Interpreter
	//				  pSetting			pointer to the Setting object
	//				  nType				cluster type
	//				  bCreateLog		states if a log for the cluster should be
	//										created (default true)
	///////////////////////////////////////////////////////////////////////////////
	Cluster( const string& strFileName, ComposedInterpreter* pInterpreter, 
			 EngineSetting* pSetting, CLUSTERTYPE nType, bool bCreateLog = true );
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of Cluster
	///////////////////////////////////////////////////////////////////////////////
	~Cluster();

// Public interface
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetType()
	//
	// description	:	This function returns the cluster type
	//
	// parameters	:	-
	//
	// returns		:	integer specifying type
	///////////////////////////////////////////////////////////////////////////////
	CLUSTERTYPE GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReadLine()
	// description	: This function reads a (complete) test line.
	//
	// parameters	: <none>
	//
	// returns		: TRUE		test line read successfully
	//				  FALSE		end of file encountered
	///////////////////////////////////////////////////////////////////////////////
	bool ReadLine();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Interpret()
	//
	// description	:	This function interprets the current cluster line.
	//
	// parameters	:	<none>
	//
	// returns		:	true	no errors found in current cluster line
	//					false	errors found in current cluster line
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretExceptParameters()
	//
	// description	:	This function interprets the current cluster line, but does
	//					not parse the parameters.
	//
	// parameters	:	<none>
	//
	// returns		:	true	no errors found in current cluster line
	//					false	errors found in current cluster line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretExceptParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretLineType()
	//
	// description	:	This function interprets action word type of the current
	//					cluster line; action
	//					word, arguments, and (if appropriate) slave name.
	//
	// parameters	:	<none>
	//
	// returns		:	true	no errors found in current cluster line
	//					false	errors found in current cluster line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretLineType();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTotalLine()
	// description	: This function returns the total number of lines in the
	//					cluster file.
	//
	// parameters	: <none>
	//
	// returns		: total number of lines
	///////////////////////////////////////////////////////////////////////////////
	long int GetTotalLine();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLineNumber()
	// description	: This function returns the number of the current test line
	//
	// parameters	: <none>
	//
	// returns		: number of current test line
	///////////////////////////////////////////////////////////////////////////////
	long int GetLineNumber() const;
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteLine()
	// description	: This function appends a new line containing the string
	//					strLine to the cluster file.
	//
	// parameters	: strLine		line to append to file
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void WriteLine(const string& strLine) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFileName()
	// description	: This function returns the name of the cluster file.
	//
	// parameters	: <none>
	//
	// returns		: string containing the name of the cluster file
	///////////////////////////////////////////////////////////////////////////////
	const string& GetFileName() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetContext()
	// description	: This function returns a pointer to the context object of the
	//				  cluster.
	//
	// parameters	: <none>
	//
	// returns		: pointer to context object
	///////////////////////////////////////////////////////////////////////////////
	Context* GetContext() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Good()
	// description	: This function returns if the cluster is ok and ready for use.
	//
	// parameters	: <none>
	//
	// returns		: TRUE		cluster can be used
	//				  FALSE		cluster cannot be used 
	///////////////////////////////////////////////////////////////////////////////
	bool Good() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: BeginConditionalLoop()
	//
	// description	: This function handles the start of a conditional loop.
	//
	// parameters	: bCondition	bool stating whether the conditional loop is to
	//								be executed
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void BeginConditionalLoop( bool bCondition );

	///////////////////////////////////////////////////////////////////////////////
	// function		: BeginUnconditionalLoop()
	//
	// description	: This function handles the start of an unconditional loop.
	//
	// parameters	: nIterations	number of loops to go
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void BeginUnconditionalLoop( int nIterations );

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetUnconditionalLoop()
	//
	// description	: This function sets the number of loops to go for the current
	//				  iterator, if it's unconditional.
	//
	// parameters	: nIterations	number of loops to go
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetUnconditionalLoop( int nIterations );

	///////////////////////////////////////////////////////////////////////////////
	// function		: EndConditionalLoop()
	//
	// description	: This function handles the end of a conditional loop.
	//
	// parameters	: None.
	//
	// returns		: true		the condition was true
	//				  false		the condition was false
	///////////////////////////////////////////////////////////////////////////////
	bool EndConditionalLoop();

	///////////////////////////////////////////////////////////////////////////////
	// function		: EndUnconditionalLoop()
	//
	// description	: This function handles the end of an unconditional loop.
	//
	// parameters	: None.
	//
	// returns		: true		the loop must be repeated
	//				  false		the loop must not be repeated
	///////////////////////////////////////////////////////////////////////////////
	bool EndUnconditionalLoop();

	///////////////////////////////////////////////////////////////////////////////
	// function		: BeginIfStatement()
	//
	// description	: This function handles the beginning of an if-statement.
	//
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void BeginIfStatement();

	///////////////////////////////////////////////////////////////////////////////
	// function		: EndIfStatement()
	//
	// description	: This function handles the end of an if-statement.
	//
	// parameters	: None.
	//
	// returns		: true		if-statement removed from stack
	//				  false		if-statement is not current control flow element
	///////////////////////////////////////////////////////////////////////////////
	bool EndIfStatement();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetControlFlow()
	//
	// description	: This function returns the current type of the flow of control.
	//				  If there is none, UNDEFINED is returned.
	//
	// parameters	: None.
	//
	// returns		: CONTROLFLOW enum integer specifying flow of control type
	///////////////////////////////////////////////////////////////////////////////
	CONTROLFLOW GetControlFlow() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCurrentLoopCounter()
	//
	// description	: This function returns the counter of the current loop; if the
	//				  cluster is currently not processing a loop, -1 is returned.
	//
	// parameters	: None.
	//
	// returns		: integer specifying current loop counter
	///////////////////////////////////////////////////////////////////////////////
	int GetCurrentLoopCounter() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCurrentLoopTotal()
	//
	// description	: This function returns the total number of loops specified for
	//				  the current loop; if the cluster is currently not processing a
	//				  loop, -1 is returned. Note that if the current loop is a
	//				  conditional one, the return value can only be 0 or 1.
	//
	// parameters	: None.
	//
	// returns		: integer specifying total loops set for current loop
	///////////////////////////////////////////////////////////////////////////////
	int GetCurrentLoopTotal() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetSection()
	//
	// description	: This function sets the name of the currect section.
	//
	// parameters	: strSection	name of the section
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetSection( const string& strSection );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSection()
	//
	// description	: This function returns the name of the currect section.
	//
	// parameters	: None
	//
	// returns		: name of the current section
	///////////////////////////////////////////////////////////////////////////////
	const string& GetSection() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetScenario()
	//
	// description	: This function sets the name of the currect scenario.
	//
	// parameters	: strScenario	name of the scenario
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetScenario( const string& strScenario );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetScenario()
	//
	// description	: This function returns the name of the currect scenario.
	//
	// parameters	: None
	//
	// returns		: name of the current scenario
	///////////////////////////////////////////////////////////////////////////////
	const string& GetScenario() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTestCase()
	//
	// description	: This function sets the name of the currect test case.
	//
	// parameters	: strTestCase	name of the test case
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetTestCase( const string& strTestCase );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCase()
	//
	// description	: This function returns the name of the currect test case.
	//
	// parameters	: None
	//
	// returns		: name of the current test case
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTestCase() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTestCondition()
	//
	// description	: This function sets the name of the currect test condition.
	//
	// parameters	: strTestCondition	name of the test condition
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetTestCondition( const string& strTestCondition );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCondition()
	//
	// description	: This function returns the name of the currect test condition.
	//
	// parameters	: None
	//
	// returns		: name of the current test condition
	///////////////////////////////////////////////////////////////////////////////
	const string& GetTestCondition() const;

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		: Read()
	// description	: This private function reads one line from the cluster file
	//					and copies its content to m_strPhysline.
	//
	// parameters	: <none>
	//
	// returns		: TRUE		line could be read
	//				  FALSE		no line could be read
	///////////////////////////////////////////////////////////////////////////////
	bool Read();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCurentTestLine()
	// description	: This private function gets the current test line from the
	//					cluster file. This means that a check must be performed to
	//					see if a test line is not split into several physical lines.
	//					If so, one test line is made up out of these. If a line is
	//					split and there is comment in between, as curent test line
	//					the concatenated comment line is given and the split line
	//					is buffered.
	//
	// parameters	: OUT	strTestLine		string to be filled with the current
	//											test line
	//
	// returns		: TRUE		current test line read
	//				  FALSE		no test line could be read
	///////////////////////////////////////////////////////////////////////////////
	bool GetCurrentTestLine(string& strTestLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckForComment()
	//
	// description	: This function checks if the specified vector of arguments is
	//				  that of a comment line; if, so the second parameter is filled
	//				  with the comment arguments.
	//
	// parameters	: vstrArgs			vector of arguments to check
	//				  vstrComment		vector to be filled with comment arguments
	//
	// returns		: true		arguments comprise a comment line
	//				  false		arguments don't comprise a comment line
	///////////////////////////////////////////////////////////////////////////////
	bool CheckForComment( const vector<string>& vstrArgs, vector<string>& vstrComment );

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckForComment()
	//
	// description	: This function checks if the specified vector of arguments is
	//				  that of a comment line.
	//
	// parameters	: vstrArgs			vector of arguments to check
	//
	// returns		: true		arguments comprise a comment line
	//				  false		arguments don't comprise a comment line
	///////////////////////////////////////////////////////////////////////////////
	bool CheckForComment( const vector<string>& vstrArgs );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertRECharactersInLine()
	// description	: This private function converts all redundant escape
	//					characters in a specified line. These are the characters
	//					that are stored in the member variable
	//					m_strRedundantEscapeCharacters. Each single occurence of
	//					such a character is removed from the line, while double
	//					occurences are replaced by single ones.
	//
	// parameters	: OUT strLine	line to be converted
	//
	// returns		: TRUE		redundant escape characters in line converted
	//				  FALSE		no redundant escape characters in line found
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertRECharactersInLine(string& strLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertRECharactersInArgument()
	//
	// description	: This function converts all redundant escape characters in a
	//				  specified argument.
	//
	// parameters	: strArgument
	//
	// returns		: true		redundant escape characters in argument converted
	//				  false		no redundant escape characters in argument found
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertRECharactersInArgument( string& strArgument );

	///////////////////////////////////////////////////////////////////////////////
	// function		: LineToArguments()
	//
	// description	: This function splits a specified line into arguments, and
	//				  returns a vector containing these.
	//
	// parameters	: strLine	line to be split
	//
	// returns		: vector containing the line's arguments
	///////////////////////////////////////////////////////////////////////////////
	vector<string> LineToArguments( const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ArgumentsToLine()
	//
	// description	: This function pastes together the elements of a vector,
	//				  separated by the delimiter, to one string, and returns this.
	//
	// parameters	: vstrArguments		arguments to concatenate
	//
	// returns		: string containing the concatenated arguments.
	///////////////////////////////////////////////////////////////////////////////
	string ArgumentsToLine( const vector<string>& vstrArguments );

	///////////////////////////////////////////////////////////////////////////////
	// function		: BeginLoop()
	//
	// description	: This function updates the cache and its iterators about the
	//				  start of a loop. If the cache is empty, or the current loop
	//				  is open, a new iterator is added to the stack; otherwise, if
	//				  the loop is conditional, the number of loops to go is reset.
	//
	// parameters	: nType			type of loop
	//				  nLoopsToGo	number of iterations for the new loop
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void BeginLoop( int nType, int nLoopsToGo );

	///////////////////////////////////////////////////////////////////////////////
	// function		: EndLoop()
	//
	// description	: This function updates the cache and its iterators about the
	//				  end of a loop. If the iterator is open, it is closed; if the
	//				  loop is unconditional, the number of loops to go is
	//				  decremented. The (new) number of loops to go is determined,
	//				  if it is greater than zero, true is returned.
	//
	// parameters	: None.
	//
	// returns		: true		the loop must be repeated
	//				  false		the loop must not be repeated
	///////////////////////////////////////////////////////////////////////////////
	bool EndLoop();

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddIterator()
	//
	// description	: This function adds an iterator of specified type to the
	//				  stack. It furthermore updates the control flow stack.
	//
	// parameters	: nType			type of iterator
	//				  nPos			start position in cache
	//				  nLoopsToGo	number of loops to go
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void AddIterator( int nType, int nPos, int nLoopsToGo );

	///////////////////////////////////////////////////////////////////////////////
	// function		: RemoveIterator()
	//
	// description	: This function removes the latest iterator from stack. It
	//				  furthermore updates the control flow stack.
	//
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void RemoveIterator();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLineFromCache()
	//
	// description	: This function moves to the next line in the cache, and fills
	//				  the referenced parameter with its contents. If the loop has
	//				  ended, this function will return to the enclosing loop. If
	//				  it's at the end of the cache is emptied.
	//
	// parameters	: strLine		to be filled with found cluster line
	//				  nLineNumber	to be filled with number of found line
	//
	// returns		: true		a line from the cache is found
	//				  false		the cache is empty
	///////////////////////////////////////////////////////////////////////////////
	bool GetLineFromCache( string& strLine, int& nLineNumber );

// member variables
private:
	CLUSTERTYPE			 m_nType;					// cluster type (cluster/template)
	bool				 m_bCreateLog;				// states if a log object should be created
	bool				 m_bState;					// cluster state
	ComposedInterpreter* m_pInterpreter;			// pointer to the interpreter
	Log*				 m_pLog;					// pointer to the cluster specific log object
	Context*			 m_pContext;				// pointer to the cluster specific context object
	IOInterface*		 m_pIOInterface;			// pointer to IOInterface
	string				 m_strPhysLine;				// current physical line
	string				 m_strTestLineBuffer;		// buffer containing test line
	string				 m_strCommentBuffer;		// buffer containing latest comment line
	string				 m_strFileName;				// name of the cluster file
	string				 m_strContToken;			// continue token
	string				 m_strRedundantEscapeChars;	// redundant escape characters
	long int			 m_nTotalLines;				// number of lines in cluster file
	long int			 m_nPhysLineNbr;			// number of the current physical (file) line
	long int			 m_nLineNumber;				// number of the current test line

	string				 m_strSection;				// current section name
	string				 m_strScenario;				// current scenario name
	string				 m_strTestCase;				// current test case name
	string				 m_strTestCondition;		// current test condition name

	Cache*				 m_pCache;					// pointer to the cache
	stack<CacheIterator> m_sCacheIterators;			// stack of active cache iterators
	int					 m_nClosedIterators;		// number of closed iterators in the stack
	stack<CONTROLFLOW>	 m_siControlFlow;			// stack of active control flow elements

	static const string	 m_strDelimiter;			// internal test line delimiter
};

#undef BASECLASS
#endif // !CLUSTER_H
