/*****************************************************************************
 *$Workfile: ParameterPart.h $
 *$Revision: 11 $
 *$Modtime: 5/10/00 5:28p $
 *$Author: Aa $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef PARAMETERPART_H
#define PARAMETERPART_H

#undef BASECLASS
#define BASECLASS Interpreter

#include <vector>
#include <string>

using namespace std;

#include "Interpreter.h"		// Baseclass definition

// Forward declarations
class Context;
class EngineSetting;
class Parser;
class AnythingCommand;
class KeepCommand;
class SnapCommand;
class EmptyCommand;
class NotEmptyCommand;
class SpacesCommand;
class ExpressionCommand;
class DateCommand;
class TimeCommand;
class ReferCommand;

////////////////////////////////////////////////////////////////////////////////
// class ParameterPart
class ParameterPart : public BASECLASS  
{
	// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of ParameterPart
	///////////////////////////////////////////////////////////////////////////////
	ParameterPart();

	ParameterPart(ParameterPart&);
	ParameterPart& operator=(ParameterPart&);

	///////////////////////////////////////////////////////////////////////////////
	// destructor of ParameterPart
	///////////////////////////////////////////////////////////////////////////////
	~ParameterPart();
	
	///////////////////////////////////////////////////////////////////////////////
	// function		: Interpret
	//
	// description	: Interprets a parameter
	//					
	// parameters	: string			parameter
	//
	// returns		: true				interpretation ok
	//				  false				interpretation error
	//				  
	///////////////////////////////////////////////////////////////////////////////
	bool Interpret(const string& strTestline);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTheParser
	//
	// description	: Sets the association to the parser
	//					
	// parameters	: Parser*			parser association
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetTheParser(Parser* pParser)
	{ m_pTheParser = pParser; };


	///////////////////////////////////////////////////////////////////////////////
	// function		: GetTheParser
	//
	// description	: Gets the association to parser
	//					
	// parameters	: None. 
	//
	// returns		: Parser*				association to parser
	//				  
	///////////////////////////////////////////////////////////////////////////////
	Parser* GetTheParser()
	{ return m_pTheParser; };

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetErrorVector
	//
	// description	: Gets reference to error string vector
	//					
	// parameters	: None.
	//
	// returns		: vector<string>&		Error vector
	//				  
	///////////////////////////////////////////////////////////////////////////////
	const vector<string>& GetErrorVector() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetContext
	//
	// description	: Set the context to be used by parser for parameter evaluation
	//					
	// parameters	: Context*				association to kernelcommand
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void SetContext(Context* pContext);

	///////////////////////////////////////////////////////////////////////////////
	// function		: Initialise()
	//
	// description	: Initialises the parameterpart with values from the
	//				  setting object;
	//					
	// parameters	: Setting*					association to setting
	//
	// returns		: None.
	//				  
	///////////////////////////////////////////////////////////////////////////////
	void Initialise(EngineSetting* pSetting);


	///////////////////////////////////////////////////////////////////////////////
	// function		: GetParameterType()
	//
	// description	: returns last parameter type
	//
	//					
	// parameters	: none
	//
	// returns		: int						Parameterpart::PARAMETERTYPE
	//
	///////////////////////////////////////////////////////////////////////////////
	int	GetParameterType()
	{ return m_nParameterType; }

	// Private member functions
private:
	///////////////////////////////////////////////////////////////////////////////
	// function		: CreateCommandEvalOrder
	//
	// description	: This function sorts the commands in the order in which they
	//				  are to be evaluated. This order is determined by comparing
	//				  the length of the corresponding prefix and places the longest
	//				  first. This way a command whose prefix is a subset of another
	//				  one's, won't be called inadvertently.
	//					
	// parameters	: <none>
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void CreateCommandEvalOrder();

	///////////////////////////////////////////////////////////////////////////////
	// function		: AddCommandToEvalOrder
	//
	// description	: This function adds the type of a command to the vector of
	//				  commands ordered in way they are to be evaluated. The order
	//				  is determined by the length of the command prefix, in
	//				  descending order.
	//					
	// parameters	: nCommandType			enum type of the command to be placed
	//											in the vector
	//				  nCommandPrefixLength	length of the command prefix
	//				  REF vprnCommands		reference to vector of command type-
	//											prefix length pairs
	//
	// returns		: <void>
	///////////////////////////////////////////////////////////////////////////////
	void AddCommandToEvalOrder(int nCommandType, int nCommandPrefixLength, vector<pair<int, int> >& vprnCommands);

	///////////////////////////////////////////////////////////////////////////////
	// function		: IndexInCommandVector
	//
	// description	: This function determine before which index in the vector a
	//				  specified prefix length should be added.
	//					
	// parameters	: nCommandPrefixLength	length of the command prefix
	//				  vprnCommands			vector of command type-prefix length
	//											pairs
	//
	// returns		: index in vector before which nCommandPrefixLength should
	//				  be added
	///////////////////////////////////////////////////////////////////////////////
	int IndexInCommandVector(int nCommandPrefixLength, const vector<pair<int, int> >& vprnCommands);

	///////////////////////////////////////////////////////////////////////////////
	// function		: DetermineCommandType
	//
	// description	: This function determines the command enum type of a specified
	//				  argument. If the argument contains no command, the type for
	//				  LITERAL is returned.
	//
	// parameters	: strArgument			argument to scan for command
	//				
	//
	// returns		: type of the command of the specified argument
	///////////////////////////////////////////////////////////////////////////////
	int DetermineCommandType(const string& strArgument);

	// Constants
public:
	enum PARAMETERTYPE			{ 
									LITERAL,		// literal argument
									EXPRESSION,		// expression command
									REFER,			// refer command 
									KEEP,			// keep command
									SNAP,			// snap command
									SPACES,			// spaces command
									TIME,			// time command
									DATE,			// date command
									EMPTY,			// empty command
									NOTEMPTY,		// not-empty command
									ANYTHING		// anything command
								};

	// Member variables
private:
	Parser*				m_pTheParser;			// association to the parser
	AnythingCommand*	m_pAnythingCommand;		// association to the AnythingCommand
	KeepCommand*		m_pKeepCommand;			// association to the KeepCommand				
	SnapCommand*		m_pSnapCommand;			// association to the SnapCommand
	EmptyCommand*		m_pEmptyCommand;		// association to the EmptyCommand
	NotEmptyCommand*	m_pNotEmptyCommand;		// association to the NotEmptyCommand
	SpacesCommand*		m_pSpacesCommand;		// association to the SpacesCommand
	ExpressionCommand*	m_pExpressionCommand;	// association to the ExpressionCommand
	ReferCommand*		m_pReferCommand;		// association to the ReferCommand
	DateCommand*		m_pDateCommand;			// association to the DateCommand
	TimeCommand*		m_pTimeCommand;			// association to the TimeCommand

	int			m_nParameterType;				// Last interpreted parametertype
	vector<int>	m_vnCommandsInEvalOrder;		// vector of command types orded in the
												//	sequence in which they are to be
												//	evaluated
};

#undef BASECLASS
#endif // !PARAMETERPART_H