/*****************************************************************************
 * $Workfile: EngineSetting.cpp $
 * $Revision: 7 $
 * $Modtime: 3/29/01 10:24a $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "EngineSetting.h"			// Class definition

// Includes
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "IOInterface.h"			// Needed to write errors to error log
#include "IOFactory.h"				// Needed for I/O interface to ini file
#include "Setting.h"				// Baseclass definition
#include "Number.h"

#define BASECLASS Setting

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Default constructor
//						============================
						EngineSetting::EngineSetting()
//						============================
{ /* EMPTY */}


// Other constructors
//						============================
						EngineSetting::EngineSetting
//						============================
(
	const string&		strFileName	// name and path of the ini file containing
									//	the Engine's settings
) : Setting(strFileName)
{ /* EMPTY */}


// Destructor
//						=============================
						EngineSetting::~EngineSetting()
//						=============================
{ /* EMPTY */}


///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=======================
bool					EngineSetting::Validate()
//						=======================
{
	bool bResult = false;	// result of ValidateSettings

	// determine the validation of each section
	bool bCluster		= ValidateClusterSettings();
	bool bGUI			= ValidateGUISettings();
	bool bKeep			= ValidateKeepSettings();
	bool bLog			= ValidateLogSettings();
	bool bMasterSlave	= ValidateMasterSlaveSettings();
	bool bReport		= ValidateReportSettings();
	bool bSnap			= ValidateSnapSettings();
	bool bSystem		= ValidateSystemSettings();
	bool bTemplate		= ValidateTemplateSettings();
	
	bResult = bCluster && bGUI && bKeep && bLog && bMasterSlave && bReport
				&& bSnap && bSystem && bTemplate;

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						======================================
bool					EngineSetting::ValidateClusterSettings()
//						======================================
{
	bool bResult	= false;	// result of ValidateClusterSettings

	bool bFileName	= false;	// states if the file name is valid
	bool bPath		= false;	// states if the path is valid

	const string SECTION = "CLUSTER";

	// validate cluster file
	string strFileName = Get(SECTION, "FileName");
	if (!strFileName.empty())
	{
		bFileName = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [CLUSTER] FileName."), string("This value must not be empty."));
	}
	
	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [CLUSTER] Path."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bFileName && bPath;

	return bResult;
}


//						==================================
bool					EngineSetting::ValidateGUISettings()
//						==================================
{
	bool bResult	= false;	// result of ValidateGUISettings

	bool bDetail	= false;	// states if the detail setting is valid
	bool bLaunchGUI	= false;	// states if the setting for launching a GUI is valid
	bool bOnTop		= false;	// states if the OnTop setting is valid
	bool bPort		= false;	// states if the port is valid

	const string SECTION = "GUI";

	// validate detail
	string strDetail = Get(SECTION, "Detail");
	if (strDetail == "Yes")
	{
		bDetail = true;
	}
	else if (strDetail == "No")
	{
		bDetail = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [GUI] Detail."), string("This value must be either Yes or No."));
	}

	// validate launch GUI
	string strLaunchGUI = Get(SECTION, "LaunchGUI");
	if (strLaunchGUI == "Yes")
	{
		bLaunchGUI = true;
	}
	else if (strLaunchGUI == "No")
	{
		bLaunchGUI = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [GUI] LaunchGUI."), string("This value must be either Yes or No."));
	}
	
	// validate GUI on top
	string strOnTop = Get(SECTION, "OnTop");
	if (strOnTop == "Yes")
	{
		bOnTop = true;
	}
	else if (strOnTop == "No")
	{
		bOnTop = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [GUI] OnTop."), string("This value must be either Yes or No."));
	}
	
	// validate port
	string strPort = Get(SECTION, "Port");
	if (!strPort.empty())
	{
		bPort = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [GUI] Port."), string("This value must not be empty."));
	}
	
	// determine end result
	bResult = bDetail && bLaunchGUI && bOnTop && bPort;

	return bResult;
}


//						===================================
bool					EngineSetting::ValidateKeepSettings()
//						===================================
{
	bool bResult	= false;	// result of ValidateKeepSettings

	bool bFileName	= false;	// states if the file name is valid
	bool bPath		= false;	// states if the path is valid

	const string SECTION = "KEEP";

	// validate keep file
	string strFileName = Get(SECTION, "FileName");
	if (!strFileName.empty())
	{
		bFileName = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [KEEP] FileName."), string("This value must not be empty."));
	}
	
	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [KEEP] Path."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bFileName && bPath;

	return bResult;
}


//						==================================
bool					EngineSetting::ValidateLogSettings()
//						==================================
{
	bool bResult	= false;	// result of ValidateLogSettings

	bool bPath		= false;	// states if the path is valid

	const string SECTION = "LOG";
	
	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [LOG] Path."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bPath;

	return bResult;
}


//						==========================================
bool					EngineSetting::ValidateMasterSlaveSettings()
//						==========================================
{
	bool bResult	= false;	// result of ValidateMasterSlaveSettings

	bool bMode		= false;	// states if the mode is valid
	bool bPort		= false;	// states if the port is valid

	const string SECTION = "MASTERSLAVE";
	
	// validate mode
	string strMode = Get(SECTION, "Mode");
	if (strMode == "Standalone")
	{
		bMode = true;
	}
	else if (strMode == "Master")
	{
		bMode = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [MASTERSLAVE] Mode."), string("This value must be either Standalone or Master."));
	}

	// validate port
	string strPort = Get(SECTION, "Port");
	if (!strPort.empty())
	{
		bPort = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [MASTERSLAVE] Port."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bMode && bPort;

	return bResult;
}


//						=====================================
bool					EngineSetting::ValidateReportSettings()
//						=====================================
{
	bool bResult		= false;	// result of ValidateReportSettings

	bool bArguments		= false;	// states if the arguments setting is valid
	bool bFileName		= false;	// states if the file name is valid
	bool bOverwrite		= false;	// states if the overwrite setting is valid
	bool bPath			= false;	// states if the path is valid
	bool bTemplatePath	= false;	// states if the template path is valid

	const string SECTION = "REPORT";
	
	// validate arguments setting
	string strArguments = Get(SECTION, "Arguments");
	if (strArguments == "Yes")
	{
		bArguments = true;
	}
	else if (strArguments == "No")
	{
		bArguments = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [REPORT] Arguments."), string("This value must be either Yes or No."));
	}

	// validate file name
	string strFileName = Get(SECTION, "FileName");
	if (!strFileName.empty())
	{
		bFileName = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [REPORT] FileName."), string("This value must not be empty."));
	}

	// validate overwrite setting
	string strOverwrite = Get(SECTION, "Overwrite");
	if (strOverwrite == "Yes")
	{
		bOverwrite = true;
	}
	else if (strOverwrite == "No")
	{
		bOverwrite = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [REPORT] Overwrite."), string("This value must be either Yes or No."));
	}

	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [REPORT] Path."), string("This value must not be empty."));
	}

	// validate report template path
	string strTemplatePath = Get(SECTION, "TemplatePath");
	if (!strTemplatePath.empty())
	{
		bTemplatePath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [REPORT] TemplatePath."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bArguments && bFileName && bOverwrite && bPath && bTemplatePath;

	return bResult;
}


//						===================================
bool					EngineSetting::ValidateSnapSettings()
//						===================================
{
	bool bResult	= false;	// result of ValidateSnapSettings

	bool bFileName	= false;	// states if the file name is valid
	bool bPath		= false;	// states if the path is valid

	const string SECTION = "SNAP";

	// validate file name
	string strFileName = Get(SECTION, "FileName");
	if (!strFileName.empty())
	{
		bFileName = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SNAP] FileName."), string("This value must not be empty."));
	}
	
	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SNAP] Path."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bFileName && bPath;

	return bResult;
}


