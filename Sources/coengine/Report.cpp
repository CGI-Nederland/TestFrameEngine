/*****************************************************************************
 * $Workfile: Report.cpp $
 * $Revision: 57 $
 * $Modtime: 11/05/01 6:31p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

// Includes
#include "Report.h"		// Class definition

#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "EngineSetting.h"
#include "IOFactory.h"
#include "IOInterface.h"
#include "LogParser.h"
#include "LogStructure.h"
#include "LogTag.h"
#include "ReportList.h"
#include "ReportSummary.h"
#include "ReportTag.h"
#include "StrUtil.h"

// Defines
#define BACKUPEXTENSION		string( "bak" )
#define LOGOFILE			string( "logo.tpl" )
#define LINEWIDTH			60
#define SPACEDELIMITER		string( "    " )
#define REPORT_FOOTER		"TestFrame Engine v2013.02. Copyright (C) 1999-2013 CGI Nederland B.V. All rights reserved."

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						==============
						Report::Report()
//						==============
{
	// Set default values for members.
	m_strReportFile = "";
	m_strOriginalReport = "";
	m_strLogFile = "";
	m_pStartStruct = 0;
	m_pReportList = new ReportList();
	m_pReportTag = new ReportTag( ReportTag::RTF );
	m_vprstrTags = m_pReportTag->GetEscapeTags();
	m_bPrintParameters = false;
	m_bOverwrite = false;
	m_strLogo = LOGOFILE;
	m_strEngineVersion = "";
	m_strEngineBuild = "";
	m_strLicenseName = "";
	m_strLicenseCompany = "";
	m_strLicenseNumber = "";
	m_pLogParser = 0;
	m_bGood = false;
	m_pLogTag = new LogTag();
	m_strCurrLineNum = "";
	m_strLastReportedLine = "";
	m_pCurrStruct = 0;

	// Fill the action-map.
	FillActionMap();
}


//						===============
						Report::~Report()
//						===============
{
	// Delete the ReportList and the LogTag objects
	delete m_pReportList;
	delete m_pReportTag;
	delete m_pLogTag;

	m_pReportList=0;
	m_pReportTag=0;
	m_pLogTag=0;

	// Delete the LogParser if it has been created.
	if ( m_pLogParser != 0 )
	{
		delete m_pLogParser;
		m_pLogParser=0;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						==================
bool					Report::Initialise
//						==================
(
	const string&		strLogFile,
	LogStructure*		pStartStruct,
	EngineSetting*		pSetting
)
{
	m_bGood = false;

	// Set the log file and starting LogStructure.
	m_strLogFile = strLogFile;
	m_pStartStruct = pStartStruct;

	// Determine if both the specified LogStructure and EngineSetting
	// objects exist.
	if ( m_pStartStruct != 0 && pSetting != 0 )
	{
		// Create the LogParser.
		if ( m_pLogParser != 0 )
		{ 
			delete m_pLogParser; 
			m_pLogParser=0;
		}
		m_pLogParser = new LogParser( m_strLogFile );

		// Determine if the LogParser is able to parse the specified log.
		if ( m_pLogParser->Good() )
		{
			// Get the necessary setting from the EngineSetting object.
			// Specify whether action word parameters are to be printed.
			m_bPrintParameters = false;
			if ( pSetting->Get( "REPORT", "Arguments" ) == "Yes" )
			{
				m_bPrintParameters = true;
			}

			// Specify whether an existing report may be overwritten.
			m_bOverwrite = false;
			if ( pSetting->Get( "REPORT", "Overwrite" ) == "Yes" )
			{
				m_bOverwrite = true;
			}

			// Specify the logo file; get the path from the settings.
			m_strLogo = pSetting->Get( "REPORT", "TemplatePath" ) + LOGOFILE;

			// Set the engine and license information.
			m_strEngineVersion = pSetting->Get( "SYSTEM", "EngineVersion" );
			m_strEngineBuild = pSetting->Get( "SYSTEM", "EngineBuild" );
			m_strComputerName = pSetting->Get( "SYSTEM", "ComputerName" );
			m_strUserName = pSetting->Get( "SYSTEM", "UserName" );
			m_strLicenseCompany = pSetting->Get( "LICENSE", "Company" );
			m_strLicenseNumber = pSetting->Get( "LICENSE", "SerialNumber" );

			// Set the language of the ReportList object.
			m_pReportList->SetLanguage( pSetting->Get( "SYSTEM", "Language" ) );

			// Clear the vectors with error line numbers and failed check line
			// numbers.
			m_vstrErrorLines.clear();
			m_vstrFailedCheckLines.clear();

			// Initialise the outlined check-, flow-control-, and
			// subcluster-tags.
			SetCheckTags();
			SetFlowControlTags();
			SetSubclusterTags();

			m_bGood = true;
		}
	}

	return m_bGood;
}


//						============
bool					Report::Good() const
//						============
{
	return m_bGood;
}


//						====================
bool					Report::CreateReport
//						====================
(
	const string&		strFile,
	const string&		strOriginal
)
{
	bool bResult = false;

	// Set the report file to create, and the original report file.
	m_strReportFile = strFile;
	m_strOriginalReport = strOriginal;

	// Write the report, and determine if this was successful.
	bResult = WriteReport();

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=====================
void					Report::FillActionMap()
//						=====================
{

	m_mAction[LogTag::ACTIONWORD]				= &Report::Action_Actionword;
	m_mAction[LogTag::ACTIONWORD_SYNONYM]		= &Report::Action_Default;
	m_mAction[LogTag::CHECK]					= &Report::Action_Check;
	m_mAction[LogTag::CLUSTER_BEGIN]			= &Report::Action_Default;
	m_mAction[LogTag::CLUSTER_END]				= &Report::Action_Default;
	m_mAction[LogTag::CLUSTER_ERROR]			= &Report::Action_ClusterError;
	m_mAction[LogTag::CLUSTER_LINE]				= &Report::Action_ClusterLine;
	m_mAction[LogTag::COMMENT_LINE]				= &Report::Action_Default;
	m_mAction[LogTag::COMPUTER_NAME]			= &Report::Action_Default;
	m_mAction[LogTag::CONNECT_SLAVE]			= &Report::Action_Default;
	m_mAction[LogTag::COPYRIGHT]				= &Report::Action_Default;
	m_mAction[LogTag::DECLARE_TEMPLATE]			= &Report::Action_Default;
	m_mAction[LogTag::DEFINE_TEMPLATE]			= &Report::Action_Default;
	m_mAction[LogTag::DISCONNECT_SLAVE]			= &Report::Action_Default;
	m_mAction[LogTag::DISPLAY_MESSAGE]			= &Report::Action_Default;
	m_mAction[LogTag::DO_CLUSTER]				= &Report::Action_DoCluster;
	m_mAction[LogTag::ELSE]						= &Report::Action_Else;
	m_mAction[LogTag::ELSE_IF]					= &Report::Action_ElseIf;
	m_mAction[LogTag::EMC_PAUSE]				= &Report::Action_Default;
	m_mAction[LogTag::EMC_RESUME]				= &Report::Action_Default;
	m_mAction[LogTag::EMC_STOP]					= &Report::Action_EMCStop;
	m_mAction[LogTag::EMPTY_LINE]				= &Report::Action_Default;
	m_mAction[LogTag::END_DEFINE_TEMPLATE]		= &Report::Action_Default;
	m_mAction[LogTag::END_IF]					= &Report::Action_EndIf;
	m_mAction[LogTag::END_REPEAT]				= &Report::Action_EndRepeat;
	m_mAction[LogTag::END_WHILE]				= &Report::Action_EndWhile;
	m_mAction[LogTag::ENGINE_BUILD_NUMBER]		= &Report::Action_Default;
	m_mAction[LogTag::ENGINE_PAUSE]				= &Report::Action_EnginePause;
	m_mAction[LogTag::ENGINE_RESET]				= &Report::Action_EngineReset;
	m_mAction[LogTag::ENGINE_RESUME]			= &Report::Action_EngineResume;
	m_mAction[LogTag::ENGINE_START]				= &Report::Action_Default;
	m_mAction[LogTag::ENGINE_STOP]				= &Report::Action_Default;
	m_mAction[LogTag::ENGINE_VERSION]			= &Report::Action_Default;
	m_mAction[LogTag::EXPORT_VARIABLE]			= &Report::Action_ExportVariable;
	m_mAction[LogTag::HEADER_AUTHOR]			= &Report::Action_Default;
	m_mAction[LogTag::HEADER_CLUSTER]			= &Report::Action_Default;
	m_mAction[LogTag::HEADER_DATE]				= &Report::Action_Default;
	m_mAction[LogTag::HEADER_DOCUMENT]			= &Report::Action_Default;
	m_mAction[LogTag::HEADER_SHEET]				= &Report::Action_Default;
	m_mAction[LogTag::HEADER_VERSION]			= &Report::Action_Default;
	m_mAction[LogTag::HEADERWORD]				= &Report::Action_Default;
	m_mAction[LogTag::IF]						= &Report::Action_If;
	m_mAction[LogTag::IMPORT_VARIABLE]			= &Report::Action_ImportVariable;
	m_mAction[LogTag::INIFILE]					= &Report::Action_Default;
	m_mAction[LogTag::INTERNAL_ERROR]			= &Report::Action_InternalError;
	m_mAction[LogTag::KEEP]						= &Report::Action_Keep;
	m_mAction[LogTag::LABEL]					= &Report::Action_Label;
	m_mAction[LogTag::LICENSE]					= &Report::Action_Default;
	m_mAction[LogTag::LINE_TO_TEMPLATE]			= &Report::Action_Default;
	m_mAction[LogTag::REGISTER_ACTIONWORD]		= &Report::Action_Default;
	m_mAction[LogTag::REGISTER_HEADERWORD]		= &Report::Action_Default;
	m_mAction[LogTag::REGISTER_TEMPLATE]		= &Report::Action_Default;
	m_mAction[LogTag::REPEAT]					= &Report::Action_Repeat;
	m_mAction[LogTag::REPORT_COMMENT]			= &Report::Action_Comment;
	m_mAction[LogTag::REPORT_ERROR]				= &Report::Action_Error;
	m_mAction[LogTag::SET]						= &Report::Action_Set;
	m_mAction[LogTag::SKIP]						= &Report::Action_Default;
	m_mAction[LogTag::SLAVE_CONNECTED]			= &Report::Action_SlaveConnected;
	m_mAction[LogTag::SLAVE_DISCONNECTED]		= &Report::Action_SlaveDisconnected;
	m_mAction[LogTag::SLAVE_LINE]				= &Report::Action_Default;
	m_mAction[LogTag::SNAP]						= &Report::Action_Snap;
	m_mAction[LogTag::STRUCTURE_BEGIN]			= &Report::Action_Default;
	m_mAction[LogTag::STRUCTURE_END]			= &Report::Action_Default;
	m_mAction[LogTag::TEMPLATE_BEGIN]			= &Report::Action_Default;
	m_mAction[LogTag::TEMPLATE_CALL]			= &Report::Action_TemplateCall;
	m_mAction[LogTag::TEMPLATE_DEFINED]			= &Report::Action_TemplateDefined;
	m_mAction[LogTag::TEMPLATE_END]				= &Report::Action_Default;
	m_mAction[LogTag::TEMPLATE_PROTOTYPE]		= &Report::Action_Default;
	m_mAction[LogTag::UNREGISTER_ACTIONWORD]	= &Report::Action_Default;
	m_mAction[LogTag::UNREGISTER_ALL_ACTIONWORDS]= &Report::Action_Default;
	m_mAction[LogTag::UNREGISTER_HEADERWORD]	= &Report::Action_Default;
	m_mAction[LogTag::USER_NAME]				= &Report::Action_Default;
	m_mAction[LogTag::WHILE]					= &Report::Action_While;
}


//						====================
void					Report::SetCheckTags()
//						====================
{
	// Determine if the ReportList object exists.
	if ( m_pReportList != 0 )
	{
		// Get the four check tags, and store them in the
		// corresponding members.
		m_strDescrTag = m_pReportList->GetText( ReportList::CHECK_ID );
		m_strExpectedTag = m_pReportList->GetText( ReportList::EXPECTED_ID );
		m_strRecordedTag = m_pReportList->GetText( ReportList::RECORDED_ID );
		m_strResultTag = m_pReportList->GetText( ReportList::RESULT_ID );

		// Place all four in a set to determine the maximum length.
		set<string> sTags;
		sTags.insert( m_strDescrTag );
		sTags.insert( m_strExpectedTag );
		sTags.insert( m_strRecordedTag );
		sTags.insert( m_strResultTag );
		int nMax = MaxLength( sTags );

		// Pad all tags (except the longest) with enough spaces to give all
		// equal length.
		m_strDescrTag += Stripe( " ", nMax - m_strDescrTag.size() );
		m_strExpectedTag += Stripe( " ", nMax - m_strExpectedTag.size() );
		m_strRecordedTag += Stripe( " ", nMax - m_strRecordedTag.size() );
		m_strResultTag += Stripe( " ", nMax - m_strResultTag.size() );
	}
}


//						==========================
void					Report::SetFlowControlTags()
//						==========================
{
	// Determine if the ReportList object exists.
	if ( m_pReportList != 0 )
	{
		// Get the three flow control tags, and store them in the
		// corresponding members.
		m_strConditionTag = m_pReportList->GetText( ReportList::CONDITION_ID );
		m_strCondResultTag = m_pReportList->GetText( ReportList::RESULT_ID );
		m_strIterationTag = m_pReportList->GetText( ReportList::ITERATION_ID );

		// Place all three in a set to determine the maximum length.
		set<string> sTags;
		sTags.insert( m_strConditionTag );
		sTags.insert( m_strCondResultTag );
		sTags.insert( m_strIterationTag );
		int nMax = MaxLength( sTags );

		// Pad all tags (except the longest) with enough spaces to give all
		// equal length.
		m_strConditionTag += Stripe( " ", nMax - m_strConditionTag.size() );
		m_strCondResultTag += Stripe( " ", nMax - m_strCondResultTag.size() );
		m_strIterationTag += Stripe( " ", nMax - m_strIterationTag.size() );
	}
}


//						=========================
void					Report::SetSubclusterTags()
//						=========================
{
	// Determine if the ReportList object exists.
	if ( m_pReportList != 0 )
	{
		// Get the two subcluster tags, and store them in the corresponding
		// members.
		m_strSubclusterTag = m_pReportList->GetText( ReportList::SUBCLUSTER_ID );
		m_strSubReportTag = m_pReportList->GetText( ReportList::REPORTNAME_ID );

		// Place both in a set to determine the maximum length.
		set<string> sTags;
		sTags.insert( m_strSubclusterTag );
		sTags.insert( m_strSubReportTag );
		int nMax = MaxLength( sTags );

		// Pad all tags (except the longest) with enough spaces to give all
		// equal length.
		m_strSubclusterTag += Stripe( " ", nMax - m_strSubclusterTag.size() );
		m_strSubReportTag += Stripe( " ", nMax - m_strSubReportTag.size() );
	}
}


//						====================
bool					Report::CreateBackup()
//						====================
{
	bool bResult = false;

	// Determine if it is necessary to create a backup of the report file;
	// i.e., if the report may not be overwritten.
	if ( !m_bOverwrite )
	{
		// Determine if the report file already exists.
		IOFactory factory;
		if ( factory.Exist( m_strReportFile ) )
		{
			// Determine the name of the backup file; this must be the name of
			// the report file with the extension changed to the backup file-
			// extension.
			string strBackup = m_strReportFile;

			// Remove any file-extension.
			string::size_type nExt = strBackup.find_last_of( "." );
			if ( nExt != string:: npos )
			{
				strBackup.erase( nExt );
			}

			// Add the backup file-extension.
			strBackup += string(".") + BACKUPEXTENSION;

			// Remove any previous backup file of this report.
			if ( factory.Exist( strBackup ) )
			{
				factory.Remove( strBackup );
			}

			// Rename the report file to the backup file.
			factory.Rename( m_strReportFile, strBackup );

			bResult = true;
		}
	}

	return bResult;
}


//						==============
string					Report::Stripe
//						==============
(
	const string&		strChar,
	int					nLength
)
{
	string strStripe;

	// Make a stripe out of the specified character.
	int nChar = 0;
	for ( ; nChar < nLength; nChar++ )
	{
		strStripe += strChar;
	}

	return strStripe;
}


//						=================
void					Report::WriteEoln()
//						=================
{
	// Place an end of line tag in the report.
	Write( m_pReportTag->GetTag( ReportTag::EOLN ) );
}


//						================
void					Report::WriteTab()
//						================
{
	// Place a tab tag in the report.
	Write( m_pReportTag->GetTag( ReportTag::TAB ) );
}


//						====================
string					Report::GetParameter
//						====================
(
	int					nIndex
)
{
	string strParameter;

	if ( m_pLogParser != 0 )
	{
		// Get the specified parameter from the current log line.
		strParameter = m_pLogParser->GetParameter( nIndex );

		// Format this parameter - escaping tags.
		FormatString( strParameter );
	}

	return strParameter;
}


//						=====================
vector<string>			Report::GetParameters()
//						=====================
{
	vector<string> vstrParams;
		
	if ( m_pLogParser != 0 )
	{
		// Get the parameters from the current log line.
		vstrParams = m_pLogParser->GetParameters();

		// Format all these parameters - escaping tags.
		if ( !vstrParams.empty() )
		{
			vector<string>::size_type nPar = 0;
			for ( ; nPar < vstrParams.size(); nPar++ )
			{
				FormatString( vstrParams[nPar] );
			}
		}
	}

	return vstrParams;
}


//						====================
void					Report::FormatString
//						====================
(
	string&				strInput
)
{
	// Escape all special tags.
	vector<pair<string, string> >::iterator itrTag = m_vprstrTags.begin();
	for ( ; itrTag != m_vprstrTags.end(); itrTag++ )
	{
		// Determine the original and replacement tag.
		string strOrig = itrTag->first;
		string strRepl = itrTag->second;

		// Replace all original tags in the input-string by the replacement
		// tags.
		string::size_type nTag = -1 * ( strRepl.size() );
		while ( ( nTag = strInput.find( strOrig, nTag + strRepl.size() ) ) != string::npos )
		{
			strInput.replace( nTag, strOrig.size(), strRepl );
		}
	}
}


//						===================
bool					Report::WriteReport()
//						===================
{
	bool bResult = false;

	// Determine if the Report-object is able to create a report.
	if ( m_bGood )
	{
		// Create a backup of the report (if necessary).
		CreateBackup();

		// Open the report file for writing, and determine if this was
		// successful.
		if ( Open( m_strReportFile, WRITE ) )
		{
			// Write the lines of the report file, divided into three
			// sections: header, body, and footer.
			WriteHeader();
			WriteBody();
			WriteFooter();

			// Close the report file.
			Close();

			bResult = true;
		}
	}

	return bResult;
}


//						===================
void					Report::WriteHeader()
//						===================
{
	// Place several tags at the top of the report file: start of document;
	// definitions of fonts; definitions of colours; definition of the normal
	// layout.
	Write( m_pReportTag->GetTag( ReportTag::STARTDOC ) );
	Write( m_pReportTag->GetTag( ReportTag::FONTTABLE ) );
	Write( m_pReportTag->GetTag( ReportTag::COLORTABLE ) );
	Write( m_pReportTag->GetTag( ReportTag::NORMAL ) );
	
	// Write a line with stripe made out of '='.
	Write( Stripe( "=", LINEWIDTH ) );
	WriteEoln();

	// Write a line with branding in big, bold Arial font; first ungarble the
	// branding string before writing it in the report.
	Write( m_pReportTag->GetTag( ReportTag::BIG ) );
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( m_pReportList->GetText( ReportList::BRANDING_ID )  );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	Write( m_pReportTag->GetTag( ReportTag::NORMALSIZE ) );
	//WriteEoln();
	//WriteEoln();

	// Determine if a logo should be used; if so, place it in the report.
	if ( m_pReportTag->UseLogo() )
	{
		PlaceLogo();
	}

	// Write all header tags in the report: engine version and build, license
	// information, and built-in and user-defined header words.
	WriteHeaderTags();

	// Write a line with stripe made out of '='.
	Write( Stripe( "=", LINEWIDTH ) );
	WriteEoln();
}


//						================
string					Report::Ungarble
//						================
(
	const string&		strInput
)
{
	// Set the ungarbled string initially to the garbled input.
	string strUngarbled = strInput;
	
	// Go passed all characters of the string.
	int nChar;
	for ( nChar = 0; nChar < strInput.length(); nChar++ )
	{
		// Determine if the specified character is not the space character ' '.
		if ( strInput[nChar] != ' ' )
		{
			// Change the character to the next one in the ASCII set.
			strUngarbled[nChar] = strInput[nChar] + 1;
		}
		else
		{
			strUngarbled[nChar] = strInput[nChar];
		}
	}

	strUngarbled[nChar] = 0;

	return strUngarbled;
}


//						=================
bool					Report::PlaceLogo()
//						=================
{
	bool bResult = false;

	// Determine if the specified logo file exists.
	IOFactory factory;
	if ( factory.Exist( m_strLogo ) )
	{	
		// Open the logo file for reading.
		IOInterface* pIOInterface = factory.CreateIOInterface( m_strLogo ); 
		pIOInterface->Open( IOInterface::IOREAD );  

		// Copy the logo file line for line into the report.
		string strLine;
		while ( pIOInterface->Read( strLine ) )
		{
			Write( strLine );
		}

		// Close the logo file.
		pIOInterface->Close();
		factory.DestroyIOInterface( pIOInterface );

		// Go to a new line in the report, and add an empty one as well.
		//WriteEoln();
		//WriteEoln();

		bResult = true;
	}

	return bResult;
}


//						=======================
void					Report::WriteHeaderTags()
//						=======================
{
	// Create a vector with header tag/parameter pairs; their order in the
	// vector reflects the order in which the lines are to be placed in the
	// report header.
	vector<pair<string, string> > vpstrHeader;

	// Add to the header vector: license name; license company; license serial
	// number; engine version; and engine build number.
	//remove license reporting
	/* string strTag = m_pReportList->GetText( ReportList::LICENSE_NAME_ID );
	vpstrHeader.push_back( make_pair( strTag, m_strLicenseName ) );

	strTag = m_pReportList->GetText( ReportList::LICENSE_COMPANY_ID );
	vpstrHeader.push_back( make_pair( strTag, m_strLicenseCompany ) );

	strTag = m_pReportList->GetText( ReportList::SERIAL_NUMBER_ID );
	vpstrHeader.push_back( make_pair( strTag, m_strLicenseNumber ) ); */
	
	string strTag = m_pReportList->GetText( ReportList::ENGINEVERSION_ID );
	vpstrHeader.push_back( make_pair( strTag, m_strEngineVersion ) );

	strTag = m_pReportList->GetText( ReportList::ENGINEBUILD_ID );
	vpstrHeader.push_back( make_pair( strTag, m_strEngineBuild ) );
	
	 strTag = m_pReportList->GetText( ReportList::USER_NAME);
	vpstrHeader.push_back( make_pair( strTag,  m_strUserName));

	strTag = m_pReportList->GetText( ReportList::COMPUTER_NAME);
	vpstrHeader.push_back( make_pair( strTag,  m_strComputerName));

	// Get from the starting LogStructure the vector of its header
	// tag/parameter pairs.
	vector<pair<string, string> > vpstrStructHead = m_pStartStruct->GetHeader();

	// Add this vector to the end of the header vector.
	if ( !vpstrStructHead.empty() )
	{
		vpstrHeader.insert( vpstrHeader.end(), vpstrStructHead.begin(), vpstrStructHead.begin() + vpstrStructHead.size() );
	}

	// Determine the length of the longest tag; to do this, copy all tags in
	// a set and the maximum length of it.
	set<string> sstrTags;
	vector<string>::size_type nTag = 0;
	for ( ; nTag < vpstrHeader.size(); nTag++ )
	{
		sstrTags.insert( vpstrHeader[nTag].first );
	}
	string::size_type nMaxTag = MaxLength( sstrTags );

	// Start writing the header tag-parameter lines to the report;
	// first, set the font to black, normal sized Courier New.
	Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
	Write( m_pReportTag->GetTag( ReportTag::NORMALSIZE ) );
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );

	// Write the license information; the first four header tags.
	WriteTagParameterLine( vpstrHeader[0], nMaxTag );
	WriteTagParameterLine( vpstrHeader[1], nMaxTag );
	WriteEoln();
	WriteTagParameterLine( vpstrHeader[2], nMaxTag );
	WriteTagParameterLine( vpstrHeader[3], nMaxTag );

	// Write an empty line.
	//WriteEoln();

	// Write the engine version and build; tags and five.

	//WriteTagParameterLine( vpstrHeader[4], nMaxTag );

	// Determine if there are other header tags.
	if ( vpstrHeader.size() > 4 )
	{
		// Write an empty line.
		//WriteEoln();

		// Write the other tags.
		for ( nTag = 5; nTag < vpstrHeader.size(); nTag++ )
		{
			WriteTagParameterLine( vpstrHeader[nTag], nMaxTag );
		}
	}

	// Set the font to Arial.
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
}


