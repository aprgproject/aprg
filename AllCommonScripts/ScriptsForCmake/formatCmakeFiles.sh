#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles="$1"

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles=$aprgDirectory
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
aprgLocatorFile=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/AddingAprgLocatorFile.sh"
searchCondition="*$aprgLocatorFile"

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
find "$aprgDirectory" -depth -type f -wholename "$searchCondition" | while read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$aprgLocatorFile||")
    aprgProjectDirectory=$(realpath "$aprgProjectDirectory/../") # move one directory up for cmakes
    scriptPrint "$scriptName" "$LINENO" "Searching in aprg project: [$aprgProjectDirectory]"
    find "$aprgProjectDirectory" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \) | while read -r aprgCppFile; do
        # use cmake lint to check
        cmake-lint "$aprgCppFile"
    done
done

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
