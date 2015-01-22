/*****************************************************************************
 * $Workfile: ActionWordList.cpp $
 * $Revision: 1 $
 * $Modtime: 8-10-99 16:14 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


#include <string>

using namespace std;

#include "ActionWordList.h"		// Class definition


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						==============================
						ActionWordList::ActionWordList()
//						==============================
{
	m_strActionWord.erase();
	m_nType = ActionWordList::UNDEFINED;
	m_strActionWordFunction.erase();
	m_strDescription.erase();
}


// Other constructors
//						==============================
						ActionWordList::ActionWordList
//						==============================
(
	const string&		strActionWord,			// action word name
	int					nType,					// action word type
	const string&		strActionWordFunction,	// action word function
	const string&		strDescription			// action word description
)
{
	m_strActionWord			= strActionWord;
	m_nType					= nType;
	m_strActionWordFunction	= strActionWordFunction;
	m_strDescription		= strDescription;
}


// Destructor
//						===============================
						ActionWordList::~ActionWordList()
//						===============================
{}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============================
const string&			ActionWordList::GetActionWord() const
//						=============================
{
	return m_strActionWord;
}


//						=====================================
const string&			ActionWordList::GetActionWordFunction() const
//						=====================================
{
	return m_strActionWordFunction;
}


//						==============================
const string&			ActionWordList::GetDescription() const
//						==============================
{
	return m_strDescription;
}


//						=======================
int						ActionWordList::GetType() const
//						=======================
{
	return m_nType;
}


//						=============================
void					ActionWordList::SetActionWord
//						=============================
(
	const string&		strActionWord	// name of the action word
)
{
	m_strActionWord = strActionWord;
}


//						=====================================
void					ActionWordList::SetActionWordFunction
//						=====================================
(
	const string&		strActionWordFunction	// action word function
)
{
	m_strActionWordFunction = strActionWordFunction;
}


//						==============================
void					ActionWordList::SetDescription
//						==============================
(
	const string&		strDescription	// action word description
)
{
	m_strDescription = strDescription;
}


//						=======================
void					ActionWordList::SetType
//						=======================
(
	int					nType	// action word type
)
{
	m_nType = nType;
}
