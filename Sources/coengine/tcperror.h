/*****************************************************************************
 * $Workfile: tcperror.h $
 * $Revision: 3 $
 * $Modtime: 4/21/00 2:07a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#ifndef TCPERROR_H
#define TCPERROR_H

#ifdef	UNIX

	// Unix
	#include <errno.h>
#else

	// Windows
	#include <winsock.h>

#endif

#include <exception>

////////////////////////////////////////////////////////////////////////////////
// class tcperror

class tcperror : public std::exception {
public:
	// Create a tcperror object with the last error code
	tcperror() throw()

#ifdef	UNIX

	// Unix
	: m_code(errno) {}
#else

	// Windows
	: m_code(WSAGetLastError()) {}
#endif

	// Create a tcperror object with the specified error code
	explicit tcperror(int code) throw()
	: m_code(code) {}

	// Get a description for this exception
	virtual const char* what() const throw();

	// Get the error code
	int code() const
	{ return m_code; }

private:
	int m_code;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !TCPERROR_H
