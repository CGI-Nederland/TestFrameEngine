/*****************************************************************************
 * $Workfile: NavigationLibrary.h $
 * $Revision: 1 $
 * $Modtime: 4/21/00 9:00a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NAVIGATIONLIBRARY_H
#define NAVIGATIONLIBRARY_H


#include <string>
#include <vector>

using namespace std;

#include "ActionWord.h"			// ActionWord and typedef for function pointers

// The strings used as names etc. can only be 1024 characters long
#define MAX_STRING_LENGTH 1024

///////////////////////////////////////////////////////////////////////////////
// Class NavigationLibrary

class NavigationLibrary
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////
	// Constructor of NavigationLibrary
	///////////////////////////////////////////////////////////////////////////
	NavigationLibrary();

	NavigationLibrary(const string& strVersion, int nBuildNumber, const string& strName, const string& strInfo,	const string& strAuthor);

	///////////////////////////////////////////////////////////////////////////
	// Destructor of NavigationLibrary
	///////////////////////////////////////////////////////////////////////////
	~NavigationLibrary();


// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetVersion
	// Description:		This function returns the version of this navigation library
	//
	// Parameters:		None
	//
	// Returns:			string				Version of this navigation library
	///////////////////////////////////////////////////////////////////////////////
	string GetVersion() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetBuildNumber
	// Description:		This function returns the build number of this navigation
	//					library
	//
	// Parameters:		None
	//
	// Returns:			int					Integer build number of this 
	//										navigation library
	///////////////////////////////////////////////////////////////////////////////
	int GetBuildNumber() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetName
	// Description:		This function returns the name of this navigation library
	//
	// Parameters:		None
	//
	// Returns:			string				Name of this navigation library
	///////////////////////////////////////////////////////////////////////////////
	string GetName() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetInfo
	// Description:		This function returns info about this navigation library
	//
	// Parameters:		None
	//
	// Returns:			string				Info about this navigation library
	///////////////////////////////////////////////////////////////////////////////
	string GetInfo() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		GetAuthor
	// Description:		This function returns the author of this navigation library
	//
	// Parameters:		None
	//
	// Returns:			string				Author of this navigation library
	///////////////////////////////////////////////////////////////////////////////
	string GetAuthor() const;

	///////////////////////////////////////////////////////////////////////////////
	// Function:		SetVersion
	// Description:		This function sets the version of this navigation library
	//
	// Parameters:		strVersion
	//
	// Returns:			1					Version of the navigation library set
	//					0					Version of the navigation library not set
	///////////////////////////////////////////////////////////////////////////////
	int SetVersion(const string& strVersion);

	///////////////////////////////////////////////////////////////////////////////
	// Function:		SetBuildNumber
	// Description:		This function sets the build number of this navigation library
	//
	// Parameters:		nBuildNumber
	//
	// Returns:			void
	///////////////////////////////////////////////////////////////////////////////
	void SetBuildNumber(int nBuildNumber);
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:		SetName
	// Description:		This function sets the name of this navigation library
	//
	// Parameters:		strName
	//
	// Returns:			1					Name of the navigation library set
	//					0					Name of the navigation library not set
	///////////////////////////////////////////////////////////////////////////////
	int SetName(const string& strName);

	///////////////////////////////////////////////////////////////////////////
	// Function:		SetInfo
	// Description:		This function sets the info of this navigation library
	//
	// Parameters:		strInfo
	//
	// Returns:			1					Info of the navigation library set
	//					0					Info of the navigation library not set
	///////////////////////////////////////////////////////////////////////////
	int SetInfo(const string& strInfo);

	///////////////////////////////////////////////////////////////////////////
	// Function:		SetAuthor
	// Description:		This function sets the author of this navigation library
	//
	// Parameters:		strAuthor
	//
	// Returns:			1					Author of the navigation library set
	//					0					Author of the navigation library not set
	///////////////////////////////////////////////////////////////////////////
	int SetAuthor(const string& strAuthor);

	///////////////////////////////////////////////////////////////////////////
	// Function:		GetNumberOfActionWords
	// Description:		This function gets the number of action words from this
	//					navigation library
	//
	// Parameters:		None
	//
	// Returns:			int					Number of action words
	///////////////////////////////////////////////////////////////////////////
	int GetNumberOfActionWords() const;

	///////////////////////////////////////////////////////////////////////////
	// Function:		AddActionWord
	// Description:		This function adds an action word to this navigation
	//					library
	//
	// Parameters:		strName				Name of the action word
	//					strFunctionName		Name of the action word function
	//					pFunction			Pointer to action word function
	//
	// Returns:			void
	///////////////////////////////////////////////////////////////////////////
	void AddActionWord(const string& strName, const string& strFunctionName, tFunction pFunction);
	
	///////////////////////////////////////////////////////////////////////////
	// Function:		ExecuteActionWord
	// Description:		This function executes an action word associated to this
	//					navigation library
	//
	// Parameters:		strActionWord		Name of the action word
	//
	// Returns:			1					Action word executed
	//					0					Action word not executed
	///////////////////////////////////////////////////////////////////////////
	int ExecuteActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////
	// Function:		RegisterActionWords
	// Description:		This function registers all the action words associated
	//					to this navigation library in the TestFrame engine
	//
	// Parameters:		None
	//
	// Returns:			1					Action words registered
	//					0					Action words not registered
	///////////////////////////////////////////////////////////////////////////
	int RegisterActionWords();

	///////////////////////////////////////////////////////////////////////////
	// Function:		UnregisterActionWords
	// Description:		This function unregisters all the action words associated
	//					to this navigation library in the TestFrame engine
	//
	// Parameters:		None
	//
	// Returns:			1					Action words unregistered
	//					0					Action words not unregistered
	///////////////////////////////////////////////////////////////////////////
	int UnregisterActionWords();

// Member variables
private:
	string						m_strVersion;			// Version of library
	int							m_nBuildNumber;			// Build number of library
	string						m_strName;				// Name of library
	string						m_strInfo;				// Info string for library
	string						m_strAuthor;			// Author of library
	vector<ActionWord>			m_vActionWords;			// Vector with action words
};

///////////////////////////////////////////////////////////////////////////////

#endif  // !NAVIGATIONLIBRARY_H
