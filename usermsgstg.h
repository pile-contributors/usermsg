/**
 * @file usermsgstg.h
 * @brief Declarations for UserMsgStg class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSGSTG_H_INCLUDE
#define GUARD_USERMSGSTG_H_INCLUDE

#include <usermsg/usermsg-config.h>
#include <usermsg/usermsg.h>

class QSettings;

//! User messages mediator settings.
class USERMSG_EXPORT UserMsgStg {

private:

    int enabled_flags_; /**< combination of 1 bit flags */
    QString s_log_file_; /**< the log file, if any */
    int log_count_; /**< number of logs to keep (0 will overwrite the
                    log file on each start */
    int roll_trigger_; /**< size of the log file in bytes that
                       tells the program to start anew */

public:

    //! Default constructor.
    UserMsgStg ();

    //! Copy constructor.
    UserMsgStg (
            const UserMsgStg & other);

    //! Destructor.
    virtual ~UserMsgStg();


    //! Serializes the settings to a string of bytes.
    QByteArray
    toByteArray () const;

    //! Load previously serialized settings from a string of bytes.
    bool
    fromByteArray (
            QByteArray * value);

    //! Saves the settings to provided QSettings.
    bool
    toQSettings (
            QSettings * stg) const;

    //! Load previously serialized settings from QSettings.
    bool
    fromQSettings (
            QSettings * stg);

    //! tells if a type is visible or not
    bool
    isEnabled (
            UserMsgEntry::Type value);

    //! enables or disables the visibility of a type
    void
    setEnabled (
            UserMsgEntry::Type ty,
            bool b_enabled);

    //! Enable all types
    void
    setAllEnabled (
            bool include_debug);

    //! The path to the log file.
    const QString &
    logFile () {
        return s_log_file_;
    }

    //! Set the path to the log file
    void
    setLogFile (
            const QString & value) {
        s_log_file_ = value;
    }

    //! The number of old log files to keep around.
    int
    oldLogFilesCount () {
        return log_count_;
    }

    //! The number of old log files to keep around.
    void
    setOldLogFilesCount (
            int value) {
        log_count_ = value;
    }

    //! Maximum size of the log file in bytes.
    int
    maxLogFileSize () {
        return roll_trigger_;
    }

    //! Maximum size of the log file in bytes.
    void
    setMaxLogFileSize (
            int value) {
        roll_trigger_ = value;
    }

private:

    //! Checks the values and brings them to sane values if necessary.
    void
    sanityCheck ();
};

#endif // GUARD_USERMSGSTG_H_INCLUDE
