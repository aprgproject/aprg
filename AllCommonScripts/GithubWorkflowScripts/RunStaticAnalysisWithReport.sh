#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
staticAnalysisJobIdentifier="$1"
staticAnalysisFilename="$2"
cppProjects="$3"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppItemWithSeverityGrep=""
cppItemAprgOnlyGrep=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonGrepCppOutput.sh"

# Validate input
if [ -z "$staticAnalysisFilename" ]; then
    scriptPrint "$scriptName" "$LINENO" "The static analysis file cannot be empty, staticAnalysisFilename: [$staticAnalysisFilename]"
    exit 1
fi

# Process input remove formatting because of JSON format
#cppProjects=${cppProjects#\[}
#cppProjects=${cppProjects%\]}
cppProjects=$(echo "$cppProjects" | tr -d ' ')
if [ -z "$cppProjects" ]; then
    scriptPrint "$scriptName" "$LINENO" "There are no C/C++ projects to process, cppProjects: [$cppProjects]"
    exit 1
fi

# Create needed functions
runStaticAnalyzersInDirectory() {
    local jobIdentifier
    local directoryPath
    jobIdentifier="$1"
    directoryPath="$2"

    scriptPrint "$scriptName" "$LINENO" "Running Static Analysis in: [$directoryPath]"
    cd "$directoryPath" || exit 1

    echo "StaticAnalysisJobIdentifier: [$jobIdentifier]" > "$staticAnalysisFilename"
    date +%Y-%m-%dT%H:%M:%S >> "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Configuring in cmake..."
    "$buildAndRunScriptPath" cleanAndConfigureWithClangAndStaticAnalyzers "StaticAnalyzersBuild" "Debug" "Ninja"
    scriptPrint "$scriptName" "$LINENO" "Configure step done"
    set +e
    scriptPrint "$scriptName" "$LINENO" "Building..."
    "$buildAndRunScriptPath" build "StaticAnalyzersBuild" "Debug" | grep -E "$cppItemWithSeverityGrep" | grep -Ev "$cppItemAprgOnlyGrep" | tee -a "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Building step done"
    set -e

    echo "DONE!" >> "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Performing [git add] to [$staticAnalysisFilename]"
    git add "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Performing [git diff] to see the local changes (file paths only):"
    git diff --cached --name-only
}

# Loop through the items and call a separate script for each
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$staticAnalysisJobIdentifier" "$cppProjectAbsolutePath"
    # break after one cpp project to make the job exit before github timeout
    break 
done