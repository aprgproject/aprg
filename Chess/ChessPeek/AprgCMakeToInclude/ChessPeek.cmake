# Assign project directory, this needs aprg directory
set(CHESS_PEEK_DIR ${APRG_DIR}/ChessPeek/ChessPeek/)

# Assign files, directories, flags, definitions and other specific steps
include(${CHESS_PEEK_DIR}/cmake/SpecificStepsAsLibrary.cmake)

include_directories(${CHESS_PEEK_INCLUDE_DIRECTORIES})
add_library(CHESS_PEEK ${CHESS_PEEK_SOURCES})
