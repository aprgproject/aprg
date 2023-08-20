# Macros for files and directories

# This macro gets all C/C++ source files from a directory and adds them to a list.
macro(GET_SOURCE_FILES_FROM_DIRECTORY outputSourceList sourceDirectory)
    #PRINT_STATUS("Source directory: [${sourceDirectory}]")
    file(GLOB_RECURSE files "${sourceDirectory}/*.hpp" "${sourceDirectory}/*.cpp" "${sourceDirectory}/*.h" "${sourceDirectory}/*.c" "${sourceDirectory}/*.cc")
    #PRINT_STATUS("Adding files: ${files}")
    list(APPEND ${outputSourceList} ${files})
endmacro()

# This macro gets all C/C++ source files from all subdirectories of a directory and adds them to a list.
macro(GET_SOURCE_FILES_FROM_SUB_DIRECTORIES outputSourceList subDirectories)
    foreach(subDirectory ${${subDirectories}})
        #PRINT_STATUS("Source sub directory: [${subDirectory}]")
        file(GLOB files "${sourceDirectory}/*.hpp" "${sourceDirectory}/*.cpp" "${sourceDirectory}/*.h" "${sourceDirectory}/*.c" "${sourceDirectory}/*.cc")
        #PRINT_STATUS("Adding files: ${files}")
        list(APPEND ${outputSourceList} ${files})
    endforeach()
endmacro()

# This macro gets a list of all subdirectories of a directory.
macro(GET_SUB_DIRECTORY_LIST result currentDirectory)
    set(resultingSubDirectories "")
    TRAVERSE_DIRECTORY(resultingSubDirectories ${currentDirectory} "")
    set(${result} ${resultingSubDirectories})
endmacro()

# This macro gets a list of all subdirectories of a directory, excluding any directories that match the specified filter.
macro(GET_SUB_DIRECTORY_LIST_WITH_EXCLUSION result currentDirectory exclude_filter)
    set(resultingSubDirectories "")
    TRAVERSE_DIRECTORY(resultingSubDirectories ${currentDirectory} "${exclude_filter}")
    set(${result} ${resultingSubDirectories})
endmacro()

# This macro recursively traverses a directory and its subdirectories, adding all directories to the output list, unless they match the specified exclude filter.
macro(TRAVERSE_DIRECTORY resultingSubDirectories currentDirectory exclude_filter)
    file(GLOB children ${currentDirectory}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            if(NOT("${exclude_filter}" STREQUAL "") AND "${child}" MATCHES "${exclude_filter}")
                #PRINT_STATUS("[DEBUG] traverse - skipping: ${child}")
            else()
                #PRINT_STATUS("[DEBUG] traverse: ${child}")
                TRAVERSE_DIRECTORY(resultingSubDirectories ${child} "${exclude_filter}")
            endif()
        endif()
    endforeach()
    set(${resultingSubDirectories} ${${resultingSubDirectories}} ${currentDirectory})
endmacro()