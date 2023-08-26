# Assign project directory, this needs aprg directory
set(BENCHMARK_LIBRARY_DIR ${APRG_DIR}/benchmark/benchmarkLibrary/)

set(BENCHMARK_LIBRARY_INCLUDE ${BENCHMARK_LIBRARY_DIR}/include)

set(BENCHMARK_LIBRARY_SOURCE_DIRECTORY ${BENCHMARK_LIBRARY_DIR}/src)

print_status("Looking for benchmark library sources C/C++ files in: [${BENCHMARK_LIBRARY_SOURCE_DIRECTORY}]")
get_source_files_from_directory(BENCHMARK_LIBRARY_SOURCES ${BENCHMARK_LIBRARY_SOURCE_DIRECTORY})

include_directories(${BENCHMARK_LIBRARY_INCLUDE})
add_library(BENCHMARK_LIBRARY ${BENCHMARK_LIBRARY_SOURCES})
set(BENCHMARK_LIBRARY_TO_LINK BENCHMARK_LIBRARY)
