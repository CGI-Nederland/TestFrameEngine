/*****************************************************************************
 * $Workfile: Key.h $
 * $Revision: 4 $
 * $Modtime: 1-05-01 15:39 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef KEY_H
#define KEY_H


#include <string>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Class Key

class Key
{
// Construction and destruction
public:
	Key();
	virtual~Key();

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
	virtual bool Encrypt();

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
	virtual bool Decrypt();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetEncrypted
	// Description: This function sets the encrypted data inside the key.
	//
	// Parameters:	strEncrypted	Encrypted data
	//
	// Returns:		true	Encrypted data set
	//				false	Encrypted data not set
	///////////////////////////////////////////////////////////////////////////////
	bool SetEncrypted(const string& strEncrypted);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetEncrypted
	// Description: This function returns the encrypted data inside the key.
	//
	// Parameters:	-
	//
	// Returns:		Encrypted data
	///////////////////////////////////////////////////////////////////////////////
	string GetEncrypted();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetNodeLock
	// Description: This function sets the node lock information inside the key.
	//
	// Parameters:	strNodeLock		Node lock information
	//
	// Returns:		true	Node lock information set
	//				false	Node lock information not set
	///////////////////////////////////////////////////////////////////////////////
	bool SetNodeLock(const string& strNodeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetNodeLock
	// Description: This function retrieves the node lock information from the key.
	//
	// Parameters:	-
	//
	// Returns:		Node lock information
	///////////////////////////////////////////////////////////////////////////////
	string GetNodeLock();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetTimeLock
	// Description: This function sets the time lock information inside the key.
	//
	// Parameters:	strTimeLock		Time lock information
	//
	// Returns:		true	Time lock information set
	//				false	Time lock information not set
	///////////////////////////////////////////////////////////////////////////////
	bool SetTimeLock(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetTimeLock
	// Description: This function retrieves the time lock information from the key.
	//
	// Parameters:	-
	//
	// Returns:		Time lock information
	///////////////////////////////////////////////////////////////////////////////
	string GetTimeLock();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	CheckTimeLock
	// Description: This function checks if the current date falls in the time 
	//				frame defined by the time lock information inside the key.
	//
	//				The timelock should have one of following formats:
	//				EMPTY				-> Unlimited validity
	//				DDMMYYYY			-> Valid this day only
	//				DDMMYYYY-			-> Valid from day
	//				-DDMMYYYY			-> Valid till day
	//				DDMMYYYY-DDMMYYYY	-> Valid from/till dates
	//
	// Parameters:	-
	//
	// Returns:		true	Current date falls in time frame
	//				false	Current date does not fall in time frame
	///////////////////////////////////////////////////////////////////////////////
	bool CheckTimeLock();

// Implementation
protected:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	SetData
	// Description: This function sets the data string in the key.
	//
	// Parameters:	strData		Data
	//
	// Returns:		true	Data set
	//				false	Data not set
	///////////////////////////////////////////////////////////////////////////////
	bool SetData(const string& strData);
	
	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetData
	// Description: This function retrieves the data string from the key.
	//
	// Parameters:	-
	//
	// Returns:		Data
	///////////////////////////////////////////////////////////////////////////////
	string GetData();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetMaxDataLength
	// Description: This function retrieves the maximum data length from the key.
	//
	// Parameters:	-
	//
	// Returns:		Maximum data length
	///////////////////////////////////////////////////////////////////////////////
	int GetMaxDataLength();

	///////////////////////////////////////////////////////////////////////////////
	// Function:	IsNumeric
	// Description: This function checks if the given string is numeric.
	//
	// Parameters:	strString	String to check
	//
	// Returns:		true		String is numeric
	//				false		String is not numeric
	///////////////////////////////////////////////////////////////////////////////
	bool IsNumeric(const string& strString);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Pad
	// Description: This function adds an asterix (*) to the data and pads to 
	//				the given length with random characters.
	//
	// Parameters:	strInput	String to pad
	//				nMax		Length to pad
	//
	// Returns:		Padded string
	///////////////////////////////////////////////////////////////////////////////
	string Pad(const string& strInput, int nMax);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	RandomCharacter
	// Description: This function returns a random character.
	//
	// Parameters:	-
	//
	// Returns:		Random character
	///////////////////////////////////////////////////////////////////////////////
	string RandomCharacter();

private:
	///////////////////////////////////////////////////////////////////////////////
	// Function:	ToHex
	// Description: This function converts a string to a hexadecimal 
	//				representation.
	//
	// Parameters:	strData		Data string to convert to hexadecimal
	//
	// Returns:		Hexadecimal representation
	///////////////////////////////////////////////////////////////////////////////
	string ToHex(const string& strData);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	FromHex
	// Description: This function converts a hexadecimal representation to the 
	//				original string.
	//
	// Parameters:	strData		Data string to convert from hexadecimal
	//
	// Returns:		Original string
	///////////////////////////////////////////////////////////////////////////////
	string FromHex(const string& strData);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	Garble
	// Description: This function garbles a string. This process is reversible 
	//				by calling the same function again.
	//
	// Parameters:	strData		Data string to (un)garble
	//
	// Returns:		(Un)garbled string
	///////////////////////////////////////////////////////////////////////////////
	string Garble(const string& strData);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetChecksum
	// Description: This function computes a four hexadecimal digit checksum of
	//				the given string.
	//
	// Parameters:	strData		Data string to compute a checksum for
	//
	// Returns:		Four digit hexadecimal checksum
	///////////////////////////////////////////////////////////////////////////////
	string GetChecksum(const string& strData);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	CheckTimeLockFormat
	// Description: This function checks whether the dates for the time lock are 
	//				in the correct format.
	//
	// Parameters:	strTimeLock	Timelock data to check
	//
	// Returns:		true		Time lock format is correct
	//				false		Time lock format is incorrect
	///////////////////////////////////////////////////////////////////////////////
	bool CheckTimeLockFormat(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	CheckStartDate
	// Description: This function checks if the current date conflicts with 
	//				the start date of the time lock or not.
	//
	// Parameters:	strTimeLock	Data string specifying the time lock
	//
	// Returns:		true		Time lock start date is satisfied
	//				false		Time lock start date is not satisfied
	///////////////////////////////////////////////////////////////////////////////
	bool CheckStartDate(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	CheckEndDate
	// Description: This function checks if the current date conflicts with 
	//				the end date of the time lock or not.
	//
	// Parameters:	strTimeLock	Data string specifying the time lock
	//
	// Returns:		true		Time lock end date is satisfied
	//				false		Time lock end date is not satisfied
	///////////////////////////////////////////////////////////////////////////////
	bool CheckEndDate(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetStartDate
	// Description: This function retrieves the start date from the time lock 
	//				string.
	//
	// Parameters:	strTimeLock	Data string specifying the time lock
	//
	// Returns:		Time lock start date
	///////////////////////////////////////////////////////////////////////////////
	string GetStartDate(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetEndDate
	// Description: This function retrieves the end date from the time lock 
	//				string.
	//
	// Parameters:	strTimeLock	Data string specifying the time lock
	//
	// Returns:		Time lock end date
	///////////////////////////////////////////////////////////////////////////////
	string GetEndDate(const string& strTimeLock);

	///////////////////////////////////////////////////////////////////////////////
	// Function:	GetCurrentDate
	// Description: This function retrieves the current date.
	//
	// Parameters:	nDay		Variable to store the day				(Out)
	//				nMonth		Variable to store the month				(Out)
	//				nYear		Variable to store the year				(Out)
	//
	// Returns:		-
	///////////////////////////////////////////////////////////////////////////////
	void GetCurrentDate(int& nDay, int& nMonth, int& nYear);

// Member variables
private:
	static string m_strLowercase;
	static string m_strUppercase;
	static string m_strDigits;
	static string m_strDateFormat;

	string m_strEncrypted;
	static int m_nMaxEncryptedLength;
	
	string m_strData;
	static int m_nMaxDataLength;

	string m_strNodeLock;
	static int m_nMaxNodeLockLength;

	string m_strTimeLock;
	static int m_nMaxTimeLockLength;

	static int m_nHashTableLength;
	static int m_nChecksumLength;

	static unsigned short Key::HashTable[];
};

///////////////////////////////////////////////////////////////////////////////

#endif // !KEY_H
