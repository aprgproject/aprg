#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../")
exitCode=0

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppItemWithSeverityGrep=""
cppItemAprgOnlyGrep=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonGrepCppOutput.sh"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# set issue to filter
issueToFilter="useStlAlgorithm"

# Show all issues found in static analysis reports
while IFS= read -r staticAnalysisReportPath; do
    scriptPrint "$scriptName" "$LINENO" "Processing static report: [$staticAnalysisReportPath]..."
    sed -E "s|.*[/\\]aprg[/\\]| F:/Branches/aprg_project/aprg/aprg/|g" "$staticAnalysisReportPath" | grep "$issueToFilter"  | grep -E "$cppItemWithSeverityGrep" | grep -Ev "$cppItemAprgOnlyGrep" || true
done < <(find "$aprgDirectory" -depth -type f -name "StaticAnalysisReport.txt")

scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

