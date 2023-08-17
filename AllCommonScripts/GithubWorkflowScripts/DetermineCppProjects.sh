#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
scriptName=$(basename "$(realpath "$0")")
aprgDirectory=$(realpath "$(dirname "$0")/../../")
#userInput="$1"
userInput="all"
cppProjects=""

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Get C/C++ projects by git changes or searching on directories.
if [[ -z $userInput ]]; then
    scriptPrint "$scriptName" "$LINENO" "The userInput is empty getting C/C++ projects from Git changes."
    "$scriptDirectory/DetectGitChanges.sh"
    read -r cppProjects < "$aprgDirectory/ZZZ_Temp/cppProjectsFromGit.txt"
else
    scriptPrint "$scriptName" "$LINENO" "The userInput is [$userInput], proceeding to search C/C++ projects."
    "$scriptDirectory/FindCppProjects.sh" "$userInput"
    read -r cppProjects < "$aprgDirectory/ZZZ_Temp/cppProjectsFound.txt"
fi

# Put AprgCommon if empty
if [[ -z $cppProjects ]]; then
    scriptPrint "$scriptName" "$LINENO" "The cppProjects is empty, adding AprgCommon to check that common functionalities are not broken."
    cppProjects="\"AprgCommon/AprgCommon\""
fi

# Save the value for Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_CPP_DIRECTORIES=[$cppProjects]" >> "$GITHUB_OUTPUT"
