/*****************************************************************************
 *$Workfile: LocalMessageCentre.h $
 *$Revision: 5 $
 *$Modtime: 21-12-99 14:13 $
 *$Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOCALEMESSAGECENTRE_H
#define LOCALEMESSAGECENTRE_H

#include <string>

using namespace std;

#include "MessageCentre.h"			// Class definition
#include "MessageCentreList.h"		// Text constants

// Forward declarations
class CDialogThread;
class CMessageCentre;

#undef BASECLASS
#define BASECLASS MessageCentre

///////////////////////////////////////////////////////////////////////////////
// class LocalMessageCentre

class LocalMessageCentre : public BASECLASS
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////
	// Constructor of LocalMessageCentre
	//
	// Parameters:	bDetail			Start in detailed state or not?
	//				strLanguage		Language of the texts
	//				bAlwaysOnTop	Should the dialog be always on top?
	//				bPause			Should the dialog start in paused state?
	///////////////////////////////////////////////////////////////////////////
	LocalMessageCentre(bool bDetail, string strLanguage, bool bAlwaysOnTop, bool bPause);
	
	///////////////////////////////////////////////////////////////////////////
	// Destructor of LocalMessageCentre
	///////////////////////////////////////////////////////////////////////////
	virtual	~LocalMessageCentre();

private:
	// It is not necessary to make copies of this dialogue
	LocalMessageCentre(const LocalMessageCentre& src);
	// It is not necessary to make copies of this dialogue
	const LocalMessageCentre& operator=(const LocalMessageCentre& rhs);

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetProgress
	// Description: This function sets the progress indicator to represent the 
	//				percentage of completed action words.
	//
	// Parameters:	nExecuted		Number of completed action words
	//				nTotal			Total number of action words to complete
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetProgress(int nExecuted, int nTotal);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetChecks
	// Description: This function sets the number of passed and failed checks
	//
	// Parameters:	nPassed		Number of passed checks
	//				nFailed		Number of failed checks
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void SetChecks(int nPassed, int nFailed);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetError
	// Description: This function sets the last error and number of errors
	//
	// Parameters:	strError		Last error message
	//				nErrors			Number of errors
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void SetError(const string& strError, int nErrors);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentCluster
	// Description: This function sets the name of the current cluster
	//
	// Parameters:	strCluster		Name of the current cluster
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void SetCurrentCluster(const string& strCluster);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetCurrentActionWord
	// Description: This function sets the current action word
	//
	// Parameters:	strActionWord	Current action word
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void SetCurrentActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	ShowMessage
	// Description: This function pops up a message box to show a message
	//
	// Parameters:	strMessage		Message string
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
    virtual void ShowMessage(const string& strMessage);


	///////////////////////////////////////////////////////////////////////////////
	// Function:	DoModeless
	// Description: This function starts a separate thread to show the dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void DoModeless();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Exit (Abstract)
	// Description: Exit the dialogue
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Exit();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnStop
	// Description: This function is called by the MFC dialogue when the user
	//				presses the stop button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnStop();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnPause
	// Description: This function is called by the MFC dialogue when the user
	//				presses the pause button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnPause();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Pause
	// Description: This function is called by the Engine when it has paused
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Pause();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Resume
	// Description: This function is called by the Engine when it has resumed again
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void Resume();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	OnDetail
	// Description: This function is called by the MFC dialogue when the user
	//				presses the More Detail or Less Detail button
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void OnDetail();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterStop
	// Description: Registers the callback pointer to the engine stop function.
	//
	// Parameters:	pStop
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterStop(void (*pStop)(void));
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterPause
	// Description: Registers the callback pointer to the engine pause function.
	//
	// Parameters:	pPause
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterPause(void (*pPause)(void));

	///////////////////////////////////////////////////////////////////////////////
	// Function:	RegisterResume
	// Description: Registers the callback pointer to the engine resume function.
	//
	// Parameters:	pResume
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	virtual void RegisterResume(void (*pResume)(void));

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetControlTexts
	// Description: This function fills all the dialogue controls with texts in the
	//				selected language
	//
	// Parameters:	<none>
	//
	// Returns:		<void>
	///////////////////////////////////////////////////////////////////////////////
	void SetControlTexts();

// Implementation
private:
	string GetText(int nID) const;
	HANDLE hThread;
	HANDLE h;

// Member variables
private:
	// Our MFC equivalent dialog
	CMessageCentre* m_pMfcDlg;

	// Our MFC thread
	CDialogThread* m_pMfcThread;

	// State: More Detail | Less Detail
	bool m_bDetail;

	// State: Paused | Not paused
	bool m_bPaused;

	// Texts
	MessageCentreList m_Texts;

	// Current cluster
	string m_strCluster;

	// Pointers to Stop, Pause and Resume functions
	void (*m_pStop)(void);
	void (*m_pPause)(void);
	void (*m_pResume)(void);
};

////////////////////////////////////////////////////////////////////////////////

#endif // !LOCALEMESSAGECENTRE_H
