/**
 * @file usermsgentry.h
 * @brief Declarations for UserMsgEntry class
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSGENTRY_H_INCLUDE
#define GUARD_USERMSGENTRY_H_INCLUDE

#include <usermsg/usermsg-config.h>

#include <QString>
#include <QDateTime>

//! user messages mediator
class USERMSG_EXPORT UserMsgEntry {

public:

    //! kind of the message
    enum Type {
        UTERROR = 0,
        UTWARNING,
        UTINFO,
        UTDBG_ERROR,
        UTDBG_WARNING,
        UTDBG_INFO
    };

private:

    QString message_; /**< the message */
    QDateTime moment_; /**< the time when this occured */
    Type type_; /**< the kind */

public:

    //! Default constructor.
    UserMsgEntry ();

    //! Copy constructor.
    UserMsgEntry (
            const UserMsgEntry & other);

    //! Constructor. Sets the message and type.
    UserMsgEntry (
            Type ty,
            const QString & message);

    //! Destructor.
    virtual ~UserMsgEntry();


    //! Get the message.
    const QString &
    message () const {
        return message_;
    }

    //! Set the message.
    void
    setMessage (
            const QString & value) {
        message_ = value;
    }


    //! Get the moment.
    const QDateTime &
    moment () const {
        return moment_;
    }

    //! Set the moment.
    void
    setMoment (
            const QDateTime & value) {
        moment_ = value;
    }


    //! Tell if the type is visible or not.
    bool
    isEnabled () const;

    //! Get the type.
    Type
    type () const {
        return type_;
    }

    //! Set the type.
    void
    setType (
            Type value) {
        type_= value;
    }

    //! Get the name of the type in all-lower-case
    QString
    typeName () const {
        return typeName (type_);
    }

    //! get the name of the type with first letter in words capitalized
    QString
    typeNameCap () const {
        return typeNameCap (type_);
    }


public:

    //! Get the name of the type in all-lower-case
    static QString
    typeName (
            Type value);

    //! get the name of the type with first letter in words capitalized
    static QString
    typeNameCap (
            Type value);

    //! Tell if the type is visible or not.
    static bool
    isEnabled (
            Type value);

protected:

private:

};

#endif // GUARD_USERMSGENTRY_H_INCLUDE
