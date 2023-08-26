include(${APRG_DIR}/gtest/AprgCMakeToInclude/CommonSteps.cmake)

set(GOOGLE_TEST_DIR ${GTEST_DIR}/googletest)

set(GTEST_INCLUDE_DIRECTORIES
    ${GOOGLE_TEST_DIR}/include
    ${GOOGLE_TEST_DIR}/
    )

add_library(gtest
    ${GOOGLE_TEST_DIR}/src/gtest-all.cc
    ${GOOGLE_TEST_DIR}/src/gtest_main.cc
    )

enable_testing(true)

