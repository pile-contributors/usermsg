/**
 * @file usermsg.h
 * @brief Declarations for UserMsg class
 * @author 
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

    //! the number of entries in the list
    int
    count () const {
        return message_list_.count ();
    }

    //! clear all entries from the list
    void
    clear () {
        message_list_.clear ();
    }

    //! get an entry at a specific location
    const UserMsgEntry &
    at (
            int i) const {
        return message_list_.at (i);
    }

    //! remove an entry at a specific location
    void
    remove (
            int i) {
        message_list_.removeAt (i);
    }

    //! Appends all entries in \p other entry to current entry
    void
    append (
            const UserMsg & other);



    //! add an error entry to the list
    inline void
    addErr (
            const QString & s_message) {
        addMsg (UserMsgEntry::ERROR, s_message);
    }

    //! add a warning entry to the list
    inline void
    addWar (
            const QString & s_message) {
        addMsg (UserMsgEntry::WARNING, s_message);
    }

    //! add an informative entry to the list
    inline void
    addInfo (
            const QString & s_message) {
        addMsg (UserMsgEntry::INFO, s_message);
    }

    //! add an error entry to the list
    inline void
    addDbgErr (
            const QString & s_message) {
        addMsg (UserMsgEntry::DBG_ERROR, s_message);
    }

    //! add a warning entry to the list
    inline void
    addDbgWar (
            const QString & s_message) {
        addMsg (UserMsgEntry::DBG_ERROR, s_message);
    }

    //! add an informative entry to the list
    inline void
    addDbgInfo (
            const QString & s_message) {
        addMsg (UserMsgEntry::DBG_INFO, s_message);
    }

    //! add an entry to the list
    void
    addMsg (
            UserMsgEntry::Type ty,
            const QString & s_message);




    //! show an error entry
    static inline void
    err (
            const QString & s_message) {
        msg (UserMsgEntry::ERROR, s_message);
    }

    //! show a warning entry
    static inline void
    war (
            const QString & s_message) {
        msg (UserMsgEntry::WARNING, s_message);
    }

    //! show an informative entry
    static inline void
    info (
            const QString & s_message) {
        msg (UserMsgEntry::INFO, s_message);
    }

    //! show an error entry
    static inline void
    dbgErr (
            const QString & s_message) {
        msg (UserMsgEntry::DBG_ERROR, s_message);
    }

    //! show a warning entry
    static inline void
    dbgWar (
            const QString & s_message) {
        msg (UserMsgEntry::DBG_ERROR, s_message);
    }

    //! show an informative entry
    static inline void
    dbgInfo (
            const QString & s_message) {
        msg (UserMsgEntry::DBG_INFO, s_message);
    }

    //! show an entry
    static void
    msg (
            UserMsgEntry::Type ty,
            const QString & s_message);



protected:

private:

};

#endif // GUARD_USERMSG_H_INCLUDE
