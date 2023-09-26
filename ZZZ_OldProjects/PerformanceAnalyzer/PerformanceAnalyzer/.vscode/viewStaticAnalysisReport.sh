#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
locateAprgScriptPath=$(realpath "$scriptDirectory/locateAprgDirectory.sh")
exitCode=0

# Validate locate aprg script path
if ! [[ -e $locateAprgScriptPath ]]; then
    echo "$scriptName:$LINENO: Error: The script [$locateAprgScriptPath] does not exist."
    exit 1
fi

# Find aprgDirectory
echo "$scriptName:$LINENO: Finding aprg directory..."
aprgDirectory=""
source "$scriptDirectory/locateAprgDirectory.sh"
findAprgDirectory "$scriptDirectory"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
cppItemWithSeverityGrep=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonGrepCppOutput.sh"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Show all issues found in static analysis reports
staticAnalysisReportPath="StaticAnalysisReport.txt"
scriptPrint "$scriptName" "$LINENO" "Processing static report: [$staticAnalysisReportPath]..."
sed -E "s|.*[/\\]aprg[/\\]| F:/Branches/aprg_project/aprg/aprg/|g" "$staticAnalysisReportPath" | grep -E "$cppItemWithSeverityGrep" || true
scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