//						=============================
void					Report::WriteTagParameterLine
//						=============================
(
	const pair<string, string>&	prstrTagPar,
	int							nOutLine
)
{
	// Get the tag and parameter.
	string strTag = prstrTagPar.first;
	string strParameter = prstrTagPar.second;

	// Write the tag.
	Write( strTag );

	// Pad the tag with spaces until the outline number is reached.
	//Write( Stripe( " ", nOutLine - strTag.length() ) );

	// Write a space, a colon, and a space.
	Write( " : " );

	// Write the parameter.
	Write( strParameter );

	// Write an end of line.
	WriteEoln();
}


//						=================
void					Report::WriteBody()
//						=================
{
	// Go through all lines of the log file.
	while ( m_pLogParser->NextLine() )
	{
		// Determine the log line number, and get the pointer to the
		// LogStructure to which this log line belongs.
		int nLine = m_pLogParser->GetLogLine();
		m_pCurrStruct = m_pStartStruct->FindLogLine( nLine );

		// Determine if it belongs to any LogStructure (within our scope).
		if ( m_pCurrStruct != 0 )
		{
			// Determine if this line is to be placed in this report.
			if ( m_pCurrStruct->GetReport() == m_strOriginalReport )
			{
				// Set the the last line number to this line (combined)
				// cluster line number.
				m_strCurrLineNum = DetermineLineNumber( m_pCurrStruct );

				// Process the line.
				ProcessLine();
			}
		}
	}
}


