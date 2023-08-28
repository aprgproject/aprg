#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
cppProjects="$1"
staticAnalysisFilename="$2"

scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"

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
    "$buildAndRunScriptPath" cleanAndConfigureWithStaticAnalyzersWithAutoFix "StaticAnalyzersBuild" "Debug" "Ninja"
    set +e
    # "note" is added in the grep to cover "FIX-IT"
    timeout 1 "$buildAndRunScriptPath" buildOnOneCore "StaticAnalyzersBuild" "Debug" | grep -P "^.*$directoryPath.* (note|style|warning|error): .*$" | tee -a "$staticAnalysisFilename"
    set -e
    
    "DONE!" >> "$staticAnalysisFilename"
    git add "$staticAnalysisFilename"
}

# Split the cppProjects into individual items
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"

# Loop through the items and call a separate script for each
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$cppProjectAbsolutePath"
    break
done
