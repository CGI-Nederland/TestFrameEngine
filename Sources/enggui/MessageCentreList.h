/*****************************************************************************
 * $Workfile: MessageCentreList.h $
 * $Revision: 3 $
 * $Modtime: 21-10-99 16:49 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef MESSAGECENTRELIST_H
#define MESSAGECENTRELIST_H

#undef BASECLASS
#define BASECLASS BabelFish

#include <string>

using namespace std;

#include "BabelFish.h"			// Definition of superclass

////////////////////////////////////////////////////////////////////////////////
// Class MessageCentreList

class MessageCentreList : public BASECLASS
{
public:
	///////////////////////////////////////////////////////////////////////////////
	// Constructor of MessageCentreList
	//
	// Parameters:		nLanguage		code for selected language
	///////////////////////////////////////////////////////////////////////////////
	MessageCentreList();
	
	///////////////////////////////////////////////////////////////////////////////
	// Destructor of MessageCentreList
	///////////////////////////////////////////////////////////////////////////////	
	~MessageCentreList();

	// String IDs
	enum 
		{	
			ID_MESS_CENTRE = 0,
			ID_TXTLBL_NUMBER_ACTIONWORDS,
			ID_TXT_NUMBER_ACTIONWORDS,
			ID_BTN_PAUSE,
			ID_BTN_RESUME,
			ID_BTN_STOP,
			ID_BTN_DETAIL_MORE,
			ID_BTN_DETAIL_LESS,
			ID_GRP_CHECKS,
			ID_TXTLBL_CHECKS_PASSED,
			ID_TXTLBL_CHECKS_FAILED,
			ID_TXTLBL_SUCCESS_RATE,
			ID_GRP_ERRORS,
			ID_TXTLBL_LAST_ERROR,
			ID_TXTLBL_ERRORS_FOUND,
			ID_TXTLBL_MESSAGE,
			ID_TXT_MESSAGE_RUNNING,
			ID_TXT_MESSAGE_PAUSED,
			ID_TXTLBL_CURRENT_ACTIONWORD,
			ID_MESSAGEBOX,
			
			NTEXTS
		};

	// Member variables
private:
	static const char* m_pszTexts[NLANGS * NTEXTS]; // Texts and translations
};

////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !MESSAGECENTRELIST
