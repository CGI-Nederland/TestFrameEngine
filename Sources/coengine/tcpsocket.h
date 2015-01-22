/*****************************************************************************
 * $Workfile: tcpsocket.h $
 * $Revision: 3 $
 * $Modtime: 4/20/00 4:01a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#ifdef	UNIX
	
	#include <netdb.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <sys/time.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>

	// Unix
	#define	INVALID_SOCKET	-1
	#define SOCKADDR_IN		sockaddr_in
	#define	SOCKADDR		sockaddr
	#define SD_SEND			2
	#define SOCKET_ERROR	-1
	#define PHOSTENT		hostent*
	
	typedef	int				SOCKET;

#else

	// Windows

	#include <winsock.h>

	// Constants that Microsoft forgot to put in winsock.h
	#ifndef SD_RECEIVE

		#define SD_RECEIVE	0
		#define SD_SEND		1
		#define SD_BOTH		2

	#endif // !SD_RECEIVE

#endif

////////////////////////////////////////////////////////////////////////////////
// class tcpsocket

class tcpsocket {
public:
	// Default constructor
	tcpsocket();

	// Create a socket and open a connection
	tcpsocket(const char* host, unsigned short port);

	// Destructor
	~tcpsocket() throw();

	// Open a connection
	void connect(const char* host, unsigned short port);

	// Close the currently open connection
	void disconnect();

	// Open a connection by accepting it from the given socket
	void accept(const tcpsocket& source);

	// Make this socket listen for clients on the specified port
	void listen(unsigned short port);

	// Receive data
	unsigned long recv(void* buffer, unsigned long size);

	// Send data
	void send(const void* buffer, unsigned long size);

	// Check if this socket has data ready to be received
	bool recv_ready(long timeout = 0);

private:
	// Hide copy constructor and copy assignment operator to prevent copying
	tcpsocket(const tcpsocket&);
	tcpsocket& operator=(const tcpsocket&);

	// Initialise an address structure
	void make_addr(const char* host, unsigned short port, SOCKADDR_IN& addr);

	SOCKET m_socket;

	// Helper class to initialise Windows sockets
	class winsock_init {
	public:
		// Initialise Windows sockets
		winsock_init();

		// Cleanup Windows sockets
		~winsock_init();

	private:
		static int m_init_count;
	};

	static winsock_init m_winsock_init;
};

////////////////////////////////////////////////////////////////////////////////

#endif // !TCPSOCKET_H
