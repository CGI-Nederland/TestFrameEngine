/*****************************************************************************
 * $Workfile: ComposedInterpreter.h $
 * $Revision: 12 $
 * $Modtime: 3/14/01 12:51p $
 * $Author: Lw $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999-2001 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef COMPOSEDINTERPRETER_H
#define COMPOSEDINTERPRETER_H

#undef BASECLASS
#define BASECLASS Interpreter

// Includes
#include <string>
#include <vector>

#include "Interpreter.h"				// Baseclass definition

// Forward declarations
class Context;
class EngineSetting;
class Log;
class ParameterPart;
class SlaveList;

////////////////////////////////////////////////////////////////////////////////
// class Interpreter
class ComposedInterpreter : public BASECLASS 
{
	// Construction and destruction
private:
	ComposedInterpreter();									// Default constructor

	ComposedInterpreter(const ComposedInterpreter& right);	// Copy constuctor

	// Other constructors
public:
	///////////////////////////////////////////////////////////////////////////////
	// function		: ComposedInterpreter
	//
	// description	: Constructs the composedinterpreter object
	//					
	// parameters	: ActionWord*		association to actionword 		   
	//				  SlaveList*		association to slavelist
	//
	// returns		: None (constructor)
	//				  
	///////////////////////////////////////////////////////////////////////////////
	ComposedInterpreter(ActionWord* pActionWord, SlaveList* pSlaveList);

	virtual ~ComposedInterpreter();							// Destructor

	// Attributes and operations

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialise()
	//
	// description	: Initialises the composed interpreter with values from the
	//				  setting object;
	//					
	// parameters	: Seting*					association to setting
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Initialise(EngineSetting* pSetting);

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Interpret()
	//
	// description	:	This function interprets all the arguments of a specified
	//					cluster line.
	//					
	// parameters	:	strLine		line to interpret
	//
	// returns		:	true		specified line is valid
	//					false		specified line is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret( const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	Interpret()
	//
	// description	:	This function interprets a specified cluster line; all
	//					arguments except the parameters are parsed; i.e., in
	//					standalone mode only the action word, and in Master mode
	//					only the slave name and the action word.
	//					
	// parameters	:	strLine		line to interpret
	//
	// returns		:	true		specified line is valid
	//					false		specified line is invalid
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretExceptParameters( const string& strLine );

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionType
	//
	// description	: Returns actiontype.
	//				  Only valid after succesfull interpretation.
	//					
	// parameters	: None.
	//
	// returns		: int				ActionWordList::ActionType
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetActionType();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionType
	//
	// description	: Returns actiontype, of the given testline without changing the
	//				  state of the interpreter.
	//				  		
	// parameters	: string			Testline
	//
	// returns		: int				ActionWordList::ActionType
	//				  
	///////////////////////////////////////////////////////////////////////////////
	int GetActionType(const string& strTestLine);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetActionType
	//
	// description	: Set the actiontype.
	//					
	// parameters	: int				ActionWordList::ActionType
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetActionType(int nActionType);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordFunction
	//
	// description	: Returns actionword function
	//				  Only valid after succesfull interpretation.
	//					
	// parameters	: None.
	//
	// returns		: string&			actionword function
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const string& GetActionWordFunction();

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetActionWordFunction
	//
	// description	: Sets actionword function
	//					
	// parameters	: string			Actionword function
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetActionWordFunction(const string& strActionWordFunction);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSlaveName
	//
	// description	: Returns slavename
	//				  Only valid after succesfull interpretation.
	//					
	// parameters	: None.
	//
	// returns		: string			Slavename
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const string& GetSlaveName();

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetSlaveName
	//
	// description	: Returns actiontype.
	//				  Only valid after succesfull interpretation.
	//					
	// parameters	: string			Slavename
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetSlaveName(const string& strSlaveName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddParameter
	//
	// description	: Adds parameter to parameter list.
	//					
	// parameters	: string			parameter
	//
	// returns		: int				ActionWordList::ActionType
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void AddParameter(const string& strParameter);

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddKeepName
	//
	// description	: Add keep variable name to the keep vector
	//					
	// parameters	: string			variable name
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void AddKeepName(const string& strKeepName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddKeepIndex
	//
	// description	: Add keep index to the keep vector
	//					
	// parameters	: int				keep index
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void AddKeepIndex(int nKeepIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: InKeepVector
	//
	// description	: This function determines if an argument whose index is
	//				  specified contains the keep command. If it does, the
	//				  referenced string parameter is filled with the name of the
	//				  cluster variable that is to be kept.
	//					
	// parameters	: nIndex			index of argument to check for keep command
	//				  REF strKeepName	to be filled with name of variable in keep
	//										command
	//
	// returns		: TRUE		argument contains keep command
	//				  FALSE		argument does not contain keep command
	///////////////////////////////////////////////////////////////////////////////
	bool InKeepVector(int nIndex, string& strKeepName);
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: AddSnapName
	//
	// description	: Add snap name to the snap vector
	//					
	// parameters	: strSnapName		name to add
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void AddSnapName(const string& strSnapName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddSnapIndex
	//
	// description	: Add index of snapped argument the snap vector
	//					
	// parameters	: nIndex		argument index to add
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void AddSnapIndex(int nIndex);

	///////////////////////////////////////////////////////////////////////////////
	// function		: InSnapVector
	//
	// description	: This function determines if an argument whose index is
	//				  specified contains the snap command. If it does, the
	//				  referenced string parameter is filled with the snap identifier.
	//					
	// parameters	: nIndex			index of argument to check for snap command
	//				  REF strSnapName	to be filled with snap identifier
	//
	// returns		: TRUE		argument contains snap command
	//				  FALSE		argument does not contain snap command
	///////////////////////////////////////////////////////////////////////////////
	bool InSnapVector(int nIndex, string& strSnapName);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetActionWordValidity
	//
	// description	: Sets the actionword validity flag
	//					
	// parameters	: true						actionword valid
	//				  false						actionword invalid
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetActionWordValidity(bool bValidity);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetActionWordValidity
	//
	// description	: Gets the actionword validity flag
	//					
	// parameters	: None.
	//
	// returns		: true						actionword valid
	//				  false						actionword invalid
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool GetActionWordValidity();

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetSlaveNameValidity
	//
	// description	: Sets the slavenane validity flag
	//					
	// parameters	: true						slavename valid
	//				  false						slavename invalid
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetSlaveNameValidity(bool bValidity);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetSlaveNameValidity
	//
	// description	: Gets the slavename validity flag
	//					
	// parameters	: None.
	//
	// returns		: true						slavename valid
	//				  false						slavename invalid
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool GetSlaveNameValidity();

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetParametersValidity
	//
	// description	: Sets the parameters validity flag
	//					
	// parameters	: true						parameters valid
	//				  false						parameters invalid
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetParametersValidity(bool bValidity);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParametersValidity
	//
	// description	: Gets the parameters validity flag
	//					
	// parameters	: None.
	//
	// returns		: true						parameters valid
	//				  false						parameters invalid
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool GetParametersValidity();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameters
	//
	// description	: Fetches the parameters.
	//					
	// parameters	: None.
	//
	// returns		: vector<string>&			string vector of parameters
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const vector<string>& GetParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetErrorVector
	//
	// description	: Fetches the error vector
	//					
	// parameters	: None.
	//
	// returns		: vector<string>&			string vector of error messages
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const vector<string>& GetErrorVector();

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetErrorVector
	//
	// description	: Sets the errorvector 
	//					
	// parameters	: vector<string>&			string vector of parameters
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetErrorVector(const vector<string>& vstrErrorVector);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetContext
	//
	// description	: Sets the context to use for evaluation of expressions
	//					
	// parameters	: Context*					association to context object
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetContext(Context* pContext);

	// Implementation
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		:	SplitLine()
	//
	// description	:	This function splits up a specified line into its
	//					arguments, which are separated by a specified delimiter.
	//					
	// parameters	:	strLine			cluster line to be split
	//					strDelimiter	delimiter string
	//
	// returns		:	vector containing the line's arguments
	///////////////////////////////////////////////////////////////////////////////
	vector<string> SplitLine( const string& strLine, const string& strDelimiter );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretLine()
	//
	// description	:	This function interprets the arguments of a specified line.
	//					A specified boolean determines whether all arguments must
	//					be parsed as described above, or whether only the arguments
	//					except the parameters are to be parsed.
	//					
	// parameters	:	strLine			cluster line to be interpreted
	//					bNoParameters	whether or not the parameters of the line
	//									are not to be parsed
	//
	// returns		:	true	the specified line is a valid cluster line
	//					false	the specified line is an invalid cluster line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretLine( const string& strLine, bool bNoParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretStandaloneArguments()
	//
	// description	:	This function interprets the specified argument vector as
	//					those of a cluster line in standalone mode; i.e., the first
	//					argument is	interpreted as an action word, and all other
	//					arguments as its parameters. A specified boolean determines
	//					whether all	arguments must be parsed, or only the action
	//					word.
	//					
	// parameters	:	vstrArguments	argument vector to be interpreted
	//					bNoParameters	whether or not the parameters of the line
	//									are not to be parsed
	//
	// returns		:	true	the arguments are those of a valid standalone line
	//					false	the arguments are not those of a valid standalone
	//							line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretStandaloneArguments(	const vector<string>& vstrArguments,
										bool bNoParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		:	InterpretMasterArguments()
	//
	// description	:	This function interprets the specified argument vector as
	//					those of a cluster line in Master mode; i.e., the first
	//					argument is	interpreted as a slave name, the second one as
	//					an action word, and all other arguments as its parameters.
	//					The action word and parameters are only parsed if they are
	//					meant for the Master Engine	(this one,) which is so if the
	//					Slave name is an empty string. A specified boolean
	//					determines whether all arguments must be parsed as
	//					described above, or whether	only the arguments except the
	//					parameters are to be parsed.
	//
	// parameters	:	vstrArguments	argument vector to be interpreted
	//					bNoParameters	whether or not the parameters of the line
	//									are not to be parsed
	//
	// returns		:	true	the arguments are those of a valid Master line
	//					false	the arguments are not those of a valid Master line
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretMasterArguments(	const vector<string>& vstrArguments,
									bool bNoParameters );

	///////////////////////////////////////////////////////////////////////////////
	// function		: InterpretParameter
	//
	// description	: 
	//					
	// parameters	: strParameter
	//				  nArgument
	//
	// returns		: 
	///////////////////////////////////////////////////////////////////////////////
	bool InterpretParameter(const string& strParameter, int nArgument);

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearParameters
	//
	// description	: Clears the parameter vector
	//					
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void ClearParameters();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearErrorVector
	//
	// description	: Clears the error vector
	//					
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void ClearErrorVector();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearKeepVector
	//
	// description	: Clears the keep vector (variable name and index)
	//					
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void ClearKeepVector();

	///////////////////////////////////////////////////////////////////////////////
	// function		: ClearSnapVector
	//
	// description	: Clears the snap vectors (name and index)
	//					
	// parameters	: None.
	//
	// returns		: void
	///////////////////////////////////////////////////////////////////////////////
	void ClearSnapVector();

	// Member variables
private:
	int				m_nActionType;					// Action type
	string			m_strActionWordFunction;		// Action word function
	string			m_strSlaveName;					// Slavename
	vector<string>	m_vstrParameters;				// Parameter vector
	vector<string>	m_vstrErrorVector;				// Error vector
	vector<string>	m_vstrKeepName;					// Keep variable name
	vector<string>	m_vstrSnapName;
	vector<int>		m_vnKeepIndex;					// Keep index
	vector<int>		m_vnSnapIndex;
	bool			m_bActionWordValidity;			// Actionword validity
	bool			m_bSlaveNameValidity;			// Slavename validity
	bool			m_bParametersValidity;			// Parameters validity
};

#undef BASECLASS
#endif // !COMPOSEDINTERPRETER_H
