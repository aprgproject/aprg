set(APRG_AUDIO_MANIPULATOR_SOURCE_DIRECTORY
    ${APRG_AUDIO_MANIPULATOR_DIR}/src
)

set(APRG_AUDIO_MANIPULATOR_TEST_DIRECTORY
    ${APRG_AUDIO_MANIPULATOR_DIR}/tst
)

set(APRG_AUDIO_MANIPULATOR_MAIN_DIRECTORY
    ${APRG_AUDIO_MANIPULATOR_DIR}/main
)

set(APRG_AUDIO_MANIPULATOR_INCLUDE_DIRECTORIES
    ${APRG_AUDIO_MANIPULATOR_SOURCE_DIRECTORY}
)

set(APRG_AUDIO_MANIPULATOR_TEST_INCLUDE_DIRECTORIES
    ${APRG_AUDIO_MANIPULATOR_TEST_DIRECTORY}
)

PRINT_STATUS("Looking for SRC directories in: [${APRG_AUDIO_MANIPULATOR_SOURCE_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_MANIPULATOR_SOURCES APRG_AUDIO_MANIPULATOR_SOURCE_DIRECTORY_LIST)

PRINT_STATUS("Looking for TST directories in: [${APRG_AUDIO_MANIPULATOR_TEST_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_MANIPULATOR_TESTS APRG_AUDIO_MANIPULATOR_TEST_DIRECTORY_LIST)

PRINT_STATUS("Looking for MAIN directories in: [${APRG_AUDIO_MANIPULATOR_MAIN_DIRECTORY}]")
GET_SOURCE_FILES_FROM_DIRECTORIES(APRG_AUDIO_MANIPULATOR_MAIN_SOURCES APRG_AUDIO_MANIPULATOR_MAIN_DIRECTORY_LIST)

set(APRG_AUDIO_MANIPULATOR_SOURCES_AND_TESTS
    ${APRG_AUDIO_MANIPULATOR_SOURCES}
    ${APRG_AUDIO_MANIPULATOR_TESTS}
)
