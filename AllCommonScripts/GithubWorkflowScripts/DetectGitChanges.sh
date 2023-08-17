#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
scriptName=$(basename "$(realpath "$0")")
aprgDirectory=$(realpath "$(dirname "$0")/../../")
aprgDirectoryName="aprg"
declare -A cppProjectsSet

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
source "$scriptDirectory/AddingAprgLocatorFile.sh"

# Detect git changes
detectedFiles=$(git diff --name-only HEAD^)

# Add only unique directories with CMakeLists.txt to set
while IFS= read -r detectedFile; do
    scriptPrint "$scriptName" "$LINENO" "Detected file: $detectedFile"
    searchingDirectory=$(dirname "$aprgDirectory/$detectedFile")
    while [ "$searchingDirectory" != "/" ] && [ "$searchingDirectory" != "." ]; do
        if [ "$(basename "$searchingDirectory")" == "$aprgDirectoryName" ]; then
            break
        elif [[ -e "$searchingDirectory$aprgLocatorFile" ]]; then
            cppProject=$(echo "\"$searchingDirectory\"" | sed -E "s|$aprgDirectory/||")
            scriptPrint "$scriptName" "$LINENO" "The cppProject is: [$cppProject]"
            cppProjectsSet["$cppProject"]=1
            break
        else
            searchingDirectory=$(dirname "$searchingDirectory")
        fi
    done
done <<< "$detectedFiles"


# Add directories with CMakeLists.txt for output
cppProjectsFromGit=""
for cppProjectsSetItem in "${!cppProjectsSet[@]}"; do
    if [[ -z $cppProjectsFromGit ]]; then
        cppProjectsFromGit="$cppProjectsSetItem"
    else
        cppProjectsFromGit="$cppProjectsFromGit,$cppProjectsSetItem"
    fi
done

# Save the value for Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjectsFromGit are: [$cppProjectsFromGit]"
echo "$cppProjectsFromGit" > "$aprgDirectory/ZZZ_Temp/cppProjectsFromGit.txt"