//						===========================
string					Report::DetermineLineNumber
//						===========================
(
	LogStructure*		pLogStruct
)
{
	// Set line number to be the cluster line number of the current line.
	string strLineNumber = IntToStr( m_pLogParser->GetClusterLine() );

	// Set the LogStructure focus on the specified one.
	LogStructure* pFocus = pLogStruct;

	// Determine if the LogStructure focussed on exists, and doesn't
	// have its own report.
	while( pFocus != 0 && !pFocus->HasOwnReport() )
	{
		// Get the LogStructure's parent.
		LogStructure* pParent = pFocus->GetParent();

		// Although if a LogStructure doesn't have its own report, it must have
		// a parent, still, determine if the returned parent exists.
		if ( pParent != 0 )
		{
			// Determine if the parent type is either CLUSTER or TEMPLATE; only
			// then will we report the parent cluster line number in front.
			LogStructure::TYPE nType = pParent->GetType();
			if ( nType == LogStructure::CLUSTER || nType == LogStructure::TEMPLATE )
			{
				// Set the line number to be the line number with its parent
				// line number added in front, separated by a point.
				strLineNumber = IntToStr( pFocus->GetParentClusterLine() ) +
								"." + strLineNumber;
			}
		}

		// Set the focus on the parent.
		pFocus = pParent;
	}

	return strLineNumber;
}


