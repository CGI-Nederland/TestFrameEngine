/*****************************************************************************
 * $Workfile: lock.h $
 * $Revision: 2 $
 * $Modtime: 12/10/99 11:16a $
 * $Author: Ws $
 ******************************************************************************
 *
 *	COPYRIGHT (C) 1999 CGI NEDERLAND B.V. - ALL RIGHTS RESERVED
 *
 ******************************************************************************/

#ifndef LOCK_H
#define LOCK_H

#include <windows.h>

namespace win32 {

////////////////////////////////////////////////////////////////////////////////
// class lock

template <class lockableT>
class lock {
public:
	// Lock the specified object
	lock(lockableT& object);

	// Unlock the object
	~lock();

private:
	lockableT& m_object;
};

////////////////////////////////////////////////////////////////////////////////

template <class lockableT> inline lock<lockableT>::lock(lockableT& object)
: m_object(object)
{ object.lock(); }

template <class lockableT> inline lock<lockableT>::~lock()
{ m_object.unlock(); }

////////////////////////////////////////////////////////////////////////////////

}

#endif //!LOCK_H
