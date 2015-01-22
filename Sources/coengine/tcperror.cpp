/*****************************************************************************
 * $Workfile: tcperror.cpp $
 * $Revision: 2 $
 * $Modtime: 4/20/00 5:34a $
 * $Author: Etb $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/


#include "tcperror.h"
#include <string>
#include <sstream>

////////////////////////////////////////////////////////////////////////////////
// Socket error messages

struct errmsg {
	int		code;
	char*	text;
};

static const errmsg messages[] = {
	{     6, "The handle is invalid." },
	{     8, "Not enough storage is available to process this command." },
	{    87, "The parameter is incorrect." },
	{   995, "The I/O operation has been aborted because of either a thread exit or an application request." },
	{   996, "Overlapped I/O event is not in a signaled state." },
	{   997, "Overlapped I/O operation is in progress." },
	{ 10004, "Interrupted function call." },
	{ 10009, "WSAEBADF" },
	{ 10013, "Permission denied." },
	{ 10014, "Bad address." },
	{ 10022, "Invalid argument." },
	{ 10024, "Too many open files." },
	{ 10035, "Resource temporarily unavailable." },
	{ 10036, "Operation now in progress." },
	{ 10037, "Operation already in progress." },
	{ 10038, "Socket operation on non-socket." },
	{ 10039, "Destination address required." },
	{ 10040, "Message too long." },
	{ 10041, "Protocol wrong type for socket." },
	{ 10042, "Bad protocol option." },
	{ 10043, "Protocol not supported." },
	{ 10044, "Socket type not supported." },
	{ 10045, "Operation not supported." },
	{ 10046, "Protocol family not supported." },
	{ 10047, "Address family not supported by protocol family." },
	{ 10048, "Address already in use." },
	{ 10049, "Cannot assign requested address." },
	{ 10050, "Network is down." },
	{ 10051, "Network is unreachable." },
	{ 10052, "Network dropped connection on reset." },
	{ 10053, "Software caused connection abort." },
	{ 10054, "Connection reset by peer." },
	{ 10055, "No buffer space available." },
	{ 10056, "Socket is already connected." },
	{ 10057, "Socket is not connected." },
	{ 10058, "Cannot send after socket shutdown." },
	{ 10059, "WSAETOOMANYREFS" },
	{ 10060, "Connection timed out." },
	{ 10061, "Connection refused." },
	{ 10062, "WSAELOOP" },
	{ 10063, "WSAENAMETOOLONG" },
	{ 10064, "Host is down." },
	{ 10065, "No route to host." },
	{ 10066, "WSAENOTEMPTY" },
	{ 10067, "Too many processes." },
	{ 10068, "WSAEUSERS" },
	{ 10069, "WSAEDQUOT" },
	{ 10070, "WSAESTALE" },
	{ 10071, "WSAEREMOTE" },
	{ 10091, "Network subsystem is unavailable." },
	{ 10092, "WINSOCK.DLL version out of range." },
	{ 10093, "Successful WSAStartup not yet performed." },
	{ 10101, "Graceful shutdown in progress." },
	{ 10102, "WSAENOMORE" },
	{ 10103, "WSAECANCELLED" },
	{ 10104, "Invalid procedure table from service provider." },
	{ 10105, "Invalid service provider version number." },
	{ 10106, "Unable to initialize a service provider." },
	{ 10107, "System call failure." },
	{ 10108, "WSASERVICE_NOT_FOUND" },
	{ 10109, "Class type not found." },
	{ 10110, "WSA_E_NO_MORE" },
	{ 10111, "WSA_E_CANCELLED" },
	{ 10112, "WSAEREFUSED" },
	{ 11001, "Host not found." },
	{ 11002, "Non-authoritative host not found." },
	{ 11003, "This is a non-recoverable error." },
	{ 11004, "Valid name, no data record of requested type." },
	{ 11005, "WSA_QOS_RECEIVERS" },
	{ 11006, "WSA_QOS_SENDERS" },
	{ 11007, "WSA_QOS_NO_SENDERS" },
	{ 11008, "WSA_QOS_NO_RECEIVERS" },
	{ 11009, "WSA_QOS_REQUEST_CONFIRMED" },
	{ 11010, "WSA_QOS_ADMISSION_FAILURE" },
	{ 11011, "WSA_QOS_POLICY_FAILURE" },
	{ 11012, "WSA_QOS_BAD_STYLE" },
	{ 11013, "WSA_QOS_BAD_OBJECT" },
	{ 11014, "WSA_QOS_TRAFFIC_CTRL_ERROR" },
	{ 11015, "WSA_QOS_GENERIC_ERROR" }
};

////////////////////////////////////////////////////////////////////////////////
// class tcperror

// const char* tcperror::what() const throw()
//
// Purpose:
//		Get a description for this exception
//
// Return value:
//		A pointer to text that describes the error
//
const char* tcperror::what() const throw()
{
	static std::string msg;
	int i;

	if (msg.empty())
	{
		std::ostringstream oss;
		oss << m_code << ": ";

		// Find the message in the list of messages
		for (i = sizeof(messages) / sizeof(errmsg); i >= 0; --i)
		{
			if (messages[i].code == m_code)
			{ break; }
		}

		if (i >= 0)
		{ oss << messages[i].text; }
		else
		{ oss << "Unknown error"; }

		msg = oss.str();
	}

	return msg.c_str();
}

////////////////////////////////////////////////////////////////////////////////
