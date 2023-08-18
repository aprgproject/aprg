#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$(realpath "$0")")
scriptName=$(basename "$(realpath "$0")")
scriptRunningOption="$1"
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

# Running WSL Build And Run Script
buildAndRunScriptPath=$(realpath "$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh")
if ! [[ -e $buildAndRunScriptPath ]]; then
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The script [$buildAndRunScriptPath] does not exist."
    exit 1
fi

if [ "$scriptRunningOption" == "outputWithHighlighting" ]; then
    $buildAndRunScriptPath "$2" "$3" "$4" "$5"
    exitCode=$?
elif [ "$scriptRunningOption" == "outputWithAbsolutePaths" ]; then
    $buildAndRunScriptPath "$2" "$3" "$4" "$5" 2>&1 | sed -E "s|\/mnt\/(\w+)\/|\U\1:/|g"
    exitCode=${PIPESTATUS[0]}
elif [ "$scriptRunningOption" == "outputWithRelativePaths" ]; then
    $buildAndRunScriptPath "$2" "$3" "$4" "$5" 2>&1 | sed -E "s|$(pwd)||g"
    exitCode=${PIPESTATUS[0]}
else
    scriptPrint "$scriptName" "$LINENO" "The script running option [$scriptRunningOption] is not supported."
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The script running option [$scriptRunningOption] is not supported by the WSL shell script."
    exit 1
fi

scriptPrint "$scriptName" "$LINENO" "The exit code is: [$exitCode]"
exit "$exitCode"

