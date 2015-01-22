/*****************************************************************************
 * $Workfile: ActionServer.cpp $
 * $Revision: 58 $
 * $Modtime: 11/13/01 6:55p $
 * $Author: Lw, AH $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "ActionServer.h"			// Class definition
#include "ActionWord.h"
#include "ActionWordList.h"
#include "Cluster.h"
#include "ComposedInterpreter.h"
#include "Condition.h"
#include "Context.h"
#include "EngineSetting.h"
#include "ErrorList.h"
#include "IOFactory.h"
#include "IOInterface.h"
#include "Log.h"
#include "MasterCommand.h"
#include "Number.h"
#include "Setting.h"				// Needed for keep setting
#include "Slave.h"
#include "StrUtil.h"
#include "Template.h"
#include "UIHandler.h"

//using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor not implemented

// Other constructors
//						==========================
						ActionServer::ActionServer
//						==========================							
(
	ComposedInterpreter*	pInterpreter,	// pointer to ComposedInterpreter
	ActionWord*				pActionWord,	// pointer to ActionWord
	UIHandler*				pUIHandler,		// pointer to User interface handler
	Setting*				pKeepSetting,	// pointer to Setting object for keep-file
	MasterCommand*			pMasterCommand	// pointer to MasterCommand
)
{
	// Initialise members.
	m_pInterpreter		= pInterpreter;
	m_pActionWord		= pActionWord;
	m_pUIHandler		= pUIHandler;
	m_pKeepSetting		= pKeepSetting;
	m_pMasterCommand	= pMasterCommand;

	m_pErrorList		= new ErrorList();
	m_pTemplate			= new Template();
	m_pCondition		= new Condition( m_pErrorList );
	m_pLog				= Log::Instance();
	m_pSetting			= 0;
						
	m_bGood				= false;

	m_bReadNextLine		= false;

	m_strTemplateDir	= "";
	m_strClusterDir		= "";
	m_strReportDir		= "";
	m_strEngineVersion	= "";
	m_strEngineBuild	= "";
	m_strRedundantEscapeChars = "";

	m_nMainClusterLines	= -1;
	m_nChecksPassed		= 0;
	m_nChecksFailed		= 0;
	m_nErrors			= 0;
	m_strLatestError	= "";

	m_bMasterSlaveMode	= false;
	m_nSlaveCommunicationMode = Slave::SYNC;

	// Map the action word types on member functions.
	FillActionMap();
}


// Destructor
//						===========================
						ActionServer::~ActionServer()
//						===========================
{
	// Delete the elements of Cluster vector.
	vector<Cluster*>::size_type nElement;
	for ( nElement = 0; nElement < m_vpClusters.size(); nElement++ )
	{
		delete m_vpClusters[nElement];
	}

	// Delete the ErrorList, Template and Condition objects.
	delete m_pErrorList;
	delete m_pTemplate;
	delete m_pCondition;

	m_pErrorList=0;
	m_pTemplate=0;
	m_pCondition=0;
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						========================
void					ActionServer::Initialise
//						========================
(
	EngineSetting*		pSetting
)
{
	// Set the validity of the ActionServer explicitly to false.
	m_bGood = false;

	// Set the pointer to the Setting object as a member.
	m_pSetting = pSetting;
	
	// Determine if the Setting pointer is not the null pointer.
	if ( pSetting != 0 )
	{
		// Determine the cluster directory as specified in the settings,
		// and set the corresponding member to this value.
		m_strClusterDir = m_pSetting->Get( "CLUSTER", "Path" );

		// Determine the name of the main cluster as stored in the Setting
		// object; then determine its full name, including path.
		string strCluster = m_pSetting->Get( "CLUSTER", "FileName" );
		strCluster = NameClusterFile( strCluster );

		// Create a Cluster object for the main cluster.
		Cluster* pCluster = new Cluster( strCluster, m_pInterpreter, m_pSetting, Cluster::TYPE_CLUSTER );

		// Determine if the main cluster could be opened.
		if ( pCluster->Good() )
		{
			// Set the ActionServer's validity to true.
			m_bGood = true;

			// Determine the Master/Slave Mode as specified in the
			// settings, and the corresponding member accordingly.
			string strMasterSlaveMode = m_pSetting->Get( "MASTERSLAVE", "Mode" );
			if ( strMasterSlaveMode == "Master" )
			{
				m_bMasterSlaveMode = true;
			}

			// Set the language in the ErrorList object to the one
			// specified in the settings.
			string strLanguage = m_pSetting->Get( "SYSTEM", "Language" );
			m_pErrorList->SetLanguage( strLanguage );

			// Set the other members whose values come from the
			// Setting object.
			m_strTemplateDir		  = m_pSetting->Get( "TEMPLATE", "Path" );
			m_strReportDir			  = m_pSetting->Get( "REPORT", "Path" );
			m_strRedundantEscapeChars = m_pSetting->Get( "SYSTEM", "RedundantEscapeChars" );
			m_strEngineVersion		  = m_pSetting->Get( "SYSTEM", "EngineVersion" );
			m_strEngineBuild		  = m_pSetting->Get( "SYSTEM", "EngineBuild" );

			// Determine report for main cluster.
			string strReport = m_pSetting->Get( "REPORT", "FileName" );
			strReport = NameReportFile( strReport );

			// Log the beginning of the main cluster.
			m_pLog->ClusterBegin( strCluster, strReport );

			// Place the main cluster in the vector of open clusters.
			m_vpClusters.push_back( pCluster );

			// Determine the number of lines in the main cluster, and
			// store this value in the corresponding member.
			m_nMainClusterLines = pCluster->GetTotalLine();

			// Get the main cluster's Context, and place it in the
			// Interpreter.
			m_pInterpreter->SetContext( pCluster->GetContext() );

			// Send to the Engine Message Centre the current number of
			// errors, number of checks, and cluster name.
			m_pUIHandler->ShowErrors( m_strLatestError, m_nErrors );
			m_pUIHandler->ShowChecks( m_nChecksPassed, m_nChecksFailed );
			m_pUIHandler->ShowCluster( strCluster );
		}
		else
		{
			delete pCluster;
			pCluster=0;
		}
	}
}


//						===================
void					ActionServer::Clear()
//						===================
{
	// Delete the elements of Cluster vector.
	vector<Cluster*>::size_type nElement;
	for ( nElement = 0; nElement < m_vpClusters.size(); nElement++ )
	{
		delete m_vpClusters[nElement];
	}

	// clear Cluster vector
	m_vpClusters.clear();

	// delete templates
	m_pTemplate->Clear();

	// reset pointer to Log and number of lines of main cluster
	m_pLog = 0;
	m_nMainClusterLines = -1;
}


//						==================
bool					ActionServer::Good() const
//						==================
{
	return m_bGood;
}


//						==================
bool					ActionServer::Next()
//						==================
{
	bool bResult = false;

	m_bReadNextLine = true;

	// check if no (main) cluster is added to the vector
	if (m_vpClusters.empty())
	{
		m_bReadNextLine = false;
	}

	// read a test line until no new line is required
	while ( m_bReadNextLine )
	{
		// read a test line from the current cluster and check if it succeeded
		if (m_vpClusters.back()->ReadLine())
		{
			// Send the progress of the main cluster to the Engine Message
			// Centre.
			m_pUIHandler->ShowProgress( m_vpClusters[0]->GetLineNumber(), m_nMainClusterLines );

			// Interpret all the arguments of the read cluster line.
			m_vpClusters.back()->InterpretExceptParameters();
			
			// Determine if the current line is to be processed by this Engine.
			if ( LineToBeProcessed() )
			{
				// Determine if the action word is valid.
				if ( m_vpClusters.back()->GetActionWordValidity() )
				{
					// Process the action of the current cluster line;
					// determine if it is an extern action word.
					if ( ProcessAction() )
					{
						// An extern action word was found; determine if there
						// were no errors found (by determining whether the next
						// line should not be read); if so, set the result to
						// true. N.B. the next is read if one or more errors
						// occured.
						if ( !m_bReadNextLine )
						{ bResult = true; }
					}
				}
				else
				{
					// Log the finding of a cluster line with an invalid
					// action word.
					LogInvalidActionWord();
				}
			}
			else
			{
				// Send the current cluster line to the specified Slave.
				SendLineToSlave();
			}
		}
		else
		{	
			// Handle the end of the cluster file, and determine if this file
			// is the main cluster.
			if ( !HandleEndOfCluster() )
			{
				// The ended cluster was the main cluster, which means that
				// there are no more lines left to read; return false.
				bResult = false;
				m_bReadNextLine = false;
			}
		}
	}

	return bResult;
}


//						===========================
string					ActionServer::GetActionWord() const
//						===========================
{
	return Argument( GetActionWordIndex() );
}


//						====================
string					ActionServer::Action() const
//						====================
{
	return m_vpClusters.back()->GetActionWordFunction();
}


//						======================
string					ActionServer::Argument
//						======================
(
	int					nArgument	// index of arguments
) const
{
	return m_vpClusters.back()->GetArgument( nArgument );
}


//						==========================
string					ActionServer::GetParameter
//						==========================
(
	int					nParameter
) const
{
	string strParameter = "";

	// Determine if the parameter index is greater than zero.
	if ( nParameter > 0 )
	{
		// Get the nParameter-th argument after the action word.
		strParameter = Argument( GetActionWordIndex() + nParameter );
	}

	return strParameter;
}


//						============================
string					ActionServer::GetClusterFile()
//						============================
{
	return m_vpClusters.back()->GetFileName();
}


//						==========================
long int				ActionServer::GetTotalLine() const
//						==========================
{
	return m_vpClusters.back()->GetTotalLine();
}


//						===========================
int						ActionServer::ArgumentCount() const
//						===========================
{
	return m_vpClusters.back()->ArgumentCount();
}


//						===================================
int						ActionServer::GetNumberOfParameters() const
//						===================================
{
	// Take as number of parameters the number of arguments minus the
	// argument containing the action word.
	int nParameters = ArgumentCount() - 1;

	// Determine if the Engine is in master-mode.
	if ( m_bMasterSlaveMode )
	{
		// Take one argument off for the Slave column.
		nParameters--;
	}

	// Determine if the number of parameters is negative.
	if ( nParameters < 0 )
	{
		// Set the number of parameters to its minimum: zero.
		nParameters = 0;
	}

	return nParameters;
}


//						========================
long int				ActionServer::LineNumber() const
//						========================
{
	return m_vpClusters.back()->GetLineNumber();
}


//						===============================
int						ActionServer::GetNumberOfErrors() const
//						===============================
{
	return m_nErrors;
}


//						============================
const string&			ActionServer::GetLatestError() const
//						============================
{
	return m_strLatestError;
}


//						========================
const string&			ActionServer::GetSection() const
//						========================
{
	return m_vpClusters.back()->GetSection();
}


//						=========================
const string&			ActionServer::GetScenario() const
//						=========================
{
	return m_vpClusters.back()->GetScenario();
}


//						=========================
const string&			ActionServer::GetTestCase() const
//						=========================
{
	return m_vpClusters.back()->GetTestCase();
}

//						==============================
const string&			ActionServer::GetTestCondition() const
//						==============================
{
	return m_vpClusters.back()->GetTestCondition();
}

//						=======================
void					ActionServer::WriteLine
//						=======================
(
	const string&		strLine		// line to append to active file
)
{
	m_vpClusters.back()->WriteLine(strLine);
}


//						==========================
bool					ActionServer::KeepArgument
//						==========================
(
	const string&		strValue,
	const int			nIndex
)
{
	bool bResult = false;	// result of KeepArgument

	string strKeepName;		// name of kept variable

	// check if the specified index contains a keep command
	if (m_pInterpreter->InKeepVector(nIndex, strKeepName))
	{
		// Add kept variable to the context with the specified value, and
		// with the type UNSPECIFIED.
		m_vpClusters.back()->GetContext()->Assign(strKeepName, strValue, Context::UNSPECIFIED);
		
		bResult = true;
	}
	else
	{
		// Convert index to string.
		string strIndex = IntToStr( nIndex );

		// Log Error
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_KEEP_INVALID_INDEX, strIndex, strValue ) );
	}

	return bResult;
}


//						====================================
string					ActionServer::GetArgumentDescription
//						====================================
(
	int nIndex
) const
{
	return GetParameterDescription( nIndex - GetActionWordIndex() );
}


//						=====================================
string					ActionServer::GetParameterDescription
//						=====================================
(
	int					nIndex
) const
{
	string strDescription = "";

	// Determine if the parameter index is greater than zero, but not greater
	// than the size of the parameter descriptions vector.
	if ( nIndex > 0 && nIndex <= m_vstrParDescr.size() )
	{
		// Get the nIndex-th parameter description; note that parameters are
		// numbered starting with 1, but the first vector element has index 0.
		strDescription = m_vstrParDescr[nIndex - 1];
	}

	return strDescription;
}


//						=======================================
int						ActionServer::GetNumberOfActiveClusters() const
//						=======================================
{
	return m_vpClusters.size();
}


//						=========================
void					ActionServer::ReportError
//						=========================
(
	const string&		strError
)
{
	// Update the text of the latest error and the number of errors.
	m_strLatestError = strError;
	m_nErrors++;

	// Send the error text to the UIHandler.
	m_pUIHandler->ShowErrors( strError, m_nErrors );
}


//						=========================
void					ActionServer::ReportCheck
//						=========================
(
	bool				bResult
)
{
	// Update the check counter depending on the specified result of the check.
	if ( bResult )
	{	m_nChecksPassed++;	}
	else
	{	m_nChecksFailed++;	}

	// Send the number of checks to the UIHandler.
	m_pUIHandler->ShowChecks( m_nChecksPassed, m_nChecksFailed );
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						===========================
void					ActionServer::FillActionMap()
//						===========================
{
	m_mActions[ActionWordList::EXTERN]			= &ActionServer::HandleExternActionWord;
	m_mActions[ActionWordList::EXTERN_HEADER]	= &ActionServer::HandleExternHeaderWord;
	m_mActions[ActionWordList::SUBCLUSTER]		= &ActionServer::HandleSubCluster;
	m_mActions[ActionWordList::TEMPLATE]		= &ActionServer::HandleTemplate;
	m_mActions[ActionWordList::DEFINE_TEMPLATE]	= &ActionServer::HandleDefineTemplate;
	m_mActions[ActionWordList::END_TEMPLATE]	= &ActionServer::HandleEndTemplate;
	m_mActions[ActionWordList::TEMPLATE_PROTO]	= &ActionServer::HandleTemplateProto;
	m_mActions[ActionWordList::DECLARE_TEMPLATE]= &ActionServer::HandleDeclareTemplate;
	m_mActions[ActionWordList::CLUSTER_AUTHOR]	= &ActionServer::HandleAuthor;
	m_mActions[ActionWordList::CLUSTER_DATE]	= &ActionServer::HandleDate;
	m_mActions[ActionWordList::CLUSTER_NAME]	= &ActionServer::HandleCluster;
	m_mActions[ActionWordList::CLUSTER_VERSION]	= &ActionServer::HandleVersion;
	m_mActions[ActionWordList::SHEET]			= &ActionServer::HandleSheet;
	m_mActions[ActionWordList::DOCUMENT]		= &ActionServer::HandleDocument;
	m_mActions[ActionWordList::SECTION]			= &ActionServer::HandleSection;
	m_mActions[ActionWordList::SCENARIO]		= &ActionServer::HandleScenario;
	m_mActions[ActionWordList::TEST_CASE]		= &ActionServer::HandleTestCase;
	m_mActions[ActionWordList::TEST_CONDITION]	= &ActionServer::HandleTestCondition;
	m_mActions[ActionWordList::EXPORT_TO_FILE]	= &ActionServer::HandleExportToFile;
	m_mActions[ActionWordList::IMPORT_FROM_FILE]= &ActionServer::HandleImportFromFile;
	m_mActions[ActionWordList::CONNECT_SLAVE]	= &ActionServer::HandleConnectSlave;
	m_mActions[ActionWordList::DISCONNECT_SLAVE]= &ActionServer::HandleDisconnectSlave;
	m_mActions[ActionWordList::IF]				= &ActionServer::HandleIf;
	m_mActions[ActionWordList::END_IF]			= &ActionServer::HandleEndIf;
	m_mActions[ActionWordList::ELSE]			= &ActionServer::HandleElse;
	m_mActions[ActionWordList::ELSE_IF]			= &ActionServer::HandleElseIf;
	m_mActions[ActionWordList::REPEAT]			= &ActionServer::HandleRepeat;
	m_mActions[ActionWordList::END_REPEAT]		= &ActionServer::HandleEndRepeat;
	m_mActions[ActionWordList::WHILE]			= &ActionServer::HandleWhile;
	m_mActions[ActionWordList::END_WHILE]		= &ActionServer::HandleEndWhile;
	m_mActions[ActionWordList::EMPTY]			= &ActionServer::HandleEmptyLine;
	m_mActions[ActionWordList::SET]				= &ActionServer::HandleSet;
}


//						===============================
bool					ActionServer::LineToBeProcessed() const
//						===============================
{
	bool bResult = true;

	// Determine if the Engine is in Master/Slave mode.
	if ( m_bMasterSlaveMode )
	{
		// Get the Slave name of the current cluster line.
		string strSlaveName = m_vpClusters.back()->GetSlaveName();

		// Check if slave name is not empty, since an empty slave name means
		// the cluster line is for the Master (which is this engine itself.)
		if ( !strSlaveName.empty() )
		{
			// The cluster line is to be sent to a Slave.
			bResult = false;
		}
	}

	return bResult;
}


//						===========================
bool					ActionServer::ProcessAction()
//						===========================
{
	bool bResult = false;

	// Determine the current action word type.
	int nAction = GetActionWordType();

	// Find this current action word type in the action map.
	ActionMap::iterator Iterator;
	Iterator = m_mActions.find( nAction );

	// Determine if the type was found in the map.
	if ( Iterator != m_mActions.end() )
	{
		// Call the ActionServer member function associated with the
		// current action word type.
		(this->*m_mActions[nAction])();

		// Only return 'true' if the type is that of a user-defined
		// action word.
		if ( nAction == ActionWordList::EXTERN )
		{
			bResult = true;
		}
	}
	else
	{
		// An invalid type was found for which no action is specified;
		// report an internal error.
		m_pLog->InternalError( __FILE__, __LINE__ );
	}

	return bResult;	
}


//						=============================
void					ActionServer::SendLineToSlave()
//						=============================
{
	// Get the Slave name.
	string strSlaveName = m_vpClusters.back()->GetSlaveName();

	// Determine if the Slave name is valid.
	if ( m_vpClusters.back()->GetMasterSlaveValidity() )
	{
		// Get the current cluster line with its Slave column removed.
		string strTestLine = GetTestLine();
		
		// Send the cluster line to the Slave.
		m_pMasterCommand->ProcessOnSlave( strSlaveName, strTestLine, m_nSlaveCommunicationMode );

		// Log sending the cluster line to the slave.
		m_pLog->SlaveLine( strSlaveName, StrToVector( strTestLine, "\t" ) );
	}
	else
	{
		// Log the finding of an invalid Slave name.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_CLUS_INVALID_SLAVE_NAME, strSlaveName ) );
	}
}


//						================================
bool					ActionServer::HandleEndOfCluster()
//						================================
{
	bool bResult = false;

	// Check if there are any flow of control structures still unclosed.
	if ( m_vpClusters.back()->GetControlFlow() != Cluster::UNDEFINED )
	{
		// Log the finding of an unclosed flow of control structure.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_UNCLOSED ) );
	}

	// Determine the type of the ended cluster, and log its end accordingly.
	switch ( m_vpClusters.back()->GetType() )
	{
		case Cluster::TYPE_CLUSTER:
		{
			// Log the end of the cluster.
			m_pLog->ClusterEnd( m_vpClusters.back()->GetFileName() );
			// export variables JU 20130415
			HandleExportAllToFile(); //is alleen
			//m_vpClusters.back()->GetContext()-> // alle variablen uit de huidige context uitlezen
			break;			
		}

		case Cluster::TYPE_TEMPLATE:
		{
			// Log the end of the template.
			m_pLog->TemplateEnd( m_vpClusters.back()->GetFileName() );
			break;			
		}

		default:
		{
			// Invalid cluster type; log an internal error.
			m_pLog->InternalError( __FILE__, __LINE__ );
			break;
		}
	}


	// Check if the current cluster is not the main cluster.
	if ( m_vpClusters.size() > 1 )
	{
		// Delete and remove the ended cluster, so focus returns to
		// calling cluster.
		delete m_vpClusters.back();
		m_vpClusters.pop_back();

		// Update the context.
		m_pInterpreter->SetContext(m_vpClusters.back()->GetContext());

		// Show the new cluster name in the Engine Message Centre.
		m_pUIHandler->ShowCluster(m_vpClusters.back()->GetFileName());

		// Set the result to true.
		bResult = true;
	}

	return bResult;
}


//						===========================
bool					ActionServer::InterpretLine()
//						===========================
{
	bool bResult = true;

	// Interpret all the arguments of the current cluster line.
	m_vpClusters.back()->Interpret();

	// Determine if errors were found in the arguments.
	if ( !m_vpClusters.back()->GetArgumentsValidity() )
	{
		// Set the result to false.
		bResult = false;

		// Get the vector with error messages.
		vector<string> vstrArgErrors = m_vpClusters.back()->GetArgumentErrors();

		// Log all these error messages.
		int nErr = 0;
		for ( nErr = 0; nErr < vstrArgErrors.size(); nErr++ )
		{
			WriteClusterError( vstrArgErrors[nErr] );
		}
	}

	return bResult;
}


//						==================================
void					ActionServer::LogInvalidActionWord()
//						==================================
{
	// Log the finding of an invalid action word.
	WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_CLUS_INVALID_ACTIONWORD, GetActionWord() ) );
}


//						===============================
int						ActionServer::GetActionWordType() const
//						===============================
{
	return m_vpClusters.back()->GetActionType();
}


//						===============================
void					ActionServer::WriteClusterError
//						===============================
(
	const string&		strError
)
{
	// Update the text of the latest error and the number of errors.
	m_strLatestError = strError;
	m_nErrors++;

	// Send the cluster error to the Log object, and to the UIHandler.
	m_pLog->ClusterError( strError );
	m_pUIHandler->ShowErrors( strError, m_nErrors );
}


//						=============================
string					ActionServer::NameClusterFile
//						=============================
(
	const string&		strClusterName		// name of the cluster
) const
{
	string strFileName = "";		// name of cluster file

	// check if cluster name is not empty
	if (!strClusterName.empty())
	{
		// check if path is not present in file name
		if ((strClusterName.find("\\") == string::npos) && 
			(strClusterName.find("/") == string::npos))
		{
			// add path to file name
			strFileName = m_strClusterDir + strClusterName;
		}
		else
		{
			strFileName = strClusterName;
		}
	}

	return strFileName;
}


//						============================
string					ActionServer::NameReportFile
//						============================
(
	const string&		strReport
) const
{
	string strFile;

	// Check if report name is not empty.
	if ( !strReport.empty() )
	{
		strFile = strReport;

		// Check if path is not present in file name.
		if ( strReport.find_first_of( "\\/" ) == string::npos )
		{
			// Add path to file name.
			strFile = m_strReportDir + strReport;
		}
	}

	return strFile;
}


//						==============================
string					ActionServer::NameTemplateFile
//						==============================
(
	const string&		strTemplateName,	// name of template
	bool				bAlreadyFile		// states if the specified name is already
											//	that of a file
) const
{
	string strTemplateFile;	// name of template file including path
	string strFileName;		// name of template file
	string strDirName;		// name of directory of this template file

	// check if specified name is already a file
	if ( bAlreadyFile )
	{
		// determine position of last slash in name
		string::size_type nLastSlashPos = strTemplateName.find_last_of( "\\/" );

		// check if path is present in template name
		if ( nLastSlashPos != string::npos )
		{
			// break up template name into file and dir name
			strFileName	= strTemplateName.substr( nLastSlashPos + 1 );
			strDirName	= strTemplateName.substr( 0, nLastSlashPos + 1 );
		}
		else
		{
			// take template name as file name and take as dir name the template dir
			strFileName	= strTemplateName;
			strDirName	= m_strTemplateDir;
		}
	}
	else
	{
		// take as dir name the template dir
		strDirName = m_strTemplateDir;

		// take as file name the template name with spaces and
		// dots replaced by underscores
		strFileName	= strTemplateName;
		string::size_type nCharPos;		// position of space or dot in file name
		
		// replace spaces and dots in template name by underscores
		while ( ( nCharPos = strFileName.find_first_of( " ." ) ) != string::npos )
		{
			strFileName.replace( nCharPos, 1, "_" );
		}
	}

	// check if the filename has no extension
	if ( strFileName.find( "." ) == string::npos )
	{
		// give file the extension: .tpt
		strFileName = strFileName + ".tpt";
	}

	// create file name and path
	strTemplateFile = strDirName + strFileName;

	return strTemplateFile;
}


//						================================
int						ActionServer::GetActionWordIndex() const
//						================================
{
	int nIndex = 1;		// index of action word in argument list of current test line

	// determine if Master/Slave mode is not stand alone
	if ( m_bMasterSlaveMode )
	{
		nIndex = 2;
	}
	
	return nIndex;
}


//						===========================
vector<string>			ActionServer::GetParameters() const
//						===========================
{
	return GetParameters( 1 );
}


//						===========================
vector<string>			ActionServer::GetParameters
//						===========================
(
	int					nStart 
) const
{
	vector<string> vstrParameters;
	int nMaxPar = ArgumentCount();
	int nPar = GetActionWordIndex() + nStart;
	for ( ; nPar <= nMaxPar; nPar++ )
	{
		vstrParameters.push_back( Argument( nPar ) );
	}

	return vstrParameters;
}


//						===============================
bool					ActionServer::CheckTemplateName
//						===============================
(
	const string&		strTemplateName		// name of template
)
{
	bool bResult = false;	// result of the function

	// check if template name is not empty
	if ( !strTemplateName.empty() )
	{
		int nType;		// type of action word

		// check if template name is already registered as action word (any type)
		if ( m_pActionWord->Find( strTemplateName, nType ) )
		{
			// check if name is used for a template
			if (nType == ActionWordList::TEMPLATE)
			{
				// overwrite template
				//@@ perhaps a warning
				bResult = true;
			}
			else
			{
				// already used for an action word with another type than template
				WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_REGISTERED, strTemplateName ) );
			}
		}
		else
		{
			// not registered, so valid for use as template name
			bResult = true;
		}
	}
	else
	{
		// no prototype specified
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NO_PROTOTYPE ) );
	}

	return bResult;
}


//							============================
bool						ActionServer::CreateTemplate
//							============================
(
	const string&			strTemplateName,		// name of template
	const vector<string>&	vstrTemplateParameters	// vector of template parameters
)
{
	bool bResult = false;	// result of creating template
	
	// determine name of template file
	string strTemplateFile = NameTemplateFile(strTemplateName, false);

	// open template file
	IOFactory Factory;
	IOInterface* pIOInterface = Factory.CreateIOInterface(strTemplateFile);
	pIOInterface->Open(IOInterface::IOWRITE);
	
	// place template protype at beginning of template file
	string strTemplatePrototype = string("template prototype") + string("\t")
								  + VectorToStr( GetParameters(), "\t" );

	// Prepend tab character for masterslave mode
	if (m_bMasterSlaveMode)
	{
		strTemplatePrototype = string("\t") + strTemplatePrototype;
	}

	WriteLineToTemplateFile(strTemplatePrototype, pIOInterface);

	// copy test lines from cluster to template file
	//	until end definition action word is found
	bool bEndOfTemplate = false;
	while (!bEndOfTemplate)
	{
		if (m_vpClusters.back()->ReadLine())
		{
			// Interpret this next line, but do not parse its parameters, since
			// only the action word type is needed, and the context must be
			// left alone.
			m_vpClusters.back()->InterpretExceptParameters();

			// check if end definition action word is found
			if (m_vpClusters.back()->GetActionType() == ActionWordList::END_TEMPLATE)
			{
				bResult			= true;
				bEndOfTemplate	= true;

				// Log the interpretation of 'end template'.
				m_pLog->EndDefineTemplate( strTemplateName );

				// Close the template file , and destroy IOInterface pointer.
				pIOInterface->Close();
				Factory.DestroyIOInterface( pIOInterface );

				// Log that the template has been successfully defined.
				m_pLog->TemplateDefined( strTemplateName, strTemplateFile );
			}
			else
			{
				// copy testline to template file
				WriteLineToTemplateFile(m_vpClusters.back()->GetTestLine(), pIOInterface); 
			}
		}
		else
		{
			// end of file encountered before end of template definition
			// invalid template
			WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NO_END_DEF, strTemplateName ) );
			bEndOfTemplate	= true;

			// Close template file 
			pIOInterface->Close();
			// Destroy IOInterface pointer
			Factory.DestroyIOInterface(pIOInterface);

			// remove template file		
			Factory.Remove(strTemplateFile); 
		}
	}

	// register template
	if (bResult)
	{
		// register template in ActionWord as action word of type TEMPLATE
		if (m_pActionWord->Find(strTemplateName))
		{
			// overwrite template
			m_pActionWord->Update(strTemplateName, ActionWordList::TEMPLATE, "", "Template");
		}
		else
		{
			// register as template
			m_pActionWord->Add(strTemplateName, ActionWordList::TEMPLATE, "", "Template");
		}

		// register template with its parameters in Template object
		m_pTemplate->Add(strTemplateName, vstrTemplateParameters, strTemplateFile);

		// Log the registration of the template.
		m_pLog->RegisterTemplate( strTemplateName, strTemplateFile );
	}

	return bResult;
}


//						==========================================
bool					ActionServer::GetTemplatePrototypeFromFile
//						==========================================
(
	const string&		strFileName,		// name of the file to check
	string&				strTemplateName,	// to be filled with the found template name
	vector<string>&		vstrParameters		// to be filled with the found template 
											//	parameters
)
{
	bool bResult = false;	// result of this function

	// create new cluster object associated with specified file.
	// last parameter specifies that no log object has to be created.
	Cluster* pCluster = new Cluster(strFileName, m_pInterpreter, m_pSetting, Cluster::TYPE_TEMPLATE, false);

	// Determine if the template file could be opened.
	if ( pCluster->Good() )
	{
		bool bFinishedWithFile = false;		// states if the file doesn't have to be searched
											//	through for a template prototype
		// read lines from file
		while (!bFinishedWithFile)
		{
			if (pCluster->ReadLine())
			{
				// Interpret this next line, but do not parse its parameters, since
				// only the action word type is needed, and the context must be
				// left alone.
				pCluster->InterpretExceptParameters();
				
				// check action word type
				switch (pCluster->GetActionType())
				{
					case ActionWordList::TEMPLATE_PROTO:
					{
						// Interpret all this test line's arguments.
						pCluster->Interpret();
						
						// template prototype found; get template name and parameters
						int nAWIndex = GetActionWordIndex();	// action word index
						strTemplateName = pCluster->GetArgument(nAWIndex + 1);

						string strParam;	// template parameter from prototype test line
						for (int i = nAWIndex + 2; (strParam = pCluster->GetArgument(i)) != ""; i++)
						{
							vstrParameters.push_back(strParam);
						}

						// Log the interpretation of 'template prototype'.
						m_pLog->TemplatePrototype( strTemplateName, vstrParameters );

						bFinishedWithFile	= true;
						bResult				= true;

						break;
					}

					case ActionWordList::EMPTY:
					{
						// read another line
						break;
					}

					default:
					{
						// action word that starts the file is no template prototype
						bFinishedWithFile = true;
						break;
					}
				}
			}
			else
			{
				// end of file encountered and no prototype found
				bFinishedWithFile = true;
			}
		}

		// Determine if an incorrect or no prototype was found in the specified
		// template file.
		if ( !bResult )
		{
			WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NO_PROTOTYPE_IN_FILE, strFileName ) );
		}
	}
	else
	{
		// Report an error that the specified template could not be opened.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NOT_OPEN, strFileName ) );
	}

	// delete cluster object
	delete pCluster;
	pCluster=0;

	return bResult;
}


//						=================================
bool					ActionServer::MaximumClustersOpen()
//						=================================
{
	bool bResult = true;

	// Check if the number of open clusters is less than the allowed maximum.
	if ( m_vpClusters.size() < MAXIMUMCLUSTERS )
	{
		bResult = false;
	}

	return bResult;
}


//						=========================
string					ActionServer::GetTestLine()
//						=========================
{
	// get test line from cluster
	string strTestLine = m_vpClusters.back()->GetTestLine();

	// remove slave part from test line
	if ( m_bMasterSlaveMode )
	{
		string::size_type nTabPos;	// position of the first tab
		///////// AH ////////
		nTabPos = strTestLine.find( "\t" );
		// check if there's a tab in the test line
		if ( nTabPos != string::npos )
		{
			// replace test line by substring of test line after first tab
			strTestLine = strTestLine.substr( nTabPos + 1 );
		}
		else
		{
			// no tab found, test line is a slave name only, remove slave name
			strTestLine = "";
		}
	}

	return strTestLine;
}


//						=======================================
vector<string>			ActionServer::GetUninterpretedArguments()
//						=======================================
{
	// Get the current cluster line; using tab ("\t") as delimiter,
	// split the cluster line into vector elements, and return this vector.
	return StrToVector( m_vpClusters.back()->GetTestLine(), "\t" );
}


//						========================================
vector<string>			ActionServer::GetUninterpretedParameters()
//						========================================
{
	// Get all uninterpreted arguments of the current cluster line.
	vector<string> vstrParameters = GetUninterpretedArguments();

	// Determine if the engine is in Master mode.
	if ( m_bMasterSlaveMode )
	{
		// Remove the first two arguments from the vector, since these are
		// the slave name and the action word.
		if ( vstrParameters.size() <= 2 || vstrParameters.empty() )
		{
			vstrParameters.clear();
		}
		else
		{
			vstrParameters.erase( vstrParameters.begin(), vstrParameters.begin() + 2 );
		}
	}
	else
	{
		// Remove only the first argument, since this is the action word.
		if ( !vstrParameters.empty() )
		{
			vstrParameters.erase( vstrParameters.begin() );
		}
	}

	return vstrParameters;
}


//						=====================================
bool					ActionServer::WriteLineToTemplateFile
//						=====================================
(
	const string&		strLineToWrite,		// line to write to template
	IOInterface*		pTemplateFile		// IOInterface pointer to template file
)
{
	bool bResult = false;

	// Add an 'end of line' to the line
	string strLine = strLineToWrite + "\n";

	// ecsape RE characters in line
	EscapeRECharactersInLine( strLine );

	// write line in template file
	bResult = pTemplateFile->Write( strLine ); 

	// Log writing the line to the template
	if ( bResult )
	{
		m_pLog->LineToTemplate( StrToVector( strLineToWrite, "\t" ) );
	}

	return bResult;
}


//						======================================
bool					ActionServer::EscapeRECharactersInLine
//						======================================
(
	string&				strLineToConvert		// line to be converted
)
{
	bool	bResult	= false;			// result of ConvertRECharactersInLine
	string	strLine	= strLineToConvert;	// copy of original line

	// check if line nor REchar string is empty
	if ( !strLine.empty() && !m_strRedundantEscapeChars.empty() )
	{
		string::size_type nStartPos = 0;	// position in line to start search for REC for
		string::size_type nRECPos;			// position of first found REC

		while ((nRECPos = strLine.find_first_of(m_strRedundantEscapeChars, nStartPos)) != string::npos)
		{
			string strREC = strLine.substr( nRECPos, 1 );	// RE character found

			// add same REC before found one
			strLine.insert( nRECPos, strREC );

			// update starting position
			nStartPos = nRECPos + 2;

			bResult = true;
		}
	}

	// add content of converted line to referenced parameter
	strLineToConvert = strLine;

	return bResult;
}


//						======================================
bool					ActionServer::HandleSelectionCondition()
//						======================================
{
	bool bResult = false;

	// Create a vector for the arguments of the condition.
	vector<string> vstrCondition = GetParameters();

	// Evaluate the condition, and determine if it is valid.
	if ( m_pCondition->Evaluate( vstrCondition ) )
	{
		// Determine the value of the condition.
		bool bCondition = m_pCondition->GetValue();

		// Log the evaluation of a condition in a selction statement; first
		// determine if it is an 'if'-test line.
		if ( GetActionWordType() == ActionWordList::IF )
		{
			m_pLog->If( vstrCondition, bCondition );
		}
		else
		{
			// If it's not an 'if-test line, it must be 'else if'.
			m_pLog->ElseIf( vstrCondition, bCondition );
		}

		// Determine if the condition's value is true.
		if ( bCondition )
		{
			// The condition is true; this means that the subsequent cluster
			// lines are to be processed.
			bResult = true;
		}
		else
		{
			// The condition is false; this means that the subsequent lines
			// must be skipped, until either an alternative ('else if ' or
			// 'else') or the end of the selection statement is encountered;
			// delagate this to the function HandleSelectionAlternative, and
			// return its result.
			bResult = HandleSelectionAlternative();
		}
	}
	else
	{
		// Report the error about an invalid condition, which the Condition
		// object found
		WriteClusterError( m_pCondition->GetError() );

		// Go to the end of the if-statement, and determine if thsi was found.
		if ( GotoEndOfStruct( ActionWordList::IF, ActionWordList::END_IF ) )
		{
			// Mark the end of the selection statement in the current
			// cluster object.
			m_vpClusters.back()->EndIfStatement();
		}
	}

	return bResult;
}


//						========================================
bool					ActionServer::HandleSelectionAlternative()
//						========================================
{
	bool bResult = false;

	// Read the next cluster lines, and skip them, until either an alternative
	// of the current selection statement is found, or its end.
	bool bReady = false;
	int  nIfs	= 0;
	while ( !bReady )
	{
		// Read the next cluster line, and determine if it's not the end
		// of the cluster.
		if ( m_vpClusters.back()->ReadLine() )
		{
			// Interpret this next line, but do not parse its parameters, since
			// only the action word type is needed, and the context must be
			// left alone.
			m_vpClusters.back()->InterpretExceptParameters();

			// Determine if the action type of the found line, and take action
			// upon it.
			switch ( m_vpClusters.back()->GetActionType() )
			{
				case ActionWordList::END_IF:
				{
					// An 'end if' action word, the end of a selection
					// statement, is found; determine if in the meanwhile no
					// other selection statements were started,
					if ( nIfs == 0 )
					{
						// Mark the end of the selection statement in the current
						// cluster object, and end the function.
						m_pLog->EndIf();
						m_vpClusters.back()->EndIfStatement();
						bResult = true;
						bReady  = true;
					}
					else
					{
						// Decrease the number of open selection statements.
						nIfs--;
						m_pLog->Skip( GetUninterpretedArguments() );
					}

					break;
				}

				case ActionWordList::ELSE_IF:
				{
					// An 'else if' action word, the start of an alternative
					// with a condition, is found; determine if in the
					// meanwhile no other selection statements were started.
					if ( nIfs == 0 )
					{
						// Interpret all the arguments of this test line.
						m_vpClusters.back()->Interpret();

						// Handle the rest of the selection statement, starting
						// with the condition of this 'else if'; delegate this,
						// and return the result.
						bResult = HandleSelectionCondition();
						bReady  = true;
					}
					else
					{
						m_pLog->Skip( GetUninterpretedArguments() );
					}

					break;
				}

				case ActionWordList::ELSE:
				{
					// An 'else' action word, the start of an alternative
					// without condition, is found; determine if in the
					// meanwhile no other selection statements were started.
					if ( nIfs == 0 )
					{
						// This alternative belongs to the current selection
						// statement; this means that the subsequent cluster
						// lines are to be processed. Log the occurence of
						// 'else', and end this function.
						m_pLog->Else();
						bResult = true;
						bReady  = true;
					}
					else
					{
						m_pLog->Skip( GetUninterpretedArguments() );
					}

					break;
				}

				case ActionWordList::IF:
				{
					// An 'if' action word, the start of a selection statement,
					// is found. Since we're handling a selection statement
					// presently, this means the start of a new one amongst
					// the lines which are the be skipped. Increment the number
					// of open if-statements.
					nIfs++;
					m_pLog->Skip( GetUninterpretedArguments() );
					break;
				}

				default:
				{
					// All other action types are to be skipped; read the next
					// line.
					m_pLog->Skip( GetUninterpretedArguments() );
					break;
				}
			}
		}
		else
		{
			// An end of cluster found instead of the specified end; set the
			// result to false;
			bReady  = true;
			bResult = false;
		}
	}

	return bResult;
}


//						=============================
bool					ActionServer::GotoEndOfStruct
//						=============================
(
	int					nBeginType,
	int					nEndType
)
{
	bool bResult = false;
	
	// Read the next lines, and skip them if they're not the specified
	// end type
	bool bReady   = false;
	int  nStructs = 0;
	while ( !bReady )
	{
		// Read the next cluster line, and determine if it's not the end
		// of the cluster.
		if ( m_vpClusters.back()->ReadLine() )
		{
			// Interpret this next line, but do not parse its parameters, since
			// only the action word type is needed, and the context must be
			// left alone.
			m_vpClusters.back()->InterpretExceptParameters();

			// Determine if the action type of the found line is the specified
			// end type.
			if ( GetActionWordType() == nEndType )
			{
				// Determine if the found end is the one we're searching for
				// by checking if the number of open structures at this point
				// in the cluster is zero.
				if ( nStructs == 0 )
				{
					bReady  = true;
					bResult = true;
				}
				else
				{
					// Decrease the number of open structures.
					nStructs--;
					m_pLog->Skip( GetUninterpretedArguments() );
				}
			}
			// Determine if the action type of the found line is the specified
			// begin type.
			else if ( GetActionWordType() == nBeginType )
			{
				// Increase the number of open structures.
				nStructs++;
				m_pLog->Skip( GetUninterpretedArguments() );
			}
			else
			{
				// Skip the lines with all other action types.
				m_pLog->Skip( GetUninterpretedArguments() );
			}
		}
		else
		{
			// An end of cluster found instead of the specified end; set the
			// result to false;
			bReady  = true;
			bResult = false;
		}
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Action processing functions

//						====================================
void					ActionServer::HandleExternActionWord()
//						====================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Log the interpretation of a user-defined action word.
		m_pLog->ActionWord( GetActionWord(), GetParameters() );

		// A valid user-defined action word is found; state that the control
		// can be returned to the user.
		m_bReadNextLine = false;

		// Send a message about the encounter of a new user-defined action word
		// to the Engine Message Centre.
		m_pUIHandler->ShowActionWord( GetTestLine() );
	}
}


//						====================================
void					ActionServer::HandleExternHeaderWord()
//						====================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Take as the report header tag the registered string which is stored
		// in the place of the action word function.
		string strTag = Action();

		// Take as value to be placed after the tag the value of the argument
		// after the action word.
		string strValue	= Argument( GetActionWordIndex() + 1 );

		// Log the interpretation of an extern header word.
		m_pLog->HeaderWord( GetActionWord(), strTag, strValue );
	}
}


//						==============================
void					ActionServer::HandleSubCluster()
//						==============================
{
	// Interpret the arguments of the test line, and determine if there
	// are errors.
	if ( !InterpretLine() )
	{
		// Error are found; return.
		return;
	}

	// Determine the file name of the subcluster and its report name,
	// both as specified in the test line.
	string strFileName = Argument( GetActionWordIndex() + 1 );
	string strReportName = Argument( GetActionWordIndex() + 2 );

	// Log the interpretation of 'do cluster'.
	m_pLog->DoCluster( strFileName, strReportName );

	// Check if the number of open clusters has not reached its allowed maximum.
	if ( !MaximumClustersOpen() )
	{
		// Determine the file name of the cluster to open.
		strFileName = NameClusterFile( strFileName );

		// Make a new cluster.
		Cluster* pCluster = new Cluster(strFileName, m_pInterpreter, m_pSetting, Cluster::TYPE_CLUSTER );

		// Determine if the cluster could be opened.
		if ( pCluster->Good() )
		{
			// Determine the file name of the cluster's report; note that if
			// the action word's second parameter is empty, this file name
			// is also empty.
			strReportName = NameReportFile( strReportName );
			
			// Log the beginning of the (sub)cluster.
			m_pLog->ClusterBegin( strFileName, strReportName );

			// add new cluster to vector
			m_vpClusters.push_back(pCluster);

			// set correct context in interpreter
			m_pInterpreter->SetContext(m_vpClusters.back()->GetContext());
			
			//import variables from keep.ini
			HandleImportFromFile();

			// show new cluster name in GUI
			m_pUIHandler->ShowCluster(m_vpClusters.back()->GetFileName());
		}
		else
		{
			// Delete Cluster object.
			delete pCluster;
			pCluster=0;

			// Report an error that the specified cluster could not be opened.
			WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_CLUSTER_NOT_OPEN, strFileName ) );
		}
	}
	else
	{
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_MAX_CLUSTERS, IntToStr( MAXIMUMCLUSTERS ) ) );
	}
}


//						============================
void					ActionServer::HandleTemplate()
//						============================
{
	// Interpret the arguments of the test line, and determine if there
	// are errors.
	if ( !InterpretLine() )
	{
		// Error are found; return.
		return;
	}

	bool bResult = false;	// result of calling the template

	// check if the function is called when a test line with a template action word is found
	if (GetActionWordType() == ActionWordList::TEMPLATE)
	{
		// Get template name and parameters from cluster.
		string strTemplateName = GetActionWord();
		vector<string> vstrParametersInCall = GetParameters();

		// Log the interpretation of a template action word.
		m_pLog->TemplateCall( strTemplateName, vstrParametersInCall );

		// check if template is registered in Template object
		vector<string>	vstrParameters;		// template parameters as registered in Template object
		string			strTemplateFile;	// file associated with template as registered in Template object
		if (m_pTemplate->Find(strTemplateName, vstrParameters, strTemplateFile))
		{
			// Check if the number of open clusters has reached its
			// allowed maximum.
			if ( MaximumClustersOpen() )
			{
				WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_MAX_CLUSTERS, IntToStr( MAXIMUMCLUSTERS ) ) );
			}
			else
			{
				// check if the number of parameters in call are not more than 
				// that as registered
				int nArguments				= ArgumentCount();
				int nParametersInCall		= nArguments - GetActionWordIndex();
				int nParametersRegistered	= vstrParameters.size();
				if (nParametersInCall <= nParametersRegistered)
				{
					// determine if there's a prototype in associated file
					string			strTemplateNameFromFile;	// template name from file
					vector<string>	vstrParametersFromFile;		// template parameters from file
					if (GetTemplatePrototypeFromFile(strTemplateFile, strTemplateNameFromFile,
														vstrParametersFromFile))
					{
						// check if prototype as registered matches with prototype from file
						if ((strTemplateName == strTemplateNameFromFile) &&
							(vstrParameters	== vstrParametersFromFile))
						{
							// add empty strings as values for template parameters not
							// filled in when the template was called
							int nEmptyParams = nParametersRegistered - nParametersInCall;
							for (; nEmptyParams > 0; nEmptyParams--)
							{
								vstrParametersInCall.push_back("");
							}

							// make a new cluster for the template file
							Cluster* pCluster = new Cluster(strTemplateFile, m_pInterpreter, m_pSetting, Cluster::TYPE_TEMPLATE );

							// Determine if the template could be opened.
							if ( pCluster->Good() )
							{
								// Log the beginning of the template.
								m_pLog->TemplateBegin( strTemplateFile );

								// add new cluster to the vector
								m_vpClusters.push_back(pCluster);

								// Assign template parameters to the context; their values are those
								// specified in the call; their types are UNSPECIFIED.
								for (int nPar = 0; nPar < nParametersRegistered; nPar++)
								{
									m_vpClusters.back()->GetContext()->Assign(vstrParameters[nPar], vstrParametersInCall[nPar], Context::UNSPECIFIED);
								}

								// set correct context in interpreter
								m_pInterpreter->SetContext(m_vpClusters.back()->GetContext());

								// show template name as new cluster in GUI
								m_pUIHandler->ShowCluster(m_vpClusters.back()->GetFileName());

								// set focus in template to line after prototype
								bool bAtPrototype = false;
								while (!bAtPrototype)
								{
									m_vpClusters.back()->ReadLine();
									m_vpClusters.back()->InterpretExceptParameters();

									switch (m_vpClusters.back()->GetActionType())
									{
										case ActionWordList::TEMPLATE_PROTO:
										{
											// At prototype test line
											bAtPrototype	= true;
											bResult			= true;

											// Log the interpretation of 'template prototype'.
											m_vpClusters.back()->Interpret();
											m_pLog->TemplatePrototype( GetParameter(1), GetParameters(2) );
											break;
										}

										case ActionWordList::EMPTY:
										{
											// empty or comment line
											// note: comment in template file before prototype will at present be ignored
											// Log that this line is skipped.
											m_pLog->Skip( GetUninterpretedArguments() );
											break;
										}

										default:
										{
											// action word other than template prototype found
											// internal error
											m_pLog->InternalError( __FILE__, __LINE__ );
											bAtPrototype	 = true;
											break;
										}
									}
								}
							}
							else
							{
								// Delete the Cluster object.
								delete pCluster;
								pCluster=0;

								// Report an error that the specified template could not be opened.
								WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NOT_OPEN, strTemplateFile ) );
							}
						}
						else
						{
							// prototypes do not match
							WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_DIFF_REGISTERED_AND_FILE, strTemplateName, strTemplateNameFromFile ) );
						}
					}
				}
				else
				{
					// incorrect number of parameters in template call
					string strParametersRegistered = IntToStr( nParametersRegistered );
					string strParametersInCall = IntToStr( nParametersInCall );

					WriteClusterError( m_pErrorList->GetText(ErrorList::ID_ERR_TPT_INCORRECT_NUMBER_PARAMETERS, 
											strTemplateName, strParametersRegistered,
											strParametersInCall ) );
				}
			}
		}
		else
		{
			// not registered in Template object, although action word is of type TEMPLATE
			m_pLog->InternalError( __FILE__, __LINE__ );
		}
	}
	else
	{
		// illegal function call
		m_pLog->InternalError( __FILE__, __LINE__ );
	}
}


//						==================================
void					ActionServer::HandleDefineTemplate()
//						==================================
{
	// Interpret the arguments of the test line, and determine if there
	// are errors.
	if ( !InterpretLine() )
	{
		// Error are found; return.
		return;
	}

	bool bResult = false;	// the result of defining the template

	// check if the function is called when a test line with a template definition
	//	action word is found
	if ( GetActionWordType() == ActionWordList::DEFINE_TEMPLATE )
	{
		// Determine name of template
		string strTemplateName = Argument( GetActionWordIndex() + 1 );

		// Determine template parameters; get the parameters of the action
		// word, and erase the first element, since this is the template name.
		vector<string> vstrTemplateParameters = GetParameters();
		vstrTemplateParameters.erase( vstrTemplateParameters.begin() );

		// Log the interpretation of 'define template'.
		m_pLog->DefineTemplate( strTemplateName, vstrTemplateParameters );

		// check if template name is valid
		if ( CheckTemplateName( strTemplateName ) )
		{
			// create template file and register template if creation was successful
			if ( CreateTemplate( strTemplateName, vstrTemplateParameters ) )
			{
				bResult = true;
			}
		}
		else
		{
			// find end of template definition and return (false)
			bool bEndOfTemplate = false;
			while ( !bEndOfTemplate )
			{
				if (m_vpClusters.back()->ReadLine())
				{
					// Interpret this next line, but do not parse its
					// parameters, since only the action word type is needed,
					// and the context must be left alone.
					m_vpClusters.back()->InterpretExceptParameters();

					// check if end definition action word is found
					if (m_vpClusters.back()->GetActionType() == ActionWordList::END_TEMPLATE)
					{
						// The end of the template definition is reached; log the
						// interpretation of 'end template'.
						bEndOfTemplate = true;
						m_pLog->EndDefineTemplate( strTemplateName );
					}
					else
					{
						// Skip this cluster line.
						m_pLog->Skip( GetUninterpretedArguments() );
					}
				}
				else
				{
					// end of file encountered before end of template definition
					// invalid template
					WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_NO_END_DEF, strTemplateName ) );
					bEndOfTemplate = true;
				}
			}
		}
	}
	else
	{
		// illegal function call
		m_pLog->InternalError( __FILE__, __LINE__ );
	}
}


//						===============================
void					ActionServer::HandleEndTemplate()
//						===============================
{
	// END_TEMPLATE without DEFINE_TEMPLATE found
	WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_END_FOUND ) );	
}


//						=================================
void					ActionServer::HandleTemplateProto()
//						=================================
{
	// Template prototype found not heading a template file
	WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_PROTOTYPE_FOUND ) );	
}


//						===================================
void					ActionServer::HandleDeclareTemplate()
//						===================================
{
	// Interpret the arguments of the test line, and determine if there
	// are errors.
	if ( !InterpretLine() )
	{
		// Error are found; return.
		return;
	}

	bool bResult = false;		// result of template declaration

	// check if the function is called when a test line with a template declaration
	//	action word is found
	if ( GetActionWordType() == ActionWordList::DECLARE_TEMPLATE )
	{
		// get template name
		string strTemplateName = Argument( GetActionWordIndex() + 1 );

		// check if template name is valid
		if ( CheckTemplateName( strTemplateName ) )
		{
			// get template file from cluster
			string strTemplateFile = NameTemplateFile(Argument(GetActionWordIndex() + 2), true);

			// check if file name is not empty
			if ( !strTemplateFile.empty() )
			{
				string			strTemplateFromFile;	// template name found in file
				vector<string>	vstrParameters;			// template parameters found in file

				// get template prototype from file
				if (GetTemplatePrototypeFromFile(strTemplateFile, strTemplateFromFile,
													vstrParameters))
				{
					// compare template from declaration with template from file prototype
					if (strTemplateName == strTemplateFromFile)
					{
						// register template in ActionWord as action word of type TEMPLATE
						if (m_pActionWord->Find(strTemplateName))
						{
							// overwrite template
							//@@ in future: warning?
							m_pActionWord->Update(strTemplateName, ActionWordList::TEMPLATE, "", "Template");
						}
						else
						{
							// register as template
							m_pActionWord->Add(strTemplateName, ActionWordList::TEMPLATE, "", "Template");
						}

						// register template with its parameters in Template object
						m_pTemplate->Add(strTemplateName, vstrParameters, strTemplateFile);

						// Log the registration of the template.
						m_pLog->RegisterTemplate( strTemplateName, strTemplateFile );

						bResult = true;
					}
					else
					{
						// different template names
						WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_TPT_DIFF_DECLARATION_AND_FILE, strTemplateName, strTemplateFromFile ) );
					}
				}
			}
			else
			{
				// no file associated with template
				WriteClusterError( m_pErrorList->GetText(ErrorList::ID_ERR_TPT_NO_FILE, strTemplateName) );
			}
		}
	}
	else
	{
		// illegal function call
		m_pLog->InternalError( __FILE__, __LINE__ );
	}
}


//						==========================
void					ActionServer::HandleAuthor()
//						==========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strClusterAuthor = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderAuthor( strClusterAuthor );
	}
}


//						===========================
void					ActionServer::HandleCluster()
//						===========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strClusterName = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderCluster( strClusterName );
	}
}


//						========================
void					ActionServer::HandleDate()
//						========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strClusterDate = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderDate( strClusterDate );
	}
}


//						===========================
void					ActionServer::HandleVersion()
//						===========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strClusterVersion = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderVersion( strClusterVersion );
	}
}


//						============================
void					ActionServer::HandleDocument()
//						============================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strDocumentName = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderDocument( strDocumentName );
	}
}


//						=========================
void					ActionServer::HandleSheet()
//						=========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strSheetName = Argument( GetActionWordIndex() + 1 );
		m_pLog->HeaderSheet( strSheetName );
	}
}


//						===========================
void					ActionServer::HandleSection()
//						===========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strSectionName = Argument(GetActionWordIndex() + 1);

		// update last section name
		m_vpClusters.back()->SetSection( strSectionName );

		// Log the interpretation of the built-in as a label with the
		// action word as its name.
		m_pLog->Label( GetActionWord(), GetParameters() );
	}
}


//						============================
void					ActionServer::HandleScenario()
//						============================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strScenarioName = Argument(GetActionWordIndex() + 1);

		// update last scenario name
		m_vpClusters.back()->SetScenario( strScenarioName );

		// Log the interpretation of the built-in as a label with the
		// action word as its name.
		m_pLog->Label( GetActionWord(), GetParameters() );
	}
}


//						============================
void					ActionServer::HandleTestCase()
//						============================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strTestCaseName = Argument(GetActionWordIndex() + 1);

		// update last test case name
		m_vpClusters.back()->SetTestCase( strTestCaseName );

		// Log the interpretation of the built-in as a label with the
		// action word as its name.
		m_pLog->Label( GetActionWord(), GetParameters() );
	}
}


//						=================================
void					ActionServer::HandleTestCondition()
//						=================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		string strTestConditionName = Argument(GetActionWordIndex() + 1);
		
		// update last test condition name
		m_vpClusters.back()->SetTestCondition( strTestConditionName );

		// Log the interpretation of the built-in as a label with the
		// action word as its name.
		m_pLog->Label( GetActionWord(), GetParameters() );
	}
}


//						================================
void					ActionServer::HandleExportAllToFile()
//						================================
{

	map<string,pair<string, int>>* pMapping = m_vpClusters.back()->GetContext()->getMappingNameValue();
	
	map<string,pair<string, int>>::iterator it = pMapping->begin();
	
	for(;it != pMapping->end();it++)
	{
		m_pKeepSetting->Set( "EXPORT", it->first,  it->second.first);
		m_pLog->ExportVariable(  it->first,  it->second.first, m_pKeepSetting->GetFileName() );
	}
	m_pKeepSetting->Export();
	

	/*tVarMap::iterator mapIterator = m_mVar.begin();
	
	map<string,string>::iterator mapIterator = pMapping->begin();

	while ( mapIterator != pMapping->end() )
	{
		// Place the variable with its value in EXPORT section of
		// the KeepSetting.
		m_pKeepSetting->Set( "EXPORT", mapIterator->first,  mapIterator->second);

		// Log that the variable has been exported.
		m_pLog->ExportVariable(  mapIterator->first,  mapIterator->second, m_pKeepSetting->GetFileName() );
		mapIterator++;
	}


	// Export the new setting to keep file.
	m_pKeepSetting->Export();*/
	
}

