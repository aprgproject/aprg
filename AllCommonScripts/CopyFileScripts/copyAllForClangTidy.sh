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
cppSkipPathRegex=""
source "$aprgDirectory/AllCommonScripts/CommonRegex/CommonRegexForPaths.sh"

scriptPrint "$scriptName" "$LINENO" "Started copying of files for clang tidy..."
cp -f "$aprgDirectory/Clang/ClangTidyFiles/tests.clang-tidy" "$aprgDirectory/.clang-tidy"
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" "../../.clang-tidy"
cp -f "$aprgDirectory/Clang/ClangTidyFiles/general.clang-tidy" "$aprgDirectory/.clang-tidy"
scriptPrint "$scriptName" "$LINENO" "The copying of files for clang tidy is finished."
