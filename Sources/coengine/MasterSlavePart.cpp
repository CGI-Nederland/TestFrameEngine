/*****************************************************************************
 *$Workfile: MasterSlavePart.cpp $
 *$Revision: 3 $
 *$Modtime: 10-12-99 16:58 $
 *$Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)
#include <iostream>

using namespace std;

#include "Interpreter.h"
#include "MasterSlavePart.h"
#include "SlaveList.h"

#define BASECLASS Interpreter


///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
MasterSlavePart::MasterSlavePart()
{
}

// Destructor
MasterSlavePart::~MasterSlavePart()
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//				==========================
bool			MasterSlavePart::Interpret 
//				==========================
(
	string& strSlaveName
) const
{
	bool bResult = false;

	// Check is slavename exists, empty slave name is also valid
	if ((GetTheSlaveList()->FindByName(strSlaveName) != NULL) || (strSlaveName.empty()))
	{
		bResult = true;
	}

	return bResult;
}
