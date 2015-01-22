/*****************************************************************************
 * $Workfile: EngineSetting.h $
 * $Revision: 1 $
 * $Modtime: 17-03-00 16:26 $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGINESETTING_H
#define ENGINESETTING_H

#undef BASECLASS
#define BASECLASS Setting

// Includes
#include <set>
#include <string>
#include <vector>

using namespace std;

#include "Setting.h"			// Baseclass definition

////////////////////////////////////////////////////////////////////////////////
// class EngineSetting

class EngineSetting : public BASECLASS
{

// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// default constructor of EngineSetting
	///////////////////////////////////////////////////////////////////////////////
	EngineSetting();

	///////////////////////////////////////////////////////////////////////////////
	// constructor of EngineSetting
	//
	// parameters	: strFileName		name of ini file containing the engine's
	//									settings
	///////////////////////////////////////////////////////////////////////////////
	explicit EngineSetting(const string& strFileName);	

	///////////////////////////////////////////////////////////////////////////////
	// destructor of EngineSetting
	///////////////////////////////////////////////////////////////////////////////
	~EngineSetting();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: Validate
	//
	// description	: This function checks if the settings from the engine ini file
	//				  are valid. For each invalid setting an error is sent to
	//				  error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all settings are valid
	//				  FALSE		at least one setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool Validate();

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateClusterSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section CLUSTER are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all cluster settings are valid
	//				  FALSE		at least one cluster setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateClusterSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateGUISettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section GUI are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all GUI settings are valid
	//				  FALSE		at least one GUI setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateGUISettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateKeepSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section KEEP are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all keep settings are valid
	//				  FALSE		at least one keep setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateKeepSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateLogSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section LOG are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all log settings are valid
	//				  FALSE		at least one log setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateLogSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateMasterSlaveSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section MASTERSLAVE are valid. For each invalid
	//				  setting an error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all master/slave settings are valid
	//				  FALSE		at least one master/slave setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateMasterSlaveSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateReportSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section REPORT are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all report settings are valid
	//				  FALSE		at least one report setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateReportSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateSnapSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section SNAP are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all snap settings are valid
	//				  FALSE		at least one snap setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateSnapSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateSystemSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section SYSTEM are valid. For each invalid setting an
	//				  error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all system settings are valid
	//				  FALSE		at least one system setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateSystemSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateSystemPrefixes
	//
	// description	: This function checks if the prefix settings from the engine
	//				  ini file in the section SYSTEM are valid. For each invalid
	//				  prefix an error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all prefix settings are valid
	//				  FALSE		at least one prefix setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateSystemPrefixes();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ValidateTemplateSettings
	//
	// description	: This function checks if the settings from the engine ini file
	//				  in the section TEMPLATE are valid. For each invalid setting
	//				  an error is sent to error.log.
	//				  
	// parameters	: none
	//
	// returns		: TRUE		all template settings are valid
	//				  FALSE		at least one template setting is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool ValidateTemplateSettings();

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsUnique
	//
	// description	: This function checks if the strings in a specified vector
	//				  are all unique. If not, the second parameter is filled with
	//				  the indices of the vector that are not unique.
	//				  
	// parameters	: vstrTexts					vector containing the strings that
	//											are to be checked for uniqueness
	//				  REF snAmbiguousIndices	to be filled with the vector indices
	//											of the elements that are not unique
	//
	// returns		: TRUE		all vector elements are unique
	//				  FALSE		not all vector elements are unique
	///////////////////////////////////////////////////////////////////////////////
	bool IsUnique(const vector<string>& vstrTexts, set<int>& snAmbiguousIndices);

// Class constants
private:

// Member variables
private:

};

////////////////////////////////////////////////////////////////////////////////

#undef BASECLASS
#endif // !ENGINESETTING_H