//						================================
void					ActionServer::HandleExportToFile()
//						================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Determine if the action word has any parameters.
		int nArguments = ArgumentCount();	// number of arguments in line
		if ( nArguments > GetActionWordIndex() )
		{
			//Determine the name of the keep file.
			string strKeepFile = m_pKeepSetting->GetFileName();
			
			// Go through each argument, which should contain a variable name.
			int c;
			for ( c = GetActionWordIndex() + 1; c <= nArguments; c++ )
			{
				// Take as variable name the value of the argument.
				string strVariableName = Argument( c );

				// Look up the variable in the context.
				pair<string, int>* ppValues;	// pointer to pair containing 
												// variable values
				ppValues = m_vpClusters.back()->GetContext()->Lookup( strVariableName );
				
				// Determine if the variable is known in the context.
				if ( ppValues != 0 )
				{
					// Determine the value of the variable.
					string strValue = ppValues->first;

					// Place the variable with its value in EXPORT section of
					// the KeepSetting.
					m_pKeepSetting->Set( "EXPORT", strVariableName, strValue );

					// Log that the variable has been exported.
					m_pLog->ExportVariable( strVariableName, strValue, strKeepFile );
				}
				else
				{
					// Create an error message that an invalid variable is specified.
					string strError = m_pErrorList->GetText( ErrorList::ID_ERR_EXPORT_INVALID_VARIABLE, strVariableName );
					WriteClusterError( strError );
				}
			}
			
			// Export the new setting to keep file.
			m_pKeepSetting->Export();
		}
		else
		{
			// Create an error message that no variables are specified.
			string strError = m_pErrorList->GetText( ErrorList::ID_ERR_NO_VARIABLES, GetActionWord() );
			WriteClusterError( strError );
		}
	}
}


