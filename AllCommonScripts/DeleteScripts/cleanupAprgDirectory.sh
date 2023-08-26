#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
deleteDirectory="$1"

deleteAllDirectoriesWithName() {
    local nameForDeletion
    nameForDeletion="$1"
    find "$deleteDirectory" -type d -name "$nameForDeletion" -delete
}

deleteAllFilesWithName() {
    local nameForDeletion
    nameForDeletion="$1"
    find "$deleteDirectory" -type f -name "$nameForDeletion" -delete
}

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate input
if [ -z "$deleteDirectory" ]; then
    deleteDirectory="$aprgDirectory"
else
    deleteDirectory=$(realpath "$deleteDirectory")
fi
if ! [[ -d $deleteDirectory ]]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The directory [$deleteDirectory] does not exist."
    exit 1
fi

deleteAllDirectoriesWithName "WindowsMsvcBuild"
deleteAllDirectoriesWithName "WindowsMinGWBuild"
deleteAllDirectoriesWithName "WindowsClangBuild"
deleteAllDirectoriesWithName "WslBuild"
deleteAllDirectoriesWithName "build-*"
deleteAllDirectoriesWithName ".vs"
deleteAllFilesWithName "CMakeLists.txt.user"
deleteAllFilesWithName "*.gch"

scriptPrint "$scriptName" "$LINENO" "Cleanup completed."
