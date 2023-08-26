# Assign common compiler flags

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    include(${APRG_DIR}/AllCommonCMakeFiles/GccAndClangFlags.cmake)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include(${APRG_DIR}/AllCommonCMakeFiles/MsvcFlags.cmake)
endif()
