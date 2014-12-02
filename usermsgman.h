/**
 * @file usermsgman.h
 * @brief Declarations for UserMsgMan class
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSGMAN_H_INCLUDE
#define GUARD_USERMSGMAN_H_INCLUDE

#include <usermsg/usermsg-config.h>
#include <usermsg/usermsg.h>

#include <QObject>
#include <QAtomicInt>

class UserMsgStg;
class UserMsg;

//! brief description
class USERMSG_EXPORT UserMsgMan : public QObject {
    Q_OBJECT

public:

    //! the calback that may be used to be informed about messages
    typedef void (*KbShowMessage) (const UserMsg & um);

private:

    bool
    enabled_; /**< cache mode (false) or display mode (true) */

    UserMsgStg *
    settings_; /**< the settings */

    QVector<UserMsg>
    message_list_; /**< the list of messages */

    QAtomicInt
    lock_; /** lock for using shared resources*/

    KbShowMessage
    kb_show_;

    static UserMsgMan *
    singleton_; /**< the one and only instance */

private:

    //! Default constructor.
    UserMsgMan ();

    //! Destructor.
    virtual ~UserMsgMan();

public:

    //! Get the singleton.
    static UserMsgMan *
    singleton ();

    //! Prepares the manager for being used.
    static bool
    init (
            bool start_disabled = false);

    //! Terminates the manager (releases resources).
    static void
    end ();

    //! Tells if the manager has been initialized.
    static bool
    isInitialized();


    //! Get the settings.
    static const UserMsgStg &
    settings ();

    //! Copy the settings to internal storage.
    static void
    setSettings (
            const UserMsgStg & value);


    //! Get the callback.
    static KbShowMessage
    callbackShow ();

    //! Copy the settings to internal storage.
    static void
    setCallbackShow (
            KbShowMessage value);


    //! Sets the cache mode; no messages are being shown.
    static void
    disable ();

    //! Exist cached mode; cached messages are being shown.
    static void
    enable (
            bool collapse_messages = false);

    //! Tells if the manager is in cached mode (false).
    static bool
    isEnabled();


    //! tells if a type is visible or not
    static bool
    isVisible (
            UserMsgEntry::Type value);

    //! enables or disables the visibility of a type
    static void
    setVisible (
            UserMsgEntry::Type ty,
            bool b_visible);

    //! Shows an error message.
    static void
    show (
            const UserMsg & um);

private:

    //! used internally to start the manager if not started already
    static void
    autostart ();


    //! Appends the message to the queue.
    void
    _addMessageToQueue (
            const UserMsg & um);

    //! Shows an error message.
    void
    _showMessage (
            const UserMsg & um);

    //! Presents the queue to the user.
    void
    _showQueue (
            bool collapse_messages);

signals:

    //! A message should be shown.
    void
    signalShow(
             UserMsg um);


};

#endif // GUARD_USERMSGMAN_H_INCLUDE