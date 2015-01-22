/*****************************************************************************
 * $Workfile: License.h $
 * $Revision: 2 $
 * $Modtime: 3-05-01 14:32 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2000, 2001 CMG NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#ifndef LICENSE_H
#define LICENSE_H

///////////////////////////////////////////////////////////////////////////////
// Engine License Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetCustomerName
// Description: This function sets the name of the customer
//
// Parameters:	pszCustomerName		Customer name
//
// Returns:		1	Customer name set
//				0	Customer name not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetCustomerName(const char* pszCustomerName);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetCustomerName
// Description: This function retrieves the name of the customer
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the customer name
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetCustomerName();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetCompanyName
// Description: This function sets the name of the company
//
// Parameters:	pszCompanyName		Company name
//
// Returns:		1	Company name set
//				0	Companyr name not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetCompanyName(const char* pszCompanyName);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetCompanyName
// Description: This function retrieves the name of the company
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the company name
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetCompanyName();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineLicenseNumber
// Description: This function sets the license number of the engine. The
//				license number consists of a version number, a serial number,
//				a customer type and a license type. (The last two are common
//				for both the engine and component license).
//
// Parameters:	pszLicenseNumber		Engine license number
//
// Returns:		1	Engine license number set
//				0	Engine license number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineLicenseNumber(const char* pszLicenseNumber);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineLicenseNumber
// Description: This function retrieves the engine license number
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the license number
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineLicenseNumber();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineVersion
// Description: This function sets the version number of the engine. The
//				version number is one of the parts of the license number.
//
// Parameters:	pszEngineVersion		Engine version number
//
// Returns:		1	Engine version number set
//				0	Engine version number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineVersion(const char* pszEngineVersion);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineVersion
// Description: This function retrieves the engine version number
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the engine version
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineVersion();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineSerialNumber
// Description: This function sets the serial number of the engine. The
//				serial number is one of the parts of the license number.
//
// Parameters:	pszSerialNumber			Engine serial number
//
// Returns:		1	Engine serial number set
//				0	Engine serial number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineSerialNumber(const char* pszSerialNumber);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineSerialNumber
// Description: This function retrieves the license serial number
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the serial number
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineSerialNumber();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineCustomerType
// Description: This function sets the customer type for the engine license.
//
// Parameters:	pszCustomerType			Customer type
//
// Returns:		1	Customer type set
//				0	Customer type not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineCustomerType(const char* pszCustomerType);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineCustomerType
// Description: This function retrieves the customer type
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the customer type
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineCustomerType();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetLicenseType
// Description: This function sets the license type for the engine license.
//
// Parameters:	pszLicenseType			License type
//
// Returns:		1	License type set
//				0	License type not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineLicenseType(const char* pszLicenseType);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineLicenseType
// Description: This function retrieves the license type
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the license type
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineLicenseType();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineTimeLock
// Description: This function sets the time lock for the engine. The time 
//				lock is an optional feature of the license mechanism. Using 
//				this mechanism the validity of the license can be limited 
//				in time.
//
// Parameters:	pszTimeLock				Engine time lock
//
//				The timelock should have one of following formats:
//				EMPTY				-> Unlimited validity
//				DDMMYYYY			-> Valid this day only
//				DDMMYYYY-			-> Valid from date
//				-DDMMYYYY			-> Valid till day
//				DDMMYYYY-DDMMYYYY	-> Valid from/till dates
//
// Returns:		1	Engine time lock set
//				0	Engine time lock not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineTimeLock(const char* pszTimeLock);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineTimeLock
// Description: This function retrieves the time lock
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the time lock
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineTimeLock();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineNodeLock
// Description: This function sets the node lock data for the engine. The node 
//				lock is an optional feature of the license mechanism. Using 
//				this mechanism the validity of the license can be limited 
//				to a single machine.
//
//				THE NODE LOCK MECHANISM IS NOT YET IMPLEMENTED
//
// Parameters:	pszNodeLock				Node lock
//
//
// Returns:		1	Engine node lock set
//				0	Engine node lock not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineNodeLock(const char* pszNodeLock);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineNodeLock
// Description: This function retrieves the node lock
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the node lock
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineNodeLock();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetEngineKey
// Description: This function sets the encrypted engine license key
//
// Parameters:	pszEngineKey		Encrypted engine license key
//
// Returns:		1	License key set
//				0	License key not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetEngineKey(const char* pszEngineKey);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetEngineKey
// Description: This function gets the encrypted data key for the engine. 
//				Before using this call all the necessary data has to be set 
//				with the lic_SetXXX calls.
//
// Parameters:	-
//
//
// Returns:		Engine encrypted data key
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetEngineKey();



///////////////////////////////////////////////////////////////////////////////
// Component License Functions
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentName
// Description: This function sets the name of the component
//
// Parameters:	pszComponentName		Component name
//
// Returns:		1	Component name set
//				0	Component name not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentName(const char* pszComponentName);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentName
// Description: This function retrieves the component name
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the component name
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentName();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentLicenseNumber
// Description: This function sets the license number of the component. The
//				license number consists of a version number, a serial number,
//				a customer type and a license type. (The last two are common
//				for both the engine and component license).
//
// Parameters:	pszLicenseNumber		Component license number
//
// Returns:		1	Component license number set
//				0	Component license number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentLicenseNumber(const char* pszLicenseNumber);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentLicenseNumber
// Description: This function retrieves the license number
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the license number
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentLicenseNumber();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentVersion
// Description: This function sets the version number of the component. The
//				version number is one of the parts of the license number.
//
// Parameters:	pszComponentVersion		Component version number
//
// Returns:		1	Component version number set
//				0	Component version number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentVersion(const char* pszComponentVersion);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentLicenseNumber
// Description: This function retrieves the component version
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the component version
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentVersion();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentSerialNumber
// Description: This function sets the serial number of the component. The
//				serial number is one of the parts of the license number.
//
// Parameters:	pszSerialNumber			Component serial number
//
// Returns:		1	Component serial number set
//				0	Component serial number not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentSerialNumber(const char* pszSerialNumber);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentSerialNumber
// Description: This function retrieves the component version
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the serial number
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentSerialNumber();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentCustomerType
// Description: This function sets the customer type for the component license.
//
// Parameters:	pszCustomerType			Customer type
//
// Returns:		1	Customer type set
//				0	Customer type not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentCustomerType(const char* pszCustomerType);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentCustomerType
// Description: This function retrieves the component version
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the customer type
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentCustomerType();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentLicenseType
// Description: This function sets the license type for the component license.
//
// Parameters:	pszLicenseType			License type
//
// Returns:		1	License type set
//				0	License type not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentLicenseType(const char* pszLicenseType);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentLicenseType
// Description: This function retrieves the license type
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the license type
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentLicenseType();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentEngineLicense
// Description: This function sets the engine license number
//
// Parameters:	pszEngineLicense		Engine license number
//
// Returns:		1	License set
//				0	License not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentEngineLicense(const char* pszEngineLicense);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentEngineLicense
// Description: This function retrieves the engine license
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the engine license
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentEngineLicense();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentTimeLock
// Description: This function sets the time lock for the component. The time 
//				lock is an optional feature of the license mechanism. Using 
//				this mechanism the validity of the license can be limited 
//				in time.
//
// Parameters:	pszTimeLock				Component time lock
//
//				The timelock should have one of following formats:
//				EMPTY				-> Unlimited validity
//				DDMMYYYY			-> Valid this day only
//				DDMMYYYY-			-> Valid from date
//				-DDMMYYYY			-> Valid till day
//				DDMMYYYY-DDMMYYYY	-> Valid from/till dates
//
// Returns:		1	Component time lock set
//				0	Component time lock not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentTimeLock(const char* pszTimeLock);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentTimeLock
// Description: This function retrieves the license time lock
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the time lock
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentTimeLock();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentNodeLock
// Description: This function sets the node lock data for a component. The node 
//				lock is an optional feature of the license mechanism. Using 
//				this mechanism the validity of the license can be limited 
//				to a single machine.
//
//				THE NODE LOCK MECHANISM IS NOT YET IMPLEMENTED
//
// Parameters:	pszNodeLock				Node lock
//
//
// Returns:		1	Component node lock set
//				0	Component node lock not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentNodeLock(const char* pszNodeLock);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentNodeLock
// Description: This function retrieves the license node lock
//
// Parameters:	-
//
// Returns:		Pointer to null terminated string containing the node lock
//				or a null pointer if the license could not be decrypted.
///////////////////////////////////////////////////////////////////////////////
const char* _stdcall lic_GetComponentNodeLock();

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_SetComponentKey
// Description: This function sets the 
//
// Parameters:	pszNodeLock				Component key
//
//
// Returns:		1	Component node lock set
//				0	Component node lock not set
///////////////////////////////////////////////////////////////////////////////
int _stdcall lic_SetComponentKey(const char* pszComponentKey);

///////////////////////////////////////////////////////////////////////////////
// Function:	lic_GetComponentKey
// Description: This function gets the encrypted data key for the component. 
//				Before using this call all the necessary data has to be set 
//				with the lic_SetXXX calls.
//
// Parameters:	-
//
//
// Returns:		Component encrypted data key
///////////////////////////////////////////////////////////////////////////////
char* _stdcall lic_GetComponentKey();

///////////////////////////////////////////////////////////////////////////////

#endif // !LICENSE_H
