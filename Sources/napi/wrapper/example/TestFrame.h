/*****************************************************************************
 * $Workfile: TestFrame.h $
 * $Revision: 2 $
 * $Modtime: 01/16/06 2:47p $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2006 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#ifndef TESTFRAME_H
#define TESTFRAME_H


#include <string>				// Strings from the Standard Template Library
using namespace std;



///////////////////////////////////////////////////////////////////////////////
// Function:		ProcessCluster
// Description:		This function starts the engine, processes a cluster and 
//					generates a report
//
// Parameters:		strClusterFile		Cluster file
//					strReportFile		Report file
//					strIniFile			Engine ini file
//
// Returns:			true				Cluster successfully processed
//					false				Cluster unsuccessfully processed
///////////////////////////////////////////////////////////////////////////////
bool ProcessCluster(const string& strClusterFile, const string& strReportFile, const string& strIniFile);

///////////////////////////////////////////////////////////////////////////////
// Function:		ProcessIniFile
// Description:		This function processes the inifile and fills the names of
//					the cluster, report and library.
//
// Parameters:		strFileName			Name of the inifile to process
//					strCluster			Will be filled with the name of
//										the cluster
//					strReport			Will be filled with the name of
//										the report
//					strIniFile			Will be filled with the name of
//										the Engine 5 ini file
//					strLibrary			Will be filled with the name of
//										the NAPI libraries
//
// Returns:			true				Inifile processed
//					false				Inifile not processed
///////////////////////////////////////////////////////////////////////////////
bool ProcessIniFile(const string& strFileName, string& strCluster, string& strReport, string& strIniFile, string& strLibrary);


///////////////////////////////////////////////////////////////////////////////
// Function:		LoadLibraries
// Description:		This function loads the NAPI libraries listed in the string
//					that is supplied to this function.
//
// Parameters:		strLibraryNames		String with the names of the libraries
//										to load, separated with semicolons.
//
// Returns:			true				All libraries loaded
//					false				Not all libraries could be loaded
///////////////////////////////////////////////////////////////////////////////
bool LoadLibraries(const string& strLibraryNames);

///////////////////////////////////////////////////////////////////////////////
// Function:		FreeLibraries
// Description:		This function frees the NAPI libraries listed in the string
//					that is supplied to this function.
//
// Parameters:		strLibraryNames		String with the names of the libraries
//										to free, separated with semicolons.
//
// Returns:			true				All libraries freed
//					false				Not all libraries could be freed
///////////////////////////////////////////////////////////////////////////////
bool FreeLibraries(const string& strLibraryNames);

///////////////////////////////////////////////////////////////////////////////
// Function:		ShowErrorMessage
// Description:		This function shows a message box with an error message
//
// Parameters:		strError			Error message
//
// Returns:			true				Message shown
//					false				Message not shown
///////////////////////////////////////////////////////////////////////////////
bool ShowErrorMessage(const string& strError);

///////////////////////////////////////////////////////////////////////////////

#endif // !TESTFRAME_H