//						===================
void					Report::ProcessLine()
//						===================
{
	// Determine the keyword-type of the current log line.
	LogTag::TAG nKeyWord = m_pLogParser->GetKeyWord();

	// Find this type in the action map.
	ActionMap::iterator Iterator = m_mAction.find( nKeyWord );

	// Determine if the type was found in the map.
	if ( Iterator != m_mAction.end() )
	{
		// Call the Report member function associated with the
		// current log line keyword-type.
		(this->*m_mAction[nKeyWord])();
	}
}


//						==================
string					Report::GetLineNum()
//						==================
{
	string strLineNum;

	// Determine if the current line number is not equal to the last reported
	// line number.
	if ( m_strCurrLineNum != m_strLastReportedLine )
	{
		// Update the last reported line number, and return the current line
		// number.
		m_strLastReportedLine = m_strCurrLineNum;
		strLineNum = m_strCurrLineNum + " :";
	}
	else
	{
		// Return a string of spaces the length of the last reported
		// line number.
		//strLineNum = Stripe( " ", m_strLastReportedLine.length() + 2 );
		strLineNum = ReportTag::TAB;
	}

	return strLineNum;
}


//						=======================
string					Report::GetResultString
//						=======================
(
	const string&		strResultKeyword,
	bool&				bResult
)
{
	string strResult;
	bResult = false;

	// Get the ID corresponding with the result argument-keyword, and set the
	// result string accordingly.
	switch ( m_pLogTag->GetArgTagID( strResultKeyword ) )
	{
		case LogTag::IS_TRUE:
		{
			strResult = m_pReportList->GetText( ReportList::TRUE_ID );
			bResult = true;
			break;
		}
		case LogTag::IS_FALSE:
		{
			strResult = m_pReportList->GetText( ReportList::FALSE_ID );
			break;
		}
		default:
		{
			// Corrupt log file or internal error.
			break;
		}
	}

	return strResult;
}


