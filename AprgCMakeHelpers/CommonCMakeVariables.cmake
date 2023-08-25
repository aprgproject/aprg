# Assign common cmake variables

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_INSTALL_PREFIX
    "${CMAKE_BINARY_DIR}/install"
    CACHE PATH "Default install path" FORCE)

set(CMAKE_COLOR_DIAGNOSTICS ON)
set(CCMAKE_COLORS "s=39:p=220:c=207:n=196:y=46")
print_variable(CMAKE_COLOR_DIAGNOSTICS)
print_variable(CCMAKE_COLORS)

include(${APRG_DIR}/AprgCMakeHelpers/CommonCMakeVariablesStaticAnalyzers.cmake)
