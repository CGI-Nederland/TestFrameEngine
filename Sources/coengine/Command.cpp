/*****************************************************************************
 * $Workfile: Command.cpp $
 * $Revision: 103 $
 * $Modtime: 11/09/02 13:51 $
 * $Author: Mdj $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include "Command.h"				// class definition

#include <string>
#include <sstream>

using namespace std;

#include "ActionServer.h"
#include "ActionWord.h"
#include "BasicNavigation.h"
#include "ComponentKey.h"
#include "ComposedInterpreter.h"
#include "EngineKey.h"
#include "EngineSetting.h"
#include "EngineUtil.h"
#include "FileName.h"
#include "GuiInterface.h"
#include "IOInterface.h"
#include "Log.h"
#include "MasterCommand.h"
#include "NavigationInterface.h"
#include "ReportGenerator.h"
#include "Setting.h"
#include "SlaveCallBackHandler.h"
#include "SlaveList.h"
#include "StrUtil.h"
#include "TcpIpServer.h"
#include "UICallBackHandler.h"
#include "UIHandler.h"
#include "GUIThread.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						================
						Command::Command()
//						================
{
	// Create the only allowed instance of Log via its static member function.
	m_pLog = Log::Instance();

	// Construct engine
	m_pSlaveList			= new SlaveList();
	m_pMasterCommand		= new MasterCommand(m_pSlaveList);
	m_pActionWord			= new ActionWord();
	m_pComposedInterpreter	= new ComposedInterpreter(m_pActionWord, m_pSlaveList);
	m_pNavigationInterface	= new NavigationInterface(this);
	m_pGuiInterface			= new GuiInterface(this);
	m_pReportGenerator		= new ReportGenerator();
	m_pBasicNavigation		= new BasicNavigation();
	m_pSetting				= new EngineSetting();
	m_pSnapSetting			= new Setting();
	m_pKeepSetting			= new Setting();
	m_pUIServer				= new TcpIpServer();
	m_pUIHandler			= new UIHandler(m_pUIServer);
	m_pUIcallbackHandler	= new UICallBackHandler(m_pGuiInterface, m_pUIHandler);
	m_pActionServer			= new ActionServer(m_pComposedInterpreter, m_pActionWord, m_pUIHandler, m_pKeepSetting, m_pMasterCommand);
	m_pMasterServer			= 0;
	m_pSlaveCallbackHandler	= 0;
	m_pGUIThread			= 0;

	// Initialise UI server callback handler
	m_pUIServer->SetCallbackHandler(m_pUIcallbackHandler);

	// Registering built in action words
	RegisterBuiltInActionWords();

	// Initialise flags
	m_bStop		= false;	// Stop not pressed
	m_bPause	= false;	// Pause not pressed

	// Initialise version, build number, and copyright strings.
	m_strVersion	= "6.1";
	m_strBuild		= "67";
	m_strCopyright	= "COPYRIGHT (C) 1999-2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED";
}

// Destructor
//						=================
						Command::~Command()
//						=================
{
	// Free al the resources again
	delete m_pMasterServer;
	delete m_pUIServer;
	delete m_pActionWord;
	delete m_pComposedInterpreter;
	delete m_pActionServer;
	delete m_pNavigationInterface;
	delete m_pGuiInterface;
	delete m_pReportGenerator;
	delete m_pBasicNavigation;
	delete m_pSetting;
	delete m_pSnapSetting;
	delete m_pKeepSetting;
	delete m_pUIHandler;
	delete m_pUIcallbackHandler;
	delete m_pSlaveList;
	delete m_pMasterCommand;
	delete m_pSlaveCallbackHandler;

	m_pMasterServer=0;
	m_pUIServer=0;
	m_pActionWord=0;
	m_pComposedInterpreter=0;
	m_pActionServer=0;
	m_pNavigationInterface=0;
	m_pGuiInterface=0;
	m_pReportGenerator=0;
	m_pBasicNavigation=0;
	m_pSetting=0;
	m_pSnapSetting=0;
	m_pKeepSetting=0;
	m_pUIHandler=0;
	m_pUIcallbackHandler=0;
	m_pSlaveList=0;
	m_pMasterCommand=0;
	m_pSlaveCallbackHandler=0;

	if (m_pGUIThread != 0)
	{
		// Force hard GUI shutdown, if GUI was not terminated by stop processing
		m_pGUIThread->Reset();
	}

	delete m_pGUIThread;
	delete m_pLog;

	m_pGUIThread=0;
	m_pLog=0;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===============================
NavigationInterface*	Command::GetNavigationInterface() const
//						===============================
{
	return m_pNavigationInterface;
}


//						=======================
GuiInterface*			Command::GetGUInterface() const
//						=======================
{
	return m_pGuiInterface;
}


///////////////////////////////////////////////////////////////////////////////
// Navigation -- Action Word Registration

//						===========================
bool					Command::RegisterActionWord
//						===========================
(
	const string&		strActionWord,			// name of action word
	const string&		strActionWordFunction	// name of associated action word function
)
{
	// Add the specified action word and its function with the user-defined
	// type EXTERN to the ActionWord object.
	bool bResult = m_pActionWord->Add(strActionWord, ActionWordList::EXTERN, strActionWordFunction, "");
	
	// Log this action if it was successful and if Log is ready.
	if ( bResult && m_pLog->Good() )
	{
		m_pLog->RegisterActionWord( strActionWord, strActionWordFunction );
	}

	return bResult;
}


//						===========================
bool					Command::RegisterHeaderWord 
//						===========================
(
	const string&		strHeaderWord,	// name of header word
	const string&		strTag			// report tag belonging to header word
)
{
	// Add the specified header word and its tag with the user-defined
	// type EXTERN_HEADER to the ActionWord object.
	bool bResult = m_pActionWord->Add(strHeaderWord, ActionWordList::EXTERN_HEADER, strTag, "");

	// Log this action if it was successful and if Log is ready.
	if ( bResult && m_pLog->Good() )
	{
		m_pLog->RegisterHeaderWord( strHeaderWord, strTag );
	}

	return bResult;
}


//						================================
bool					Command::CreateActionWordSynonym
//						================================
(
	const string&	strActionWord,	// action word name 
	const string&	strSynonym		// synonym for action word name
)
{
	bool bResult = m_pActionWord->CreateSynonym(strActionWord, strSynonym);

	// Log this action if it was successful and if Log is ready.
	if ( bResult && m_pLog->Good() )
	{
		m_pLog->ActionWordSynonym( strActionWord, strSynonym );
	}

	return bResult;
}


//						=============================
bool					Command::UnregisterActionWord 
//						=============================
(
	const string&		strActionWord	// action word name
)
{
	bool bResult = false;	// result of UnregisterActionWord
	int nType;				// action word type

	// Check if action word is registered in list
	if (m_pActionWord->Find(strActionWord, nType))
	{
		// Check if registered action word is of type externally defined
		if (nType == ActionWordList::EXTERN)
		{
			// Check if action word is removed
			if (m_pActionWord->Delete(strActionWord))
			{ bResult = true; }
		}
	}

	// Log this action if it was successful and if Log is ready.
	if ( bResult && m_pLog->Good() )
	{
		m_pLog->UnregisterActionWord( strActionWord );
	}

	return bResult;
}


//						=============================
bool					Command::UnregisterHeaderWord 
//						=============================
(
	const string&		strHeaderWord	// name of header word
)
{
	bool bResult = false;	// result of operation
	int nType;				// action word type

	// check if header word is registered in list
	if (m_pActionWord->Find(strHeaderWord, nType))
	{
		// check if registered header word is of type externally defined header word
		if (nType == ActionWordList::EXTERN_HEADER)
		{
			// remove header word
			if (m_pActionWord->Delete(strHeaderWord))
			{ 
				bResult = true;
			}
		}
	}

	// Log this action if it was successful and if Log is ready.
	if ( bResult && m_pLog->Good() )
	{
		m_pLog->UnregisterHeaderWord( strHeaderWord );
	}

	return bResult;
}


//						=================================
int						Command::UnregisterAllActionWords()
//						=================================
{
	int nDeletedExtern			= m_pActionWord->DeleteAllOfType(ActionWordList::EXTERN);
	int nDeletedExternHeader	= m_pActionWord->DeleteAllOfType(ActionWordList::EXTERN_HEADER);

	// Log this action if Log is ready.
	if ( m_pLog->Good() )
	{
		m_pLog->UnregisterAllActionWords();
	}

	return nDeletedExtern + nDeletedExternHeader;
}


///////////////////////////////////////////////////////////////////////////////
// Navigation -- State Control

//						====================
bool  					Command::StartEngine
//						====================
(
	const string&		strClusterFileName,	// name and path of the cluster file
	const string&		strReportFileName,	// name and path of the report file
	const string&		strIniFileName		// name and path of the ini file with the
											//	settings of the Engine
)
{
	bool bResult = false;	// result of StartEngine

	// Read the settings from the inifile
	InitialiseSettings(m_pSetting, strIniFileName);

	// Check if the engine license key is valid
//	if (ValidateEngineLicense(m_pSetting)) Remove license check JU 20130408
//{
		// update the engine settings and write them to the ini file
		UpdateIniFile(strClusterFileName, strReportFileName);

		// check if all engine settings are valid
		if (m_pSetting->Validate())
		{
			// read the keep and the snap file
			ReadKeepFile();
			ReadSnapFile();

			// Initialise ui server
			if (m_pUIServer != 0) 
			{	
				// Convert port number to int
				unsigned int unPort;
				istringstream	issPort(m_pSetting->Get("GUI","Port"));
				issPort >> unPort;

				if (!issPort.fail())
				{
					m_pUIServer->SetPort(unPort);
					m_pUIServer->Start();
				}
			}

			// Check for master slaveslave mode
			if ( InMasterMode() )
			{
				// Create master server
				m_pMasterServer = new TcpIpServer();

				if (m_pMasterServer != 0) 
				{
					// Convert port number to int
					unsigned int unPort;
					istringstream	issPort(m_pSetting->Get("MASTERSLAVE","Port"));
					issPort >> unPort;

					if (!issPort.fail())
					{
						// Create callback handler
						m_pSlaveCallbackHandler = new SlaveCallBackHandler(m_pSlaveList);

						// Notify MasterCommand
						m_pMasterCommand->SetMasterServer(m_pMasterServer);

						// Initialise masterslave server
						m_pMasterServer->SetPort(unPort);
						m_pMasterServer->SetCallbackHandler(m_pSlaveCallbackHandler);
						m_pMasterServer->Start();
					}
				}
			}

			// Initialise ComposedInterpreter.
			m_pComposedInterpreter->Initialise( m_pSetting );

			// Initialise Log.
			m_pLog->Initialise( m_pSetting );

			// Determine if Log is ready for logging.
			if ( m_pLog->Good() )
			{
				// Write the log header.
				WriteLogHeader( strClusterFileName, strReportFileName, strIniFileName );

				// Initialise ActionServer.
				m_pActionServer->Initialise( m_pSetting );

				// Determine if the ActionServer could be initialised.
				if ( m_pActionServer->Good() )
				{
					// Start a local GUI if necessary
					if (m_pSetting->Get("GUI","LaunchGUI") == "Yes")
					{ 
						LaunchGUI(); 
					}

					// Initialise GUI settings
					InitialiseGUI();
					
					// Wait for GUI connect
					if (m_pSetting->Get("SYSTEM","WaitForGUI") == "Yes")
					{
						int nRetry = (10 * 60 * 5); // Wait a maximum of 5 minutes for GUI

						while ((m_pUIServer->GetNumberOfClients() == 0) && (nRetry != 0) ) 
						{
							nRetry--;
							EngineSleep(100); 
						} 
					}

					bResult = true;
				}
			}
		}
//	}

	// Determine if the Engine could not be started.
	if ( !bResult )
	{
		FinishProcessing();
	}

	return bResult;
}


//						===================
void					Command::StopEngine()
//						===================
{
	m_pLog->EngineStop();

	// Finish processing
	FinishProcessing();
}


///////////////////////////////////////////////////////////////////////////////
// Navigation -- Report Generating

//						=======================
bool					Command::GenerateReport()
//						=======================
{
	bool bResult = false;

	// Determine if the Log-, EngineSetting- and ReportGenerator objects exist.
	if ( m_pLog != 0 && m_pSetting != 0 && m_pReportGenerator != 0 )
	{
		// Determine the name of the log file.
		string strLog = m_pLog->GetLogName();

		// Start generating report(s) from the log file.
		bResult = m_pReportGenerator->Start( strLog, m_pSetting );
	}

	return bResult;
}


//						==============================
bool					Command::GenerateReportFromLog
//						==============================
(
	const string&		strLogFileName,			// Name of the log file
	const string&		strReportName,			// Name of the report
	const string&		strIniFilename			// Name of the inifile
)
{
	bool bResult = false;

	// Create an EngineSetting object for the specified ini-file.
	EngineSetting* pSetting = new EngineSetting();
	InitialiseSettings( pSetting, strIniFilename );
	
	// Only proceed when the license key is valid.
//	if ( ValidateEngineLicense( pSetting ) )  JU 20120408 remove license check
//	{
		// Check if the log and report filenames are not empty
		if( (strLogFileName.size() != 0) && (strReportName.size() != 0) )
		{
			// Check if all engine settings are valid.
			if ( pSetting->Validate() )
			{
				// Set the location of the log file to the one from the settings,
				// if none is specified in the name.
				FileName fnLog( strLogFileName );
				if ( fnLog.GetLocation().empty() )
				{
					fnLog.ChangeLocation( pSetting->Get( "LOG", "Path" ) );
				}
				string strLog = fnLog.GetFile();

				// Set the location of the report file to the one from the
				// settings, if none is specified in the name.
				FileName fnReport( strReportName );
				if ( fnReport.GetLocation().empty() )
				{
					fnReport.ChangeLocation( pSetting->Get( "REPORT", "Path" ) );
				}
				string strReport = fnReport.GetFile();

				// Start generating report(s) from the log file.
				bResult = m_pReportGenerator->Start( strLog, pSetting, strReport );
			}
		}
//	}

	// Delete the EngineSetting object.
	delete pSetting;

	pSetting=0;

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Navigation -- Test Flow

// The loop inside Command::ProcessNexLine() disappears when compiled with 
// optimisations switched on.
// We therefore do not want optimisation of this function.
#pragma optimize( "", off )

//						========================
bool					Command::ProcessNextLine()
//						========================
{
	bool bPauseLoop = false;		// boolean to set when going into the Pause loop

	if (m_bPause)
	{
		// Log pausing the engine.
		m_pLog->EnginePause();
	}
	if (m_bStop)
	{
		return (false);
	}

	// Pause loop: block if pause flag is set
	while (m_bPause) 
	{ 
		// Wait for 100 miliseconds
		EngineSleep(100);

		// Check if stop is pressed in pause mode.
		if (m_bStop)
		{
			// Cluster done: write to log file and return
			m_pLog->EMCStop();
			return (false);
		}

		// Check no UI clients available
		if (m_pUIServer->GetNumberOfClients() == 0) 
		{
			// Connection to client(s) lost, continue with test
			m_bPause = false;
		}

		bPauseLoop = true;
	}
	// The only way to come out of the while loop is by pressing Resume
	// button; check this through bPauseLoop and use this to log the action.
	if (bPauseLoop)
	{
		// Log resuming the engine.
		m_pLog->EngineResume();
	}

	// Get next line, and return the result of this operation; true means a
	// next line is found; false means the main cluster has ended.
	return m_pActionServer->Next();
}

// Switch optimisation back on.
#pragma optimize( "", on ) 

///////////////////////////////////////////////////////////////////////////////
// Navigation -- Run Time Information

//						======================
string					Command::GetActionWord()
//						======================
{
	return m_pActionServer->GetActionWord();
}


//						==============================
string					Command::GetActionWordFunction
//						==============================
(
	const string&		strActionWord	// action word to get associated function for
)
{
	string strActionWordFunction;		// action word function to return

	// check if an action word is specified
	if (strActionWord.empty())
	{
		// return current action
		strActionWordFunction = m_pActionServer->Action();
	}
	else
	{
		int	nDummy;			// Dummy standin for actiontype

		// get action word function associated with specified action word
		if (!m_pActionWord->Find(strActionWord, nDummy, strActionWordFunction))
		{
			// return an empty string if the action word could not be found
			strActionWordFunction = string();
		}
	}

	return strActionWordFunction;
}


//						====================
string					Command::GetArgument
//						====================
(
	int					nIndex		// index of argument list
)
{
	return m_pActionServer->Argument(nIndex); 
}


//						=====================
string					Command::GetParameter
//						=====================
(
	int					nIndex
)
{
	return m_pActionServer->GetParameter( nIndex );
}


//						=============================
int						Command::GetNumberOfArguments()
//						=============================
{
	return m_pActionServer->ArgumentCount();
}


//						==============================
int						Command::GetNumberOfParameters()
//						==============================
{
	return m_pActionServer->GetNumberOfParameters();
}


//						====================
string					Command::GetTestCase()
//						====================
{
	return m_pActionServer->GetTestCase();
}

//						=========================
string					Command::GetTestCondition()
//						=========================
{
	return m_pActionServer->GetTestCondition();
}

//						===================
string					Command::GetSection()
//						===================
{
	return m_pActionServer->GetSection();
}


//						====================
string					Command::GetScenario()
//						====================
{
	return m_pActionServer->GetScenario();
}


//						=======================
string					Command::GetClusterFile()
//						=======================
{
	return m_pActionServer->GetClusterFile();
}


//						======================
int						Command::GetLineNumber()
//						======================
{
	return (int) m_pActionServer->LineNumber();
}


//						==========================
int						Command::GetNumberOfErrors()
//						==========================
{
	return m_pActionServer->GetNumberOfErrors();
}


//						=======================
string					Command::GetLatestError()
//						=======================
{
	return m_pActionServer->GetLatestError();
}


//						===============================
string					Command::GetArgumentDescription
//						===============================
(
	int				nIndex
)
{
	return m_pActionServer->GetArgumentDescription(nIndex);
}


//						================================
string					Command::GetParameterDescription
//						================================
(
	int					nIndex
)
{
	return m_pActionServer->GetParameterDescription( nIndex );
}


//						=====================
const string&			Command::GetCopyright() const
//						=====================
{
	return m_strCopyright;
}


//						===================
const string&			Command::GetVersion() const
//						===================
{
	return m_strVersion;
}


//						=================
const string&			Command::GetBuild() const
//						=================
{
	return m_strBuild;
}


//						===================
const string&			Command::GetLogFile() const
//						===================
{
	return m_pLog->GetLogName();
}

///////////////////////////////////////////////////////////////////////////////
// Navigation -- Reporting

//						======================
void					Command::ReportComment
//						======================
(
	const string&		strComment
)
{
	m_pLog->ReportComment( strComment );
}


//						====================
bool					Command::ReportError
//						====================
(
	const string&		strErrorText,	// text of error message
	int					nErrorTypeCode	// error type code
)
{
	bool bResult = false;

	Log::ERRORCODE nErrorCodeToUse;	// error code to use for call to ActionServer

	// check error type code
	switch (nErrorTypeCode)
	{
		case 0:
		// error type: WARNING
		{
			nErrorCodeToUse = Log::NUM_ERR_WARNING;
			bResult			= true;
			break;
		}

		case 1:
		// error type: ERROR
		{
			nErrorCodeToUse = Log::NUM_ERR_ERROR;
			bResult			= true;
			break;
		}

		case 2:
		// error type: CHECK
		{
			nErrorCodeToUse = Log::NUM_ERR_CHECK;
			bResult			= true;
			break;
		}

		case 3:
		// error type: FATAL
		{
			nErrorCodeToUse = Log::NUM_ERR_FATAL;
			bResult			= true;
			break;
		}

		default:
		// invalid code
		{
			nErrorCodeToUse = Log::NUM_ERR_FATAL;
			bResult = false;
		}
	}

	// Log error if type was valid
	if ( bResult )
	{
		m_pLog->ReportError( nErrorCodeToUse, strErrorText );
		m_pActionServer->ReportError( strErrorText );
	}

	return bResult;
}

//						====================
bool					Command::ReportCheck
//						====================
(
	const string&		strDescription,	// description of check
	const string&		strExpected,	// string containing expected value
	const string&		strRecorded,	// string to be compared with expected value
	int					nCheckResult	// check result value
)
{	
	bool bResult = false;
	
	// Determine if the specified result value is one of the two allowed
	// values: 0 or 1.
	if ( nCheckResult == 0 || nCheckResult == 1 )
	{
		// Set the result value to false if 0 is specified, and to true if 1.
		bool bCheck = false;
		if ( nCheckResult == 1 )
		{ bCheck = true; }

		// Log the check; specify as check type CHECK_REPORT, since it is
		// logged via tfe_ReportCheck; set the index to 0, since for this
		// check type it can be ignored.
		try
		{
			m_pLog->Check( bCheck, strDescription, strExpected, strRecorded, Log::CHECK_REPORT, 0 );
			m_pActionServer->ReportCheck( bCheck );
			bResult = 1;
		}
		catch (...) 
		{
			m_pLog->ReportError( Log::NUM_ERR_ERROR, "error Command::ReportCheck " );
		}

	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Navigation -- Checking

//						====================
bool					Command::CheckString
//						====================
(
	const string&		strDescription,	// description of check
	const string&		strExpected,	// string containing expected value
	const string&		strRecorded		// string to be compared with expected value
)
{
	bool bResult = false;

	// Compare recorded against expected value
	bResult = m_pBasicNavigation->Compare(strRecorded, strExpected);

	// Log the check; specify as check type CHECK_STRING, since it is logged
	// via tfe_CheckString; set the index to 0, since for this check type it
	// can be ignored.
	m_pLog->Check( bResult, strDescription, strExpected, strRecorded, Log::CHECK_STRING, 0 );
	m_pActionServer->ReportCheck( bResult );

	return bResult;
}


//						======================
bool					Command::CheckArgument
//						======================
(
	int					nArgumentIndex,		// index of argument to be compared with string
	const string&		strRecorded,		// string to be compared with argument
	bool				bHorizontal			// states whether or not a check is to be
											//	printed horizontally in the report
)
{
	bool bResult = false;	// result of CheckArgument

	// Determine if the argument index is greater than zero.
	if ( nArgumentIndex > 0 )
	{
		// Determine the description.
		string strDescription = GetArgumentDescription( nArgumentIndex );

		// Check if description is empty.
		if ( strDescription.empty() )
		{
			// Take as description the index of the argument, 
			// preceded by "Argument".
			strDescription = "Argument " + IntToStr( nArgumentIndex );
		}

		bResult = PerformArgCheck( strDescription, nArgumentIndex, strRecorded, Log::CHECK_ARGUMENT );
	}

	return bResult;
}


//						=======================
bool					Command::CheckParameter
//						=======================
(
	int					nParameterIndex,
	const string&		strRecorded
)
{
	bool bResult = false;

	// Determine is the parameter index is greater than zero.
	if ( nParameterIndex > 0 )
	{
		// Determine the description.
		string strDescription = GetParameterDescription( nParameterIndex );

		// Check if description is empty.
		if ( strDescription.empty() )
		{
			// Take as description the index of the parameter,
			// preceded by "Parameter".
			strDescription = "Parameter " + IntToStr( nParameterIndex );
		}

		// Determine the argument index, corrected for the difference
		// between argument and parameter index.
		int nIndex = nParameterIndex + 1;
		if ( InMasterMode() )
		{
			// Add one more to the argument index because of the slave column.
			nIndex++;
		}

		bResult = PerformArgCheck( strDescription, nIndex, strRecorded, Log::CHECK_PARAMETER );
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Navigation -- Cluster variables

//						=====================
bool					Command::KeepArgument 
//						=====================
(
	const string&		strValue, 
	int					nIndex
)
{
	bool bResult = false; 

	string strKeepName;		// name of the kept variable

	// check if specified argument contains keep command and if so, add it to the context
	if (m_pActionServer->KeepArgument(strValue, nIndex))
	{
		// determine kept variable name
		m_pComposedInterpreter->InKeepVector(nIndex, strKeepName);
		
		// add kept variable and value to keep file
		m_pKeepSetting->Set("KEEP", strKeepName, strValue);
		m_pKeepSetting->Export();

		// Log keep action; first determine the name of the keep file.
		string strKeepFile = m_pKeepSetting->GetFileName();
		m_pLog->Keep( strKeepName, strValue, nIndex, strKeepFile );

		bResult = true;
	}

	return bResult;
}


//						======================
bool					Command::KeepParameter
//						======================
(
	const string&		strValue,
	int					nIndex
)
{
	bool bResult = false;

	// Determine is the parameter index is greater than zero.
	if ( nIndex > 0 )
	{
		// Determine the number of argument to correct for the difference
		// between argument and parameter index.
		int nCorrection = 1;
		if ( InMasterMode() )
		{ 
			nCorrection = 2; 
		}

		// Delegate to KeepArgument.
		bResult = KeepArgument( strValue, nIndex + nCorrection);
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Navigation -- GUI

//						=======================
void					Command::DisplayMessage 
//						=======================
(
	const string&		strMessage	// message to be displayed
)
{
	// Log displaying a message.
	m_pLog->DisplayMessage( strMessage );

	// Pause only if a UI client is available
	if (m_pUIServer->GetNumberOfClients() != 0) 
	{
		// Pause the engine
		Pause();
	}

	// Display message on UI	
	m_pUIHandler->ShowMessage(strMessage);
}


///////////////////////////////////////////////////////////////////////////////
// Navigation -- Old Interface Support

//						====================
string					Command::ReadSetting 
//						====================
(
	const string&	strIniFile,	// location and name of file
	const string&	strSection,	// section name
	const string&	strOption	// option name
)
{
	Setting* pSetting	= new Setting();	// pointer to setting object
	string strResult;						// result of operation

	// specifying location and name of file to object
	pSetting->SetFileName(strIniFile);

	// check if object was filled with contents of file
	if (pSetting->Import())
	{
		// retrieving value of location in file specified by
		// section and option
		strResult = pSetting->Get(strSection, strOption);
	}

	delete pSetting;

	pSetting=0;

	return strResult;
}


//						=====================
bool					Command::WriteSetting 
//						=====================
(
	const string&	strIniFile,	// location and name of file
	const string&	strSection,	// section name
	const string&	strOption,	// option name
	const string&	strValue	// option value
)
{
	Setting* pSetting	= new Setting();	// pointer to setting object
	bool bResult		= false;			// result of operation

	// specifying location and name of file to object
	pSetting->SetFileName(strIniFile);

	// fill object with contents of file
	pSetting->Import();

	// check if value was changed or added
	if (pSetting->Set(strSection, strOption, strValue))
	{
		// check changes were saved to file
		if (pSetting->Export())
		{ bResult = true; }
	}

	delete pSetting;

	pSetting=0;

	return bResult;
}


//						==================
int						Command::LineCount()
//						==================
{
	// return value of GetTotalLine (long) is casted to int.
	return (int) m_pActionServer->GetTotalLine();
}


//						===============
int						Command::Status()
//						===============
{
	// NOTE mn: What does this method do?
	return (0);
}


//						=====================
int						Command::DateArgument
//						=====================
(
	int nIndex
)
{
	return (0);
}


///////////////////////////////////////////////////////////////////////////////
// GUI

//						=========================
void					Command::StopASynchronous()
//						=========================
{
	// Set the stop flag
	m_bStop = true;

	m_pLog->EMCStop();
}


//						==============
int						Command::Pause()
//						==============
{
	// Check not already in Pause state
	if (!m_bPause)
	{
		// Set pause flag
		m_bPause = true;

		m_pLog->EMCPause();

		// Notify GUI
		m_pUIHandler->SetPause(m_bPause);
	}

	//@@ change return to void
	return (0);
}


//						===============
int						Command::Resume()
//						===============
{
	// Check in pause state
	if (m_bPause)
	{
		// Clear pause flag
		m_bPause = false;

		m_pLog->EMCResume();

		// Notify GUI
		m_pUIHandler->SetPause(m_bPause);
	}

	//@@ change return to void
	return (0);
}

////////////////
//						=======================
void					Command::LogEngineReset()
//						=======================
{
	m_pLog->EngineReset();
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=======================
string					Command::GetLicenseFile
//						=======================
(
	EngineSetting*		pSetting
)
{
	string strLicenseFile;

	if (pSetting != 0)
	{
		// Determine path of license file from engine ini file
		string strLicensePath = pSetting->Get("LICENSE","Path");

		// Concatenate file name to the path
		strLicenseFile = strLicensePath + "license.key";
	}

	// Return the file name
	return strLicenseFile;
}

//						==============================
/*bool					Command::ValidateEngineLicense
//						==============================
(
	EngineSetting*		pSetting
)
{
	// Default result is failure
	bool bResult = false;
	
	// Get the filename of the license key
	string strLicenseFile = GetLicenseFile(pSetting);

	// Object for license file settings
	Setting license;

	// Import the data from the license file
	if (license.Import(strLicenseFile))
	{
		// Retrieve the encrypted key data
		string strEncryptedData = license.Get("Engine", "Key");

		// Create an Engine key
		EngineKey key;

		// Set the encrypted data
		key.SetEncrypted(strEncryptedData);

		// Decrypt the data
		if (key.Decrypt())
		{
			// Check the time lock
			if (key.CheckTimeLock())
			{
				// Retrieve the license data
				m_strCustomerName = key.GetCustomerName();
				m_strCompanyName = key.GetCompanyName();
				m_strLicenseNumber = key.GetLicenseNumber();

				// We have a valid license!
				bResult = true;
			}
			else
			{
				// Error, key expired
				string strError = "Engine license key has expired. (" + key.GetTimeLock() + ")";
				IOInterface::WriteIOError(string("Engine 6.1"), strError, string("Contact CGI for a valid license."));
			}
		}
		else
		{
			// Error, illegal key
			IOInterface::WriteIOError(string("Engine 6.1"), string("Engine license key is invalid."), string("Contact CGI for a valid license."));
		}
	}
	else
	{
		// Error, could not open license file
		string strError = "Could not open license file: " + strLicenseFile;
		IOInterface::WriteIOError(string("Engine 6.1"), strError, string("Make sure the license path in the Engine inifile is correct."));
	}

	return bResult;
}*/

