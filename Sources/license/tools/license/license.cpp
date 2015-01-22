/*****************************************************************************
 * $Workfile: license.cpp $
 * $Revision: 3 $
 * $Modtime: 11-05-01 15:14 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <iostream>		// streams
#include <string>		// strings
using namespace std;

#include "License.h"	// DLL interface

///////////////////////////////////////////////////////////////////////////////
// Forward declarations

void DisplayHelp();
bool CreateEngineKey(const string& strCustomerName, const string& strCompanyName, const string& strLicenseNumber, const string& strTimeLock);
bool CreateComponentKey(const string& strComponentName,	const string& strComponentLicenseNumber,	const string& strEngineLicenseNumber, const string& strTimeLock);

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
{
	// Count the number of parameters
	if ((argc == 5) || (argc == 6))
	{
		// Check the first parameter, the switch
		string strSwitch = string(argv[1]);

		if ((strSwitch == "-e") || (strSwitch == "-E"))
		{
			// Engine key switch
			string strCustomer = string(argv[2]);
			string strCompany = string(argv[3]);
			string strLicense = string(argv[4]);
			string strTimeLock;

			// Time lock is optional
			if (argc == 6)
			{
				strTimeLock = string(argv[5]);
			}

			// Try to create the engine key
			if (!CreateEngineKey(strCustomer, strCompany, strLicense, strTimeLock))
			{
				// Key creation failed
				DisplayHelp();
			}
		}
		else if ((strSwitch == "-c") || (strSwitch == "-C"))
		{
			// Component key switch
			string strComponent = string(argv[2]);
			string strComponentLicense = string(argv[3]);
			string strEngineLicense = string(argv[4]);
			string strTimeLock;

			// Time lock is optional
			if (argc == 6)
			{
				strTimeLock = string(argv[5]);
			}

			// Try to create the component key
			if (!CreateComponentKey(strComponent, strComponentLicense, strEngineLicense, strTimeLock))
			{
				// Key creation failed
				DisplayHelp();
			}
		}
		else
		{
			// Illegal switch
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
	cout << "TestFrame ConTest Engine 5.5 License Tool" << endl;
	cout << "(C) 2013 CGI NEDERLAND B.V." << endl << endl;
	cout << "To create an Engine license key use:" << endl << endl;
	cout << "\tlicense -e customer company license [timelock]" << endl << endl;
	cout << "\t\tcustomer\tName of the customer\t[Max. 40 characters]" << endl;
	cout << "\t\tcompany\t\tName of the company\t[Max. 40 characters]" << endl;
	cout << "\t\tlicense\t\tEngine license number\t[AAA-BBBBBB-C-DD]" << endl;
	cout << "\t\t[timelock]\tOptional time lock\t[DDMMYYYY-DDMMYYYY]" << endl << endl;

	cout << "To create a Component license key use:" << endl;
	cout << "\tlicense -c component componentlicense enginelicense [timelock]" << endl;
	cout << "\t\tcomponent\tName of the component\t[Max. 40 characters]" << endl;
	cout << "\t\tcomponentlicense\tComponent license number\t[AAA-BBBBBB-C-DD]" << endl;
	cout << "\t\tenginelicense\tEngine license number\t[AAA-BBBBBB-C-DD]" << endl;
	cout << "\t\t[timelock]\tOptional time lock\t[DDMMYYYY-DDMMYYYY]" << endl << endl;
}

//						===============
bool					CreateEngineKey
//						===============
(
	const string&		strCustomerName,
	const string&		strCompanyName,
	const string&		strLicenseNumber,
	const string&		strTimeLock
)
{
	// Default result is failure
	bool bResult = false;

	// First set the name of the customer
	if (lic_SetCustomerName(strCustomerName.c_str()) == 1)
	{
		// Set the name of the company
		if (lic_SetCompanyName(strCompanyName.c_str()) == 1)
		{
			// Set the license number
			if (lic_SetEngineLicenseNumber(strLicenseNumber.c_str()) == 1)
			{
				// Set the time lock
				if (lic_SetEngineTimeLock(strTimeLock.c_str()) == 1)
				{
					// Retrieve the Engine key
					const char* pKey = lic_GetEngineKey();

					if (pKey != 0)
					{
						cout << "[ENGINE]" << endl;
						cout << "Key=" << string(pKey) << endl << endl;
						cout << "[COMPONENTS]" << endl;
				
						// Creation succeeded
						bResult = true;
					}
				}
			}
		}
	}

	return bResult;
}

//						==================
bool					CreateComponentKey
//						==================
(
	const string&		strComponentName,
	const string&		strComponentLicenseNumber,
	const string&		strEngineLicenseNumber,
	const string&		strTimeLock
)
{
	// Default result is failure
	bool bResult = false;

	// First set the name of the component
	if (lic_SetComponentName(strComponentName.c_str()) == 1)
	{
		// Set the component license number
		if (lic_SetComponentLicenseNumber(strComponentLicenseNumber.c_str()) == 1)
		{
			// Set the engine license number
			if (lic_SetEngineLicenseNumber(strEngineLicenseNumber.c_str()) == 1)
			{
				// Set the time lock
				if (lic_SetComponentTimeLock(strTimeLock.c_str()) == 1)
				{
					// Retrieve the Component key
					char* pKey = lic_GetComponentKey();

					if (pKey != 0)
					{
						cout << strComponentName << "="<< string(pKey) << endl;
				
						// Creation succeeded
						bResult = true;
					}
				}
			}
		}
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////