//						=====================================
bool					EngineSetting::ValidateSystemSettings()
//						=====================================
{
	bool bResult				= false;	// result of ValidateSystemSettings

	bool bLanguage				= false;	// states if the language is valid
	bool bPrecision				= false;	// states if the precision is valid
	bool bRedundantEscapeChars	= false;	// states if the redundant escape 
											//	characters are valid
	bool bWaitForGUI			= false;	// states if wait for GUI is valid
	bool bPrefixes				= false;	// states if the prefixes are valid

	const string SECTION = "SYSTEM";

	// validate language
	string strLanguage = Get(SECTION, "Language");
	if (   strLanguage == "GB" || strLanguage == "DE"
		|| strLanguage == "FR" || strLanguage == "NL"
		|| strLanguage == "LT" )
	{
		bLanguage = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] Language."), string("This value must be GB, DE, FR or NL."));
	}

	// Validate precision.
	string strPrecision = Get(SECTION, "Precision");
	if (!strPrecision.empty())
	{
		// Get latest character from string, and check if it one of:
		// e, E, f, g, G.
		char c = strPrecision[strPrecision.length() - 1];
		if ( c == 'e' || c == 'E' || c == 'f' || c == 'g' || c == 'G' )
		{
			// Check if the characters before the last one spell out an
			// integer in the range 0..15, or *.
			string strPrec = strPrecision.substr( 0, strPrecision.length() - 1 );
			Number num( strPrec );
			if ( num.IsInt() )
			{
				if ( num.GetNumValue() >= 0 && num.GetNumValue() <= 15 )
				{
					bPrecision = true;
				}
			}
			else if ( strPrec == "*" )
			{
				bPrecision = true;
			}
		}
	}

	if (!bPrecision )
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] Precision."), 
			string("This value must an integer in the range 0..15 or *, followed by e, E, f, g or G."));
	}

	// validate redundant escape characters
	// this value can contain any character or none at all
	bRedundantEscapeChars = true;

	// validate wait for GUI
	string strWaitForGUI = Get(SECTION, "WaitForGUI");
	if (strWaitForGUI == "Yes")
	{
		bWaitForGUI = true;
	}
	else if (strWaitForGUI == "No")
	{
		bWaitForGUI = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] WaitForGUI."), string("This value must be either Yes or No."));
	}

	// validate the system prefix settings
	bPrefixes = ValidateSystemPrefixes();

	// determine end result
	bResult = bLanguage && bPrecision && bRedundantEscapeChars
				&& bWaitForGUI && bPrefixes;

	return bResult;
}


