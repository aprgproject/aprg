#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
locatorFile=$(basename "$1")
if [ -z "$2" ]; then
	# If there are no second argument use the first argument
	fileToCopy=$(realpath "$(pwd)/$1")
else
	fileToCopy=$(realpath "$(pwd)/$2")
fi
if [ "$3" == "DeleteOriginalLocatorFiles" ]; then
	deleteOption="DeleteOriginalLocatorFiles"
else
	deleteOption=""
fi
skipRegexPattern="\/aprg\/Python\/|\/aprg\/AllCommonScripts\/"
shortenedPathLengthForDisplay=50

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Validate input
if [ -z "$locatorFile" ]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The filename cannot be empty."
	exit 1
fi
if ! [[ -e $fileToCopy ]]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The file [$fileToCopy] does not exist."
	exit 1
fi

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$aprgDirectory] with the filename [$locatorFile]..."
fileToCopyDisplay=$(echo "$fileToCopy" | tail -c "$shortenedPathLengthForDisplay")
scriptPrint "$scriptName" "$LINENO" "Copying [...$fileToCopyDisplay] ->"
find "$aprgDirectory" -type f -name "$locatorFile" | while read -r locationPath; do
    # Check if it can be skipped
	if  [[ ! "$locationPath" =~ $skipRegexPattern ]]; then
		locationDirectory=$(dirname "$locationPath")
		locationDirectoryDisplay=$(echo "$locationDirectory" | tail -c "$shortenedPathLengthForDisplay")
        scriptPrint "$scriptName" "$LINENO" "-> to [...$locationDirectoryDisplay]."
        if [ "$deleteOption" == "DeleteOriginalLocatorFiles" ]; then
            rm -f "$locationPath"
        fi
        cp -f "$fileToCopy" "$locationDirectory"
	fi
done

scriptPrint "$scriptName" "$LINENO" "File replacements completed."
