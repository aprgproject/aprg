#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
aprgCommonCmakeDirectory=$(realpath "$aprgDirectory/AllCommonCMakeFiles")
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
checkCmakeFilesInDirectory() {
    local localLintStatus
    local directoryPath
    localLintStatus="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Searching for cmake files in: [$directoryPath]"

    while IFS= read -r filePath; do
        cmake-lint --suppress-decorations "$filePath"
        currentStatus=$?
        if [ "$currentStatus" -gt "$localLintStatus" ]; then
            localLintStatus=$currentStatus
        fi
    done < <(find "$directoryPath" -depth -type f \( -name "CMakeLists.txt" -o -name "*.cmake" \))

    return "$localLintStatus"
}

# Start linting
lintStatus=0

# Find all common cmake files
scriptPrint "$scriptName" "$LINENO" "Searching for common cmake files in [$aprgCommonCmakeDirectory] ..."
checkCmakeFilesInDirectory "$lintStatus" "$aprgCommonCmakeDirectory"
lintStatus=$?

# Find all cmake files in aprg directories
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles] ..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$aprgLocatorFile||")
    checkCmakeFilesInDirectory "$lintStatus" "$aprgProjectDirectory"
    lintStatus=$?

    aprgCmakeIncludeDirectory=$(realpath "$aprgProjectDirectory/../AprgCmakeInclude") 
    if [ -d "$aprgCmakeIncludeDirectory" ]; then
        checkCmakeFilesInDirectory "$lintStatus" "$aprgCmakeIncludeDirectory"
        lintStatus=$?
    fi
done < <(find "$directoryToConvertAllFiles" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."

scriptPrint "$scriptName" "$LINENO" "lintStatus: [$lintStatus]"
exit "$lintStatus"


