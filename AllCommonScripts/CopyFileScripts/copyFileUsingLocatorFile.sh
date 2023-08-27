#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
includePathRegex=$(basename "$1")
skipPathRegex=$(basename "$2")
locatorFilename=$(basename "$3")
if [ -z "$4" ]; then
    # If there are no second argument use the first argument
    fileToCopy=$(realpath "$(pwd)/$3")
else
    fileToCopy=$(realpath "$(pwd)/$4")
fi
if [ "$5" == "DeleteOriginalLocatorFiles" ]; then
    deleteOption="DeleteOriginalLocatorFiles"
else
    deleteOption=""
fi
shortenedPathLengthForDisplay=50

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate input
if [ -z "$locatorFilename" ]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The locatorFilename cannot be empty."
    exit 1
fi
if ! [[ -e $fileToCopy ]]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The file [$fileToCopy] does not exist."
    exit 1
fi

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$aprgDirectory] with the filename [$locatorFilename]..."
fileToCopyDisplay=$(echo "$fileToCopy" | tail -c "$shortenedPathLengthForDisplay")
scriptPrint "$scriptName" "$LINENO" "Copying [...$fileToCopyDisplay] ->"
find "$aprgDirectory" -type f -name "$locatorFilename" | while read -r locatorFilePath; do
    # Check if it can be skipped
    if  [[ "$locatorFilePath" =~ $includePathRegex && ! "$locatorFilePath" =~ $skipPathRegex ]]; then
        locatorDirectory=$(dirname "$locatorFilePath")
        directoryToDisplay=$(echo "$locatorDirectory" | tail -c "$shortenedPathLengthForDisplay")
        scriptPrint "$scriptName" "$LINENO" "-> to [...$directoryToDisplay]."
        if [ "$deleteOption" == "DeleteOriginalLocatorFiles" ]; then
            rm -f "$locatorFilePath"
        fi
        cp -f "$fileToCopy" "$locatorDirectory"
    fi
done

scriptPrint "$scriptName" "$LINENO" "File replacements completed."