//						=====================================
bool					EngineSetting::ValidateSystemPrefixes()
//						=====================================
{
	bool bResult			= false;	// result of ValidateSystemPrefixes

	bool bAnythingPrefix	= false;	// states if the anything prefix is valid
	bool bContText			= false;	// states if the continue token is valid
	bool bDatePrefix		= false;	// states if the date prefix is valid
	bool bTimePrefix		= false;	// states if the time prefix is valid
	bool bEmptyPrefix		= false;	// states if the empty prefix is valid
	bool bExpressionPrefix	= false;	// states if the expression prefix is valid
	bool bKeepPrefix		= false;	// states if the keep prefix is valid
	bool bNotEmptyPrefix	= false;	// states if the not-empty prefix is valid
	bool bSnapPrefix		= false;	// states if the snap prefix is valid
	bool bSpacesPrefix		= false;	// states if the spaces prefix is valid
	bool bReferPrefix		= false;	// states if the spaces prefix is valid

	const string SECTION = "SYSTEM";

	const string ANYTHINGPREFIX		= "AnythingPrefix";
	const string CONTTEXT			= "ContText";
	const string DATEPREFIX			= "DatePrefix";
	const string TIMEPREFIX			= "TimePrefix";
	const string EMPTYPREFIX		= "EmptyPrefix";
	const string EXPRESSIONPREFIX	= "ExpressionPrefix";
	const string KEEPPREFIX			= "KeepPrefix";
	const string NOTEMPTYPREFIX		= "NotEmptyPrefix";
	const string SNAPPREFIX			= "SnapPrefix";
	const string SPACESPREFIX		= "SpacesPrefix";
	const string REFERPREFIX		= "ReferPrefix";

	// validate anything prefix
	string strAnythingPrefix = Get(SECTION, ANYTHINGPREFIX);
	if (!strAnythingPrefix.empty())
	{
		bAnythingPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] AnythingPrefix."), string("This value must not be empty."));
	}

	// validate continue token
	string strContText = Get(SECTION, CONTTEXT);
	if (!strContText.empty())
	{
		bContText = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] ContText."), string("This value must not be empty."));
	}

	// validate date prefix
	string strDatePrefix = Get(SECTION, DATEPREFIX);
	if (!strDatePrefix.empty())
	{
		bDatePrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] DatePrefix."), string("This value must not be empty."));
	}

	// validate time prefix
	string strTimePrefix = Get(SECTION, TIMEPREFIX);
	if (!strTimePrefix.empty())
	{
		bTimePrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] TimePrefix."), string("This value must not be empty."));
	}

	// validate empty prefix
	string strEmptyPrefix = Get(SECTION, EMPTYPREFIX);
	if (!strEmptyPrefix.empty())
	{
		bEmptyPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] EmptyPrefix."), string("This value must not be empty."));
	}

	// validate expression prefix
	string strExpressionPrefix = Get(SECTION, EXPRESSIONPREFIX);
	if (!strExpressionPrefix.empty())
	{
		bExpressionPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] ExpressionPrefix."), string("This value must not be empty."));
	}

	// validate refer prefix, same semantics as expression
	string strReferPrefix = Get(SECTION, REFERPREFIX);
	if (!strReferPrefix.empty())
	{
		bReferPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] ReferPrefix."), string("This value must not be empty."));
	}

	// validate keep prefix
	string strKeepPrefix = Get(SECTION, KEEPPREFIX);
	if (!strKeepPrefix.empty())
	{
		bKeepPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] KeepPrefix."), string("This value must not be empty."));
	}

	// validate not-empty prefix
	string strNotEmptyPrefix = Get(SECTION, NOTEMPTYPREFIX);
	if (!strNotEmptyPrefix.empty())
	{
		bNotEmptyPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] NotEmptyPrefix."), string("This value must not be empty."));
	}

	// validate snap prefix
	string strSnapPrefix = Get(SECTION, SNAPPREFIX);
	if (!strSnapPrefix.empty())
	{
		bSnapPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] SnapPrefix."), string("This value must not be empty."));
	}

	// validate spaces prefix
	string strSpacesPrefix = Get(SECTION, SPACESPREFIX);
	if (!strSpacesPrefix.empty())
	{
		bSpacesPrefix = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [SYSTEM] SpacesPrefix."), string("This value must not be empty."));
	}

	// determine intermediate result
	bResult = bAnythingPrefix && bContText && bDatePrefix && bTimePrefix
				&& bEmptyPrefix	&& bExpressionPrefix && bKeepPrefix
				&& bNotEmptyPrefix && bSnapPrefix && bSpacesPrefix;

	if (bResult)
	{
		// create map of prefix descriptions/values
		typedef map<string, string> PrefixMap;
		PrefixMap mPrefixes;
		mPrefixes[ANYTHINGPREFIX]	= strAnythingPrefix;
		mPrefixes[CONTTEXT]			= strContText;
		mPrefixes[DATEPREFIX]		= strDatePrefix;
		mPrefixes[TIMEPREFIX]		= strTimePrefix;
		mPrefixes[EMPTYPREFIX]		= strEmptyPrefix;
		mPrefixes[EXPRESSIONPREFIX]	= strExpressionPrefix;
		mPrefixes[KEEPPREFIX]		= strKeepPrefix;
		mPrefixes[NOTEMPTYPREFIX]	= strNotEmptyPrefix;
		mPrefixes[SNAPPREFIX]		= strSnapPrefix;
		mPrefixes[SPACESPREFIX]		= strSpacesPrefix;

		// create vector of prefix values
		vector<string> vstrPrefixes;
		PrefixMap::iterator Iterator = mPrefixes.begin();
		while (Iterator != mPrefixes.end())
		{
			vstrPrefixes.push_back((Iterator++)->second);
		}

		// check prefix values for uniqueness
		set<int> snAmbiguousIndices;		// set of indices of vector elements
											//	that are not unique
		if (!IsUnique(vstrPrefixes, snAmbiguousIndices))
		{
			bResult = false;

			// determine descriptions of ambiguous prefixes
			string	strAmbiguous;

			// take each of the indices of ambiguous element and add its
			// corresponding prefix name to the report string
			PrefixMap::iterator FirstPrefix = mPrefixes.begin();
			set<int>::iterator IndexIter = snAmbiguousIndices.begin();
			while (IndexIter != snAmbiguousIndices.end())
			{
				// determine (next) index number from set
				int nIndex = *(IndexIter++);
				// determine iterator to corresponding map element
				Iterator = FirstPrefix;
				for (int i = 0; i < nIndex; i++)
				{ Iterator++; }
				// get prefix name and add it to report string
				string strPrefixName = Iterator->first;
				strAmbiguous += (string(" ") + strPrefixName);
			}

			// write error to log
			IOInterface::WriteIOError(string("Ini file"), string("Not all prefix values in [SYSTEM] are unique."), string("Ambiguous prefixes:"+ strAmbiguous +"."));
		}
	}

	return bResult;
}


