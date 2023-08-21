#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
immediateDirectoryName=$(basename "$(pwd)")
numberOfCores=$(nproc)
scriptOption="$1"
buildDirectoryName="$2"
argument1="$3"
argument2="$4"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

# Validate inputs
if [[ -z $scriptOption ]]; then
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The scriptOption: [$scriptOption] is empty."
    exit 1
fi

# Display variable values
scriptPrint "$scriptName" "$LINENO" "The current path is [$(pwd)]."
scriptPrint "$scriptName" "$LINENO" "The scriptPath is [$scriptPath]."
scriptPrint "$scriptName" "$LINENO" "The scriptOption is [$scriptOption]."
scriptPrint "$scriptName" "$LINENO" "The buildDirectoryName is [$buildDirectoryName]."
scriptPrint "$scriptName" "$LINENO" "The argument1 is [$argument1] and argument2 is [$argument2]."
scriptPrint "$scriptName" "$LINENO" "The immediateDirectoryName is [$immediateDirectoryName]."

# Setup folders for compilation
cd ..
mkdir -p "$buildDirectoryName"
cd "$buildDirectoryName"
scriptPrint "$scriptName" "$LINENO" "The build path is [$(pwd)] and the output of 'ls -la':"
ls -la

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

performClean() {
    if [ "$buildDirectoryName" = "$(basename "$(pwd)")" ]; then
        scriptPrint "$scriptName" "$LINENO" "Deleting everything in [$(pwd)]."
        rm -rf ./*
        scriptPrint "$scriptName" "$LINENO" "After deletion in [$(pwd)] contents:"
        ls -la
    fi
}

# Perform script actions based from script option
if [ "$scriptOption" == "clean" ]; then
    performClean
elif [ "$scriptOption" == "configureWithDefaultCompiler" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithGcc" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    cCompilerLocation="$(command -v gcc)"
    cppCompilerLocation="$(command -v g++)"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    scriptPrint "$scriptName" "$LINENO" "The cCompilerLocation is [$cCompilerLocation] and cppCompilerLocation is [$cppCompilerLocation]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithClang" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    cCompilerLocation="$(command -v clang)"
    cppCompilerLocation="$(command -v clang++)"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    scriptPrint "$scriptName" "$LINENO" "The cCompilerLocation is [$cCompilerLocation] and cppCompilerLocation is [$cppCompilerLocation]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithClangWithAsan" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    cCompilerLocation="$(command -v clang)"
    cppCompilerLocation="$(command -v clang++)"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    scriptPrint "$scriptName" "$LINENO" "The cCompilerLocation is [$cCompilerLocation] and cppCompilerLocation is [$cppCompilerLocation]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" -DCMAKE_C_FLAGS:STRING="-g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="-g -fsanitize=address -fno-omit-frame-pointer" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithClangAndStaticAnalyzers" ]; then
    performClean
    buildType="$argument1"
    cmakeGenerator="$argument2"
    cppCompilerLocation="$(command -v clazy)" # Use clazy as static analyzer
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    scriptPrint "$scriptName" "$LINENO" "The cppCompilerLocation is [$cppCompilerLocation]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "-DAPRG_ENABLE_STATIC_ANALYZERS=ON" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "build" ]; then
    buildType="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The numberOfCores is [$numberOfCores]."
    cmake --build . --config "$buildType"  --parallel "$numberOfCores" 2>&1 # | tee "$(pwd)/BuildOutput.txt"
elif [ "$scriptOption" == "install" ]; then
    buildType="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    cmake --install . --verbose --config "$buildType"
elif [ "$scriptOption" == "run" ]; then
    gtestFilter="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The gtestFilter is [$gtestFilter]."
    cd install/runDirectory
    scriptPrint "$scriptName" "$LINENO" "The current directory is [$(pwd)] and the output of ls:"
    ls -la
    for fileInBin in ./*; do
        if [[ -x "$fileInBin" ]]; then
            scriptPrint "$scriptName" "$LINENO" "Running executable: [$(pwd)/$fileInBin]."
            if [[ -z $gtestFilter ]]; then
                "$fileInBin"
            else 
                "$fileInBin" "$gtestFilter"
            fi
        fi
    done
else
    scriptPrint "$scriptName" "$LINENO" "The script option [$scriptOption] is not found."
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The script option [$scriptOption] is NOT supported by the shell script."
    exit 1
fi