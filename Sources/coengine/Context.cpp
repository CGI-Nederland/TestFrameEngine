/*****************************************************************************
 * $Workfile: Context.cpp $
 * $Revision: 4 $
 * $Modtime: 1/30/01 11:46a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable:4786)

#include "Context.h"	// Class definition

#include <string>
#include <map> 
#include <sstream> 

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
Context::Context()
{
	// Empty.
}

// Destructor
Context::~Context()
{
	// Empty.
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===============
Context::tValues*		Context::Lookup
//						===============
(
	const string&		strName		// variable name
)
{
	tValues* tvResult;	// result of Lookup

	// Look up the variable name in the map m_mVar.
	tVarMap::iterator Iterator = m_mVar.find( strName );

	// Check if the name was found.
	if ( Iterator != m_mVar.end() )
	{
		// Give as result the address of the corresponding value/type pair.
		tvResult = &(Iterator->second);
	}
	else
	{
		// Variable not found; return null pointer.
		tvResult = 0;
	}

	return tvResult;
}


//						===============
void					Context::Assign
//						===============
(
	const string&		strName,	// variable name
	const string&		strValue,	// variable value
	int					nType		// variable type
)
{
	// Create a pair of the variable value and variable type; then, add
	// an element to the map m_mVar with this pair as its value and the
	// variable name as its key.
	m_mVar[strName] = make_pair( strValue, nType );
}

//						===============
Context::tVarMap*	Context::getMappingNameValue
//						===============
(
		// variable type
)
{
	/*map <string,string> values;
	tVarMap::iterator mapIterator = m_mVar.begin();
	while ( mapIterator != m_mVar.end() )
	{
		values[mapIterator->first] = mapIterator->second.first;
		mapIterator++;
	}*/
	return &m_mVar;	
}
