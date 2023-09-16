#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
scriptOption="$1"
firstArgument="$2"
secondArgument="$3"
cppProjects=""

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
excludedConfigurations=""
projectsThatAreWindowsOnly=""
projectsThatAreLinuxOnly=""
source "$scriptDirectory/ProjectsThatAreOsDependent.sh"
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
    source "$scriptDirectory/FindCppProjectsFromGitChanges.sh"
    detectGitChanges
    cppProjects="$cppProjectsFromGit"
    scriptPrint "$scriptName" "$LINENO" "The C/C++ projects based from git changes: [$cppProjects]"
elif [[ "$scriptOption" == "checkUserInputWithSingleOutput" || "$scriptOption" == "checkUserInputWithMultipleOutput" ]]; then
    userInput="$firstArgument"
    scriptPrint "$scriptName" "$LINENO" "Searching C/C++ projects based from user input: [$userInput]..."
    cppProjectsFound=""
    source "$scriptDirectory/FindCppProjectsFromUserInput.sh"
    findCppProjects "$scriptOption" "$userInput"
    cppProjects="$cppProjectsFound"
    scriptPrint "$scriptName" "$LINENO" "The C/C++ projects based from user input: [$cppProjects]"
elif [[ "$scriptOption" == "checkStaticAnalysisFiles" ]]; then
    staticAnalysisJobIdentifier="$firstArgument"
    staticAnalysisFilename="$secondArgument"
    scriptPrint "$scriptName" "$LINENO" "Searching C/C++ projects..."
    scriptPrint "$scriptName" "$LINENO" "The job identifier of the run is [$staticAnalysisJobIdentifier]"
    scriptPrint "$scriptName" "$LINENO" "The results will be placed on [$staticAnalysisFilename]"
    cppProjectsFound=""
    source "$scriptDirectory/FindCppProjectsForStaticAnalysis.sh"
    findCppProjectsForStaticAnalysis "$staticAnalysisJobIdentifier" "$staticAnalysisFilename"
    cppProjects="$cppProjectsFound"
    scriptPrint "$scriptName" "$LINENO" "The C/C++ projects based from static analysis: [$cppProjects]"
else
    scriptPrint "$scriptName" "$LINENO" "The script option [$scriptOption] is not found."
    exit 1
fi

# Save environment variables in Github Workflow
scriptPrint "$scriptName" "$LINENO" "The cppProjects are: [$cppProjects]"
# shellcheck disable=SC2154
echo "APRG_CPP_DIRECTORIES=[$cppProjects]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The projectsThatAreWindowsOnly are: [$projectsThatAreWindowsOnly]"
# shellcheck disable=SC2154
echo "APRG_WINDOWS_ONLY_PROJECTS=[$projectsThatAreWindowsOnly]" >> "$GITHUB_OUTPUT"

scriptPrint "$scriptName" "$LINENO" "The projectsThatAreLinuxOnly are: [$projectsThatAreLinuxOnly]"
# shellcheck disable=SC2154
echo "APRG_LINUX_ONLY_PROJECTS=[$projectsThatAreLinuxOnly]" >> "$GITHUB_OUTPUT"

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
