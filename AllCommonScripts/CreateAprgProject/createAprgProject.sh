#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
scriptOption="$1"
projectName="$2"
capitalUnderscoreName="$3"
parentDirectory=$(realpath "$4")

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate input
if [ -z "$scriptOption" ]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The scriptOption cannot be empty, scriptOption: [$scriptOption]."
    exit 1
fi
if [ -z "$projectName" ]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The projectName cannot be empty, projectName: [$projectName]."
    exit 1
fi
if ! [[ -d $parentDirectory ]]; then
    scriptPrint "$scriptName" "$LINENO" "Error: The directory [$parentDirectory] does not exist."
    exit 1
fi

# Utility Functions
copyTemplateFiles() {
    templateName="$1"
    templateDirectory="$aprgDirectory/$templateName"
    projectDirectory="$parentDirectory/$projectName"
    scriptPrint "$scriptName" "$LINENO" "copyTemplateFiles() [$templateName] [$templateDirectory] [$projectDirectory]"
    mkdir -p "$projectDirectory"
    rsync --verbose --archive --recursive --force --include='*/' --include='.*' "$templateDirectory/*" "$projectDirectory"
}

replaceAllText() {
    local targetString
    local replacementString
    targetString="$1"
    replacementString="$2"
    scriptPrint "$scriptName" "$LINENO" "replaceAllText() [$targetString] [$replacementString]"
    "$aprgDirectory/AllCommonScripts/ReplaceTextScripts/replaceText.sh" "$projectDirectory" "$targetString" "$replacementString"
}

if [ "$scriptOption" == "TemplateForAllCases" ]; then
    copyTemplateFiles "TemplateForAllCases" 
    cd "$projectDirectory" || exit 1
    replaceAllText "TemplateForAllCases" "$projectName"
    replaceAllText "TEMPLATE_FOR_ALL_CASES" "$capitalUnderscoreName"
elif [ "$scriptOption" == "TemplateForLibraries" ]; then
    copyTemplateFiles "TemplateForLibraries" 
    cd "$projectDirectory" || exit 1
    replaceAllText "TemplateForLibraries" "$projectName"
    replaceAllText "TEMPLATE_FOR_LIBRARIES" "$capitalUnderscoreName"
elif [ "$scriptOption" == "TemplateForPrograms" ]; then
    copyTemplateFiles "TemplateForPrograms" 
    cd "$projectDirectory" || exit 1
    replaceAllText "TemplateForPrograms" "$projectName"
    replaceAllText "TEMPLATE_FOR_PROGRAMS" "$capitalUnderscoreName"
else
    scriptPrint "$scriptName" "$LINENO" "The script option [$scriptOption] is not supported by this script."
    exit 1
fi