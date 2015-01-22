/*****************************************************************************
 * $Workfile: Context.h $
 * $Revision: 4 $
 * $Modtime: 1/30/01 11:51a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef CONTEXT_H
#define CONTEXT_H

// Includes
#include <string>
#include <map>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class Context
class Context 
{
	// Type definitions

	////////////////////////////////////////////////////////////////////////////
	// Construction and destruction
public:
	Context();							// Constructor

private:
	Context( const Context& right );	// Copy contructor
	// Member variables
	typedef pair<string, int>		tValues;	// Typedef for value/type pair
	typedef map<string, tValues>	tVarMap;	// Typedef for map of name on 
												//   value and type

	tVarMap	m_mVar;		// Variable/value/type map

	// Other constructors
public:
	~Context();							// Destructor

	///////////////////////////////////////////////////////////////////////////////
	// Attributes and operations

	///////////////////////////////////////////////////////////////////////////////
	// function		: Lookup()
	//
	// description	: This function looks up a specified variable name in the
	//				  context. If it is found, a reference to its value/type pair
	//				  is returned; if it is not found, the null pointer is returned.
	//					
	// parameters	: strName		variable name
	//
	// returns		: pointer to the value/type pair; a null pointer means the
	//				  variable is not in the context.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	pair<string, int>* Lookup( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		: Assign()
	//
	// description	: This function adds a variable to the context. For this
	//				  variable its name, value and type must be specified. If a
	//				  variable with the same name already exists, its value and
	//				  type will be overwritten with the new ones.
	//
	// parameters	: strName		variable name
	//				  strValue		variable value
	//				  nType			variable type
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void Assign( const string& strName, const string& strValue, int nType );

	///////////////////////////////////////////////////////////////////////////////
	// function		: getMappingNameValue()
	//
	// description	: This function returns all stored variabels in the mapping as name value pairs.
	//					this is usefull when writing all the known variables to a the keep file
	//
	// parameters	: null
	//
	// returns		: pointer to map with name value <string,string> pairs
	///////////////////////////////////////////////////////////////////////////////
	Context::tVarMap* getMappingNameValue();

// Class constants
public:
	enum TYPE	{	INT,
					FLOAT,
					STRING,
					UNSPECIFIED
				};


};

#endif // !CONTEXT_H
