#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
inputDirectory="$1"

# Use aprg directory if there are no arguments
if [ -z "$inputDirectory" ]; then
    inputDirectory="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
shellScriptsSkipPathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
skipPathRegex="$shellScriptsSkipPathRegex"

# Create needed functions
checkShellScriptsInDirectory() {
    local localLintStatus
    local directoryPath
    localLintStatus="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Searching for shell scripts in: [$directoryPath]"

    while IFS= read -r filePath; do
        if  [[ ! "$filePath" =~ $skipPathRegex ]]; then
            scriptPrint "$scriptName" "$LINENO" "Processing shell script: [$filePath]"

            shellcheck --severity=error --format tty "$filePath"
            currentStatus=$?
            if [ "$currentStatus" -gt "$localLintStatus" ]; then
                localLintStatus=$currentStatus
            fi
        fi
    done < <(find "$directoryPath" -type f -name "*.sh")

    return "$localLintStatus"
}

# Start linting
lintStatus=0

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$inputDirectory]..."
checkShellScriptsInDirectory "$lintStatus" "$inputDirectory"
lintStatus=$?

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."

scriptPrint "$scriptName" "$LINENO" "lintStatus: [$lintStatus]"
exit "$lintStatus"
