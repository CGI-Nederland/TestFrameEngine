/*****************************************************************************
 * $Workfile: BabelFish.h $
 * $Revision: 8 $
 * $Modtime: 12/01/99 3:49p $
 * $Author: Em $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/
/*	''The Babel fish,'' said The Hitch Hiker's Guide to the Galaxy quietly, 
	''is small, yellow and leech-like, and probably the oddest thing in the 
	Universe. It feeds on brainwave energy not from its carrier but from those 
	around it. It absorbs all unconscious mental frequencies from this brainwave 
	energy to nourish itself with. It then excretes into the mind of its carrier 
	a telepathic matrix formed by combining the conscious thought frequencies 
	with nerve signals picked up from the speech centres of the brain which has 
	supplied them. The practical upshot of all this is that if you stick a Babel
	fish in your ear you can instantly understand anything said to you in any 
	form of language. The speech patterns you actually hear decode the brainwave 
	matrix which has been fed into your mind by your Babelfish.               

	Douglas Adams															  */


#ifndef BABELFISH_H
#define BABELFISH_H

#include <string>

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// class BabelFish

class BabelFish
{
// Construction and destruction
public:
	///////////////////////////////////////////////////////////////////////////////
	// constructor of BabelFish
	///////////////////////////////////////////////////////////////////////////////
	BabelFish();
	
	///////////////////////////////////////////////////////////////////////////////
	// destructor of BabelFish
	///////////////////////////////////////////////////////////////////////////////	
	virtual ~BabelFish();

// Attributes and operations
public:

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetLanguage
	// description	: Sets the language
	//
	// parameters	: strLanguage		Selected language
	//
	// returns		: None.
	///////////////////////////////////////////////////////////////////////////////
	void SetLanguage(string strLanguage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetLanguage
	// description	: Sets the language
	//
	// parameters	: nLanguage			Selected language
	//
	// returns		: None.
	///////////////////////////////////////////////////////////////////////////////
	void SetLanguage(int nLanguage);

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLanguage
	// description	: Gets the current language string
	//
	// parameters	: None
	//
	// returns		: string			Selected language
	///////////////////////////////////////////////////////////////////////////////
	string GetLanguage() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLanguage
	// description	: Gets the current language ID
	//
	// parameters	: None
	//
	// returns		: string			Selected language ID
	///////////////////////////////////////////////////////////////////////////////
	string GetLanguageID() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLanguage
	// description	: Gets a language description string
	//
	// parameters	: nLanguage			Language to return string for
	//
	// returns		: string			Language description string
	///////////////////////////////////////////////////////////////////////////////
	string GetLanguage(int nLanguage) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLanguageID
	// description	: Gets a language ID
	//
	// parameters	: nLanguage			Language to return ID for
	//
	// returns		: string			Language ID
	///////////////////////////////////////////////////////////////////////////////
	string GetLanguageID(int nLanguage) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetCurrentLanguageID
	// description	: Gets the current selected ID
	//
	// parameters	: 
	//
	// returns		: int			m_nLanguage 	// Selected language
	///////////////////////////////////////////////////////////////////////////////
	int GetCurrentLanguageID() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetLanguages
	// description	: Gets the number of languages
	//
	// parameters	: none
	//
	// returns		: int				The number of languages
	///////////////////////////////////////////////////////////////////////////////
	int GetLanguages() const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetText()
	// description	: This function returns the text assigned to the specified
	//					string ID in the language defined whilst BabelFish was
	//					created.
	//
	// parameters	: nID		string ID
	//
	// returns		: text assigned to string ID
	///////////////////////////////////////////////////////////////////////////////
	string GetText(int nID) const; 

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetText()
	// description	: This function returns the text assigned to the specified
	//					string ID in the language defined whilst BabelFish was
	//					created. Where %1 occurs in the text, this is replaced by
	//					strArgument1.
	//
	// parameters	: nID				string ID
	//				  strArgument1		string replacing %1 in text
	//
	// returns		: text assigned to string ID
	///////////////////////////////////////////////////////////////////////////////
	string GetText(int nID, const string& strArgument1) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: GetText()
	// description	: This function returns the text assigned to the specified
	//					string ID in the language defined whilst BabelFish was
	//					created. Where %1 and %2 occur in the text, these are 
	//					replaced by strArgument1 and strArgument2 respectively.
	//
	// parameters	: nID				string ID
	//				  strArgument1		string replacing %1 in text
	//				  strArgument2		string replacing %2 in text
	//
	// returns		: text assigned to string ID
	///////////////////////////////////////////////////////////////////////////////	
	string GetText(int nID, const string& strArgument1, const string& strArgument2) const;


	///////////////////////////////////////////////////////////////////////////////
	// function		: GetText()
	// description	: This function returns the text assigned to the specified
	//					string ID in the language defined whilst BabelFish was
	//					created. Where %1, %2 and %3 occur in the text, these are 
	//					replaced by strArgument1, strArgument2 and strArgument3
	//					respectively.
	//
	// parameters	: nID				string ID
	//				  strArgument1		string replacing %1 in text
	//				  strArgument2		string replacing %2 in text
	//				  strArgument3		string replacing %3 in text
	//
	// returns		: text assigned to string ID
	///////////////////////////////////////////////////////////////////////////////		
	string GetText(int nID, const string& strArgument1, const string& strArgument2, const string& strArgument3) const;

	///////////////////////////////////////////////////////////////////////////////
	// function		: SetTextPointer
	//
	// description	: This function sets the textpointer
	//
	// parameters	: pszTexts				Pointer to texts
	//
	// returns		: None.
	///////////////////////////////////////////////////////////////////////////////		
	void SetTextPointer(const char** pszTexts, int nTexts);

// Constants
	// Languages
	enum 
		{	
			GB = 0,		// English
			DE,			// German
			FR,			// French
			NL,			// Dutch
			LT,			// Latin

			NLANGS
		};


// Member variables

private:
	int m_nLanguage;								// Selected language
	int m_nTexts;									// Number of texts
	const char** m_pszTexts;						// Texts and translations
	static const char* m_pszLanguages[NLANGS];		// Language strings
	static const char* m_pszLanguageIDs[NLANGS];	// Language strings
};

////////////////////////////////////////////////////////////////////////////////

#endif // !BABELFISH_H