//						=======================
string					Report::GetResultString
//						=======================
(
	const string&		strResultKeyword
)
{
	bool bDummy;
	return GetResultString( strResultKeyword, bDummy );
}


//						==============================
LogStructure*			Report::ChildStartedOnCurrLine()
//						==============================
{
	LogStructure* pChild = 0;

	// Get the current cluster line.
	int nLine = m_pLogParser->GetClusterLine();

	// Get the children of the current LogStructure.
	set<LogStructure*> spChildren = m_pCurrStruct->GetChildren();

	// Go passed all the children until none are left or until the one
	// searched for is found.
	set<LogStructure*>::iterator itrChild = spChildren.begin();
	for ( ; itrChild != spChildren.end() && pChild == 0; itrChild++ )
	{
		// Determine if the parent cluster line of the child is the
		// current line.
		if ( (*itrChild)->GetParentClusterLine() == nLine )
		{
			pChild = *itrChild;
		}
	}

	return pChild;
}


//						===================
void					Report::WriteFooter()
//						===================
{
	WriteEoln();

	// Write a line with stripe made out of '='.
	Write( Stripe( "=", LINEWIDTH ) );
	WriteEoln();

	// Set the font to Courier New.
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );

	// Create a ReportSummary object, initialise it, and get from it the vector
	// with summary lines.
	ReportSummary rptSum;
	rptSum.Initialise( m_pReportList, m_pReportTag, m_pStartStruct,
					   m_vstrErrorLines, m_vstrFailedCheckLines );
	vector<string> vstrSummary = rptSum.GetSummary();

	// Print all lines of the summary, each followed by an 'end of line'.
	if ( !vstrSummary.empty() )
	{
		vector<string>::size_type nLine = 0;
		for ( ; nLine < vstrSummary.size(); nLine++ )
		{
			Write( vstrSummary[nLine] );
			WriteEoln();
		}
	}

	// Set the font back to Arial.
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );

	// Write a line with stripe made out of '='.
	Write( Stripe( "=", LINEWIDTH ) );
	WriteEoln();

	// Place a copyright notice at the bottom of the report.
	Write( m_pReportTag->GetTag( ReportTag::SMALL ) );
	WriteEoln();
	Write( REPORT_FOOTER );
	Write( m_pReportTag->GetTag( ReportTag::NORMALSIZE ) );

	// Place the tag for the end of the document in the report.
	Write( m_pReportTag->GetTag( ReportTag::ENDDOC ) );
}


//						====================
bool					Report::AddErrorLine()
//						====================
{
	bool bResult = false;

	// Determine if the current cluster line is not present in the vector
	// of error lines.
	if ( FindInVector( m_vstrErrorLines, m_strCurrLineNum ) == m_vstrErrorLines.end() )
	{
		// Add the current cluster line number to the back of the vector.
		m_vstrErrorLines.push_back( m_strCurrLineNum );
		bResult = true;
	}

	return bResult;
}


//						==========================
bool					Report::AddFailedCheckLine()
//						==========================
{
	bool bResult = false;

	// Determine if the current cluster line is present in the vector
	// of failed check lines.
	if ( FindInVector( m_vstrFailedCheckLines, m_strCurrLineNum ) == m_vstrFailedCheckLines.end() )
	{
		// Add the current cluster line number to the back of the vector.
		m_vstrFailedCheckLines.push_back( m_strCurrLineNum );
		bResult = true;
	}

	return bResult;
}


//////////////////////////////////////////////////////
// Keyword action functions

//						======================
void					Report::Action_Default()
//						======================
{
	// Ignore this line completely.
}

//						=========================
void					Report::Action_Actionword()
//						=========================
{
	// The ACTIONWORD keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the linenumber and the name of the action word (the keyword's
	// first parameter).
	Write( GetLineNum() );
	WriteTab();
	Write( GetParameter( 1 ) );

	// Determine if in the settings it is specified whether the action word
	// parameters are to be printed in the report.
	if ( m_bPrintParameters )
	{
		// Get all the keyword's parameters, and remove the first one, which
		// is the (already printed) name of the action word.
		vector<string> vstrParams = GetParameters();
		vstrParams.erase( vstrParams.begin() );

		// Print all these parameters, separated by spaces.
		vector<string>::iterator itrPar = vstrParams.begin();
		for ( ; itrPar != vstrParams.end(); itrPar++ )
		{
			Write( SPACEDELIMITER );
			Write( *itrPar );
		}
	}

	//WriteEoln();
}


