/*****************************************************************************
 * $Workfile: $
 * $Revision: $
 * $Modtime: $
 * $Author: $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000-2013 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


package TestFrame;

/**
 * Java interface for TestFrame Engine 6.0. This java interface uses the 
 * Java Native Interface (JNI) of JDK 1.6 for the communication between the Java 
 * navigation code and the Engine C++ code. JNI is currently available for 
 * both the Windows and the Solaris platform, so this approach should work 
 * for both platforms.
 *
 * @author	<a href=mailto:Engine5@logicacmg.nl>Engine 5 Team</a>
 * @version	$Revision: $ $Modtime: $
 */
public class Engine
{
	/**
	 * Create an Engine. The Engine DLL (Windows) or shared library (Solaris) is
	 * loaded in this static initialiser before the class is used the first time.
	 */
	static
	{
		// Load the system library with the Java Native Interface code that 
		// interfaces with the C++ engine.
		System.loadLibrary("JavaEngine");
	}

	///////////////////////////////////////////////////////////////////////////////
	//  ENGINE CONSTRUCTION AND DESTRUCTION UNIX USE ONLY

	/** Constructs the engine (UNIX ONLY!).	*/
	//public native static void CreateEngine();

	/** Destructs the engine (UNIX ONLY!).	*/
	//public native static void DeleteEngine();

	///////////////////////////////////////////////////////////////////////////////
	//	ACTION WORD REGISTRATION

	/** Registers an action word with its associated function.
	 * @param	pszActionWord				Name of action word.
	 *			pszActionWordFunction		Name of associated function.
	 * @return	1							Action word successfully registered.
	 *			0							Action word could not be registered.
	 */
	public native static int RegisterActionWord(String strActionWord, String strActionWordFunction);

	/** Register a specific type of action word, a header word. 
	 * @param	strHeaderWord		Name of header word.
	 * @param	strReportTag		Tag to be placed in the report.
	 * @return	1					Header word successfully registered
	 * 			0					Header word could not be registered
	 */
	public native static int RegisterHeaderWord(String strHeaderWord, String strReportTag);

	/** Create a synonym for an action word.
	 * @param	strActionWord		Name of action word
	 * @param	strSynonym			Name of synonym
	 * @return	1					Synonym successfully created
	 *		 	0					Synonym could not be created
	 */
	public native static int CreateActionWordSynonym(String strActionWord, String strSynonym);
	
	/** Unregister an action word.
	 * @param	strActionWord		Name of action word
	 * @return	1					Action word successfully unregistered
	 *		 	0					Action word could not be unregistered
	 */
	public native static int UnregisterActionWord(String strActionWord);

	/** Unregisters a previously registered header word.
	 * @param	strHeaderWord		Name of header word
	 * @return	1					Header word successfully unregistered
	 *		 	0					Header word could not be unregistered
	 */
	public native static int UnRegisterHeaderWord(String strHeaderWord);

	/** Unregister all extern action words.
	 * @return	1					Action words successfully unregistered
	 *		 	0					Action words could not be unregistered
	 */
	public native static int UnregisterAllActionWords();

	///////////////////////////////////////////////////////////////////////////////
	//	STATE CONTROL
	
	/** Start the engine processing a cluster.
	 * @param	strClusterFilename		Name and path of the cluster to process
	 * @param	strReportFilename		Name and path of the report to generate
	 * @param	strIniFile				Name and path of the inifile to use
	 * @return	1						Engine started successfully
	 *			0						Engine could not be started
	 */
	public native static int StartEngine(String strClusterFilename, String strReportFilename, String strIniFile);

	/** Stops the engine processing the cluster. Clears all 
	 * information that was entered via this cluster.
	 * @return	1						Engine stopped successfully
	 *			0						Engine could not be stopped
	 */
	public native static int StopEngine();
	
	///////////////////////////////////////////////////////////////////////////////
	//	REPORT GENERATING

	/** Generates the report for the last processed cluster.
	 * @return	1						Report successfully generated
	 *			0						Report could not be generated
	 */
	public native static int GenerateReport();

	/** Generates the report for the given log file.
	 * @return	1						Report successfully generated
	 *			0						Report could not be generated
	 */
	public native static int GenerateReportFromLog(String strLogFilename, String strReportFilename, String strIniFile);