//						==================================
void					ActionServer::HandleImportFromFile()
//						==================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Determine if the action word has any parameters.
		int nArguments = ArgumentCount();	// number of arguments in line
		if ( nArguments > GetActionWordIndex() )
		{
			//Determine the name of the keep file.
			string strKeepFile = m_pKeepSetting->GetFileName();

			// Go through each argument, which should contain a variable name.
			int c;
			for ( c = GetActionWordIndex() + 1; c <= nArguments; c++ )
			{
				// Take as variable name the value of the argument.
				string strVariableName = Argument( c );

				// Determine if the variable is known in the keep setting.
				if ( m_pKeepSetting->Find( "EXPORT", strVariableName ) )
				{
					// Determine variable value.
					string strValue = m_pKeepSetting->Get( "EXPORT", strVariableName );

					// Add the variable to the cluster context; specify that its type
					// is UNSPECIFIED.
					m_vpClusters.back()->GetContext()->Assign( strVariableName, strValue, Context::UNSPECIFIED );

					// Log that the variable has been imported.
					m_pLog->ImportVariable( strVariableName, strValue, strKeepFile );
				}
				else
				{
					// Create an error message that an invalid variable is specified.
					string strError = m_pErrorList->GetText( ErrorList::ID_ERR_IMPORT_INVALID_VARIABLE, strVariableName );
					WriteClusterError( strError );
				}
			}
		}
		else
		{
			// Create an error message that no variables are specified.
			string strError = m_pErrorList->GetText( ErrorList::ID_ERR_NO_VARIABLES, GetActionWord() );
			WriteClusterError( strError );
		}
	}
}


