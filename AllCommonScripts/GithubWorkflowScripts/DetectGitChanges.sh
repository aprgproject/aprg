#!/bin/bash

detectGitChanges() {
    # Set variable values
    local scriptName
    local aprgDirectory
    local aprgDirectoryName
    local cppProjectsSet
    scriptName="DetectGitChanges.sh"
    aprgDirectory=$(realpath "$(dirname "$0")/../../")
    aprgDirectoryName="aprg"
    declare -A cppProjectsSet
    
    # Source needed scripts
    source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
    cppIndicatorFilePath=""
    source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
    
    # Detect git changes
    scriptPrint "$scriptName" "$LINENO" "Calling Git Diff command ..."
    detectedFiles=$(git diff --name-only HEAD^)
    scriptPrint "$scriptName" "$LINENO" "The Git Diff command is finished."
    
    # Add only unique directories with CMakeLists.txt to set
    while IFS= read -r detectedFile; do
        scriptPrint "$scriptName" "$LINENO" "Detected file: $detectedFile"
        searchingDirectory=$(dirname "$aprgDirectory/$detectedFile")
        while [ "$searchingDirectory" != "/" ] && [ "$searchingDirectory" != "." ]; do
            if [ "$(basename "$searchingDirectory")" == "$aprgDirectoryName" ]; then
                break
            elif [[ -e "$searchingDirectory$cppIndicatorFilePath" ]]; then
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
        cppProjectsFromGit="$cppProjectsFromGit$cppProjectsSetItem,"
    done
    
    # Save the value for Github Workflow
    scriptPrint "$scriptName" "$LINENO" "The cppProjectsFromGit are: [$cppProjectsFromGit]"
    export cppProjectsFromGit
}
