/******************************************************************************
 * $Workfile: BabelFish.cpp $
 * $Revision: 7 $
 * $Modtime: 12/01/99 3:51p $
 * $Author: Em $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#include <afxwin.h>
#include "BabelFish.h"	

const char* BabelFish::m_pszLanguages[] = 
	{	
		"English",					// English	
		"Deutsch",					// German
		"Français",					// French
		"Nederlands",				// Dutch
		"Latinum"					// Latin
	};

const char* BabelFish::m_pszLanguageIDs[] = 
	{	
		"GB",					// English	
		"DE",					// German
		"FR",					// French
		"NL",				    // Dutch
		"LT"					// Latin
	};


////////////////////////////////////////////////////////////////////////////////
// Construction and destruction

BabelFish::BabelFish()
{
	m_nLanguage = GB;		// Default British
	m_nTexts = 0;			// Zero texts
	m_pszTexts = 0;			// No texts yet

}
	
BabelFish::~BabelFish()
{
	// Nothing to destruct
}

/////////////////////////////////////////////////////////////////////////////////
// Attributes and operations

//						======================
void					BabelFish::SetLanguage
//						======================
(
	string				strLanguage			// Selected language
)
{
	if (strLanguage == GetLanguageID(GB)) 
	{ m_nLanguage = GB;	}
	else if (strLanguage == GetLanguageID(DE))
	{ m_nLanguage = DE;	}
	else if (strLanguage == GetLanguageID(FR))
	{ m_nLanguage = FR;	}
	else if (strLanguage == GetLanguageID(NL))
	{ m_nLanguage = NL;	}
	else if (strLanguage == GetLanguageID(LT))
	{ m_nLanguage = LT;	}
	else 
	{
		// Default
		m_nLanguage = GB;
	}
}

//						======================
void					BabelFish::SetLanguage
//						======================
(
	int					nLanguage			// Selected language
)
{
	// Check if language enum is valid
	if ((nLanguage < 0) || (nLanguage >= NLANGS)) 
	{
		// Default
		m_nLanguage = GB;
	}
	else
	{
		// Valid
		m_nLanguage = nLanguage;
	}
}

//						======================
string					BabelFish::GetLanguage() const
//						======================
{
	string str;			// Language descriptor
	
	if (m_nLanguage < NLANGS)
	{ str = m_pszLanguages[m_nLanguage]; }

	return str;
}

//						======================
string					BabelFish::GetLanguage
//						======================
(
	int					nLanguage
) const
{
	string str;			// Language descriptor
	
	if (nLanguage < NLANGS)
	{ str = m_pszLanguages[nLanguage]; }

	return str;
}

//						========================
string					BabelFish::GetLanguageID() const
//						========================
{
	string str;			// Language descriptor
	
	if (m_nLanguage < NLANGS)
	{ str = m_pszLanguageIDs[m_nLanguage]; }

	return str;
}

//						========================
string					BabelFish::GetLanguageID
//						========================
(
	int					nLanguage
) const
{
	string str;			// Language descriptor
	
	if (nLanguage < NLANGS)
	{ str = m_pszLanguageIDs[nLanguage]; }

	return str;
}


//						===============================
int						BabelFish::GetCurrentLanguageID() const
//						===============================
{
	return m_nLanguage;
}



//						=======================
int						BabelFish::GetLanguages() const
//						=======================
{
	return NLANGS;
}


//						==================
string					BabelFish::GetText
//						==================
(
	int					nID			// String ID
) const
{
	string str;			// (Translated) string
	
	if ((nID < m_nTexts) && (m_pszTexts != 0))
	{ str = m_pszTexts[NLANGS * nID + m_nLanguage]; }

	return str;
}

//						==================
string					BabelFish::GetText
//						==================
(
	int					nID,			// String ID
	const string&		strArgument1	// String argument 1
) const
{
	int	   nPosition;	// Position of placeholder
	string str;			// (Translated) string

	if ((nID < m_nTexts) && (m_pszTexts != 0))
	{ 
		str = m_pszTexts[NLANGS * nID + m_nLanguage];
		nPosition = str.find("%1");
		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{ str.replace(nPosition, 2, strArgument1); }
	}
	return str;
}


//						==================
string					BabelFish::GetText
//						==================
(
	int					nID,			// String ID
	const string&		strArgument1,	// String argument 1
	const string&		strArgument2	// String argument 2
) const
{
	int	   nPosition;	// Position of placeholder
	string str;			// (Translated) string

	if ((nID < m_nTexts) && (m_pszTexts != 0))
	{ 
		str = m_pszTexts[NLANGS * nID + m_nLanguage];
		nPosition = str.find("%1");

		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{ 
			str.replace(nPosition, 2, strArgument1);
		}
		nPosition = str.find("%2");

		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{ 
			str.replace(nPosition, 2, strArgument2);
		}
	}

	return str;
}

//						==================
string					BabelFish::GetText
//						==================
(
	int					nID,			// String ID
	const string&		strArgument1,	// String argument 1
	const string&		strArgument2,	// String argument 2
	const string&		strArgument3	// String argument 3
) const
{
	int	   nPosition;	// Position of placeholder
	string str;			// (Translated) string

	if ((nID < m_nTexts) && (m_pszTexts != 0))
	{ 
		str = m_pszTexts[NLANGS * nID + m_nLanguage];
		nPosition = str.find("%1");

		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{ 
			str.replace(nPosition, 2, strArgument1);
		}
		nPosition = str.find("%2");

		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{
			str.replace(nPosition, 2, strArgument2); 
		}
		nPosition = str.find("%3");

		// If placeholder found, replace with argument
		if (nPosition != str.npos) 
		{ 
			str.replace(nPosition, 2, strArgument3);
		}
	}

	return str;
}


//						=========================
void					BabelFish::SetTextPointer
//						=========================
(
	const char**		pszTexts,		// Pointer to text constants
	int					nTexts			// Number of text constants
)
{ 
	m_pszTexts = pszTexts;
	m_nTexts = nTexts;
}

/////////////////////////////////////////////////////////////////////////////////
