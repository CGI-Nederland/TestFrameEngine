/*****************************************************************************
 * $Workfile: Template.h $
 * $Revision: 2 $
 * $Modtime: 12-11-99 13:59 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TEMPLATE_H
#define TEMPLATE_H


#include <string>
#include <vector>
#include <map>

using namespace std;

#include "TemplateList.h"

class Template
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of Cluster
	///////////////////////////////////////////////////////////////////////////////
	Template();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of Cluster
	///////////////////////////////////////////////////////////////////////////////
	~Template();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Add()
	// description	: This function adds a template with its corresponding parameters
	//					and filename to the map. Should the template already exist,
	//					its parameters and filename will be overwritten.
	//
	// parameters	: strTemplateName			name of the template
	//				  vstrTemplateParameters	vector containing the parameter names
	//				  strTemplateFile			name of the template file
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void Add(const string& strTemplateName, const vector<string>& vstrTemplateParameters,
				const string& strTemplateFile);
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Find()
	// description	: This function finds a template in the map. If the template is
	//					found, the function will fill vstrTemplateParameters with
	//					the parameter names corresponding to the template and 
	//					strTemplateFile with the corresponding filename.
	//
	// parameters	: strTemplateName				name of the template
	//				  OUT vstrTemplateParameters	vector to be filled with the 
	//													parameter names
	//				  OUT strTemplateFile			string to be filled with the 
	//													name of the template file
	//
	// returns		: TRUE		template found
	//				  FALSE		template not found
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const string& strTemplateName, vector<string>& vstrTemplateParameters,
				string& strTemplateFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Clear()
	// description	: This function clears the map with TemplateList object.
	//
	// parameters	: <none>
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void Clear();

private:
	// member variables
	typedef map<string, TemplateList*>	TemplateMap;
	TemplateMap							m_TemplateMap;	// map containing templates
};

#endif // !TEMPLATE_H
