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

# Output projects
changedProjects="AprgCommon/AprgCommon,AprgMath/AprgMath"
echo "::set-output name=ProjectsToBuild::$changedProjects"
