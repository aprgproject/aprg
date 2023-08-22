# Macros for files and directories

# This macro gets all C/C++ source files from a directory and adds them to a list.
macro(get_source_files_from_directory outputSourceList sourceDirectory)
    # print_status("Source directory: [${sourceDirectory}]")
    file(
        GLOB_RECURSE
        files
        "${sourceDirectory}/*.hpp"
        "${sourceDirectory}/*.cpp"
        "${sourceDirectory}/*.h"
        "${sourceDirectory}/*.c"
        "${sourceDirectory}/*.cc")
    # print_status("Adding files: ${files}")
    list(APPEND ${outputSourceList} ${files})
endmacro()

# This macro gets all C/C++ source files from all subdirectories of a directory and adds them to a list.
macro(get_source_files_from_sub_directories outputSourceList subDirectories)
    foreach(subDirectory ${${subDirectories}})
        # print_status("Source sub directory: [${subDirectory}]")
        file(
            GLOB
            files
            "${sourceDirectory}/*.hpp"
            "${sourceDirectory}/*.cpp"
            "${sourceDirectory}/*.h"
            "${sourceDirectory}/*.c"
            "${sourceDirectory}/*.cc")
        # print_status("Adding files: ${files}")
        list(APPEND ${outputSourceList} ${files})
    endforeach()
endmacro()

# This macro gets a list of all subdirectories of a directory.
macro(get_sub_directory_list result currentDirectory)
    set(resultingSubDirectories "")
    traverse_directory(resultingSubDirectories ${currentDirectory} "")
    set(${result} ${resultingSubDirectories})
endmacro()

# This macro gets a list of all subdirectories of a directory, excluding any directories that match the specified
# filter.
macro(get_sub_directory_list_with_exclusion result currentDirectory exclude_filter)
    set(resultingSubDirectories "")
    traverse_directory(resultingSubDirectories ${currentDirectory} "${exclude_filter}")
    set(${result} ${resultingSubDirectories})
endmacro()

# This macro recursively traverses a directory and its subdirectories,
# adding all directories to the output list, unlessthey match the specified exclude filter.
macro(traverse_directory resultingSubDirectories currentDirectory exclude_filter)
    file(GLOB children ${currentDirectory}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            if(NOT ("${exclude_filter}" STREQUAL "") AND "${child}" MATCHES "${exclude_filter}")
                # print_status("[DEBUG] traverse - skipping: ${child}")
            else()
                # print_status("[DEBUG] traverse: ${child}")
                traverse_directory(resultingSubDirectories ${child} "${exclude_filter}")
            endif()
        endif()
    endforeach()
    set(${resultingSubDirectories} ${${resultingSubDirectories}} ${currentDirectory})
endmacro()
