/*****************************************************************************
 * $Workfile: tcpstream.h $
 * $Revision: 1 $
 * $Modtime: 1-12-99 14:10 $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef TCPSTREAM_H
#define TCPSTREAM_H


#include <iostream>
#include "tcpsocket.h"

////////////////////////////////////////////////////////////////////////////////
// class basic_tcpbuf

template <class charT, class traits = std::char_traits<charT> >
class basic_tcpbuf : public std::basic_streambuf<charT,traits> {
public:
	// Default constructor
	basic_tcpbuf()
	: m_connected(false), m_recv_timeout(-1) {}

	// Destructor
	virtual ~basic_tcpbuf()
	{
		// If connected, flush the output buffer; do not throw exceptions from
		// the destructor. The connection is closed by the socket's destructor.
		if (is_connected())
		{
			try
			{ overflow(); }
			catch (tcperror&) {}
		}
	}

	// Check if a connection is open
	bool is_connected() const
	{ return m_connected; }

	// Open a connection
	basic_tcpbuf<charT,traits>* connect(const char* host, unsigned short port)
	{
		// If already connected, return failure
		if (is_connected())
		{ return 0; }

		// Initialise get and put areas
		setg(m_get_area, m_get_area + sizeof(m_get_area), m_get_area + sizeof(m_get_area));
		setp(m_put_area, m_put_area + sizeof(m_put_area));

		// Open a connection
		m_socket.connect(host, port);
		m_connected = true;

		// Return success
		return this;
	}

	// Wait for a client to connect and open the connection
	basic_tcpbuf<charT,traits>* accept(tcpsocket& source)
	{
		// If already connected, return failure
		if (is_connected())
		{ return 0; }

		// Initialise get and put areas
		setg(m_get_area, m_get_area + sizeof(m_get_area), m_get_area + sizeof(m_get_area));
		setp(m_put_area, m_put_area + sizeof(m_put_area));

		// Wait until there is a connection ready to be accepted on the
		// source socket; return failure if a timeout occurs
		if (!source.recv_ready(m_recv_timeout))
		{ return 0; }

		// Accept the next pending connection from the source socket
		m_socket.accept(source);
		m_connected = true;

		// Return success
		return this;
	}

	// Close the currently open connection
	basic_tcpbuf<charT,traits>* disconnect()
	{
		// If already disconnected, return failure
		if (!is_connected())
		{ return 0; }

		// Flush the put area, return 0 on failure
		if (overflow() == traits::eof())
		{ return 0; }

		// Close the connection
		m_socket.disconnect();
		m_connected = false;

		// Return success
		return this;
	}

	// Return a reference to the socket
	tcpsocket& socket()
	{ return m_socket; }

	// Get the current timeout (in milliseconds) for receive and accept
	long recv_timeout() const
	{ return m_recv_timeout; }

	// Set the current timeout (in milliseconds) for receive and accept
	void recv_timeout(long timeout)
	{ m_recv_timeout = timeout; }

protected:
	// Receive characters from the input sequence
	virtual int_type underflow()
	{
		// If not connected, return failure
		if (!is_connected())
		{ return traits::eof(); }

		// If there is no get area at all, return failure
		if (!gptr())
		{ return traits::eof(); }

		// If there are no characters in the get area, fill the get area
		if (gptr() >= egptr())
		{
			// Make sure the put area is flushed before receiving (our peer might need
			// to read and interpret the data and send a response for us to read)
			if (sync() == -1)
			{ return traits::eof(); }

			// Wait until data is available for reading, return failure if a
			// timeout occurs
			if (!m_socket.recv_ready(m_recv_timeout))
			{ return traits::eof(); }

			// Receive data to fill the get area
			unsigned long count = m_socket.recv(m_get_area, sizeof(m_get_area));
			if (!count)
			{
				// If recv() returns zero, the connection was closed by out peer
				m_connected = false;
				return traits::eof();
			}

			// Reset the get area pointers
			setg(m_get_area, m_get_area, m_get_area + count);
		}

		// Return the current character
		return traits::to_int_type(*gptr());
	}

	// Send characters to the output sequence
	virtual int_type overflow(int_type c = traits::eof())
	{
		// If not connected, return failure
		if (!is_connected())
		{ return traits::eof(); }

		// Flush the put area
		if (sync() == -1)
		{ return traits::eof(); }

		// Consume the character if it is not the end-of-file indicator
		if (!traits::eq_int_type(c, traits::eof()))
		{
			char_type ch = traits::to_char_type(c);

			// If there is room in the put area, store the character, otherwise
			// send it immediately
			if (pptr() && (pptr() < epptr()))
			{
				// Store the character in the put area
				*pptr() = ch;
				pbump(1);
			}
			else
			{
				// No buffer space available, send the character immediately
				m_socket.send(&ch, sizeof(ch));
			}
		}

		// Return success
		return traits::not_eof(c);
	}

	// Flush characters in the output sequence
	virtual int sync()
	{
		// If not connected, return failure
		if (!is_connected())
		{ return -1; }

		// If there are characters in the put area, flush them
		if (pbase() && (pbase() < pptr()))
		{
			// Send the characters in the put area
			m_socket.send(pbase(), pptr() - pbase());

			// Reset the put area pointers
			setp(pbase(), epptr());
		}

		// Return success
		return 0;
	}

private:
	// Hide copy constructor and copy assignment operator to prevent copying
	basic_tcpbuf(const basic_tcpbuf&);
	basic_tcpbuf& operator=(const basic_tcpbuf&);

	tcpsocket	m_socket;
	bool		m_connected;

	char_type	m_get_area[80];
	char_type	m_put_area[80];

	long		m_recv_timeout;
};

////////////////////////////////////////////////////////////////////////////////
// class basic_tcpstream

template <class charT, class traits = std::char_traits<charT> >
class basic_tcpstream : public std::basic_iostream<charT,traits> {
public:
	basic_tcpstream()
	: std::basic_iostream<charT,traits>(&sb) {}

	explicit basic_tcpstream(const char* host, unsigned short port)
	: std::basic_iostream<charT,traits>(&sb)
	{ connect(host, port); }

	basic_tcpbuf<charT,traits>* rdbuf()
	{ return &sb; }

	bool is_connected()
	{ return rdbuf()->is_connected(); }

	void connect(const char* host, unsigned short port)
	{ if (!rdbuf()->connect(host, port)) setstate(failbit); }

	void accept(tcpsocket& source)
	{ if (!rdbuf()->accept(source)) setstate(failbit); }

	void disconnect()
	{ if (!rdbuf()->disconnect()) setstate(failbit); }

	tcpsocket& socket()
	{ return rdbuf()->socket(); }

	long recv_timeout() const
	{ return rdbuf()->recv_timeout(); }

	void recv_timeout(long timeout)
	{ rdbuf()->recv_timeout(timeout); }

private:
	// Hide copy constructor and copy assignment operator to prevent copying
	basic_tcpstream(const basic_tcpstream&);
	basic_tcpstream& operator=(const basic_tcpstream&);

	basic_tcpbuf<charT,traits> sb;
};

////////////////////////////////////////////////////////////////////////////////

typedef basic_tcpbuf<char>			tcpbuf;
typedef basic_tcpbuf<wchar_t>		wtcpbuf;

typedef basic_tcpstream<char>		tcpstream;
typedef basic_tcpstream<wchar_t>	wtcpstream;

////////////////////////////////////////////////////////////////////////////////

#endif // !TCPSTREAM_H
