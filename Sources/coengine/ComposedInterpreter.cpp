/*****************************************************************************
 * $Workfile: ComposedInterpreter.cpp $
 * $Revision: 25 $
 * $Modtime: 8/13/01 3:02p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include "ComposedInterpreter.h"	// Class definition

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#include "ActionWordList.h"			// ActionWordList definition
#include "ActionWordPart.h"			// ActionWordPart definition
#include "EngineSetting.h"			// EngineSetting definition
#include "Interpreter.h"			// Baseclass definition
#include "MasterSlavePart.h"		// MasterSlavePart definition
#include "ParameterPart.h"			// ParameterPart definition
#include "Parser.h"
#include "StrUtil.h"				// Needed for Trim functionality and
									// vector-string conversions

// Defines.
#define DELIMITER	"\t"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Init constructor
ComposedInterpreter::ComposedInterpreter
(	
	ActionWord*		pActionWord,
	SlaveList*		pSlaveList
)
{
	// Initialise the action type to undefined
	m_nActionType = ActionWordList::UNDEFINED;

	// Initialise associations
	SetTheComposedInterpreter(this);
	SetTheActionWord(pActionWord);
	SetTheSlaveList(pSlaveList);

	// Construct the other interpreterparts
	SetTheMasterSlavePart(new MasterSlavePart());
	SetTheParameterPart(new ParameterPart());
	SetTheActionWordPart(new ActionWordPart());
}


// Destructor
ComposedInterpreter::~ComposedInterpreter()
{
	delete GetTheParameterPart();
	delete GetTheActionWordPart();
	delete GetTheMasterSlavePart();
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===============================
void					ComposedInterpreter::Initialise
//						===============================
(
	EngineSetting*		pSetting	// pointer to EngineSetting object
)

{
	// Initialise interpreter mode
	if ((pSetting->Get("SYSTEM", "InterpreterMode")) == "Fixed")
	{
		// Initialise the default interpreter mode
		SetInterpreterMode(FIXED);
	}
	else if ((pSetting->Get("SYSTEM", "InterpreterMode")) == "Free")
	{
		// Initialise the default interpreter mode
		SetInterpreterMode(FREE);
	} 
	else 
	{
		// Error, init on default
		SetInterpreterMode(FIXED);
	}

	// Initialise masterslavemode
	if ((pSetting->Get("MASTERSLAVE", "Mode")) == "Standalone")
	{
		// Initialise masterslave mode
		SetMasterSlaveMode(STANDALONE);
	}
	else if ((pSetting->Get("MASTERSLAVE", "Mode")) == "Master")
	{
		// Initialise masterslave mode
		SetMasterSlaveMode(MASTERSLAVE);
	}
	else
	{
		// Initialise the default masterslave mode
		SetMasterSlaveMode(STANDALONE);
	}

	// Initialise the parameterpart
	GetTheParameterPart()->Initialise(pSetting);
}


//						==============================
bool					ComposedInterpreter::Interpret 
//						==============================
(
	const string&		strLine
)
{
	// Interpret the specified line; set the boolean parameter to false to
	// specify that all arguments (including the parameters) must be parsed.
	return InterpretLine( strLine, false );
}


//						==============================================
bool					ComposedInterpreter::InterpretExceptParameters
//						==============================================
(
	const string&		strLine
)
{
	// Interpret the specified line, but do not parse the parameters.
	return InterpretLine( strLine, true );
}


//						==================================
int						ComposedInterpreter::GetActionType()
//						==================================
{
	return m_nActionType;
}


//						==================================
int						ComposedInterpreter::GetActionType
//						==================================
(
	const string&		strTestLine
)				
{
	int nTemporaryActionType;
	vector<string> vArgument;
	string::size_type nTabPosition = 0;
	string::size_type nStartPosition = 0;

	// Store current actionwordtype
	int nActionType = m_nActionType;

	// Parse the testline and store elements in a string vector;	
    do 
	{	
		// Find tab
		nTabPosition = strTestLine.find( "\t", nStartPosition );

		// No tab found, end positions
		if ( nTabPosition == string::npos )
		{
			nTabPosition = strTestLine.length();
		}

		vArgument.push_back(strTestLine.substr(nStartPosition,(nTabPosition-nStartPosition)));

		// Skip the tab
		nStartPosition = nTabPosition + 1;
	} 
	while ( nTabPosition != strTestLine.length() );

	// Use the first element
	int nElement = 0;

	// If master/slave mode is enabled and there are enough arguments
	if ((GetMasterSlaveMode() == MASTERSLAVE) && (vArgument.size() >= 2))
	{
		// Use second element
		nElement = 1;
	}

	GetTheActionWordPart()->Interpret( vArgument[nElement] );

	// Fetch the interpreted actionwordtype
	nTemporaryActionType = m_nActionType;

	// Restore old actionwordtype
	m_nActionType = nActionType;

	// Return interpreted actionwordtype
	return nTemporaryActionType;
}


//						==================================
void					ComposedInterpreter::SetActionType
//						==================================
(
	int					nActionType
)
{
	m_nActionType = nActionType;
}


//						==========================================
const string&			ComposedInterpreter::GetActionWordFunction()
//						==========================================
{
	return m_strActionWordFunction;
}


//						==========================================
void					ComposedInterpreter::SetActionWordFunction
//						==========================================
(
	const string&		strActionWordFunction
)
{
	m_strActionWordFunction = strActionWordFunction;
}


//						=================================
const string&			ComposedInterpreter::GetSlaveName()
//						=================================
{
	return m_strSlaveName;
}


//						=================================
void					ComposedInterpreter::SetSlaveName
//						=================================
(
	const string&		strSlaveName
)
{
	m_strSlaveName = strSlaveName;
}


//						=================================
void					ComposedInterpreter::AddParameter
//						=================================
(
	const string&		strParameter
)
{
	m_vstrParameters.push_back(strParameter);
}


//						================================
void					ComposedInterpreter::AddKeepName
//						================================
(
	const string&		strKeepName
)
{
	m_vstrKeepName.push_back(strKeepName);
}


//						=================================
void					ComposedInterpreter::AddKeepIndex
//						=================================
(
	int					nKeepIndex
)
{
	m_vnKeepIndex.push_back(nKeepIndex);
}


//						=================================
bool					ComposedInterpreter::InKeepVector
//						=================================
(
	int					nIndex,
	string&				strKeepName
)
{
	bool bResult = false;	// result of InKeepVector

	int cKeepElements = m_vnKeepIndex.size();
	int nVectorIndex;

	// go through KeepIndex vector until the end or the specified index is found
	for (int i = 0; (!bResult) && (i < cKeepElements); i++)
	{
		// check if specified index is in KeepIndex vector
		if (nIndex == m_vnKeepIndex[i])
		{
			bResult = true;
			nVectorIndex = i;
		}
	}
	
	// fill keep name if index is found
	if (bResult)
	{
		strKeepName = m_vstrKeepName[nVectorIndex];
	}

	return bResult;
}


//						================================
void					ComposedInterpreter::AddSnapName
//						================================
(
	const string&		strSnapName
)
{
	m_vstrSnapName.push_back(strSnapName);
}


//						=================================
void					ComposedInterpreter::AddSnapIndex
//						=================================
(
	int					nIndex
)
{
	m_vnSnapIndex.push_back(nIndex);
}


//						=================================
bool					ComposedInterpreter::InSnapVector
//						=================================
(
	int					nIndex,
	string&				strSnapName
)
{
	bool bResult = false;	// result of InKeepVector

	int cSnapElements = m_vnSnapIndex.size();
	int nVectorIndex;

	// go through SnapIndex vector until the end or the specified index is found
	for (int i = 0; (!bResult) && (i < cSnapElements); i++)
	{
		// check if specified index is in SnapIndex vector
		if (nIndex == m_vnSnapIndex[i])
		{
			bResult = true;
			nVectorIndex = i;
		}
	}
	
	// fill snap name if index is found
	if (bResult)
	{
		strSnapName = m_vstrSnapName[nVectorIndex];
	}

	return bResult;
}


//						==========================================
void					ComposedInterpreter::SetActionWordValidity
//						==========================================
(
	bool				bValidity
)
{
	m_bActionWordValidity = bValidity;
}


//						==========================================
bool					ComposedInterpreter::GetActionWordValidity()
//						==========================================
{
	return m_bActionWordValidity;
}


//						=========================================
void					ComposedInterpreter::SetSlaveNameValidity
//						=========================================
(
	bool				bValidity
)
{
	m_bSlaveNameValidity = bValidity;
}


//						=========================================
bool					ComposedInterpreter::GetSlaveNameValidity()
//						=========================================
{
	return m_bSlaveNameValidity;
}


//						==========================================
void					ComposedInterpreter::SetParametersValidity
//						==========================================
(
	bool				bValidity
)
{
	m_bParametersValidity = bValidity;
}


//						==========================================
bool					ComposedInterpreter::GetParametersValidity()
//						==========================================
{
	return m_bParametersValidity;
}


//						==================================
const vector<string>&	ComposedInterpreter::GetParameters()
//						==================================
{
	return m_vstrParameters;
}


//						===================================
const vector<string>&	ComposedInterpreter::GetErrorVector()
//						===================================
{
	return m_vstrErrorVector;
}


//						===================================
void					ComposedInterpreter::SetErrorVector
//						===================================
(
	const vector<string>&	vstrErrorVector
)
{
	m_vstrErrorVector = vstrErrorVector;
}


//						===============================
void					ComposedInterpreter::SetContext
//						===============================
(
	Context*			pContext
)
{
	// Delegate to context to parameterpart
	GetTheParameterPart()->SetContext(pContext); 
}


///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==============================
vector<string>			ComposedInterpreter::SplitLine
//						==============================
(
	const string&		strLine,
	const string&		strDelimiter
)
{
	// Split the specified line on the delimiter into arguments which
	// are placed in a vector.
	vector<string> vstrArguments = StrToVector( strLine, strDelimiter );

	// To remove trailing empty arguments, go through the vector from end to
	// beginning as long as the vector is not empty and the last argument is
	// empty.
	while ( !vstrArguments.empty() && vstrArguments.back().empty() )
	{
		// Remove the empty argument.
		vstrArguments.pop_back();
	}

	return vstrArguments;
}


//						==================================
bool					ComposedInterpreter::InterpretLine
//						==================================
(
	const string&		strLine,
	bool				bNoParameters
)
{
	bool bResult = false;

	// Split up the cluster into its arguments, and place these in a vector.
	vector<string> vstrArguments = SplitLine( strLine, DELIMITER );

	// Determine if there are no arguments at all.
	if ( vstrArguments.empty() )
	{
		// The cluster line is an empty line; set the interpreter members
		// accordingly.
		SetActionWordValidity( true );
		SetParametersValidity( true );
		SetSlaveNameValidity( true );
		SetSlaveName( "" );
		SetActionType( ActionWordList::EMPTY );
		bResult = true;
	}
	else
	{
		// The arguments are going to be parsed; first initialise the
		// interpreter members.
		SetActionWordValidity( false );
		SetSlaveNameValidity( false );
		SetParametersValidity( true );
		ClearParameters();
		ClearErrorVector();
		ClearKeepVector();
		ClearSnapVector();
		SetActionType( ActionWordList::UNDEFINED );

		// Determine the Master/Slave mode.
		switch ( GetMasterSlaveMode() )
		{
			case STANDALONE:
			{
				// Interpret the arguments as those of a standalone line,
				// and store the result.
				bResult = InterpretStandaloneArguments( vstrArguments, bNoParameters );
				break;
			}

			case MASTERSLAVE:
			{
				// Interpret the arguments as those of a Master line,
				// and store the result.
				bResult = InterpretMasterArguments( vstrArguments, bNoParameters );
				break;
			}

			default:
			{
				// Invalid Master/Slave mode; error.
				break;
			}
		}
	}

	return bResult;
}


//						=================================================
bool					ComposedInterpreter::InterpretStandaloneArguments
//						=================================================
(
	const vector<string>&	vstrArguments,
	bool					bNoParameters
)
{
	bool bResult = false;

	// Take as action word the first argument, and trim its leading and
	// trailing spaces.
	string strActionWord = trim( vstrArguments[0] );

	// Interpret the action word, and set the action word validity accordingly.
	SetActionWordValidity( GetTheActionWordPart()->Interpret( strActionWord ) );

	// Insert the action word as the first argument.
	AddParameter( strActionWord );

	// Determine if the arguments are to be interpreted.
	if ( !bNoParameters )
	{
		// Go through all arguments as parameters, starting at element 1
		// (since at 0 the action word is placed.)
		int nElement;
		for ( nElement = 1; nElement < vstrArguments.size(); ++nElement )
		{
			// Interpret the parameter, and determine if it didn't fail.
			if ( !InterpretParameter( vstrArguments[nElement], nElement ) )
			{
				// If only parameter interpretation fails, the validity
				// of the parameters becomes false.
				SetParametersValidity( false );
			}
		}
	}

	// Set the result to be the result of the action word interpretation and
	// the parameter interpretation.
	bResult = GetActionWordValidity() && GetParametersValidity();

	return bResult;
}


//						=============================================
bool					ComposedInterpreter::InterpretMasterArguments
//						=============================================
(
	const vector<string>&	vstrArguments,
	bool					bNoParameters
)
{
	bool bResult = false;

	// Take as slave name the first argument.
	string strSlaveName = vstrArguments[0];

	// Interpret the slave name, and set the slave name validity accordingly.
	SetSlaveNameValidity( GetTheMasterSlavePart()->Interpret( strSlaveName ) );
	
	// Store the slave name, and insert it as the first argument.
	SetSlaveName( strSlaveName );
	AddParameter( strSlaveName );

	// Check if there are arguments other than the slave name.
	if ( vstrArguments.size() > 1)
	{
		// Determine if the cluster line is meant to be processed by this
		// Engine; i.e., determine is the slave name is an empty string.
		if ( strSlaveName.empty() )
		{
			// Take as action word the second argument, and trim its leading
			// and trailing spaces.
			string strActionWord = trim( vstrArguments[1] );

			// Interpret the action word, and set the action word validity
			// accordingly.
			SetActionWordValidity( GetTheActionWordPart()->Interpret( strActionWord ) );

			// Insert the action word as the second argument.
			AddParameter( strActionWord );

			// Determine if the arguments are to be interpreted.
			if ( !bNoParameters )
			{
				// Go through all arguments as parameters, starting at element
				// 2 (since at 0 the slave name, and at 1 the action word is
				// placed.)
				int nElement;
				for ( nElement = 2; nElement < vstrArguments.size(); ++nElement )
				{
					// Interpret the parameter, and determine if it didn't fail.
					if ( !InterpretParameter( vstrArguments[nElement], nElement ) )
					{
						// If only parameter interpretation fails, the validity
						// of the parameters becomes false.
						SetParametersValidity( false );
					}
				}
			}
		}
		else
		{
			// The cluster line is intended for a slave; set the action word-
			// and parameter validity to true.
			SetActionWordValidity( true );
			SetParametersValidity( true );
		}
	}
	else
	{
		// The arguments are those of an empty line (either for the Master or
		// for a Slave); set the interpreter members accordingly.
		SetActionType( ActionWordList::EMPTY );
		SetActionWordValidity( true );
	}

	// Set the result to be the result of the slave name interpretation, the
	// action word interpretation and the parameter interpretation.
	bResult = GetSlaveNameValidity() && GetActionWordValidity() && GetParametersValidity();

	return bResult;
}


//						=======================================
bool					ComposedInterpreter::InterpretParameter
//						=======================================
(
	const string&		strParameter,
	int					nIndex
)
{
	bool bResult = true;		// result of InterpreterParameter

	int nArgument = nIndex + 1;	// argument index

	if (!GetTheParameterPart()->Interpret(strParameter))
	{
		// Fetch the error vector
		vector<string> vError = GetTheParameterPart()->GetErrorVector();

		// Add argument information to the errors
		for (int cnErrors = 0; cnErrors < vError.size(); cnErrors++)
		{
			// Build error string
			ostringstream strError;
			strError<<"["<<nArgument<<"] "<<strParameter<<" : "<<vError.at(cnErrors);

			// Add to error vector
			m_vstrErrorVector.push_back(strError.str());
		}

		// Flag for error
		bResult = false;
	} 

	// Perform specific parametertype action
	switch (GetTheParameterPart()->GetParameterType())
	{
		case ParameterPart::KEEP:
		{
			// Add the keep index to the keep vector
			GetTheComposedInterpreter()->AddKeepIndex(nArgument);
			break;
		}

		case ParameterPart::SNAP:
		{
			// add the snap index
			GetTheComposedInterpreter()->AddSnapIndex(nArgument);
			break;
		}
	}

	return bResult;
}


//						====================================
void					ComposedInterpreter::ClearParameters()
//						====================================
{
	m_vstrParameters.clear();
}


//						=====================================
void					ComposedInterpreter::ClearErrorVector()
//						=====================================
{
	m_vstrErrorVector.clear();

	// Clear also the errors stored in the parser.
	GetTheParameterPart()->GetTheParser()->ClearErrors();
}


//						====================================
void					ComposedInterpreter::ClearKeepVector()
//						====================================
{
	m_vstrKeepName.clear();
	m_vnKeepIndex.clear();
}


//						====================================
void					ComposedInterpreter::ClearSnapVector()
//						====================================
{
	m_vstrSnapName.clear();
	m_vnSnapIndex.clear();
}
