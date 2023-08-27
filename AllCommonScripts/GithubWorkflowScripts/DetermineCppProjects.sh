#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
scriptOption="$1"
userInput="$2"
cppProjects=""

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
excludedConfigurations=""
source "$scriptDirectory/ExcludedConfigurations.sh"
projectsWithBoost=""
source "$scriptDirectory/ProjectsWithBoost.sh"
projectsWithGsl=""
source "$scriptDirectory/ProjectsWithGsl.sh"
projectsWith7Zip=""
source "$scriptDirectory/ProjectsWith7Zip.sh"

scriptPrint "$scriptName" "$LINENO" "The scriptOption is: [$scriptOption]"

# Get C/C++ projects by git changes or by user input.
if [[ "$scriptOption" == "checkGit" ]]; then
    scriptPrint "$scriptName" "$LINENO" "Searching C/C++ projects from Git changes..."
    cppProjectsFromGit=""
    source "$scriptDirectory/DetectGitChanges.sh"
    detectGitChanges
    cppProjects="$cppProjects $cppProjectsFromGit"
    scriptPrint "$scriptName" "$LINENO" "The C/C++ projects based from git changes: [$cppProjects]"
elif [[ "$scriptOption" == "checkUserInput" ]]; then
    scriptPrint "$scriptName" "$LINENO" "Searching C/C++ projects based from user input: [$userInput]..."
    cppProjectsFound=""
    source "$scriptDirectory/FindCppProjects.sh"
    findCppProjects "$userInput"
    cppProjects="$cppProjects $cppProjectsFound"
    scriptPrint "$scriptName" "$LINENO" "The C/C++ projects based from user input: [$cppProjects]"
fi

# Put AprgCommon if empty
if [[ -z $cppProjects ]]; then
    scriptPrint "$scriptName" "$LINENO" "The cppProjects is empty, adding AprgCommon to check that common functionalities are not broken."
    cppProjects='"AprgCommon/AprgCommon"'
fi

# Save environment variables in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_CPP_DIRECTORIES=[$cppProjects]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The excludedConfigurations are: [$excludedConfigurations]"
# shellcheck disable=SC2154
echo "APRG_EXCLUDED_CONFIGURATIONS=[$excludedConfigurations]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The projectsWithBoost are: [$projectsWithBoost]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_BOOST=[$projectsWithBoost]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The projectsWithGsl are: [$projectsWithGsl]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_GSL=[$projectsWithGsl]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The projectsWith7Zip are: [$projectsWith7Zip]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_7ZIP=[$projectsWith7Zip]" >> "$GITHUB_OUTPUT"
