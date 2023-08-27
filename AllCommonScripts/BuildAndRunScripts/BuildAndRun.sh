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
cCompilerLocation=""
cppCompilerLocation=""
lsCommand="ls -la --color=auto"

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

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

getArgumentsForConfigure() {
    buildType="$argument1"
    cmakeGenerator="$argument2"
}

getArgumentsForBuild() {
    buildType="$argument1"
}

getGccCompilers() {
    cCompilerLocation="$(command -v gcc)"
    cppCompilerLocation="$(command -v g++)"
}

getClangCompilers() {
    cCompilerLocation="$(command -v clang)"
    cppCompilerLocation="$(command -v clang++)"
}

getClangAndClazyCompiler() {
    cCompilerLocation="$(command -v clang)"
    cppCompilerLocation="$(command -v clazy)" # Use clazy as static analyzer
}

printConfigureParameters() {
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType] and cmakeGenerator is [$cmakeGenerator]."
    if [[ -n $cCompilerLocation ]]; then
        scriptPrint "$scriptName" "$LINENO" "The cCompilerLocation is [$cCompilerLocation]."
    fi
    if [[ -n $cppCompilerLocation ]]; then
        scriptPrint "$scriptName" "$LINENO" "The cppCompilerLocation is [$cppCompilerLocation]."
    fi
    scriptPrint "$scriptName" "$LINENO" "The build path is [$(pwd)] and the output of [$lsCommand]:"
    $lsCommand
}

printBuildParameters() {
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The numberOfCores is [$numberOfCores]."
    scriptPrint "$scriptName" "$LINENO" "The build path is [$(pwd)] and the output of [$lsCommand]:"
    $lsCommand
}

printInstallParameters() {
    scriptPrint "$scriptName" "$LINENO" "The buildType is [$buildType]."
    scriptPrint "$scriptName" "$LINENO" "The build path is [$(pwd)] and the output of [$lsCommand]:"
    $lsCommand
}

performClean() {
    if [ "$buildDirectoryName" = "$(basename "$(pwd)")" ]; then
        scriptPrint "$scriptName" "$LINENO" "Deleting everything in [$(pwd)]."
        rm -rf ./*
        scriptPrint "$scriptName" "$LINENO" "After deletion in [$(pwd)] contents:"
        $lsCommand
    fi
}

performRun(){
    scriptPrint "$scriptName" "$LINENO" "The first argument is [$argument1]."
    outputLogPath="$(pwd)/runOutput.log"
    scriptPrint "$scriptName" "$LINENO" "The outputLogPath is [$outputLogPath]."
    cd install/runDirectory
    scriptPrint "$scriptName" "$LINENO" "The current directory is [$(pwd)] and the output of [$lsCommand]:"
    $lsCommand
    for fileInInstall in ./*; do
        if [[ -x "$fileInInstall" ]]; then
            scriptPrint "$scriptName" "$LINENO" "Running executable: [$(pwd)/$fileInInstall]."
            if [[ -z $argument1 ]] || [[ $argument1 == "--gtest_filter=*.*" ]]; then
                
                set +e
                "$fileInInstall" | tee "$outputLogPath"
                set -e
                failingTests=$(sed -n -E 's@^.*\[  FAILED  \]\s+((\w|\.)+)\s+\(.*$@\1@p' "$outputLogPath")
                scriptPrint "$scriptName" "$LINENO" "The contents of failingTests are: [$failingTests]"
                if [[ -z "$failingTests" ]]; then
                    scriptPrint "$scriptName" "$LINENO" "All tests passed!"
                else
                    scriptPrint "$scriptName" "$LINENO" "Running the failing tests again..."
                
                    while IFS= read -r failingTestName; do
                        echo "Running failing test: [$failingTestName]"
                        set +e
                        "$fileInInstall" "--gtest_filter=$failingTestName"
                        set -e
                    done <<< "$failingTests"
                    exit 1
                fi
                
            else 
                "$fileInInstall" "$argument1"
            fi
        fi
    done
}

# Perform script actions based from script option
if [ "$scriptOption" == "clean" ]; then
    performClean
elif [ "$scriptOption" == "cleanAndConfigureWithDefaultCompiler" ]; then
    performClean
    getArgumentsForConfigure
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithGcc" ]; then
    performClean
    getArgumentsForConfigure
    getGccCompilers
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithClang" ]; then
    performClean
    getArgumentsForConfigure
    getClangCompilers
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithClangWithAsan" ]; then
    performClean
    getArgumentsForConfigure
    getClangCompilers
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" -DCMAKE_C_FLAGS:STRING="-g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="-g -fsanitize=address -fno-omit-frame-pointer" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithClangAndStaticAnalyzers" ]; then
    performClean
    getArgumentsForConfigure
    getClangAndClazyCompiler
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "-DAPRG_ENABLE_STATIC_ANALYZERS=ON" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "cleanAndConfigureWithStaticAnalyzersWithAutoFix" ]; then
    performClean
    getArgumentsForConfigure
    getClangAndClazyCompiler
    printConfigureParameters
    cmake -DCMAKE_BUILD_TYPE="$buildType" -DCMAKE_C_COMPILER="$cCompilerLocation" -DCMAKE_CXX_COMPILER="$cppCompilerLocation" "-DAPRG_ENABLE_STATIC_ANALYZERS=ON" "-DAPRG_ENABLE_STATIC_ANALYZERS_AUTO_FIX=ON" "../$immediateDirectoryName/" "-G" "$cmakeGenerator"
elif [ "$scriptOption" == "build" ]; then
    getArgumentsForBuild
    printBuildParameters
    cmake --build . --config "$buildType" --parallel "$numberOfCores"
elif [ "$scriptOption" == "buildOnOneCore" ]; then
    getArgumentsForBuild
    printBuildParameters
    cmake --build . --config "$buildType" --parallel 1
elif [ "$scriptOption" == "install" ]; then
    getArgumentsForBuild
    printInstallParameters
    cmake --install . --verbose --config "$buildType"
elif [ "$scriptOption" == "run" ]; then
    performRun
else
    scriptPrint "$scriptName" "$LINENO" "The script option [$scriptOption] is not found."
    scriptPrintInCppMatcherFormat "$scriptPath" "$LINENO" "${BASH_LINENO[0]}" "error: The script option [$scriptOption] is NOT supported by the shell script."
    exit 1
fi

scriptPrint "$scriptName" "$LINENO" "The script is finished."
