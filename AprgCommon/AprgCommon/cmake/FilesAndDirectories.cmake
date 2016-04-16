set(APRG_COMMON_INCLUDE_DIRECTORIES
    ${APRG_COMMON_DIR}/src
)

set(APRG_COMMON_SOURCES
    ${APRG_COMMON_DIR}/src/AlbaFileReader.cpp
    ${APRG_COMMON_DIR}/src/AlbaFileReader.hpp
    ${APRG_COMMON_DIR}/src/AlbaMacroArgumentCounter.hpp
    ${APRG_COMMON_DIR}/src/AlbaOptional.cpp
    ${APRG_COMMON_DIR}/src/AlbaOptional.hpp
    ${APRG_COMMON_DIR}/src/AlbaRaiiafPointer.cpp
    ${APRG_COMMON_DIR}/src/AlbaRaiiafPointer.hpp
    ${APRG_COMMON_DIR}/src/AlbaRandomizer.cpp
    ${APRG_COMMON_DIR}/src/AlbaRandomizer.hpp
    ${APRG_COMMON_DIR}/src/AlbaStringHelper.cpp
    ${APRG_COMMON_DIR}/src/AlbaStringHelper.hpp
    ${APRG_COMMON_DIR}/src/AlbaWindowsTimer.cpp    ${APRG_COMMON_DIR}/src/AlbaWindowsTimer.hpp
    ${APRG_COMMON_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluator.cpp
    ${APRG_COMMON_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluator.hpp
    ${APRG_COMMON_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.cpp
    ${APRG_COMMON_DIR}/src/GrepStringEvaluator/AlbaGrepStringEvaluatorTerm.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/AlbaLargeSorter.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/AlbaLargeSorterCache.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/AlbaLargeSorterConfiguration.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/AlbaLargeSorterTypes.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/DataBlock.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/DataBlockFileHandler.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/DataBlockMemoryHandler.hpp
    ${APRG_COMMON_DIR}/src/LargeSorter/DataBlocks.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWebPathHandler.hpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.cpp
    ${APRG_COMMON_DIR}/src/PathHandlers/AlbaWindowsPathHandler.hpp
)

set(APRG_COMMON_TESTS
    ${APRG_COMMON_DIR}/tst/AlbaFileReader_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaLargeSorter_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaMacroArgumentCounter_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaOptional_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaPathHandler_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaRaiiafPointer_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaRandomizer_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaStringHelper_unit.cpp
    ${APRG_COMMON_DIR}/tst/AlbaWindowsTimer_unit.cpp
    ${APRG_COMMON_DIR}/tst/GrepStringEvaluator/AlbaGrepStringEvaluator_unit.cpp)

set(APRG_COMMON_SOURCES_AND_TESTS
    ${APRG_COMMON_SOURCES}
    ${APRG_COMMON_TESTS}
)
