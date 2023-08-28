#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
generateReportScriptPath="$aprgDirectory/Python/GithubWorkflowScripts/generate_static_analysis_report.py"
analyzerOutputFile="$aprgDirectory/ZZZ_Temp/analyzerIssues.txt"
cppProjects="$1"

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
    "$buildAndRunScriptPath" cleanAndConfigureWithClangAndStaticAnalyzers "StaticAnalyzersBuild" "Debug" "Ninja"
    set +e
    "$buildAndRunScriptPath" build "StaticAnalyzersBuild" "Debug" | grep -P "^.*$directoryPath.* (style|warning|error): .*$" | tee -a "$analyzerOutputFile"
    set -e
}

# Loop through the items and call a separate script for each
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$cppProjectAbsolutePath"
done

scriptPrint "$scriptName" "$LINENO" "Generating report using python script: [$generateReportScriptPath]"
python3 "$generateReportScriptPath"