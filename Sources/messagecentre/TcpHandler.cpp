/*****************************************************************************
 * $Workfile: TcpHandler.cpp $
 * $Revision: 2 $
 * $Modtime: 4/21/00 1:23a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <sstream>
using namespace std;

#include "TcpHandler.h"


///////////////////////////////////////////////////////////////////////////////

//						=====================
bool					TcpHandler::GetString
//						=====================
(
	string				strArgument,
	int					nPosition,
	string&				strString
)
{
	bool bResult = false;
	int nFirstPosition = 0;
	int nSecondPosition = 0;

	// Position has to be zero or greater
	if (nPosition >= 0)
	{
		// Find the two colons
		for (int i = 0; i <= nPosition; i++)
		{
			nFirstPosition = nSecondPosition;
			nSecondPosition = strArgument.find_first_of(":", nFirstPosition+1);
		}

		if (nFirstPosition != string::npos)
		{
			// Cut the part out of the string
			if ((nFirstPosition == 0) && (nSecondPosition != string::npos))
			{ strArgument = strArgument.substr(nFirstPosition, nSecondPosition); }
			else if ((nFirstPosition == 0) && (nSecondPosition == string::npos))
			{ strArgument = strArgument.substr(nFirstPosition, strArgument.length()); }
			else
			{ strArgument = strArgument.substr(nFirstPosition+1, 
									nSecondPosition-nFirstPosition-1); }


			strString = strArgument;
			bResult = true;
		}
	}

	return bResult;
}

//						======================
bool					TcpHandler::GetInteger
//						======================
(
	string				strArgument,
	int					nPosition,
	int&				nInteger
)
{
	bool bResult = false;
	string strInteger;

	// Get the string at that position
	if (GetString(strArgument, nPosition, strInteger))
	{
		// Convert to an integer
		istringstream stream(strInteger);
		stream >> nInteger;
		
		// Check the result of the conversion
		bResult = !stream.fail();
	}

	return bResult;
}

///////////////////////////////////////////////////////////////////////////////