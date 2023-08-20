#!/bin/bash

findCppProjects() {
    # Set variable values
    local scriptName
    local aprgDirectory
    local userInput
    scriptName="FindCppProjects.sh"
    aprgDirectory=$(realpath "$(dirname "$0")/../../")
    userInput="$1"
    
    # Source needed scripts
    source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
    aprgLocatorFile=""
    source "$aprgDirectory/AllCommonScripts/CommonRegex/AddingAprgLocatorFile.sh"
    
    searchCondition=""
    if [[ -z $userInput ]] || [ "$userInput" == "all" ]; then
        scriptPrint "$scriptName" "$LINENO" "The user input is [$userInput], setting a different condition."
        searchCondition="*$aprgLocatorFile"
    else
        searchCondition="*$userInput*$aprgLocatorFile"
    fi
    scriptPrint "$scriptName" "$LINENO" "Searching directories for C/C++ projects using searchCondition: [$searchCondition]"
    cppProjectsFound=$(find "$aprgDirectory" -depth -type f -wholename "$searchCondition" -exec sh -c 'echo "$1" | sed -E "s|^.*$2/(.*)$3.*$|\"\1\"|"' sh {} "$aprgDirectory" "$aprgLocatorFile" \;  | xargs -0 -n1 | paste -sd "," -)
    
    scriptPrint "$scriptName" "$LINENO" "The cppProjectsFound are: [$cppProjectsFound]"
    export cppProjectsFound
}
