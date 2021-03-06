/**
 * @file usermsg_json.cc
 * @brief Callback that generates output in JSON format.
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
#include <QTextStream>

#include <stdlib.h>
#include <stdio.h>

static QString escapeForJson (const QString & input)
{
    QString result;
    foreach(const QChar & c, input) {

        if (c == '"') {
            result.append ("\\\"");
        } else if (c == '\\') {
           result.append ("\\\\");
        } else if (c == '/') {
            result.append ("\\/");
        } else if (c == QChar(8)) {
            result.append ("\\b");
        } else if (c == QChar(9)) {
            result.append ("\\t");
        } else if (c == QChar(10)) {
            result.append ("\\n");
        } else if (c == QChar(12)) {
            result.append ("\\f");
        } else if (c == QChar(13)) {
            result.append ("\\r");
        } else {
            result.append (c);
        }
    }

    return result;
}

static QString dateForJson (const QDateTime & input)
{
    return input.toString (Qt::ISODate);
}

void USERMSG_EXPORT showUserMsgJson (const UserMsg & um)
{

    QTextStream d (stderr, QIODevice::WriteOnly);
    int i_max = um.count ();
    if (i_max > 0) {
        d << "{"
          << "\"title\":\"" << um.title () << "\","
          << "[";
        for (int i = 0; i < i_max; ++i) {
            const UserMsgEntry & e = um.at (i);
            if (e.isEnabled()) {
                if (i == 0) d << "{";
                else d << ",{";

                switch (e.type ()) {
                case UserMsgEntry::UTERROR: {
                    d << "\"type\":\"error\",";
                    break; }
                case UserMsgEntry::UTWARNING: {
                    d << "\"type\":\"warning\",";
                    break; }
                case UserMsgEntry::UTINFO: {
                    d << "\"type\":\"info\",";
                    break; }
                case UserMsgEntry::UTDBG_ERROR: {
                    d << "\"type\":\"derror\",";
                    break; }
                case UserMsgEntry::UTDBG_WARNING: {
                    d << "\"type\":\"dwarning\",";
                    break; }
                case UserMsgEntry::UTDBG_INFO: {
                    d << "\"type\":\"debug\",";
                    break; }
                default: {
                    d << "\"type\":null,";
                    break; }
                }
                d << "\"moment\":\"" << dateForJson (e.moment ()) << "\",";
                d << "\"message\":\"" << escapeForJson (e.message ()) << "\"";

                d << "}";
            }
        }
        d << "]"
          << "}";
    }
}