//						================================
void					ActionServer::HandleConnectSlave()
//						================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// create vector with slave names
		vector<string> vstrSlaveNames = GetParameters();

		// Log the interpretation of 'connect slave'.
		m_pLog->ConnectSlave( vstrSlaveNames );

		// Wait for all slaves to register; logging of successful registration
		// or time-out is delegated to MasterCommand.
		m_pMasterCommand->WaitForSlaveRegistration( vstrSlaveNames );
	}
}


//						===================================
void					ActionServer::HandleDisconnectSlave()
//						===================================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// create vector with slave names
		vector<string> vstrSlaveNames = GetParameters();

		// Log the interpretation of 'disconnect slave'.
		m_pLog->DisconnectSlave( vstrSlaveNames );

		// Determine if there are any slave names.
		if ( !vstrSlaveNames.empty() )
		{
			// Go passed all specified slaves.
			vector<string>::size_type nSlave = 0;
			for ( ; nSlave < vstrSlaveNames.size(); nSlave++ )
			{
				// Disconnect the specified slave, and determine if this
				// was not successful.
				if ( !m_pMasterCommand->Disconnect( vstrSlaveNames[nSlave] ) )
				{
					//@@TODO: report an error that a slave has been specified
					// which is not connected.
				}

			}
		}
	}
}


