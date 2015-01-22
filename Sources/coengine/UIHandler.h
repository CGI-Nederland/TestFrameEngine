/*****************************************************************************
 * $Workfile: UIHandler.h $
 * $Revision: 5 $
 * $Modtime: 6/22/00 10:49a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef UIHANDLER_H
#define UIHANDLER_H

#include "TcpHandler.h"

// Forward declarations
class TcpIpServer;

class UIHandler
{
	// Construction and destruction	
public:
	explicit UIHandler(TcpIpServer* pTcpIpServer);

	~UIHandler();							// Destructor
private:
	UIHandler();							// Default constructor
	UIHandler(const UIHandler& right);		// Copy constructor

	// Other constructors
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowActionWord
	//
	// description	: Show actionword on the UI
	//					
	// parameters	: string&					actionword
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowMessage
	//
	// description	: Show message on the UI
	//					
	// parameters	: string&					message
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowMessage(const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowProgress
	//
	// description	: Show progress on the UI
	//					
	// parameters	: int						Number of excuted
	//				  int						Number of total
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowProgress(const int	nExecuted, const int nTotal);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowErrors
	//
	// description	: Show error on the UI
	//					
	// parameters	: string&					Error message
	//				  int						Number of errors
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowErrors(const string& strErrorMessage, const int nErrorCount );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowCluster
	//
	// description	: Show cluster on the UI
	//					
	// parameters	: string&					message
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowCluster(const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowChecks
	//
	// description	: Show checks on the UI
	//					
	// parameters	: int						nPassed
	//				  int						nFailed
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowChecks(const int nPassed, const int nFailed);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetLanguage
	//
	// description	: Sets the current language
	//					
	// parameters	: string		Language
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetLanguage(const string& strLanguage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetPause
	//
	// description	: Sets the pause state
	//					
	// parameters	: bool			true pause
	//								false no pause
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetPause(const bool bPause);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetOnTop
	//
	// description	: Sets the ShowOnTop state
	//					
	// parameters	: bool			true On Top
	//								false Not On Top
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetOnTop(const bool bOnTop);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetDetail
	//
	// description	: Set the detail state
	//					
	// parameters	: bool			true show detail
	//								false don't show detail
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetDetail(const bool bDetail);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ShowAll
	//
	// description	: Show the current GUI to a specified client
	//					
	// parameters	: int				client ID
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void ShowAll(const int	nID);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Terminate
	//
	// description	: Terminate all the connected GUI's
	//					
	// parameters	: none
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Terminate();

	// Implementation

private:
	///////////////////////////////////////////////////////////////////////////////
	// function		: FormatUIMessage
	//
	// description	: Formats a UI message, "commmand:argument"
	//					
	// parameters	: string&					message
	//
	// returns		: string					formatted message
	//				  
	///////////////////////////////////////////////////////////////////////////////
	string FormatUIMessage(const string& strCommand, const string& strArgument) const;

	// Member variables
private:

	TcpIpServer*		m_pTcpIpServer;			// Association to tcpip server

	// Current GUI state store
	string				m_strActionWord;		
	string				m_strCluster;
	string				m_strError;
	string				m_strProgress;
	string				m_strChecks;
	string				m_strMessage;
	string				m_strLanguage;
	string				m_strOnTop;
	string				m_strPause;
	string				m_strDetail;
};

#endif //!UIHANDLER_H