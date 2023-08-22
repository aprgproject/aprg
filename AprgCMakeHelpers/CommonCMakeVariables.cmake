# Assign common cmake variables

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_INSTALL_PREFIX
    "${CMAKE_BINARY_DIR}/install"
    CACHE PATH "Default install path" FORCE)

include(${APRG_DIR}/AprgCMakeHelpers/CommonCMakeVariablesStaticAnalyzers.cmake)
