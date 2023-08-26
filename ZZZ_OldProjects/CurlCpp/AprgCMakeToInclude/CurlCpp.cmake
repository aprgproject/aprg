#Include curl library, this needs aprg directory
include(${APRG_DIR}/curl/AprgCMakeToInclude/Curl.cmake)

# Assign project directory, this needs aprg directory
set(APRG_CURL_CPP_DIR ${APRG_DIR}/CurlCpp/CurlCpp/)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_CURL_CPP_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${APRG_CURL_CPP_INCLUDE_DIRECTORIES})
add_library(APRG_CURL_CPP ${APRG_CURL_CPP_SOURCES})
target_link_libraries(APRG_CURL_CPP ${CURL_LIBRARIES_TO_LINK})
