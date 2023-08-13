#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
scriptRunningOption=$1
locateScriptPath=$(realpath "$scriptDirectory/locateAprgDirectory.sh")
exitCode=0

# Find aprgDirectory
echo "$scriptName:$LINENO: Finding aprg directory..."
if ! [[ -e $locateScriptPath ]]; then
	echo "$scriptName:$LINENO: Error: The script [$locateScriptPath] does not exist."
	exit 1
fi
source "$scriptDirectory/locateAprgDirectory.sh"
findAprgDirectory $scriptDirectory

# Validate aprgDirectory
if ! [[ -e $aprgDirectory ]]; then
	echo "$scriptName:$LINENO: Error: The script [$aprgDirectory] does not exist."
	exit 1
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Running WSL Build And Run Script
buildAndRunScriptPath=$(realpath "$aprgDirectory/AllCommonScripts/BuildAndRunScripts/BuildAndRun.sh")
if ! [[ -e $buildAndRunScriptPath ]]; then
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The script [$buildAndRunScriptPath] does not exist."
	exit 1
fi

if [ "$scriptRunningOption" == "outputWithHighlighting" ]; then
	# This command prints output with highlighting because stdout and stderr are maintained
	$buildAndRunScriptPath $2 $3 $4 $5
	exitCode=$?
elif [ "$scriptRunningOption" == "outputWithAbsolutePaths" ]; then
    # This command prints output without highlighting but with corrected absolute paths
	$buildAndRunScriptPath $2 $3 $4 $5 2>&1 | sed -E "s|\/mnt\/(\w+)\/|\U\1:/|g"
	exitCode=$?
elif [ "$scriptRunningOption" == "outputWithRelativePaths" ]; then
    # This command prints output without highlighting but with corrected relative paths from the project directory
	$buildAndRunScriptPath $2 $3 $4 $5 2>&1 | sed -E "s|$(pwd)||g"
	exitCode=$?
else
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The script option [$scriptOption] is not supported by the WSL shell script."
	exitCode=$?
fi

scriptPrint $scriptName $LINENO "The exit code is: [$exitCode]"
exit $exitCode

