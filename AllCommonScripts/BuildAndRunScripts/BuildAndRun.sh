#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
immediateDirectoryName=$(basename "$(dirname "$(pwd)")")
numberOfCores=$(nproc)
scriptOption=$1
buildDirectoryName=$2
argument1=$3
argument2=$4

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Validate inputs
if [[ -z $scriptOption ]]; then
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The scriptOption: [$scriptOption] is empty."
    exit 1
fi

# Display variable values
scriptPrint "$scriptName" "$LINENO" "The scriptPath is [$scriptPath]."
scriptPrint "$scriptName" "$LINENO" "The scriptOption is [$scriptOption]."
scriptPrint "$scriptName" "$LINENO" "The buildDirectoryName is [$buildDirectoryName]."
scriptPrint "$scriptName" "$LINENO" "The argument1 is [$argument1] and argument2 is [$argument2]."
scriptPrint "$scriptName" "$LINENO" "The immediateDirectoryName is [$immediateDirectoryName]."

# Setup folders for compilation
cd ..
mkdir -p "$buildDirectoryName"
cd "$buildDirectoryName"
scriptPrint "$scriptName" "$LINENO" "The build path is [$(pwd)]"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Perform script actions based from script option
if [ "$scriptOption" == "clean" ]; then
    if [ "$buildDirectoryName" = "$(basename "$(pwd)")" ]; then
        scriptPrint "$scriptName" "$LINENO" "Deleting everything in [$(pwd)]."
        rm -rf ./*
        scriptPrint "$scriptName" "$LINENO" "After deletion in [$(pwd)] contents:"
        ls -la
    fi
elif [ "$scriptOption" == "configureWithDefaultCompiler" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The cmakeGenerator is [$cmakeGenerator]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithGcc" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The cmakeGenerator is [$cmakeGenerator]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithClang" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The cmakeGenerator is [$cmakeGenerator]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "configureWithClangWithAsan" ]; then
    buildType="$argument1"
    cmakeGenerator="$argument2"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The cmakeGenerator is [$cmakeGenerator]."
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_FLAGS:STRING="-g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="-g --coverage -fsanitize=address -fno-omit-frame-pointer" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "build" ]; then
    buildType="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    cmake --build . --config "$buildType"  --parallel "$numberOfCores"
elif [ "$scriptOption" == "install" ]; then
    buildType="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    cmake --install . --verbose --config "$buildType"
elif [ "$scriptOption" == "run" ]; then
    gtestFilter="$argument1"
    scriptPrint "$scriptName" "$LINENO" "The gtestFilter is [$gtestFilter]."
    cd install/bin
    for fileInBin in ./*; do
        if [[ -x "$fileInBin" ]]; then
            scriptPrint "$scriptName" "$LINENO" "Running executable: [$fileInBin]."
            "$fileInBin" "$gtestFilter"
        fi
    done
else
    scriptPrint "$scriptName" "$LINENO" "The script option [$scriptOption] is not found."
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The script option [$scriptOption] is NOT supported by the shell script."
    exit 1
fi