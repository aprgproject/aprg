#!/bin/bash

findAprgDirectory() {
    # Set variable values
    local aprgDirectoryName
    local scriptName
    local inputDirectory
    aprgDirectoryName="aprg"
    scriptName="locateAprgDirectory.sh"
    inputDirectory=$(realpath "$1")
    aprgDirectory=""
    
    # Validate input
    if ! [ -d "$inputDirectory" ]; then
        echo "$scriptName:$LINENO: Error: The input directory [$inputDirectory] is not a directory."
        exit 1
    fi
    
    # Display variable values
    echo "$scriptName:$LINENO: The aprg directory name is [$aprgDirectoryName]."
    echo "$scriptName:$LINENO: The input directory is [$inputDirectory] for searching [$aprgDirectoryName] directory."
    
    # Set variable values for search
    searchingDirectory="$inputDirectory"
    
    # Loop until we reach the root directory ("/")
    while [ "$searchingDirectory" != "/" ]; do
        # Check if the directory exists in the current directory
        if [ "$(basename "$searchingDirectory")" == "$aprgDirectoryName" ]; then
            aprgDirectory="$searchingDirectory"
            break
        else
            # Go one directory up
            searchingDirectory=$(dirname "$searchingDirectory")
        fi
    done
    
    # Validate aprgDirectory
    if [ "$searchingDirectory" == "/" ]  || [ "$searchingDirectory" == "." ]; then
        echo "$scriptName:$LINENO: Error: The directory name [$aprgDirectoryName] is not found in any parent directories of [$inputDirectory]."
        exit 1
    fi
    if ! [[ -d $aprgDirectory ]]; then
        echo "$scriptName:$LINENO: Error: The aprg directory [$aprgDirectory] is not a directory."
        exit 1
    fi
    
    echo "$scriptName:$LINENO: The aprg directory is [$aprgDirectory]."
    export aprgDirectory
}