//						=================================
bool					Command::ValidateComponentLicense
//						=================================
(
	const string&		strComponentName
)
{
	// Default result is failure
	bool bResult = false;
	
	// Get the filename of the license key
	string strLicenseFile = GetLicenseFile(m_pSetting);

	// Object for license file settings
	Setting license;

	// Import the data from the license file
	if (license.Import(strLicenseFile))
	{
		// Retrieve the encrypted key data
		string strEncryptedData = license.Get("Components", strComponentName);

		// Create a Component key
		ComponentKey key;

		// Set the encrypted data
		key.SetEncrypted(strEncryptedData);

		// Decrypt the data
		if (key.Decrypt())
		{
			// Check the time lock
			if (key.CheckTimeLock())
			{
				// Retrieve the component name from the key
				string strKeyComponentName = key.GetComponentName();

				// Name in key should match the passed name
				if (strKeyComponentName == strComponentName)
				{
					// Retrieve the engine license number
					string strLicenseNumber = key.GetEngineLicenseNumber();
					
					// Engine license number should match the one from the
					// component key to prevent copying to other license files
					if (m_strLicenseNumber == strLicenseNumber)
					{
						// We have a valid license!
						bResult = true;
					}
					else
					{
						// Error, invalid engine license number
						string strError = "Component license is invalid: Engine license number does not match key (" + strComponentName + ").";
						IOInterface::WriteIOError(string("TestFrame Engine 6.1"), strError, string("Contact CGI for a valid license."));
					}
				}
				else
				{
					// Error, invalid component name
					string strError = "Component license is invalid: component name does not match key (" + strComponentName + ").";
					IOInterface::WriteIOError(string("TestFrame Engine 6.1"), strError, string("Contact CGI for a valid license."));
				}
			}
			else
			{
				// Error, key expired
				string strError = "Engine component key has expired: " + strComponentName + " (" + key.GetTimeLock() + ")";
				IOInterface::WriteIOError(string("TestFrame Engine 6.1"), strError, string("Contact CGI for a valid license."));
			}
		}
		else
		{
			// Error, illegal key
			string strError = "Engine component key is invalid: " + strComponentName;
			IOInterface::WriteIOError(string("TestFrame Engine 6.1"), strError, string("Contact CGI for a valid license."));
		}
	}
	else
	{
		// Error, could not open license file
		string strError = "Could not open license file: " + strLicenseFile;
		IOInterface::WriteIOError(string("TestFrame Engine 6.1"), strError, string("Make sure the license path in the Engine inifile is correct."));
	}

	return bResult;
}

