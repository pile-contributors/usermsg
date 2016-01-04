
# enable/disable cmake debug messages related to this pile
set (USERMSG_DEBUG_MSG OFF)

# make sure support code is present; no harm
# in including it twice; the user, however, should have used
# pileInclude() from pile_support.cmake module.
include(pile_support)

# initialize this module
macro    (usermsgInit
          usermsg_use_mode)

    # default name
    if (NOT USERMSG_INIT_NAME)
        set(USERMSG_INIT_NAME "UserMsg")
    endif ()

    # compose the list of headers and sources
    set(USERMSG_HEADERS
        "usermsgman.h"
        "usermsgstg.h"
        "usermsgentry.h"
        "usermsg.h"
        "logmsg.h"
        "impl/usermsg_impl.h")
    set(USERMSG_SOURCES
        "usermsgman.cc"
        "usermsgstg.cc"
        "usermsgentry.cc"
        "usermsg.cc"
        "logmsg.cc"
        "impl/usermsg_json.cc"
        "impl/usermsg_user.cc"
        "impl/usermsg_xml.cc")
    set(USERMSG_QT_MODS
        "Core"
        "Widgets")

    pileSetSources(
        "${USERMSG_INIT_NAME}"
        "${USERMSG_HEADERS}"
        "${USERMSG_SOURCES}")

    pileSetCommon(
        "${USERMSG_INIT_NAME}"
        "0;0;1;d"
        "ON"
        "${usermsg_use_mode}"
        ""
        "basics"
        "user-interaction")

endmacro ()