//						====================
void					Report::Action_Check()
//						====================
{
	// The CHECK keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Get data from the log line: the result keyword (1st parameter),
	// the description (2nd), the expected value (3rd), and the recorded
	// value (4th).
	string strResult = GetParameter( 1 );
	string strDescr = GetParameter( 2 );
	string strExp = GetParameter( 3 );
	string strRec = GetParameter( 4 );

	// Get the line number to print.
	string strLineNum = GetLineNum();

	// Print the description on a separate line in the following format:
	// <linenum><tab><descr tag> : <descr>
	//Write( strLineNum ); // this produces spaces het check of is displayed here
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strDescrTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( strDescr );
	WriteEoln();

	// Print the expected value on a separate line in the following format:
	// <linenum line-out><tab><exp tag> : <exp>
	// Write( Stripe( " ", strLineNum.length() ) ); ffies geen 4 spaties meer
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strExpectedTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( strExp );
	WriteEoln();

	// Print the recorded value on a separate line in the following format:
	// <linenum line-out><tab><rec tag> : <rec>
	//Write( Stripe( " ", strLineNum.length() ) ); ffies geen 4 spaties meer
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strRecordedTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( strRec );
	WriteEoln();

	// Print the result on a separate line in the following format:
	// <linenum line-out><tab><result tag> : <result>
	//Write( Stripe( " ", strLineNum.length() ) ); ffies geen 4 spaties meer
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strResultTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );

	// Get the ID corresponding with the result argument-keyword, and set the
	// result string to report accordingly.
	switch ( m_pLogTag->GetArgTagID( strResult ) )
	{
		case LogTag::PASSED:
		{
			// Print the 'passed'-tag in green.
			Write( m_pReportTag->GetTag( ReportTag::GREEN ) );
			Write( m_pReportList->GetText( ReportList::CHK_PASSED_ID ) );
			Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
			break;
		}
		case LogTag::FAILED:
		{
			// Add the current line number to the vector of line numbers
			// with failed checks.
			AddFailedCheckLine();
			
			// Print the 'failed'-tag in red.
			Write( m_pReportTag->GetTag( ReportTag::RED ) );
			Write( m_pReportList->GetText( ReportList::CHK_FAILED_ID ) );
			Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
			break;
		}
		default:
		{
			// Corrupt log file or internal error.
			break;
		}
	}

	WriteEoln();
}


//						===========================
void					Report::Action_ClusterError()
//						===========================
{
	// The CLUSTER_ERROR keyword has been found.
	// Add the current line number to the vector of line numbers on which
	// an error occurred.
	AddErrorLine();

	// Write an empty line in the report.
	WriteEoln();

	// Print the cluster error on a line in the following format:
	// <line num><tab><cluster err tag> : <err message>
	// The error message is the log line keyword's first parameter;
	// the error tag and message are in red.
	Write( GetLineNum() );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::RED ) );
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ERR_CLUSTER_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	Write( " : " );
	Write( GetParameter( 1 ) );
	Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
	WriteEoln();
}


//						==========================
void					Report::Action_ClusterLine()
//						==========================
{
	// The CLUSTER_LINE keyword has been found.
	// If belonging to the cluster line started with this log line, a cluster
	// error has been found, a line must be placed in the report; so, determine
	// if this is the case.
	if ( m_pCurrStruct->HasClusterError( m_pLogParser->GetLogLine() ) )
	{
		// First, write an empty line in the report.
		WriteEoln();

		// Print the linenumber.
		Write( GetLineNum() );
		//WriteTab();

		// Print in red, bold, courier new the two characters '->'.
		Write( m_pReportTag->GetTag( ReportTag::RED ) );
		Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
		Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
		Write( "->" );
		Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
		Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
		Write( m_pReportTag->GetTag( ReportTag::BLACK ) );

		// Print in italics all the argument of the cluster line. i.e. all
		// parameters of the keyword, separated by spaces.
		Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
		vector<string> vstrParams = GetParameters();
		vector<string>::iterator itrPar = vstrParams.begin();
		for ( ; itrPar != vstrParams.end(); itrPar++ )
		{
			Write( SPACEDELIMITER );
			Write( *itrPar );
		}

		Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
		WriteEoln();
	}
}