//						======================
void					Command::UpdateIniFile
//						======================
(
	const string&		strClusterFileName,	// cluster file to update
	const string&		strReportFileName	// report file to update
)
{
	// check if the specified cluster file is not empty
	if (!strClusterFileName.empty())
	{
		// update the cluster file name and path settings
		// determine file name
		string strFileName = GetFileName(strClusterFileName);

		// check if file name is not empty
		if (!strFileName.empty())
		{ m_pSetting->Set("CLUSTER", "FileName", strFileName); }

		// determine path
		string strFilePath = GetFilePath(strClusterFileName);

		// check if path is not empty
		if (!strFilePath.empty())
		{ m_pSetting->Set("CLUSTER", "Path", strFilePath); }
	}

	// check if the specified report file is not empty
	if (!strReportFileName.empty())
	{
		// update the report file name and path settings
		// determine file name
		string strFileName = GetFileName(strReportFileName);

		// check if file name is not empty 
		if (!strFileName.empty())
		{ m_pSetting->Set("REPORT", "FileName", strFileName); }

		// determine path
		string strFilePath = GetFilePath(strReportFileName);

		// check if filepath s not empty
		if (!strFilePath.empty())
		{ m_pSetting->Set("REPORT", "Path", strFilePath); }
	}

	// Update license name, company and serial number
	m_pSetting->Set("LICENSE", "Name", m_strCustomerName);
	m_pSetting->Set("LICENSE", "Company", m_strCompanyName);
	m_pSetting->Set("LICENSE", "SerialNumber", m_strLicenseNumber);

	// Update Engine version
	m_pSetting->Set("SYSTEM", "EngineVersion", m_strVersion);
	m_pSetting->Set("SYSTEM", "EngineBuild", m_strBuild);

	// Export these updated values to the ini file
	m_pSetting->Export();
}


