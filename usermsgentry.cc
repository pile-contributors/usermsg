/**
 * @file usermsgentry.cc
 * @brief Definitions for UserMsgEntry class.
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include <usermsg/usermsg.h>
#include "usermsg-private.h"

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
    type_(ERROR)
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
    case ERROR: return QObject::tr("error");
    case WARNING: return QObject::tr("warning");
    case INFO: return QObject::tr("information");
    case DBG_ERROR: return QObject::tr("debug error");
    case DBG_WARNING: return QObject::tr("debug warning");
    case DBG_INFO: return QObject::tr("debug information");
    default: return QObject::tr("unknown");
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
QString UserMsgEntry::typeNameCap (UserMsgEntry::Type value)
{
    switch (value) {
    case ERROR: return QObject::tr("Error");
    case WARNING: return QObject::tr("Warning");
    case INFO: return QObject::tr("Information");
    case DBG_ERROR: return QObject::tr("Debug Error");
    case DBG_WARNING: return QObject::tr("Debug Warning");
    case DBG_INFO: return QObject::tr("Debug Information");
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
