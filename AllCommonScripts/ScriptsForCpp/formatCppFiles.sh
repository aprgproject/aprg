#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles="$1"

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppIndicatorFilePath=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
searchCondition="*$cppIndicatorFilePath"

# Create needed functions
tempFile=$(mktemp)
formatCppFilesInDirectory() {
    local directoryPath
    directoryPath="$1"

    scriptPrint "$scriptName" "$LINENO" "Searching for C/C++ files in: [$directoryPath]"

    while IFS= read -r filePath; do
        # unix style line endings
        dos2unix "$filePath"

        # convert tabs to 4 spaces
        expand -t 4 "$filePath" > "$tempFile"
        mv "$tempFile" "$filePath"

        # use cmake format as final format
        clang-format -style=file -i "$filePath"
    done < <(find "$directoryPath" -depth -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -o -name "*.h" \))
}

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$cppIndicatorFilePath||")
    scriptPrint "$scriptName" "$LINENO" "Searching in aprg project: [$aprgProjectDirectory]"
    formatCppFilesInDirectory "$aprgProjectDirectory"
done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
