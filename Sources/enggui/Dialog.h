/*****************************************************************************
 *$Workfile: Dialog.h $
 *$Revision: 1 $
 *$Modtime: 12-10-99 0:11 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef DIALOG_H
#define DIALOG_H

#include <string>

using namespace std;

// Forward declaration
class CDialog;

////////////////////////////////////////////////////////////////////////////////
// class Dialog

class Dialog 
{
// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessage (Abstract)
	// Description: This function pops up a message box to show a message
	//
	// Parameters:	strMessage		Message string
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void ShowMessage(const string& strMessage) = 0;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !DIALOG_H
 