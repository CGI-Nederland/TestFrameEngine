/*****************************************************************************
 * $Workfile: ExprResult.cpp $
 * $Revision: 1 $
 * $Modtime: 1/30/01 12:42p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

// When symbols are longer than 255 characters, the warning is disabled.
#pragma warning(disable:4786)

#include "ExprResult.h"		// Class definition

#include <stdio.h>			// Needed for sprintf()
#include <string>

using namespace std;

#include "Context.h"
#include "Number.h"
#include "StrUtil.h"

// Definition
#define MAXPRECISION 15		// Define the maximum value of the precision number
							// to be 15.
#define BUFMAX 500			// Define the size of the character buffer in which
							// a string converted from a float is stored, to be
							// 500.
///////////////////////////////////////////////////////////////////////////////
// Construction and destruction

// Constructor
//						======================
						ExprResult::ExprResult
//						======================
( 
	const string&		strPrecision
)
{
	// Set the precision number, which is all characters from Precision
	// except the last one.
	m_strPrecNum = strPrecision.substr( 0, strPrecision.length() - 1 );

	// Set the precision conversion character, which is the last character
	// from Precision.
	m_strPrecConv = strPrecision.substr( strPrecision.length() - 1 );

	// Initialise value, type, and status.
	m_strValue = "";
	m_nType    = UNDEFINED;
	m_nStatus  = UNDEF_STATUS;
}

// Destructor
//						=======================
						ExprResult::~ExprResult()
//						=======================
{
	// Empty.						
}

///////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						===================
void					ExprResult::SetType
//						===================
(
	int					nType	// result type
)
{
	m_nType = nType;
}


//						===================
int						ExprResult::GetType() const
//						===================
{
	return m_nType;
}


//						====================
void					ExprResult::SetValue
//						====================
(
	const string&		strValue	// value
)
{
	m_strValue = strValue;
}


//						====================
const string&			ExprResult::GetValue() const
//						====================
{
	return m_strValue;
}


//						=====================
void					ExprResult::SetStatus
//						=====================
(
	int					nStatus		// result status
)
{
	m_nStatus = nStatus;
}


//						=====================
int						ExprResult::GetStatus() const
//						=====================
{
	return m_nStatus;
}


//						=======================
double*					ExprResult::GetNumValue()
//						=======================
{
	double* pdlNumValue = 0;	// default is null pointer

	// Check if the type is INT or FLOAT.
	if ( m_nType == INT || m_nType == FLOAT )
	{
		// Create a Number object for the value of result.
		Number number( m_strValue );

		// Check if the value is that of a number.
		if ( number.IsNumber() )
		{
			// Get the numerical value, and place it in the member m_dlNumValue.
			m_dlNumValue = number.GetNumValue();
			pdlNumValue  = &m_dlNumValue;
		}
	}

	return pdlNumValue;
}


//						========================
bool					ExprResult::ConvertToInt()
//						========================
{
	bool bResult = false;
	
	// Determine the current type.
	switch ( m_nType )
	{
		case INT:
		{
			// The type is already INT, so nothing changes.
			bResult = true;
			break;
		}

		case STRING:
		case UNSPECIFIED:
		{
			// In these cases, conversion to INT is only possible if the value
			// also lies in the set of integer values; check this.
			if ( HasIntValue() )
			{
				// Change type to INT.
				SetType( INT );
				bResult = true;
			}
			break;
		}
	
		case FLOAT:
		case VAR:
		default:
		{
			// In these cases, conversion to INT is not allowed.
			bResult = false;
			break;
		}
	}

	return bResult;
}


//						==========================
bool					ExprResult::ConvertToFloat()
//						==========================
{
	bool bResult = false;
	
	// Determine the current type.
	switch ( m_nType )
	{
		case FLOAT:
		{
			// The type is already FLOAT, so nothing changes.
			bResult = true;
			break;
		}

		case INT:
		{
			// Change type to FLOAT; leave value the same.
			SetType( FLOAT );
			bResult = true;
			break;
		}

		case STRING:
		case UNSPECIFIED:
		{
			// In these cases, conversion to FLOAT is only possible if the
			// value also lies in the set of float values; check this.
			if ( HasFloatValue() )
			{
				// Change type to INT.
				SetType( FLOAT );
				bResult = true;
			}
			break;
		}
	
		case VAR:
		default:
		{
			// In these cases, conversion to FLOAT is not allowed.
			bResult = false;
			break;
		}
	}

	return bResult;
}


//						===========================
bool					ExprResult::ConvertToString()
//						===========================
{
	bool bResult = false;
	
	// Determine the current type.
	switch ( m_nType )
	{
		case STRING:
		{
			// The type is already STRING, so nothing changes.
			bResult = true;
			break;
		}

		case UNSPECIFIED:
		{
			// Change type to STRING; leave value the same.
			SetType( STRING );
			bResult = true;
			break;
		}
	
		case INT:
		{
			// Change the value to that of an integer.
			IntToString();

			// Change type to STRING.
			SetType( STRING );
			bResult = true;
			break;
		}
		
		case FLOAT:
		{
			// Change the value depending on the setting Precision.
			FloatToString();

			// Change type to STRING.
			SetType( STRING );
			bResult = true;
			break;
		}
		
		case VAR:
		default:
		{
			// In these cases, conversion to STRING is not allowed.
			bResult = false;
			break;
		}
	}

	return bResult;
}


//						==========================
bool					ExprResult::ConvertFromVar
//						==========================
(
	Context&		context
)
{
	bool bResult = false;

	// Check if the type is VAR.
	if ( m_nType == VAR )
	{
		// Look the variable name up in the context.
		pair<string, int>* pprVar = context.Lookup( m_strValue );

		// Check if the variable exists by checking no null pointer was returned.
		if ( pprVar != 0 )
		{
			bResult = true;

			// Change result value to variable's contents.
			m_strValue = pprVar->first;

			// Change result type to variable's type.
			switch ( pprVar->second )
			{
				case Context::INT:
				{
					m_nType = INT;
					break;
				}

				case Context::FLOAT:
				{
					m_nType = FLOAT;
					break;
				}

				case Context::STRING:
				{
					m_nType = STRING;
					break;
				}

				case Context::UNSPECIFIED:
				{
					m_nType = UNSPECIFIED;
					break;
				}

				default:
				{
					// Internal error; set status to INTERNAL_ERROR.
					m_nStatus = INTERNAL_ERROR;
					bResult   = false;
					break;
				}
			}
		}
		else
		{
			// The variable does not exist in the context; set the status
			// to UNKNOWN_VAR_ERROR.
			m_nStatus = UNKNOWN_VAR_ERROR;
		}
	}

	return bResult;
}


//						==================================
bool					ExprResult::ConvertFromUnspecified()
//						==================================
{
	bool bResult = false;

	// Check if the type is UNSPECIFIED.
	if ( m_nType == UNSPECIFIED )
	{
		bResult = true;

		// Try to convert the value to INT, and check if this didn't succeed.
		if ( !ConvertToInt() )
		{
			// The value could not be converted to INT; now, try to convert
			// it to FLOAT, and check if this didn't succeed.
			if ( !ConvertToFloat() )
			{
				// The value could not be converted to an arithmetic type
				// (INT or FLOAT), so convert it to STRING.
				ConvertToString();
			}
		}
	}

	return bResult;
}


//						================
bool					ExprResult::IsOK() const
//						================
{
	bool bResult = false;

	// Check if status is OK.
	if ( m_nStatus == OK )
	{
		bResult = true;
	}

	return bResult;
}


//						=================
bool					ExprResult::IsInt() const
//						=================
{
	bool bResult = false;

	// Check if type is INT.
	if ( m_nType == INT )
	{
		bResult = true;
	}

	return bResult;
}


//						===================
bool					ExprResult::IsFloat() const
//						===================
{
	bool bResult = false;

	// Check if type is FLOAT.
	if ( m_nType == FLOAT )
	{
		bResult = true;
	}

	return bResult;
}


//						====================
bool					ExprResult::IsNumber() const
//						====================
{
	bool bResult = false;

	// Check if type is either INT or FLOAT.
	if ( m_nType == INT || m_nType == FLOAT )
	{
		bResult = true;
	}

	return bResult;
}


//						====================
bool					ExprResult::IsString() const
//						====================
{
	bool bResult = false;

	// Check if type is STRING.
	if ( m_nType == STRING )
	{
		bResult = true;
	}

	return bResult;
}


//						=========================
bool					ExprResult::IsUnspecified() const
//						=========================
{
	bool bResult = false;

	// Check if type is UNSPECIFIED.
	if ( m_nType == UNSPECIFIED )
	{
		bResult = true;
	}

	return bResult;
}


//						=============================
bool					ExprResult::InterpretAsNumber() const
//						=============================
{
	// Determine if the result has either an integer or a floating point value.
	return ( HasIntValue() || HasFloatValue() );
}

///////////////////////////////////////////////////////////////////////////////
// Implementation

//						=======================
bool					ExprResult::HasIntValue() const
//						=======================
{
	// Create a Number object for the value of result.
	Number number( m_strValue );

	// Check if the value is that of an integer; return the result.
	return number.IsInt();
}


//						=========================
bool					ExprResult::HasFloatValue() const
//						=========================
{
	// Create a Number object for the value of result.
	Number number( m_strValue );

	// Check if the value is that of a float; return the result.
	return number.IsFloat();
}


//						=======================
void					ExprResult::IntToString()
//						=======================
{
	// Create a Number object for the value.
	Number number( m_strValue );

	// Determine if the number is an integer.
	if ( number.IsInt() )
	{
		// Change the value to that of the number's integer part.
		m_strValue = number.GetIntegerPart();
	}
}


//						=========================
void					ExprResult::FloatToString()
//						=========================
{
	// Create a Number object for the value.
	Number number( m_strValue );

	// Get the numerical value.
	double dlNumVal = number.GetNumValue();

	string strPrecNum = m_strPrecNum;	// precision number

	// Check if the precision number is "*".
	if ( m_strPrecNum == "*" )
	{
		// Depending on conversion character, the precision number must
		// be either the precision or the significance of value; determine
		// if this conversion character is G or g.
		int nPrecNum;
		if ( m_strPrecConv == "G" || m_strPrecConv == "g" )
		{
			// The precision number must be taken as the significance of
			// value; use the Number object to determine it.
			nPrecNum = number.GetSignificance();
		}
		else
		{
			// The precision number must be taken as the precision of value;
			// use the Number object to determine it.
			nPrecNum = number.GetPrecision();
		}

		// Determine if the precision number is larger than its maximum
		// allowed value.
		if ( nPrecNum > MAXPRECISION )
		{
			// Set the precision number to its maximum.
			nPrecNum = MAXPRECISION;
		}

		// Convert the precision number to a string.
		strPrecNum = IntToStr( nPrecNum );
	}

	// Create the format string for the conversion.
	string strFormat = "%." + strPrecNum + m_strPrecConv;

	// Place the new value in a char buffer.
	char cBuffer[BUFMAX];
	sprintf( cBuffer, strFormat.c_str(), dlNumVal );
	cBuffer[BUFMAX - 1] = '\0';

	// Change the value into the content of the buffer.
	m_strValue = string( cBuffer );
}