//						======================
void					Report::Action_Comment()
//						======================
{
	// The REPORT_COMMENT keyword has been found.
	// First, get the line number to print; determine if the line number
	// is not already printed by determining if the returned string doesn't
	// start with a blank space.
	string strLineNum = GetLineNum();
	if ( strLineNum.substr( 0, 1 ) != " " )
	{
		// Place an empty line in the report
		WriteEoln();
	}

	// Print the line number, followed by a tab; then, print the comment
	// string (log line keyword's 1st parameter) in italics.
	Write( strLineNum );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( GetParameter( 1 ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	//WriteEoln();
}


//						========================
void					Report::Action_DoCluster()
//						========================
{
	// The DO_CLUSTER keyword has been found; this means a subcluster is
	// specified to be started.
	// First, write an empty line in the report.
	WriteEoln();

	// Print: the line number; the subcluster-tag; a colon; and (in bold font)
	// the name of the subcluster, which is the log line keyword's
	// 1st parameter.
	Write( GetLineNum() );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strSubclusterTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( GetParameter( 1 ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();

	// Determine if a child LogStructure of the current one has the current
	// cluster line number as its parent's cluster line number; this means that
	// child was started on this line.
	LogStructure* pChild = ChildStartedOnCurrLine();
	if ( pChild != 0 )
	{
		// This child-LogStructure is the started subcluster; determine if it has
		// its own report.
		if ( pChild->HasOwnReport() )
		{
			// Print this subcluster's report name.
			Write( GetLineNum() );
			//WriteTab();
			Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
			Write( m_strSubReportTag );
			Write( " : " );
			Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
			Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
			string strReport = pChild->GetReport();
			FormatString( strReport );
			Write( strReport );
			Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
			WriteEoln();
		}
	}
}


//						===================
void					Report::Action_Else()
//						===================
{
	// The ELSE keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the else-tag; this last one in a bold font.
	Write( GetLineNum() );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ELSE_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						=====================
void					Report::Action_ElseIf()
//						=====================
{
	// The ELSE_IF keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Get the line number.
	string strLineNum = GetLineNum();

	// Print three lines; the first contains the line number and the
	// else if-tag; this last one in a bold font.
	Write( strLineNum );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ELSE_IF_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();

	// Print the second line: the condition (parameter 1).
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strConditionTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( GetParameter(1) );
	WriteEoln();

	// Print the third line: the result (parameter 2) in italics.
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strCondResultTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( GetResultString( GetParameter(2) ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						======================
void					Report::Action_EMCStop()
//						======================
{
	// The EMC_STOP keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Determine the time at which the button was pressed.
	string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

	// Print the message that the stop button was pressed; this last one in
	// a bold font.
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::EMC_STOP_ID, strTime ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						====================
void					Report::Action_EndIf()
//						====================
{
	// The END_IF keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the end if-tag; this last one in a bold font.
	Write( GetLineNum() );
	WriteTab();

	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::END_IF_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						========================
void					Report::Action_EndRepeat()
//						========================
{
	// The END_REPEAT keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the end repeat-tag; this last one in a bold font.
	Write( GetLineNum() );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::END_REPEAT_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						=======================
void					Report::Action_EndWhile()
//						=======================
{
	// The END_WHILE keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the end while-tag; this last one in a bold font.
	Write( GetLineNum() );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::END_WHILE_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						==========================
void					Report::Action_EnginePause()
//						==========================
{
	// The ENGINE_PAUSE keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Determine the time at which the engine was paused.
	string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

	// Print the message that the engine was paused; this last one in a
	// bold font.
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ENGINE_PAUSE_ID, strTime ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						==========================
void					Report::Action_EngineReset()
//						==========================
{
	// The ENGINE_RESET keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Determine the time at which the engine was reset.
	string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

	// Print the message that the engine was reset; this last one in a
	// bold font.
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ENGINE_RESET_ID, strTime ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						===========================
void					Report::Action_EngineResume()
//						===========================
{
	// The ENGINE_RESUME keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Determine the time at which the engine was resumed.
	string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

	// Print the message that the engine was resumed; this last one in a
	// bold font.
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ENGINE_RESUME_ID, strTime ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();
}


//						====================
void					Report::Action_Error()
//						====================
{
	// The REPORT_ERROR keyword has been found.
	// Add the current line number to the vector of line numbers on which
	// an error occurred.
	AddErrorLine();
	
	// First, write an empty line in the report.
	WriteEoln();

	// Get the correct error tag, depending on the error type keyword, which
	// is the log line keyword's first parameter.
	string strTag;
	switch ( m_pLogTag->GetArgTagID( GetParameter( 1 ) ) )
	{
		case LogTag::ERR_CHECK:
		{
			strTag = m_pReportList->GetText( ReportList::ERR_CHECK_ID );
			break;
		}
		case LogTag::ERR_ERROR:
		{
			strTag = m_pReportList->GetText( ReportList::ERR_ERROR_ID );
			break;
		}
		case LogTag::ERR_FATAL:
		{
			strTag = m_pReportList->GetText( ReportList::ERR_FATAL_ID );
			break;
		}
		case LogTag::ERR_WARNING:
		{
			strTag = m_pReportList->GetText( ReportList::ERR_WARNING_ID );
			break;
		}
		default:
		{
			strTag = m_pReportList->GetText( ReportList::ERR_UNDEFINED_ID );
			break;
		}
	}

	// Print the error on a line in the following format:
	// <line num><tab><err tag> : <err message>
	// The error message is the log line keyword's second parameter;
	// the error tag and message are in red.
	Write( GetLineNum() );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::RED ) );
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( strTag );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	Write( " : " );
	Write( GetParameter( 2 ) );
	Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
	WriteEoln();
}


//						=============================
void					Report::Action_ExportVariable()
//						=============================
{
	// The EXPORT_VARIABLE keyword has been found.
	// First, get the line number to print; determine if the line number
	// is not already printed by determining if the returned string doesn't
	// start with a blank space.
	string strLineNum = GetLineNum();
	if ( strLineNum.substr( 0, 1 ) != " " )
	{
		// Place an empty line in the report
		WriteEoln();
	}

	// Print the line number, followed by a tab.
	Write( strLineNum );
	WriteTab();

	// Get the name of the exported cluster variable (log line
	// keyword's 1st parameter); put this name in bold font.
	string strVar = GetParameter( 1 );
	strVar = m_pReportTag->GetTag( ReportTag::BOLD ) + strVar +
			 m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the value of the exported cluster variable (log line
	// keyword's 2nd parameter); put this value in bold font.
	string strValue = GetParameter( 2 );
	strValue = m_pReportTag->GetTag( ReportTag::BOLD ) + strValue +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Write the message that the variable has been exported, in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::VARIABLE_EXPORTED_ID, strVar, strValue ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	//WriteEoln();
}


//						=================
void					Report::Action_If()
//						=================
{
	// The IF keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Get the line number.
	string strLineNum = GetLineNum();

	// Print three lines; the first contains the line number and the if-tag;
	// this last one in a bold font.
	Write( strLineNum );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::IF_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();

	// Print the second line: the condition (parameter 1).
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strConditionTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( GetParameter(1) );
	WriteEoln();

	// Print the third line: the result (parameter 2) in italics.
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strCondResultTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( GetResultString( GetParameter(2) ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						=============================
void					Report::Action_ImportVariable()
//						=============================
{
	// The IMPORT_VARIABLE keyword has been found.
	// First, get the line number to print; determine if the line number
	// is not already printed by determining if the returned string doesn't
	// start with a blank space.
	string strLineNum = GetLineNum();
	if ( strLineNum.substr( 0, 1 ) != " " )
	{
		// Place an empty line in the report
		WriteEoln();
	}

	// Print the line number, followed by a tab.
	Write( strLineNum );
	WriteTab();

	// Get the name of the imported cluster variable (log line
	// keyword's 1st parameter); put this name in bold font.
	string strVar = GetParameter( 1 );
	strVar = m_pReportTag->GetTag( ReportTag::BOLD ) + strVar +
			 m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the value of the imported cluster variable (log line
	// keyword's 2nd parameter); put this value in bold font.
	string strValue = GetParameter( 2 );
	strValue = m_pReportTag->GetTag( ReportTag::BOLD ) + strValue +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Write the message that the variable has been imported, in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::VARIABLE_IMPORTED_ID, strVar, strValue ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						============================
void					Report::Action_InternalError()
//						============================
{
	// The INTERNAL_ERROR keyword has been found.
	// Add the current line number to the vector of line numbers on which
	// an error occurred.
	AddErrorLine();

	// First, write an empty line in the report.
	WriteEoln();

	// Print the internal error tag in bold, red letters.
	string strLineNum = GetLineNum();
	Write( strLineNum );
	//WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::RED ) );
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::ERR_INTERNAL_ID ) );
	WriteEoln();

	// Print the file in which the error occurred.
	//Write( Stripe( " ", strLineNum.length() ) );
	WriteTab();
	Write( "file : " );
	Write( GetParameter( 1 ) );
	WriteEoln();

	// Print the line on which the error occurred.
	//Write( Stripe( " ", strLineNum.length() ) );
	WriteTab();
	Write( "line : " );
	Write( GetParameter( 2 ) );
	WriteEoln();

	// Set the font to normal sized, black letters.
	Write( m_pReportTag->GetTag( ReportTag::BLACK ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
}


//						===================
void					Report::Action_Keep()
//						===================
{
	// The KEEP keyword has been found.
	// First, get the line number to print; determine if the line number
	// is not already printed by determining if the returned string doesn't
	// start with a blank space.
	string strLineNum = GetLineNum();
	if ( strLineNum.substr( 0, 1 ) != " " )
	{
		// Place an empty line in the report
		WriteEoln();
		
	}

	// Print the line number, followed by a tab.
	Write( strLineNum );
	WriteTab();

	// Get the name of the kept cluster variable (log line
	// keyword's 1st parameter); put this name in bold font.
	string strVar = GetParameter( 1 );
	strVar = m_pReportTag->GetTag( ReportTag::BOLD ) + strVar + 
			 m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the value of the kept cluster variable (log line
	// keyword's 2nd parameter); put this value in bold font.
	string strValue = GetParameter( 2 );
	strValue = m_pReportTag->GetTag( ReportTag::BOLD ) + strValue +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Write the message that the variable has been kept, in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::VARIABLE_KEPT_ID, strVar, strValue ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	//WriteEoln();
}


//						====================
void					Report::Action_Label()
//						====================
{
	// The LABEL keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Set the font to big italics.
	Write( m_pReportTag->GetTag( ReportTag::BIG ) );
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );

	// Print the name of the label (keyword parameter 1) underlined.
	// N.B.: in future instead of this name a tag registered along
	// with this name (using tfe_RegisterLabel) must be printed.
	Write( m_pReportTag->GetTag( ReportTag::UNDERLINED ) );
	Write( GetParameter( 1 ) );
	Write( m_pReportTag->GetTag( ReportTag::UNUNDERLINED ) );

	// Print some spaces as a delimiter.
	Write( SPACEDELIMITER );

	// Print the description of the label (keyword parameter 2) underlined.
	Write( m_pReportTag->GetTag( ReportTag::UNDERLINED ) );
	Write( GetParameter( 2 ) );
	Write( m_pReportTag->GetTag( ReportTag::UNUNDERLINED ) );

	Write( m_pReportTag->GetTag( ReportTag::NORMALSIZE ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						=====================
void					Report::Action_Repeat()
//						=====================
{
	// The REPEAT keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the repeat-tag; this last one in a bold font.
	// After the tag, between parentheses, print the counter (log line's 2nd
	// parameter) and the total number of iterations (1st parameter).
	Write( GetLineNum() );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::REPEAT_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	Write( " ( " );
	Write( GetParameter(2) );
	Write( " / " );
	Write( GetParameter(1) );
	Write( " )" );
	WriteEoln();
}


//						==================
void					Report::Action_Set()
//						==================
{
	// The SET keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number and the set-tag
	Write( GetLineNum() );
	WriteTab();
	Write( m_pReportList->GetText( ReportList::SET_ID ) );

	// Determine if in the settings it is specified whether the action word
	// parameters are to be printed in the report.
	if ( m_bPrintParameters )
	{
		// Get all the keyword's parameters, and print these, separated by
		// space delimiter.
		vector<string> vstrParams = GetParameters();
		vector<string>::iterator itrPar = vstrParams.begin();
		for ( ; itrPar != vstrParams.end(); itrPar++ )
		{
			Write( SPACEDELIMITER );
			Write( *itrPar );
		}
	}

	WriteEoln();
}


//						=============================
void					Report::Action_SlaveConnected()
//						=============================
{
	// The SLAVE_CONNECTED keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );

	// Get the name of the connected slave (log line keyword's 1st parameter);
	// make this string in bold font.
	string strSlave = GetParameter( 1 );
	strSlave = m_pReportTag->GetTag( ReportTag::BOLD ) + strSlave +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Determine if the connection was successfull by determining if the log
	// line keyword's 2nd parameter is the argument-keyword OK.
	if ( m_pLogTag->GetArgTagID( GetParameter(2) ) == LogTag::OK )
	{
		// Determine the connection time.
		string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

		// Print the message that the slave was connected.
		Write( m_pReportList->GetText( ReportList::SLAVE_CONNECTED_ID, strSlave, strTime ) );
	}
	else
	{
		// Print the message that the slave could not be connected.
		Write( m_pReportList->GetText( ReportList::SLAVE_CONNECT_FAIL_ID, strSlave ) );
	}

	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						================================
void					Report::Action_SlaveDisconnected()
//						================================
{
	// The SLAVE_DISCONNECTED keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Get the name of the disconnected slave (log line keyword's 1st
	// parameter); make this string in bold font.
	string strSlave = GetParameter( 1 );
	strSlave = m_pReportTag->GetTag( ReportTag::BOLD ) + strSlave +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Determine the disconnection time.
	string strTime = m_pLogParser->GetDateTime().Get( "hh:mm:ss" );

	// Print the message that the slave was disconnected; in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::SLAVE_DISCONNECTED_ID, strSlave, strTime ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						===================
void					Report::Action_Snap()
//						===================
{
	// The SNAP keyword has been found.
	// First, get the line number to print; determine if the line number
	// is not already printed by determining if the returned string doesn't
	// start with a blank space.
	string strLineNum = GetLineNum();
	if ( strLineNum.substr( 0, 1 ) != " " )
	{
		// Place an empty line in the report
		WriteEoln();
	}

	// Print the line number, followed by a tab.
	Write( strLineNum );
	WriteTab();

	// Get the name of the snap-identifier (log line keyword's
	// 1st parameter); put this name in bold font.
	string strIden = GetParameter( 1 );
	strIden = m_pReportTag->GetTag( ReportTag::BOLD ) + strIden + 
			  m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the value of the snapped value (log line keyword's 
	// 2nd parameter); put this value in bold font.
	string strValue = GetParameter( 2 );
	strValue = m_pReportTag->GetTag( ReportTag::BOLD ) + strValue +
			   m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the argument in which the snap occurred (log line keyword's
	// 3rd parameter)
	string strArg = GetParameter( 3 );

	// Write the message that the value has been snapped, in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::VALUE_SNAPPED_ID, strArg, strValue, strIden ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						===========================
void					Report::Action_TemplateCall()
//						===========================
{
	// The TEMPLATECALL keyword has been found.
	// Printing such a line is the same as printing a ACTIONWORD line;
	// therefore, call this function.
	Action_Actionword();
}


//						==============================
void					Report::Action_TemplateDefined()
//						==============================
{
	// The TEMPLATE_DEFINED keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Print the line number followed by a tab.
	Write( GetLineNum() );
	WriteTab();

	// Get the name of the defined template (log line keyword's 1st parameter);
	// put this name in bold font.
	string strTemplate = GetParameter( 1 );
	strTemplate = m_pReportTag->GetTag( ReportTag::BOLD ) + strTemplate +
				  m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Get the name of the created template file (log line keyword's 2nd
	// parameter); put this name in bold font.
	string strFile = GetParameter( 2 );
	strFile = m_pReportTag->GetTag( ReportTag::BOLD ) + strFile +
			  m_pReportTag->GetTag( ReportTag::UNBOLD );

	// Write the message that the template has been defined, in italics.
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( m_pReportList->GetText( ReportList::TEMPLATE_DEFINED_ID, strTemplate, strFile ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();
}


//						====================
void					Report::Action_While()
//						====================
{
	// The WHILE keyword has been found.
	// First, write an empty line in the report.
	WriteEoln();

	// Get the line number.
	string strLineNum = GetLineNum();

	// Print four lines; the first contains the line number and the if-tag;
	// this last one in a bold font.
	Write( strLineNum );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::BOLD ) );
	Write( m_pReportList->GetText( ReportList::WHILE_ID ) );
	Write( m_pReportTag->GetTag( ReportTag::UNBOLD ) );
	WriteEoln();

	// Print the second line: the condition (parameter 1).
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strConditionTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( GetParameter(1) );
	WriteEoln();

	// Print the third line: the result (parameter 2) in italics.
	bool bResult = false;
	//Write( Stripe( "", strLineNum.length() ) );
	WriteTab();
	Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
	Write( m_strCondResultTag );
	Write( " : " );
	Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
	Write( m_pReportTag->GetTag( ReportTag::ITALIC ) );
	Write( GetResultString( GetParameter(2), bResult ) );
	Write( m_pReportTag->GetTag( ReportTag::UNITALIC ) );
	WriteEoln();

	// Print the fourth line only if the result is true: the current
	// value of the loop counter (parameter 3).
	if ( bResult )
	{
		//Write( Stripe( "", strLineNum.length() ) );
		WriteTab();
		Write( m_pReportTag->GetTag( ReportTag::COURIERNEW ) );
		Write( m_strIterationTag );
		Write( " : " );
		Write( m_pReportTag->GetTag( ReportTag::ARIAL ) );
		Write( GetParameter(3) );
		WriteEoln();
	}
}

///////////////////////////////////////////////////////////////////////////////
