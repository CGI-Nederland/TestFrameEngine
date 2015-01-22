
#ifndef COMMANDLINE_H
#define COMMANDLINE_H

// During debug builds the debug information is truncated to 255 chars
#pragma warning(disable:4786)

#include <string>
#include <vector>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class CommandLine

class CommandLine
{
// Construction and destruction
public:
	explicit CommandLine(const char* pszCommandLine);
	~CommandLine();

// Attributes and operations
public:
	bool GetSwitch(const string& strSwitch) const;
	bool GetString(const string& strKey, string& strValue) const;
	bool GetInteger(const string& strKey, int& nValue) const;
	bool GetInteger(const string& strKey, unsigned short& nValue) const;
	void Dump();

// Implementation
	bool Process();

// Member variables
private:
	string m_strCommandLine;
	vector<string> m_vstrCommandLine;
};

///////////////////////////////////////////////////////////////////////////////

#endif // !COMMANDLINE_H
