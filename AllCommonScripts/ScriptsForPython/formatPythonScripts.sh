#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
inputDirectory="$1"

# Use aprg directory if there are no arguments
if [ -z "$inputDirectory" ]; then
    inputDirectory="$aprgDirectory/Python"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
pythonIncludePathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"
pathRegex="$pythonIncludePathRegex"

# Create needed functions
formatPythonScriptsInDirectory() {
    local directoryPath
    directoryPath="$1"

    scriptPrint "$scriptName" "$LINENO" "Searching for python scripts in: [$directoryPath]"

    while IFS= read -r filePath; do
        if  [[ "$filePath" =~ $pathRegex ]]; then
            scriptPrint "$scriptName" "$LINENO" "Processing python file: [$filePath]"
            
            # unix style line endings
            dos2unix "$filePath"
        
            # convert tabs to 4 spaces
            expand -t 4 "$filePath" > "$tempFile"
            mv "$tempFile" "$filePath"

            # be sure to make it an executable
            chmod +x "$filePath"

            # use autopep8 to format
            autopep8 --in-place "$filePath"
        fi
    done < <(find "$directoryPath" -type f -name "*.py")
}

# Find all files with the same name in the target folder
tempFile=$(mktemp)
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$inputDirectory]..."
formatPythonScriptsInDirectory "$inputDirectory"

scriptPrint "$scriptName" "$LINENO" "All shell scripts in the directory are processed."