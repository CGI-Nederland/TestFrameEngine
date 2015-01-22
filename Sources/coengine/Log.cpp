/*****************************************************************************
 * $Workfile: Log.cpp $
 * $Revision: 23 $
 * $Modtime: 8/20/01 3:32p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "Log.h"			// Class definition

#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "EngineSetting.h"
#include "FileName.h"
#include "LogTag.h"
#include "Mutex.h"
#include "StrUtil.h"

// Defines
#define NOT_ALLOWED_IN_FILE		string( "./\\:*?\"<>|" )
#define LOG_EXTENSION			string( "log" )

///////////////////////////////////////////////////////////////////////////////

// Initiate the static data member of Log: set the pointer to its one
// allowed instance to the null pointer.
Log* Log::m_pLog = 0;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//				========
				Log::Log()
//				========
{
	m_bGood = false;
	m_nLineNumber = 0;
}

//				=========
				Log::~Log()
//				=========
{
	Close();
	m_pLog = 0;
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						=============
Log*					Log::Instance()
//						=============
{
	// Determine if the pointer to Log's one allowed instance is
	// the null pointer.
	if ( m_pLog == 0 )
	{
		// Create the instance of Log.
		m_pLog = new Log;
	}

	return m_pLog;
}


//						===============
void					Log::Initialise
//						===============
(
	EngineSetting*		pSetting	// pointer to Setting object
)
{
	// Set the log name to the name of the cluster; place the '@' character
	// after it.
	m_strLogName = pSetting->Get( "CLUSTER", "FileName" ) + "@";

	// Make a string out of the current date and time (separated by an
	// underscore), and add this to the back of the file name.
	DateTime dt;
	m_strLogName += dt.Get( "YYYYMMDD_hhmmss" );

	// Replace all characters that are not allowed in a file name by underscores.
	string::size_type nChar;
	while ( (nChar = m_strLogName.find_first_of( NOT_ALLOWED_IN_FILE )) != string::npos )
	{
		m_strLogName.replace( nChar, 1, "_" );
	}

	// Create a FileName object of the log name; set its extension;
	// set its location as specified in the settings.
	FileName fnLog( m_strLogName );
	fnLog.ChangeExtension( LOG_EXTENSION );
	fnLog.ChangeLocation( pSetting->Get( "LOG", "Path" ) );

	// Determine if the file name is unique.
	int nCounter = 0;
	bool bUnique = false;
	while ( !bUnique )
	{
		// If the name was already once found to be not unique, add
		// another '#' character to the back of the name.
		if ( nCounter > 0 )
		{
			fnLog.ChangeName( fnLog.GetName() + "#" );
		}

		// Get the new log file.
		m_strLogName = fnLog.GetFile();

		// Determine if a file with this name/location already exists.
		if( FileExists( m_strLogName ) )
		{
			// File name already exists; update counter.
			nCounter++;
		}
		else
		{
			bUnique = true;
		}
	}

	// Open the output medium for writing, and check if this succeeds.
	if ( Open( m_strLogName, WRITE ) )
	{
		m_bGood = true;
	}
}


//						=========
bool					Log::Good() const
//						=========
{
	return m_bGood;
}


//						==================
void					Log::SetLineNumber
//						==================
(
	int					nLine
)
{
	// Store the linenumber in the member variable
	m_nLineNumber = nLine;
}


//						===============
const string&			Log::GetLogName() const
//						===============
{
	return m_strLogName;
}

///////////////
// Data logging

//						==============
void					Log::Copyright
//						==============
(
	const string&		strCopyright
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::COPYRIGHT ) );
	vstrArgs.push_back( strCopyright );
	
	WriteLine( vstrArgs );
}


//						==================
void					Log::EngineVersion
//						==================
(
	const string&		strVersion
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_VERSION ) );
	vstrArgs.push_back( strVersion );
	
	WriteLine( vstrArgs );
}


//						======================
void					Log::EngineBuildNumber
//						======================
(
	const string&		strBuild
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_BUILD_NUMBER ) );
	vstrArgs.push_back( strBuild );
	
	WriteLine( vstrArgs );
}

//						======================
void					Log::UserName
//						======================
(
	const string&		strUserName
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::USER_NAME ) );
	vstrArgs.push_back( strUserName );
	
	WriteLine( vstrArgs );
}

//						============
void					Log::ComputerName
//						============
(
	const string&		strName
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::COMPUTER_NAME ) );
	vstrArgs.push_back( strName );
	
	WriteLine( vstrArgs );
}

//						============
void					Log::License
//						============
(
	const string&		strName,
	const string&		strCompany,
	const string&		strSerialNumber
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::LICENSE ) );
	vstrArgs.push_back( strName );
	vstrArgs.push_back( strCompany );
	vstrArgs.push_back( strSerialNumber );
	
	WriteLine( vstrArgs );
}


//						============
void					Log::IniFile
//						============
(
	const string&		strSection,
	const string&		strKey,
	const string&		strValue
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::INIFILE ) );
	vstrArgs.push_back( strSection );
	vstrArgs.push_back( strKey );
	vstrArgs.push_back( strValue );
	
	WriteLine( vstrArgs );
}


//						=======================
void					Log::RegisterActionWord
//						=======================
(
	const string&		strActionWord,
	const string&		strFunction
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REGISTER_ACTIONWORD ) );
	vstrArgs.push_back( strActionWord );
	vstrArgs.push_back( strFunction );
	
	WriteLine( vstrArgs );
}


//						=======================
void					Log::RegisterHeaderWord
//						=======================
(
	const string&		strHeaderWord,
	const string&		strReportTag
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REGISTER_HEADERWORD ) );
	vstrArgs.push_back( strHeaderWord );
	vstrArgs.push_back( strReportTag );
	
	WriteLine( vstrArgs );
}


//						======================
void					Log::ActionWordSynonym
//						======================
(
	const string&		strActionWord,
	const string&		strSynonym
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ACTIONWORD_SYNONYM ) );
	vstrArgs.push_back( strActionWord );
	vstrArgs.push_back( strSynonym );
	
	WriteLine( vstrArgs );
}


//						=========================
void					Log::UnregisterActionWord
//						=========================
(
	const string&		strActionWord
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::UNREGISTER_ACTIONWORD ) );
	vstrArgs.push_back( strActionWord );
	
	WriteLine( vstrArgs );
}


//						=========================
void					Log::UnregisterHeaderWord
//						=========================
(
	const string&		strHeaderWord
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::UNREGISTER_HEADERWORD ) );
	vstrArgs.push_back( strHeaderWord );
	
	WriteLine( vstrArgs );
}


//						=============================
void					Log::UnregisterAllActionWords()
//						=============================
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::UNREGISTER_ALL_ACTIONWORDS ) );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::EngineStart
//						================
(
	const string&		strCluster,
	const string&		strReport,
	const string&		strIniFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_START ) );
	vstrArgs.push_back( strCluster );
	vstrArgs.push_back( strReport );
	vstrArgs.push_back( strIniFile );
	
	WriteLine( vstrArgs );
}


//						===============
void					Log::EngineStop()
//						===============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_STOP ) );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::EngineReset()
//						================
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_RESET ) );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::EnginePause()
//						================
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_PAUSE ) );
	
	WriteLine( vstrArgs );
}


//						=================
void					Log::EngineResume()
//						=================
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ENGINE_RESUME ) );
	
	WriteLine( vstrArgs );
}


//						=============
void					Log::EMCPause()
//						=============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::EMC_PAUSE ) );
	
	WriteLine( vstrArgs );
}


//						==============
void					Log::EMCResume()
//						==============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::EMC_RESUME ) );
	
	WriteLine( vstrArgs );
}


//						============
void					Log::EMCStop()
//						============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::EMC_STOP ) );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::DisplayMessage
//						===================
(
	const string&		strMessage
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::DISPLAY_MESSAGE ) );
	vstrArgs.push_back( strMessage );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::ClusterLine
//						================
(
	const vector<string>&	vstrArguments
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CLUSTER_LINE ) );
	vstrArgs.insert( vstrArgs.end(), vstrArguments.begin(), vstrArguments.end() );
	
	WriteLine( vstrArgs );
}


//						==============
void					Log::EmptyLine()
//						==============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::EMPTY_LINE ) );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::CommentLine
//						================
(
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::COMMENT_LINE ) );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						===============
void					Log::ActionWord
//						===============
(
	const string&			strActionWord,
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ACTIONWORD ) );
	vstrArgs.push_back( strActionWord );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						========
void					Log::Set
//						========
(
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SET ) );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						=========
void					Log::Skip
//						=========
(
	const vector<string>&	vstrArguments
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SKIP ) );
	vstrArgs.insert( vstrArgs.end(), vstrArguments.begin(), vstrArguments.end() );
	
	WriteLine( vstrArgs );
}


//						=================
void					Log::ClusterBegin
//						=================
(
	const string&		strCluster,
	const string&		strReport
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CLUSTER_BEGIN ) );
	vstrArgs.push_back( strCluster );
	vstrArgs.push_back( strReport );
	
	WriteLine( vstrArgs );
}


//						===============
void					Log::ClusterEnd
//						===============
(
	const string&		strCluster
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CLUSTER_END ) );
	vstrArgs.push_back( strCluster );
	
	WriteLine( vstrArgs );
}


//						==============
void					Log::DoCluster
//						==============
(
	const string&		strSubcluster,
	const string&		strReport
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::DO_CLUSTER ) );
	vstrArgs.push_back( strSubcluster );
	vstrArgs.push_back( strReport );
	
	WriteLine( vstrArgs );
}


//						=================
void					Log::TemplateCall
//						=================
(
	const string&			strTemplate,
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::TEMPLATE_CALL ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						==================
void					Log::TemplateBegin
//						==================
(
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::TEMPLATE_BEGIN ) );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::TemplateEnd
//						================
(
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::TEMPLATE_END ) );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						======================
void					Log::TemplatePrototype
//						======================
(
	const string&			strTemplate,
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::TEMPLATE_PROTOTYPE ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::DefineTemplate
//						===================
(
	const string&			strTemplate,
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::DEFINE_TEMPLATE ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::LineToTemplate
//						===================
(
	const vector<string>&	vstrArguments
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::LINE_TO_TEMPLATE ) );
	vstrArgs.insert( vstrArgs.end(), vstrArguments.begin(), vstrArguments.end() );
	
	WriteLine( vstrArgs );
}


//						======================
void					Log::EndDefineTemplate
//						======================
(
	const string&		strTemplate
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::END_DEFINE_TEMPLATE ) );
	vstrArgs.push_back( strTemplate );
	
	WriteLine( vstrArgs );
}


//						====================
void					Log::TemplateDefined
//						====================
(
	const string&		strTemplate,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::TEMPLATE_DEFINED ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.push_back( strFile );

	WriteLine( vstrArgs );
}


//						====================
void					Log::DeclareTemplate
//						====================
(
	const string&		strTemplate,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::DECLARE_TEMPLATE ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.push_back( strFile );

	WriteLine( vstrArgs );
}


//						=====================
void					Log::RegisterTemplate
//						=====================
(
	const string&		strTemplate,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REGISTER_TEMPLATE ) );
	vstrArgs.push_back( strTemplate );
	vstrArgs.push_back( strFile );

	WriteLine( vstrArgs );
}


//						===============
void					Log::HeaderWord
//						===============
(
	const string&		strHeaderWord,
	const string&		strReportTag,
	const string&		strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADERWORD ) );
	vstrArgs.push_back( strHeaderWord );
	vstrArgs.push_back( strReportTag );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						==================
void					Log::HeaderCluster
//						==================
(
	const string&		strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_CLUSTER ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						===============
void					Log::HeaderDate
//						===============
(
	const string&	strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_DATE ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						=================
void					Log::HeaderAuthor
//						=================
(
	const string&		strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_AUTHOR ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						==================
void					Log::HeaderVersion
//						==================
(
	const string&		strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_VERSION ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						===================
void					Log::HeaderDocument
//						===================
(
	const string&	strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_DOCUMENT ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						================
void					Log::HeaderSheet
//						================
(
	const string&		strParameter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::HEADER_SHEET ) );
	vstrArgs.push_back( strParameter );

	WriteLine( vstrArgs );
}


//						==========
void					Log::Label
//						==========
(
	const string&			strName,
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::LABEL ) );
	vstrArgs.push_back( strName );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::ExportVariable
//						===================
(
	const string&		strVariable,
	const string&		strValue,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::EXPORT_VARIABLE ) );
	vstrArgs.push_back( strVariable );
	vstrArgs.push_back( strValue );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::ImportVariable
//						===================
(
	const string&		strVariable,
	const string&		strValue,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::IMPORT_VARIABLE ) );
	vstrArgs.push_back( strVariable );
	vstrArgs.push_back( strValue );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						=========
void					Log::Keep
//						=========
(
	const string&		strVariable,
	const string&		strValue,
	int					nArgument,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::KEEP ) );
	vstrArgs.push_back( strVariable );
	vstrArgs.push_back( strValue );
	vstrArgs.push_back( IntToStr( nArgument ) );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						=========
void					Log::Snap
//						=========
(
	const string&		strIdentifier,
	const string&		strValue,
	int					nArgument,
	const string&		strFile
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SNAP ) );
	vstrArgs.push_back( strIdentifier );
	vstrArgs.push_back( strValue );
	vstrArgs.push_back( IntToStr( nArgument ) );
	vstrArgs.push_back( strFile );
	
	WriteLine( vstrArgs );
}


//						==========
void					Log::Check
//						==========
(
	bool				bResult,
	const string&		strDescription,
	const string&		strExpected,
	const string&		strRecorded,
	CHECKTYPE			nType,
	int					nIndex
)
{
	vector<string> vstrArgs;

	// Place the CHECK-keyword at the beginning of the line.
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CHECK ) );

	// Add the appropriate result-keyword.
	if ( bResult )
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::PASSED ) );
	}
	else
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::FAILED ) );
	}
	
	// Add description, expected value, and recorded value.
	vstrArgs.push_back( strDescription );
	vstrArgs.push_back( strExpected );
	vstrArgs.push_back( strRecorded );

	// Add the appropriate check type-keyword; in case of type CHECK_ARGUMENT
	// or CHECK_PARAMETER also add the index.
	switch ( nType )
	{
		case CHECK_ARGUMENT:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::CH_ARGUMENT ) );
			vstrArgs.push_back( IntToStr( nIndex ) );
			break;
		}
		
		case CHECK_PARAMETER:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::CH_PARAMETER ) );
			vstrArgs.push_back( IntToStr( nIndex ) );
			break;
		}

		case CHECK_STRING:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::CH_STRING ) );
			break;
		}

		case CHECK_REPORT:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::CH_REPORT ) );
			break;
		}
	}

	WriteLine( vstrArgs );
}


//						==================
void					Log::ReportComment
//						==================
(
	const string&		strComment
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REPORT_COMMENT ) );
	vstrArgs.push_back( strComment );
	
	WriteLine( vstrArgs );
}


//						================
void					Log::ReportError
//						================
(
	ERRORCODE			nType,
	const string&		strMessage
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REPORT_ERROR ) );

	switch ( nType )
	{
		case NUM_ERR_WARNING:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::ERR_WARNING ) );
			break;
		}

		case NUM_ERR_ERROR:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::ERR_ERROR ) );
			break;
		}

		case NUM_ERR_CHECK:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::ERR_CHECK ) );
			break;
		}

		case NUM_ERR_FATAL:
		{
			vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::ERR_FATAL ) );
			break;
		}
	}

	vstrArgs.push_back( strMessage );
	
	WriteLine( vstrArgs );
}


//						=================
void					Log::ClusterError
//						=================
(
	const string&		strMessage
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CLUSTER_ERROR ) );
	vstrArgs.push_back( strMessage );
	
	WriteLine( vstrArgs );
}


//						==================
void					Log::InternalError
//						==================
(
	const string&		strFile,
	int					nLine
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::INTERNAL_ERROR ) );
	vstrArgs.push_back( strFile );
	vstrArgs.push_back( IntToStr( nLine ) );
	
	WriteLine( vstrArgs );
}


//						=======
void					Log::If
//						=======
(
	const vector<string>&	vstrCondition,
	bool					bResult
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::IF ) );
	vstrArgs.push_back( VectorToStr( vstrCondition, " " ) );

	if ( bResult )
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_TRUE ) );
	}
	else
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_FALSE ) );
	}
	
	WriteLine( vstrArgs );
}


//						===========
void					Log::ElseIf
//						===========
(
	const vector<string>&	vstrCondition,
	bool					bResult
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ELSE_IF ) );
	vstrArgs.push_back( VectorToStr( vstrCondition, " " ) );

	if ( bResult )
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_TRUE ) );
	}
	else
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_FALSE ) );
	}
	
	WriteLine( vstrArgs );
}


//						=========
void					Log::Else()
//						=========
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::ELSE ) );
	
	WriteLine( vstrArgs );
}


//						==========
void					Log::EndIf()
//						==========
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::END_IF ) );
	
	WriteLine( vstrArgs );
}


//						===========
void					Log::Repeat
//						===========
(
	int					nTotal,
	int					nCounter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::REPEAT ) );
	vstrArgs.push_back( IntToStr( nTotal ) );
	vstrArgs.push_back( IntToStr( nCounter ) );
	
	WriteLine( vstrArgs );
}


//						==============
void					Log::EndRepeat()
//						==============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::END_REPEAT ) );
	
	WriteLine( vstrArgs );
}


//						==========
void					Log::While
//						==========
(
	const vector<string>&	vstrCondition,
	bool					bResult,
	int						nCounter
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::WHILE ) );
	vstrArgs.push_back( VectorToStr( vstrCondition, " " ) );

	if ( bResult )
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_TRUE ) );
	}
	else
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::IS_FALSE ) );
	}
	
	vstrArgs.push_back( IntToStr( nCounter ) );

	WriteLine( vstrArgs );
}


//						=============
void					Log::EndWhile()
//						=============
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::END_WHILE ) );
	
	WriteLine( vstrArgs );
}


//						==============
void					Log::SlaveLine
//						==============
(
	const string&			strSlave,
	const vector<string>&	vstrArguments
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SLAVE_LINE ) );
	vstrArgs.push_back( strSlave );
	vstrArgs.insert( vstrArgs.end(), vstrArguments.begin(), vstrArguments.end() );
	
	WriteLine( vstrArgs );
}


//						=================
void					Log::ConnectSlave
//						=================
(
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::CONNECT_SLAVE ) );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						===================
void					Log::SlaveConnected
//						===================
(
	const string&		strSlave,
	bool				bConnected
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SLAVE_CONNECTED ) );
	vstrArgs.push_back( strSlave );

	if ( bConnected )
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::OK ) );
	}
	else
	{
		vstrArgs.push_back( m_LogTag.GetArgTag( LogTag::TIMEOUT ) );
	}

	WriteLine( vstrArgs );
}


//						====================
void					Log::DisconnectSlave
//						====================
(
	const vector<string>&	vstrParameters
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::DISCONNECT_SLAVE ) );
	vstrArgs.insert( vstrArgs.end(), vstrParameters.begin(), vstrParameters.end() );
	
	WriteLine( vstrArgs );
}


//						======================
void					Log::SlaveDisconnected
//						======================
(
	const string&		strSlave
)
{
	vector<string> vstrArgs;
	vstrArgs.push_back( m_LogTag.GetTag( LogTag::SLAVE_DISCONNECTED ) );
	vstrArgs.push_back( strSlave );
	
	WriteLine( vstrArgs );
}

///////////////////////////////////////////////////////////////////////////////
//	Implementation

//						==============
bool					Log::WriteLine
//						==============
(
	const vector<string>&	vstrArguments
)
{
	bool bResult = false;

	vector<string> vstrArgs = vstrArguments;

	// Escape tabs in all arguments.
	vector<string>::size_type nArg;
	for ( nArg = 0; nArg < vstrArgs.size(); nArg++ )
	{
		EscapeTabs( vstrArgs[nArg] );
	}

	// Lock the mutex object so only this call will be able to write in
	// the log file.
	m_Lock.Lock();

	// Create a DateTime object (for the current date/time),
	// and get a date-string and time-string from it.
	DateTime dtNow;
	string strFormatted = dtNow.Get( "YYYY-MM-DD" ) + DELIMITER + 
						  dtNow.Get( "hh:mm:ss.nnn" ) + DELIMITER +
						  IntToStr( m_nLineNumber ) + DELIMITER +
						  VectorToStr( vstrArgs, DELIMITER );

	// Escape returns to prevent the creation of extra log lines
	EscapeReturns( strFormatted );

	// Append a '\n' to the string
	strFormatted += "\n";

	// Write the string to the log file
	bResult = Write( strFormatted );

	// Unlock the mutex to give it free again.
	m_Lock.Unlock();

	return bResult;
}


//						==================
int						Log::EscapeReturns
//						==================
(
	string&				strLine
)
{
	int nReplacements = 0;
	
	// Replace returns with "\n"
	string::size_type nCharPos;
	while ( (nCharPos = strLine.find_first_of("\n")) != string::npos )
	{
		strLine.replace( nCharPos, 1, "\\n" );
		nReplacements++;
	}

	return nReplacements;
}


//						===============
int						Log::EscapeTabs
//						===============
(
	string&				strLine
)
{
	int nReplacements = 0;
	
	// Replace tabs with "\t"
	string::size_type nCharPos;
	while ( (nCharPos = strLine.find_first_of("\t")) != string::npos )
	{
		strLine.replace( nCharPos, 1, "\\t" );
		nReplacements++;
	}

	return nReplacements;
}

///////////////////////////////////////////////////////////////////////////////

#undef NOT_ALLOWED_IN_FILE
#undef LOG_EXTENSION
