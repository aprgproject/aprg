#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
replaceDirectory=$(realpath "$1")
targetString="$2"
replacementString="$3"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate input
if ! [[ -d $replaceDirectory ]]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The directory [$replaceDirectory] does not exist."
    exit 1
fi
if [ -z "$targetString" ]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The targetString cannot be empty, targetString: [$targetString]."
    exit 1
fi

scriptPrint "$scriptName" "$LINENO" "Changing directory..."
cd "$replaceDirectory" || true
scriptPrint "$scriptName" "$LINENO" "Current directory before replacing: [$(pwd)]"

scriptPrint "$scriptName" "$LINENO" "Replacing text with [$targetString] to [$replacementString] in [$replaceDirectory]."

# Rename directories
scriptPrint "$scriptName" "$LINENO" "Renaming directories, targetString in [*$targetString*]."
find . -depth -type d -name "*$targetString*" -execdir sh -c 'newname=$(echo "$1" | sed "s/$2/$3/g"); mv "$1" "$newname"' sh {} "$targetString" "$replacementString" \;

# Rename filenames
scriptPrint "$scriptName" "$LINENO" "Renaming filenames, targetString in [*$targetString*]."
find . -depth -type f -name "*$targetString*" -execdir rename "s/$targetString/$replacementString/g" {} \;

# Replace contents
scriptPrint "$scriptName" "$LINENO" "Replacing contents, targetString in [$targetString]."
find . -type f -exec sed -i "s/$targetString/$replacementString/g" {} +

scriptPrint "$scriptName" "$LINENO" "Replacements for contents completed."
