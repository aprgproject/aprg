#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
aprgDirectoryName="aprg"
declare -A cppProjectsSet

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"
source "$scriptDirectory/AddingAprgLocatorFile.sh"

# Detect git changes
detectedFiles=$(git diff --name-only HEAD^)

scriptPrint "$scriptName" "$LINENO" "$detectedFiles"

# Add only unique directories with CMakeLists.txt to set
while IFS= read -r detectedFile; do
    scriptPrint "$scriptName" "$LINENO" "Detected file: $detectedFile"
    searchingDirectory=$(dirname "$aprgDirectory/$detectedFile")
    while [ "$searchingDirectory" != "/" ] && [ "$searchingDirectory" != "." ]; do
        if [ "$(basename "$searchingDirectory")" == "$aprgDirectoryName" ]; then
            break
        elif [[ -e "$searchingDirectory$aprgLocatorFile" ]]; then
            formattedRelativePath=$(echo "\"$searchingDirectory\"" | sed -E "s|$aprgDirectory/||")
            scriptPrint "$scriptName" "$LINENO" "The formattedRelativePath is: [$formattedRelativePath]"
            cppProjectsSet["$formattedRelativePath"]=1
            break
        else
            searchingDirectory=$(dirname "$searchingDirectory")
        fi
    done
done <<< "$detectedFiles"


# Add directories with CMakeLists.txt for output
cppProjects=""
for cppProjectsSetItem in "${!cppProjectsSet[@]}"; do
    if [[ -z $cppProjects ]]; then
        cppProjects="$cppProjectsSetItem"
    else
        cppProjects="$cppProjects,$cppProjectsSetItem"
    fi
done

# Save the value for Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_DETECTED_CPP_DIRECTORIES=$cppProjects" >> "$GITHUB_OUTPUT"
