# Assign common compiler flags

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    include(${APRG_DIR}/AllCommonCMakeFiles/GccAndClangFlags.cmake)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    include(${APRG_DIR}/AllCommonCMakeFiles/MsvcFlags.cmake)
endif()

if(NOT APRG_BUILD_FLAGS_TAG)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(APRG_BUILD_FLAGS_TAG "APRG_COMPILER_FLAGS_FOR_DEBUG")
    elseif(CMAKE_BUILD_TYPE STREQUAL Release)
        set(APRG_BUILD_FLAGS_TAG "APRG_COMPILER_FLAGS_FOR_RELEASE")
    endif()
endif()

print_variable(APRG_BUILD_FLAGS_TAG)
print_variable(${APRG_BUILD_FLAGS_TAG})

if(NOT APRG_LINK_FLAGS_TAG)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
        set(APRG_LINK_FLAGS_TAG "APRG_LINKER_FLAGS_FOR_DEBUG")
    elseif(CMAKE_BUILD_TYPE STREQUAL Release)
        set(APRG_LINK_FLAGS_TAG "APRG_LINKER_FLAGS_FOR_RELEASE")
    endif()
endif()

print_variable(APRG_LINK_FLAGS_TAG)
print_variable(${APRG_LINK_FLAGS_TAG})


# Putting build and link flags in cmake
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_COMMON_C_FLAGS} ${${APRG_BUILD_FLAGS_TAG}}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${APRG_COMPILER_COMMON_FLAGS} ${APRG_COMPILER_COMMON_CPP_FLAGS} ${${APRG_BUILD_FLAGS_TAG}}")
set(CMAKE_EXE_LINKER_FLAGS ${${APRG_LINK_FLAGS_TAG}})

print_variable(CMAKE_C_FLAGS)
print_variable(CMAKE_CXX_FLAGS)
print_variable(CMAKE_EXE_LINKER_FLAGS)
