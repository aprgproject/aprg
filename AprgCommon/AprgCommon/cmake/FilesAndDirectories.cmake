set(APRG_COMMON_INCLUDE_DIRECTORIES
    ${APRG_COMMON_DIR}/src
)

set(APRG_COMMON_SOURCES
    ${APRG_COMMON_DIR}/src/Bit/AlbaBitManipulation.hpp
    ${APRG_COMMON_DIR}/src/Container/AlbaContainerHelper.cpp
    ${APRG_COMMON_DIR}/src/Container/AlbaContainerHelper.hpp
    ${APRG_COMMON_DIR}/src/File/AlbaFileReader.cpp    ${APRG_COMMON_DIR}/src/File/AlbaFileReader.hpp
    ${APRG_COMMON_DIR}/src/Macros/AlbaMacroArgumentCounter.hpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaMemoryBuffer.cpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaMemoryBuffer.hpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaRaiiafPointer.cpp
    ${APRG_COMMON_DIR}/src/Memory/AlbaRaiiafPointer.hpp
    ${APRG_COMMON_DIR}/src/Optional/AlbaOptional.cpp
    ${APRG_COMMON_DIR}/src/Optional/AlbaOptional.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.hpp
    ${APRG_COMMON_DIR}/src/String/AlbaStringHelper.cpp
    ${APRG_COMMON_DIR}/src/String/AlbaStringHelper.hpp
    ${APRG_COMMON_DIR}/src/Timer/AlbaWindowsTimer.cpp
    ${APRG_COMMON_DIR}/src/Timer/AlbaWindowsTimer.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaDisplayTable.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaDisplayTable.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserAutomation.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserAutomation.hpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserInterface.cpp
    ${APRG_COMMON_DIR}/src/User/AlbaUserInterface.hpp
)

set(APRG_COMMON_TESTS
    ${APRG_COMMON_DIR}/tst/AlbaBitManipulation_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaContainerHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaDisplayTable_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaFileReader_unit.cpp    ${APRG_COMMON_DIR}/tst/AlbaMacroArgumentCounter_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaMemoryBuffer_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaOptional_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaPathHandler_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaRaiiafPointer_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaStringHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaUserAutomation_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaWindowsTimer_unit.cpp
)

set(APRG_COMMON_SOURCES_AND_TESTS
    ${APRG_COMMON_SOURCES}
    ${APRG_COMMON_TESTS}
)
