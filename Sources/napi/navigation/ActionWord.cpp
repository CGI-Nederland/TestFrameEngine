/*****************************************************************************
 * $Workfile: ActionWord.cpp $
 * $Revision: 1 $
 * $Modtime: 4/20/00 3:44p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "ActionWord.h"
#include <string>

using namespace std;



///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						======================
						ActionWord::ActionWord()
//						======================
{
	m_strName = 		string("");			// Name of action word
	m_strFunctionName = string("");			// Name of action word function
	m_pFunction =		0;					// Pointer to action word function
}

//						======================
						ActionWord::ActionWord
//						======================
(
	const string&		strName,			// Name of action word
	const string&		strFunctionName,	// Name of action word function
	tFunction			pFunction			// Pointer to action word function
)
{
	m_strName = 		strName;
	m_strFunctionName = strFunctionName;
	m_pFunction = 		pFunction;
}

//						=======================
						ActionWord::~ActionWord()
//						=======================
{}


//						===================
string					ActionWord::GetName() const
//						===================
{
	// Return the name of the action word
	return m_strName;
}

//						===========================
string					ActionWord::GetFunctionName() const
//						===========================
{
	// Return the name of the action word function
	return m_strFunctionName;
}

//						===================
bool					ActionWord::Execute() const
//						===================
{
	bool bResult = false;

	// Beware of null pointers
	if (m_pFunction != 0)
	{
		// Execute the associated action word
		m_pFunction();
		bResult = true;
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
