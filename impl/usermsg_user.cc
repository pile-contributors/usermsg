/**
 * @file usermsg_user.cc
 * @brief Callback that generates output in human readable format.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "../usermsg.h"
#include "../usermsg-private.h"
#include "../usermsgman.h"
#include "usermsg_impl.h"

#include <QDebug>
#include <QFile>
#include <QDateTime>

static QString escapeForUser (const QString & input)
{
    QString result;
    foreach(const QChar & c, input) {

        if (c == '"') {
            result.append ("\\\"");
        } else if (c == '\\') {
           result.append ("\\\\");
        } else if (c == '/') {
            result.append ("\\/");
        } else if (c == 8) {
            result.append ("\\b");
        } else if (c == 9) {
            result.append ("\\t");
        } else if (c == 10) {
            result.append ("\\n");
        } else if (c == 12) {
            result.append ("\\f");
        } else if (c == 13) {
            result.append ("\\r");
        } else {
            result.append (c);
        }
    }

    return result;
}

static QString dateForUser (const QDateTime & input)
{
    return input.toString (Qt::TextDate);
}

void USERMSG_EXPORT showUserMsgUser (const UserMsg & um)
{
    QFile serr;
    serr.open (stdout, QIODevice::WriteOnly);
    QDebug d (&serr);

    int i_max = um.count ();
    if (i_max > 0) {
        d << um.title () << "\n";
        for (int i = 0; i < i_max; ++i) {
            const UserMsgEntry & e = um.at (i);
            if (e.isEnabled()) {

                switch (e.type ()) {
                case UserMsgEntry::UTERROR: {
                    d << "[ERROR]";
                    break; }
                case UserMsgEntry::UTWARNING: {
                    d << "[WARN ]";
                    break; }
                case UserMsgEntry::UTINFO: {
                    d << "[INFO ]";
                    break; }
                case UserMsgEntry::UTDBG_ERROR: {
                    d << "[D ERR]";
                    break; }
                case UserMsgEntry::UTDBG_WARNING: {
                    d << "[D WAR]";
                    break; }
                case UserMsgEntry::UTDBG_INFO: {
                    d << "[DEBUG]";
                    break; }
                default: {
                    d << "[     ]";
                    break; }
                }
                d << dateForUser (e.moment ())
                  << ": "
                  << escapeForUser (e.message ())
                  << "\n";
            }
            d << "\n";
        }
    }
}
