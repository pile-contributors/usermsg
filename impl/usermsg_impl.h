/**
 * @file usermsg.h
 * @brief Declarations for UserMsg class
 * @author Nicu Tofan <nicu.tofan@gmail.com>
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSG_IMPL_H_INCLUDE
#define GUARD_USERMSG_IMPL_H_INCLUDE

#include <usermsg/usermsg-config.h>
#include <usermsg/usermsg.h>

void USERMSG_EXPORT showUserMsgUser (const UserMsg & um);
void USERMSG_EXPORT showUserMsgJson (const UserMsg & um);
void USERMSG_EXPORT showUserMsgXml  (const UserMsg & um);

#endif // GUARD_USERMSG_IMPL_H_INCLUDE
