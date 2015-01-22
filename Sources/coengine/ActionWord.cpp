/*****************************************************************************
 * $Workfile: ActionWord.cpp $
 * $Revision: 7 $
 * $Modtime: 8/16/01 5:08p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)


#include "ActionWord.h"
#include "ActionWordList.h"

#include <map>
#include <vector>
#include <string>

using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						======================
						ActionWord::ActionWord()
//						======================
{}


// Destructor
//						=======================
						ActionWord::~ActionWord()
//						=======================
{}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===============
bool					ActionWord::Add
//						===============
(
	const string&		strActionWord,	// action word name
	int					nType,			// action word type
	const string&		strFunction,	// action word function
	const string&		strDescription	// action word description
)
{
	bool bResult = false;	// result of Add

	// check if specified action word is not empty
	if (!strActionWord.empty())
	{
		// check if action word is not already added
		if (!Find(strActionWord))
		{
			m_ActionWordMap[strActionWord]	= ActionWordList(strActionWord, nType, strFunction, strDescription);
			bResult							= true;
		}
	}

	return bResult;
}


//						==================
bool					ActionWord::Delete
//						==================
(
	const string&		strActionWord	// action word name
)
{
	bool bDeleteResult = false;	// states whether or not the delete was performed succesfully

	if (Find(strActionWord))
	{
		m_ActionWordMap.erase(strActionWord);
		bDeleteResult = true;
	}

	return bDeleteResult;
}


//						================
bool					ActionWord::Find
//						================
(
	const string&		strActionWord,	// action word name
	int&				nType,			// OUT: action word type
	string&				strFunction,	// OUT: action word function
	string&				strDescription	// OUT: action word description
) 
{
	bool					bFound;		// states whether or not the action word is found
	ActionWordMap::iterator	Iterator;	// iterator for ActionWordMap

	// find the action word
	Iterator = m_ActionWordMap.find(strActionWord);

	// check if action word is not in map
	if (Iterator == m_ActionWordMap.end())
	{
		bFound = false;
	}
	else
	{
		// fill in parameters from ActionWordList
		nType			= Iterator->second.GetType();
		strFunction		= Iterator->second.GetActionWordFunction();
		strDescription	= Iterator->second.GetDescription();
		bFound			= true;
	}

	return bFound;
}


//						================
bool					ActionWord::Find
//						================
(
	const string&		strActionWord,	// action word name
	int&				nType,			// OUT: action word type
	string&				strFunction		// OUT: action word function
)
{
	bool					bFound;		// states whether or not the action word is found
	ActionWordMap::iterator	Iterator;	// iterator for ActionWordMap

	// find the action word
	Iterator = m_ActionWordMap.find(strActionWord);

	// check if action word is not in map
	if (Iterator == m_ActionWordMap.end())
	{
		bFound = false;
	}
	else
	{
		// fill in parameters from ActionWordList
		nType		= Iterator->second.GetType();
		strFunction	= Iterator->second.GetActionWordFunction();
		bFound		= true;
	}

	return bFound;
}


//						================
bool					ActionWord::Find
//						================
(
	const string&		strActionWord,	// action word name
	int&				nType			// OUT: action word type
)
{
	bool					bFound;		// states whether or not the action word is found
	ActionWordMap::iterator	Iterator;	// iterator for ActionWordMap

	// find the action word
	Iterator = m_ActionWordMap.find(strActionWord);

	// check if action word is not in map
	if (Iterator == m_ActionWordMap.end())
	{
		bFound = false;
	}
	else
	{
		// fill in nType from ActionWordList
		nType	= Iterator->second.GetType();
		bFound	= true;
	}

	return bFound;
}


//						================
bool					ActionWord::Find
//						================
(
	const string&		strActionWord			// action word name
)
{
	bool bFound;	// states whether or not the action word is found

	// check if action word is not in map
	if (m_ActionWordMap.find(strActionWord) == m_ActionWordMap.end())
	{
		bFound = false;
	}
	else
	{
		bFound = true;
	}

	return bFound;
}


//						==================
bool					ActionWord::Update
//						==================
(
	const string&		strActionWord,	// action word name
	int					nType,			// action word type
	const string&		strFunction,	// action word function
	const string&		strDescription	// action word description
)
{
	bool bUpdateResult = false;	// states whether or not the delete was performed succesfully

	if (Find(strActionWord))
	{
		m_ActionWordMap[strActionWord] = ActionWordList(strActionWord, nType, strFunction, strDescription);
		bUpdateResult = true;
	}

	return bUpdateResult;
}

//						=========================
bool					ActionWord::CreateSynonym
//						=========================
(
	const string&		strActionWord,	// action word name
	const string&		strSynonym		// synonym for action word name
)
{
	bool bResult = false;	// Contains the result of the operation

	// Check if synonym is not registered in list.
	if (!Find(strSynonym))
	{
		int nType;					// action word type
		string strFunction;			// action word function
		string strDescription;		// action word description
		
		// Check if actionword is registered in list.
		if (Find(strActionWord, nType, strFunction, strDescription))
		{
			// Add synonym to actionword list.
			Add(strSynonym, nType, strFunction, strDescription);
			bResult = true;
		}
	}

	return bResult;
}

//						===========================
int						ActionWord::DeleteAllOfType
//						===========================
(
	int					nType		// action word type to delete
)
{
	int nDeletedActionWords = 0;	// number of action words deleted

	// iterator for ActionWordMap	
	ActionWordMap::iterator	Iterator = m_ActionWordMap.begin();

	// loop through the entire map
	while (Iterator != m_ActionWordMap.end())
	{
		// check if stored type equals type specified in function call
		if (Iterator->second.GetType() == nType)
		{
			// determine iterator for action word after the one that is
			// about to be deleted, and store it
			ActionWordMap::iterator	NextIter = Iterator;
			NextIter++;

			// remove selected element
			m_ActionWordMap.erase(Iterator);

			// update the Iterator
			Iterator = NextIter;

			// update the number of deleted action words
			nDeletedActionWords++;
		}
		else
		{
			Iterator++;
		}
	}

	return nDeletedActionWords;
}


//								========================
vector<pair<string, string> >	ActionWord::GetAllOfType
//								========================
(
	int					nType
)
{
	vector<pair<string, string> > vprActionWords;

	// Iterator for ActionWordMap.
	ActionWordMap::iterator	Iterator = m_ActionWordMap.begin();

	// Go passed all elements in the map.
	for ( ;Iterator != m_ActionWordMap.end(); Iterator++ )
	{
		// Determine if the stored type equals the specified type.
		if ( Iterator->second.GetType() == nType )
		{
			// Get the action word name and function.
			string strActionWord = Iterator->first;
			string strFunction = Iterator->second.GetActionWordFunction();

			// Make a pair of the name and function, and store this in the
			// vector to return.
			vprActionWords.push_back( make_pair( strActionWord, strFunction ) );
		}
	}

	return vprActionWords;
}
