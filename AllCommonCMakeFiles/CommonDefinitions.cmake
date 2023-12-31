# Assign common definitions

# NOTE: CMAKE_BUILD_TYPE is set as Debug in AllCommonSteps.cmake if its empty
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_RELEASE)
endif()

set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_DIR="${APRG_DIR}")

if(WIN32)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DOS_WINDOWS)
elseif(APPLE)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DOS_APPLE)
elseif(UNIX)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DOS_LINUX)
endif()

# Use Git to get code version
# Use [git rev-parse HEAD] to get full git version
# Use [git rev-parse --short HEAD] to get short version
find_package(Git) # Requires CMake 2.8.11+
if(GIT_EXECUTABLE)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        RESULT_VARIABLE status
        OUTPUT_VARIABLE GIT_CODE_VERSION
        ERROR_QUIET OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(status)
        set(GIT_CODE_VERSION "NoVersion")
    endif()
endif()
set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_CODE_REVISION="${GIT_CODE_VERSION}")

# SVN is not used anymore
# find_package(Subversion)
# if(SUBVERSION_FOUND)
#     Subversion_WC_INFO(${PROJECT_SOURCE_DIR} SvnProject IGNORE_SVN_FAILURE)
#     message("Code revision is ${SvnProject_WC_REVISION}")
#     set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_CODE_REVISION="${SvnProject_WC_REVISION}")
# endif()

if(APRG_TEST_MODE)
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_TEST_MODE_ON)
else()
    set(COMMON_DEFINITIONS ${COMMON_DEFINITIONS} -DAPRG_TEST_MODE_OFF)
endif()

add_definitions(${COMMON_DEFINITIONS})
