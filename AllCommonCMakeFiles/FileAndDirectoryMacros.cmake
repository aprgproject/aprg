# Macros for files and directories

# Macro: get_source_files_from_directory
# -> Retrieves a list of C/C++ source files (headers, sources, and others) from the specified source directory.
# -> Appends the list of files to the provided output list variable.
# -> Usage: get_source_files_from_directory(outputSourceList sourceDirectory)
macro(get_source_files_from_directory outputSourceList sourceDirectory)
    # Retrieve all C/C++ source files (headers, sources, etc.) from the directory.
    file(
        GLOB_RECURSE
        files
        "${sourceDirectory}/*.hpp"
        "${sourceDirectory}/*.cpp"
        "${sourceDirectory}/*.h"
        "${sourceDirectory}/*.c"
        "${sourceDirectory}/*.cc")
    # Append the gathered source files to the output list.
    list(APPEND ${outputSourceList} ${files})
endmacro()

# Macro: get_source_files_from_sub_directories
# -> Retrieves C/C++ source files from subdirectories within the specified list of subdirectories.
# -> Appends the list of files to the provided output list variable.
# -> Usage: get_source_files_from_sub_directories(outputSourceList subDirectories)
macro(get_source_files_from_sub_directories outputSourceList subDirectories)
    foreach(subDirectory ${${subDirectories}})
        # Retrieve C/C++ source files (headers, sources, etc.) from the subdirectory.
        file(
            GLOB
            files
            "${subDirectory}/*.hpp"
            "${subDirectory}/*.cpp"
            "${subDirectory}/*.h"
            "${subDirectory}/*.c"
            "${subDirectory}/*.cc")
        # Append the gathered source files to the output list.
        list(APPEND ${outputSourceList} ${files})
    endforeach()
endmacro()

# Macro: get_sub_directory_list
# -> Retrieves a list of subdirectories within the specified directory.
# -> Appends the list of subdirectories to the provided output list variable.
# -> Usage: get_sub_directory_list(result currentDirectory)
macro(get_sub_directory_list result currentDirectory)
    set(resultingSubDirectories "")
    traverse_directory(resultingSubDirectories ${currentDirectory} "")
    set(${result} ${resultingSubDirectories})
endmacro()

# Macro: get_sub_directory_list_with_exclusion
# -> Retrieves a list of subdirectories within the specified directory, excluding those matching the given filter.
# -> Appends the filtered list of subdirectories to the provided output list variable.
# -> Usage: get_sub_directory_list_with_exclusion(result currentDirectory exclude_filter)
macro(get_sub_directory_list_with_exclusion result currentDirectory exclude_filter)
    set(resultingSubDirectories "")
    traverse_directory(resultingSubDirectories ${currentDirectory} "${exclude_filter}")
    set(${result} ${resultingSubDirectories})
endmacro()

# Macro: traverse_directory
# -> Recursively traverses the specified directory and its subdirectories.
# -> Adds all directories to the output list, except those matching the specified exclude filter.
# -> Usage: traverse_directory(resultingSubDirectories currentDirectory exclude_filter)
macro(traverse_directory resultingSubDirectories currentDirectory exclude_filter)
    file(GLOB children ${currentDirectory}/*)
    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            if(NOT ("${exclude_filter}" STREQUAL "") AND "${child}" MATCHES "${exclude_filter}")
                # Skip directories that match the exclusion filter.
            else()
                # Traverse the subdirectory recursively.
                traverse_directory(resultingSubDirectories ${child} "${exclude_filter}")
            endif()
        endif()
    endforeach()
    # Append the current directory to the resulting list.
    set(${resultingSubDirectories} ${${resultingSubDirectories}} ${currentDirectory})
endmacro()