//						=======================================
bool					EngineSetting::ValidateTemplateSettings()
//						=======================================
{
	bool bResult	= false;	// result of ValidateTemplateSettings

	bool bPath		= false;	// states if the path is valid

	const string SECTION = "TEMPLATE";
	
	// validate path
	string strPath = Get(SECTION, "Path");
	if (!strPath.empty())
	{
		bPath = true;
	}
	else
	{
		// write error to log
		IOInterface::WriteIOError(string("Ini file"), string("Invalid value for [TEMPLATE] Path."), string("This value must not be empty."));
	}

	// determine end result
	bResult = bPath;

	return bResult;
}


//							=======================
bool						EngineSetting::IsUnique
//							=======================
(
	const vector<string>&	vstrTexts,			// vector containing the strings that
												//	are to be checked for uniqueness
	set<int>&				snAmbiguousIndices	// to be filled with the vector indices
												//	of the elements that are not unique
)
{
	bool bResult = true;	// result of CheckForUniqueness

	// clear set of ambiguous indices before use
	snAmbiguousIndices.clear();

	// check all vector elements against each other
	int nSize = vstrTexts.size();
	for (int i = 0; i < (nSize - 1); i++)
	{
		for (int j = i + 1; j < nSize; j++)
		{
			if (vstrTexts[i] == vstrTexts[j])
			{
				// elements i anf j are not unique
				bResult = false;
				// add indices of ambiguous elements to the set
				snAmbiguousIndices.insert(i);
				snAmbiguousIndices.insert(j);
			}
		}
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////