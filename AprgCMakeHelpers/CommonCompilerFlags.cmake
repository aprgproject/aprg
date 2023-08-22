# Assign common compiler flags

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    include(${APRG_DIR}/AprgCMakeHelpers/GccFlags.cmake)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include(${APRG_DIR}/AprgCMakeHelpers/MsvcFlags.cmake)
endif()
