
# enable/disable cmake debug messages related to this pile
set (USERMSG_DEBUG_MSG ON)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (usermsgInit
          ref_cnt_use_mode)

    # default name
    if (NOT USER_MSG_INIT_NAME)
        set(USER_MSG_INIT_NAME "UserMsg")
    endif ()

    # compose the list of headers and sources
    set(USERMSG_HEADERS
        "usermsgman.h"
        "usermsgstg.h"
        "usermsgentry.h"
        "usermsg.h")
    set(USERMSG_SOURCES
        "usermsgman.cc"
        "usermsgstg.cc"
        "usermsgentry.cc"
        "usermsg.cc")
    set(USERMSG_QT_MODS
        "Core"
        "Widgets")

    pileSetSources(
        "${USER_MSG_INIT_NAME}"
        "${USERMSG_HEADERS}"
        "${USERMSG_SOURCES}")

    pileSetCommon(
        "${USER_MSG_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${ref_cnt_use_mode}"
        ""
        "category1"
        "tag1;tag2")

endmacro ()
