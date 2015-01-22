/*****************************************************************************
 * $Workfile: ReportGenerator.cpp $
 * $Revision: 1 $
 * $Modtime: 8/22/01 6:16p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "ReportGenerator.h"		// Class definition

#include <string>

using namespace std;

#include "EngineSetting.h"
#include "FileName.h"
#include "LogProcessor.h"
#include "LogStructure.h"
#include "Report.h"
#include "ReportList.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//						================================
						ReportGenerator::ReportGenerator()
//						================================
{
	// Set default values for members.
	m_pLogProcessor = new LogProcessor();
	m_pReportList = new ReportList();
	m_pReport = new Report();
	m_pSetting = 0;
	m_pMainCluster = 0;
}

//						=================================
						ReportGenerator::~ReportGenerator()
//						=================================
{
	delete m_pReportList;
	delete m_pLogProcessor;
	delete m_pReport;

	m_pReportList=0;
	m_pLogProcessor=0;
	m_pReport=0;

	// Delete the main cluster-LogStructure (which will delete all its
	// children).
	if ( m_pMainCluster != 0 )
	{
		delete m_pMainCluster;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Public interface

//						======================
bool					ReportGenerator::Start
//						======================
(
	const string&		strLog,
	EngineSetting*		pSetting,
	const string&		strMainReport
)
{
	bool bResult = false;

	// Only start if the specified Setting object exists.
	if ( pSetting != 0 )
	{
		// Set the number of generated reports (original and substitute)
		// to zero, and clear the map of reports.
		m_nReports = 0;
		m_nSubstitutes = 0;
		m_mReports.clear();

		// Set the log-file member, settings-member, and main report file member.
		m_strLogFile = strLog;
		m_pSetting = pSetting;
		m_strMainReport = strMainReport;

		// Set the language of the ReportList.
		m_pReportList->SetLanguage( m_pSetting->Get( "SYSTEM", "Language" ) );

		// Process the log file, and get the pointer to the 
		// main cluster-LogStructure.
		m_pMainCluster = m_pLogProcessor->StartProcessing( strLog, m_pReportList );
		
		// Determine if a main cluster has been found.
		if ( m_pMainCluster != 0 )
		{
			// Get the map with report/LogStructure pairs.
			m_mReports = m_pLogProcessor->GetReports();

			// Create a report file for each of the specified reports.
			CreateReports();

			// Determine the number of reports that had to be generated.
			int nTotalReports = 0;
			if ( !m_mReports.empty() )
			{
				nTotalReports = m_mReports.size();
			}

			// Determine if the number of original reports that are generated,
			// is the same as the number of reports that had to be generated.
			if ( m_nReports == nTotalReports )
			{
				bResult = true;
			}
		}
	}

	return bResult;
}


//						======================
bool					ReportGenerator::Start
//						======================
(
	const string&		strLog,
	EngineSetting*		pSetting
)
{
	// Call the overloaded variant; set the main report file to
	// be an empty string.
	return Start( strLog, pSetting, "" );
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						==============================
void					ReportGenerator::CreateReports()
//						==============================
{
	// Go passed all reports in the map returned by LogProcessor.
	map<string, LogStructure*>::iterator Iterator = m_mReports.begin();
	for ( ; Iterator != m_mReports.end(); Iterator++ )
	{
		// Determine the report name and corresponding starting LogStructure.
		string strOriginal = Iterator->first;
		LogStructure* pStartLogStruct = Iterator->second;

		// Set the file name to create to be the same as the file name
		// specified in the log.
		string strFile = strOriginal;

		// Determine if we are dealing with the main cluster.
		if ( pStartLogStruct == m_pMainCluster )
		{
			// Determine if the forced main report file name is not empty.
			if ( !m_strMainReport.empty() )
			{
				// Set the file name to create to be the one specified
				// by the member.
				strFile = m_strMainReport;
			}
		}

		// Initialise the Report object, and determine if this was successful.
		if ( m_pReport->Initialise( m_strLogFile, pStartLogStruct, m_pSetting ) )
		{
			// Create the specified report; determine if this was successful.
			if ( m_pReport->CreateReport( strFile, strOriginal ) )
			{
				// Update the number of generated original reports.
				m_nReports++;
			}
			else
			{
				// Since the specified report could not be written, create a
				// substitute report for it.
				CreateSubstituteReport( strOriginal );
			}
		}
	}
}


//						=======================================
bool					ReportGenerator::CreateSubstituteReport
//						=======================================
(
	const string&		strReport
)
{
	bool bResult = false;

	// Take the specified report file; change its location to an empty
	// string, so the working directory is taken.
	FileName fnReport( strReport );
	fnReport.ChangeLocation( "" );

	// Change the name of the file to the original name following by a time
	// stamp consting of date and time.
	DateTime dtNow;
	fnReport.ChangeName( fnReport.GetName() + dtNow.Get( "@YYYYMMDD_hhmmss" ) ); 

	// Create a report with this file name; note that the Report object must
	// already have been initialised.
	if ( m_pReport->CreateReport( fnReport.GetFile(), strReport ) )
	{
		// Update the number of substitute reports.
		m_nSubstitutes++;
		bResult= true;
	}

	return bResult;
}
