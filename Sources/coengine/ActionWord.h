/*****************************************************************************
 * $Workfile: ActionWord.h $
 * $Revision: 4 $
 * $Modtime: 8/16/01 5:08p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ACTIONWORD_H
#define ACTIONWORD_H


#include <map>
#include <string>
#include <vector>

using namespace std;

#include "ActionWordList.h"


class ActionWord
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ActionWord
	///////////////////////////////////////////////////////////////////////////////
	ActionWord();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of ActionWord
	///////////////////////////////////////////////////////////////////////////////
	~ActionWord();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Add()
	// description	: This function adds an action word with its associated function,
	//					type and description to the vector m_vActionWordList.
	//
	// parameters	: strActionWord		action word name
	//				  nType				action word type
	//				  strFunction		action word function
	//				  strDescription	action word description
	//
	// returns		: TRUE		Action word added successfully
	//				  FALSE		Action word already added to list
	///////////////////////////////////////////////////////////////////////////////
	bool Add(const string& strActionWord, int nType, const string& strFunction, const string& strDescription);	

	///////////////////////////////////////////////////////////////////////////////
	// function		: Delete()
	// description	: This function deletes an action word from the vector
	//					m_vActionWordList.
	//
	// parameters	: strActionWord		action word name
	//
	// returns		: TRUE		deletion successfull
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Delete(const string& strActionWord);
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Find()
	// description	: This function searches for an action word in the list and if
	//					found, gives as reference the corresponding type, action 
	//					word function and description.
	//
	// parameters	: strActionWord			action word name
	//				  OUT nType				to be filled with action word type
	//				  OUT Function			to be filled with action word function
	//				  OUT strDescription	to be filled with action word description
	//
	// returns		: TRUE		action word found in list
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strActionWord, int& nType, string& strFunction, string& strDescription);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Find()
	// description	: This function searches for an action word in the list and if
	//					found, gives as reference the corresponding type and action
	//					word function.
	//
	// parameters	: strActionWord			action word name
	//				  OUT nType				to be filled with action word type
	//				  OUT strFunction		to be filled with action word function
	//
	// returns		: TRUE		action word found in list
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strActionWord, int& nType, string& strFunction);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Find()
	// description	: This function searches for an action word in the list and if
	//					found, gives as reference the corresponding type.
	//
	// parameters	: strActionWord			action word name
	//				  OUT nType				to be filled with action word type
	//
	// returns		: TRUE		action word found in list
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strActionWord, int& nType);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Find()
	// description	: This function searches for an action word in the list and if
	//					found, returns true, otherwise false.
	//
	// parameters	: strActionWord					action word name
	//
	// returns		: TRUE		action word found in list
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Update()
	// description	: This function updates for an action word its corresponding
	//					function, type and description. If an argument is left empty
	//					it will not be updated and remain as before.
	//
	// parameters	: strActionWord		action word name
	//				  nType				action word type
	//				  strFunction		action word function
	//				  strDescription	action word description
	//
	// returns		: TRUE		action word updated
	//				  FALSE		action word not found in list
	///////////////////////////////////////////////////////////////////////////////
	bool Update(const string& strActionWord, int nType, const string& strFunction, const string& strDescription);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateSynonym()
	//
	// description	: Creates a synonym for an existing ActionWord.
	//				  The operation fails if the ActionWord does not exist
	//				  or when the synonym is already being used.
	//				  	
	// parameters	: strActionWord		action word name
	//				  strSynonym		synonym for action word name
	//
	// returns		: TRUE		the operation succeeded
	//				  FALSE		the operation failed
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool CreateSynonym(const string& strActionWord, const string& strSynonym);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Delete()
	// description	: This function deletes an action word from the vector
	//					m_vActionWordList.
	//
	// parameters	: nType		action word type
	//
	// returns		: int		the number of action words deleted
	//
	///////////////////////////////////////////////////////////////////////////////
	int DeleteAllOfType(int nType);

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllOfType()
	//
	// description	:	This function return all action words of a specified type,
	//					together with their action word functions.
	//
	// parameters	:	nType	action word type
	//
	// returns		:	vector containing action word/function pairs
	///////////////////////////////////////////////////////////////////////////////
	vector<pair<string, string> > GetAllOfType( int nType );

private:
	// member variables
	typedef map<string, ActionWordList>	ActionWordMap;
	ActionWordMap						m_ActionWordMap;	// map containing templates
};


#endif  // !ACTIONWORD_H