//						======================
void					ActionServer::HandleIf()
//						======================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Mark the start of a selection statement in the current cluster object.
		m_vpClusters.back()->BeginIfStatement();

		// Handle the selection statement, starting with evaluation of the
		// (first) condition.
		HandleSelectionCondition();
	}
}


//						=========================
void					ActionServer::HandleEndIf()
//						=========================
{
	// The 'end if' built-in has no arguments, so they don't need to be
	// interpreted.
	// Determine if presently a selection statement is active.
	if ( m_vpClusters.back()->GetControlFlow() == Cluster::IF )
	{
		// Mark the end of a selection statement in the current Cluster object.
		m_pLog->EndIf();
		m_vpClusters.back()->EndIfStatement();
	}
	else
	{
		// Fill the parameter with the error message that an unexpected
		// 'end if' has been encountered.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_BUILT_IN, GetActionWord() ) );
	}
}


//						========================
void					ActionServer::HandleElse()
//						========================
{
	// The 'else' built-in has no arguments, so they don't need to be
	// interpreted; if this function is used by the 'else if' built-in, the
	// arguments must already be interpreted.
	// Determine if presently a selection statement is active.
	if ( m_vpClusters.back()->GetControlFlow() == Cluster::IF )
	{
		// The found 'else' or 'else if' means the end of the processable
		// part of the current selection statement. Go to the end of the
		// selection statement, skipping all lines in between; determine
		// if the end was found.
		if ( GotoEndOfStruct( ActionWordList::IF, ActionWordList::END_IF ) )
		{
			// Mark the end of the selection statement in the current
			// Cluster object.
			m_pLog->EndIf();
			m_vpClusters.back()->EndIfStatement();
		}
		else
		{
			// No end is found for the current selection statement; fill the
			// parameter with this error.
			WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_NO_END_IF ) );
		}
	}
	else
	{
		// Fill the parameter with the error message that the current action
		// word (either 'else' or 'else if') is unexpected.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_BUILT_IN, GetActionWord() ) );
	}
}