//						=====================
void					Command::ReadKeepFile()
//						=====================
{
	// determine keep file name
	string strKeepFile = m_pSetting->Get("KEEP","Path") + m_pSetting->Get("KEEP","FileName"); 

	if (!strKeepFile.empty())
	{
		// read all the settings from the keep file
		m_pKeepSetting->Import(strKeepFile);
	}
}

//						=====================
void					Command::WriteKeepFile()
//						=====================
{
	// determine keep file name
	string strKeepFile = m_pSetting->Get("KEEP","Path") + m_pSetting->Get("KEEP","FileName"); 

	if (!strKeepFile.empty())
	{
		// write all the settings to the keep file
		m_pKeepSetting->Export(strKeepFile);
	}
}


//						=====================
void					Command::ReadSnapFile()
//						=====================
{
	// determine snap file name
	string strSnapFile = m_pSetting->Get("SNAP","Path") + m_pSetting->Get("SNAP","FileName"); 

	if (!strSnapFile.empty())
	{
		// read all the settings from the snap file
		m_pSnapSetting->Import(strSnapFile);
	}
}


//						======================
void					Command::InitialiseGUI()
//						======================
{
	// Send language to GUI
	m_pUIHandler->SetLanguage(m_pSetting->Get("SYSTEM","Language"));

	// Send initial pause state to GUI
	m_pUIHandler->SetPause(false);

	// Send GUI on top on/off to GUI
	if (m_pSetting->Get("GUI","OnTop") == "Yes")
	{
		m_pUIHandler->SetOnTop(true);
	}
	else
	{
		m_pUIHandler->SetOnTop(false);
	}

	// Send GUI detail on/off to GUI
	if (m_pSetting->Get("GUI","Detail") == "Yes")
	{
		m_pUIHandler->SetDetail(true);
	}
	else
	{
		m_pUIHandler->SetDetail(false);
	}
}


