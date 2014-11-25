if (NOT USERMSG_BUILD_MODE)
    set (USERMSG_BUILD_MODE STATIC)
endif ()

include(pile_support)
pileInclude (UserMsg)
usermsgInit(${USERMSG_BUILD_MODE})
