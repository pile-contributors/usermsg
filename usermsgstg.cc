/**
 * @file usermsgstg.cc
 * @brief Definitions for UserMsgStg class.
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "usermsgstg.h"
#include "usermsg-private.h"
#include "usermsg.h"
#include "usermsgman.h"

#include <QBuffer>
#include <QSettings>
#include <QByteArray>
#include <QDataStream>
#include <QVariant>

/**
 * @class UserMsgStg
 *
 * The class stores the settings for the UserMsg system.
 * An instance of this class is stored inside UserMsgMan.
 *
 */

static const char * guard_string = "./guard/.";

enum TypeFlag {
    TF_NONE = 0x0000,

    TF_ERROR = 0x0001,
    TF_WARNING = 0x0002,
    TF_INFO = 0x0004,
    TF_DBG_ERROR = 0x0008,
    TF_DBG_WARNING = 0x0010,
    TF_DBG_INFO = 0x0020,

    TF_ALL_NON_DEBUG =
        TF_ERROR | TF_WARNING | TF_INFO,
    TF_ALL_DEBUG =
        TF_DBG_ERROR | TF_DBG_WARNING | TF_DBG_INFO,
    TF_ALL =
        TF_ERROR | TF_WARNING | TF_INFO |
        TF_DBG_ERROR | TF_DBG_WARNING | TF_DBG_INFO,
};


/* ------------------------------------------------------------------------- */
/**
 * Converts a type into coresponding flag.
 */
static TypeFlag typeToFlag (UserMsgEntry::Type ty)
{
    USERMSG_TRACE_ENTRY;

    switch (ty) {
    case UserMsgEntry::UTERROR: return TF_ERROR;
    case UserMsgEntry::UTWARNING: return TF_WARNING;
    case UserMsgEntry::UTINFO: return TF_INFO;
    case UserMsgEntry::UTDBG_ERROR: return TF_DBG_ERROR;
    case UserMsgEntry::UTDBG_WARNING: return TF_DBG_WARNING;
    case UserMsgEntry::UTDBG_INFO: return TF_DBG_INFO;
    default: return TF_NONE;
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
/**
 * Default values are loaded in this instance.
 */
UserMsgStg::UserMsgStg() :
    enabled_flags_(TF_ALL_NON_DEBUG)
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Values are copied from the \p other instance.
 */
UserMsgStg::UserMsgStg (const UserMsgStg & other)
{
    USERMSG_TRACE_ENTRY;


    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 *
 */
UserMsgStg::~UserMsgStg()
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * A marker is placed both at the beginning and at the end of the stream.
 */
QByteArray UserMsgStg::toByteArray () const
{
    USERMSG_TRACE_ENTRY;
    QBuffer buffer;
    buffer.open (QBuffer::WriteOnly);
    QDataStream out(&buffer);
    out << QString(guard_string);

    out << enabled_flags_;

    out << QString(guard_string);

    USERMSG_TRACE_EXIT;
    return buffer.buffer ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The stream must begin and end with the marker.
 */
bool UserMsgStg::fromByteArray (QByteArray * value)
{
    USERMSG_TRACE_ENTRY;
    QString guard;
    QBuffer buffer (value);
    buffer.open(QIODevice::ReadOnly);

    QDataStream in (&buffer);

    in >> guard;
    if (guard != guard_string) {
        USERMSG_DEBUGM ("Start guard not found in stream.\n");
        return false;
    }

    in >> enabled_flags_;

    in >> guard;
    if (guard != guard_string) {
        USERMSG_DEBUGM ("End guard not found in stream.\n");
        return false;
    }

    USERMSG_TRACE_EXIT;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The settings are saved in a group called `UserMsg`.
 */
bool UserMsgStg::toQSettings ( QSettings * stg) const
{
    USERMSG_TRACE_ENTRY;
    stg->beginGroup ("UserMsg");

    stg->setValue ("enabled_flags_", enabled_flags_);

    stg->endGroup ();
    USERMSG_TRACE_EXIT;
    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * The settings are loaded from a group called `UserMsg`.
 */
bool UserMsgStg::fromQSettings ( QSettings * stg)
{
    USERMSG_TRACE_ENTRY;
    stg->beginGroup ("UserMsg");

    bool b_ret = false;
    for (;;) {

        enabled_flags_ = stg->value ("enabled_flags_", TF_ALL_NON_DEBUG).toInt ();

        b_ret = true;
        break;
    }

    stg->endGroup ();
    USERMSG_TRACE_EXIT;

    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool UserMsgStg::isEnabled (UserMsgEntry::Type value)
{
    TypeFlag tf = typeToFlag (value);
    return (enabled_flags_ & tf) != 0;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgStg::setEnabled (UserMsgEntry::Type ty, bool b_enabled)
{
    TypeFlag tf = typeToFlag (ty);
    if (b_enabled) {
        enabled_flags_ = enabled_flags_ | tf;
    } else {
        enabled_flags_ = enabled_flags_ & (~tf);
    }
}
/* ========================================================================= */

