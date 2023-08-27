#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
cppProjects="$1"

scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

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
    "$buildAndRunScriptPath" cleanAndConfigureWithStaticAnalyzersWithAutoFix "StaticAnalyzersBuild" "Debug" "Ninja"
    "$buildAndRunScriptPath" build "StaticAnalyzersBuild" "Debug"
}


# Split the cppProjects into individual items
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
chmod +x "$buildAndRunScriptPath"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"

# Loop through the items and call a separate script for each
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$cppProjectAbsolutePath"
done
