/*****************************************************************************
 * $Workfile: UIHandler.cpp $
 * $Revision: 5 $
 * $Modtime: 6/22/00 2:35p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
#pragma warning(disable:4786)

#include <string>
#include <sstream>

using namespace std;

#include "UIHandler.h"
#include "TcpIpServer.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

UIHandler::UIHandler
(
	TcpIpServer*	pTcpIpServer
)
{
	// Store as members
	m_pTcpIpServer  = pTcpIpServer;
}

// Destructor
UIHandler::~UIHandler()
{
	// Empty
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//			=========================
void		UIHandler::ShowActionWord
//			=========================
(
	const string& strActionWord	
) 
{
	// Store current state
	m_strActionWord = strActionWord;

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("ActionWord"),strActionWord));
}


//			======================
void		UIHandler::ShowMessage
//			======================
(
	const string& strMessage	
) 
{
	// Store current state
	m_strMessage = strMessage;

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Message"),strMessage));
}

//			======================
void		UIHandler::ShowCluster
//			======================
(
	const string& strCluster	
) 
{
	// Store current state
	m_strCluster = strCluster;

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Cluster"),strCluster));
}

//			=====================
void		UIHandler::ShowErrors
//			=====================
(
	const string&	strErrorMessage,
	const int		nErrorCount
) 
{
	ostringstream ossValue;
	ossValue << strErrorMessage << ":" << nErrorCount;

	// Store current state
	m_strError = ossValue.str();

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Error"),ossValue.str()));
}

//			=======================
void		UIHandler::ShowProgress
//			=======================
(
	const int	  nExecuted,
	const int	  nTotal
) 
{
	ostringstream ossValue;
	ossValue << nExecuted << ":" << nTotal;

	// Store current state
	m_strProgress = ossValue.str();

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Progress"),ossValue.str()));
}

//			=====================
void		UIHandler::ShowChecks
//			=====================
(
	const int	  nPassed,
	const int	  nFailed
) 
{
	ostringstream ossValue;
	ossValue << nPassed << ":" << nFailed;

	// Store current state
	m_strChecks = ossValue.str();

	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Checks"),ossValue.str()));
}

//			=======================
void		UIHandler::SetLanguage
//			=======================
(
	const string&	strLanguage
) 
{
	// Store current state
	m_strLanguage = strLanguage;
}

//			===================
void		UIHandler::SetOnTop
//			===================
(
	const bool		bOnTop
) 
{
	// Store current state
	m_strOnTop = (bOnTop ? "Yes" : "No");
}

//			====================
void		UIHandler::SetPause
//			====================
(
	const bool		bPause
) 
{
	// Store current state
	m_strPause = (bPause ? "Yes" : "No");
	// Send to GUIs
	m_pTcpIpServer->Broadcast(FormatUIMessage(string("Pause"), m_strPause));
}

//			=====================
void		UIHandler::SetDetail
//			=====================
(
	const bool		bDetail
) 
{
	// Store current state
	m_strDetail = (bDetail ? "Yes" : "No");
}


//			==================
void		UIHandler::ShowAll
//			==================
(
	const int	nID
)
{
	// Send the current engine state to the GUI
	string strMessage;
	strMessage = FormatUIMessage(m_strDetail, m_strLanguage);
	strMessage = FormatUIMessage(strMessage, m_strOnTop);
	strMessage = FormatUIMessage(strMessage, m_strPause);
	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("Center"), strMessage));

	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("ActionWord"),m_strActionWord));
	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("Cluster"),m_strCluster));
	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("Error"),m_strError));
	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("Progress"),m_strProgress));
	m_pTcpIpServer->SendMessage(nID, FormatUIMessage(string("Checks"),m_strChecks));
	
}

//			====================
void		UIHandler::Terminate()
//			====================
{
	// Broadcast the terminate message
	m_pTcpIpServer->Broadcast("Terminate");
}


//			==========================
string		UIHandler::FormatUIMessage
//			==========================
(
	const string& strCommand, 
	const string& strArgument
) const
{
	return (strCommand + string(":") + strArgument);
}

