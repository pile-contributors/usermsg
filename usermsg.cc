/**
 * @file usermsg.cc
 * @brief Definitions for UserMsg class.
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "usermsg.h"
#include "usermsg-private.h"
#include "usermsgman.h"

#include <QVector>

/**
 * @class UserMsg
 *
 * The class associates a title, a user-defined value and a list of
 * entries, each with its own timestamp, type and string message.
 */

/* ------------------------------------------------------------------------- */
/**
 * Creates an instance without a title
 * and with a NULL value for user payload.
 */
UserMsg::UserMsg() :
    title_(),
    user_payload_(NULL),
    message_list_()
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * This is a bit dangerous as the user pointer is copied
 * without any notice or reference counting. Pointer lifetime
 * must be well understood.
 */
UserMsg::UserMsg (const UserMsg & other) :
    title_(other.title_),
    user_payload_(other.user_payload_),
    message_list_()
{
    USERMSG_TRACE_ENTRY;

    foreach(const UserMsgEntry & e, other.message_list_) {
        message_list_.append (UserMsgEntry (e));
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 *
 */
UserMsg::UserMsg (const QString & title, void * user_data) :
    title_(title),
    user_payload_(user_data),
    message_list_()
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * .
 */
UserMsg::~UserMsg()
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Requests the manager to show this instance. identical to
 * UserMsgMan::show().
 */
void UserMsg::show()
{
    if (count() == 0) return;

    UserMsgMan::show (*this);

    clear ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The list is not sorted based on the timestamps.
 */
void UserMsg::append(const UserMsg & other)
{
    foreach(const UserMsgEntry & e, other.message_list_) {
        message_list_.append (e);
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Creates a UserMsgEntry instance and appends it to the list.
 */
void UserMsg::addMsg (
        UserMsgEntry::Type ty, const QString & s_message)
{
    UserMsgEntry new_value (ty, s_message);
    message_list_.append (new_value);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The function simply creates an instance, adds the message
 * and shows it.
 */
void UserMsg::msg (
        UserMsgEntry::Type ty, const QString & s_message)
{
    UserMsg um;
    um.addMsg (ty, s_message);
    um.show ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Uses the underlying platform to show the message.
 */
void UserMsg::fatalException (const QString & s_message)
{
    /** @todo stub */
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * @returns either QMessageBox::Yes or QMessageBox::No.
 */
int UserMsg::consoleAskYN (const QString & s_message)
{
    /** @todo stub */
    return Yes;
}
/* ========================================================================= */


