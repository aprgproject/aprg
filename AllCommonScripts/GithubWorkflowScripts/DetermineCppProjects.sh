#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
userInput="$1"
cppProjectsFromGit="$2"
cppProjects=""

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"
source "$scriptDirectory/AddingAprgLocatorFile.sh"

# Put AprgCommon if empty
if [[ -z $userInput ]]; then
    scriptPrint "$scriptName" "$LINENO" "The userInput is empty getting C/C++ projects from Git changes."
    cppProjects="$cppProjectsFromGit"
else
    searchCondition=""
    scriptPrint "$scriptName" "$LINENO" "The userInput is [$userInput]."
    if [ "$userInput" == "all" ]; then
        searchCondition="*$aprgLocatorFile"
    else
        searchCondition="*$userInput*$aprgLocatorFile"
    fi
    scriptPrint "$scriptName" "$LINENO" "Searching directories for C/C++ projects using searchCondition: [$searchCondition]"
    cppProjects=$(find "$aprgDirectory" -depth -type f -wholename "$searchCondition" -exec sh -c 'echo "$1" | sed -E "s|^.*$2/(.*)$3.*$|\"\1\"|"' sh {} "$aprgDirectory" "$aprgLocatorFile" \;  | xargs -0 -n1 | paste -sd "," -)
fi

# Put AprgCommon if empty
if [[ -z $cppProjects ]]; then
    scriptPrint "$scriptName" "$LINENO" "The cppProjects is empty, adding AprgCommon to check that common functionalities are not broken."
    cppProjects="\"AprgCommon/AprgCommon\""
fi

# Save the value for Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_INPUT_CPP_DIRECTORIES=[$cppProjects]" >> "$GITHUB_OUTPUT"
