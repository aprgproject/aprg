#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles=$1

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
	directoryToConvertAllFiles=$aprgDirectory
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
find "$directoryToConvertAllFiles" -type f -name "*.sh" | while read -r locationPath; do
    dos2unix "$locationPath"
    shellcheck "$locationPath"
done

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."
