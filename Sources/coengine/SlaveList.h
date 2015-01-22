/*****************************************************************************
 * $Workfile: SlaveList.h $
 * $Revision: 3 $
 * $Modtime: 6/15/01 6:10p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef SLAVELIST_H
#define SLAVELIST_H

// Includes
#include <map>
#include <string>

// Forward declarations
class Log;
class Slave;

////////////////////////////////////////////////////////////////////////////////
// class SlaveList

class SlaveList
{
	// Construction and destruction
public:
	SlaveList();					// Constructor

private:
	SlaveList(const SlaveList& src);	// Copy contructor

	// Other constructors
public:
	~SlaveList();					// Destructor

	// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	Add()
	//
	// description	:	Add a slave to the list
	//				  	
	// parameters	:	strName			slave name
	//					pSlave			pointer slave object
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void Add( const string& strName, Slave* pSlave );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FindByName()
	//
	// description	:	Finds a slave by name
	//				  	
	// parameters	:	strName			slave name
	//
	// returns		:	pointer to slave object; null if not found
	///////////////////////////////////////////////////////////////////////////////
	Slave* FindByName( const string& strName );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	FindByID()
	//
	// description	:	Finds a slave by name
	//				  	
	// parameters	:	nID				slave ID
	//
	// returns		:	pointer to slave object; null if not found
	///////////////////////////////////////////////////////////////////////////////
	Slave* FindByID( const int nID );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Clear()
	//
	// description	:	Clear the slave list
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void Clear();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Remove()
	//
	// description	:	Removes a slave from the list
	//				  	
	// parameters	:	strName			slave name
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void Remove( const string& strName );

	// Implementation
private:

	// Class constants
public:

	// Member variables
private:
	map<string, Slave*>		m_mpSlave;		// Slave map
	Log*					m_pLog;			// Log object
};

////////////////////////////////////////////////////////////////////////////////

#endif // !SLAVELIST_H