	///////////////////////////////////////////////////////////////////////////////
	//	TEST FLOW
	
	/** Proces the next test line with a registered user defined action word.
	 * @return	1						Next valid line found
	 *			0						No next valid line found
	 */
	public native static int ProcessNextLine();

	///////////////////////////////////////////////////////////////////////////////
	//	RUN TIME INFORMATION
	
	/** Returns the name of the action word of the current test line.
	 *  @return				Name of the action word of the current test line
	 */
	public native static String GetActionWord();

	/**	Return the name of the action word function associated with the 
	 * action word of the current test line.
	 * @return 				Name of the action word function of the current test line
	 */
	public native static String GetActionWordFunction();

	/** Returns the argument with the specified index from the current test 
	 * line's argument list.
	 * @param	nIndex		Index of argument list
	 * @return 				Specified argument from the current test line's
	 *						argument list.
	 */
	public native static String GetArgument(int nIndex);
	
	/**	Returns the number of arguments from the current test line.
	 * @return				Number of arguments
	 */
	public native static int GetNumberOfArguments();

	/** Returns the value of the parameter with the specified index after the 
	 *  action word from the current test line.
	 * @param	nIndex		Index of parameter list
	 * @return 				Specified parameter from the current test line's
	 *						parameter list.
	 */
	public native static String GetParameter(int nIndex);
	
	/**	Returns the number of parameters after the action word from the current test line.
	 * @return				Number of paramters
	 */
	public native static int GetNumberOfParameters();

	/** Returns the current test case.
	 * @return 				Name of the current test case
	 */
	public native static String GetTestCase();

	/** Returns the description of the current test condition.
	 * @return 				Name of the current test condition
	 */
	public native static String GetTestCondition();	

	/** Returns the current section.
	 * @return				Name of the current section
	 */
	public native static String GetSection();

	/** Returns the current scenario.
	 * @return				Name of the current scenario
	 */
	public native static String GetScenario();

	/** Returns the current cluster file.
	 * @return				Current cluster file
	 */
	public native static String GetClusterFile();

	/** Returns the current line number.
	 * @return				Current line number
	 */
	public native static int GetLineNumber();

	/** Returns the number of errors found since the engine was started.
	 * @return				Number of errors found since the engine was started
	 */
	public native static int GetNumberOfErrors();

	/** Returns the text of the latest error.
	 * @return				Text of the latest error
	 */
	public native static String GetLatestError();

	/** Returns the description of the argument with the specified index.
	 * @param	nIndex		Index of argument description list
	 * @return				Specified argument description
	 */
	public native static String GetArgumentDescription(int nIndex);

	/** Returns the description of the paramter with the specified index after the action word.
	 * @param	nIndex		Index of parameter description list
	 * @return				Specified parameter description
	 */
	public native static String GetParameterDescription(int nIndex);

	/** Return the copyright information of the Engine.
	 * @return				Copyright information
	 */
	 public native static String GetCopyright();

	/** Return the version number of the Engine.
	 * @return				Version info	
	 */
	public native static String GetVersion();

	/** Return the build number of the Engine.
	 * @return				Build number	
	 */
	public native static String GetBuild();

	/** Return the current log file of the Engine.
	 * @return				Name and path of log file	
	 */
	public native static String GetLogFile();

	///////////////////////////////////////////////////////////////////////////////
	//	REPORTING
	
	/** Send a string to the log to be written in report as comment.
	 * @param	strComment	Text to be written in the report as comment
	 * @return	1			Text successfully written in log
	 *			0			Text could not be written in log
	 */
	public native static int ReportComment(String strComment);

	/** Sends a string to the log to be written in report as an error.
	 * @param	strErrorText	Text to be written in report as error
	 * @param	nErrorTypeCode	Error type code
	 * @return	1		Text successfully written in log
	 *		0		Text could not be written in log
	 * @see #TFE_WARNING
	 * @see #TFE_ERROR
	 * @see #TFE_CHECK
	 * @see #TFE_FATAL
	 */
	public native static int ReportError(String strErrorText, int nErrorTypeCode);
	
