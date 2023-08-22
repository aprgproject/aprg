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
    directoryToConvertAllFiles=$aprgDirectory
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
aprgLocatorFile=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/AddingAprgLocatorFile.sh"
searchCondition="*$aprgLocatorFile"

tempFile=$(mktemp)
formatCmakeFile() {
    local cmakeFile
    cmakeFile="$1"
    
    # unix style line endings
    dos2unix "$cmakeFile"

    # convert tabs to 4 spaces
    expand -t 4 "$cmakeFile" > "$tempFile"
    mv "$tempFile" "$cmakeFile"

    # use cmake format as final format
    cmake-format -i "$cmakeFile"
}

checkCmakeFile() {
    local cmakeFile
    cmakeFile="$1"

    # use cmake lint to check
    cmake-lint --suppress-decorations "$cmakeFile"
}

# Find all common cmake files
scriptPrint "$scriptName" "$LINENO" "Searching for common cmake files in [$aprgCommonCmakeDirectory] ..."
find "$aprgCommonCmakeDirectory" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \) | while read -r aprgCmakeFile; do
    checkCmakeFile "$aprgCmakeFile"
done

# Find all cmake files in aprg directories
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles] ..."
find "$aprgDirectory" -depth -type f -wholename "$searchCondition" | while read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$aprgLocatorFile||")
    scriptPrint "$scriptName" "$LINENO" "Searching in aprg project: [$aprgProjectDirectory]"
    find "$aprgProjectDirectory" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \) | while read -r aprgCmakeFile; do
        checkCmakeFile "$aprgCmakeFile"
    done
    aprgCmakeIncludeDirectory=$(realpath "$aprgProjectDirectory/../AprgCmakeInclude") 
    if [ -d "$aprgCmakeIncludeDirectory" ]; then
        scriptPrint "$scriptName" "$LINENO" "Searching in AprgCmakeInclude directory: [$aprgCmakeIncludeDirectory]"
        find "$aprgCmakeIncludeDirectory" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \) | while read -r aprgCmakeFile; do
            checkCmakeFile "$aprgCmakeFile"
        done
    fi
done

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
