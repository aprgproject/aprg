#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
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

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Show all issues found in static analysis reports
sed -E "s|/home/runner/work/aprg/|F:/Branches/aprg_project/aprg/|g" "$scriptDirectory/../StaticAnalysisReport.txt"

scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

