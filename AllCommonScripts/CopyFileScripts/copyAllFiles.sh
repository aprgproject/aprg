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

scriptPrint "$scriptName" "$LINENO" "Started copying of files for cpp projects..."
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/cmake/LocateAprgDirectory.cmake
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/cmake/AddFlags.cmake
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/c_cpp_properties.json
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/launch.json
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/settings.json
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/tasks.json
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/locateAprgDirectory.sh
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/.vscode/runWslCommonScript.sh
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" CppProjects/CMakePresets.json
scriptPrint "$scriptName" "$LINENO" "The copying of files for cpp projects is finished."

scriptPrint "$scriptName" "$LINENO" "Started copying of files for clang tidy..."
cp -f "$aprgDirectory/Clang/ClangTidyFiles/tests.clang-tidy" "$aprgDirectory/.clang-tidy"
$copyUsingLocatorFile ".*" "$cppSkipPathRegex" "$aprgDirectory/.clang-tidy"
cp -f "$aprgDirectory/Clang/ClangTidyFiles/general.clang-tidy" "$aprgDirectory/.clang-tidy"
scriptPrint "$scriptName" "$LINENO" "The copying of files for clang tidy is finished."
