/**
 * @file usermsg_xml.cc
 * @brief Callback that generates output in XML format.
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

static QString escapeForXml (const QString & input)
{
    QString result;
    foreach(const QChar & c, input) {

        if (c == '<') {
            result.append ("&lt;");
        } else if (c == '>') {
            result.append ("&gt;");
        } else if (c == '&') {
            result.append ("&amp;");
        } else if (c == '\'') {
            result.append ("&apos;");
        } else if (c == '"') {
            result.append ("&quot;");
        } else if (c == 13) {
            result.append ("&#x0d;");
        } else if (c == 10) {
            result.append ("&#x0a;");
        } else if (c == 9) {
            result.append ("&#x09;");
        } else {
            result.append (c);
        }
    }

    return result;
}

static QString dateForXml (const QDateTime & input)
{
    return input.toString (Qt::ISODate);
}

void USERMSG_EXPORT showUserMsgXml (const UserMsg & um)
{
    // << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
    QFile serr;
    serr.open (stdout, QIODevice::WriteOnly);
    QDebug d (&serr);

    int i_max = um.count ();
    if (i_max > 0) {
        d << "<usermsg title=\"" << escapeForXml(um.title ()) << "\">";
        for (int i = 0; i < i_max; ++i) {
            const UserMsgEntry & e = um.at (i);
            if (e.isEnabled()) {
                d << "<usermsgentry moment=\"" << dateForXml (e.moment ()) << "\" "
                  << "type=\"";

                switch (e.type ()) {
                case UserMsgEntry::UTERROR: {
                    d << "error";
                    break; }
                case UserMsgEntry::UTWARNING: {
                    d << "warning";
                    break; }
                case UserMsgEntry::UTINFO: {
                    d << "info";
                    break; }
                case UserMsgEntry::UTDBG_ERROR: {
                    d << "derror";
                    break; }
                case UserMsgEntry::UTDBG_WARNING: {
                    d << "dwarning";
                    break; }
                case UserMsgEntry::UTDBG_INFO: {
                    d << "debug";
                    break; }
                default: {
                    d << "null";
                    break; }
                }
                d << "\">" << escapeForXml(e.message ())
                  << "</usermsgentry>";
            }
        }
        d << "</usermsg>";
    }
}
