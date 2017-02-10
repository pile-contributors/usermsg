/**
 * @file usermsgstg.cc
 * @brief Definitions for UserMsgStg class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
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

static QString guard_string ("./guard/.");
static QString ver2_string ("./ver2/.");

enum TypeFlag {
    TF_NONE = 0x0000,

    TF_ERROR = 0x0001,
    TF_WARNING = 0x0002,
    TF_INFO = 0x0004,
    TF_DEBUGM_ERROR = 0x0008,
    TF_DEBUGM_WARNING = 0x0010,
    TF_DEBUGM_INFO = 0x0020,

    TF_ALL_NON_DEBUG =
        TF_ERROR | TF_WARNING | TF_INFO,
    TF_ALL_DEBUG =
        TF_DEBUGM_ERROR | TF_DEBUGM_WARNING | TF_DEBUGM_INFO,
    TF_ALL =
        TF_ERROR | TF_WARNING | TF_INFO |
        TF_DEBUGM_ERROR | TF_DEBUGM_WARNING | TF_DEBUGM_INFO,
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
    case UserMsgEntry::UTDBG_ERROR: return TF_DEBUGM_ERROR;
    case UserMsgEntry::UTDBG_WARNING: return TF_DEBUGM_WARNING;
    case UserMsgEntry::UTDBG_INFO: return TF_DEBUGM_INFO;
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
    enabled_flags_(TF_ALL_NON_DEBUG),
    s_log_file_(),
    log_count_ (10), // keep ten old logs
    roll_trigger_ (1024*1024*2) // two megabytes log size by default
{
    USERMSG_TRACE_ENTRY;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Values are copied from the \p other instance.
 */
UserMsgStg::UserMsgStg (const UserMsgStg & other) :
    enabled_flags_(other.enabled_flags_),
    s_log_file_(other.s_log_file_),
    log_count_(other.log_count_),
    roll_trigger_(other.roll_trigger_)
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
    out << guard_string;

    out << enabled_flags_;
    out << s_log_file_;
    out << guard_string;
    out << ver2_string;
    out << log_count_;
    out << roll_trigger_;
    out << guard_string;

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
    buffer.open (QIODevice::ReadOnly);

    QDataStream in (&buffer);

    in >> guard;
    if (guard != guard_string) {
        USERMSG_DEBUGM ("Start guard not found in stream.\n");
        return false;
    }

    in >> enabled_flags_;
    in >> s_log_file_;
    in >> guard;
    if (guard == ver2_string) {
        // added on 2017-02-10; strings generated prior to this date
        // will not have following fields:
        in >> log_count_;
        in >> roll_trigger_;
        in >> guard;
    }
    sanityCheck ();

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
    stg->setValue ("s_log_file_", s_log_file_);
    stg->setValue ("log_count_", log_count_);
    stg->setValue ("roll_trigger_", roll_trigger_);

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
        s_log_file_ = stg->value ("s_log_file_").toString ();
        log_count_ = stg->value ("log_count_", 10).toInt ();
        roll_trigger_ = stg->value ("roll_trigger_", 1024*1024*10).toInt ();

        b_ret = true;
        break;
    }
    sanityCheck ();

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

/* ------------------------------------------------------------------------- */
void UserMsgStg::setAllEnabled(bool include_debug)
{
    if (include_debug) enabled_flags_ = TF_ALL;
    else enabled_flags_ = TF_ALL_NON_DEBUG;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgStg::sanityCheck ()
{
    // log_count_ sanity check
    if (log_count_ < 0) {
        log_count_ = 1;
    } else if (log_count_ > 1000) {
        log_count_ = 10;
    }
    // roll_trigger_  sanity check
    if (roll_trigger_ < 0) {
        roll_trigger_ = 1024*1024*1;
    } else if (roll_trigger_ > 1024*1024*1024*1) {
        roll_trigger_ = 1024*1024*10;
    }
}
/* ========================================================================= */
