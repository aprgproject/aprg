#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
allCommonCMakeFilesDirectory=$(realpath "$aprgDirectory/AllCommonCMakeFiles")
inputDirectory="$1"

# Use aprg directory if there are no arguments
if [ -z "$inputDirectory" ]; then
    inputDirectory="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppIndicatorFilePath=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
searchCondition="*$cppIndicatorFilePath"

# Create needed functions
checkCMakeFilesInDirectory() {
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
scriptPrint "$scriptName" "$LINENO" "Searching for common cmake files in [$allCommonCMakeFilesDirectory] ..."
checkCMakeFilesInDirectory "$lintStatus" "$allCommonCMakeFilesDirectory"
lintStatus=$?

# Find all cmake files in aprg directories
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$inputDirectory] ..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$cppIndicatorFilePath||")
    checkCMakeFilesInDirectory "$lintStatus" "$aprgProjectDirectory"
    lintStatus=$?

    aprgCMakeIncludeDirectory=$(realpath "$aprgProjectDirectory/../AprgCMakeToInclude") 
    if [ -d "$aprgCMakeIncludeDirectory" ]; then
        checkCMakeFilesInDirectory "$lintStatus" "$aprgCMakeIncludeDirectory"
        lintStatus=$?
    fi
done < <(find "$inputDirectory" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."

scriptPrint "$scriptName" "$LINENO" "lintStatus: [$lintStatus]"
exit "$lintStatus"


