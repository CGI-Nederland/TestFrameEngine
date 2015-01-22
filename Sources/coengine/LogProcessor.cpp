/*****************************************************************************
 * $Workfile: LogProcessor.cpp $
 * $Revision: 2 $
 * $Modtime: 11/05/01 6:25p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "LogProcessor.h"			// Class definition

#include <map>
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "LogParser.h"
#include "LogStructure.h"
#include "LogTag.h"
#include "ReportList.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==========================
						LogProcessor::LogProcessor()
//						==========================
{
	// Create a new LogTag object.
	m_pLogTag = new LogTag();

	// Initialise other members to their defaults.
	Clear();

	// Map LogTag keyword IDs onto member functions.
	FillActionMap();
}


//						===========================
						LogProcessor::~LogProcessor()
//						===========================
{
	delete m_pLogTag;
	m_pLogTag=0;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=============================
LogStructure*			LogProcessor::StartProcessing
//						=============================
(
	const string&		strLog,
	ReportList*			pReportList
)
{
	// Set members to default values.
	Clear();

	// Determine if the pointer to the ReportList is not null.
	if ( pReportList != 0 )
	{
		// Create the LogParser for the given log.
		m_pLogParser = new LogParser( strLog );

		// Determine if the LogParser is able to parse its log.
		if ( m_pLogParser->Good() )
		{
			// Set the ReportList.
			m_pReportList = pReportList;

			// Get a new log line from the LogParser until end of file is found.
			while ( m_pLogParser->NextLine() )
			{
				// Process the newly read line.
				ProcessLine();
			}

			// Handle the end of processing.
			HandleEndProcessing();
		}

		// Delete the LogParser, and reset its pointer to zero.
		delete m_pLogParser;
		m_pLogParser = 0;
	}

	return m_pMainCluster;
}


//							========================
map<string, LogStructure*>	LogProcessor::GetReports() const
//							========================
{
	return m_mReports;
}

///////////////////////////////////////////////////////////////////////////////
//	Implementation

//						===========================
void					LogProcessor::FillActionMap()
//						===========================
{
	m_mAction[LogTag::ACTIONWORD]				= &LogProcessor::Action_ActionWord;
	m_mAction[LogTag::ACTIONWORD_SYNONYM]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::CHECK]					= &LogProcessor::Action_Check;
	m_mAction[LogTag::CLUSTER_BEGIN]			= &LogProcessor::Action_ClusterBegin;
	m_mAction[LogTag::CLUSTER_END]				= &LogProcessor::Action_ClusterEnd;
	m_mAction[LogTag::CLUSTER_ERROR]			= &LogProcessor::Action_ClusterError;
	m_mAction[LogTag::CLUSTER_LINE]				= &LogProcessor::Action_ClusterLine;
	m_mAction[LogTag::COMMENT_LINE]				= &LogProcessor::Action_NonTestLine;
	m_mAction[LogTag::CONNECT_SLAVE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::COPYRIGHT]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::DECLARE_TEMPLATE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::DEFINE_TEMPLATE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::DISCONNECT_SLAVE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::DISPLAY_MESSAGE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::DO_CLUSTER]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ELSE]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::ELSE_IF]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::EMC_PAUSE]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::EMC_RESUME]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::EMC_STOP]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::EMPTY_LINE]				= &LogProcessor::Action_NonTestLine;
	m_mAction[LogTag::END_DEFINE_TEMPLATE]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::END_IF]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::END_REPEAT]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::END_WHILE]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_BUILD_NUMBER]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::USER_NAME]				= &LogProcessor::Action_UserName;
	m_mAction[LogTag::COMPUTER_NAME]			= &LogProcessor::Action_ComputerName;
	m_mAction[LogTag::ENGINE_PAUSE]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_RESET]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_RESUME]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_START]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_STOP]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::ENGINE_VERSION]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::EXPORT_VARIABLE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::HEADER_AUTHOR]			= &LogProcessor::Action_HeaderAuthor;
	m_mAction[LogTag::HEADER_CLUSTER]			= &LogProcessor::Action_HeaderCluster;
	m_mAction[LogTag::HEADER_DATE]				= &LogProcessor::Action_HeaderDate;
	m_mAction[LogTag::HEADER_DOCUMENT]			= &LogProcessor::Action_HeaderDocument;
	m_mAction[LogTag::HEADER_SHEET]				= &LogProcessor::Action_HeaderSheet;
	m_mAction[LogTag::HEADER_VERSION]			= &LogProcessor::Action_HeaderVersion;
	m_mAction[LogTag::HEADERWORD]				= &LogProcessor::Action_HeaderWord;
	m_mAction[LogTag::IF]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::IMPORT_VARIABLE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::INIFILE]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::INTERNAL_ERROR]			= &LogProcessor::Action_InternalError;
	m_mAction[LogTag::KEEP]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::LABEL]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::LICENSE]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::LINE_TO_TEMPLATE]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::REGISTER_ACTIONWORD]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::REGISTER_HEADERWORD]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::REGISTER_TEMPLATE]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::REPEAT]					= &LogProcessor::Action_Default;
	m_mAction[LogTag::REPORT_COMMENT]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::REPORT_ERROR]				= &LogProcessor::Action_Error;
	m_mAction[LogTag::SET]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::SKIP]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::SLAVE_CONNECTED]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::SLAVE_DISCONNECTED]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::SLAVE_LINE]				= &LogProcessor::Action_Default;
	m_mAction[LogTag::SNAP]						= &LogProcessor::Action_Default;
	m_mAction[LogTag::STRUCTURE_BEGIN]			= &LogProcessor::Action_StructureBegin;
	m_mAction[LogTag::STRUCTURE_END]			= &LogProcessor::Action_StructureEnd;
	m_mAction[LogTag::TEMPLATE_BEGIN]			= &LogProcessor::Action_TemplateBegin;
	m_mAction[LogTag::TEMPLATE_CALL]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::TEMPLATE_DEFINED]			= &LogProcessor::Action_Default;
	m_mAction[LogTag::TEMPLATE_END]				= &LogProcessor::Action_TemplateEnd;
	m_mAction[LogTag::TEMPLATE_PROTOTYPE]		= &LogProcessor::Action_Default;
	m_mAction[LogTag::UNREGISTER_ACTIONWORD]	= &LogProcessor::Action_Default;
	m_mAction[LogTag::UNREGISTER_ALL_ACTIONWORDS]= &LogProcessor::Action_Default;
	m_mAction[LogTag::UNREGISTER_HEADERWORD]	= &LogProcessor::Action_Default;
	m_mAction[LogTag::WHILE]					= &LogProcessor::Action_Default;
}


//						=========================
void					LogProcessor::ProcessLine()
//						=========================
{
	// Set the last recorded time to be the time of the current log line.
	SetLastTime();

	// Determine the keyword-type of the current log line.
	LogTag::TAG nKeyWord = m_pLogParser->GetKeyWord();

	// Find this type in the action map.
	ActionMap::iterator Iterator;
	Iterator = m_mAction.find( nKeyWord );

	// Determine if the type was found in the map.
	if ( Iterator != m_mAction.end() )
	{
		// Call the LogProcessor member function associated with the
		// current log line keyword-type.
		(this->*m_mAction[nKeyWord])();
	}
}


//						=========================
void					LogProcessor::SetLastTime()
//						=========================
{
	// Set the last recorded time to be the time of the current log line.
	m_dtLast = m_pLogParser->GetDateTime();
}


//						======================
void					LogProcessor::SetStart
//						======================
(
	LogStructure*		pLogStruct
)
{
	// Set the starting time of the specified LogStructure to be the
	// last recorded time.
	if ( pLogStruct != 0 )
	{
		pLogStruct->SetStartTime( m_dtLast );
	}
}


//						====================
void					LogProcessor::SetEnd
//						====================
(
	LogStructure*		pLogStruct
)
{
	// Set the end time of the specified LogStructure to be the
	// last recorded time.
	if ( pLogStruct != 0 )
	{
		pLogStruct->SetEndTime( m_dtLast );
	}
}


//						========================
LogStructure*			LogProcessor::LastStruct() const
//						========================
{
	LogStructure* pLogStruct = 0;

	// Determine if there are any open LogStructures
	if ( AnyOpen() )
	{
		pLogStruct = m_vpLogStructures.back();
	}

	return pLogStruct;
}


//						=====================
bool					LogProcessor::AnyOpen() const
//						=====================
{
	bool bResult = false;

	// Determine if the vector of open LogStructures contains any elements.
	if ( !m_vpLogStructures.empty() )
	{
		bResult = true;
	}

	return bResult;
}


//						==============================
void					LogProcessor::RemoveLastStruct()
//						==============================
{
	// Determine if there are any LogStructures.
	if ( AnyOpen() )
	{
		// Remove the last one from the vector.
		m_vpLogStructures.pop_back();
	}
}


//						=================================
void					LogProcessor::HandleEndProcessing()
//						=================================
{
	// Determine if there are any LogStructures still open; if so, this
	// means those structures are not correctly completed; in other words:
	// the test was stopped before it was completed.
	// Set the end time of all open LogStructures to be the last recorded time;
	// however, don't set them to be completed; clear the element from the
	// vector.
	while ( AnyOpen() )
	{
		SetEnd( LastStruct() );
		RemoveLastStruct();
	}
}


//						=============================
string					LogProcessor::DetermineReport
//						=============================
(
	const string&		strReport
)
{
	// Set the report name to the one specified.
	string strNewReport = strReport;

	// Determine if the report name has already been added to
	// the map of report names.
	while ( m_mReports.find( strNewReport ) != m_mReports.end() )
	{
		// Determine a new report name based on the old one by adding "#"
		// on the end of the name, before the extension.
		// Determine where the extension begins.
		string::iterator Iterator = strNewReport.end();
		string::size_type nExt = strNewReport.find_last_of( "." );
		if ( nExt != string::npos )
		{
			Iterator = strNewReport.begin() + nExt;
		}
		strNewReport.insert( Iterator, '#' );
	}

	return strNewReport;
}


//						===================
void					LogProcessor::Clear()
//						===================
{
	// Clear members.
	m_pLogParser = 0;
	m_pReportList = 0;
	m_pMainCluster = 0;
	m_dtLast.Set( 1, 1, 1, 0, 0, 0, 0 );
	m_vpLogStructures.clear();
	m_mReports.clear();
}

//////////////////////////////////////////////////////
// Keyword action functions

//						============================
void					LogProcessor::Action_Default()
//						============================
{
	if ( AnyOpen() )
	{
		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						===============================
void					LogProcessor::Action_ActionWord()
//						===============================
{
	// The ACTIONWORD keyword has been found.
	if ( AnyOpen() )
	{
		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						==========================
void					LogProcessor::Action_Check()
//						==========================
{
	// The CHECK keyword has been found.
	if ( AnyOpen() )
	{
		// Determine the cluster line number.
		int nClusterLine = m_pLogParser->GetClusterLine();

		// Determine the keyword's first parameter, which must be the
		// argument-tag specifying its result.
		string strResult = m_pLogParser->GetParameter( 1 );

		// Determine the result-tag's corresponding ID, and take
		// corresponding action.
		switch ( m_pLogTag->GetArgTagID( strResult ) )
		{
			case LogTag::PASSED:
			{
				LastStruct()->AddChecksPassed( nClusterLine );
				break;
			}
			case LogTag::FAILED:
			{
				LastStruct()->AddChecksFailed( nClusterLine );
				break;
			}
			default:
			{
				// Incorrect result-tag; corrupt log file, or internal error.
				break;
			}
		}

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						=================================
void					LogProcessor::Action_ClusterBegin()
//						=================================
{
	// The CLUSTER_BEGIN keyword has been found.

	// First determine its parent.
	LogStructure* pParent = 0;
	if ( AnyOpen() )
	{
		pParent = LastStruct();
	}

	// Determine the report specified; this is the keyword's second parameter.
	string strReport = m_pLogParser->GetParameter( 2 );

	// Determine if the report is to be used.
	strReport = DetermineReport( strReport );

	// Create a new LogStructure of type CLUSTER.
	LogStructure* pLogStructure = new LogStructure( LogStructure::CLUSTER, pParent, strReport );

	// Determine if this cluster has no parent.
	if ( pParent == 0 )
	{
		// This cluster is the main cluster; set the pointer to the main
		// cluster-LogStructure to the newly created one.
		m_pMainCluster = pLogStructure;
	}

	// Determine if the specified report name is not empty.
	if ( !strReport.empty() )
	{
		// This cluster is to start its own report; add the report and the
		// pointer to the LogStructure to the member map.
		// Note that any previous mentioning of this report will be overwritten.
		m_mReports[strReport] = pLogStructure;
	}

	// Set the starting time of this LogStructure to be the last recorded time
	// (which is the current line's time).
	SetStart( pLogStructure );

	// Add this log line to the new LogStructure.
	pLogStructure->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );

	// Add the LogStructure to the vector of open ones.
	m_vpLogStructures.push_back( pLogStructure );
}


//						===============================
void					LogProcessor::Action_ClusterEnd()
//						===============================
{
	// The CLUSTER_END keyword has been found.

	// Determine if there are any open LogStructures.
	if ( AnyOpen() )
	{
		// Add this log line to the last one opened.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );

		// Set the end time in this one; set it to be complete;
		// and remove it from the group of open ones (not deleted!)
		SetEnd( LastStruct() );
		LastStruct()->SetComplete();
		RemoveLastStruct();
	}
	else
	{
		// Corrupt log file, or internal error.
	}
}


//						=================================
void					LogProcessor::Action_ClusterError()
//						=================================
{
	// The CLUSTER_ERROR keyword has been found.
	if ( AnyOpen() )
	{
		// Determine the cluster line number.
		int nClusterLine = m_pLogParser->GetClusterLine();

		// Add a cluster error to the latest LogStructure.
		LastStruct()->AddError( LogStructure::ERR_CLUSTER, nClusterLine );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						================================
void					LogProcessor::Action_ClusterLine()
//						================================
{
	if ( AnyOpen() )
	{
		int nClusterLine = m_pLogParser->GetClusterLine();
		int nLogLine = m_pLogParser->GetLogLine();

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( nLogLine, nClusterLine );

		// Add the occurence of an action word (assuming beforehand that is it
		// contains an actionword, which means that lines that turn out to be
		// empty lines or comment lines must be removed).
		LastStruct()->AddActionWord( nClusterLine, nLogLine );
	}
}


//						==========================
void					LogProcessor::Action_Error()
//						==========================
{
	// The REPORT_ERROR keyword has been found.
	if ( AnyOpen() )
	{
		// Get its first parameter; this must be an argument-tag specifying
		// the error type.
		string strType = m_pLogParser->GetParameter( 1 );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );

		// Determine the cluster line number.
		int nClusterLine = m_pLogParser->GetClusterLine();

		// Determine the argument-tag ID for the type, and take action
		// for each one.
		switch ( m_pLogTag->GetArgTagID( strType ) )
		{
			case LogTag::ERR_CHECK:
			{
				LastStruct()->AddError( LogStructure::ERR_CHECK, nClusterLine );
				break;
			}
			case LogTag::ERR_ERROR:
			{
				LastStruct()->AddError( LogStructure::ERR_ERROR, nClusterLine );
				break;
			}
			case LogTag::ERR_FATAL:
			{
				LastStruct()->AddError( LogStructure::ERR_FATAL, nClusterLine );
				break;
			}
			case LogTag::ERR_WARNING:
			{
				LastStruct()->AddError( LogStructure::ERR_WARNING, nClusterLine );
				break;
			}
			default:
			{
				// Incorrect error-type-tag; corrupt log file, or internal error.
				break;
			}
		}
	}
}


//						=================================
void					LogProcessor::Action_HeaderAuthor()
//						=================================
{
	// The HEADER_AUTHOR keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::CLUSTERAUTHOR_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}

//						=================================
void					LogProcessor::Action_UserName()
//						=================================
{
	// The USER_NAME keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::USER_NAME );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}

//						=================================
void					LogProcessor::Action_ComputerName()
//						=================================
{
	// The COMPUTER_NAME keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::COMPUTER_NAME);

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						==================================
void					LogProcessor::Action_HeaderCluster()
//						==================================
{
	// The HEADER_CLUSTER keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::CLUSTERNAME_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						===============================
void					LogProcessor::Action_HeaderDate()
//						===============================
{
	// The HEADER_DATE keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::CLUSTERDATE_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						===================================
void					LogProcessor::Action_HeaderDocument()
//						===================================
{
	// The HEADER_DOCUMENT keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::DOCUMENT_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						================================
void					LogProcessor::Action_HeaderSheet()
//						================================
{
	// The HEADER_SHEET keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::SHEET_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						==================================
void					LogProcessor::Action_HeaderVersion()
//						==================================
{
	// The HEADER_VERSION keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's first parameter, which is the parameter.
		string strParameter = m_pLogParser->GetParameter( 1 );

		// Get the language-dependent tag from ReportList.
		string strTag = m_pReportList->GetText( ReportList::CLUSTERVERSION_ID );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						===============================
void					LogProcessor::Action_HeaderWord()
//						===============================
{
	// The HEADERWORD keyword has been found.
	if ( AnyOpen() )
	{
		// Get the keyword's second and third parameter, which are the tag
		// and parameter resp.
		string strTag = m_pLogParser->GetParameter( 2 );
		string strParameter = m_pLogParser->GetParameter( 3 );

		// Add a header tag/parameter pair to the latest LogStructure.
		LastStruct()->AddHeader( strTag, strParameter );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						==================================
void					LogProcessor::Action_InternalError()
//						==================================
{
	// The INTERNAL_ERROR keyword has been found.
	if ( AnyOpen() )
	{
		// Determine the cluster line number.
		int nClusterLine = m_pLogParser->GetClusterLine();

		// Add an internal error to the latest LogStructure.
		LastStruct()->AddError( LogStructure::ERR_INTERNAL, nClusterLine );

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );
	}
}


//						================================
void					LogProcessor::Action_NonTestLine()
//						================================
{
	if ( AnyOpen() )
	{
		int nClusterLine = m_pLogParser->GetClusterLine();

		// Add this log line to the latest LogStructure.
		LastStruct()->AddLogLine( m_pLogParser->GetLogLine(), nClusterLine );

		// Remove the occurence of an action word (assuming that one was
		// already added for this line when the keyword [CLUSTER_LINE]
		// was found).
		LastStruct()->RemoveActionWord( nClusterLine );
	}
}


//						===================================
void					LogProcessor::Action_StructureBegin()
//						===================================
{
	// The STRUCTURE_BEGIN keyword has been found.

	// First determine its parent.
	LogStructure* pParent = 0;
	if ( AnyOpen() )
	{
		pParent = LastStruct();
	}
	else
	{
		// A structure element without a parent means a corrupt log file,
		// or an internal error.
	}

	// Create a new LogStructure of type STRUCTURE; take as report name an
	// empty string, denoting it has no report of its own.
	LogStructure* pLogStructure = new LogStructure( LogStructure::STRUCTURE, pParent, "" );

	// Set the starting time of this LogStructure to be the last recorded time
	// (which is the current line's time).
	SetStart( pLogStructure );

	// Add this log line to the new LogStructure.
	pLogStructure->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );

	// Add the LogStructure to the vector of open ones.
	m_vpLogStructures.push_back( pLogStructure );
}


//						=================================
void					LogProcessor::Action_StructureEnd()
//						=================================
{
	// The END_STRUCTURE keyword has been found.
	// End it the same way as a LogStructure of type CLUSTER.
	Action_ClusterEnd();
}


//						==================================
void					LogProcessor::Action_TemplateBegin()
//						==================================
{
	// The TEMPLATE_BEGIN keyword has been found.

	// First determine its parent.
	LogStructure* pParent = 0;
	if ( AnyOpen() )
	{
		pParent = LastStruct();
	}
	else
	{
		// A template without a parent means a corrupt log file,
		// or an internal error.
	}

	// Create a new LogStructure of type TEMPLATE; take as report name an
	// empty string, denoting it has no report of its own.
	LogStructure* pLogStructure = new LogStructure( LogStructure::TEMPLATE, pParent, "" );

	// Set the starting time of this LogStructure to be the last recorded time
	// (which is the current line's time).
	SetStart( pLogStructure );

	// Add this log line to the new LogStructure.
	pLogStructure->AddLogLine( m_pLogParser->GetLogLine(), m_pLogParser->GetClusterLine() );

	// Add the LogStructure to the vector of open ones.
	m_vpLogStructures.push_back( pLogStructure );
}


//						================================
void					LogProcessor::Action_TemplateEnd()
//						================================
{
	// The END_TEMPLATE keyword has been found.
	// End it the same way as a LogStructure of type CLUSTER.
	Action_ClusterEnd();
}
