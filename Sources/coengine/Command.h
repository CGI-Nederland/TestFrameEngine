/*****************************************************************************
 * $Workfile: Command.h $
 * $Revision: 45 $
 * $Modtime: 10/23/01 11:41a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef COMMAND_H
#define COMMAND_H

// Includes
#include <string>
#include <vector>

using namespace std;

#include "Log.h"	// Include i.s.o. forward declaration because of used enum

// Forward declarations
class ActionServer;
class ActionWord;
class BasicNavigation;
class ComposedInterpreter;
class EngineSetting;
class GuiInterface;
class GUIThread;
class MasterCommand;
class NavigationInterface;
class ReportGenerator;
class SlaveCallBackHandler;
class SlaveList;
class Setting;
class TcpIpServer;
class UICallBackHandler;
class UIHandler;


////////////////////////////////////////////////////////////////////////////////
// class Command

class Command 
{
	// Construction and destruction
public:
	Command();						// Constructor

private:
	Command(const Command& right);	// Copy contructor
	Command& operator=(Command&);
	// Other constructors
public:
	~Command();						// Destructor

	// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNavigationInterface()
	//
	// description	: Gets a reference to the navigation interface
	//				  
	// parameters	: -.
	//
	// returns		: NavigationInterface*			
	///////////////////////////////////////////////////////////////////////////////
	NavigationInterface* GetNavigationInterface() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetGUInterface()
	//
	// description	: Gets a reference to the navigation interface
	//				  
	// parameters	: -.
	//
	// returns		: GUInterface*			
	///////////////////////////////////////////////////////////////////////////////
	GuiInterface* GetGUInterface() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: RegisterActionword
	//
	// description	: Registers an externally defined action word
	//				  	
	// parameters	: strActionWord				action word name
	//				  strActionWordFunction		associated action word function
	//
	// returns		: true		action word successfully registered
	//				  false		action word could not be registered
	///////////////////////////////////////////////////////////////////////////////
	bool RegisterActionWord(const string& strActionWord, const string& strActionWordFunction);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnregisterActionword
	//
	// description	: Unregisters an externally defined action word
	//				  
	// parameters	: strActionWord		action word name
	//
	// returns		: true		action word successfully unregistered
	//				  false		action word could not be unregistered
	///////////////////////////////////////////////////////////////////////////////
	bool UnregisterActionWord(const string& strActionWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: RegisterHeaderword
	//
	// description	: This function registers an externally defined header word.
	//				  
	// parameters	: strHeaderWord		name of header word
	//				  strTag			report tag belonging to this header word
	//
	// returns		: true		header word successfully registered
	//				  false		header word could not be registered
	///////////////////////////////////////////////////////////////////////////////
	bool RegisterHeaderWord(const string& strHeaderWord, const string& strTag);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateActionWordSynonym
	//
	// description	: Creates a synonym for an existing ActionWord.
	//				  The operation fails if the ActionWord does not exist
	//				  or when the synonym is already being used.
	//				  	
	// parameters	: strActionWord		action word name
	//				  strSynonym		synonym for action word name
	//
	// returns		: true		synonym successfully created
	//				  false		synonym could not be created
	///////////////////////////////////////////////////////////////////////////////
	bool CreateActionWordSynonym(const string& strActionWord, const string& strSynonym);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnregisterHeaderWord
	//
	// description	: Unregisters an externally defined header word.
	//				  
	// parameters	: strHeaderWord		header word name
	//
	// returns		: true		header word successfully unregistered
	//				  false		header word could not be unregistered
	///////////////////////////////////////////////////////////////////////////////
	bool UnregisterHeaderWord(const string& strHeaderWord);

	///////////////////////////////////////////////////////////////////////////////
	// function		: UnregisterAllActionWords
	//
	// description	: Unregisters all externally defined action words and 
	//					externally defined header words.
	//				  
	// parameters	: -
	//
	// returns		: number of unregistered action words
	///////////////////////////////////////////////////////////////////////////////
	int UnregisterAllActionWords();

	///////////////////////////////////////////////////////////////////////////////
	// function		: StartEngine
	//
	// description	: This function starts the engine processing a cluster.
	//				  	
	// parameters	: strClusterFileName	name of cluster file
	//				  strReportFileName		name of report file
	//				  strIniFile			name of ini file containing settings
	//
	// returns		: true		engine successfully started
	//				  false		engine could not be started
	///////////////////////////////////////////////////////////////////////////////
	bool StartEngine(const string& strClusterFileName, const string& strReportFileName, const string& strIniFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: StopEngine
	//
	// description	: This function stops the engine processing the cluster it's 
	//				  busy with and clears all information that was entered via
	//				  this cluster.
	//				  	
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void StopEngine();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GenerateReport
	//
	// description	: Generates a report for the last processed cluster.
	//				  	
	// parameters	: -
	//
	// returns		: true		Report successfully generated
	//				  false		Report could not be generated
	///////////////////////////////////////////////////////////////////////////////
	bool GenerateReport();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GenerateReportFromLog
	//
	// description	: Generates the report for the given log file using the
	//				  settings from the inifile.
	//				  	
	// parameters	: strLogFilename		Name of the logfile to process
	//				  strReportName			Name of the report file to create
	//				  strIniFile			Name of the inifile
	//
	// returns		: true					Report successfully generated
	//				  false					Report could not be generated
	///////////////////////////////////////////////////////////////////////////////
	bool GenerateReportFromLog(const string& strLogFilename, const string& strReportName, const string& strIniFilename);

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

	///////////////////////////////////////////////////////////////////////////////
	// function		: GotoNextSection()
	//
	// description	: This function processes all test lines until and including
	//					the first valid test line of the next section of the
	//					current cluster, or, if the current cluster is ended, the
	//					first valid line of the calling cluster.
	//				  
	// parameters	: -
	//
	// returns		: true		first valid test line of next section processed
	//				  false		no valid test line in next sections found; 
	//								end of main cluster
	///////////////////////////////////////////////////////////////////////////////
	bool GotoNextSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GotoNextScenario()
	//
	// description	: This function processes all test lines until and including
	//					the first valid test line of the next scenario of the
	//					current cluster, or, if the current cluster is ended, the
	//					first valid line of the calling cluster.
	//				  
	// parameters	: -
	//
	// returns		: true		first valid test line of next scenario processed
	//				  false		no valid test line in next scenario found; 
	//								end of main cluster
	///////////////////////////////////////////////////////////////////////////////
	bool GotoNextScenario();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GotoNextTestCase()
	//
	// description	: This function processes all test lines until and including
	//					the first valid test line of the next test case of the
	//					current cluster, or, if the current cluster is ended, the
	//					first valid line of the calling cluster.
	//				  
	// parameters	: -
	//
	// returns		: true		first valid test line of next test case processed
	//				  false		no valid test line in next test case found; 
	//								end of main cluster
	///////////////////////////////////////////////////////////////////////////////
	bool GotoNextTestCase();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWord
	//
	// description	: This function returns the current action word
	//				  	
	// parameters	: -
	//
	// returns		: string containing the current action word
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
	//				  specified index after the action from the current test line.
	//
	// parameters	: nIndex	parameter index
	//
	// returns		: specified parameter value
	///////////////////////////////////////////////////////////////////////////////
	string GetParameter( int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfArguments
	// description	: This function returns the number of argument from the current
	//				  test line.
	//
	// parameters	: -
	//
	// returns		: number of arguments
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfArguments();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfParameters
	// description	: This function returns the number of parameters of the
	//				  current action word.
	//
	// parameters	: -
	//
	// returns		: number of parameters
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCase()
	//
	// description	: This function returns the current test case of the current 
	//					cluster.
	//				  	
	// parameters	: -
	//
	// returns		: name of the current test case
	///////////////////////////////////////////////////////////////////////////////
	string GetTestCase();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTestCondition()
	//
	// description	: This function returns the current test condition of the current 
	//					cluster.
	//				  	
	// parameters	: -
	//
	// returns		: name of the current test condition
	///////////////////////////////////////////////////////////////////////////////
	string GetTestCondition();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSection()
	//
	// description	: This function returns the current section of the current 
	//					cluster.
	//				  	
	// parameters	: -
	//
	// returns		: name of the current section
	///////////////////////////////////////////////////////////////////////////////
	string GetSection();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetScenario()
	//
	// description	: This function returns the current scenario of the current 
	//					cluster.
	//				  	
	// parameters	: -
	//
	// returns		: name of the current scenario
	///////////////////////////////////////////////////////////////////////////////
	string GetScenario();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetClusterFile()
	//
	// description	: This function returns the file name of the current cluster.
	//				  	
	// parameters	: -
	//
	// returns		: file name of the current cluster
	///////////////////////////////////////////////////////////////////////////////
	string GetClusterFile();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLineNumber()
	//
	// description	: This function returns the number of the current test line.
	//				  	
	// parameters	: -
	//
	// returns		: number of the current test line
	///////////////////////////////////////////////////////////////////////////////
	int GetLineNumber();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumberOfErrors()
	//
	// description	: This function returns the number of errors found as of yet.
	//				  	
	// parameters	: -
	//
	// returns		: number of errors found as of yet
	///////////////////////////////////////////////////////////////////////////////
	int GetNumberOfErrors();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLatestError()
	//
	// description	: This function returns the latest error.
	//				  	
	// parameters	: -
	//
	// returns		: string containing the latest error
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
	// description	: This function returns the parameter description with the
	//				  specified index.
	//				  
	// parameters	: nIndex	parameter index
	//
	// returns		: specified parameter's description
	///////////////////////////////////////////////////////////////////////////////
	string GetParameterDescription( int nIndex );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCopyright
	//
	// description	: The function returns the string containing the copyright
	//				  information.
	//				  
	// parameters	: -
	//
	// returns		: string containing the copyright information
	///////////////////////////////////////////////////////////////////////////////
	const string& GetCopyright() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetVersion
	//
	// description	: The function returns the string containing the version of the
	//				  Engine.
	//				  
	// parameters	: -
	//
	// returns		: string containing the version of the Engine.
	///////////////////////////////////////////////////////////////////////////////
	const string& GetVersion() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetBuild
	//
	// description	: This function returns the string containing the build number
	//				  of the Engine.
	//				  
	// parameters	: -
	//
	// returns		: string containing the build number of the Engine.
	///////////////////////////////////////////////////////////////////////////////
	const string& GetBuild() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLogFile
	//
	// description	: This function returns the string containing the log file
	//				  of the Engine.
	//				  
	// parameters	: -
	//
	// returns		: string containing the log file of the Engine.
	///////////////////////////////////////////////////////////////////////////////
	const string& GetLogFile() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: ReportComment
	//
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
	//
	// description	: This function reports an error of a specified type. The 
	//					allowed codes are 0, 1, 2 and 3 which mean WARNING, ERROR, 
	//					CHECK and FATAL respectively.
	//				  	
	// parameters	: strMessage	text of error message
	//				  nErrorType	error type code
	//
	// returns		: true		error successfully sent to log
	//				  false		error could not be sent to log
	///////////////////////////////////////////////////////////////////////////////
	bool ReportError(const string& strMessage, int nErrorType);

	///////////////////////////////////////////////////////////////////////////////
 	// function		: ReportCheck
	//
	// description	: This function sends a result of a check to the log
	//				  	
	// parameters	: strDescription	description of reportcheck
	//				  strExpected		string containing expected value
	//				  strRecorded		string to be compared with expected value
	//				  nCheckResult		check result value
	//
	// returns		: true		check result successfully sent to log
	//				  false		check result could not be sent to log
	///////////////////////////////////////////////////////////////////////////////
	bool ReportCheck(const string& strDescription, const string& strExpected, const string& strRecorded, int nCheckResult);

	///////////////////////////////////////////////////////////////////////////////
	// function		: CheckString
	//
	// description	: This function checks if the comparison between two strings 
	//				  is considered passed or failed.
	//				  	
	// parameters	: strDescription	description of the check
	//				  strExpected		string containing expected value
	//				  strRecorded		string to be compared with expected value
	//
	// returns		: true		check is considered passed
	//				  false		check is considered failed
	///////////////////////////////////////////////////////////////////////////////
	bool CheckString(const string& strDescription, const string& strExpected, const string& strRecorded);

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
	// function		: KeepArgument(string strValue, int nIndex)
	//
	// description	: 
	//				  
	// parameters	: strValue
	//				  nIndex
	//
	// returns		: true		operation succesfull
	//				  false		operation failed
	///////////////////////////////////////////////////////////////////////////////
	bool KeepArgument( const string& strValue, int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: KeepParameter
	//
	// description	: 
	//				  
	// parameters	: strValue
	//				  nIndex
	//
	// returns		: true		operation succesfull
	//				  false		operation failed
	///////////////////////////////////////////////////////////////////////////////
	bool KeepParameter( const string& strValue, int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: DisplayMessage
	//
	// description	: This function displays a specified message on a GUI.
	//				  
	// parameters	: strMessage		message to be displayed
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void DisplayMessage(const string& strMessage);

	///////////////////////////////////////////////////////////////////////////////
	// Function		: ValidateComponentLicense
	//
	// Description	: This function checks if a component license is valid. If 
	//				  not, it writes an error message to error.log.
	//				  
	// Parameters	: strComponentName		Name of the component license to check
	//
	// Returns		: true		Component license is valid
	//				  false		Component license is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateComponentLicense(const string& strComponentName);

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
	//				  false		operation failed
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
	// description	: Returns the current status of the engine
	//				  	
	// parameters	: -
	//
	// returns		: integer.
	///////////////////////////////////////////////////////////////////////////////
	int Status();

	///////////////////////////////////////////////////////////////////////////////
	// function		: DateArgument(int nIndex)
	//
	// description	: TO BE REMOVED
	//				  	
	// parameters	: nIndex
	//
	// returns		: integer
	///////////////////////////////////////////////////////////////////////////////
	int DateArgument(int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: StopASynchronous()
	//
	// description	: ASynchronous stop
	//				  	
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void StopASynchronous();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Pause()
	//
	// description	: 
	//				  	
	// parameters	: -.
	//
	// returns		: integer
	///////////////////////////////////////////////////////////////////////////////
	int Pause();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Resume()
	//
	// description	: 
	//				  	
	// parameters	: -
	//
	// returns		: integer
	///////////////////////////////////////////////////////////////////////////////
	int Resume();

	///////////////////////////////////////////////////////////////////////////////
	// function		:	LogEngineReset()
	//
	// description	:	This function logs a reset of the engine.
	//				  	
	// parameters	:	-
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void LogEngineReset();

	// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// Function		: ValidateEngineLicense
	//
	// Description	: This function checks if the engine license is valid. If 
	//				  not, it writes an error message to error.log. It 
	//				  retrieves the location of the license file from the 
	//				  Engine settings object.
	//				  
	// Parameters	: pSetting	Pointer to a Engine settings object
	//
	// Returns		: true		Engine license is valid
	//				  false		Engine license is invalid
	///////////////////////////////////////////////////////////////////////////////
	//bool ValidateEngineLicense(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// Function		: GetLicenseFile
	//
	// Description	: This function retieves the location of the license key file 
	//				  from the given Engine settings object.
	//				  
	// Parameters	: pSetting	Pointer to a Engine settings object
	//
	// Returns		: true		Engine license is valid
	//				  false		Engine license is invalid
	///////////////////////////////////////////////////////////////////////////////
	string GetLicenseFile(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// Function		: ReadKeepFile
	//
	// Description	: This function read the variables form the keep file.
	//				  
	// Parameters	: -
	//
	// Returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void ReadKeepFile();

	///////////////////////////////////////////////////////////////////////////////
	// Function		: WriteKeepFile
	//
	// Description	: This function write the variables to be kept :) to the the keep file.
	//				  
	// Parameters	: -
	//
	// Returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void WriteKeepFile();

	///////////////////////////////////////////////////////////////////////////////
	// Function		: CreateSnapFile
	//
	// Description	: This function creates the snap file.
	//				  
	// Parameters	: -
	//
	// Returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void ReadSnapFile();

	///////////////////////////////////////////////////////////////////////////////
	// Function		: InitialiseGUI
	//
	// Description	: This function initialises the GUI with the settings from the
	//				  engine ini file.
	//				  
	// Parameters	: -
	//
	// Returns		: -		
	///////////////////////////////////////////////////////////////////////////////
	void InitialiseGUI();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: FinishProcessing
	//
	// description	: Finishes processing clusters
	//				  
	// parameters	: -
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void FinishProcessing();

	///////////////////////////////////////////////////////////////////////////////
	// function		: LaunchGUI
	//
	// description	: Launches a local GUI
	//				  
	// parameters	: -
	//
	// returns		: true			successful
	//				  false			otherwise
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool LaunchGUI();

	///////////////////////////////////////////////////////////////////////////////
	// function		: UpdateIniFile
	//
	// description	: This function updates several engine settings in the engine
	//				  ini file: file names of the cluster and the report, and name,
	//				  company and serial number from the license.
	//				  
	// parameters	: strClusterFileName	cluster file to update
	//				  strReportFileName		report file to update
	//
	// returns		: -
	///////////////////////////////////////////////////////////////////////////////
	void UpdateIniFile(const string& strClusterFile, const string& strReportFile);

	///////////////////////////////////////////////////////////////////////////////
	// function		: RegisterBuiltInActionWords()
	//
	// description	: Registers all built in actionwords.
	//				  
	// parameters	: -
	//
	// returns		: -			
	///////////////////////////////////////////////////////////////////////////////
	void RegisterBuiltInActionWords();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFileName(const string& strFileName)
	//
	// description	: Searches for a filesystem separator token and uses this token
	//				  to retrieve the filename, when no token is found the value of
	//				  the parameter "strFileName" is returned.
	//
	// parameters	: strFileName	location and name of file
	//
	// returns		: string		name of file	
	///////////////////////////////////////////////////////////////////////////////
	string GetFileName(const string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFilePath(const string& strFileName)
	//
	// description	: Searches for a filesystem separator token and uses this token
	//				  to retrieve the filepath, when no token is found an empty
	//				  string is returned.
	//				  
	// parameters	: strFileName	location and name of file
	//
	// returns		: string		location of file			
	///////////////////////////////////////////////////////////////////////////////
	string GetFilePath(const string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: InitialiseSettings
	//
	// description	: Reads the settings from the given inifile.
	//				  
	// parameters	: pSetting			pointer to a setting object
	//				  strIniFilename	location and name of file
	//
	// returns		: true				Settings successfully initialised
	//				  false				Inifile could not be read
	///////////////////////////////////////////////////////////////////////////////
	bool InitialiseSettings(EngineSetting* pSetting, const string& strIniFilename);

	///////////////////////////////////////////////////////////////////////////////
	// function		: InMasterMode
	//
	// description	: This function states whether or not the Engine runs in Master
	//				  mode.
	//				  
	// parameters	: -
	//
	// returns		: true		Engine in Master mode
	//				  false		Engine in Standalone mode
	///////////////////////////////////////////////////////////////////////////////
	bool InMasterMode() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		:	WriteLogHeader
	//
	// description	:	This function writes the log header.
	//				  
	// parameters	:	strCluster		cluster passed to tfe_StartEngine
	//					strReport		report passed to tfe_StartEngine
	//					strIniFile		ini file passed to tfe_StartEngine
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void WriteLogHeader( const string& strCluster, const string& strReport,
						 const string& strIniFile );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	PerformArgCheck
	//
	// description	:	This function perform a check on an argument value.
	//				  
	// parameters	:	strDescription		description of the check
	//					nIndex				argument index
	//					strRecorded			recorded value to check with
	//					nCheckType			check type (either CHECK_ARGUMENT or
	//										CHECK_PARAMETER).
	//
	// returns		:	true	passed check or snap
	//					false	failed check
	///////////////////////////////////////////////////////////////////////////////
	bool PerformArgCheck( const string& strDescription, int nIndex, 
						  const string& strRecorded, Log::CHECKTYPE nCheckType );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	PerformSnap
	//
	// description	:	This function performs a snap action.
	//				  
	// parameters	:	nArgument			index of argument with snap command
	//					strIdentifier		snap identifier
	//					strValue			value to snap
	//
	// returns		:	-
	///////////////////////////////////////////////////////////////////////////////
	void PerformSnap( int nArgument, const string& strIdentifier,
					  const string& strValue );

	// Class constants
public:

	// Member variables
private:
	ActionServer*			m_pActionServer;			// Association to action server
	ActionWord*				m_pActionWord;				// Association to actionword
	BasicNavigation*		m_pBasicNavigation;			// Association to basic navigation
	ComposedInterpreter*	m_pComposedInterpreter;		// Association to composed interpreter
	GuiInterface*			m_pGuiInterface;			// Association to graphical user interface
	MasterCommand*			m_pMasterCommand;			// Association to master command
	NavigationInterface*	m_pNavigationInterface;		// Association to navigation interface
	ReportGenerator*		m_pReportGenerator;			// Association to report generator
	EngineSetting*			m_pSetting;					// Association to engine setting
	Setting*				m_pSnapSetting;				// Association to snap setting
	Setting*				m_pKeepSetting;				// Association to keep setting
	SlaveCallBackHandler*	m_pSlaveCallbackHandler;	// Association to slave callback handler
	SlaveList*				m_pSlaveList;				// Association to slave list
	TcpIpServer*			m_pMasterServer;			// Association to master server
	TcpIpServer*			m_pUIServer;				// Association to user interface server
	UICallBackHandler*		m_pUIcallbackHandler;		// Association to user interface callback
	UIHandler*				m_pUIHandler;				// Association to user interface handler
	GUIThread*				m_pGUIThread;				// Association to GUI thread handler
	Log*					m_pLog;

	bool					m_bStop;					// Stop flag
	bool					m_bPause;					// Pause flag				

	string					m_strLogFileName;			// Log file name
	string					m_strVersion;				// Version string
	string					m_strBuild;					// Build number string
	string					m_strCopyright;				// Copyright string

	string					m_strCustomerName;			// Customer name (license)
	string					m_strCompanyName;			// Company name (license)
	string					m_strLicenseNumber;			// License number (license)
};

////////////////////////////////////////////////////////////////////////////////

#endif // !COMMAND_H