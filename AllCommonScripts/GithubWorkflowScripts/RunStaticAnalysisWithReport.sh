#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
cppProjects="$1"
staticAnalysisFilename="$2"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate input
if [ -z "$staticAnalysisFilename" ]; then
    scriptPrint "$scriptName" "$LINENO" "The static analysis file cannot be empty, staticAnalysisFilename: [$staticAnalysisFilename]"
    exit 1
fi

# Process input remove formatting because of JSON format
cppProjects=${cppProjects#\[}
cppProjects=${cppProjects%\]}
cppProjects=$(echo "$cppProjects" | tr -d ' ')
if [ -z "$cppProjects" ]; then
    scriptPrint "$scriptName" "$LINENO" "There are no C/C++ projects to process, cppProjects: [$cppProjects]"
    exit 1
fi

# Create needed functions
runStaticAnalyzersInDirectory() {
    local directoryPath
    directoryPath="$1"

    scriptPrint "$scriptName" "$LINENO" "Running Static Analysis in: [$directoryPath]"
    cd "$directoryPath" || exit 1

    date +%Y-%m-%dT%H:%M:%S > "$staticAnalysisFilename"
    "$buildAndRunScriptPath" cleanAndConfigureWithClangAndStaticAnalyzers "StaticAnalyzersBuild" "Debug" "Ninja"
    set +e
    "$buildAndRunScriptPath" build "StaticAnalyzersBuild" "Debug" | grep -P "^.*$directoryPath.* (style|warning|error): .*$" | tee -a "$staticAnalysisFilename"
    set -e

    echo "DONE!" >> "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Performing [git add] to [$staticAnalysisFilename]"
    git add "$staticAnalysisFilename"
    scriptPrint "$scriptName" "$LINENO" "Performing [git diff] to see the local changes (just showing the first 10 lines):"
    git diff --cached | head -n 10
}

# Loop through the items and call a separate script for each
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$cppProjectAbsolutePath"
    break
done