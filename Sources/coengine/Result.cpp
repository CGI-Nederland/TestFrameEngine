/*****************************************************************************
 * $Workfile: Result.cpp $
 * $Revision: 17 $
 * $Modtime: 6/18/01 5:13p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include "Result.h"

#include <string>

using namespace std;

#include "IOFactory.h"
#include "IOInterface.h"

///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

//				===============
				Result::~Result()
//				===============
{
	if ( m_pIOInterface != 0 )
	{
		IOFactory Factory;
		Factory.DestroyIOInterface(m_pIOInterface); 
	}
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//				============
bool			Result::Read
//				============
(
  string&	strLine
)
{
	bool bResult = false;

	// Reads a complete line from the io source
	// and puts it in strLine.
	if ( m_pIOInterface != 0 )
	{ bResult = m_pIOInterface->Read(strLine); }

	return bResult;
}

//				=============
bool			Result::Write
//				=============
(
  const string&	strLine
)
{
	bool bResult = false;

	// Writes strLine as a complete line to the io source.
	if ( m_pIOInterface != 0 )
	{ bResult = m_pIOInterface->Write(strLine); }

	return bResult;
}

//				============
bool			Result::Open
//				============
(
const string&	strFilename,
int				nMode
)
{

	bool bOpen= false;

	// First check if the m_pIOInterface is not already used
	// This can happen if CreateLog is called after UseLog
	// In that case return false

	if (m_pIOInterface == 0)
	{

		IOFactory Factory;
		m_pIOInterface = Factory.CreateIOInterface(strFilename); 

		switch (nMode)
		{
			case WRITE:
			{
				m_pIOInterface->Open(strFilename, IOInterface::IOWRITE);
				bOpen = m_pIOInterface->IsOpen();
				break;
			}
			case READ:
			{
				m_pIOInterface->Open(strFilename, IOInterface::IOREAD);
				bOpen = m_pIOInterface->IsOpen();
				break;
			}

			default:
			{
				// error
				break;
			}
		}
	}
	
	// reset pointer to IOInterface if file could not be opened
	if (!bOpen)
	{
		m_pIOInterface = 0;
	}

	return bOpen;
}


//				=============
void			Result::Close()
//				=============
{
	// Check if the IOInterface pointer is initialized
	if (m_pIOInterface != 0 )
	{
		// Check if the file is open.
		if(m_pIOInterface->IsOpen())
		{
			// Close the file.
			m_pIOInterface->Close();
		}

		IOFactory Factory;
		// Destroy the IOInterface pointer
		Factory.DestroyIOInterface(m_pIOInterface);
		// Give IOInterface pointer valid start value.
		m_pIOInterface = 0;
	}
}


//				==================
bool			Result::FileExists
//				==================
(
const string& filename
)
{
	IOFactory Factory;

	// Test if the file already exists.
	return Factory.Exist(filename); 	
}

