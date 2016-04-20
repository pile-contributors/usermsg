/**
 * @file usermsg.h
 * @brief Declarations for UserMsg class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSG_H_INCLUDE
#define GUARD_USERMSG_H_INCLUDE

#include <usermsg/usermsg-config.h>
#include <usermsg/usermsgentry.h>

#include <QVector>



//! user messages mediator
class USERMSG_EXPORT UserMsg {

    enum StandardReply {
        // keep this in sync with QMessageBox::StandardButton
        NoButton           = 0x00000000,
        Ok                 = 0x00000400,
        Save               = 0x00000800,
        SaveAll            = 0x00001000,
        Open               = 0x00002000,
        Yes                = 0x00004000,
        YesToAll           = 0x00008000,
        No                 = 0x00010000,
        NoToAll            = 0x00020000,
        Abort              = 0x00040000,
        Retry              = 0x00080000,
        Ignore             = 0x00100000,
        Close              = 0x00200000,
        Cancel             = 0x00400000,
        Discard            = 0x00800000,
        Help               = 0x01000000,
        Apply              = 0x02000000,
        Reset              = 0x04000000,
        RestoreDefaults    = 0x08000000,

    };


private:

    QString
    title_; /**< a title for this message */

    void *
    user_payload_; /**< user defined data that the user sets */

    QVector<UserMsgEntry>
    message_list_; /**< the list of messages */

public:

    //! Default constructor.
    UserMsg ();

    //! Copy constructor.
    UserMsg (
            const UserMsg & other);

    //! Constructor that also sets the title and payload.
    UserMsg (
            const QString & title,
            void * user_data = NULL);


    //! Destructor.
    virtual ~UserMsg();


    //! Get the title.
    const QString &
    title () const {
        return title_;
    }

    //! Set the title.
    void
    setTitle (
            const QString & value) {
        title_ = value;
    }


    //! Get the payload.
    void *
    userData () const {
        return user_payload_;
    }

    //! Set the payload.
    void
    setUserData (
            void * value) {
        user_payload_ = value;
    }

    //! Show the content of this structure.
    void
    show ();

    //! The number of entries in the list.
    int
    count () const {
        return message_list_.count ();
    }

    //! Clear all entries from the list.
    void
    clear () {
        message_list_.clear ();
    }

    //! Get an entry at a specific location.
    const UserMsgEntry &
    at (
            int i) const {
        return message_list_.at (i);
    }

    //! Remove an entry at a specific location.
    void
    remove (
            int i) {
        message_list_.removeAt (i);
    }

    //! Appends all entries in \p other entry to current entry.
    void
    append (
            const UserMsg & other);



    //! Add an error entry to the list.
    inline void
    addErr (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTERROR, s_message);
    }

    //! add a warning entry to the list.
    inline void
    addWar (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTWARNING, s_message);
    }

    //! Add an informative entry to the list.
    inline void
    addInfo (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTINFO, s_message);
    }

    //! Add an error entry to the list.
    inline void
    addDbgErr (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTDBG_ERROR, s_message);
    }

    //! Add a warning entry to the list.
    inline void
    addDbgWar (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTDBG_WARNING, s_message);
    }

    //! Add an informative entry to the list.
    inline void
    addDbgInfo (
            const QString & s_message) {
        addMsg (UserMsgEntry::UTDBG_INFO, s_message);
    }

    //! Add an entry to the list.
    void
    addMsg (
            UserMsgEntry::Type ty,
            const QString & s_message);

    //! Adds messages from two instances and deposits them in a new one.
    UserMsg operator+ (const UserMsg & s) const;
    UserMsg & operator+= (const UserMsg & s);

    //! Adds the string as an error message and deposits them in a new instance.
    UserMsg operator+ (const QString & s) const;
    UserMsg & operator+= (const QString & s);

    //! Adds the string as a warning message and deposits them in a new instance.
    UserMsg operator& (const QString & s) const;
    UserMsg & operator&= (const QString & s);

    //! Adds the string as an informative message and deposits them in a new instance.
    UserMsg operator* (const QString & s) const;
    UserMsg & operator*= (const QString & s);

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


    //! Termination message.
    static void
    fatalException (
            const QString & s_message);


    //! Ask a question at the console; accept Yes/No answer.
    static int
    consoleAskYN (
            const QString & s_message);

protected:

private:

};

#endif // GUARD_USERMSG_H_INCLUDE
