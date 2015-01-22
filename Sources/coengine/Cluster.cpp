/*****************************************************************************
 * $Workfile: Cluster.cpp $
 * $Revision: 18 $
 * $Modtime: 8/16/01 6:29p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "Cluster.h"				// Class definition

// Includes
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

#include "ActionWordList.h"
#include "Cache.h"
#include "CacheIterator.h"
#include "ComposedInterpreter.h"
#include "Context.h"
#include "EngineSetting.h"
#include "Log.h"
#include "IOFactory.h"
#include "IOInterface.h"
#include "StrUtil.h"			// Needed for trim functionality and 
								// vector-string conversions.

///////////////////////////////////////////////////////////////////////////////
// Constants

// set internal test line delimiter to tab
const string Cluster::m_strDelimiter = "\t";


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						================
						Cluster::Cluster()
//						================
{
	// empty
}


// Other constructors
//						================
						Cluster::Cluster
//						================
(
	const string&			strFileName,	// name of the cluster file to construct
											//	Cluster object for
	ComposedInterpreter*	pInterpreter,	// pointer to the Composed Interpreter
	EngineSetting*			pSetting,		// pointer to the EngineSetting
	CLUSTERTYPE				nType,			// cluster type
	bool					bCreateLog		// states if a log should be created (default true)
)
{
	// Set cluster type.
	m_nType = nType;

	// determine whether to create a log object for this cluster or not
	m_bCreateLog = bCreateLog;

	// set linenumbers to default
	m_nTotalLines	= -1;
	m_nPhysLineNbr	= 0;

	// set pointer to the Interpreter
	m_pInterpreter	= pInterpreter;

	// open cluster file
	m_strFileName	= strFileName;
	
	IOFactory Factory;

	m_pIOInterface = Factory.CreateIOInterface(m_strFileName);
	m_pIOInterface->Open(IOInterface::IOREAD);					// Block here

	// set cluster state to default
	m_bState = false;

	// set cluster state
	if (m_pIOInterface->IsOpen())
	{ m_bState = true; }

	// create log object
	if ( m_bCreateLog && m_bState )
	{
		m_pLog = Log::Instance();
		m_pLog->SetLineNumber( 0 );
	}
	else
	{
		m_pLog = 0;
	}

	// create context
	Context* pContext	= new Context();
	m_pContext			= pContext;

	// get continue token from Setting
	m_strContToken = pSetting->Get("SYSTEM", "ContText");

	// get the redundant escape character string from Setting
	m_strRedundantEscapeChars = pSetting->Get("SYSTEM", "RedundantEscapeChars");

	// Create the cache, and set the number of closed iterators to zero.
	m_pCache = new Cache();
	m_nClosedIterators = 0;

	// Set empty strings as the	default names of the current section, scenario,
	// test case, and test condition.
	m_strSection = "";
	m_strScenario = "";
	m_strTestCase = "";
	m_strTestCondition = "";
}


// Destructor
//						=================
						Cluster::~Cluster()
//						=================
{
	// delete context object
	delete m_pContext;
	
	m_pContext=0;

	// delete IOInterface object
	IOFactory Factory;
	m_pIOInterface->Close(); 
	Factory.DestroyIOInterface(m_pIOInterface);

	// Delete the cache.
	delete m_pCache;
	m_pCache=0;
}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						================
Cluster::CLUSTERTYPE	Cluster::GetType() const
//						================
{
	return m_nType;
}


//						=================
bool					Cluster::ReadLine()
//						=================
{
	bool bResult = false;	// result of ReadLine

	// initialize variables for current test line	
	m_strTestLine.erase();
	m_bActionValid		= false;
	m_bMasterSlaveValid = false;
	m_bArgumentsValid	= false;
	m_nActionType		= ActionWordList::UNDEFINED;
	m_strAction.erase();
	m_strSlaveName.erase();
	m_vstrArguments.clear();
	m_vstrArgumentErrors.clear();
	m_bInterpretResult	= false;

	string strTestLine;		// to be filled with current test line
	int    nLineNumber;		// to be filled with current test line number

	// Determine if a line can be retrieved from the cache, and if so,
	// get it.
	if ( GetLineFromCache( strTestLine, nLineNumber ) )
	{
		// Update line contents and number to the ones found in the cache.
		m_strTestLine = strTestLine;
		m_nLineNumber = nLineNumber;
		bResult		  = true;
	}
	else		
	{
		// Determine if a test line can be read from cluster file, and if
		// so, get it.
		if ( GetCurrentTestLine( strTestLine ) )
		{
			// Update the test line content.
			m_strTestLine = strTestLine;
			
			// Add the test line to the cache. Note that it will only be
			// added if the cache is in recording mode; otherwise nothing
			// will change.
			if ( m_pCache->Add( m_nLineNumber, m_strTestLine ) )
			{
				// Update the position of the current iterator.
				m_sCacheIterators.top().SetPosition( m_pCache->Size() - 1 );
			}

			bResult = true;
		}
	}

	if ( m_pLog != 0 )
	{
		// Determine if a cluster line was found.
		if ( bResult )
		{
			// Update the line number, and log the reading of a cluster line.
			m_pLog->SetLineNumber( m_nLineNumber );
			m_pLog->ClusterLine( StrToVector( m_strTestLine, m_strDelimiter ) );
		}
		else
		{
			// End of the cluster; (re)set the line number to 0.
			m_pLog->SetLineNumber( 0 );
		}
	}

	return bResult;
}


//						==================
bool					Cluster::Interpret()
//						==================
{
	// Send the current cluster line to the Interpreter, and store the
	// result in its member.
	m_bInterpretResult = m_pInterpreter->Interpret( m_strTestLine );

	// Get all the properties of the interpreted cluster line from the
	// Interpreter, and store them.
	m_bActionValid		 = m_pInterpreter->GetActionWordValidity();
	m_bMasterSlaveValid	 = m_pInterpreter->GetSlaveNameValidity();
	m_bArgumentsValid	 = m_pInterpreter->GetParametersValidity();
	m_strAction			 = m_pInterpreter->GetActionWordFunction();
	m_strSlaveName		 = m_pInterpreter->GetSlaveName();
	m_vstrArguments		 = m_pInterpreter->GetParameters();
	m_nActionType		 = m_pInterpreter->GetActionType();
	m_vstrArgumentErrors = m_pInterpreter->GetErrorVector();

	// Return the interpretation result of the current test line.
	return m_bInterpretResult;
}


//						==================================
bool					Cluster::InterpretExceptParameters()
//						==================================
{
	// Send the current cluster line to the Interpreter; however, let the
	// parameters not be parsed; store the result in its member.
	m_bInterpretResult = m_pInterpreter->InterpretExceptParameters( m_strTestLine );

	// Get all the properties of the interpreted cluster line from the
	// Interpreter, and store them.
	m_bActionValid		 = m_pInterpreter->GetActionWordValidity();
	m_bMasterSlaveValid	 = m_pInterpreter->GetSlaveNameValidity();
	m_bArgumentsValid	 = m_pInterpreter->GetParametersValidity();
	m_strAction			 = m_pInterpreter->GetActionWordFunction();
	m_strSlaveName		 = m_pInterpreter->GetSlaveName();
	m_vstrArguments		 = m_pInterpreter->GetParameters();
	m_nActionType		 = m_pInterpreter->GetActionType();
	m_vstrArgumentErrors = m_pInterpreter->GetErrorVector();

	// Return the interpretation result of the current test line.
	return m_bInterpretResult;
}


//						=====================
long int				Cluster::GetTotalLine()
//						=====================
{
	// check cluster state
	if (Good())
	{
		string s;		// string to copy file line to

		IOFactory Factory;
		IOInterface* pIOInterface;

		// create interface to cluster file
		pIOInterface = Factory.CreateIOInterface(m_strFileName); 

		// Check if lines are countable
		if (pIOInterface->IsCountable())
		{

			// open cluster file
			pIOInterface->Open(IOInterface::IOREAD);

			// check if file is open
			if (pIOInterface->IsOpen())
			{
				// determine number of lines in file
				for (m_nTotalLines = 0 ; pIOInterface->Read(s) ; m_nTotalLines++)
				{}

				pIOInterface->Close(); // close cluster file
			}
		}
		// destroy interface to cluster file
		Factory.DestroyIOInterface(pIOInterface);
	}

	return m_nTotalLines;
}


//						======================
long int				Cluster::GetLineNumber() const
//						======================
{
	return m_nLineNumber;
}


//						==================
void					Cluster::WriteLine
//						==================
(
	const string&		strLine	// line to append to file
) const
{
	IOFactory Factory;
	IOInterface* pIOInterface;
	ostringstream ossLine;

	pIOInterface = Factory.CreateIOInterface(m_strFileName);	// create interface to cluster file

	pIOInterface->Open(IOInterface::IOAPPEND);	// open cluster file

	ossLine << strLine << endl;

	pIOInterface->Write(ossLine.str()); // append line to cluster file

	pIOInterface->Close();	// close cluster file

	Factory.DestroyIOInterface(pIOInterface); // destroy interface to cluster file
}


//						====================
const string&			Cluster::GetFileName() const
//						====================
{
	return m_strFileName;
}


//						===================
Context*				Cluster::GetContext() const
//						===================
{
	return m_pContext;
}


//						=============
bool					Cluster::Good()	const
//						=============
{
	return m_bState;
}


//						=============================
void					Cluster::BeginConditionalLoop
//						=============================
(
	bool				bCondition
)
{
	// Determine the loops to go based on the specified condition result.
	int nLoopsToGo = 0;
	if ( bCondition )
	{
		nLoopsToGo = 1;
	}

	// Begin a loop of conditional type.
	BeginLoop( CacheIterator::CONDITIONAL, nLoopsToGo );
}


//						===============================
void					Cluster::BeginUnconditionalLoop
//						===============================
(
	int					nIterations
)
{
	// Begin a loop of unconditional type, taking as loops to go the
	// specified number of iterations.
	BeginLoop( CacheIterator::UNCONDITIONAL, nIterations );
}


//						=============================
void					Cluster::SetUnconditionalLoop
//						=============================
(
	int					nIterations
)
{
	// Determine if there's an iterator on the stack.
	if ( !m_sCacheIterators.empty() )
	{
		// Determine if the current one is of unconditional type.
		if ( m_sCacheIterators.top().GetType() == CacheIterator::UNCONDITIONAL )
		{
			// Set the number of loops to go as specified.
			m_sCacheIterators.top().SetLoopsToGo( nIterations );
		}
	}
}


//						===========================
bool					Cluster::EndConditionalLoop()
//						===========================
{
	// End the current loop; the returned bool states whether the loop must
	// be repeated (at least once.)
	return EndLoop();
}


//						=============================
bool					Cluster::EndUnconditionalLoop()
//						=============================
{
	// End the current loop; the returned bool states whether the loop must
	// be repeated (at least once.)
	return EndLoop();
}


//						=========================
void					Cluster::BeginIfStatement()
//						=========================
{
	// Add an IF control flow element to the stack.
	m_siControlFlow.push( IF );
}


//						=======================
bool					Cluster::EndIfStatement()
//						=======================
{
	bool bResult = false;

	// Determine if the current control flow element is an IF.
	if ( m_siControlFlow.top() == IF )
	{
		// Remove element from the control flow stack.
		m_siControlFlow.pop();
	}

	return bResult;
}


//						=======================
Cluster::CONTROLFLOW	Cluster::GetControlFlow() const
//						=======================
{
	CONTROLFLOW nResult = UNDEFINED;

	// Determine if there is a control flow element placed on the stack.
	if ( !m_siControlFlow.empty() )
	{
		// Take the current element.
		nResult = m_siControlFlow.top();
	}

	return nResult;
}


//						==============================
int						Cluster::GetCurrentLoopCounter() const
//						==============================
{
	int nCounter = -1;

	// Determine if the cluster is currently processing a loop.
	if ( !m_sCacheIterators.empty() )
	{
		// Get the current iterator's counter.
		nCounter = m_sCacheIterators.top().GetCounter();
	}

	return nCounter;
}


//						============================
int						Cluster::GetCurrentLoopTotal() const
//						============================
{
	int nTotal = -1;

	// Determine if the cluster is currently processing a loop.
	if ( !m_sCacheIterators.empty() )
	{
		// Get the current iterator's total number of loops.
		nTotal = m_sCacheIterators.top().GetTotalLoops();
	}

	return nTotal;
}


//						===================
void					Cluster::SetSection
//						===================
(
	const string&		strSection
)
{
	m_strSection = strSection;
}


//						===================
const string&			Cluster::GetSection() const
//						===================
{
	return m_strSection;
}


//						====================
void					Cluster::SetScenario
//						====================
(
	const string&		strScenario
)
{
	m_strScenario = strScenario;
}


//						====================
const string&			Cluster::GetScenario() const
//						====================
{
	return m_strScenario;
}


//						====================
void					Cluster::SetTestCase
//						====================
(
	const string&		strTestCase
)
{
	m_strTestCase = strTestCase;
}


//						====================
const string&			Cluster::GetTestCase() const
//						====================
{
	return m_strTestCase;
}


//						=========================
void					Cluster::SetTestCondition
//						=========================
(
	const string&		strTestCondition
)
{
	m_strTestCondition = strTestCondition;
}


//						=========================
const string&			Cluster::GetTestCondition() const
//						=========================
{
	return m_strTestCondition;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=============
bool					Cluster::Read()
//						=============
{
	bool	bReadResult = false;	// states the result of Read
	string	strLine;				// string to copy file line to

	// get test line from IOInterface
	if (m_pIOInterface->Read(strLine))
	{
		// check if there are any redundant escape characters specified
		if (!m_strRedundantEscapeChars.empty())
		{
			ConvertRECharactersInLine(strLine);
		}

		// update (physical) line and line number number
		m_strPhysLine = strLine;
		m_nPhysLineNbr++;

		bReadResult = true;
	}

	return bReadResult;
}


//						===========================
bool					Cluster::GetCurrentTestLine
//						===========================
(
	string&				strTestLine
)
{
	bool bResult = false;

	// Determine if the test line buffer is filled.
	if ( !m_strTestLineBuffer.empty() )
	{
		// Move the contents of test line buffer to the current test line,
		// empty the buffer, and return true.
		strTestLine = m_strTestLineBuffer;
		m_strTestLineBuffer.erase();
		return true;
	}

	// Update line number.
	m_nLineNumber = m_nPhysLineNbr + 1;

	bool bMustStartWithCont	= false;
	bool bCommentInBetween	= false;
	vector<string> vstrContinuedComment;
	vector<string> vstrTempArgs;
	vector<string> vstrCommentBuffer = LineToArguments( m_strCommentBuffer );

	// Read lines from the cluster file as long as no complete cluster line
	// has been found.
	bool bLineComplete = false;
	while ( !bLineComplete )
	{
		// Read the next line from the cluster file, and check if it is not
		// the end of the file.
		if ( Read() )
		{
			// State initially that the read line is a valid part of a test
			// line (split or not.)
			bool bValidLinePart = true;

			// Split up the read line into arguments.
			vector<string> vstrArgs = LineToArguments( m_strPhysLine );

			// Check if this read line is expected to have a continue token
			// in its first argument.
			if ( bMustStartWithCont )
			{
				// Determine if the trimmed first argument is a continue token.
				if ( trim( vstrArgs[0] ) == m_strContToken )
				{
					// Remove the first argument.
					vstrArgs.erase( vstrArgs.begin() );

					// Determine if comment has been found in-between a split
					// test line.
					if ( bCommentInBetween )
					{
						// Add the comment arguments to the comment
						// buffer vector.
						vector<string>::size_type nArg;
						for ( nArg = 0; nArg < vstrContinuedComment.size(); nArg++ )
						{
							vstrCommentBuffer.push_back( vstrContinuedComment[nArg] );
						}
					}
				}
				else
				{
					// State that this current line is not a (part of the
					// split) test line.
					bValidLinePart = false;

					// Since it not (part of) a test line, determine if this
					// line is a comment line; if so, the comment arguments are
					// placed in the vector vstrContinuedComment.
					if ( CheckForComment( vstrArgs, vstrContinuedComment ) )
					{
						// State that comment was found in-between a split line.
						bCommentInBetween = true;
					}
				}
			}
			
			// Determine if the current line from the cluster file is a test
			// line, or part of a test line.
			if ( bValidLinePart )
			{
				// State that initially the line does not end with a
				// continue token.
				vector<string>::size_type nContArg = 0;

				// Determine if the current line is not a comment line.
				if ( !CheckForComment( LineToArguments( m_strPhysLine ) ) )
				{
					// Go passed all arguments (from back to front), except
					// the first argument, to determine if one is a continue
					// token.
					vector<string>::size_type nArg;
					for ( nArg = vstrArgs.size() - 1; (nContArg == 0) && (nArg > 0); nArg-- )
					{
						// Determine if the current argument, trimmed, is the
						// continue token.
						if ( trim( vstrArgs[nArg] ) == m_strContToken )
						{
							nContArg = nArg;
						}
					}
				}

				// Determine if a continue token has been found in an argument
				// other than the first one.
				if ( nContArg > 0 )
				{
					// State that the following read line is expected to start
					// with a continue token.
					bMustStartWithCont = true;

					// Remove the continue token and all subsequent arguments
					// from the vector of current line arguments.
					vstrArgs.erase( vstrArgs.begin() + nContArg, vstrArgs.end() );

					// Add the arguments to the vector of temporary arguments.
					vector<string>::size_type nArg;
					for ( nArg = 0; nArg < vstrArgs.size(); nArg++ )
					{
						vstrTempArgs.push_back( vstrArgs[nArg] );
					}
				
					// Make the size of the comment buffer match the temporary
					// arguments of the test line.
					// Fill up the comment buffer with empty strings if it has
					// less arguments than the temporary argument vector.
					while ( vstrTempArgs.size() > vstrCommentBuffer.size() )
					{
						vstrCommentBuffer.push_back( "" );
					}
					// Should the comment buffer contain more arguments than
					//the temporary argument vector, remove these.
					while ( vstrTempArgs.size() < vstrCommentBuffer.size() )
					{
						vstrCommentBuffer.pop_back();
					}
				}
				else
				{
					// No continue token is found at the end of the line;
					// the end of a test line or comment line has been found.
					bLineComplete = true;
					bResult		  = true;

					// Add the arguments to the vector of temporary arguments.
					vector<string>::size_type nArg;
					for ( nArg = 0; nArg < vstrArgs.size(); nArg++ )
					{
						vstrTempArgs.push_back( vstrArgs[nArg] );
					}
				}

			}
		}
		else
		{
			// The end of the cluster file has been found.
			bLineComplete	= true;
			bResult			= false;
		}
	}

	// Determine if a test line was found
	if ( bResult )
	{
		// Determine if comment was placed in-between a split test line.
		if ( bCommentInBetween )
		{
			// Place the temporary test line in the test line buffer, and give
			// as referenced test line the continued comment line placed in the
			// comment buffer.
			m_strTestLineBuffer = ArgumentsToLine( vstrTempArgs );
			strTestLine         = ArgumentsToLine( vstrCommentBuffer );
		}
		else
		{
			// Give as referenced parameter, the contents of the test line,
			// the line pasted together from the temporary arguments.
			strTestLine = ArgumentsToLine( vstrTempArgs );

			// Determine if the found cluster line is a comment line.
			if ( CheckForComment( vstrTempArgs ) )
			{
				// Update the comment buffer.
				m_strCommentBuffer = ArgumentsToLine( vstrTempArgs );
			}
		}
	}

	return bResult;
}


//						========================
bool					Cluster::CheckForComment
//						========================
(
	const vector<string>&	vstrArgs,
	vector<string>&			vstrComment
)
{
	bool bResult = false;

	// Paste the arguments together to a line.
	string strLine = ArgumentsToLine( vstrArgs );

	// Check if the line is not empty.
	if ( !strLine.empty() )
	{
		// Check if the action type of the line is EMPTY, which means the
		// line is a comment line.
		if ( m_pInterpreter->GetActionType(strLine) == ActionWordList::EMPTY )
		{
			bResult = true;

			// Set the comment arguments to be those of the original line,
			// but minus the first argument.
			vstrComment = vstrArgs;
			vstrComment.erase( vstrComment.begin() );
		}
	}
	
	return bResult;
}


//						========================
bool					Cluster::CheckForComment
//						========================
(
	const vector<string>&	vstrArgs
)
{
	vector<string> vstrDummy;

	return CheckForComment( vstrArgs, vstrDummy );
}


//						==================================
bool					Cluster::ConvertRECharactersInLine
//						==================================
(
	string&				strLineToConvert
)
{
	bool bResult = false;

	// Make a copy of the line to convert.
	string strLine = strLineToConvert;

	// Determine if there is anything to convert by determining if the line is
	// not empty and there are redundant escape characters specified.
	if ( !strLine.empty() && !m_strRedundantEscapeChars.empty() )
	{
		// Split up the line into arguments.
		vector<string> vstrArguments = LineToArguments( strLine );

		// Go passed all arguments.
		int nArg;
		for ( nArg = 0; nArg < vstrArguments.size(); nArg++ )
		{
			// Convert the redundant escape characters in the present argument.
			if ( ConvertRECharactersInArgument( vstrArguments[nArg] ) )
			{
				bResult = true;
			}
		}

		// Concatenate the converted arguments back to a line.
		strLine = ArgumentsToLine( vstrArguments );
	}

	// Change the referenced parameter.
	strLineToConvert = strLine;

	return bResult;
}


//						======================================
bool					Cluster::ConvertRECharactersInArgument
//						======================================
(
	string&				strArgument
)
{
	bool bResult = false;

	// Make a copy of the argument to convert.
	string strArg = strArgument;

	// Determine if the argument is not empty.
	if ( !strArg.empty() )
	{
		// Determine if the first character of the argument is one of the
		// redundant escape characters; first determine if there are at least
		// three characters.
		if ( strArg.length() >= 3 )
		{
			if ( m_strRedundantEscapeChars.find( strArg.substr( 0, 1 ) ) != string::npos )
			{
				// Determine if the argument's last character is the same (redundant
				// escape) character as the first one.
				if ( strArg.substr( strArg.length() - 1, 1 ) == strArg.substr( 0, 1 ) )
				{
					// Remove the first and last character from the argument string.
					strArg = strArg.substr( 1, strArg.length() - 2 );
				}
			}
		}

		// Remove the other redundant escape characters.
		string::size_type nStart = 0;
		string::size_type nPos;

		// Go passed all redundant escape chars in the argument.
		nPos = strArg.find_first_of( m_strRedundantEscapeChars, nStart );
		while ( nPos != string::npos )
		{
			// Get the found redundant escape character.
			string strREC = strArg.substr( nPos, 1 );

			// Determine if the following character is the same redundant
			// escape character.
			if ( strArg.substr( nPos + 1, 1 ) == strREC )
			{
				// Replace these two characters by a single one.
				strArg.replace( nPos, 2, strREC );

				// Update the starting position.
				nStart = nPos + 1;
			}
			else
			{
				// Only a single redundant escape character at this position;
				// remove it from the argument.
				strArg.erase( nPos, 1 );
			}

			// Determine the position of the next redundant escape character.
			nPos = strArg.find_first_of( m_strRedundantEscapeChars, nStart );
		}
	}

	// Determine if redundant escape characters have been converted.
	if ( strArg != strArgument )
	{
		// Change the referenced argument.
		strArgument = strArg;
		bResult = true;
	}

	return bResult;
}


//						========================
vector<string>			Cluster::LineToArguments
//						========================
(
	const string&		strLine
)
{
	return StrToVector( strLine, m_strDelimiter );
}


//						========================
string					Cluster::ArgumentsToLine
//						========================
(
	const vector<string>&	vstrArguments
)
{
	return VectorToStr( vstrArguments, m_strDelimiter );
}


//						==================
void					Cluster::BeginLoop
//						==================
(
	int					nType,
	int					nLoopsToGo
)
{
	// Determine if the cache is empty.
	if ( m_pCache->Empty() )
	{
		// Set the cache in recording state.
		m_pCache->StartRecording();

		// Place the current test line in the cache.
		m_pCache->Add( m_nLineNumber, m_strTestLine );

		// Add an iterator to the stack, of the specified type, with the
		// specified number of loops to go, starting on position 0.
		AddIterator( nType, 0, nLoopsToGo );
	}
	else
	{
		// The cache is not empty; determine if the current iterator is open.
		if ( m_sCacheIterators.top().IsOpen() )
		{
			// Get the current position in the cache from the current iterator.
			int nPos = m_sCacheIterators.top().GetPosition();

			// Add an iterator to the stack, of the specified type, with the
			// specified number of loops to go, starting on the found position.
			AddIterator( nType, nPos, nLoopsToGo );
		}
		else
		{
			// The iterator is closed, which means we're dealing with an
			// iteration through the cache; determine if the current position
			// is not the iterator's start position, to determine a new loop
			// is started.
			if ( m_sCacheIterators.top().GetPosition() > m_sCacheIterators.top().GetBegin() )
			{
				// Get the iterator's current position.
				int nPos = m_sCacheIterators.top().GetPosition();

				// Add an iterator to the stack, of the specified type, with the
				// specified number of loops to go, starting on the found position.
				AddIterator( nType, nPos, nLoopsToGo );
			}
			else
			{
				// The loop beginning is that of the current iterator;
				// determine if the iterator is of conditional type.
				if ( nType == CacheIterator::CONDITIONAL )
				{
					// Reset the loops to go as specified by the condition.
					m_sCacheIterators.top().SetLoopsToGo( nLoopsToGo );
				}
			}
		}
	}
}


//						================
bool					Cluster::EndLoop()
//						================
{
	bool bResult = false;
	int  nLoops  = -1;

	// Check if there's a current iterator.
	if ( !m_sCacheIterators.empty() )
	{
		// Determine if the current iterator is open.
		if ( m_sCacheIterators.top().IsOpen() )
		{
			// Close the current iterator.
			m_sCacheIterators.top().Close();
			m_nClosedIterators++;

			// Determine if the current iterator is the only one going through
			// the cache; if so, this means the end of the cache is reached,
			// and it can be set out of recording mode.
			if ( m_sCacheIterators.size() == 1 )
			{
				m_pCache->StopRecording();
			}
		}

		// Determine if the current iterator is of unconditional type.
		if ( m_sCacheIterators.top().GetType() == CacheIterator::UNCONDITIONAL )
		{
			// Decrement the number of loops to go, and keep the new number
			// loops to go.
			nLoops = m_sCacheIterators.top().DecrementLoopsToGo();
		}
		// Otherwise, determine if the current iterator is of conditional type.
		else if ( m_sCacheIterators.top().GetType() == CacheIterator::CONDITIONAL )
		{
			// Get the number of loops to go for the current iterator.
			nLoops = m_sCacheIterators.top().GetLoopsToGo();
		}

		// Check if the number of loops to go is greater than 0.
		if ( nLoops > 0 )
		{
			// Set the current position of the current iterator to (before)
			// its beginning.
			m_sCacheIterators.top().SetToBeginning();
			bResult = true;
		}
		else
		{
			// The loop is completely finished; remove it.
			RemoveIterator();

			// Since every iterator has been closed before it is removed,
			// decrease the number of closed iterators.
			m_nClosedIterators--;
		}
	}

	return bResult;
}


//						====================
void					Cluster::AddIterator
//						====================
(
	int					nType,
	int					nPos,
	int					nLoopsToGo
)
{
	// Add an iterator to the stack, of the specified type, with the
	// specified number of loops to go, starting on the found position.
	m_sCacheIterators.push( CacheIterator( m_pCache, nType, nPos, nLoopsToGo ) );

	// Add a control flow element to the stack, of specified type.
	switch ( nType )
	{
		case CacheIterator::UNCONDITIONAL:
		{
			m_siControlFlow.push( REPEAT );
			break;
		}

		case CacheIterator::CONDITIONAL:
		{
			m_siControlFlow.push( WHILE );
			break;
		}

		default:
		{
			// Internal error.
			break;
		}
	}
}


//						=======================
void					Cluster::RemoveIterator()
//						=======================
{
	// Get the current iterator's end position.
	int nEnd = m_sCacheIterators.top().GetEnd();

	// Remove the current iterator from the iterator stack, and the current
	// control flow element from the control flow stack.
	m_sCacheIterators.pop();
 	m_siControlFlow.pop();

	// Determine if there is still an iterator on the stack.
	if ( !m_sCacheIterators.empty() )
	{
		// Set the position of the current iterator to the end
		// of the last one.
		m_sCacheIterators.top().SetPosition( nEnd );
	}
	else
	{
		// There are no more iterators; clear the cache, and stop recording.
		m_pCache->Clear();
		m_pCache->StopRecording();
	}
}


//						=========================
bool					Cluster::GetLineFromCache
//						=========================
(
	string&				strLine,
	int&				nLineNumber
)
{
	bool bResult = false;

	// Determine if there are any closed iterators.
	if ( m_nClosedIterators > 0 )
	{
		// Move the current iterator to the next position.
		m_sCacheIterators.top().Next();

		// Get the new line contents and number from the cache, and fill
		// the reference parameters with this data.
		strLine     = m_sCacheIterators.top().GetLine();
		nLineNumber = m_sCacheIterators.top().GetLineNumber();
		bResult     = true;
	}

	return bResult;
}
