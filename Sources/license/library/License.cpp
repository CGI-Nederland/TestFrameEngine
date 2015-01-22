/*****************************************************************************
 * $Workfile: License.cpp $
 * $Revision: 2 $
 * $Modtime: 3-05-01 14:33 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

#include "ComponentKey.h"
#include "EngineKey.h"

///////////////////////////////////////////////////////////////////////////////
// Globals

#define BUFFERSIZE		321

char g_pszBuffer[BUFFERSIZE];		// Buffer for the return values

EngineKey g_theEngineKey;			// The Engine key
ComponentKey g_theComponentKey;		// The component key
///////////////////////////////////////////////////////////////////////////////

BOOL APIENTRY			DllMain
(
	HANDLE				hModule, 
	DWORD				ul_reason_for_call,
	LPVOID				lpReserved
)
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

///////////////////////////////////////////////////////////////////////////////

//						===================
int _stdcall 			lic_SetCustomerName
//						===================
(
	const char* 		pszCustomerName			// Customer Name		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszCustomerName != 0)
	{
		// Store the customer name in the engine key
		if (g_theEngineKey.SetCustomerName(pszCustomerName))
		{
			// Customer name was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						===================
const char* _stdcall	lic_GetCustomerName()
//						===================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetCustomerName().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						==================
int _stdcall 			lic_SetCompanyName
//						==================
(
	const char* 		pszCompanyName			// Company Name			(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszCompanyName != 0)
	{
		// Store the company name in the engine key
		if (g_theEngineKey.SetCompanyName(pszCompanyName))
		{
			// Company name was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						==================
const char* _stdcall	lic_GetCompanyName()
//						==================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetCompanyName().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						==========================
int _stdcall 			lic_SetEngineLicenseNumber
//						==========================
(
	const char* 		pszLicenseNumber			// License Number		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszLicenseNumber != 0)
	{
		// Store the license number in the engine key
		if (g_theEngineKey.SetLicenseNumber(pszLicenseNumber))
		{
			// License number was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						==========================
const char* _stdcall	lic_GetEngineLicenseNumber()
//						==========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetLicenseNumber().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						====================
int _stdcall 			lic_SetEngineVersion
//						====================
(
	const char* 		pszEngineVersion		// Engine version		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszEngineVersion != 0)
	{
		// Store the engine version in the engine key
		if (g_theEngineKey.SetEngineVersion(pszEngineVersion))
		{
			// Engine version was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						====================
const char* _stdcall	lic_GetEngineVersion()
//						====================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetEngineVersion().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=========================
int _stdcall 			lic_SetEngineSerialNumber
//						=========================
(
	const char* 		pszSerialNumber			// Serial Number		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszSerialNumber != 0)
	{
		// Store the serial number in the engine key
		if (g_theEngineKey.SetSerialNumber(pszSerialNumber))
		{
			// Serial number was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=========================
const char* _stdcall	lic_GetEngineSerialNumber()
//						=========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetSerialNumber().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=========================
int _stdcall 			lic_SetEngineCustomerType
//						=========================
(
	const char* 		pszCustomerType			// Customer Type		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszCustomerType != 0)
	{
		// Store the customer type in the engine key
		if (g_theEngineKey.SetCustomerType(pszCustomerType))
		{
			// Customer type was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=========================
const char* _stdcall	lic_GetEngineCustomerType()
//						=========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetCustomerType().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						========================
int _stdcall 			lic_SetEngineLicenseType
//						========================
(
	const char* 		pszLicenseType			// License Type		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszLicenseType != 0)
	{
		// Store the license type in the engine key
		if (g_theEngineKey.SetLicenseType(pszLicenseType))
		{
			// License type was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						========================
const char* _stdcall	lic_GetEngineLicenseType()
//						========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetCustomerType().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=====================
int _stdcall			lic_SetEngineTimeLock
//						=====================
(
	const char*			pszTimeLock				// Time Lock		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszTimeLock != 0)
	{
		// Store the time lock in the engine key
		if (g_theEngineKey.SetTimeLock(pszTimeLock))
		{
			// Time lock was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=====================
const char* _stdcall	lic_GetEngineTimeLock()
//						=====================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetTimeLock().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=====================
int _stdcall			lic_SetEngineNodeLock
//						=====================
(
	const char*			pszNodeLock				// Node Lock		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszNodeLock != 0)
	{
		// Store the node lock in the engine key
		if (g_theEngineKey.SetNodeLock(pszNodeLock))
		{
			// Node lock was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=====================
const char* _stdcall	lic_GetEngineNodeLock()
//						=====================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the engine key
	if (g_theEngineKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetNodeLock().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						================
int _stdcall 			lic_SetEngineKey
//						================
(
	const char* 		pszEngineKey			// Engine Key		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszEngineKey != 0)
	{
		// Set the encrypted engine key
		if (g_theEngineKey.SetEncrypted(pszEngineKey))
		{
			// Engine key was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						================
const char* _stdcall	lic_GetEngineKey()
//						================
{
	// Default result is failure
	char* pszResult = 0;

	// Try to encrypt the engine key
	if (g_theEngineKey.Encrypt())
	{
		// Copy the string to the global buffer
		strcpy(g_pszBuffer, g_theEngineKey.GetEncrypted().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}








///////////////////////////////////////////////////////////////////////////////








//						====================
int _stdcall 			lic_SetComponentName
//						====================
(
	const char* 		pszComponentName			// Component Name		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszComponentName != 0)
	{
		// Store the component name in the component key
		if (g_theComponentKey.SetComponentName(pszComponentName))
		{
			// Component name was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						====================
const char* _stdcall	lic_GetComponentName()
//						====================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetComponentName().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}


//						=============================
int _stdcall 			lic_SetComponentLicenseNumber
//						=============================
(
	const char* 		pszLicenseNumber			// License Number		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszLicenseNumber != 0)
	{
		// Store the license number in the component key
		if (g_theComponentKey.SetLicenseNumber(pszLicenseNumber))
		{
			// License number was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=============================
const char* _stdcall	lic_GetComponentLicenseNumber()
//						=============================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetLicenseNumber().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=======================
int _stdcall 			lic_SetComponentVersion
//						=======================
(
	const char* 		pszComponentVersion		// Component version	(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszComponentVersion != 0)
	{
		// Store the component version in the component key
		if (g_theComponentKey.SetComponentVersion(pszComponentVersion))
		{
			// Component version was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=======================
const char* _stdcall	lic_GetComponentVersion()
//						=======================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetComponentVersion().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						============================
int _stdcall 			lic_SetComponentSerialNumber
//						============================
(
	const char* 		pszSerialNumber			// Serial Number		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszSerialNumber != 0)
	{
		// Store the serial number in the component key
		if (g_theEngineKey.SetSerialNumber(pszSerialNumber))
		{
			// Serial number was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						============================
const char* _stdcall	lic_GetComponentSerialNumber()
//						============================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetSerialNumber().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						============================
int _stdcall 			lic_SetComponentCustomerType
//						============================
(
	const char* 		pszCustomerType			// Customer Type		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszCustomerType != 0)
	{
		// Store the customer type in the component key
		if (g_theComponentKey.SetCustomerType(pszCustomerType))
		{
			// Customer type was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						============================
const char* _stdcall	lic_GetComponentCustomerType()
//						============================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetCustomerType().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						===========================
int _stdcall 			lic_SetComponentLicenseType
//						===========================
(
	const char* 		pszLicenseType			// License Type		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszLicenseType != 0)
	{
		// Store the license type in the component key
		if (g_theComponentKey.SetLicenseType(pszLicenseType))
		{
			// License type was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						===========================
const char* _stdcall	lic_GetComponentLicenseType()
//						===========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetLicenseType().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						=============================
int _stdcall			lic_SetComponentEngineLicense
//						=============================
(
	const char*			pszEngineLicense				// Engine license	(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszEngineLicense != 0)
	{
		// Store the time lock in the component key
		if (g_theComponentKey.SetEngineLicenseNumber(pszEngineLicense))
		{
			// Engine license was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						=============================
const char* _stdcall	lic_GetComponentEngineLicense()
//						=============================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetEngineLicenseNumber().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						========================
int _stdcall			lic_SetComponentTimeLock
//						========================
(
	const char*			pszTimeLock				// Time Lock		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszTimeLock != 0)
	{
		// Store the time lock in the component key
		if (g_theComponentKey.SetTimeLock(pszTimeLock))
		{
			// Time lock was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						========================
const char* _stdcall	lic_GetComponentTimeLock()
//						========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetTimeLock().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						========================
int _stdcall			lic_SetComponentNodeLock
//						========================
(
	const char*			pszNodeLock				// Node Lock		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszNodeLock != 0)
	{
		// Store the node lock in the component key
		if (g_theComponentKey.SetNodeLock(pszNodeLock))
		{
			// Node lock was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						========================
const char* _stdcall	lic_GetComponentNodeLock()
//						========================
{
	// Default result is failure
	const char* pszResult = 0;

	// Try to decrypt the component key
	if (g_theComponentKey.Decrypt())
	{
		// Copy the string to the medium sized global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetNodeLock().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

//						===================
int _stdcall 			lic_SetComponentKey
//						===================
(
	const char* 		pszComponentKey			// Component Key		(In)
)
{
	// Default result is failure
	int nResult = 0;
	
	// Watch out for null pointers
	if (pszComponentKey != 0)
	{
		// Set the encrypted component key
		if (g_theComponentKey.SetEncrypted(pszComponentKey))
		{
			// Engine key was set successfully
			nResult = 1;
		}
	}

	return nResult;
}

//						===================
char* _stdcall			lic_GetComponentKey()
//						===================
{
	// Default result is failure
	char* pszResult = 0;

	// Set the engine license number in the component key
	g_theComponentKey.SetEngineLicenseNumber(g_theEngineKey.GetLicenseNumber());

	// Try to encrypt the component key
	if (g_theComponentKey.Encrypt())
	{
		// Copy the string to the global buffer
		strcpy(g_pszBuffer, g_theComponentKey.GetEncrypted().c_str());

		pszResult = g_pszBuffer;
	}
	
	return pszResult;
}

///////////////////////////////////////////////////////////////////////////////
