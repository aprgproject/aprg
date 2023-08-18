#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
scriptName=$(basename "$(realpath "$0")")
aprgDirectory=$(realpath "$(dirname "$0")/../../")
userInput="$1"
cppProjects=""

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
source "$scriptDirectory/ExcludedConfigurations.sh"

# Get C/C++ projects by git changes or searching on directories.
if [[ -z $userInput ]]; then
    scriptPrint "$scriptName" "$LINENO" "The userInput is empty so getting C/C++ projects from Git changes."
    chmod +x "$scriptDirectory/DetectGitChanges.sh"
    "$scriptDirectory/DetectGitChanges.sh"
    read -r cppProjects < "$aprgDirectory/ZZZ_Temp/cppProjectsFromGit.txt"
else
    scriptPrint "$scriptName" "$LINENO" "The userInput is [$userInput], proceeding to search C/C++ projects."
    chmod +x "$scriptDirectory/FindCppProjects.sh"
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
# shellcheck disable=SC2154
echo "APRG_EXCLUDED_CONFIGURATIONS=[$excludedConfigurations]" >> "$GITHUB_OUTPUT"
