#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
buildAndRunScriptPath="$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh"
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

# Split the cppProjects into individual items
scriptPrint "$scriptName" "$LINENO" "cppProjects: [$cppProjects]"
IFS=',' read -ra cppProjectDirectories <<< "$cppProjects"

# Loop through the items and call a separate script for each
for cppProjectDirectory in "${cppProjectDirectories[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "cppProjectDirectory in: [$cppProjectDirectory]"
    cppProjectAbsolutePath=$(realpath "$aprgDirectory/$cppProjectDirectory/")
    scriptPrint "$scriptName" "$LINENO" "cppProjectAbsolutePath in: [$cppProjectAbsolutePath]"
    runStaticAnalyzersInDirectory "$cppProjectAbsolutePath"
done

# Save issues into a map, and increment count for each issue
declare -A issueToCountMap
while read -r lineInAnalyzerOutput; do
    issues=$(echo "$lineInAnalyzerOutput" | sed -nE 's|^.*\[(.*)\].*$|\1|p')
    if [[ -n "$issues" ]]; then
        IFS=',' read -ra issues <<< "$issues"
        for issue in "${issues[@]}"; do
            (( issueToCountMap["$issue"]++ ))
        done
    fi
done < "$analyzerOutputFile"

# Sort the counts in descending order and store the keys (issue names) in an array
sortedIssues=()
while IFS= read -r issueAndCount; do
    issue="${issueAndCount%% *}"
    sortedIssues+=("$issue")
done < <(for issue in "${!issueToCountMap[@]}"; do echo "$issue ${issueToCountMap[$issue]}"; done | sort -nr -k2)

# Print the contents of the map with highest counts first
for issue in "${sortedIssues[@]}"; do
    scriptPrint "$scriptName" "$LINENO" "issue: [$issue] | numberOfHits: ${issueToCountMap[$issue]}"
done