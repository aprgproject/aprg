# Assign macros, common flags, definitions and other common steps

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Default install path" FORCE)

include(${APRG_DIR}/AprgCMakeHelpers/FileAndDirectoryMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/PrintMacros.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonFlags.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDefinitions.cmake)
include(${APRG_DIR}/AprgCMakeHelpers/CommonDependencies.cmake)
