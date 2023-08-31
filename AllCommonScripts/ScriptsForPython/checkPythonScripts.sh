#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
inputDirectory="$1"

# Use aprgDirectory/Python directory if there are no arguments
if [ -z "$inputDirectory" ]; then
    inputDirectory="$aprgDirectory/Python"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
pythonIncludePathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
pathRegex="$pythonIncludePathRegex"

# Create needed functions
checkPythonScriptsInDirectory() {
    local localLintStatus
    local directoryPath
    localLintStatus="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Searching for python scripts in: [$directoryPath]"

    while IFS= read -r filePath; do
        if  [[ "$filePath" =~ $pathRegex ]]; then
            scriptPrint "$scriptName" "$LINENO" "Processing python file: [$filePath]"
            
            flake8 "--config" "$aprgDirectory/.flake8" "$filePath" | sed -E "s@\/mnt\/(\w+)\/@ \U\1:/@g"
            currentStatus=$?
            if [ "$currentStatus" -gt "$localLintStatus" ]; then
                localLintStatus=$currentStatus
            fi
            
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
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$inputDirectory]..."
checkPythonScriptsInDirectory "$lintStatus" "$inputDirectory"
lintStatus=$?

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."

scriptPrint "$scriptName" "$LINENO" "lintStatus: [$lintStatus]"
exit "$lintStatus"