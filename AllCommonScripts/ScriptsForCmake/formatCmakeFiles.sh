#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
aprgCommonCmakeDirectory=$(realpath "$aprgDirectory/AprgCMakeHelpers")
directoryToConvertAllFiles="$1"

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
aprgLocatorFile=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/AddingAprgLocatorFile.sh"
searchCondition="*$aprgLocatorFile"

# Create needed functions
tempFile=$(mktemp)
formatCmakeFilesInDirectory() {
    local directoryPath
    directoryPath="$1"

    scriptPrint "$scriptName" "$LINENO" "Searching for cmake files in: [$directoryPath]"

    while IFS= read -r filePath; do
        # unix style line endings
        dos2unix "$filePath"

        # convert tabs to 4 spaces
        expand -t 4 "$filePath" > "$tempFile"
        mv "$tempFile" "$filePath"

        # use cmake format as final format
        cmake-format -i "$filePath"
    done < <(find "$directoryPath" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \))
}

# Find all common cmake files
formatCmakeFilesInDirectory "$aprgCommonCmakeDirectory"

# Find all cmake files in aprg directories
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles] ..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$aprgLocatorFile||")
    scriptPrint "$scriptName" "$LINENO" "Searching in aprg project: [$aprgProjectDirectory]"
    formatCmakeFilesInDirectory "$aprgProjectDirectory"
    aprgCmakeIncludeDirectory=$(realpath "$aprgProjectDirectory/../AprgCmakeInclude") 
    if [ -d "$aprgCmakeIncludeDirectory" ]; then
        scriptPrint "$scriptName" "$LINENO" "Searching in AprgCmakeInclude directory: [$aprgCmakeIncludeDirectory]"
        formatCmakeFilesInDirectory "$aprgCmakeIncludeDirectory"
    fi
done < <(find "$directoryToConvertAllFiles" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
