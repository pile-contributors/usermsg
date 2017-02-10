/**
 * @file usermsgman.cc
 * @brief Definitions for Example class.
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#include "usermsgman.h"
#include "usermsg-private.h"
#include "usermsg.h"
#include "usermsgstg.h"

#include <QThread>
#include <QTextStream>
#include <QDir>
#include <QRegularExpression>
#include <QStandardPaths>

/**
 * @class UserMsgMan
 *
 * A singleton is created internally and it
 * manages the settings and behavior of UserMsg.
 *
 * The manager can be explicitly initialized
 * but it does not have to. Any static
 * function that will be invoked will first check
 * for its existance and it will create it
 * if it does not exist.
 *
 * Resources can be freed using
 * UserMsgMan::end(), for example at the end of
 * the application.
 *
 * Initial state for the manager is enabled; to
 * start in disabled state use
 * @code
 * UserMsgMan::init (false);
 * @endcode
 * at the beginning of your application.
 *
 *
 */

UserMsgMan * UserMsgMan::singleton_ = NULL;

enum LockState {
    StateLocked,
    StateUnlocked
};

//! Aquire the lock; wait for it if necesary.
#define UM_AQUIRE_LOCK \
    while (!singleton_->lock_.testAndSetAcquire (StateUnlocked, StateLocked)) { \
    QThread::usleep (50); \
    }

//! Release the lock.
#define UM_RELEASE_LOCK \
    while (!singleton_->lock_.testAndSetRelease (StateLocked, StateUnlocked)) { \
    QThread::usleep (50); \
    }

/* ------------------------------------------------------------------------- */
UserMsgMan * UserMsgMan::singleton ()
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    USERMSG_TRACE_EXIT;
    return singleton_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Sets the singleton to point to this instance.
 */
