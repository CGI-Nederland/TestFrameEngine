/*****************************************************************************
 * $Workfile: NavigationInterface.h $
 * $Revision: 27 $
 * $Modtime: 10/23/01 10:46a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef NAVIGATIONINTERFACE_H
#define NAVIGATIONINTERFACE_H

#include <string>

using namespace std;

// Forward declarations
class Command;


class NavigationInterface
{
	// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of NavigationInterface
	///////////////////////////////////////////////////////////////////////////////
	NavigationInterface();

	///////////////////////////////////////////////////////////////////////////////
	// constructor of ActionServer
	//
	// parameters	: pCommand		pointer to Command
	///////////////////////////////////////////////////////////////////////////////
	explicit NavigationInterface(Command* pCommand);
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of ActionServer
	///////////////////////////////////////////////////////////////////////////////
	~NavigationInterface();

	// Attributes and operations
public:

///////////////////////////////////////////////////////////////////////////////////
//	ACTION WORD REGISTRATION
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: RegisterActionWord
	// description	: This function registers an action word with its associated
	//				  function.
	//
	// parameters	: strActionWord				name of action word
	//				  strActionWordFunction		name of associated function
	//
	// returns		: true		action word successfully registered
	//				  false		action word could not be registered
	///////////////////////////////////////////////////////////////////////////////
	bool RegisterActionWord(const string& strActionWord, const string& strActionWordFunction);

	///////////////////////////////////////////////////////////////////////////////
	// function		: RegisterHeaderWord
	// description	: This function registers a specific type of action word, 
	//				  a header word.
	//
	// parameters	: strHeaderWord		name of header word
	//				  strReportTag		tag to be placed in the report when the
	//									header word is encountered in a cluster
	//
	// returns		: true		header word successfully registered
	//				  false		header word could not be registered
	///////////////////////////////////////////////////////////////////////////////
	bool RegisterHeaderWord(const string& strHeaderWord, const string& strReportTag);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateActionWordSynonym
	// description	: This function creates a synonym for an action word.
	//
	// parameters	: strActionWord		name of action word
	//				  strSynonym		name of synonym
	//
	// returns		: true		synonym successfully created
	//				  false		synonym could not be created
	///////////////////////////////////////////////////////////////////////////////
	bool CreateActionWordSynonym(const string& strActionWord, const string& strSynonym);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnregisterActionWord
	// description	: This function unregisters an action word.
	//
	// parameters	: strActionWord		name of action word
	//
	// returns		: true		action word successfully unregistered
	//				  false		action word could not be unregistered
	///////////////////////////////////////////////////////////////////////////////
	bool UnregisterActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnRegisterHeaderWord
	// description	: This function removes a previously registered header word from
	//				  the engine's list of registered action words.
	//
	// parameters	: strHeaderWord		name of header word
	//
	// returns		: true		header word successfully unregistered
	//				  false		header word could not be unregistered
	///////////////////////////////////////////////////////////////////////////////
	bool UnregisterHeaderWord(const string& strHeaderWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnregisterAllActionWords
	// description	: This function unregisters all extern action words.
	//
	// parameters	: -
	//
	// returns		: 1		action words successfully unregistered
	//				  0		action words could not be unregistered
	///////////////////////////////////////////////////////////////////////////////
	int UnregisterAllActionWords();

///////////////////////////////////////////////////////////////////////////////////
//	STATE CONTROL
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: StartEngine
	// description	: This function starts the engine processing a cluster.
	//
	// parameters	: strClusterFilename	name of cluster file
	//				  strReportFilename		name of report file
	//				  strIniFile			name of Engine ini file
	//
	// returns		: true		engine successfully started
	//				  false		engine could not be started
	///////////////////////////////////////////////////////////////////////////////
	bool StartEngine(const string& strClusterFileName, const string& strReportFileName, const string& strIniFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: StopEngine
	// description	: This function stops the engine processing the cluster it's 
	//				  busy with and clears all information that was entered via
	//				  this cluster.
	//
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void StopEngine();

///////////////////////////////////////////////////////////////////////////////////
//	REPORT GENERATING
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: GenerateReport
	// description	: This function generates the report for the last processed 
	//				  cluster.
	//
	// parameters	: -
	//
	// returns		: true				Report successfully generated
	//				  false				Report could not be generated
	///////////////////////////////////////////////////////////////////////////////
	bool GenerateReport();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GenerateReportFromLog
	// description	: This function generates the report for the given log file
	//				  using the settings from the inifile
	//
	// parameters	: strLogFileName	Name of the logfile to process
	//				  strReportName		Name of the report
	//				  strIniFile		Name of the inifile
	//
	// returns		: true				Report successfully generated
	//				  false				Report could not be generated
	///////////////////////////////////////////////////////////////////////////////
	bool GenerateReportFromLog(const string& strLogFilename, const string& strReportName, const string& strIniFile);


///////////////////////////////////////////////////////////////////////////////////
//	TEST FLOW
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: ProcessNextLine
	//
	// description	: This function processes all test lines until and including
	//				  the next test line with a externally defined action word.
	//				  
	// parameters	: -
	//
	// returns		: true		next valid test line processed
	//				  false		no next valid test line found; end of cluster
	///////////////////////////////////////////////////////////////////////////////
	bool ProcessNextLine();

///////////////////////////////////////////////////////////////////////////////////
//	RUN TIME INFORMATION
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWord
	// description	: This function returns the name of the action word of the 
	//				  current test line.
	//
	// parameters	: -
	//
	// returns		: name of the action word of the current test line
	///////////////////////////////////////////////////////////////////////////////
	string GetActionWord();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordFunction
	// description	: This function returns the name of the action word function 
	//				  associated with the action word of the current test line.
	//
	// parameters	: strActionWord		TODO: rewrite so parameter can be removed
	//
	// returns		: name of the action word function of the current test line
	///////////////////////////////////////////////////////////////////////////////
	string GetActionWordFunction(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgument
	// description	: This function returns the argument with the specified index 
	//				  from the current test line's argument list.
	//
	// parameters	: nIndex	index of argument list
	//
	// returns		: specified argument from the current test line's argument list
	///////////////////////////////////////////////////////////////////////////////
	string GetArgument(int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameter
	//
	// description	: This function returns the value of the parameter with the
	//				  specified index after the action word from the current test
	//				  line.
	//
	// parameters	: nIndex	parameter
	//
	// returns		: specified parameter's value
	///////////////////////////////////////////////////////////////////////////////
	string GetParameter( int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfArguments
	// description	: This function returns the number of arguments from the current
	//				  test line.
	//
	// parameters	: -
	//
	// returns		: number of arguments
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfArguments();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfParameters
	// description	: This function returns the number of parameters of the current
	//				  action word.
	//
	// parameters	: -
	//
	// returns		: number of parameters
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCase
	// description	: This function returns the current test case.
	//
	// parameters	: -
	//
	// returns		: name of the current test case
	///////////////////////////////////////////////////////////////////////////////
	string GetTestCase();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCondition
	// description	: This function returns the current test condition.
	//
	// parameters	: -
	//
	// returns		: name of the current test condition
	///////////////////////////////////////////////////////////////////////////////
	string GetTestCondition();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSection
	// description	: This function returns the current section.
	//
	// parameters	: -
	//
	// returns		: name of the current section
	///////////////////////////////////////////////////////////////////////////////
	string GetSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetScenario
	// description	: This function returns the current scenario.
	//
	// parameters	: -
	//
	// returns		: name of the current scenario
	///////////////////////////////////////////////////////////////////////////////
	string GetScenario();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetClusterFile
	// description	: This function returns the current cluster file.
	//
	// parameters	: -
	//
	// returns		: current cluster file
	///////////////////////////////////////////////////////////////////////////////
	string GetClusterFile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLineNumber
	// description	: This function returns the current line number.
	//
	// parameters	: -
	//
	// returns		: current line number
	///////////////////////////////////////////////////////////////////////////////
	int GetLineNumber();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfErrors
	// description	: This function returns the number of errors found since the 
	//				  engine was started.
	//
	// parameters	: -
	//
	// returns		: number of errors found as of yet
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfErrors();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLatestError
	// description	: This function returns the text of the latest error.
	//
	// parameters	: -
	//
	// returns		: text of the latest error
	///////////////////////////////////////////////////////////////////////////////
	string GetLatestError();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetArgumentDescription
	//
	// description	: This function returns the argument description with the
	//				  specified index from the last read argument description list.
	//				  
	// parameters	: nIndex	index of argument description list
	//
	// returns		: specified argument description
	///////////////////////////////////////////////////////////////////////////////
	string GetArgumentDescription(int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameterDescription
	//
	// description	: This function returns the decsription of the specified
	//				  parameter.
	//				  
	// parameters	: nIndex	parameter index
	//
	// returns		: specified parameter's description
	///////////////////////////////////////////////////////////////////////////////
	string GetParameterDescription( int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCopyright
	// description	: This function returns the copyright information.
	//
	// parameters	: -
	//
	// returns		: copyright information
	///////////////////////////////////////////////////////////////////////////////
	string GetCopyright();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetVersion
	// description	: This function returns the version.
	//
	// parameters	: -
	//
	// returns		: version string
	///////////////////////////////////////////////////////////////////////////////
	string GetVersion();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetBuild
	//
	// description	: This function returns the build number of the Engine.
	//
	// parameters	: -
	//
	// returns		: string containing the build number of the Engine
	///////////////////////////////////////////////////////////////////////////////
	string GetBuild();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLogFile
	// description	: This function returns the current log file.
	//
	// parameters	: -
	//
	// returns		: current log file
	///////////////////////////////////////////////////////////////////////////////
	string GetLogFile();

///////////////////////////////////////////////////////////////////////////////////
//	REPORTING
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReportComment
	// description	: This function sends a string to the log to be written in 
	//				  report as comment.
	//
	// parameters	: strComment	text to be written in report as comment
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void ReportComment(const string& strComment);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReportError
	// description	: This function sends a string to the log to be written in 
	//				  report as an error.
	//
	// parameters	: strMessage	TODO: change to strErrorText
	//								text to be written in report as error
	//				  nErrorType	TODO: change to nErrorTypeCode
	//								error type code
	//
	// returns		: true			text successfully written in log
	//				  false			text could not be written in log
	///////////////////////////////////////////////////////////////////////////////
	bool ReportError(const string& strMessage, int nErrorType);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReportCheck
	// description	: This function sends a result of a check to the log
	//
	// parameters	: pszDescription	description of reportcheck
	//				  strExpected		expected string
	//				  strRecorded		recorded string
	//				  nCheckResult		check result value
	//
	// returns		: true		check result successfully sent to log
	//				  false		check result could not be sent to log
	///////////////////////////////////////////////////////////////////////////////
	bool ReportCheck(const string& pszDescription, const string& strExpected, const string& strRecorded, int nCheckResult);
	
///////////////////////////////////////////////////////////////////////////////////
//	CHECKING
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckString
	// description	: This function checks if the comparison between two strings 
	//				  is considered passed or failed.
	//
	// parameters	: strCheckLabel		TODO: change to pszDescription
	//									description of check
	//				  strExpected		expected string
	//				  strRecorded		recorded string
	//
	// returns		: true				check passed
	//				  false				check failed
	///////////////////////////////////////////////////////////////////////////////
	bool CheckString(const string& strCheckLabel, const string& strExpected, const string& strRecorded);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckArgument
	//
	// description	: This function checks if the comparison between a specified
	//				  argument and a specified string is considered passed or
	//				  failed. If the argument contains a command, this command is
	//				  evaluated. In the case of a snap command, a snap operation is
	//				  performed and the result will be passed; in the case of a
	//				  not-empty command, the result will be passed if the specified
	//				  string is not empty. As description of the check is taken the
	//				  description of the argument; if this is empty, its index will
	//				  be taken.
	//				  	
	// parameters	: nArgumentIndex	index of argument to be compared with string
	//				  strRecorded		string to be compared with argument
	//				  bHorizontal		states whether or not a check is to be
	//									printed horizontally in the report
	//
	// returns		: true		check is considered passed
	//				  false		check is considered failed
	///////////////////////////////////////////////////////////////////////////////
	bool CheckArgument(int nArgumentIndex, const string& strRecorded, bool bHorizontal);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckParameter
	//
	// description	: This function is as CheckArgument, only the specified index
	//				  is that of a parameter instead of an argument; also, always
	//				  a vertical check is taken.
	//				  	
	// parameters	: nParameterIndex	index of parameter to be compared with string
	//				  strRecorded		string to be compared with argument
	//
	// returns		: true		check is considered passed
	//				  false		check is considered failed
	///////////////////////////////////////////////////////////////////////////////
	bool CheckParameter( int nParameterIndex, const string& strRecorded );

///////////////////////////////////////////////////////////////////////////////
//	CLUSTER VARIABLES
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: KeepArgument
	//
	// description	: This function sets the value of a cluster variable in a
	//				  specified argument of the current test line. 
	//
	// parameters	: nIndex	index of the argument containing the cluster
	//							variable in a keep command
	//				  pszValue	value to which the cluster variable is to be set
	//				
	// returns		: true		cluster variable successfully kept
	//				  false		cluster variable could not be kept
	///////////////////////////////////////////////////////////////////////////////
	bool KeepArgument( int nIndex, const string& strValue );

	///////////////////////////////////////////////////////////////////////////////
	// function		: KeepParameter
	//
	// description	: This function sets the value of a cluster variable in a
	//				  specified parameter of the current action word.
	//
	// parameters	: nIndex	index of the parameter containing the cluster
	//							variable in a keep command
	//				  pszValue	value to which the cluster variable is to be set
	//				
	// returns		: true		cluster variable successfully kept
	//				  false		cluster variable could not be kept
	///////////////////////////////////////////////////////////////////////////////
	bool KeepParameter( int nIndex, const string& strValue );

///////////////////////////////////////////////////////////////////////////////
//	GUI
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: DisplayMessage
	// description	: This function sends a string containig a message to be 
	//				  displayed on screen to a GUI-window.
	//
	// parameters	: strMessage	message to be displayed
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void DisplayMessage(const string& strMessage);

///////////////////////////////////////////////////////////////////////////////
//	LICENSE
///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckLicense
	// description	: This function checks if a valid license for the given 
	//				  component name is present in the license file.
	//
	// parameters	: strComponentName	Name of the component to check
	//
	// returns		: true		Valid component license present
	//				  false		Valid component license not present
	///////////////////////////////////////////////////////////////////////////////
	bool CheckLicense(const string& strComponentName);

///////////////////////////////////////////////////////////////////////////////////
//	FUNCTIONS NEEDED TO SUPPORT OLD INTERFACE
///////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReadSetting(const string& strIniFile, const string& strSection, const string& strOption)
	//
	// description	: Returns the value belonging to the specified option
	//				  in the specified section in the specified file.
	//
	// parameters	: strIniFile	location and name of file
	//				  strSection	section name
	//				  strOption		option name	
	//
	// returns		: string		option value
	///////////////////////////////////////////////////////////////////////////////
	string ReadSetting(const string& strIniFile, const string& strSection, const string& strOption);

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteSetting(const string& strIniFile, const string& strSection, const string& strOption, const string& strValue)
	//
	// description	: Adds or changes the value belonging to the specified option
	//				  in the specified section in the specified file.
	//				  	
	// parameters	: strIniFile	location and name of file
	//				  strSection	section name
	//				  strOption		option name
	//				  strValue		option value
	//
	// returns		: true		operation succesfull
	//				  false		an error occurred
	///////////////////////////////////////////////////////////////////////////////
	bool WriteSetting(const string& strIniFile, const string& strSection, const string& strOption, const string& strValue);

	///////////////////////////////////////////////////////////////////////////////
	// function		: LineCount()
	//
	// description	: 
	//				  	
	// parameters	: -
	//
	// returns		: integer
	///////////////////////////////////////////////////////////////////////////////
	int LineCount();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Status()
	//
	// description	: Returns the current status of the engine.
	//				  	
	// parameters	: -
	//
	// returns		: integer.
	///////////////////////////////////////////////////////////////////////////////
	int Status();

	///////////////////////////////////////////////////////////////////////////////
	// function		: DateArgument(int nIndex)
	//
	// description	: 
	//				  	
	// parameters	: nIndex
	//
	// returns		: integer
	///////////////////////////////////////////////////////////////////////////////
	int DateArgument(int nIndex);

	// Implementation
private:

	// Class constants
public:

	// Member variables
private:
	Command*	m_pCommand; // Pointer to Command object
};

////////////////////////////////////////////////////////////////////////////////

#endif // !NAVIGATIONINTERFACE_H