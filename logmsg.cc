/**
 * @file usermsg.cc
 * @brief Definitions for UserMsg class.
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "logmsg.h"
#include "usermsg.h"
#include "usermsg-private.h"
#include "usermsgman.h"

#include <QVector>
#include <QObject>

/**
 * @class LogMsg
 *
 *
 */

/* ------------------------------------------------------------------------- */
/**
 * The function simply creates an instance, adds the message
 * and logs it.
 */
void LogMsg::msg (
        UserMsgEntry::Type ty, const QString & s_message)
{
    UserMsg um (QObject::tr("log-only"));
    um.addMsg (ty, s_message);
    UserMsgMan::singleton()->_logMessage (um);
    um.clear ();
}
/* ========================================================================= */
