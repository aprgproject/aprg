#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Detect git changes
changedFiles=$(git diff --name-only HEAD^)
scriptPrint $scriptName $LINENO "changedFiles: [$changedFiles]"

# Output projects
changedProjects="AprgCommon/AprgCommon,AprgMath/AprgMath"
scriptPrint $scriptName $LINENO "changedProjects: [$changedProjects]"
echo "::set-env name=ProjectsToBuildInEnv::$changedProjects"
