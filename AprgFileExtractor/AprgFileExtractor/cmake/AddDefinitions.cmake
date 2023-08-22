
if(WIN32)
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="${APRG_DIR}/AprgFileExtractor/7z64/7z.exe")
    add_definitions(-DNULL_DEVICE="nul")
elseif(UNIX)
    add_definitions(-DPATH_OF_7Z_EXECUTABLE="7z")
    add_definitions(-DNULL_DEVICE="/dev/null")
endif()
add_definitions(-DPATH_OF_7Z_TEMP_FILE="${APRG_DIR}/AprgFileExtractor/Temp/TempFile.txt")
