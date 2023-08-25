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
aprgShellScriptsPathSkipRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
skipPathRegex="$aprgShellScriptsPathSkipRegex"

# Create needed functions
tempFile=$(mktemp)
formatShellScriptsInDirectory() {
    local localLintStatus
    local directoryPath
    localLintStatus="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Searching for shell scripts in: [$directoryPath]"

    while IFS= read -r filePath; do
        if  [[ ! "$filePath" =~ $skipPathRegex ]]; then
            scriptPrint "$scriptName" "$LINENO" "Processing shell script: [$filePath]"
            
            # unix style line endings
            dos2unix "$filePath"
        
            # convert tabs to 4 spaces
            expand -t 4 "$filePath" > "$tempFile"
            mv "$tempFile" "$filePath"
        fi
    done < <(find "$directoryPath" -type f -name "*.sh")

    return "$localLintStatus"
}

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
formatShellScriptsInDirectory "$directoryToConvertAllFiles"

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."