UserMsgMan::UserMsgMan() :
    QObject(),
    enabled_ (true),
    settings_ (new UserMsgStg()),
    message_list_ (),
    lock_ (StateUnlocked),
    kb_show_ (NULL),
    log_file_ (NULL),
    logger_ (NULL)
{
    USERMSG_TRACE_ENTRY;
    singleton_ = this;

    qRegisterMetaType<UserMsg>("UserMsg");
    qRegisterMetaType<UserMsgEntry>("UserMsgEntry");

    _openLogFile ();

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Resets the singleton to NULL.
 */
UserMsgMan::~UserMsgMan()
{
    USERMSG_TRACE_ENTRY;
    if (logger_ != NULL) {
        logger_->flush ();
        delete logger_;
    }
    if (log_file_ != NULL) {
        delete log_file_;
    }

    singleton_ = NULL;
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * A new instance is only created if the singleton is NULL.
 *
 * @returns true if everything went OK.
 */
bool UserMsgMan::init (bool start_disabled)
{
    USERMSG_TRACE_ENTRY;

    // create the thingy
    if (singleton_ == NULL) {
        new UserMsgMan ();
    }

    // disable it
    if (start_disabled) {
        disable ();
    }

    USERMSG_TRACE_EXIT;

    return true;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * If the singleton exists is being destroyed.
 */
void UserMsgMan::end ()
{
    USERMSG_TRACE_ENTRY;

    if (singleton_ != NULL) {
        delete singleton_;
        singleton_ = NULL;
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * This is the only static function that will not create the singleton
 *
 * @returns true if the singleton is non-NULL.
 */
bool UserMsgMan::isInitialized ()
{
    USERMSG_TRACE_ENTRY;

    bool b_ret = (singleton_ != NULL);

    USERMSG_TRACE_EXIT;
    return b_ret;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * @returns a constant reference to internal settings.
 */
const UserMsgStg & UserMsgMan::settings ()
{
    autostart ();
    return *singleton_->settings_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 *
 */
void UserMsgMan::setSettings (const UserMsgStg & value)
{
    autostart ();
    *singleton_->settings_ = value;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 *
 */
void UserMsgMan::disable ()
{
    USERMSG_TRACE_ENTRY;

    autostart ();
    UM_AQUIRE_LOCK;
    singleton_->enabled_ = false;
    UM_RELEASE_LOCK;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 *
 */
void UserMsgMan::enable (bool collapse_messages)
{
    USERMSG_TRACE_ENTRY;
    autostart ();

    singleton_->_showQueue (collapse_messages);

    UM_AQUIRE_LOCK;
    singleton_->enabled_ = true;
    UM_RELEASE_LOCK;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool UserMsgMan::isEnabled()
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    USERMSG_TRACE_EXIT;
    return (singleton_->enabled_);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
bool UserMsgMan::isVisible (UserMsgEntry::Type value)
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    USERMSG_TRACE_EXIT;
    return (singleton_->settings_->isEnabled (value));
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::setVisible (
        UserMsgEntry::Type ty, bool b_visible)
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    (singleton_->settings_->setEnabled (ty, b_visible));
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::setAllVisible (bool include_debug)
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    (singleton_->settings_->setAllEnabled (include_debug));
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
UserMsgMan::KbShowMessage UserMsgMan::callbackShow ()
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    USERMSG_TRACE_EXIT;
    return singleton_->kb_show_;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::setCallbackShow ( UserMsgMan::KbShowMessage value)
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    singleton_->kb_show_ = value;
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
const QString & UserMsgMan::logFile()
{
    USERMSG_TRACE_ENTRY;
    autostart ();
    USERMSG_TRACE_EXIT;
    return singleton_->settings_->logFile ();
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::setLogFile (const QString & value)
{
    USERMSG_TRACE_ENTRY;
    autostart ();

    UM_AQUIRE_LOCK;
    singleton_->settings_->setLogFile (value);
    singleton_->_openLogFile ();
    UM_RELEASE_LOCK;

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::autosetLogFile (const QString & base_name)
{
    QString s_log_path;
    QString s_base_name = base_name;
    s_base_name.replace (QRegularExpression ("\\s+"), "_");

#   if defined(__WIN32__) || defined (_WIN32)

    s_log_path = QStandardPaths::standardLocations (
                QStandardPaths::DataLocation).at (0);
    QDir d_lg (s_log_path);
    if (!d_lg.exists ()) d_lg.mkpath (".");

#   else

    s_log_path = "/var/log";

#   endif

    QString s_log_file = QString("%1/%2.log")
            .arg (s_log_path)
            .arg (s_base_name);

    UserMsgMan::setLogFile (s_log_file);
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
void UserMsgMan::autostart()
{
    if (singleton_ == NULL) {
        init ();
    }
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Presents a message to the user.
 */
void UserMsgMan::show (const UserMsg & um)
{
    USERMSG_TRACE_ENTRY;
    autostart ();

    if (singleton_->enabled_) {
        singleton_->_showMessage (um);
    } else {
        singleton_->_addMessageToQueue (um);
    }

    singleton_->_logMessage (um);

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * If log is available logs the message, otherwise does nothing.
 */
void UserMsgMan::_logPrefix (const UserMsgEntry & e)
{
    USERMSG_TRACE_ENTRY;
    (*logger_) << "  "
               << e.moment ().toString (Qt::ISODate)
               << " ";
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */


/* ------------------------------------------------------------------------- */
/**
 * If log is available logs the message, otherwise does nothing.
 *
 * Each line in the log file starts with a preamble that tells the time
 * when that message was produced, the type of the message and actual content.
 * When a message has more than one line the text is padded without
 * repetaing the timestamp.
 *
 * Here are some examples ("|" character is there just to indicate the
 * start of the line and is not part of the actual output):
 * @code
 * |  2017-02-10T21:37:49 title   : This is where a UserMsg starts
 * |  2017-02-10T21:37:49 error   : Text of the error message
 * |                              : that extends on two lines.
 * |  2017-02-10T21:37:46 warning : Warning message
 * |  2017-02-10T21:37:46 debug   : Debug message
 * @endcode
 */
void UserMsgMan::_logMessage (const UserMsg & um)
{
    USERMSG_TRACE_ENTRY;

    if (logger_ != NULL) {

        int i_max = um.count ();
        if (i_max > 0) {

            UM_AQUIRE_LOCK;
            const QString & t = um.title ();
            if (t.isEmpty ()) {
                _logPrefix (um.at (0));
                (*logger_) << "title   ";
                (*logger_) << um.title () << endl;
            }

            for (int i = 0; i < i_max; ++i) {
                const UserMsgEntry & e = um.at (i);
                _logPrefix (e);

                switch (e.type ()) {
                case UserMsgEntry::UTERROR: {
                    (*logger_) << "error   ";
                    break; }
                case UserMsgEntry::UTWARNING: {
                    (*logger_) << "warning ";
                    break; }
                case UserMsgEntry::UTINFO: {
                    (*logger_) << "info    ";
                    break; }
                case UserMsgEntry::UTDBG_ERROR: {
                    (*logger_) << "derror  ";
                    break; }
                case UserMsgEntry::UTDBG_WARNING: {
                    (*logger_) << "dwarning";
                    break; }
                case UserMsgEntry::UTDBG_INFO: {
                    (*logger_) << "debug   ";
                    break; }
                default: {
                    (*logger_) << "null    ";
                    break; }
                }
                (*logger_) << ": ";

                // Have the start of the text align with the rest of the
                // message in lines other than the first
                // for redability.
                static QChar new_line ('\n');
                static QLatin1String new_line_padding (
                            "\n                              : ");
                QString final = e.message ();
                (*logger_) << final.replace (new_line, new_line_padding, Qt::CaseInsensitive) << endl;
            }
            UM_RELEASE_LOCK;
        }
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * Presents a message to the user.
 */
void UserMsgMan::_showMessage (const UserMsg & um)
{
    USERMSG_TRACE_ENTRY;

    if (kb_show_ != NULL)
        kb_show_ (um);
    emit signalShow (um);

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * .
 */
void UserMsgMan::_showQueue (bool collapse_messages)
{
    USERMSG_TRACE_ENTRY;
    UM_AQUIRE_LOCK;

    if (collapse_messages) {
        UserMsg um_all;
        foreach(const UserMsg & um, message_list_) {
            um_all.append (um);
        }
        if (kb_show_ != NULL)
            kb_show_ (um_all);
        emit signalShow (um_all);
    } else {
        foreach(const UserMsg & um, message_list_) {
            if (kb_show_ != NULL)
                kb_show_ (um);
            emit signalShow (um);
        }
    }

    message_list_.clear ();
    UM_RELEASE_LOCK;
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * This method checks to see if the trigger file size was reached an,
 * if so, starts the roll feature:
 *
 * - deletes last possible log file;
 * - moves each log file to next number;
 * - moves current log file to log.1.
 */
void UserMsgMan::_logRollFeature (const QString & s_log_file_path)
{
    USERMSG_TRACE_ENTRY;

    for (;;) {
        int roll_trigger = settings_->maxLogFileSize ();
        int log_count = settings_->oldLogFilesCount ();

        // Check the size to see if we need to do this at this time?
        QFile current_file (s_log_file_path);
        if (current_file.size() < roll_trigger) {
            break;
        }

        // We do; start by deleting the last file, if any.
        static const QString roll_files ("%1.%2");
        QFile last_file (
                    QString (roll_files)
                    .arg (s_log_file_path)
                    .arg (log_count));
        if (last_file.exists()) {
            if (!last_file.remove ()) {
                printf("Cannot remove last log file");
            }
        }

        // Next, move each file to next number.
        QString to = last_file.fileName ();
        QString from;
        for (int i = log_count-1; i > 0; --i) {
            from = QString (roll_files)
                    .arg (s_log_file_path)
                    .arg (i);
            QFile file (from);
            if (file.exists()) {
                if (!file.copy (to)) {
                    printf("Cannot copy log file");
                }
                if (!file.remove ()) {
                    printf("Cannot move log file");
                }
            }
            to = from;
        }

        // Finally move current file out of the way.
        if (!current_file.copy (to)) {
            printf("Cannot copy current log file");
        }
        if (!current_file.remove ()) {
            printf("Cannot move current log file");
        }
        break;
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * @warning The caller must acquire the lock itself.
 */
void UserMsgMan::_openLogFile ()
{
    USERMSG_TRACE_ENTRY;

    if (logger_ != NULL) {
        logger_->flush ();
        delete logger_;
        logger_ = NULL;
    }

    if (log_file_ != NULL) {
        if (log_file_->isOpen ()) {
            log_file_->close ();
        }
        delete log_file_;
        log_file_ = NULL;
    }

    const QString & s_log_file_path = settings_->logFile ();
    if (!s_log_file_path.isEmpty ()) {

        int flg = QIODevice::WriteOnly | QIODevice::Text;
        if (settings_->oldLogFilesCount () == 0) {
            // 0 will overwrite the log file on each start
        } else {
            flg = flg | QIODevice::Append;
            _logRollFeature (s_log_file_path);
        }

        log_file_ = new QFile (s_log_file_path);
        if (log_file_->open ((QIODevice::OpenModeFlag)flg)) {
            logger_ = new QTextStream (log_file_);
        } else {
            printf("Failed to open log file; logging will "
                   "be disabled in this session.\n");
            delete log_file_;
            log_file_ = NULL;
        }
    }

    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

/* ------------------------------------------------------------------------- */
/**
 * .
 */
void UserMsgMan::_addMessageToQueue (const UserMsg & um)
{
    USERMSG_TRACE_ENTRY;
    UM_AQUIRE_LOCK;
    if (enabled_) {
        UM_RELEASE_LOCK;
        _showMessage (um);
    } else {
        message_list_.append (um);
        UM_RELEASE_LOCK;
    }
    USERMSG_TRACE_EXIT;
}
/* ========================================================================= */

void UserMsgMan::anchorVtable () const {}
