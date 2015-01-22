/*****************************************************************************
 * $Workfile: TemplateList.h $
 * $Revision: 1 $
 * $Modtime: 11-11-99 18:19 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TEMPLATELIST_H
#define TEMPLATELIST_H


#include <string>
#include <vector>

using namespace std;


class TemplateList
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of TemplateList
	///////////////////////////////////////////////////////////////////////////////
	TemplateList();

	///////////////////////////////////////////////////////////////////////////////
	// destructor of TemplateList
	///////////////////////////////////////////////////////////////////////////////
	~TemplateList();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFileName()
	// description	: This function returns the name of the template file.
	//
	// parameters	: <none>
	//
	// returns		: string containing the name of the template file
	///////////////////////////////////////////////////////////////////////////////
	const string& GetFileName();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfParameters()
	// description	: This function returns the number of template parameters.
	//
	// parameters	: <none>
	//
	// returns		: number of template parameters
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameter()
	// description	: This function returns a template parameter specified by nIndex.
	//					The first parameter has index 0. If the index is invalid,
	//					an empty string will be returned.
	//
	// parameters	: nIndex	position of parameter in vector
	//
	// returns		: string containing the template parameter
	///////////////////////////////////////////////////////////////////////////////
	string GetParameter(int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetFileName()
	// description	: This function sets the name of the template file.
	//
	// parameters	: strFileName		name of the template file
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void SetFileName(const string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddParameter()
	// description	: This function adds a parameter to the vector.
	//
	// parameters	: strParameter		template parameter to add to vector
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void AddParameter(const string& strParameter);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearParameters()
	// description	: This function deletes all parameters and clears the vector.
	//
	// parameters	: <none>
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void ClearParameters();

private:
	// member variables
	string			m_strFileName;		// name of the template file
	vector<string>	m_vstrParameters;	// vector of template parameters
};

#endif // !TEMPLATELIST_H
