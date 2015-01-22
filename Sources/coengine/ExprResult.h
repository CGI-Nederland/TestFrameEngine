/*****************************************************************************
 * $Workfile: ExprResult.h $
 * $Revision: 4 $
 * $Modtime: 1/30/01 12:42p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef EXPRRESULT_H
#define EXPRRESULT_H

#include <string>

using namespace std;

// Forward declarations
class Context;

////////////////////////////////////////////////////////////////////////////////
// class ExprResult
class ExprResult
{
	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ExprResult
	//
	// parameters	: pSetting		pointer to Setting object
	///////////////////////////////////////////////////////////////////////////////
	explicit ExprResult( const string& strPrecision );

private:
	ExprResult();						// Default constructor

	// A definition of a copy constructor is omitted, so the default copy
	// constructor is used.

public:
	~ExprResult();						// Destructor

	////////////////////////////////////////////////////////////////////////////
	// ATTRIBUTES AND OPERATIONS
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: SetType()
	//
	// description	: This function sets the result type.
	//					
	// parameters	: nType		result type
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetType( int nType );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetType()
	//
	// description	: This function returns the result type.
	//					
	// parameters	: None
	//
	// returns		: integer specifying the return type
	///////////////////////////////////////////////////////////////////////////////
	int GetType() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetValue()
	//
	// description	: This function sets the value.
	//					
	// parameters	: strValue		value
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetValue( const string& strValue );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetValue()
	//
	// description	: This function returns the value.
	//					
	// parameters	: None
	//
	// returns		: string containing the value
	///////////////////////////////////////////////////////////////////////////////
	const string& GetValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetStatus()
	//
	// description	: This function sets the result status.
	//					
	// parameters	: nStatus		result status
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void SetStatus( int nStatus );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetStatus()
	//
	// description	: This function returns the result status.
	//					
	// parameters	: None
	//
	// returns		: integer specifying the result status
	///////////////////////////////////////////////////////////////////////////////
	int GetStatus() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetNumValue()
	//
	// description	: This function returns (a pointer to) the numerical value.
	//				  This value is determined by the value and the result type.
	//				  Only if the type is INT or FLOAT, and if the value is that of
	//				  a number, can a value be returned; otherwise, the null
	//				  pointer is returned.
	//					
	// parameters	: None
	//
	// returns		: pointer to the double containing the numerical value; if it
	//				  is the null pointer, there is no numerical value
	///////////////////////////////////////////////////////////////////////////////
	double* GetNumValue();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertToInt()
	//
	// description	: This function converts the result to type INT. This is only
	//				  possible: when the type is already INT; depending on the
	//				  value, when the type is STRING or UNSPECIFIED.
	//					
	// parameters	: None
	//
	// returns		: true		result converted to INT
	//				  false		result could not be converted to INT
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertToInt();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertToFloat()
	//
	// description	: This function converts the result to type FLOAT. This is only
	//				  possible: when the type is already FLOAT; when the type is
	//				  INT; depending on the value, when the type is STRING or 
	//				  UNSPECIFIED.
	//					
	// parameters	: None
	//
	// returns		: true		result converted to FLOAT
	//				  false		result could not be converted to FLOAT
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertToFloat();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertToString()
	//
	// description	: This function converts the result to type STRING. This is
	//				  possible, unless the type is VAR. When the type is FLOAT, the
	//				  value may also be changed.
	//					
	// parameters	: None
	//
	// returns		: true		result converted to STRING
	//				  false		result could not be converted to STRING
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertToString();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertFromVar()
	//
	// description	: This function converts the result from type VAR to the type
	//				  of the variable's value; also, the value is changed from the
	//				  variable's name to its content. All this is only possible if
	//				  the type is VAR, and if the variable is present in the
	//				  specified context.
	//					
	// parameters	: context	context in which the variable should be pressent
	//
	// returns		: true		result converted from VAR
	//				  false		result could not be converted from VAR
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertFromVar( Context& context );

	///////////////////////////////////////////////////////////////////////////////
	// function		: ConvertFromUnspecified()
	//
	// description	: This function converts the result from type UNSPECIFIED to
	//				  one of the types, INT, FLOAT, or STRING. It does so in the
	//				  following order: if it can be converted to an INT, it is
	//				  converted to an INT; otherwise, if it can be converted to a
	//				  FLOAT, it is converted to a FLOAT; otherwise, it is converted
	//				  to a STRING.
	//					
	// parameters	: None
	//
	// returns		: true		result converted from UNSPECIFIED
	//				  false		result could not be converted from UNSPECIFIED
	///////////////////////////////////////////////////////////////////////////////
	bool ConvertFromUnspecified();

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsOK()
	//
	// description	: This function states whether the result status is OK.
	//					
	// parameters	: None
	//
	// returns		: true		status is OK
	//				  false		status is not OK
	///////////////////////////////////////////////////////////////////////////////
	bool IsOK() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsInt()
	//
	// description	: This function states whether the result type is INT.
	//					
	// parameters	: None
	//
	// returns		: true		type is INT
	//				  false		type is not INT
	///////////////////////////////////////////////////////////////////////////////
	bool IsInt() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsFloat()
	//
	// description	: This function states whether the result type is FLOAT.
	//					
	// parameters	: None
	//
	// returns		: true		type is FLOAT
	//				  false		type is not FLOAT
	///////////////////////////////////////////////////////////////////////////////
	bool IsFloat() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsNumber()
	//
	// description	: This function states whether the result type is a number
	//				  type; i.e. whether the type is either INT or FLOAT.
	//					
	// parameters	: None
	//
	// returns		: true		type is a number type
	//				  false		type is not a number type
	///////////////////////////////////////////////////////////////////////////////
	bool IsNumber() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsString()
	//
	// description	: This function states whether the result type is STRING.
	//					
	// parameters	: None
	//
	// returns		: true		type is STRING
	//				  false		type is not STRING
	///////////////////////////////////////////////////////////////////////////////
	bool IsString() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IsUnspecified()
	//
	// description	: This function states whether the result type is UNSPECIFIED.
	//					
	// parameters	: None
	//
	// returns		: true		type is UNSPECIFIED
	//				  false		type is not UNSPECIFIED
	///////////////////////////////////////////////////////////////////////////////
	bool IsUnspecified() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: InterpretAsNumber()
	//
	// description	: This function determines if the the value can be interpreted
	//				  as a number; i.e., if the value can be that of an integer or
	//				  a floating point.
	//					
	// parameters	: None
	//
	// returns		: true		result can be a number
	//				  false		result can not be a number
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretAsNumber() const;

private:
	////////////////////////////////////////////////////////////////////////////
	// IMPLEMENTATION

	///////////////////////////////////////////////////////////////////////////////
	// function		: HasIntValue()
	//
	// description	: This function determines whether the value (regardless of
	//				  type) belongs to the set of integer values.
	//					
	// parameters	: None
	//
	// returns		: true		result has integer value
	//				  false		result does not have integer value
	///////////////////////////////////////////////////////////////////////////////
	bool HasIntValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: HasFloatValue()
	//
	// description	: This function determines whether the value (regardless of
	//				  type) belongs to the set of float values.
	//					
	// parameters	: None
	//
	// returns		: true		result has float value
	//				  false		result does not have float value
	///////////////////////////////////////////////////////////////////////////////
	bool HasFloatValue() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: IntToString()
	//
	// description	: This function changes the value to that of an integer; i.e.,
	//				  enclosing spaces are removed, as well as leading zeros.
	//					
	// parameters	: None
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void IntToString();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: FloatToString()
	//
	// description	: This function changes, depending on the setting Precision, 
	//				  the value to that of a floating point number. The precision 
	//				  may be changed, as well as the exponent.
	//					
	// parameters	: None
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void FloatToString();

// Constants
public:
	enum TYPE	{	INT,			// integer constant
					FLOAT,			// float constant
					STRING,			// string constant
					UNSPECIFIED,	// constant of unspecified type
					VAR,			// variable name
					UNDEFINED
				};

	enum STATUS	{	OK,
					UNKNOWN_VAR_ERROR,
					ASSIGN_NO_VAR_ERROR,
					SUB_NO_NUM_ERROR,
					MUL_NO_NUM_ERROR,
					DIV_NO_NUM_ERROR,
					DIV_BY_ZERO_ERROR,
					INTERNAL_ERROR,
					UNDEF_STATUS
				};

// Member variables
private:
	string	m_strPrecNum;		// Precision number from Setting
	string  m_strPrecConv;		// Precision conversion character from Setting
	int		m_nType;			// Result type
	string	m_strValue;			// Value
	double	m_dlNumValue;		// Numerical value
	int		m_nStatus;			// Result status
};

#endif // !EXPRRESULT_H