//						==================
bool					Command::LaunchGUI()
//						==================
{
	bool bResult = false;

#ifdef	UNIX

	// Unix
	// No GUI available for UNIX systems, yet

#else

	// Build commandline string
	string strCommandLine("-h localhost -p ");
	
	// Add gui port setting
	strCommandLine += m_pSetting->Get("GUI","Port");

	// Greate GUI thread
	m_pGUIThread = new GUIThread();
	m_pGUIThread->SetCommandLine(strCommandLine);

	// Start GUI
	if (m_pGUIThread->Start())
	{
		bResult = true;
	}

#endif

	return bResult;
}


//						=========================
void					Command::FinishProcessing()
//						=========================
{
	
	// Destruction of all pointers used in ActionServer
	m_pActionServer->Clear(); 

	// Clear stop and pause flags
	m_bStop		= false;
	m_bPause	= false;

	// Destroy the message centre
	m_pUIHandler->Terminate();


	// Stop the TCP-IP threads
	if (m_pUIServer != 0)
	{ m_pUIServer->Stop(); }
	if (m_pMasterServer != 0)
	{ m_pMasterServer->Stop(); }
	
	// Delete GUI thread
	delete m_pGUIThread; // causes jni to hang already in destructor
	m_pGUIThread = 0;
}


