/*****************************************************************************
 * $Workfile: NavigationLibrary.cpp $
 * $Revision: 2 $
 * $Modtime: 9/20/00 2:03p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include "NavigationLibrary.h"		// Class definition
#include "Coengine.h"				// Engine exports

#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						====================================
						NavigationLibrary::NavigationLibrary()
//						====================================
{
	m_strVersion = 		string("");		// Version of library
	m_nBuildNumber = 	0;				// Build number of library
	m_strName = 		string("");		// Name of library
	m_strInfo = 		string("");		// Info string for library
	m_strAuthor = 		string("");		// Author of library
}

//						====================================
						NavigationLibrary::NavigationLibrary
//						====================================
(
	const string&		strVersion,
	int 				nBuildNumber,
	const string&		strName,
	const string&		strInfo,
	const string&		strAuthor
)
{
	m_strVersion = 		strVersion;		// Version of library
	m_nBuildNumber = 	nBuildNumber;	// Build number of library
	m_strName = 		strName;		// Name of library
	m_strInfo = 		strInfo;		// Info string for library
	m_strAuthor = 		strAuthor;		// Author of library
}

// Destructor
//						=====================================
						NavigationLibrary::~NavigationLibrary()
//						=====================================
{}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=============================
string					NavigationLibrary::GetVersion() const
//						=============================
{
		return m_strVersion;
}

//						=================================
int						NavigationLibrary::GetBuildNumber() const
//						=================================
{
		return m_nBuildNumber;
}

//						==========================
string					NavigationLibrary::GetName() const
//						==========================
{
		return m_strName;
}

//						==========================
string					NavigationLibrary::GetInfo() const
//						==========================
{
		return m_strInfo;
}

//						============================
string					NavigationLibrary::GetAuthor() const
//						============================
{
		return m_strAuthor;
}

//						==========================
int 					NavigationLibrary::SetName
//						==========================
(
	const string&		strName
)
{
	int nResult = 0;
	
	// Check if we do not exceed the maximum string length
	if (strName.length() <= MAX_STRING_LENGTH)
	{
		m_strName = strName;
		nResult = 1;
	}

	return nResult;
}

//						==========================
int						NavigationLibrary::SetInfo
//						==========================
(
	const string&		strInfo
)
{
	int nResult = 0;
	
	// Check if we do not exceed the maximum string length
	if (strInfo.length() <= MAX_STRING_LENGTH)
	{
		m_strInfo = strInfo;
		nResult = 1;
	}

	return nResult;
}

//						=============================
int						NavigationLibrary::SetVersion
//						=============================
(
	const string&		strVersion
)
{
	int nResult = 0;
	
	// Check if we do not exceed the maximum string length
	if (strVersion.length() <= MAX_STRING_LENGTH)
	{
		m_strVersion = strVersion;
		nResult = 1;
	}

	return nResult;
}

//						=================================
void					NavigationLibrary::SetBuildNumber
//						=================================
(
	int					nBuildNumber
)
{
	m_nBuildNumber = nBuildNumber;
}

//						============================
int						NavigationLibrary::SetAuthor
//						============================
(
	const string&		strAuthor
)
{
	int nResult = 0;
	
	// Check if we do not exceed the maximum string length
	if (strAuthor.length() <= MAX_STRING_LENGTH)
	{
		m_strAuthor = strAuthor;
		nResult = 1;
	}

	return nResult;
}

//						================================
void					NavigationLibrary::AddActionWord
//						================================
(
	const string&		strName,
	const string&		strFunctionName,
	tFunction			pFunction
)
{
	// Insert a new action word at the back of the vector
	m_vActionWords.push_back(ActionWord(strName, strFunctionName, pFunction));
}

//						=========================================
int 					NavigationLibrary::GetNumberOfActionWords() const
//						=========================================
{
	int nResult = 0;

	// Only calculate the size if the vector is not empty
	if (!m_vActionWords.empty())
	{ 
		nResult = static_cast<int>(m_vActionWords.size()); 
	}

	return nResult;
}

//						======================================
int						NavigationLibrary::RegisterActionWords()
//						======================================
{
	int nResult = 0;

	// Only proceed if we have action words
	if (!m_vActionWords.empty())
	{
		vector<ActionWord>::iterator Iterator = m_vActionWords.begin();

		string strName;
		string strFunctionName;
		
		// Loop through all action words
		while (Iterator != m_vActionWords.end())
		{
			// Register action word
			strName = Iterator->GetName();
			strFunctionName = Iterator->GetFunctionName();
			nResult = tfe_RegisterActionWord(strName.c_str(), strFunctionName.c_str());

			// Next action word
			Iterator++;
		}
	}

	return nResult;
}

//						========================================
int						NavigationLibrary::UnregisterActionWords()
//						========================================
{
	int nResult = 0;

	// Only proceed if we have action words
	if (!m_vActionWords.empty())
	{
		vector<ActionWord>::iterator Iterator = m_vActionWords.begin();

		string strName;
		
		// Loop through all action words
		while (Iterator != m_vActionWords.end())
		{
			// Unregister action word
			strName = Iterator->GetName();
			nResult = tfe_UnregisterActionWord(strName.c_str());
			
			// Next action word
			Iterator++;
		}
	}

	return nResult;
}

//						====================================
int						NavigationLibrary::ExecuteActionWord
//						====================================
(
	const string&		strActionWord
)
{
	int nResult = 0;

	// Only proceed if we have action words
	if (!m_vActionWords.empty())
	{
		vector<ActionWord>::iterator Iterator = m_vActionWords.begin();

		// Loop throug all action words
		while (Iterator != m_vActionWords.end())
		{
			if (Iterator->GetName() == strActionWord)
			{
				// We have found the actionword so execute
				if (Iterator->Execute())
				{ nResult = 1; }
				break;
			}

			// Next action word
			Iterator++;
		}
	}

	return nResult;
}

///////////////////////////////////////////////////////////////////////////////
