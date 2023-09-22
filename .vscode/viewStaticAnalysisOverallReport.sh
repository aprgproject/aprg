#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../")
exitCode=0

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Show all issues found in static analysis reports
while IFS= read -r staticAnalysisReportPath; do
    scriptPrint "$scriptName" "$LINENO" "Processing static report: [$staticAnalysisReportPath]..."
    sed -E "s|.*[/\\]aprg[/\\]| F:/Branches/aprg_project/aprg/aprg/|g" "$staticAnalysisReportPath" | grep "bugprone-narrowing-conversions" | grep -P "^.* (note|style|warning|error): .*$" | grep -v "test_info_" | grep -v "TestFactory" | grep -v "TestBody" | grep -v "benchmark_" | grep -v "testing::" | grep -v "benchmark::" || true
done < <(find "$aprgDirectory" -depth -type f -name "StaticAnalysisReport.txt")

scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

