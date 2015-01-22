/*****************************************************************************
 * $Workfile: NavigationInterface.cpp $
 * $Revision: 28 $
 * $Modtime: 10/23/01 11:09a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// Disable Visual C++ warning, function name in debugfile is truncated
#pragma warning(disable:4786)

#include "NavigationInterface.h"	// class definition

#include <string>

using namespace std;

#include "Command.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						========================================
						NavigationInterface::NavigationInterface()
//						========================================
{
}

//						========================================
						NavigationInterface::NavigationInterface
//						========================================
(
	Command*			pCommand		// pointer to Command object
)
{
	// Initializing pointer to Command object.
	m_pCommand = pCommand;
}

// Destructor
//						=========================================
						NavigationInterface::~NavigationInterface()
//						=========================================
{
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

///////////////////////////////////////////////////////////////////////////////////
//	ACTION WORD REGISTRATION
///////////////////////////////////////////////////////////////////////////////////

//						=======================================
bool					NavigationInterface::RegisterActionWord
//						=======================================
(
	const string&		strActionWord,			// name of action word
	const string&		strActionWordFunction	// name of action word function
)
{
	return m_pCommand->RegisterActionWord(strActionWord, strActionWordFunction);
}


//						=======================================
bool					NavigationInterface::RegisterHeaderWord 
//						=======================================
(
	const string&		strHeaderWord,	// name of header word
	const string&		strReportTag	// report tag
)
{
	return m_pCommand->RegisterHeaderWord(strHeaderWord, strReportTag);
}


//						============================================
bool					NavigationInterface::CreateActionWordSynonym
//						============================================
(
	const string&		strActionWord,	// name of action word
	const string&		strSynonym		// synonym for action word
)
{
	return m_pCommand->CreateActionWordSynonym(strActionWord, strSynonym);
}


//						=========================================
bool					NavigationInterface::UnregisterActionWord 
//						=========================================
(
	const string&		strActionWord	// name of action word
)
{
	return m_pCommand->UnregisterActionWord(strActionWord);
}


//						=========================================
bool					NavigationInterface::UnregisterHeaderWord
//						=========================================
(
	const string&		strHeaderWord	// name of header word
)
{
	return m_pCommand->UnregisterHeaderWord(strHeaderWord);
}


//						=============================================
int						NavigationInterface::UnregisterAllActionWords()
//						=============================================
{
	return m_pCommand->UnregisterAllActionWords();
}


///////////////////////////////////////////////////////////////////////////////////
//	STATE CONTROL
///////////////////////////////////////////////////////////////////////////////////

//						================================
bool  					NavigationInterface::StartEngine
//						================================
(
	const string& strClusterFileName,	// name of cluster file
	const string& strReportFileName,	// name of report file
	const string& strIniFile			// name of Engine ini file
)
{
	return m_pCommand->StartEngine(strClusterFileName, strReportFileName, strIniFile);
}


//						===============================
void					NavigationInterface::StopEngine()
//						===============================
{
	m_pCommand->StopEngine();
}


///////////////////////////////////////////////////////////////////////////////////
//	REPORT GENERATING
///////////////////////////////////////////////////////////////////////////////////

//						===================================
bool					NavigationInterface::GenerateReport()
//						===================================
{
	return m_pCommand->GenerateReport();
}

//						==========================================
bool					NavigationInterface::GenerateReportFromLog
//						==========================================
(
	const string&		strLogFilename,
	const string&		strReportName,
	const string&		strIniFile
 )
{
	return m_pCommand->GenerateReportFromLog(strLogFilename, strReportName, strIniFile);
}

///////////////////////////////////////////////////////////////////////////////////
//	TEST FLOW
///////////////////////////////////////////////////////////////////////////////////

//						====================================
bool					NavigationInterface::ProcessNextLine()
//						====================================
{
	return m_pCommand->ProcessNextLine();
}

///////////////////////////////////////////////////////////////////////////////////
//	RUN TIME INFORMATION
///////////////////////////////////////////////////////////////////////////////////

//						==================================
string					NavigationInterface::GetActionWord()
//						==================================
{
	return m_pCommand->GetActionWord();
}


//						==========================================
string					NavigationInterface::GetActionWordFunction
//						==========================================
(
	const string&		strActionWord
)
{
	// todo: rewrite m_pCommand->Action, so no parameter is needed
	return m_pCommand->GetActionWordFunction(strActionWord);
}


//						================================
string					NavigationInterface::GetArgument
//						================================
(
	int					nIndex		// index of argument in list
)
{
	return m_pCommand->GetArgument(nIndex);
}


//						=================================
string					NavigationInterface::GetParameter
//						=================================
(
	int					nIndex
)
{
	return m_pCommand->GetParameter( nIndex );
}


//						=========================================
int						NavigationInterface::GetNumberOfArguments()
//						=========================================
{
	return m_pCommand->GetNumberOfArguments();
}


//						==========================================
int						NavigationInterface::GetNumberOfParameters()
//						==========================================
{
	return m_pCommand->GetNumberOfParameters();
}


//						================================
string					NavigationInterface::GetTestCase()
//						================================
{
	return m_pCommand->GetTestCase();
}

//						=====================================
string					NavigationInterface::GetTestCondition()
//						=====================================
{
	return m_pCommand->GetTestCondition();
}


//						===============================
string					NavigationInterface::GetSection()
//						===============================
{
	return m_pCommand->GetSection();
}


//						================================
string					NavigationInterface::GetScenario()
//						================================
{
	return m_pCommand->GetScenario();
}


//						===================================
string					NavigationInterface::GetClusterFile()
//						===================================
{
	return m_pCommand->GetClusterFile();
}


//						==================================
int						NavigationInterface::GetLineNumber()
//						==================================
{
	return m_pCommand->GetLineNumber();
}


//						======================================
int						NavigationInterface::GetNumberOfErrors()
//						======================================
{
	return m_pCommand->GetNumberOfErrors();
}


//						===================================
string					NavigationInterface::GetLatestError()
//						===================================
{
	return m_pCommand->GetLatestError();
}


//						===========================================
string					NavigationInterface::GetArgumentDescription
//						===========================================
(
	int					nIndex	// index of argument description list
)
{
	return m_pCommand->GetArgumentDescription(nIndex);
}


//						============================================
string					NavigationInterface::GetParameterDescription
//						============================================
(
	int					nIndex
)
{
	return m_pCommand->GetParameterDescription( nIndex );
}


//						=================================
string					NavigationInterface::GetCopyright()
//						=================================
{
	return m_pCommand->GetCopyright();
}


//						===============================
string					NavigationInterface::GetVersion()
//						===============================
{
	return m_pCommand->GetVersion();
}


//						=============================
string					NavigationInterface::GetBuild()
//						=============================
{
	return m_pCommand->GetBuild();
}


//						===============================
string					NavigationInterface::GetLogFile()
//						===============================
{
	return m_pCommand->GetLogFile();
}

///////////////////////////////////////////////////////////////////////////////////
//	REPORTING
///////////////////////////////////////////////////////////////////////////////////

//						==================================
void					NavigationInterface::ReportComment
//						==================================
(
	const string&		strComment	// text to be written in report as comment
)
{
	m_pCommand->ReportComment(strComment);
}


//						================================
bool					NavigationInterface::ReportError
//						================================
(
	const string&		strMessage,		// error message to be reported
	int					nErrorType		// error type code
)
{
	return m_pCommand->ReportError(strMessage, nErrorType);
}

//						================================
bool					NavigationInterface::ReportCheck 
//						================================
(
	const string&		strDescription,	// description of check
	const string&		strExpected,	// string containing expected value
	const string&		strRecorded,	// string to be compared with expected value
	int					nCheckResult	// check result value
)
{
	return m_pCommand->ReportCheck(strDescription, strExpected, strRecorded, nCheckResult);
}

///////////////////////////////////////////////////////////////////////////////////
//	CHECKING
///////////////////////////////////////////////////////////////////////////////////

//						================================
bool					NavigationInterface::CheckString 
//						================================
(
	const string&		strDescription,	// description of check
	const string&		strExpected,	// string containing expected value
	const string&		strRecorded		// string to be compared with expected value
)
{
	return m_pCommand->CheckString(strDescription, strExpected, strRecorded);
}


//						==================================
bool					NavigationInterface::CheckArgument
//						==================================
(
	int					nArgumentIndex,	// index of argument to be compared with string
	const string&		strRecorded,	// string to be compared with argument
	bool				bHorizontal		// states whether or not a check is to be
										//	printed horizontally in the report
)
{
	return m_pCommand->CheckArgument(nArgumentIndex, strRecorded, bHorizontal);
}


//						===================================
bool					NavigationInterface::CheckParameter
//						===================================
(
	int					nParameterIndex,
	const string&		strRecorded
)
{
	return m_pCommand->CheckParameter( nParameterIndex, strRecorded );
}


///////////////////////////////////////////////////////////////////////////////////
//	CLUSTER VARIABLES
///////////////////////////////////////////////////////////////////////////////////

//						=================================
bool					NavigationInterface::KeepArgument 
//						=================================
(
	int					nIndex,			// index number
	const string&		strValue		// value to be kept
)
{
	return m_pCommand->KeepArgument(strValue, nIndex);
}


//						==================================
bool					NavigationInterface::KeepParameter
//						==================================
(
	int					nIndex,
	const string&		strValue
)
{
	return m_pCommand->KeepParameter( strValue, nIndex );
}

///////////////////////////////////////////////////////////////////////////////////
//	GUI
///////////////////////////////////////////////////////////////////////////////////

//						===================================
void					NavigationInterface::DisplayMessage 
//						===================================
(
	const string&		strMessage	// message to be displayed
)
{
	m_pCommand->DisplayMessage(strMessage);
}

///////////////////////////////////////////////////////////////////////////////////
//	LICENSE
///////////////////////////////////////////////////////////////////////////////////

//						=================================
bool					NavigationInterface::CheckLicense
//						=================================
(
	const string&		strComponentName
)
{
	return m_pCommand->ValidateComponentLicense(strComponentName);
}

///////////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS NEEDED TO SUPPORT OLD INTERFACE
///////////////////////////////////////////////////////////////////////////////////

//						================================
string					NavigationInterface::ReadSetting 
//						================================
(
	const string&		strIniFile,	// location and name of file
	const string&		strSection,	// section name
	const string&		strOption	// option name
)
{
	return m_pCommand->ReadSetting(strIniFile, strSection, strOption);
}


//						=================================
bool					NavigationInterface::WriteSetting 
//						=================================
(
	const string&		strIniFile,	// location and name of file
	const string&		strSection,	// section name
	const string&		strOption,	// option name
	const string&		strValue	// option value
)
{
	return m_pCommand->WriteSetting(strIniFile, strSection, strOption, strValue);
}


//						==============================
int						NavigationInterface::LineCount()
//						==============================
{
	return m_pCommand->LineCount();
}


//						===========================
int						NavigationInterface::Status()
//						===========================
{
	return m_pCommand->Status(); 
}


//						=================================
int						NavigationInterface::DateArgument
//						=================================
(
	int					nIndex
)
{
	return m_pCommand->DateArgument(nIndex);
}
