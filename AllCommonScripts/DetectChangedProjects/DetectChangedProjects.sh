#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
aprgDirectoryName="aprg"
declare -A cmakelistDirectoriesSet

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Detect git changes
detectedFiles=$(git diff --name-only HEAD^)

# Add only unique directories with CMakeLists.txt to set
while IFS= read -r detectedFile; do
    scriptPrint "$scriptName" "$LINENO" "Detected file: $detectedFile"
    searchingDirectory=$(dirname "$aprgDirectory/$detectedFile")
    while [ "$searchingDirectory" != "/" ] && [ "$searchingDirectory" != "." ]; do
        if [ "$(basename "$searchingDirectory")" == "$aprgDirectoryName" ]; then
            break
        elif [[ -e "$searchingDirectory/CMakeLists.txt" ]]; then
            formattedRelativePath=$(echo "\"$searchingDirectory\"" | sed -E "s|$aprgDirectory/||")
            scriptPrint "$scriptName" "$LINENO" "The formattedRelativePath is: [$formattedRelativePath]"
            cmakelistDirectoriesSet["$formattedRelativePath"]=1
            break
        else
            searchingDirectory=$(dirname "$searchingDirectory")
        fi
    done
done <<< "$detectedFiles"


# Add directories with CMakeLists.txt for output
cmakelistDirectories=""
for cmakelistDirectoriesSetItem in "${!cmakelistDirectoriesSet[@]}"; do
    if [[ -z $cmakelistDirectories ]]; then
        cmakelistDirectories="$cmakelistDirectoriesSetItem"
    else
        cmakelistDirectories="$cmakelistDirectories,$cmakelistDirectoriesSetItem"
    fi
done

# Put AprgCommon if empty
if [[ -z $cmakelistDirectories ]]; then
	cmakelistDirectories="\"AprgCommon/AprgCommon\""
fi

# Save the value for Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cmakelistDirectories are: [$cmakelistDirectories]"
echo "APRG_CMAKELIST_DIRECTORIES=[$cmakelistDirectories]" >> "$GITHUB_OUTPUT"
