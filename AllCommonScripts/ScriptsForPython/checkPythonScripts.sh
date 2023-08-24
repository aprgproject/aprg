#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles="$1"

# Use aprgDirectory/Python directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles="$aprgDirectory/Python"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
pythonProjectsPathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
pathRegex="$pythonProjectsPathRegex"

# Create needed functions
checkPythonScriptsInDirectory() {
    local localLintStatus
    local directoryPath
    localLintStatus="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Searching for python scripts in: [$directoryPath]"

    while IFS= read -r filePath; do
        if  [[ "$filePath" =~ $pathRegex ]]; then
            pylint "--rcfile=$aprgDirectory/.pylintrc" "$filePath"
            currentStatus=$?
            if [ "$currentStatus" -gt "$localLintStatus" ]; then
                localLintStatus=$currentStatus
            fi
        fi
    done < <(find "$directoryPath" -type f -name "*.py")

    return "$localLintStatus"
}

# Start linting
lintStatus=0

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
checkPythonScriptsInDirectory "$lintStatus" "$directoryToConvertAllFiles"
lintStatus=$?

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."

scriptPrint "$scriptName" "$LINENO" "lintStatus: [$lintStatus]"
exit "$lintStatus"