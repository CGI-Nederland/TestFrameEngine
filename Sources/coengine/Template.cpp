/*****************************************************************************
 * $Workfile: Template.cpp $
 * $Revision: 2 $
 * $Modtime: 12-11-99 14:01 $
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
#include <map>

using namespace std;

#include "Template.h"
#include "TemplateList.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						==================
						Template::Template()
//						==================
{}


// Destructor
//						===================
						Template::~Template()
//						===================
{
	// delete all TemplateList objects and clear the map
	Clear();
}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//							=============
void						Template::Add
//							=============
(
	const string&			strTemplateName,		// name of the template
	const vector<string>&	vstrTemplateParameters,	// vector containing the parameter names
	const string&			strTemplateFile			// name of the template file
)
{
	TemplateList* pTemplateList;	// pointer to a template list object

	// check if template already exists
	if (m_TemplateMap.find(strTemplateName) != m_TemplateMap.end())
	{
		// get pointer to it and clear the parameters
		pTemplateList = m_TemplateMap[strTemplateName];
		pTemplateList->ClearParameters();
	}
	else
	{
		// create new one and add it to map
		pTemplateList					= new TemplateList();
		m_TemplateMap[strTemplateName]	= pTemplateList;
	}

	// add template file name
	pTemplateList->SetFileName(strTemplateFile);

	// add parameters
	int cParameters = static_cast<int>(vstrTemplateParameters.size());	// number of parameters
	for (int cCounter = 0; cCounter < cParameters; cCounter++)
	{
		pTemplateList->AddParameter(vstrTemplateParameters[cCounter]);
	}
}


//							==============
bool						Template::Find
//							==============
(
	const string&			strTemplateName,		// name of the template
	vector<string>&			vstrTemplateParameters,	// vector to be filled with the parameter names
	string&					strTemplateFile			// string to be filled with name of the template file
)
{
	bool					bFound = false;			// states whether or not the template is found

	// check if template is in map
	if (m_TemplateMap.find(strTemplateName) != m_TemplateMap.end())
	{
		bFound = true;

		// fill template file
		strTemplateFile = m_TemplateMap[strTemplateName]->GetFileName();

		// fill template parameters
		vstrTemplateParameters.clear();
		int cParameters = m_TemplateMap[strTemplateName]->GetNumberOfParameters();
		for (int cCounter = 0; cCounter < cParameters; cCounter++)
		{
			vstrTemplateParameters.push_back(m_TemplateMap[strTemplateName]->GetParameter(cCounter));
		}
	}

	return bFound;
}


//							===============
void						Template::Clear()
//							===============
{
	// delete all TemplateList objects
	for (TemplateMap::iterator	p = m_TemplateMap.begin(); p != m_TemplateMap.end(); ++p)
	{
		delete p->second;
		p->second=0;
	}

	// clear the map
	m_TemplateMap.clear();
}