//						===================================
void					Command::RegisterBuiltInActionWords()
//						===================================
{
	// Header words
	m_pActionWord->Add("cluster",			ActionWordList::CLUSTER_NAME, "", "");
	m_pActionWord->Add("Cluster",			ActionWordList::CLUSTER_NAME, "", "");
	m_pActionWord->Add("groupe de test",	ActionWordList::CLUSTER_NAME, "", "");
	
	m_pActionWord->Add("author",	ActionWordList::CLUSTER_AUTHOR, "", "");
	m_pActionWord->Add("Autor",		ActionWordList::CLUSTER_AUTHOR, "", "");
	m_pActionWord->Add("auteur",	ActionWordList::CLUSTER_AUTHOR, "", "");
	
	m_pActionWord->Add("date",		ActionWordList::CLUSTER_DATE, "", "");
	m_pActionWord->Add("Datum",		ActionWordList::CLUSTER_DATE, "", "");
	m_pActionWord->Add("datum",		ActionWordList::CLUSTER_DATE, "", "");
	
	m_pActionWord->Add("version",	ActionWordList::CLUSTER_VERSION, "", "");
	m_pActionWord->Add("Version",	ActionWordList::CLUSTER_VERSION, "", "");
	m_pActionWord->Add("versie",	ActionWordList::CLUSTER_VERSION, "", "");

	m_pActionWord->Add("document",	ActionWordList::DOCUMENT , "", "");
	m_pActionWord->Add("Dokument",	ActionWordList::DOCUMENT , "", "");

	m_pActionWord->Add("sheet",				ActionWordList::SHEET , "", "");
	m_pActionWord->Add("Arbeitsblatt",		ActionWordList::SHEET , "", "");
	m_pActionWord->Add("feuille de calcul",	ActionWordList::SHEET , "", "");
	m_pActionWord->Add("blad",				ActionWordList::SHEET , "", "");

	// Built-in action words for structuring
	m_pActionWord->Add("scenario",		ActionWordList::SCENARIO , "", "");
	m_pActionWord->Add("Testszenario",	ActionWordList::SCENARIO , "", "");
	m_pActionWord->Add("scénario",		ActionWordList::SCENARIO , "", "");

	m_pActionWord->Add("section",		ActionWordList::SECTION , "", "");
	m_pActionWord->Add("Testabschnitt",	ActionWordList::SECTION , "", "");
	m_pActionWord->Add("sectie",		ActionWordList::SECTION , "", "");

	m_pActionWord->Add("test case",		ActionWordList::TEST_CASE , "", "");
	m_pActionWord->Add("Testfall",		ActionWordList::TEST_CASE , "", "");
	m_pActionWord->Add("cas de test",	ActionWordList::TEST_CASE , "", "");
	m_pActionWord->Add("testgeval",		ActionWordList::TEST_CASE , "", "");
	m_pActionWord->Add("testcase",		ActionWordList::TEST_CASE , "", "");

	m_pActionWord->Add("test condition",	ActionWordList::TEST_CONDITION , "", "");
	m_pActionWord->Add("Testbedingung",		ActionWordList::TEST_CONDITION , "", "");
	m_pActionWord->Add("condition de test",	ActionWordList::TEST_CONDITION , "", "");
	m_pActionWord->Add("testconditie",		ActionWordList::TEST_CONDITION , "", "");
	m_pActionWord->Add("testcondition",		ActionWordList::TEST_CONDITION , "", "");

	// Built-in action words for subclusters
	m_pActionWord->Add("do cluster",			ActionWordList::SUBCLUSTER, "", "");	
	m_pActionWord->Add("Führe Cluster aus",		ActionWordList::SUBCLUSTER, "", "");	
	m_pActionWord->Add("exécuter cluster",		ActionWordList::SUBCLUSTER, "", "");	
	m_pActionWord->Add("voer cluster uit",		ActionWordList::SUBCLUSTER, "", "");	

	// Built-in action words for templates
	m_pActionWord->Add("define template",			ActionWordList::DEFINE_TEMPLATE, "", "");
	m_pActionWord->Add("Definiere Template",		ActionWordList::DEFINE_TEMPLATE, "", "");
	m_pActionWord->Add("définition de template",	ActionWordList::DEFINE_TEMPLATE, "", "");
	m_pActionWord->Add("definieer template",		ActionWordList::DEFINE_TEMPLATE, "", "");
	m_pActionWord->Add("definiëer template",		ActionWordList::DEFINE_TEMPLATE, "", "");

	m_pActionWord->Add("end template",			ActionWordList::END_TEMPLATE, "", "");
	m_pActionWord->Add("Ende Template",			ActionWordList::END_TEMPLATE, "", "");
	m_pActionWord->Add("fin de template",		ActionWordList::END_TEMPLATE, "", "");
	m_pActionWord->Add("einde template",		ActionWordList::END_TEMPLATE, "", "");

	m_pActionWord->Add("template prototype",	ActionWordList::TEMPLATE_PROTO, "", "");

	m_pActionWord->Add("declare template",			ActionWordList::DECLARE_TEMPLATE, "", "");
	m_pActionWord->Add("Deklariere Template",		ActionWordList::DECLARE_TEMPLATE, "", "");
	m_pActionWord->Add("déclaration de template",	ActionWordList::DECLARE_TEMPLATE, "", "");
	m_pActionWord->Add("declareer template",		ActionWordList::DECLARE_TEMPLATE, "", "");

	// Built-in action words for data transfer
	m_pActionWord->Add("export variable",		ActionWordList::EXPORT_TO_FILE, "", "");
	m_pActionWord->Add("Exportiere Variable",	ActionWordList::EXPORT_TO_FILE, "", "");
	m_pActionWord->Add("exporter variable",		ActionWordList::EXPORT_TO_FILE, "", "");
	m_pActionWord->Add("exporteer variabele",	ActionWordList::EXPORT_TO_FILE, "", "");

	m_pActionWord->Add("import variable",		ActionWordList::IMPORT_FROM_FILE, "", "");
	m_pActionWord->Add("Importiere Variable",	ActionWordList::IMPORT_FROM_FILE, "", "");
	m_pActionWord->Add("importer variable",		ActionWordList::IMPORT_FROM_FILE, "", "");
	m_pActionWord->Add("importeer variabele",	ActionWordList::IMPORT_FROM_FILE, "", "");

	// Built-in action words for Master/Slave communication
	m_pActionWord->Add("connect slave",			ActionWordList::CONNECT_SLAVE , "", "");
	m_pActionWord->Add("Verbinde Slave",		ActionWordList::CONNECT_SLAVE , "", "");
	m_pActionWord->Add("connecter esclave",		ActionWordList::CONNECT_SLAVE , "", "");
	m_pActionWord->Add("verbind slaaf",			ActionWordList::CONNECT_SLAVE , "", "");

	m_pActionWord->Add("disconnect slave",		ActionWordList::DISCONNECT_SLAVE , "", "");
	m_pActionWord->Add("Beende Slave",			ActionWordList::DISCONNECT_SLAVE , "", "");
	m_pActionWord->Add("déconnecter esclave",	ActionWordList::DISCONNECT_SLAVE , "", "");
	m_pActionWord->Add("verbreek slaaf",		ActionWordList::DISCONNECT_SLAVE , "", "");

	// Built-in action words for flow of control
	m_pActionWord->Add( "if",			ActionWordList::IF, "", "" );

	m_pActionWord->Add( "end if",		ActionWordList::END_IF, "", "" );

	m_pActionWord->Add( "else",			ActionWordList::ELSE, "", "" );

	m_pActionWord->Add( "else if",		ActionWordList::ELSE_IF, "", "" );

	m_pActionWord->Add( "repeat",		ActionWordList::REPEAT, "", "" );

	m_pActionWord->Add( "end repeat",	ActionWordList::END_REPEAT, "", "" );

	m_pActionWord->Add( "while",		ActionWordList::WHILE, "", "" );

	m_pActionWord->Add( "end while",	ActionWordList::END_WHILE, "", "" );

	// Utility built-in action words
	m_pActionWord->Add( "set", ActionWordList::SET, "", "" );
}


