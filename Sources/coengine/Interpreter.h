/*****************************************************************************
 * $Workfile: Interpreter.h $
 * $Revision: 5 $
 * $Modtime: 4/21/00 1:12a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
using namespace std;

// Forward declarations
class	ComposedInterpreter;
class	Setting;
class	ParameterPart;
class	MasterSlavePart;
class	ActionWordPart;
class	ActionWord;
class	SlaveList;

////////////////////////////////////////////////////////////////////////////////
// class Interpreter

class Interpreter 
{
// Construction and destruction
public:
	Interpreter(){};						// Default constructor
	virtual ~Interpreter() {};				// Destructor

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret
	//
	// description	: Interprets the string
	//					
	// parameters	: string				test line
	//
	// returns		: true					Interpretation ok
	//				  false					Interpretation error
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret(string& strTestLine) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheComposedInterpreter
	//
	// description	: Get association to composed interpreter
	//					
	// parameters	: None.
	//
	// returns		: ComposedInterpreter*		association to composed interpreter
	//				  
	///////////////////////////////////////////////////////////////////////////////
	ComposedInterpreter* GetTheComposedInterpreter()
	{ return m_pTheComposedInterpreter; };


	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheComposedInterpreter
	//
	// description	: Set association to composed interpreter
	//					
	// parameters	: ComposedInterpreter*		association to composed interpreter
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheComposedInterpreter(ComposedInterpreter* value)
	{ m_pTheComposedInterpreter = value; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheParameterPart
	//
	// description	: Get association to parameter part
	//					
	// parameters	: None.
	//
	// returns		: ParameterPart*		association to parameter part
	//				  
	///////////////////////////////////////////////////////////////////////////////
	ParameterPart* GetTheParameterPart() const
	{ return m_pTheParameterPart; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheParameterPart
	//
	// description	: Set the association to parameterpart 
	//					
	// parameters	: ParameterPart*		association to parameter part
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheParameterPart(ParameterPart* value)
	{ m_pTheParameterPart = value; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheMasterSlavePart
	//
	// description	: Get association to masterslave part
	//					
	// parameters	: None.
	//
	// returns		: MasterSlavePart*		association to masterslave part
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const MasterSlavePart* GetTheMasterSlavePart() const
	{ return m_pTheMasterSlavePart; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheMasterSlavePart
	//
	// description	: Set association to masterslave part
	//					
	// parameters	: MasterSlavePart*		association to masterslave part
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheMasterSlavePart(MasterSlavePart* value)
	{ m_pTheMasterSlavePart = value; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheSlaveList
	//
	// description	: Get association to slavelist
	//					
	// parameters	: None.
	//
	// returns		: SlaveList*			association to masterslave part
	//				  
	///////////////////////////////////////////////////////////////////////////////
	SlaveList* GetTheSlaveList() const
	{ return m_pTheSlaveList; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheSlaveList
	//
	// description	: Set association to slavelist
	//					
	// parameters	: SlaveList*			association to slavelist part
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheSlaveList(SlaveList* pSlaveList)
	{ m_pTheSlaveList = pSlaveList; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheActionWordPart
	//
	// description	: Get association to actionword part
	//					
	// parameters	: None.
	//
	// returns		: ActionWordPart*		association to actionword part
	//				  
	///////////////////////////////////////////////////////////////////////////////
	ActionWordPart* GetTheActionWordPart()
	{ return m_pTheActionWordPart; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheActionWordPart
	//
	// description	: Set association to actionword part
	//					
	// parameters	: ActionWordPart*		association to actionword part
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheActionWordPart(ActionWordPart* value)
	{ m_pTheActionWordPart = value; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheActionWord
	//
	// description	: Get association to actionword
	//					
	// parameters	: None.
	//
	// returns		: ActionWord*			association to actionword
	//				  
	///////////////////////////////////////////////////////////////////////////////
	ActionWord* GetTheActionWord() const
	{ return m_pTheActionWord; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheActionWord
	//
	// description	: Set association to actionword.
	//					
	// parameters	: ActionWord*				association to composed interpreter
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheActionWord(ActionWord* value)
	{ m_pTheActionWord = value; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetInterpreterMode
	//
	// description	: Sets the interpreter mode, FIXED or FREE.
	//					
	// parameters	: int						Interpreter::Mode
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetInterpreterMode(int nMode)
	{ m_nInterpreterMode = nMode; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetInterpreterMode
	//
	// description	: Gets the interpreter mode, FIXED or FREE.
	//					
	// parameters	: None,
	//
	// returns		: int						Interpreter::InterpreterMode
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const int GetInterpreterMode() const
	{ return m_nInterpreterMode; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetMasterSlaveMode
	//
	// description	: Sets the masterslave mode.
	//					
	// parameters	: int						Interpreter::MasterSlaveMode
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetMasterSlaveMode(int nMode)
	{ m_nMasterSlaveMode = nMode; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetMasterSlaveMode
	//
	// description	: Gets the masterslave mode, STANDALONE or MASTERSLAVE
	//					
	// parameters	: None.
	//
	// returns		: int						Interpreter::MasterSlaveMode
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const int GetMasterSlaveMode() const
	{ return m_nMasterSlaveMode; };

protected:		// These are only used by subclasses of interpreter.

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLine
	//
	// description	: Fetches the current line to interpret
	//					
	// parameters	: None.
	//
	// returns		: string&					line to interpret
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const string& GetLine() const
	{ return m_strLine; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetLine
	//
	// description	: Sets the line to interpret
	//					
	// parameters	: string					line to interpret
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetLine(string& strValue)
	{ m_strLine = strValue; };

// Class constants

	enum InterpreterMode { FREE, FIXED };
	enum MasterSlaveMode { MASTERSLAVE, STANDALONE };
 
// Member variables
private:
	string	m_strLine;				// Line to interpret
	int		m_nInterpreterMode;		// FIXED of FREE
	int		m_nMasterSlaveMode;		// STANDALONE or MASTERSLAVE

	// Data Members for Associations
 
	static ComposedInterpreter*	m_pTheComposedInterpreter;		// association ComposedInterpreter 
	static ParameterPart*		m_pTheParameterPart;			// association ParameterPart
	static MasterSlavePart*		m_pTheMasterSlavePart;			// association MasterSlavePart
	static ActionWordPart*		m_pTheActionWordPart;			// association ActionWordPart
	static ActionWord*			m_pTheActionWord;				// association ActionWord
	static SlaveList*			m_pTheSlaveList;				// association SlaveList
};

#endif // !INTERPRETER_H