//						==========================
void					ActionServer::HandleElseIf()
//						==========================
{
	// Interpret the arguments of the test line, and determine if there
	// are no errors.
	if ( InterpretLine() )
	{
		// Call the same function as for the 'else' action word.
		HandleElse();
	}
}


//						==========================
void					ActionServer::HandleRepeat()
//						==========================
{
	// Begin an unconditional loop; set its number of iterations to a
	// default -1.
	m_vpClusters.back()->BeginUnconditionalLoop( -1 );
	
	// Get the current loop counter.
	int nCounter = m_vpClusters.back()->GetCurrentLoopCounter();

	// Determine if it's the loop's first iteration.
	if ( nCounter == 1 )
	{
		// Set the number of iterations to default -1.
		int nIterations = -1;
		bool bValidArguments = false;

		// Interpret the arguments of the test line; determine if there
		// are no errors.
		if ( InterpretLine() )		
		{
			// The arguments are valid.
			bValidArguments = true;

			// Determine the number of iterations specified in the test line,
			// using a Number object.
			string strIterations = Argument( GetActionWordIndex() + 1 );
			Number number( strIterations );

			// Determine if the specified number is an integer.
			if ( number.IsInt() )
			{
				// Set the number of iterations.
				nIterations = StrToInt( strIterations );
			}
	
			// Set the number of iterations of this unconditional loop
			m_vpClusters.back()->SetUnconditionalLoop( nIterations );
		}

		// Determine if the number of iterations is positive.
		if ( nIterations > 0 )
		{
			// Log the start of an unconditional loop.
			m_pLog->Repeat( nIterations, 1 );
		}
		else
		{
			// The number of iterations is zero, or set to less than zero; get
			// the name of the (repeat) action word to be used in a possible
			// error message.
			string strActionWord = GetActionWord();

			// Determine if the loop was found to be invalid, i.e., if its number
			// of iterations is less than zero; also determine if the interpreter
			// found no errors.
			if ( nIterations < 0 && bValidArguments )
			{
				// Report an error about that the argument of 'repeat' may only
				// be a non-negative integer.
				string strError = m_pErrorList->GetText( ErrorList::ID_ERR_PARAM_REPEAT, strActionWord );
				WriteClusterError( strError );
			}

			// Go to the end of the repeat loop; determine if no error
			// occurred during this operation.
			if ( GotoEndOfStruct( ActionWordList::REPEAT, ActionWordList::END_REPEAT ) )
			{
				// End the trivial or invalid unconditional loop.
				m_vpClusters.back()->EndUnconditionalLoop();
			}
			else
			{
				// An end of cluster found instead of 'end repeat';
				// fill the referenced parameter with this error.
				string strError = m_pErrorList->GetText( ErrorList::ID_ERR_NO_END_LOOP, strActionWord );
				WriteClusterError( strError );
			}

		}
	}
	else
	{
		// The loop is not started, but already repeated. The number of
		// iterations specified in the test line can therefore be ignored,
		// since the total number of loops was set during the start of the
		// loop; get this total number.
		int nTotalLoops = m_vpClusters.back()->GetCurrentLoopTotal();

		// Log the repetition of an unconditional loop.
		m_pLog->Repeat( nTotalLoops, nCounter );
	}
}


