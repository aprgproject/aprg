#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
directoryToConvertAllFiles="$1"

# Use aprg directory if there are no arguments
if [ -z "$directoryToConvertAllFiles" ]; then
    directoryToConvertAllFiles="$aprgDirectory"
fi

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"
aprgLocatorFile=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/AddingAprgLocatorFile.sh"
searchCondition="*$aprgLocatorFile"

# Create needed functions
copyFilesToTestDirectories() {
    local directoryPath
    directoryPath="$1"

    testDirectorySearchCondition="$directoryPath/tst*"
    while IFS= read -r testDirectoryPath; do
        scriptPrint "$scriptName" "$LINENO" "Copying to: [$testDirectoryPath]"
        cp "ClangTidyFiles/tests.clang-tidy" "$testDirectoryPath/.clang-tidy"
    done < <(find "$directoryPath" -maxdepth 1 -type d -wholename "$testDirectorySearchCondition")
}

# Find all files with the same name in the target folder
scriptPrint "$scriptName" "$LINENO" "Searching all files in [$directoryToConvertAllFiles]..."
while IFS= read -r aprgProjectLocatorPath; do
    aprgProjectDirectory=$(echo "$aprgProjectLocatorPath" | sed -E "s|$aprgLocatorFile||")
    copyFilesToTestDirectories "$aprgProjectDirectory"
done < <(find "$aprgDirectory" -depth -type f -wholename "$searchCondition")

scriptPrint "$scriptName" "$LINENO" "All C/C++ in the directory are processed."
