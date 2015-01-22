/*****************************************************************************
 * $Workfile: ComponentKey.h $
 * $Revision: 1 $
 * $Modtime: 25-04-01 17:01 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef COMPONENTKEY_H
#define COMPONENTKEY_H

#include <vector>
#include <string>

#include "Key.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
// Class ComponentKey

class ComponentKey : public Key
{
// Construction and destruction
public:
	ComponentKey();
	virtual~ComponentKey();

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
	// Function:	SetComponentName
	// Description: This function sets the component name.
	//
	// Parameters:	strComponentName		Component name
	//
	// Returns:		true	Component name set
	//				false	Component name not set
	///////////////////////////////////////////////////////////////////////////
	bool SetComponentName(const string& strComponentName);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetComponentName
	// Description: This function retrieves the component name.
	//
	// Parameters:	-			
	//
	// Returns:		Component name
	///////////////////////////////////////////////////////////////////////////
	string GetComponentName();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetEngineLicenseNumber
	// Description: This function sets the engine license number.
	//
	// Parameters:	strEngineLicenseNumber	Engine license number
	//
	// Returns:		true	Engine license number set
	//				false	Engine license number not set
	///////////////////////////////////////////////////////////////////////////
	bool SetEngineLicenseNumber(const string& strEngineLicenseNumber);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetLicenseNumber
	// Description: This function retrieves the license number.
	//
	// Parameters:	-			
	//
	// Returns:		License number
	///////////////////////////////////////////////////////////////////////////
	string GetEngineLicenseNumber();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetReserved
	// Description: This function sets the reserved data. In the component key 
	//				there is still room for future expansions.
	//
	// Parameters:	strReserved				Reserved data
	//
	// Returns:		true	Reserved data set
	//				false	Reserved data not set
	///////////////////////////////////////////////////////////////////////////
	bool SetReserved(const string& strReserved);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetReservedData
	// Description: This function retrieves the reserved data.
	//
	// Parameters:	-			
	//
	// Returns:		Reserved data
	///////////////////////////////////////////////////////////////////////////
	string GetReserved();

	///////////////////////////////////////////////////////////////////////////
	// Function:	SetLicenseNumber
	// Description: This function sets the license number, consisting of 
	//				the component version, the serial number, the customer type 
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
	// Function:	SetComponentVersion
	// Description: This function sets the component version.
	//
	// Parameters:	strComponentVersion		Component version
	//
	// Returns:		true	Component version set
	//				false	Component version not set
	///////////////////////////////////////////////////////////////////////////
	bool SetComponentVersion(const string& strComponentVersion);

	///////////////////////////////////////////////////////////////////////////
	// Function:	GetComponentVersion
	// Description: This function retrieves the component version.
	//
	// Parameters:	-			
	//
	// Returns:		Component version
	///////////////////////////////////////////////////////////////////////////
	string GetComponentVersion();

	///////////////////////////////////////////////////////////////////////////
	// Function:	CheckComponentVersion
	// Description: This function checks the format of the passed component
	//				version.
	//
	// Parameters:	strComponentVersion		Component version
	//
	// Returns:		true	Component version correct
	//				false	Component version incorrect
	///////////////////////////////////////////////////////////////////////////
	bool CheckComponentVersion(const string& strComponentVersion);

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
	string m_strComponentName;
	static int m_nMaxComponentNameLength;

	string m_strEngineLicenseNumber;
	static int m_nMaxEngineLicenseNumberLength;

	string m_strReserved;
	static int m_nMaxReservedLength;

	static int m_nMaxLicenseNumberLength;

	string m_strComponentVersion;
	static int m_nMaxComponentVersionLength;

	string m_strSerialNumber;
	static int m_nMaxSerialNumberLength;

	string m_strCustomerType;
	static int m_nMaxCustomerTypeLength;

	string m_strLicenseType;
	static int m_nMaxLicenseTypeLength;
};

///////////////////////////////////////////////////////////////////////////////

#endif // !COMPONENTKEY_H
