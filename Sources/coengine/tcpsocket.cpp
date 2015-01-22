/*****************************************************************************
 * $Workfile: tcpsocket.cpp $
 * $Revision: 5 $
 * $Modtime: 4/25/00 1:15p $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#include "tcpsocket.h"
#include "tcperror.h"
#include <memory.h>

#ifdef	UNIX

	#include <unistd.h>

#endif

////////////////////////////////////////////////////////////////////////////////
// class tcpsocket

// tcpsocket::tcpsocket()
//
// Purpose:
//		Default constructor
//
// Exceptions:
//		Throws a tcperror if the socket cannot be created.
//
// Comments:
//		The default constructor creates a new, unconnected socket. Use the
//		member functions connect() or accept() to make a connection.
//
tcpsocket::tcpsocket()
: m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	// Check if the socket was created successfully
	if (m_socket == INVALID_SOCKET)
	{ throw tcperror(); }
}

// tcpsocket::tcpsocket(const char* host, unsigned short port)
//
// Purpose:
//		Create a socket and open a connection
//
// Parameters:
//		host				Host name or TCP/IP address separated by dots
//		port				Port number
//
// Exceptions:
//		Throws a tcperror if the socket cannot be created or the connection
//		cannot be opened.
//
// Comments:
//		This constructor creates a new socket and makes a connection by
//		calling the member function connect().
//
tcpsocket::tcpsocket(const char* host, unsigned short port)
: m_socket(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
	// Check if the socket was created successfully
	if (m_socket == INVALID_SOCKET)
	{ throw tcperror(); }

	// Open the connection
	connect(host, port);
}

// tcpsocket::~tcpsocket() throw()
//
// Purpose:
//		Destructor
//
// Comments:
//		The destructor destroys the socket. Normally the socket should not
//		be connected when it is destroyed. If it is, the connection is
//		teminated immediately.
//
tcpsocket::~tcpsocket() throw()
{
	// Destroy the socket
	if (m_socket != INVALID_SOCKET)
	{
		shutdown(m_socket, SD_SEND);

#ifdef	UNIX

		// Unix
		close(m_socket);
#else

		// Windows
		closesocket(m_socket);
#endif
	}
}

// void tcpsocket::connect(const char* host, unsigned short port)
//
// Purpose:
//		Open a connection
//
// Parameters:
//		host				Host name or TCP/IP address separated by dots
//		port				Port number
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function opens a connection with the specified host. The host may
//		be specified by name, or with an IP address which consists of four
//		numbers separated by dots.
//
void tcpsocket::connect(const char* host, unsigned short port)
{
	// Initialise the address structure
	SOCKADDR_IN addr;
	make_addr(host, port, addr);

	// Open the connection
	if (::connect(m_socket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)))
	{ throw tcperror(); }
}

// void tcpsocket::disconnect()
//
// Purpose:
//		Close the currently open connection
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function gracefully closes the currently open connection.
//
void tcpsocket::disconnect()
{
	
	// Shutdown the socket
	if (shutdown(m_socket, SD_SEND))
	{
		throw tcperror();
	}


#ifdef	UNIX

		// Unix
	if	(close(m_socket))

#else

		// Windows
	if  (closesocket(m_socket))

#endif

	{ throw tcperror(); }

	// Bart Beumer CHANGE: als disconnect succesvol is, dan moet de handle
	// wel op INVALID SOCKET gezet worden. Anders wordt gepoogd de socket
	// ook in de destructor te sluiten.
	//
	m_socket = INVALID_SOCKET;
}

// void tcpsocket::accept(const tcpsocket& source)
//
// Purpose:
//		Open a connection by accepting it from the given socket
//
// Parameters:
//		source				Socket to accept a connection from
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function is meant to be used by server applications to accept
//		connections from clients. The socket 'source' must have been set to
//		listen mode before calling this function.
//
//		Note, the socket on which accept() is called should not be connected
//		when you call accept() on it. If it is, the connection is terminated
//		immediately.
//
//		This function blocks until a connection becomes available to be
//		accepted.
//
void tcpsocket::accept(const tcpsocket& source)
{
	// Destroy the current socket (terminates any open connection)
	 
#ifdef	UNIX

	// Unix
	if ((m_socket != INVALID_SOCKET) && close (m_socket))
#else

	// Windows
	if ((m_socket != INVALID_SOCKET) && closesocket(m_socket))
#endif

	{ throw tcperror(); }

	// Accept a connection from the given socket
	m_socket = ::accept(source.m_socket, 0, 0);
	if (m_socket == INVALID_SOCKET)
	{ throw tcperror(); }
}

// void tcpsocket::listen(unsigned short port)
//
// Purpose:
//		Make this socket listen for clients on the specified port
//
// Parameters:
//		port				Port number
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function puts the socket into listening mode, so that it can be
//		used in a call to accept().
//
void tcpsocket::listen(unsigned short port)
{
	// Initialise the address structure
	SOCKADDR_IN addr;
	make_addr(0, port, addr);

#ifdef	UNIX

	// Unix
	// Socket option enable
	int nSetValue = 1;

	// Reuse socket
	setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, (char*) &nSetValue, sizeof(int));
#endif

	// Bind the address
	if (bind(m_socket, reinterpret_cast<SOCKADDR*>(&addr), sizeof(addr)))
	{ throw tcperror(); }

	// Make the socket listen
	if (::listen(m_socket, SOMAXCONN))
	{ throw tcperror(); }
}

// unsigned long tcpsocket::recv(void* buffer, unsigned long size)
//
// Purpose:
//		Receive data
//
// Parameters:
//		buffer				Buffer to store data into
//		size				Size of the buffer
//
// Return value:
//		The number of bytes actually received.
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function receives data from the currently open connection.
//		Note that the actual number of bytes received may be less than the
//		size of the buffer. If this function is called while no data is ready
//		to be received, this function blocks until data is available.
//
unsigned long tcpsocket::recv(void* buffer, unsigned long size)
{
	// Receive data (possibly blocks)
	int count = ::recv(m_socket, static_cast<char*>(buffer), size, 0);
	if (count == SOCKET_ERROR)
	{ throw tcperror(); }

	// Return the number of bytes received
	return count;
}

// void tcpsocket::send(const void* buffer, unsigned long size)
//
// Purpose:
//		Send data
//
// Parameters:
//		buffer				Buffer to store data into
//		size				Size of the buffer
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function sends data through the currently open connection.
//
void tcpsocket::send(const void* buffer, unsigned long size)
{
	// Send data
	if (::send(m_socket, static_cast<const char*>(buffer), size, 0) == SOCKET_ERROR)
	{ throw tcperror(); }
}

// bool tcpsocket::recv_ready(long timeout)
//
// Purpose:
//		Check if this socket has data ready to be received
//
// Parameters:
//		timeout				Timeout value in milliseconds
//
// Return value:
//		true if data becomes available within the timeout period,
//		false if no data becomes available
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function checks if data is available to be received. If data
//		is available, the next call to recv() is guaranteerd not to block.
//
//		When called on a socket that has been put into listening mode, this
//		function will mark the socket as readable if a connection is waiting
//		to be accepted, which means that accept() is guaranteed not to block.
//
//		If the connection is closed gracefully while this function is waiting,
//		the socket will be marked readable, this function returns and the
//		next call to recv() will immediately return with 0 bytes received.
//
//		The default value for 'timeout' is 0, which means the function does
//		not wait. If -1 is specified, the function blocks until data is
//		available for receiving.
//
bool tcpsocket::recv_ready(long timeout)
{
	// Initialise the timeout structure if necessary
	timeval tv;
	if (timeout != -1)
	{
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = (timeout % 1000) * 1000;
	}

	// TODO: In Windows sockets, the first parameter of select() is not used.
	// What should the value be when using another socket library?
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_socket, &fds);

	// Check if data is available to be received

#ifdef	UNIX

	// Unix
	int result = select((m_socket+1), &fds, 0, 0, (timeout != -1 ? &tv : 0));

#else

	// Windows
	int result = select(0, &fds, 0, 0, (timeout != -1 ? &tv : 0));

#endif
	if (result == SOCKET_ERROR)
	{ throw tcperror(); }

	// Return true if data is available, false otherwise
	return (result != 0);
}

// void tcpsocket::make_addr(const char* host, unsigned short port,
//     SOCKADDR_IN& addr)
//
// Purpose:
//		Initialise an address structure
//
// Parameters:
//		host				Host name or TCP/IP address separated by dots
//		port				Port number
//		addr				Address structure to initialise
//
// Exceptions:
//		Throws a tcperror if any socket error occurs.
//
// Comments:
//		This function uses the given host name and port number to initialse
//		the address structure. The host name may be a null pointer or a pointer
//		to an empty string, in which case the address is set to a "don't care"
//		value.
//
void tcpsocket::make_addr(const char* host, unsigned short port,
	SOCKADDR_IN& addr)
{
	// Initialise the address structure
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

	if (host && host[0])
	{
		// Try to convert the dotted format string to an address
		addr.sin_addr.s_addr = inet_addr(host);

#ifdef	UNIX

		// Unix
		if (addr.sin_addr.s_addr != -1)
#else

		// Windows
		if (addr.sin_addr.s_addr == htonl(INADDR_NONE))
#endif
		{
			// Try to convert the host name to an address
			PHOSTENT phe = gethostbyname(host);
			if (!phe)
			{ throw tcperror(); }

			// Copy it into the address structure
			memcpy(&addr.sin_addr, phe->h_addr, phe->h_length);
		}
	}
	else
	{
		// No address specified, use a "don't care" value
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
}

////////////////////////////////////////////////////////////////////////////////
// class winsock_init

tcpsocket::winsock_init tcpsocket::m_winsock_init;
int tcpsocket::winsock_init::m_init_count = 0;

// tcpsocket::winsock_init::winsock_init()
//
// Purpose:
//		Initialise Windows sockets
//
tcpsocket::winsock_init::winsock_init()
{
	if (!m_init_count++)
	{
#ifdef	UNIX
#else
		// Windows

		WSADATA wsadata;
		WSAStartup(MAKEWORD(2, 0), &wsadata);
#endif
	}
}

// tcpsocket::winsock_init::~winsock_init()
//
// Purpose:
//		Cleanup Windows sockets
//
tcpsocket::winsock_init::~winsock_init()
{
	if (!--m_init_count)
	{ 
#ifdef	UNIX
#else
		// Windows
		WSACleanup(); 
#endif
	}
}

////////////////////////////////////////////////////////////////////////////////
