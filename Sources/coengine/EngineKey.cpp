/*****************************************************************************
 * $Workfile: EngineKey.cpp $
 * $Revision: 1 $
 * $Modtime: 1-05-01 16:23 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#pragma warning(disable:4786)

#include <vector>
using namespace std;

#include "EngineKey.h"


///////////////////////////////////////////////////////////////////////////////
// Constants

int EngineKey::m_nMaxCustomerNameLength = 40;
int EngineKey::m_nMaxCompanyNameLength = 40;
int EngineKey::m_nMaxLicenseNumberLength = 20;
int EngineKey::m_nMaxEngineVersionLength = 3;
int EngineKey::m_nMaxSerialNumberLength = 6;
int EngineKey::m_nMaxCustomerTypeLength = 1;
int EngineKey::m_nMaxLicenseTypeLength = 2;

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

EngineKey::EngineKey()
{
	// Empty
}

EngineKey::~EngineKey()
{
	// Empty
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						==================
bool					EngineKey::Encrypt()
//						==================
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

//						==================
bool					EngineKey::Decrypt()
//						==================
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

//						==========================
bool					EngineKey::SetCustomerName
//						==========================
(
	const string&		strCustomerName
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the customer name
	if (strCustomerName.length() <= m_nMaxCustomerNameLength)
	{
		// Copy the data to the member variable
		m_strCustomerName = strCustomerName;
		
		bResult = true;
	}

	return bResult;
}

//						==========================
string					EngineKey::GetCustomerName()
//						==========================
{
	// Return the value of the member variable
	return m_strCustomerName;
}

//						=========================
bool					EngineKey::SetCompanyName
//						=========================
(
	const string&		strCompanyName
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the company name
	if (strCompanyName.length() <= m_nMaxCompanyNameLength)
	{
		// Copy the data to the member variable
		m_strCompanyName = strCompanyName;
		
		bResult = true;
	}

	return bResult;
}

//						=========================
string					EngineKey::GetCompanyName()
//						=========================
{
	// Return the value of the member variable
	return m_strCompanyName;
}

//						===========================
bool					EngineKey::SetLicenseNumber
//						===========================
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
		string::size_type	nStartPos = 0;
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
			bool bVersion = SetEngineVersion(vstrParts[0]);
			bool bSerial = SetSerialNumber(vstrParts[1]);
			bool bCustomer = SetCustomerType(vstrParts[2]);
			bool bLicense = SetLicenseType(vstrParts[3]);

			bResult = true;
		}
	}

	return bResult;
}


//						===========================
string					EngineKey::GetLicenseNumber()
//						===========================
{
	string strLicenseNumber;

	// Retrieve the parts of the license number
	string strEngineVersion = GetEngineVersion();
	string strSerialNumber = GetSerialNumber();
	string strCustomerType = GetCustomerType();
	string strLicenseType = GetLicenseType();

	// Check the parts of the license number
	if ((CheckEngineVersion(strEngineVersion)) && 
		(CheckSerialNumber(strSerialNumber)) && 
		(CheckCustomerType(strCustomerType)) && 
		(CheckLicenseType(strLicenseType)))
	{
		// Everything is ok so paste the parts together
		strLicenseNumber += strEngineVersion + "-";
		strLicenseNumber += strSerialNumber + "-";
		strLicenseNumber += strCustomerType + "-";
		strLicenseNumber += strLicenseType;
	}

	return strLicenseNumber;
}

//						==========================
bool					EngineKey::SetSerialNumber
//						==========================
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

//						==========================
string					EngineKey::GetSerialNumber()
//						==========================
{
	// Return the value of the member variable
	return m_strSerialNumber;
}

//						============================
bool					EngineKey::CheckSerialNumber
//						============================
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

//						===========================
bool					EngineKey::SetEngineVersion
//						===========================
(
	const string&		strEngineVersion
)
{
	// Default result is failure
	bool bResult = false;

	// Check the given engine version
	if (CheckEngineVersion(strEngineVersion))
	{
		// Copy the data to the member variable
		m_strEngineVersion = strEngineVersion;

		bResult = true;
	}

	return bResult;
}

//						===========================
string					EngineKey::GetEngineVersion()
//						===========================
{
	// Return the value of the member variable
	return m_strEngineVersion;
}

//						=============================
bool					EngineKey::CheckEngineVersion
//						=============================
(
	const string&		strEngineVersion
)
{
	// Default result is failure
	bool bResult = false;

	// Check the length of the engine version
	if (strEngineVersion.length() == m_nMaxEngineVersionLength)
	{
		// The engine version should be numeric
		bResult = IsNumeric(strEngineVersion);
	}

	return bResult;
}

//						==========================
bool					EngineKey::SetCustomerType
//						==========================
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

//						==========================
string					EngineKey::GetCustomerType()
//						==========================
{
	// Return the value of the member variable
	return m_strCustomerType;
}

//						============================
bool					EngineKey::CheckCustomerType
//						============================
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

//						=========================
bool					EngineKey::SetLicenseType
//						=========================
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

//						=========================
string					EngineKey::GetLicenseType()
//						=========================
{
	// Return the value of the member variable
	return m_strLicenseType;
}

//						===========================
bool					EngineKey::CheckLicenseType
//						===========================
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

//						======================
bool					EngineKey::ComposeData()
//						======================
{
	// Default result is failure
	bool bResult = false;

	string strCustomerName = GetCustomerName();
	string strCompanyName = GetCompanyName();
	string strLicenseNumber = GetLicenseNumber();

	// Pad strings to reach the desired lengths
	strCustomerName = Pad(strCustomerName, m_nMaxCustomerNameLength);
	strCompanyName = Pad(strCompanyName, m_nMaxCompanyNameLength);
	strLicenseNumber = Pad(strLicenseNumber, m_nMaxLicenseNumberLength);

	// Scramble the strings to get one big string
	string strScrambled;

	// Compute the chunk sizes for the scrambling
	string::size_type nNameChunk = m_nMaxCustomerNameLength / m_nMaxLicenseNumberLength;
	string::size_type nCompanyChunk = m_nMaxCompanyNameLength / m_nMaxLicenseNumberLength;
	string::size_type nLicenseChunk = m_nMaxLicenseNumberLength / m_nMaxLicenseNumberLength;

	// Process all the strings
	string::size_type i;
	for (i = 0; i < m_nMaxLicenseNumberLength; i++)
	{
		strScrambled.append(strCustomerName.substr(nNameChunk*i, nNameChunk));
		strScrambled.append(strCompanyName.substr(nCompanyChunk*i, nCompanyChunk));
		strScrambled.append(strLicenseNumber.substr(nLicenseChunk*i, nLicenseChunk));
	}
	
	// Copy the scrambled data to the member variable
	bResult = SetData(strScrambled);

	return bResult;
}

//						========================
bool					EngineKey::DecomposeData()
//						========================
{
	// Default result is failure
	bool bResult = false;

	// Retrieve the data from the baseclass
	string strData = GetData();
	int nDataLength = strData.length();

	string strCustomerName;
	string strCompanyName;
	string strLicenseNumber;

	// Check the length of the data
	if (nDataLength == GetMaxDataLength())
	{
		// Compute the chunk sizes for the descrambling
		string::size_type nNameChunk = m_nMaxCustomerNameLength / m_nMaxLicenseNumberLength;
		string::size_type nCompanyChunk = m_nMaxCompanyNameLength / m_nMaxLicenseNumberLength;
		string::size_type nSerialChunk = m_nMaxLicenseNumberLength / m_nMaxLicenseNumberLength;
		string::size_type nTotalChunkSize = nNameChunk + nCompanyChunk + nSerialChunk;

		// Descramble the data
		string::size_type i;
		for (i = 0; i < m_nMaxLicenseNumberLength; i++)
		{
			strCustomerName.append(strData.substr(nTotalChunkSize*i, nNameChunk));
			strCompanyName.append(strData.substr(nTotalChunkSize*i + nNameChunk, nCompanyChunk));
			strLicenseNumber.append(strData.substr(nTotalChunkSize*i + nNameChunk + nCompanyChunk, nSerialChunk));
		}

		// Remove the random generated parts
		strCustomerName = strCustomerName.substr(0, strCustomerName.find("*"));
		strCompanyName = strCompanyName.substr(0, strCompanyName.find("*"));
		strLicenseNumber = strLicenseNumber.substr(0, strLicenseNumber.find("*"));

		// Store the resulting strings
		SetCustomerName(strCustomerName);
		SetCompanyName(strCompanyName);
		SetLicenseNumber(strLicenseNumber);
	
		bResult = true;
	}

	return bResult;
}


///////////////////////////////////////////////////////////////////////////////
