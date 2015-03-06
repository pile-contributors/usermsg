/**
 * @file usermsg.h
 * @brief Declarations for UserMsg class
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_LOGMSG_H_INCLUDE
#define GUARD_LOGMSG_H_INCLUDE

#include <usermsg/usermsg-config.h>
#include <usermsg/usermsgentry.h>

#include <QVector>



//! Log messages.
class USERMSG_EXPORT LogMsg {


public:

    //! Show an error entry.
    static inline void
    err (
            const QString & s_message) {
        msg (UserMsgEntry::UTERROR, s_message);
    }

    //! Show a warning entry.
    static inline void
    war (
            const QString & s_message) {
        msg (UserMsgEntry::UTWARNING, s_message);
    }

    //! Show an informative entry.
    static inline void
    info (
            const QString & s_message) {
        msg (UserMsgEntry::UTINFO, s_message);
    }

    //! Show an error entry.
    static inline void
    dbgErr (
            const QString & s_message) {
        msg (UserMsgEntry::UTDBG_ERROR, s_message);
    }

    //! Show a warning entry.
    static inline void
    dbgWar (
            const QString & s_message) {
        msg (UserMsgEntry::UTDBG_ERROR, s_message);
    }

    //! Show an informative entry.
    static inline void
    dbgInfo (
            const QString & s_message) {
        msg (UserMsgEntry::UTDBG_INFO, s_message);
    }

    //! Show an entry.
    static void
    msg (
            UserMsgEntry::Type ty,
            const QString & s_message);

};

#endif // GUARD_LOGMSG_H_INCLUDE
