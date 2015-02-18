/**
 * @file usermsgstg.h
 * @brief Declarations for UserMsgStg class
 * @author 
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

    int enabled_flags_;

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

};

#endif // GUARD_USERMSGSTG_H_INCLUDE
