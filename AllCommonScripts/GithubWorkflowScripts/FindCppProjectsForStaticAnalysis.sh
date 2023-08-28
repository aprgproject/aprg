#!/bin/bash

findCppProjectsForStaticAnalysis() {
    # Set variable values
    local scriptName
    local aprgDirectory
    local staticAnalysisFilename
    scriptName="FindCppProjectsForStaticAnalysis.sh"
    aprgDirectory=$(realpath "$(dirname "$0")/../../")
    staticAnalysisFilename="$1"
    
    # Source needed scripts
    source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
    cppIndicatorFilePath=""
    source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
    
    currentDateTime=$(date +%s)
    cppProjectsFound=""
    searchCondition="*$cppIndicatorFilePath"
    scriptPrint "$scriptName" "$LINENO" "Searching directories for C/C++ projects using searchCondition: [$searchCondition]"
    while IFS= read -r aprgProjectLocatorPath; do
        aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$cppIndicatorFilePath||")
        staticAnalysisOutputPath="$aprgProjectDirectory/$staticAnalysisFilename"
        cppProject=$(echo "$aprgProjectDirectory" | sed -E "s|^.*$aprgDirectory/(.*)$|\"\1\"|")
        if [[ -e $staticAnalysisOutputPath ]]; then
            scriptPrint "$scriptName" "$LINENO" "Check when the file was modified, staticAnalysisOutputPath: [$staticAnalysisOutputPath]"
            modifiedDateTime=$(stat -c %Y "$staticAnalysisOutputPath")
            timeDifference=$((currentDateTime - modifiedDateTime))
            scriptPrint "$scriptName" "$LINENO" "currentDateTime: [$currentDateTime], modifiedDateTime: [$modifiedDateTime], timeDifference: [$timeDifference]"
            if [ "$timeDifference" -gt 86400 ]; then
                scriptPrint "$scriptName" "$LINENO" "This file was modified more than 24 hours ago, staticAnalysisOutputPath: [$staticAnalysisOutputPath]"
                cppProjectsFound+="$cppProject,"
            fi
        else
            scriptPrint "$scriptName" "$LINENO" "This file does not exist, staticAnalysisOutputPath: [$staticAnalysisOutputPath]"
            cppProjectsFound+="$cppProject,"
        fi
    done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition")
    
    scriptPrint "$scriptName" "$LINENO" "The cppProjectsFound are: [$cppProjectsFound]"
    export cppProjectsFound
}
