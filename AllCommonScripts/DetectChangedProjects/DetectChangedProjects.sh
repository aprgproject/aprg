#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
aprgDirectoryName="aprg"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Detect git changes
#detectedFiles=$(git diff --name-only HEAD^)

detectedProjects=""
searchingDirectory="$aprgDirectory/AprgCommon/AprgCommon/src/Common/Container/AlbaXY.hpp"
while [ "$searchingDirectory" != "/" ]; do
    scriptPrint $scriptName $LINENO "The searchingDirectory is: [$searchingDirectory]"
	if [ $(basename "$searchingDirectory") == "$aprgDirectoryName" ]; then
		break
    elif ! [[ -e $"$searchingDirectory/CMakeLists.txt" ]]; then
        formattedRelativePath=$(echo "\"$searchingDirectory\"" || sed -E "s|$aprgDirectory|\|")
    	if [[ -z $detectedProjects ]]; then
            detectedProjects=$formattedRelativePath
        else
            detectedProjects=$detectedProjects,$formattedRelativePath
        if
	else
		searchingDirectory=$(dirname "$searchingDirectory")
	fi
done

scriptPrint $scriptName $LINENO "The detectedProjects is: [$detectedProjects]"
# Output projects
detectedProjects="\"AprgCommon/AprgCommon\",\"AprgMath/AprgMath\""
echo "APRG_CHANGED_DIRECTORIES=[$detectedProjects]" >> "$GITHUB_OUTPUT"