//						=============================
void					ActionServer::HandleEndRepeat()
//						=============================
{
	// The 'end repeat' built-in has no arguments, so they don't need to be
	// interpreted.
	// Determine if the 'end repeat' is correctly used; i.e., determine if
	// the current control flow element is an unconditional loop,
	// a repeat-loop.
	if ( m_vpClusters.back()->GetControlFlow() == Cluster::REPEAT )
	{
		// End the unconditional loop.
		m_vpClusters.back()->EndUnconditionalLoop();

		// Log the end of an unconditional loop.
		m_pLog->EndRepeat();
	}
	else
	{
		// Log a cluster error that an 'end repeat' is found while 'repeat'
		// is not the latest control flow element.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_BUILT_IN, GetActionWord() ) );
	}
}


//						=========================
void					ActionServer::HandleWhile()
//						=========================
{
	// Interpret the arguments of the test line, and determine if there
	// are errors.
	if ( !InterpretLine() )
	{
		// Errors are found; return.
		return;
	}

	// Create a vector for the arguments of the condition.
	vector<string> vstrCondition = GetParameters();

	// Evaluate the condition, and store the whether this operation was
	// successful.
	bool bValid	= m_pCondition->Evaluate( vstrCondition );

	// After the condition has been evaluated, get its value, and store it;
	// note, though, that this value is meaningful if the evaluation was
	// successful.
	bool bValue = m_pCondition->GetValue();

	// Begin a conditional loop; state that the loop should only be opened
	// if it is both valid and true.
	m_vpClusters.back()->BeginConditionalLoop( bValid && bValue );

	// Determine if the condition was evaluated as valid.
	if ( bValid )
	{
		// Get the current loop counter.
		int nCounter = m_vpClusters.back()->GetCurrentLoopCounter();

		// Log the encounter of a while-action word, along with its condition,
		// its value, and its counter.
		m_pLog->While( vstrCondition, bValue, nCounter );
	}

	// Determine if the condition is either invalid, or false, or both.
	if ( !bValid || !bValue )
	{
		// Determine if the condition could not be evaluated.
		if ( !bValid )
		{
			// Report the error about an invalid condition, which the Condition
			// object found
			WriteClusterError( m_pCondition->GetError() );
		}

		// Get name of action word.
		string strActionWord = GetActionWord();

		// Go to the end of the while loop; determine if no error
		// occurred during this operation.
		if ( GotoEndOfStruct( ActionWordList::WHILE, ActionWordList::END_WHILE ) )
		{
			// End the conditional loop.
			m_vpClusters.back()->EndConditionalLoop();

			// Log the end of the conditional loop, if it is valid.
			if ( bValid )
			{
				//bResult = true;
				m_pLog->EndWhile();
			}
		}
		else
		{
			// An end of cluster found instead of 'end while';
			// log this error.
			WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_NO_END_LOOP, strActionWord ) );
		}
	}
}


