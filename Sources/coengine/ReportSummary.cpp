/*****************************************************************************
 * $Workfile: ReportSummary.cpp $
 * $Revision: 1 $
 * $Modtime: 8/09/01 7:36p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "ReportSummary.h"		// Class definition

#include <set>
#include <string>
#include <vector>

using namespace std;

#include "DateTime.h"
#include "Duration.h"
#include "LogStructure.h"
#include "LogTag.h"
#include "ReportList.h"
#include "ReportTag.h"
#include "StrUtil.h"

// Defines
#define INDENT				string( "- " )
#define ONLY_THIS_REPORT	true

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						============================
						ReportSummary::ReportSummary()
//						============================
{
	// Set default values for members.
	m_pReportList = 0;
	m_pReportTag = 0;
	m_pStartStruct = 0;
	m_bGood = false;
	m_nActionWords = 0;
	m_nFailedActionWords = 0;
	m_nErrors = 0;
	m_nErrWarning = 0;
	m_nErrError = 0;
	m_nErrCheck = 0;
	m_nErrFatal = 0;
	m_nErrCluster = 0;
	m_nErrIntern = 0;
	m_nChecks = 0;
	m_nChecksPassed = 0;
	m_nChecksFailed = 0;
	m_nOutline = 0;
}


//						=============================
						ReportSummary::~ReportSummary()
//						=============================
{
	// empty.
}

///////////////////////////////////////////////////////////////////////////////
// Public interface


//						=========================
bool					ReportSummary::Initialise
//						=========================
(
	ReportList*				pReportList,
	ReportTag*				pReportTag,
	LogStructure*			pStartStruct,
	const vector<string>&	vstrErrorLines,
	const vector<string>&	vstrFailedCheckLines
)
{
	m_bGood = false;

	// Determine if the referenced objects exist.
	if ( pReportList != 0 && pReportTag != 0 && pStartStruct != 0 )
	{
		// Set the members.
		m_bGood = true;
		m_pReportList = pReportList;
		m_pReportTag = pReportTag;
		m_pStartStruct = pStartStruct;
		m_vstrErrorLines = vstrErrorLines;
		m_vstrFailedCheckLines = vstrFailedCheckLines;

		// Create the summary.
		CreateSummary();
	}

	return m_bGood;
}


//						===================
bool					ReportSummary::Good() const
//						===================
{
	return m_bGood;
}


//						=========================
const vector<string>&	ReportSummary::GetSummary() const
//						=========================
{
	return m_vstrSummary;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						============================
void					ReportSummary::CreateSummary()
//						============================
{
	// Set the statistics as determined by the LogStructures.
	SetStatistics();

	// Determine the outline.
	DetermineOutline();

	// Create the test line section.
	TestLineSection();

	// Create the error section.
	ErrorSection();

	// Create the check section.
	CheckSection();

	// Create the time section.
	TimeSection();
}


//						============================
void					ReportSummary::SetStatistics()
//						============================
{
	// Get statistics from the LogStructures, for all the lines printed in this
	// report: number of action words; number of failed action words; numbers of
	// errors for all six types; numbers of passed and failed checks.
	m_nActionWords = m_pStartStruct->GetAllActionWords( ONLY_THIS_REPORT );
	m_nFailedActionWords = m_pStartStruct->GetAllFailedActionWords( ONLY_THIS_REPORT );
	m_nErrWarning = m_pStartStruct->GetAllErrors( LogStructure::ERR_WARNING, ONLY_THIS_REPORT );
	m_nErrError = m_pStartStruct->GetAllErrors( LogStructure::ERR_ERROR, ONLY_THIS_REPORT );
	m_nErrCheck = m_pStartStruct->GetAllErrors( LogStructure::ERR_CHECK, ONLY_THIS_REPORT );
	m_nErrFatal = m_pStartStruct->GetAllErrors( LogStructure::ERR_FATAL, ONLY_THIS_REPORT );
	m_nErrCluster = m_pStartStruct->GetAllErrors( LogStructure::ERR_CLUSTER, ONLY_THIS_REPORT );
	m_nErrIntern = m_pStartStruct->GetAllErrors( LogStructure::ERR_INTERNAL, ONLY_THIS_REPORT );
	m_nChecksPassed = m_pStartStruct->GetAllChecksPassed( ONLY_THIS_REPORT );
	m_nChecksFailed = m_pStartStruct->GetAllChecksFailed( ONLY_THIS_REPORT );

	// Calculate the total number of errors and the total number of checks.
	m_nErrors = m_nErrWarning + m_nErrError + m_nErrCheck + m_nErrFatal + 
				m_nErrCluster + m_nErrIntern;
	m_nChecks = m_nChecksPassed + m_nChecksFailed;
}


//						===============================
void					ReportSummary::DetermineOutline()
//						===============================
{
	// Create a set of tags from the ReportList object; some are only added
	// if they are to be printed (which depends on the value behind the tag).
	set<string> sstrTags;

	// Add 'number of test lines' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::NUMTESTLINES_ID ) );

	// Add 'succeeded test lines' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::SUCC_LINES_ID ) );

	// Add 'number of errors' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::NUMERROR_ID ) );

	// Add 'warning' tag, only there are any.
	if ( m_nErrWarning > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_WARNING_ID ) );
	}

	// Add 'error' tag, only there are any.
	if ( m_nErrError > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_ERROR_ID ) );
	}

	// Add 'check error' tag, only there are any.
	if ( m_nErrCheck > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_CHECK_ID ) );
	}

	// Add 'fatal error' tag, only there are any.
	if ( m_nErrFatal > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_FATAL_ID ) );
	}

	// Add 'cluster error' tag, only there are any.
	if ( m_nErrCluster > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_CLUSTER_ID ) );
	}

	// Add 'internal error' tag, only there are any.
	if ( m_nErrIntern > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::ERR_INTERNAL_ID ) );
	}

	// Add 'errors at lines' tag, only there are any.
	if ( !m_vstrErrorLines.empty() )
	{
		sstrTags.insert( m_pReportList->GetText( ReportList::ERROR_AT_LINE_ID ) );
	}

	// Add 'number of checks' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::NUMCHECK_ID ) );

	// Add 'passed checks' tag, only if there any checks.
	if ( m_nChecks > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::NUMPASSEDCHK_ID ) );
	}

	// Add 'failed checks' tag, only if there any checks.
	if ( m_nChecks > 0 )
	{
		sstrTags.insert( INDENT + m_pReportList->GetText( ReportList::NUMFAILEDCHK_ID ) );
	}

	// Add 'checks at lines' tag, only there are any.
	if ( !m_vstrFailedCheckLines.empty() )
	{
		sstrTags.insert( m_pReportList->GetText( ReportList::FAIL_AT_LINE_ID ) );
	}

	// Add 'start time' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::STARTTIME_ID ) );

	// Add 'stop time' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::STOPTIME_ID ) );

	// Add 'time used' tag.
	sstrTags.insert( m_pReportList->GetText( ReportList::TIMEUSED_ID ) );

	// Determine the length of the longest of all these strings, and store it
	// in the outline member.
	m_nOutline = MaxLength( sstrTags );
}


//						==============================
void					ReportSummary::TestLineSection()
//						==============================
{
	// Create the 'number of test lines' line.
	NumberOfTestLines();

	// Add an empty line to the summary-vector.
	m_vstrSummary.push_back( "" );

	// Create the 'succeeded test lines' line.
	SucceededTestLines();
}


//						===========================
void					ReportSummary::ErrorSection()
//						===========================
{
	// Add an empty line to the summary-vector.
	m_vstrSummary.push_back( "" );

	// Create the 'number of errors' line.
	NumberOfErrors();

	// Create the 'warning' line.
	Warning();

	// Create the 'error' line.
	Error();

	// Create the 'check error' line.
	CheckError();

	// Create the 'fatal error' line.
	FatalError();

	// Create the 'cluster error' line.
	ClusterError();

	// Create the 'internal error' line.
	InternalError();

	// Create the 'errors on lines' line.
	ErrorsOnLine();
}


//						===========================
void					ReportSummary::CheckSection()
//						===========================
{
	// Add an empty line to the summary-vector.
	m_vstrSummary.push_back( "" );

	// Create the 'number of checks' line.
	NumberOfChecks();

	// Create the 'passed checks' line.
	PassedChecks();

	// Create the 'failed checks' line.
	FailedChecks();

	// Create the 'fails on lines' line.
	FailsOnLine();
}


//						==========================
void					ReportSummary::TimeSection()
//						==========================
{
	// Add an empty line to the summary-vector.
	m_vstrSummary.push_back( "" );

	// Create the 'start time' line.
	StartTime();

	// Create the 'stop time' line.
	StopTime();

	// Create the 'time used' line.
	TimeUsed();
}


//						================================
void					ReportSummary::NumberOfTestLines()
//						================================
{
	// Create the 'number of test lines' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::NUMTESTLINES_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Add the found number.
	strLine += IntToStr( m_nActionWords );

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						=================================
void					ReportSummary::SucceededTestLines()
//						=================================
{
	// Create the 'succeeded test lines' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::SUCC_LINES_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Determine the number of succeeded test lines by subtracted the number
	// of failed ones from the total number; determine the percentage.
	int nSucceeded = m_nActionWords - m_nFailedActionWords;
	int nPercentage = Percentage( nSucceeded, m_nActionWords );

	// Go to big-sized font.
	strLine += m_pReportTag->GetTag( ReportTag::BIG );

	// Based on the percentage, set the font colour to either green (100%)
	// or red (<100%).
	if ( nPercentage == 100 )
	{
		strLine += m_pReportTag->GetTag( ReportTag::GREEN );
	}
	else
	{
		strLine += m_pReportTag->GetTag( ReportTag::RED );
	}

	// Add the percentage to the line.
	strLine += IntToStr( nPercentage ) + "%";

	// Return to black, normal-sized font.
	strLine += m_pReportTag->GetTag( ReportTag::BLACK );
	strLine += m_pReportTag->GetTag( ReportTag::NORMALSIZE );

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						=============================
void					ReportSummary::NumberOfErrors()
//						=============================
{
	// Create the 'number of errors' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::NUMERROR_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Add the found number.
	strLine += IntToStr( m_nErrors );

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						======================
void					ReportSummary::Warning()
//						======================
{
	// Determine if there are any warnings.
	if ( m_nErrWarning > 0 )
	{
		// Create the 'warning' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_WARNING_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrWarning );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						====================
void					ReportSummary::Error()
//						====================
{
	// Determine if there are any errors of type 'error'.
	if ( m_nErrError > 0 )
	{
		// Create the 'error' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_ERROR_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrError );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						=========================
void					ReportSummary::CheckError()
//						=========================
{
	// Determine if there are any check errors.
	if ( m_nErrCheck > 0 )
	{
		// Create the 'check error' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_CHECK_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrCheck );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						=========================
void					ReportSummary::FatalError()
//						=========================
{
	// Determine if there are any fatal errors.
	if ( m_nErrFatal > 0 )
	{
		// Create the 'fatal error' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_FATAL_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrFatal );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						===========================
void					ReportSummary::ClusterError()
//						===========================
{
	// Determine if there are any cluster errors.
	if ( m_nErrCluster > 0 )
	{
		// Create the 'cluster error' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_CLUSTER_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrCluster );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						============================
void					ReportSummary::InternalError()
//						============================
{
	// Determine if there are any internal errors.
	if ( m_nErrIntern > 0 )
	{
		// Create the 'internal error' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::ERR_INTERNAL_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number.
		strLine += IntToStr( m_nErrIntern );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						===========================
void					ReportSummary::ErrorsOnLine()
//						===========================
{
	// Determine if there are any line numbers on which errors occurred.
	if ( !m_vstrErrorLines.empty() )
	{
		// Create the 'errors on lines' line, and add it to the vector.
		// Determine the tag.
		string strTag = m_pReportList->GetText( ReportList::ERROR_AT_LINE_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Create one string out of the elements of the set; use ", " to
		// separate the elements; add it to the line.
		strLine += VectorToStr( m_vstrErrorLines, ", " );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						=============================
void					ReportSummary::NumberOfChecks()
//						=============================
{
	// Create the 'number of checks' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::NUMCHECK_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Add the found number.
	strLine += IntToStr( m_nChecks );

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						===========================
void					ReportSummary::PassedChecks()
//						===========================
{
	// Determine if there are any checks.
	if ( m_nChecks > 0 )
	{
		// Create the 'passed checks' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::NUMPASSEDCHK_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number of passed checks.
		strLine += IntToStr( m_nChecksPassed );

		// Determine the percentage of failed checks.
		int nPercentage = Percentage( m_nChecksPassed, m_nChecks );
		string strPercentage = IntToStr( nPercentage ) + "%";

		// Add the percentage to the line, preceeded by two tabs, a possibly
		// some spaces to right-outline the percentages of passed and
		// failed checks.
		strLine += m_pReportTag->GetTag( ReportTag::TAB );
		strLine += m_pReportTag->GetTag( ReportTag::TAB );
		strLine += Spaces( 4 - strPercentage.length() );
		strLine += strPercentage;

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						===========================
void					ReportSummary::FailedChecks()
//						===========================
{
	// Determine if there are any checks.
	if ( m_nChecks > 0 )
	{
		// Create the 'failed checks' line, and add it to the vector.
		// Determine the tag; it has an indentation.
		string strTag = INDENT + m_pReportList->GetText( ReportList::NUMFAILEDCHK_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Add the found number of failed checks.
		strLine += IntToStr( m_nChecksFailed );

		// Determine the percentage of passed checks.
		int nPercentage = Percentage( m_nChecksFailed, m_nChecks );
		string strPercentage = IntToStr( nPercentage ) + "%";

		// Add the percentage to the line, preceeded by two tabs, a possibly
		// some spaces to right-outline the percentages of passed and
		// failed checks.
		strLine += m_pReportTag->GetTag( ReportTag::TAB );
		strLine += m_pReportTag->GetTag( ReportTag::TAB );
		strLine += Spaces( 4 - strPercentage.length() );
		strLine += strPercentage;

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						==========================
void					ReportSummary::FailsOnLine()
//						==========================
{
	// Determine if there are any line numbers on which checks failed.
	if ( !m_vstrFailedCheckLines.empty() )
	{
		// Create the 'errors on lines' line, and add it to the vector.
		// Determine the tag.
		string strTag = m_pReportList->GetText( ReportList::FAIL_AT_LINE_ID );

		// Add the tag, the number of spaces to outline, and a colon.
		string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

		// Create one string out of the elements of the vector; use ", " to
		// separate the elements; add it to the line.
		strLine += VectorToStr( m_vstrFailedCheckLines, ", " );

		// Add this line to the summary-vector.
		m_vstrSummary.push_back( strLine );
	}
}


//						========================
void					ReportSummary::StartTime()
//						========================
{
	// Create the 'start time' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::STARTTIME_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Get the starting date/time from the starting LogStructure; place
	// it in a string; add the found starting time to the line.
	strLine += m_pStartStruct->GetStartTime().Get();

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						=======================
void					ReportSummary::StopTime()
//						=======================
{
	// Create the 'stop time' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::STOPTIME_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Get the end date/time from the starting LogStructure; place
	// it in a string; add the found end time to the line.
	// Add the found end time to the line.
	strLine += m_pStartStruct->GetEndTime().Get();

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						=======================
void					ReportSummary::TimeUsed()
//						=======================
{
	// Create the 'time used' line, and add it to the vector.
	// Determine the tag.
	string strTag = m_pReportList->GetText( ReportList::TIMEUSED_ID );

	// Add the tag, the number of spaces to outline, and a colon.
	string strLine = strTag + Spaces( m_nOutline - strTag.length() ) + " : ";

	// Determine the difference between the end- and starting time.
	Duration durDiff = m_pStartStruct->GetEndTime() - m_pStartStruct->GetStartTime();

	// Place the time difference in a string, and add it to the line.
	strLine += durDiff.Get( "hh:mm:ss:nnn" );

	// Add this line to the summary-vector.
	m_vstrSummary.push_back( strLine );
}


//						=====================
string					ReportSummary::Spaces
//						=====================
(
	int					nSpaces
)
{
	string strResult;

	// Create a string consisting of the specified number of spaces.
	string::size_type nCurr = 0;
	for ( ; nCurr < nSpaces; nCurr++ )
	{
		strResult += " ";
	}

	return strResult;
}


//						=========================
int						ReportSummary::Percentage
//						=========================
(
	int					nPart,
	int					nTotal
)
{
	int nPerc = 0;

	// Determine if the total is greater than zero, and the part is less
	// than or equal to total.
	if ( nTotal > 0 && nPart <= nTotal )
	{
		// The percentage is rounded to the integer value less or equal to the
		// outcome of the percentage calculation.
		nPerc = (100 * nPart)/nTotal;

		// Check if the percentage should be rounded upward;
		// use the modulo for this.
		double dMod = (100 * nPart)%nTotal;
		if ( (dMod/nTotal) >= 0.5 )
		{
			nPerc++;
		}

		// Determine if the calculated percentage is 100, but the part is less
		// than the total.
		if ( nPerc == 100 && nPart < nTotal )
		{
			// Round the percentage downwards to 99.
			nPerc = 99;
		}
		// Determine if the percentage is zero, but the part is not zero.
		else if ( nPerc == 0 && nPart > 0 )
		{
			// Round the percentage upwards to 1.
			nPerc = 1;
		}
	}

	return nPerc;
}
