/**
 * @file usermsgentry.cc
 * @brief Definitions for UserMsgEntry class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include <usermsg/usermsg.h>
#include "usermsg-private.h"

#include <QObject>

/**
 * @class UserMsgEntry
 *
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * The moment is set to current moment. The type is set to ERROR.
 */
UserMsgEntry::UserMsgEntry() :
    message_(),
    moment_(QDateTime::currentDateTime ()),
    type_(UTERROR)
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * All the elements (including moment) are copied.
 */
UserMsgEntry::UserMsgEntry(const UserMsgEntry & other) :
    message_(other.message_),
    moment_(other.moment_),
    type_(other.type_)
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The moment is set to current date/time.
 */
UserMsgEntry::UserMsgEntry (Type ty, const QString & message) :
    message_(message),
    moment_(QDateTime::currentDateTime ()),
    type_(ty)
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Detailed description for destructor.
 */
UserMsgEntry::~UserMsgEntry()
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString UserMsgEntry::typeName(UserMsgEntry::Type value)
{
    switch (value) {
    case UTERROR: return QObject::tr("error");
    case UTWARNING: return QObject::tr("warning");
    case UTINFO: return QObject::tr("information");
    case UTDBG_ERROR: return QObject::tr("debug error");
    case UTDBG_WARNING: return QObject::tr("debug warning");
    case UTDBG_INFO: return QObject::tr("debug information");
    default: return QObject::tr("unknown");
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString UserMsgEntry::typeNameCap (UserMsgEntry::Type value)
{
    switch (value) {
    case UTERROR: return QObject::tr("Error");
    case UTWARNING: return QObject::tr("Warning");
    case UTINFO: return QObject::tr("Information");
    case UTDBG_ERROR: return QObject::tr("Debug Error");
    case UTDBG_WARNING: return QObject::tr("Debug Warning");
    case UTDBG_INFO: return QObject::tr("Debug Information");
    default: return QObject::tr("Unknown");
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool UserMsgEntry::isEnabled (Type value)
{
    /** @todo implement isEnabled */

    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool UserMsgEntry::isEnabled () const
{
    return UserMsgEntry::isEnabled (type_);
}
/* ========================================================================= */
