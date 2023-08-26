#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles="$1"
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppIndicatorFilePath=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
searchCondition="*$cppIndicatorFilePath"

# Create needed functions
runStaticAnalyzersInDirectory() {
    local directoryPath
    directoryPath="$1"

    scriptPrint "$scriptName" "$LINENO" "Searching for C/C++ files in: [$directoryPath]"

    cd "$directoryPath" || exit 1
    "$buildAndRunScriptPath" cleanAndConfigureWithStaticAnalyzersWithAutoFix "StaticAnalyzersBuild" "Debug" "Ninja"
    "$buildAndRunScriptPath" build "StaticAnalyzersBuild" "Debug"
}

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$cppIndicatorFilePath||")
    scriptPrint "$scriptName" "$LINENO" "Searching in aprg project: [$aprgProjectDirectory]"
    runStaticAnalyzersInDirectory "$aprgProjectDirectory"
done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
