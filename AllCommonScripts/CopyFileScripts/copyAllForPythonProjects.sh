#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
scriptDirectory=$(dirname "$(realpath "$0")")
copyUsingLocatorFile=$(realpath "$scriptDirectory/copyFileUsingLocatorFile.sh")

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
pythonIncludePathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"

scriptPrint "$scriptName" "$LINENO" "Started copying of files for python projects..."
$copyUsingLocatorFile "$pythonIncludePathRegex" "^$" PythonProjects/.vscode/launch.json
scriptPrint "$scriptName" "$LINENO" "The copying of files for python projects is finished."