//						====================
string					Command::GetFileName
//						====================
(
	const string& strFileName
)
{
	string strResult = strFileName;	// string containing return value of method

	string::size_type nPos = strFileName.find_last_of( "/\\" );

	// check if filesystem separator "/" or "\" is found 
	if ( nPos != string::npos )
	{ 
		strResult = strFileName.substr( nPos + 1 );
	}
	
	return strResult;
}

//						====================
string					Command::GetFilePath
//						====================
(
	const string& strFileName
)
{
	string strResult;	// string containing return value of method

	string::size_type nPos = strFileName.find_last_of( "/\\" );

	// check if filesystem separator "/" or "\" is found 
	if ( nPos != string::npos )
	{ 
		strResult = strFileName.substr( 0, nPos + 1 );
	}

	return strResult;
}

//						===========================
bool					Command::InitialiseSettings
//						===========================
(
	EngineSetting*		pSetting,				// Pointer to a setting object
	const string&		strIniFilename			// Name of the inifile to read
)
{
	bool bResult = false;

	// We need a valid setting object to do our work
	if (pSetting != 0)
	{
		// Initialization of Setting object
		pSetting->SetFileName(strIniFilename);		

		// Fill the Setting object with data from file
		bResult = pSetting->Import();
	}

	return bResult;
}