	/** Sends an integer as a result of a check to the log.
	 * @param	strDescription		Description of check
	 * @param	strExpected		Expected string
	 * @param	strRecorded		Recorded string
	 * @param	nCheckResult		Check result value
	 * @return	1			Check passed
	 *		0			Check failed
	 */
	public static native int ReportCheck(String strDescription, String strExpected, String strRecorded, int nCheckResult);
	
	/** Sends an integer as a result of a check to the log 
	 * default result is passed written to log.
	 * @param	strDescription		Description of check
	 * @param	strExpected		Expected string
	 * @param	strRecorded		Recorded string
	 * @return	1			Check passed
	 *		0			Check failed
	 */
	public static native int ReportCheck(String strDescription, String strExpected, String strRecorded);
		
	///////////////////////////////////////////////////////////////////////////////
	//	CHECKING

	/** Checks if the comparison between two strings is considered passed or failed.
	 * @param	strDescription		Description of check
	 * @param	strExpected			Expected string
	 * @param	strRecorded			Recorded string
	 * @return	1					Check passed
	 *			0					Check failed
	 */
	public static native int CheckString(String strDescription, String strExpected, String strRecorded);

	/** Checks if the comparison between a specified argument and a specified
	 	string is considered passed or failed. If the argument contains a command,
	 	this command is evaluated. In the case of a snap command, a snap operation is
	 	performed and the result will be passed; in the case of a not-empty command,
	 	the result will be passed if the specified	string is not empty. As
	 	description of the check is taken the description of the argument; if this
	 	is empty, its index will be taken.

	 * @param	nIndex			Index of argument to be compared with string
	 * @param	strRecorded		String to be compared with argument
	 * @return	1		check passed
	 *			0		check failed
	 */
	public static native int CheckArgument(int nIndex, String strRecorded);
	
	/** Checks if the comparison between a specified parameter and a specified
	 	string is considered passed or failed. If the parameter contains a command,
	 	this command is evaluated. In the case of a snap command, a snap operation is
	 	performed and the result will be passed; in the case of a not-empty command,
	 	the result will be passed if the specified	string is not empty. As
	 	description of the check is taken the description of the parameter; if this
	 	is empty, its index will be taken.

	 * @param	nIndex			Index of parameter to be compared with string
	 * @param	strRecorded		String to be compared with parameter
	 * @return	1		check passed
	 *			0		check failed
	 */
	public static native int CheckParameter(int nIndex, String strRecorded);
	
	///////////////////////////////////////////////////////////////////////////////
	//						Cluster Variables

	/** Keeps the given value for future actions using the keep or snap function.
	 * @param	nIndex		Contains the position of the argument that holds
	 *						the keep/snap function (starting at 1)
	 * @param	strValue	Contains the value that needs to be kept/snapped
	 * @return	1			The keep/snap was successful
	 *			0			The keep snap failed
	 */
	public static native int KeepArgument(int nIndex, String strValue);

	/** Keeps the given value for future actions using the keep or snap function.
	 * @param	nIndex		Contains the position of the parameter that holds
	 *						the keep/snap function (starting at 1)
	 * @param	strValue	Contains the value that needs to be kept/snapped
	 * @return	1			The keep/snap was successful
	 *			0			The keep snap failed
	 */
	public static native int KeepParameter(int nIndex, String strValue);

	///////////////////////////////////////////////////////////////////////////////
	//	GUI
	
	/** Sends a string containig a message to be displayed on screen to a GUI-window.
	 * @param	strMessage	Message to be displayed
	 * @return	1			Message successfully displayed
	 *		  	0			Message could not be displayed
	 */
	public static native int DisplayMessage(String strMessage);
	
	////////////////////////////////////////////////////////////////////////////////
	// Constants
	
	/** Error type code: warning level
	 * @see #ReportError
	 */
	public static int TFE_WARNING = 0;
	
	/** Error type code: error level
	 * @see #ReportError
	 */
	public static int TFE_ERROR	=   1;

	/** Error type code: check level
	 * @see #ReportError
	 */
	public static int TFE_CHECK	=   2;

	/** Error type code: fatal level
	 * @see #ReportError
	 */
	public static int TFE_FATAL	=   3;
}
