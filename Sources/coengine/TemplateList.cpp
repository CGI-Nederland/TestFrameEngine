/*****************************************************************************
 * $Workfile: TemplateList.cpp $
 * $Revision: 1 $
 * $Modtime: 11-11-99 18:19 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)
// When decorated name length is exceeded, the warning is disabled.
#pragma warning(disable:4503)


#include <string>
#include <vector>

using namespace std;

#include "TemplateList.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						==========================
						TemplateList::TemplateList()
//						==========================
{}


// Destructor
//						===========================
						TemplateList::~TemplateList()
//						===========================
{}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=========================
const string&			TemplateList::GetFileName()
//						=========================
{
	return m_strFileName;
}


//						===================================
int						TemplateList::GetNumberOfParameters()
//						===================================
{
	return static_cast<int>(m_vstrParameters.size());
}


//						==========================
string					TemplateList::GetParameter
//						==========================
(
	int					nIndex		// position of parameter in vector
)
{
	string	strParameter;							// name of template parameter
	int		nParameters = GetNumberOfParameters();	// number of parameters

	// check if nIndex is valid
	if (nIndex >= 0 && nIndex < nParameters)
	{
		// get specified parameter from vector
		strParameter = m_vstrParameters[nIndex];
	}

	return strParameter;
}


//						=========================
void					TemplateList::SetFileName
//						=========================
(
	const string&		strFileName		// name of template file
)
{
	m_strFileName = strFileName;
}


//						==========================
void					TemplateList::AddParameter
//						==========================
(
	const string&		strParameter	// parameter to add to vector
)
{
	m_vstrParameters.push_back(strParameter);
}


//						=============================
void					TemplateList::ClearParameters()
//						=============================
{
	m_vstrParameters.clear();
}
