# Assign project directory, this needs aprg directory
set(CHESS_UTILITIES_DIR ${APRG_DIR}/Chess/ChessUtilities/ChessUtilities/)

# Assign files, directories, flags, definitions and other specific steps
include(${CHESS_UTILITIES_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${CHESS_UTILITIES_INCLUDE_DIRECTORIES})
add_library(CHESS_UTILITIES ${CHESS_UTILITIES_SOURCES})
