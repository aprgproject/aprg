cmake_minimum_required(VERSION 3.16)

# Set project details
project(AprgGnuPlot C CXX)
set(OUTFILE ${PROJECT_NAME})
set(APRG_GNU_PLOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Locate APRG Directory first because its used on other cmakes
include(${APRG_GNU_PLOT_DIR}/cmake/LocateAprgDirectory.cmake)

# Assign macros, common flags, definitions and other common steps
include(${APRG_DIR}/AllCommonCMakeFiles/AllCommonSteps.cmake)

# Include other projects
include(${APRG_DIR}/AprgGnuPlot/AprgCMakeToInclude/GnuPlotWrapper.cmake)
include(${APRG_DIR}/gtest/AprgCMakeToInclude/gtest.cmake)
include(${APRG_DIR}/AprgCommon/AprgCMakeToInclude/AprgCommon.cmake)
include(${APRG_DIR}/boost/AprgCMakeToInclude/boost.cmake)
include(${APRG_DIR}/AprgAlgebra/AprgCMakeToInclude/AprgAlgebra.cmake)
include(${APRG_DIR}/AprgGeometry/AprgCMakeToInclude/AprgGeometry.cmake)

# Assign files, directories, flags, definitions and other specific steps
include(${APRG_GNU_PLOT_DIR}/cmake/SpecificStepsAsExecutable.cmake)

# Do final steps
add_executable(${OUTFILE} ${APRG_GNU_PLOT_SOURCES_AND_TESTS})
include_directories(
  ${APRG_GNU_PLOT_INCLUDE_DIRECTORIES}
  ${APRG_GNU_PLOT_TEST_INCLUDE_DIRECTORIES} ${GTEST_INCLUDE_DIRECTORIES})
target_link_libraries(${OUTFILE} APRG_GEOMETRY APRG_ALGEBRA APRG_COMMON
                      ${Boost_LIBRARIES} ${APRG_GTEST_DEPENDENCIES})
add_test(${OUTFILE} ${OUTFILE})
install(TARGETS ${OUTFILE} DESTINATION runDirectory)
include(${APRG_DIR}/AllCommonCMakeFiles/LastStep.cmake)
