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
    sed -E "s|/home/runner/work/aprg/|F:/Branches/aprg_project/aprg/|g" "$staticAnalysisReportPath" | grep "clang-diagnostic-sign-compare" || true
done < <(find "$aprgDirectory" -depth -type f -name "StaticAnalysisReport.txt")

scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

