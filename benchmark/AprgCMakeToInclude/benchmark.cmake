# Assign project directory, this needs aprg directory
set(BENCHMARK_DIR ${APRG_DIR}/benchmark/benchmark/)
set(BENCHMARK_LIBRARY_DIR ${APRG_DIR}/benchmark/benchmarkLibrary/)

# Assign files, directories, flags, definitions and other specific steps
include(${BENCHMARK_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${BENCHMARK_LIBRARY_INCLUDE})
add_library(BENCHMARK ${BENCHMARK_LIBRARY_SOURCES})
