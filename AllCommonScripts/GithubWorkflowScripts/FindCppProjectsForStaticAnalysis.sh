#!/bin/bash

findCppProjectsForStaticAnalysis() {
    # Set variable values
    local scriptName
    local aprgDirectory
    local staticAnalysisFilename
    scriptName="FindCppProjectsForStaticAnalysis.sh"
    aprgDirectory=$(realpath "$(dirname "$0")/../../")
    jobIdentifierFromRun="$1"
    staticAnalysisFilename="$2"
    
    # Source needed scripts
    source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
    cppIndicatorFilePath=""
    source "$aprgDirectory/AllCommonScripts/CommonRegex/IndicatorPaths.sh"
    
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

            scriptPrint "$scriptName" "$LINENO" "The static analysis file exists, checking the job identifiers..."
            read -r jobIdentifierLine < "$staticAnalysisOutputPath"
            jobIdentifierFromFile=$(echo "$jobIdentifierLine" | sed -nE "s|^.*StaticAnalysisJobIdentifier:.*\[(.*)\].*$|\1|p")
            scriptPrint "$scriptName" "$LINENO" "jobIdentifierFromRun: [$jobIdentifierFromRun], jobIdentifierFromFile: [$jobIdentifierFromFile]"

            if [ "$jobIdentifierFromRun" == "$jobIdentifierFromFile" ]; then
                scriptPrint "$scriptName" "$LINENO" "The job indentifiers MATCH so the project is NOT ADDED."
            else
                scriptPrint "$scriptName" "$LINENO" "The job indentifiers DO NOT MATCH so the project is ADDED."
                cppProjectsFound+="$cppProject,"
            fi

        else
            scriptPrint "$scriptName" "$LINENO" "The project is ADDED because the static analysis file does not exist."
            cppProjectsFound+="$cppProject,"
        fi

    done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition" | sort -f)
    
    scriptPrint "$scriptName" "$LINENO" "The cppProjectsFound are: [$cppProjectsFound]"
    export cppProjectsFound
}
