/*****************************************************************************
 * $Workfile: ActionWord.h $
 * $Revision: 1 $
 * $Modtime: 4/20/00 3:43p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ACTIONWORD_H
#define ACTIONWORD_H


#include <string>

using namespace std;


// Define a type for function pointers
typedef void (*tFunction)(void);


///////////////////////////////////////////////////////////////////////////////
// Class ActionWord

class ActionWord
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of ActionWord
	///////////////////////////////////////////////////////////////////////////////
	ActionWord();

	ActionWord(const string& strName, const string& strFunctionName, tFunction pFunction);
	
	///////////////////////////////////////////////////////////////////////////////
	// Destructor of ActionWord
	///////////////////////////////////////////////////////////////////////////////
	~ActionWord();


// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetName
	// Description:		This function returns the name of the action word
	//
	// Parameters:		None
	//
	// Returns:			String				Name of the action word
	///////////////////////////////////////////////////////////////////////////////
	string	GetName() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetFunctionName
	// Description:		This function returns the name of the action word function
	//
	// Parameters:		None
	//
	// Returns:			String				Name of the action word function
	///////////////////////////////////////////////////////////////////////////////
	string	GetFunctionName() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		Execute
	// Description:		This function executes the function registered with this
	//					action word
	//
	// Parameters:		None
	//
	// Returns:			true				Action word executed
	//					false				Action word not executed
	///////////////////////////////////////////////////////////////////////////////
	bool Execute() const;

// Member variables
private:
	string						m_strName;				// Name of action word
	string						m_strFunctionName;		// Name of action word function
	tFunction					m_pFunction;			// Pointer to action word function
};

///////////////////////////////////////////////////////////////////////////////

#endif  // !ACTIONWORD_H
