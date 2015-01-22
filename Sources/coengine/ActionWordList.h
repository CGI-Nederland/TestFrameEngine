/*****************************************************************************
 * $Workfile: ActionWordList.h $
 * $Revision: 13 $
 * $Modtime: 5/01/01 4:33p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ACTIONWORDLIST_H
#define ACTIONWORDLIST_H


#include <string>

using namespace std;


class ActionWordList
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of ActionWordList
	///////////////////////////////////////////////////////////////////////////////
	ActionWordList();

	///////////////////////////////////////////////////////////////////////////////
	// constructor of ActionWordList
	//
	// parameters :	strActionWord			action word name
	//				nType					action word type
	//				strActionWordFunction	action word function
	//				strDescription			action word description
	///////////////////////////////////////////////////////////////////////////////
	ActionWordList(const string& strActionWord, int nType, const string& strActionWordFunction, const string& strDescription);
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of ActionWordList
	///////////////////////////////////////////////////////////////////////////////
	~ActionWordList();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWord()
	// description	: This function returns the name of the action word.
	//
	// parameters	: <none>
	//
	// returns		: string containing name of action word
	///////////////////////////////////////////////////////////////////////////////
	const string& GetActionWord() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordFunction()
	// description	: This function returns the action word function.
	//
	// parameters	: <none>
	//
	// returns		: string containing action word function
	///////////////////////////////////////////////////////////////////////////////
	const string& GetActionWordFunction() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetDescription()
	// description	: This function returns the action word description.
	//
	// parameters	: <none>
	//
	// returns		: string containing action word description
	///////////////////////////////////////////////////////////////////////////////
	const string& GetDescription() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetType()
	// description	: This function returns the action word type.
	//
	// parameters	: <none>
	//
	// returns		: integer containing action word type
	///////////////////////////////////////////////////////////////////////////////
	int GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetActionWord()
	// description	: This function sets the name of the action word.
	//
	// parameters	: strActionWord		name of the action word
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void SetActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetActionWordFunction()
	// description	: This function sets the action word function.
	//
	// parameters	: strActionWordFunction		action word function
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void SetActionWordFunction(const string& strActionWordFunction);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetDescription()
	// description	: This function sets the action word description.
	//
	// parameters	: strDescription	action word description
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void SetDescription(const string& strDescription);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetType()
	// description	: This function sets the action word type.
	//
	// parameters	: nType	action word type
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void SetType(int nType);

	// enumerations
	enum ACTIONTYPE	{
						EXTERN,				// extern defined action word
						EXTERN_HEADER,		// extern defined header word
						SUBCLUSTER,			// action word invoking a subcluster
						TEMPLATE,			// action word invoking a template
						DEFINE_TEMPLATE,	// action word starting a template definition
						END_TEMPLATE,		// action word ending a template definition
						TEMPLATE_PROTO,		// action word stating prototype of template at beginning of template file
						DECLARE_TEMPLATE,	// action word declaring a template
						CLUSTER_AUTHOR,		// header action word logging cluster author
						CLUSTER_DATE,		// header action word logging cluster date
						CLUSTER_NAME,		// header action word logging cluster name
						CLUSTER_VERSION,	// header action word logging cluster version
						SHEET,				// header action word logging sheet name
						DOCUMENT,			// header action word logging document name
						SECTION,			// action word stating a new section
						SCENARIO,			// action word stating a new scenario
						TEST_CASE,			// action word stating a new test case
						TEST_CONDITION,		// action word stating a new test condition
						EXPORT_TO_FILE,		// action word for exporting variables to the keep-file
						IMPORT_FROM_FILE,	// action word for importing variables from the keep-file
						CONNECT_SLAVE,		// master/slave action word to connect slave
						DISCONNECT_SLAVE,	// master/slave action word to disconnect slave
						EMPTY,				// no action word
						IF,
						END_IF,
						ELSE,
						ELSE_IF,
						REPEAT,
						END_REPEAT,
						WHILE,
						END_WHILE,
						SET,
						UNDEFINED
					};

private:
	// member variables
	string m_strActionWord;			// action word name
	int	   m_nType;					// action word type
	string m_strActionWordFunction;	// action word function
	string m_strDescription;		// action word description
};


#endif  // !ACTIONWORDLIST_H