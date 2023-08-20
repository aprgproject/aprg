#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
userInput="$1"
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

# Get C/C++ projects by git changes or searching on directories.
if [[ -z $userInput ]]; then
    scriptPrint "$scriptName" "$LINENO" "The userInput is empty so getting C/C++ projects from Git changes."
    cppProjectsFromGit=""
    source "$scriptDirectory/DetectGitChanges.sh"
    detectGitChanges
    cppProjects=$cppProjectsFromGit
else
    scriptPrint "$scriptName" "$LINENO" "The userInput is [$userInput], proceeding to search C/C++ projects."
    cppProjectsFound=""
    source "$scriptDirectory/FindCppProjects.sh"
    findCppProjects "$userInput"
    cppProjects=$cppProjectsFound
fi

# Put AprgCommon if empty
if [[ -z $cppProjects ]]; then
    scriptPrint "$scriptName" "$LINENO" "The cppProjects is empty, adding AprgCommon to check that common functionalities are not broken."
    cppProjects='"AprgCommon/AprgCommon"'
fi

# Save C/C++ Projects in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_CPP_DIRECTORIES=[$cppProjects]" >> "$GITHUB_OUTPUT"

# Save Excluded Configurations in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The excludedConfigurations are: [$excludedConfigurations]"
# shellcheck disable=SC2154
echo "APRG_EXCLUDED_CONFIGURATIONS=[$excludedConfigurations]" >> "$GITHUB_OUTPUT"

# Save Excluded Configurations in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The projectsWithBoost are: [$projectsWithBoost]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_BOOST=[$projectsWithBoost]" >> "$GITHUB_OUTPUT"

# Save Excluded Configurations in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The projectsWithGsl are: [$projectsWithGsl]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_GSL=[$projectsWithGsl]" >> "$GITHUB_OUTPUT"

# Save Excluded Configurations in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The projectsWith7Zip are: [$projectsWith7Zip]"
# shellcheck disable=SC2154
echo "APRG_PROJECTS_WITH_7ZIP=[$projectsWith7Zip]" >> "$GITHUB_OUTPUT"
