# Assign project directory, this needs aprg directory
set(BENCHMARK_DIR ${APRG_DIR}/benchmark/benchmark/)
set(BENCHMARK_FROM_GIT_HUB_DIR ${APRG_DIR}/benchmark/benchmarkFromGitHub/)

# Assign files, directories, flags, definitions and other specific steps
include(${BENCHMARK_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${BENCHMARK_INCLUDE_DIRECTORIES})
add_library(BENCHMARK ${BENCHMARK_SOURCES})
