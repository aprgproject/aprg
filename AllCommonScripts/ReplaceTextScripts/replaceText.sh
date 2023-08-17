#!/bin/bash

# Set variable values
scriptName=$(basename "$(realpath "$0")")
aprgDirectory=$(realpath "$(dirname "$0")/../../")
replaceDirectory=$(realpath "$1")
targetString=$2
replacementString=$3

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

scriptPrint "$scriptName" "$LINENO" "Replacing text with [$targetString] to [$replacementString] in [$replaceDirectory]."

# Rename directories
find . -depth -type d -name "*$targetString*" -execdir bash -c 'newname=$(echo "$1" | sed "s/$2/$3/g"); mv "$1" "$newname"' bash {} "$targetString" "$replacementString" \;

# Rename filenames
find . -depth -type f -name "*$targetString*" -execdir rename "s/$targetString/$replacementString/g" {} \;

# Replace contents
find . -type f -exec sed -i "s/$targetString/$replacementString/g" {} +

scriptPrint "$scriptName" "$LINENO" "Replacements for contents completed."
