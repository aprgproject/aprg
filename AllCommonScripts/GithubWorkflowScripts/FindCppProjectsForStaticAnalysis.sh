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
        scriptPrint "$scriptName" "$LINENO" "The cppProject: [$cppProject]"
        scriptPrint "$scriptName" "$LINENO" "The static analysis file: [$staticAnalysisOutputPath]"
        if [[ -e $staticAnalysisOutputPath ]]; then
            scriptPrint "$scriptName" "$LINENO" "The static analysis file exists, proceeding to check when the file was modified..."
            modifiedDateTime=$(stat -c %Y "$staticAnalysisOutputPath")
            timeDifference=$((currentDateTime - modifiedDateTime))
            scriptPrint "$scriptName" "$LINENO" "currentDateTime: [$currentDateTime], modifiedDateTime: [$modifiedDateTime], timeDifference: [$timeDifference]"
            if [ "$timeDifference" -gt 86400 ]; then
                scriptPrint "$scriptName" "$LINENO" "The project is ADDED because the static analysis file was modified more than 24 hours ago."
                cppProjectsFound+="$cppProject,"
            else
                scriptPrint "$scriptName" "$LINENO" "The project is NOT ADDED because the static analysis file was modified within the last 24 hours."
            fi
        else
            scriptPrint "$scriptName" "$LINENO" "The project is ADDED because the static analysis file does not exist."
            cppProjectsFound+="$cppProject,"
        fi
    done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition" | sort -f)
    
    scriptPrint "$scriptName" "$LINENO" "The cppProjectsFound are: [$cppProjectsFound]"
    export cppProjectsFound
}
