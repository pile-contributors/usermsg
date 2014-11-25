/**
 * @file usermsg-private.h
 * @brief Declarations for UserMsg class
 * @author 
 * @copyright Copyright 2014 piles contributors. All rights reserved.
 * This file is released under the
 * [MIT License](http://opensource.org/licenses/mit-license.html)
 */

#ifndef GUARD_USERMSG_PRIVATE_H_INCLUDE
#define GUARD_USERMSG_PRIVATE_H_INCLUDE

#include <usermsg/usermsg-config.h>

#if 0
#    define USERMSG_DEBUGM printf
#else
#    define USERMSG_DEBUGM black_hole
#endif

#if 0
#    define USERMSG_TRACE_ENTRY printf("USERMSG ENTRY %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define USERMSG_TRACE_ENTRY
#endif

#if 0
#    define USERMSG_TRACE_EXIT printf("USERMSG EXIT %s in %s[%d]\n", __func__, __FILE__, __LINE__)
#else
#    define USERMSG_TRACE_EXIT
#endif


static inline void black_hole (...)
{}

#endif // GUARD_USERMSG_PRIVATE_H_INCLUDE
