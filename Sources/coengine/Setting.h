/*****************************************************************************
 * $Workfile: Setting.h $
 * $Revision: 6 $
 * $Modtime: 8/15/01 5:28p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef SETTING_H
#define SETTING_H

// Includes
#include <map>
#include <string>
#include <vector>

using namespace std;

// Forward declarations
class IOInterface;

////////////////////////////////////////////////////////////////////////////////
// class Setting

class Setting
{

// Construction and destruction
public:
	Setting();						// Default constructor

	virtual ~Setting();				// Destructor

	// Other constructors
	explicit Setting(const std::string& strFileName);	

private:
	Setting(const Setting& src){};
	Setting& operator=(const Setting& src){};

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetFileName(const std::string& strFileName)
	//
	// description	: Sets the location and the name of the file used
	//					
	// parameters	: strFileName	location and name of file
	//
	// returns		: <void>
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetFileName(const std::string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetFileName()
	//
	// description	: Returns the location and name of the file used
	//					
	// parameters	: None
	//
	// returns		: <string>	location and name of file	
	//				  
	///////////////////////////////////////////////////////////////////////////////
	std::string GetFileName() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: Import()
	//
	// description	: Imports all settings from specified file.
	//					
	// parameters	: None.
	//
	// returns		: true			Import succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Import();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Import(const std::string& strFileName)
	//
	// description	: Imports all settings from specified file.
	//					
	// parameters	: strFileName	location and name of file
	//
	// returns		: true			Import succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Import(const std::string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Export()
	//
	// description	: Exports all settings to specified file.
	//				  
	// parameters	: None.
	//
	// returns		: true			Export succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Export();

	///////////////////////////////////////////////////////////////////////////////
	// function		: Export(const std::string& strFileName)
	//
	// description	: Exports all settings to specified file.
	//				  
	// parameters	: strFileName	location and name of file
	//
	// returns		: true			Export succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Export(const std::string& strFileName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Get(const std::string& strSection, const std::string& strKey)
	//
	// description	: Retreives the Value belonging to the Section-Key combination.
	//				  An empty string is returned when the Section-Key combination
	//				  is non existent.
	//
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//
	// returns		: Value of type std::string.
	//
	///////////////////////////////////////////////////////////////////////////////
	std::string Get(const std::string& strSection, const std::string& strKey);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Set(const std::string& strSection, const std::string& strKey, const std::string& strValue)
	//
	// description	: Updates Value of specified Section-Key combination.
	//				  When non existent, the Section-Key-Value values are added. 
	//
	//					
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//				  strValue		const std::string&.
	//
	// returns		: true			Value succesfully updated or added.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Set(const std::string& strSection, const std::string& strKey, const std::string& strValue);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Update(const std::string& strSection, const std::string& strKey, const std::string& strValue)
	//
	// description	: Updates Value of specified Section-Key combination.
	//				  
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//				  strValue		const std::string&.
	//
	// returns		: true			Update succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Update(const std::string& strSection, const std::string& strKey, const std::string& strValue);
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Find(const std::string& strSection, const std::string& strKey)
	//
	// description	: Checks if specified Section-Key combination exists
	//				  
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//
	// returns		: true			Section-Key combination found.
	//				  false			Section-Key combination not found.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Find(const std::string& strSection, const std::string& strKey);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Add(const std::string& strSection, const std::string& strKey, const std::string& strValue)
	//
	// description	: Adds the Key-Value pair to the specified Section,
	//				  Section will be created when non existent.
	//					
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//				  strValue		const std::string&.
	//
	// returns		: true			Addition succesfull.
	//				  false			An error occurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Add(const std::string& strSection, const std::string& strKey, const std::string& strValue);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Remove(const std::string& strSection, const std::string& strKey)
	//
	// description	: Removes Key-Value pair from specified Section-Key combination.
	//				  Removal failes when combination does not exist.
	//
	// parameters	: strSection	const std::string&.
	//				  strKey		const std::string&.
	//
	// returns		: true			Removal succesfull.
	//				  false			Removal failed.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool Remove(const std::string& strSection, const std::string& strKey);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SaveOnChange(bool bValue)
	//
	// description	: Manipulation of the SaveOnChange flag.
	//
	// parameters	: bValue	boolean flag.
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SaveOnChange(bool bValue);

	///////////////////////////////////////////////////////////////////////////////
	// function		:	GetAllSettings()
	//
	// description	:	This functions returns a vector containing all settings in
	//					this object
	//
	// parameters	:	-
	//
	// returns		:	vector containing the settings
	///////////////////////////////////////////////////////////////////////////////
	vector<pair<pair<string, string>, string> > GetAllSettings();

	// Implementation
private:

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteFile2Map()
	//
	// description	: Imports all settings from specified file.
	//					
	// parameters	: None.
	//
	// returns		: true			Import succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool WriteFile2Map();

	///////////////////////////////////////////////////////////////////////////////
	// function		: WriteMap2File()
	//
	// description	: Exports all settings to specified file.
	//				  
	// parameters	: None.
	//
	// returns		: true			Export succesfull.
	//				  false			An error ocurred.
	//
	///////////////////////////////////////////////////////////////////////////////
	bool WriteMap2File();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ToUpper(std::string strSrc)
	//
	// description	: Converts a string to uppercase.
	//
	// parameters	: strSrc	source string.
	//
	// returns		: To UPPERCASE converted std::string.
	//
	///////////////////////////////////////////////////////////////////////////////
	std::string ToUpper(std::string strSrc);

	// Class constants
private:
	// Definition of string pair, to be used for storing section-key combinations
	typedef std::pair<std::string, std::string> STR2STRPAIR; 
	// Definition of map containing a string pair as the Map-Key
	// and a string as the Map-Value, to be used for storing section-key-value
	// combinations.
	typedef std::map<STR2STRPAIR, std::string> PAIR2STRMAP;
	// Constant containing file-extension for backup files
	static const std::string BACKUP;

	// Member variables
protected:
	IOInterface*	m_pIOInterface;		// Interface to io layer	
	std::string		m_strFileName;		// Location and name of file.
	PAIR2STRMAP		m_SettingMap;		// Container of section-key-value combnations
	bool			m_bSaveOnChange;	// Save on change flag.
};

////////////////////////////////////////////////////////////////////////////////

#endif // !SETTING_H