//						=====================
bool					Command::InMasterMode() const
//						=====================
{
	bool bResult = false;

	// Determine if the MasterSlave setting specifies that the Engine is
	// to run in Master mode.
	if ( m_pSetting->Get( "MASTERSLAVE","Mode" ) == "Master" )
	{
		bResult = true;
	}

	return bResult;
}


//						=======================
void					Command::WriteLogHeader
//						=======================
(
	const string&		strCluster,
	const string&		strReport,
	const string&		strIniFile
)
{
	// Log: engine start, copyright, engine version, engine build number,
	// and license information.
	m_pLog->EngineStart( strCluster, strReport, strIniFile );
	m_pLog->Copyright( m_strCopyright );
	m_pLog->EngineVersion( m_strVersion );
	m_pLog->EngineBuildNumber( m_strBuild );
	//m_pLog->License( m_strCustomerName, m_strCompanyName, m_strLicenseNumber );
	
	char lpszComputer[255];
    DWORD dComputer = sizeof(lpszComputer);
	GetComputerName(lpszComputer, &dComputer);
	m_pLog->ComputerName(lpszComputer);
	m_pSetting->Set("SYSTEM", "ComputerName", lpszComputer);

	char lpszUsername[255];
	DWORD dUsername = sizeof(lpszUsername);
	GetUserName(lpszUsername, &dUsername);
	m_pLog->UserName(lpszUsername);
	m_pSetting->Set("SYSTEM", "UserName", lpszUsername);
	// Get all ini-file settings, and log these.
	vector<pair<pair<string, string>, string> > vprSettings;
	vprSettings = m_pSetting->GetAllSettings();
	vector<pair<pair<string, string>, string> >::size_type nSet;
	for ( nSet = 0; nSet < vprSettings.size(); nSet++ )
	{
		string strSection = vprSettings[nSet].first.first;
		string strKey	  = vprSettings[nSet].first.second;
		string strValue   = vprSettings[nSet].second;
		m_pLog->IniFile( strSection, strKey, strValue );
	}

	// Get all user-defined action words, and log these.
	vector<pair<string, string> > vprActions;
	vprActions = m_pActionWord->GetAllOfType( ActionWordList::EXTERN );
	vector<pair<string, string> >::size_type nAct;
	for ( nAct = 0; nAct < vprActions.size(); nAct++ )
	{
		string strActionWord = vprActions[nAct].first;
		string strFunction   = vprActions[nAct].second;
		m_pLog->RegisterActionWord( strActionWord, strFunction );
	}

	// Get all user-defined header words, and log these.
	vprActions = m_pActionWord->GetAllOfType( ActionWordList::EXTERN_HEADER );
	for ( nAct = 0; nAct < vprActions.size(); nAct++ )
	{
		string strHeaderWord = vprActions[nAct].first;
		string strTag		 = vprActions[nAct].second;
		m_pLog->RegisterHeaderWord( strHeaderWord, strTag );
	}
}


//						========================
bool					Command::PerformArgCheck
//						========================
(
	const string&		strDescription,
	int					nIndex,
	const string&		strRecorded,
	Log::CHECKTYPE		nCheckType
)
{
	bool bResult = false;

	// Get the argument to check.
	string strArgument = GetArgument( nIndex );
	
	// Determine if the argument is to be snapped.
	string strSnapIdentifier;
	if ( m_pComposedInterpreter->InSnapVector( nIndex, strSnapIdentifier ) )
	{
		PerformSnap( nIndex, strSnapIdentifier, strRecorded );
		bResult = true;
	}
	else
	{
		// Determine if argument is not-empty command.
		if ( strArgument == m_pSetting->Get("SYSTEM", "NotEmptyPrefix") )
		{
			// Determine if recorded string is not empty.
			if ( !strRecorded.empty() )
			{
				bResult = true;
			}
		}
		// Otherwise, determine if argument is anything command.
		else if (strArgument == m_pSetting->Get("SYSTEM", "AnythingPrefix"))
		{
			// Result is always passed.
			bResult = true;
		}
		else
		{
			// Compare argument value with recorded string.
			bResult = m_pBasicNavigation->Compare( strRecorded, strArgument );
		}

		// Log the check
		m_pLog->Check( bResult, strDescription, strArgument, strRecorded, nCheckType, nIndex );
		m_pActionServer->ReportCheck( bResult );
	}

	return bResult;
}


//						====================
void					Command::PerformSnap
//						====================
(
	int					nArgument,
	const string&		strIdentifier,
	const string&		strValue
)
{
	string strSnapId = strIdentifier;

	// Determine if the snap identifier is empty.
	if ( strSnapId.empty() )
	{
		// Fill identifier with line and argument number.
		strSnapId = "(L:" + IntToStr( GetLineNumber() ) + ", A:" +
					IntToStr( nArgument ) + ")";
	}

	// Take as snap file section name the name of the cluster.
	string strSection = GetClusterFile();

	// add snap identifier with value to snap file
	m_pSnapSetting->Set( strSection, strSnapId, strValue);
	m_pSnapSetting->Export();		

	// Log the snap action; first determine the name of the snap-file.
	string strSnapFile = m_pSnapSetting->GetFileName();
	m_pLog->Snap( strSnapId, strValue, nArgument, strSnapFile );
}

///////////////////////////////////////////////////////////////////////////////