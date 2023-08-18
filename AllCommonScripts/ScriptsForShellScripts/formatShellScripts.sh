#!/bin/bash

# Set variable values
scriptName=$(basename "$(realpath "$0")")
aprgDirectory=$(realpath "$(dirname "$0")/../../")
directoryToConvertAllFiles="$1"
aprgShellScriptsPathSkipRegex=""

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles=$aprgDirectory
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
skipPathRegex="$aprgShellScriptsPathSkipRegex"

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
tempFile=$(mktemp)
find "$directoryToConvertAllFiles" -type f -name "*.sh" | while read -r locationPath; do
    if  [[ ! "$locationPath" =~ $skipPathRegex ]]; then
        dos2unix "$locationPath"
        expand -t 4 "$locationPath" > "$tempFile"
        mv "$tempFile" "$locationPath"
    fi
done

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."