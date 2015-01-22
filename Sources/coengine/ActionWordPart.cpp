/*****************************************************************************
 * $Workfile: ActionWordPart.cpp $
 * $Revision: 5 $
 * $Modtime: 4/12/01 4:56p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include <iostream>

using namespace std;

#include "ActionWord.h"				// Needed for list of valid action words
#include "ActionWordList.h"			// Needed for list of action word types
#include "ActionWordPart.h"			// Class definition
#include "ComposedInterpreter.h"	// Composition class
#include "StrUtil.h"				// Needed for trim functionality

#define BASECLASS Interpreter

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
ActionWordPart::ActionWordPart()
{
}

// Destructor
ActionWordPart::~ActionWordPart()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=========================
bool					ActionWordPart::Interpret
//						=========================
(
	const string&		strActionWordArgument		// argument to check for action word
)
{
	bool bResult = false;			// result of Interpret

	// trim specified argument to determine action word
	string strActionWord = trim(strActionWordArgument);

	// check if the specified action word is empty
	if (strActionWord.empty())
	{
		// no action word, so argument belongs to an empty line or a comment line
		GetTheComposedInterpreter()->SetActionType(ActionWordList::EMPTY);
		bResult = true;
	}
	else
	{
		int	   nActionType;		// action word type
		string strFunction;		// action word function

		// check if action word is valid
		if (GetTheActionWord()->Find(strActionWord, nActionType, strFunction))
		{
			// store the attributes in the composed interpreter
			GetTheComposedInterpreter()->SetActionWordFunction(strFunction);
			GetTheComposedInterpreter()->SetActionType(nActionType);
			bResult = true;
		}
		else
		{
			GetTheComposedInterpreter()->SetActionType(ActionWordList::UNDEFINED);
		}
	}

	return bResult;
}