//						============================
void					ActionServer::HandleEndWhile()
//						============================
{
	// The 'end while' built-in has no arguments, so they don't need to be
	// interpreted.
	// Determine if the 'end while' is correctly used; i.e., determine if
	// the current control flow element is a conditional loop,
	// a while-loop.
	if ( m_vpClusters.back()->GetControlFlow() == Cluster::WHILE )
	{
		// End the conditional loop.
		m_vpClusters.back()->EndConditionalLoop();

		// Log the end of the conditional loop.
		m_pLog->EndWhile();
	}
	else
	{
		// Log the cluster error that an 'end while' is found while 'while'
		// is not the latest control flow element.
		WriteClusterError( m_pErrorList->GetText( ErrorList::ID_ERR_UNEXP_BUILT_IN, GetActionWord() ) );
	}
}


//						=============================
void					ActionServer::HandleEmptyLine()
//						=============================
{
	// Get the cluster line's uninterpreted parameters.
	vector<string> vstrParameters = GetUninterpretedParameters();

	// Remove all empty parameters from the end.
	bool bReady = false;
	while ( !bReady && !vstrParameters.empty() )
	{
		if ( vstrParameters.back().empty() )
		{
			vstrParameters.pop_back();
		}
		else
		{
			bReady = true;
		}
	}

	// Determine if the cluster is truly an empty line.
	if ( vstrParameters.empty() )
	{
		// Log the interpretation of an empty line.
		m_pLog->EmptyLine();
	}
	else
	{
		// The line is a comment line; log its interpretation.
		m_pLog->CommentLine( vstrParameters );

		// Fill the parameter descriptions vector with the found comment
		// line parameters.
		m_vstrParDescr = vstrParameters;
	}
}


//						=======================
void					ActionServer::HandleSet()
//						=======================
{
	// The built-in 'set' has no functionality other than offering an action
	// word with which arguments can be evaluated (to set cluster variables,
	// etc.); so, interpret the arguments of the test line, and determine if
	// this was successful.
	if ( InterpretLine() )
	{
		// Log the interpretation of 'set'.
		m_pLog->Set( GetParameters() );
	}
}
