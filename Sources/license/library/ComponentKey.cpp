/*****************************************************************************
 * $Workfile: ComponentKey.cpp $
 * $Revision: 1 $
 * $Modtime: 1-05-01 16:31 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable:4786)

#include <vector>
using namespace std;

#include "ComponentKey.h"

///////////////////////////////////////////////////////////////////////////////

int ComponentKey::m_nMaxComponentNameLength = 40;
int ComponentKey::m_nMaxEngineLicenseNumberLength = 20;
int ComponentKey::m_nMaxReservedLength = 20;
int ComponentKey::m_nMaxLicenseNumberLength = 20;
int ComponentKey::m_nMaxComponentVersionLength = 3;
int ComponentKey::m_nMaxSerialNumberLength = 6;
int ComponentKey::m_nMaxCustomerTypeLength = 1;
int ComponentKey::m_nMaxLicenseTypeLength = 2;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

ComponentKey::ComponentKey()
{
	// Empty
}

ComponentKey::~ComponentKey()
{
	// Empty
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						=====================
bool					ComponentKey::Encrypt()
//						=====================
{
	// Default result is failure
	bool bResult = false;

	// First compose the data
	bResult = ComposeData();

	if (bResult)
	{
		// Call the baseclass implementation
		bResult = Key::Encrypt();
	}

	return bResult;
}

//						=====================
bool					ComponentKey::Decrypt()
//						=====================
{
	// First call the baseclass implementation
	bool bResult = Key::Decrypt();

	if (bResult)
	{
		// On success decompose the data
		bResult = DecomposeData();
	}

	return bResult;
}

//						==============================
bool					ComponentKey::SetComponentName
//						==============================
(
	const string&		strComponentName
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the customer name
	if (strComponentName.length() <= m_nMaxComponentNameLength)
	{
		// Copy the data to the member variable
		m_strComponentName = strComponentName;
		
		bResult = true;
	}

	return bResult;
}

//						==============================
string					ComponentKey::GetComponentName()
//						==============================
{
	// Return the value of the member variable
	return m_strComponentName;
}

//						====================================
bool					ComponentKey::SetEngineLicenseNumber
//						====================================
(
	const string&		strEngineLicenseNumber
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the engine license number
	if (strEngineLicenseNumber.length() <= m_nMaxEngineLicenseNumberLength)
	{
		// Copy the data to the member variable
		m_strEngineLicenseNumber = strEngineLicenseNumber;
		
		bResult = true;
	}

	return bResult;
}

//						====================================
string					ComponentKey::GetEngineLicenseNumber()
//						====================================
{
	// Return the value of the member variable
	return m_strEngineLicenseNumber;
}

//						=========================
bool					ComponentKey::SetReserved
//						=========================
(
	const string&		strReserved
)
{
	// Copy the data to the member variable
	m_strReserved = strReserved;

	return true;
}

//						=========================
string 					ComponentKey::GetReserved()
//						=========================
{
	// Return the value of the member variable
	return m_strReserved;
}

//						==============================
bool					ComponentKey::SetLicenseNumber
//						==============================
(
	const string&		strLicenseNumber
)
{
	// Default result is failure
	bool bResult = false;

	// See if license number is not empty
	if (!strLicenseNumber.empty())
	{
		// Vector for the parts of the license number
		vector<string> vstrParts;

		// Split hte license number in parts
		bool bFinished = false;
		string::size_type nStartPos = 0;
		while (!bFinished)
		{
			// Determine position of the (next) dash (-)
			string::size_type nDashPos = strLicenseNumber.find("-", nStartPos);

			// Check if no dash was found
			if (nDashPos == string::npos)
			{
				nDashPos	= strLicenseNumber.length();
				bFinished	= true;
			}

			// Add part to vector
			vstrParts.push_back(strLicenseNumber.substr(nStartPos, nDashPos - nStartPos));

			// Update next starting position
			nStartPos = nDashPos + 1;
		}

		// Check if there are four parts found
		if (vstrParts.size() == 4)
		{
			// Store codes in member variables
			bool bVersion = SetComponentVersion(vstrParts[0]);
			bool bSerial = SetSerialNumber(vstrParts[1]);
			bool bCustomer = SetCustomerType(vstrParts[2]);
			bool bLicense = SetLicenseType(vstrParts[3]);

			bResult = true;
		}
	}

	return bResult;
}

//						==============================
string					ComponentKey::GetLicenseNumber()
//						==============================
{
	string strLicenseNumber;

	// Retrieve the parts of the license number
	string strComponentVersion = GetComponentVersion();
	string strSerialNumber = GetSerialNumber();
	string strCustomerType = GetCustomerType();
	string strLicenseType = GetLicenseType();

	// Check the parts of the license number
	if ((CheckComponentVersion(strComponentVersion)) && 
		(CheckSerialNumber(strSerialNumber)) && 
		(CheckCustomerType(strCustomerType)) && 
		(CheckLicenseType(strLicenseType)))
	{
		// Everything is ok so paste the parts together
		strLicenseNumber += strComponentVersion + "-";
		strLicenseNumber += strSerialNumber + "-";
		strLicenseNumber += strCustomerType + "-";
		strLicenseNumber += strLicenseType;
	}

	return strLicenseNumber;
}

//						=================================
bool					ComponentKey::SetComponentVersion
//						=================================
(
	const string&		strComponentVersion
)
{
	// Default result is failure
	bool bResult = false;

	// Check the given component version
	if (CheckComponentVersion(strComponentVersion))
	{
		// Copy the data to the member variable
		m_strComponentVersion = strComponentVersion;

		bResult = true;
	}

	return bResult;
}

//						=================================
string					ComponentKey::GetComponentVersion()
//						=================================
{
	// Return the value of the member variable
	return m_strComponentVersion;
}

//						===================================
bool					ComponentKey::CheckComponentVersion
//						===================================
(
	const string&		strComponentVersion
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the component version
	if (strComponentVersion.length() == m_nMaxComponentVersionLength)
	{
		// The component version should be numeric
		bResult = IsNumeric(strComponentVersion);
	}

	return bResult;
}

//						=============================
bool					ComponentKey::SetSerialNumber
//						=============================
(
	const string&		strSerialNumber
)
{
	// Default result is failure
	bool bResult = false;

	// Check the given serial number
	if (CheckSerialNumber(strSerialNumber))
	{
		// Copy the data to the member variable
		m_strSerialNumber = strSerialNumber;

		bResult = true;
	}

	return bResult;
}

//						=============================
string					ComponentKey::GetSerialNumber()
//						=============================
{
	// Return the value of the member variable
	return m_strSerialNumber;
}

//						===============================
bool					ComponentKey::CheckSerialNumber
//						===============================
(
	const string&		strSerialNumber
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the serial number
	if (strSerialNumber.length() == m_nMaxSerialNumberLength)
	{
		// The serial number should be numeric
		bResult = IsNumeric(strSerialNumber);
	}

	return bResult;
}

//						=============================
bool					ComponentKey::SetCustomerType
//						=============================
(
	const string&		strCustomerType
)
{
	// Default result is failure
	bool bResult = false;

	// Check the given customer type
	if (CheckCustomerType(strCustomerType))
	{
		// Copy the data to the member variable
		m_strCustomerType = strCustomerType;

		bResult = true;
	}

	return bResult;
}

//						=============================
string					ComponentKey::GetCustomerType()
//						=============================
{
	// Return the value of the member variable
	return m_strCustomerType;
}

//						===============================
bool					ComponentKey::CheckCustomerType
//						===============================
(
	const string&		strCustomerType
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the customer type
	if (strCustomerType.length() == m_nMaxCustomerTypeLength)
	{
		// The customer type should be numeric
		bResult = IsNumeric(strCustomerType);
	}

	return bResult;
}

//						============================
bool					ComponentKey::SetLicenseType
//						============================
(
	const string&		strLicenseType
)
{
	// Default result is failure
	bool bResult = false;

	// Check the given license type
	if (CheckLicenseType(strLicenseType))
	{
		// Copy the data to the member variable
		m_strLicenseType = strLicenseType;

		bResult = true;
	}

	return bResult;
}

//						============================
string					ComponentKey::GetLicenseType()
//						============================
{
	// Return the value of the member variable
	return m_strLicenseType;
}

//						==============================
bool					ComponentKey::CheckLicenseType
//						==============================
(
	const string&		strLicenseType
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the license type
	if (strLicenseType.length() == m_nMaxLicenseTypeLength)
	{
		// The license type should be numeric
		bResult = IsNumeric(strLicenseType);
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=========================
bool					ComponentKey::ComposeData()
//						=========================
{
	// Default result is failure
	bool bResult = false;

	string strComponentName = GetComponentName();
	string strEngineLicenseNumber = GetEngineLicenseNumber();
	string strReserved = GetReserved();
	string strLicenseNumber = GetLicenseNumber();

	// Pad strings to reach the desired lengths
	strComponentName = Pad(strComponentName, m_nMaxComponentNameLength);
	strEngineLicenseNumber = Pad(strEngineLicenseNumber, m_nMaxEngineLicenseNumberLength);
	strReserved = Pad(strReserved, m_nMaxReservedLength);
	strLicenseNumber = Pad(strLicenseNumber, m_nMaxLicenseNumberLength);

	// Scramble the strings to get one big string
	string strScrambled;

	// Compute the chunk sizes for the scrambling
	string::size_type  nComponentChunk = m_nMaxComponentNameLength / m_nMaxLicenseNumberLength;
	string::size_type  nEngineChunk = m_nMaxEngineLicenseNumberLength / m_nMaxLicenseNumberLength;
	string::size_type  nReservedChunk = m_nMaxReservedLength / m_nMaxLicenseNumberLength;
	string::size_type  nLicenseChunk = m_nMaxLicenseNumberLength / m_nMaxLicenseNumberLength;

	// Process all the strings
	string::size_type i;
	for (i = 0; i < m_nMaxLicenseNumberLength; i++)
	{
		strScrambled.append(strComponentName.substr(nComponentChunk*i, nComponentChunk));
		strScrambled.append(strEngineLicenseNumber.substr(nEngineChunk*i, nEngineChunk));
		strScrambled.append(strReserved.substr(nReservedChunk*i, nReservedChunk));
		strScrambled.append(strLicenseNumber.substr(nLicenseChunk*i, nLicenseChunk));
	}
	
	// Copy the scrambled data to the member variable
	bResult = SetData(strScrambled);

	return bResult;
}

//						===========================
bool					ComponentKey::DecomposeData()
//						===========================
{
	// Default result is failure
	bool bResult = false;

	// Retrieve the data from the baseclass
	string strData = GetData();
	string::size_type  nDataLength = strData.length();

	string strComponentName;
	string strEngineLicenseNumber;
	string strReserved;
	string strLicenseNumber;

	// Check the length of the data
	if (nDataLength == GetMaxDataLength())
	{
		// Compute the chunk sizes for the descrambling
		string::size_type  nComponentChunk = m_nMaxComponentNameLength / m_nMaxLicenseNumberLength;
		string::size_type  nEngineChunk = m_nMaxEngineLicenseNumberLength / m_nMaxLicenseNumberLength;
		string::size_type  nReservedChunk = m_nMaxReservedLength / m_nMaxLicenseNumberLength;
		string::size_type  nLicenseChunk = m_nMaxLicenseNumberLength / m_nMaxLicenseNumberLength;
		string::size_type  nTotalChunkSize = nComponentChunk + nEngineChunk + nReservedChunk + nLicenseChunk;

		// Descramble the data
		string::size_type i;
		for (i = 0; i < m_nMaxLicenseNumberLength; i++)
		{
			strComponentName.append(strData.substr(nTotalChunkSize*i, nComponentChunk));
			strEngineLicenseNumber.append(strData.substr(nTotalChunkSize*i + nComponentChunk, nEngineChunk));
			strReserved.append(strData.substr(nTotalChunkSize*i + nComponentChunk + nEngineChunk, nReservedChunk));
			strLicenseNumber.append(strData.substr(nTotalChunkSize*i + nComponentChunk + nEngineChunk + nReservedChunk, nLicenseChunk));
		}

		// Remove the random generated parts
		strComponentName = strComponentName.substr(0, strComponentName.find("*"));
		strEngineLicenseNumber = strEngineLicenseNumber.substr(0, strEngineLicenseNumber.find("*"));
		strReserved = strReserved.substr(0, strReserved.find("*"));
		strLicenseNumber = strLicenseNumber.substr(0, strLicenseNumber.find("*"));

		// Store the resulting strings
		SetComponentName(strComponentName);
		SetEngineLicenseNumber(strEngineLicenseNumber);
		SetReserved(strReserved);
		SetLicenseNumber(strLicenseNumber);
	
		bResult = true;
	}

	return bResult;
}


///////////////////////////////////////////////////////////////////////////////
