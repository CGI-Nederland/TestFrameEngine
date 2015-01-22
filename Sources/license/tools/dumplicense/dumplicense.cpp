/*****************************************************************************
 * $Workfile: dumplicense.cpp $
 * $Revision: 2 $
 * $Modtime: 11-05-01 15:02 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <iostream>		// streams
#include <string>		// strings
using namespace std;

#include "IniFile.h"	// IniFile object
#include "License.h"	// DLL interface

///////////////////////////////////////////////////////////////////////////////
// Forward declarations

void DisplayHelp();
void DumpEngineKey(const string& strEngineKey);
void DumpComponentKey(const string& strComponentName, const string& strComponentKey);

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// Count the number of parameters
	if (argc == 2)
	{
		// Retrieve the name of the license file
		string strLicenseFile = string(argv[1]);

		// Create an inifile object
		IniFile license;

		// Import the settings from the license file
		if (license.Import(strLicenseFile))
		{
			// First retrieve and dump the engine key
			string strEngineKey = license.Get("ENGINE", "Key");
			DumpEngineKey(strEngineKey);

			// Print the components header
			cout << endl << "Component License Keys" << endl;
			cout << "======================" << endl << endl;

			// Now retrieve and dump all the component keys
			SECTION sSection = license.GetSection("COMPONENTS");

			// Get the first component key
			SECTION::iterator Iterator = sSection.begin();

			// Process all the components
			while (Iterator != sSection.end())
			{
				// Retrieve the key value pairs
				string strKey = Iterator->first;
				string strValue = Iterator->second;

				// Dump the info from the component key
				DumpComponentKey(strKey, strValue);

				// Get the next component
				Iterator++;
			}
		}
		else
		{
			// Error, could not open the license file
			cout << "Error, could not open license file: " << strLicenseFile << endl << endl;
			DisplayHelp();
		}
	}
	else
	{
		// Wrong number of parameters
		DisplayHelp();
	}

	return 0;
}
	
//						===========	
void					DisplayHelp()
//						===========
{
	// Display an explanation of this tool
	cout << "TestFrame ConTest Engine 5.5 License Dump Tool" << endl;
	cout << "(C) 2001 CMG NEDERLAND B.V." << endl << endl;
	cout << "To dump the contents of a license file use:" << endl << endl;
	cout << "\tdumplicense licensefile" << endl << endl;
	cout << "\tlicensefile\tName and path of the license file" << endl << endl;
}

//						=============
void					DumpEngineKey
//						=============
(
	const string&		strEngineKey
)
{
	// Print the header
	cout << "TestFrame ConTest Engine 5.5 License Dump Tool" << endl;
	cout << "(C) 2001 CMG NEDERLAND B.V." << endl << endl;
	cout << "Engine License Key" << endl;
	cout << "==================" << endl << endl;

	// Set the engine key in the library
	if (lic_SetEngineKey(strEngineKey.c_str()) == 1)
	{
		// Default result is success
		bool bResult = true;

		// Retrieve the customer name
		string strCustomerName;
		const char* pszCustomerName = lic_GetCustomerName();
		if (pszCustomerName != 0)
		{ strCustomerName = string(pszCustomerName); }
		else
		{ bResult = false; }

		// Retrieve the company name
		string strCompanyName;
		const char* pszCompanyName = lic_GetCompanyName();
		if (pszCompanyName != 0)
		{ strCompanyName = string(pszCompanyName); }
		else
		{ bResult = false; }

		// Retrieve the license number
		string strLicenseNumber;
		const char* pszLicenseNumber = lic_GetEngineLicenseNumber();
		if (pszLicenseNumber != 0)
		{ strLicenseNumber = string(pszLicenseNumber); }
		else
		{ bResult = false; }

		// Retrieve the time lock
		string strTimeLock;
		const char* pszTimeLock = lic_GetEngineTimeLock();
		if (pszTimeLock != 0)
		{ strTimeLock = string(pszTimeLock); }
		else
		{ bResult = false; }

		// Retrieve the node lock
		string strNodeLock;
		const char* pszNodeLock = lic_GetEngineNodeLock();
		if (pszNodeLock != 0)
		{ strNodeLock = string(pszNodeLock); }
		else
		{ bResult = false; }

		// Display the information
		if (bResult)
		{
			cout << "Customer name:\t" << strCustomerName << endl;
			cout << "Company name:\t" << strCompanyName << endl;
			cout << "License number:\t" << strLicenseNumber << endl;
			cout << "Time lock:\t" << strTimeLock << endl;
			cout << "Node lock:\t" << strNodeLock << endl;
		}
		else
		{
			// Error, the license key is invalid
			cout << "Error, the engine license key is invalid." << endl;
		}
	}
	else
	{
		// Error, the license key is invalid
		cout << "Error, the engine license key is invalid." << endl;
	}
}

//						================
void					DumpComponentKey
//						================
(
	const string&		strComponentName,
	const string&		strComponentKey
)
{
	// Print the component header
	cout << "[" << strComponentName << "]" << endl;

	// Set the component key in the library
	if (lic_SetComponentKey(strComponentKey.c_str()) == 1)
	{
		// Default result is success
		bool bResult = true;

		// Retrieve the component name
		string strComponentName;
		const char* pszComponentName = lic_GetComponentName();
		if (pszComponentName != 0)
		{ strComponentName = string(pszComponentName); }
		else
		{ bResult = false; }

		// Retrieve the license number
		string strLicenseNumber;
		const char* pszLicenseNumber = lic_GetComponentLicenseNumber();
		if (pszLicenseNumber != 0)
		{ strLicenseNumber = string(pszLicenseNumber); }
		else
		{ bResult = false; }

		// Retrieve the engine license
		string strEngineLicense;
		const char* pszEngineLicense = lic_GetComponentEngineLicense();
		if (pszEngineLicense != 0)
		{ strEngineLicense = string(pszEngineLicense); }
		else
		{ bResult = false; }

		// Retrieve the time lock
		string strTimeLock;
		const char* pszTimeLock = lic_GetComponentTimeLock();
		if (pszTimeLock != 0)
		{ strTimeLock = string(pszTimeLock); }
		else
		{ bResult = false; }

		// Retrieve the node lock
		string strNodeLock;
		const char* pszNodeLock = lic_GetComponentNodeLock();
		if (pszNodeLock != 0)
		{ strNodeLock = string(pszNodeLock); }
		else
		{ bResult = false; }

		// Display the information
		if (bResult)
		{
			cout << "Component name:\t" << strComponentName << endl;
			cout << "License number:\t" << strLicenseNumber << endl;
			cout << "Engine license:\t" << strEngineLicense << endl;
			cout << "Time lock:\t" << strTimeLock << endl;
			cout << "Node lock:\t" << strNodeLock << endl << endl;
		}
		else
		{
			// Error, the license key is invalid
			cout << "Error, the component license key is invalid." << endl << endl;
		}
	}
	else
	{
		// Error, the license key is invalid
		cout << "Error, the component license key is invalid." << endl;
	}
}

///////////////////////////////////////////////////////////////////////////////
