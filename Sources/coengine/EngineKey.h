/*****************************************************************************
 * $Workfile: EngineKey.h $
 * $Revision: 1 $
 * $Modtime: 25-04-01 17:01 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef ENGINEKEY_H
#define ENGINEKEY_H

#include <string>
using namespace std;

#include "Key.h"
///////////////////////////////////////////////////////////////////////////////
// Class EngineKey

class EngineKey : public Key
{
// Construction and destruction
public:
	EngineKey();
	virtual~EngineKey();

// Attributes and operations
public:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	Encrypt
	// Description: This function encrypts all the data inside the key. The result 
	//				is stored and can be retrieved with the GetEncrypted member 
	//				function.
	//
	// Parameters:	-
	//
	// Returns:		true	Encryption succeeded
	//				false	Encryption failed
	///////////////////////////////////////////////////////////////////////////////
	bool Encrypt();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Decrypt
	// Description: This function decrypts all the data inside the key. The results 
	//				are stored and can be retrieved with the GetXXX member 
	//				functions. The string to decrypt can be set with the 
	//				SetEncrypted member function.
	//
	// Parameters:	-
	//
	// Returns:		true	Decryption succeeded
	//				false	Decryption failed
	///////////////////////////////////////////////////////////////////////////////
	bool Decrypt();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetCustomerName
	// Description: This function sets the customer name.
	//
	// Parameters:	strCustomerName			Customer name
	//
	// Returns:		true	Customer name set
	//				false	Customer name not set
	///////////////////////////////////////////////////////////////////////////
	bool SetCustomerName(const string& strCustomerName);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetCustomerName
	// Description: This function retrieves the customer name.
	//
	// Parameters:	-			
	//
	// Returns:		Customer name
	///////////////////////////////////////////////////////////////////////////
	string GetCustomerName();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetCompanyName
	// Description: This function sets the company name.
	//
	// Parameters:	strCompanyName			Company name
	//
	// Returns:		true	Company name set
	//				false	Company name not set
	///////////////////////////////////////////////////////////////////////////
	bool SetCompanyName(const string& strCompanyName);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetCompanyName
	// Description: This function retrieves the company name.
	//
	// Parameters:	-			
	//
	// Returns:		Company name
	///////////////////////////////////////////////////////////////////////////
	string GetCompanyName();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetLicenseNumber
	// Description: This function sets the license number, consisting of 
	//				the engine version, the serial number, the customer type 
	//				and the license type.
	//
	// Parameters:	strLicenseNumber		License number
	//
	// Returns:		true	License number set
	//				false	License number not set
	///////////////////////////////////////////////////////////////////////////
	bool SetLicenseNumber(const string& strLicenseNumber);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetLicenseNumber
	// Description: This function retrieves the license number.
	//
	// Parameters:	-			
	//
	// Returns:		License number
	///////////////////////////////////////////////////////////////////////////
	string GetLicenseNumber();
	
	///////////////////////////////////////////////////////////////////////////
	// Function:	SetEngineVersion
	// Description: This function sets the engine version.
	//
	// Parameters:	strEngineVersion		Engine version
	//
	// Returns:		true	Engine version set
	//				false	Engine version not set
	///////////////////////////////////////////////////////////////////////////
	bool SetEngineVersion(const string& strEngineVersion);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetEngineVersion
	// Description: This function retrieves the engine version.
	//
	// Parameters:	-			
	//
	// Returns:		Engine version
	///////////////////////////////////////////////////////////////////////////
	string GetEngineVersion();

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckEngineVersion
	// Description: This function checks the format of the passed engine
	//				version.
	//
	// Parameters:	strEngineVersion		Engine version
	//
	// Returns:		true	Engine version correct
	//				false	Engine version incorrect
	///////////////////////////////////////////////////////////////////////////
	bool CheckEngineVersion(const string& strEngineVersion);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetSerialNumber
	// Description: This function sets the license serial number.
	//
	// Parameters:	strSerialNumber			Serial number
	//
	// Returns:		true	Serial number set
	//				false	Serial number not set
	///////////////////////////////////////////////////////////////////////////
	bool SetSerialNumber(const string& strSerialNumber);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetSerialNumber
	// Description: This function retrieves the serial number.
	//
	// Parameters:	-			
	//
	// Returns:		Serial number
	///////////////////////////////////////////////////////////////////////////
	string GetSerialNumber();

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckSerialNumber
	// Description: This function checks the format of the passed serial
	//				number.
	//
	// Parameters:	strSerialNumber		Serial number
	//
	// Returns:		true	Serial number correct
	//				false	Serial number incorrect
	///////////////////////////////////////////////////////////////////////////
	bool CheckSerialNumber(const string& strSerialNumber);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetCustomerType
	// Description: This function sets the customer type.
	//
	// Parameters:	strCustomerType			Customer type
	//
	// Returns:		true	Customer type set
	//				false	Customer type not set
	///////////////////////////////////////////////////////////////////////////
	bool SetCustomerType(const string& strCustomerType);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetCustomerType
	// Description: This function retrieves the customer type.
	//
	// Parameters:	-			
	//
	// Returns:		Customer type
	///////////////////////////////////////////////////////////////////////////
	string GetCustomerType();

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckCustomerType
	// Description: This function checks the format of the passed customer
	//				type string.
	//
	// Parameters:	strCustomerType		Customer type
	//
	// Returns:		true	Customer type correct
	//				false	Customer type incorrect
	///////////////////////////////////////////////////////////////////////////
	bool CheckCustomerType(const string& strCustomerType);

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetLicenseType
	// Description: This function sets the license type.
	//
	// Parameters:	strLicenseType			License type
	//
	// Returns:		true	License type set
	//				false	License type not set
	///////////////////////////////////////////////////////////////////////////
	bool SetLicenseType(const string& strLicenseType);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetLicenseType
	// Description: This function retrieves the license type.
	//
	// Parameters:	-			
	//
	// Returns:		License type
	///////////////////////////////////////////////////////////////////////////
	string GetLicenseType();

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckLicenseType
	// Description: This function checks the format of the passed license 
	//				type string.
	//
	// Parameters:	strLicenseType		License type
	//
	// Returns:		true	License type correct
	//				false	License type incorrect
	///////////////////////////////////////////////////////////////////////////
	bool CheckLicenseType(const string& strLicenseType);

// Implementation
private:
	///////////////////////////////////////////////////////////////////////////
	// Function:	ComposeData
	// Description: This function combines all the license data, garbles it 
	//				and sets it in the data member of the key baseclass.
	//
	// Parameters:	-
	//
	// Returns:		true	Data composed
	//				false	Data not composed
	///////////////////////////////////////////////////////////////////////////
	bool ComposeData();

	///////////////////////////////////////////////////////////////////////////
	// Function:	DecomposeData
	// Description: This function retrieves the data from the key baseclass, 
	//				degarbles it and stores all the license data in the 
	//				member variables.
	//
	// Parameters:	-
	//
	// Returns:		true	Data decomposed
	//				false	Data not decomposed
	///////////////////////////////////////////////////////////////////////////
	bool DecomposeData();

// Member variables
private:
	string m_strCustomerName;
	static int m_nMaxCustomerNameLength;

	string m_strCompanyName;
	static int m_nMaxCompanyNameLength;

	static int m_nMaxLicenseNumberLength;

	string m_strSerialNumber;
	static int m_nMaxSerialNumberLength;

	string m_strEngineVersion;
	static int m_nMaxEngineVersionLength;
	
	string m_strCustomerType;
	static int m_nMaxCustomerTypeLength;

	string m_strLicenseType;
	static int m_nMaxLicenseTypeLength;
};

///////////////////////////////////////////////////////////////////////////////

#endif // !ENGINEKEY_H
