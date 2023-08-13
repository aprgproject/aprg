#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
immediateDirectoryName=$(basename "$(dirname "$(pwd)")")
numberOfCores=$(nproc)
scriptOption=$1
buildType=$2
buildDirectoryName=$3
firstArgument=$4

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Validate inputs
if [[ -z $scriptOption ]]; then
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The scriptOption: [$scriptOption] is empty."
	exit 1
fi
if [[ -z $buildType ]]; then
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The buildType: [$buildType] is empty."
	exit 1
fi
if [[ -e $buildDirectoryName ]]; then
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The buildDirectoryName: [$buildDirectoryName] does not exist."
	exit 1
fi

# Display variable values
scriptPrint $scriptName $LINENO "The scriptPath is [$scriptPath]"
scriptPrint $scriptName $LINENO "The scriptOption is [$scriptOption]"
scriptPrint $scriptName $LINENO "The buildType is [$buildType]"
scriptPrint $scriptName $LINENO "The buildDirectoryName is [$buildDirectoryName]"
scriptPrint $scriptName $LINENO "The firstArgument is [$firstArgument]"
scriptPrint $scriptName $LINENO "The immediateDirectoryName is [$immediateDirectoryName]"

# Setup folders for compilation
cd ..
mkdir -p $buildDirectoryName
cd $buildDirectoryName
scriptPrint $scriptName $LINENO "The build path is [$(pwd)]"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Perform script actions
if [ "$scriptOption" == "clean" ]; then
	if [ "$buildDirectoryName" = $(basename "$(pwd)") ]; then
		scriptPrint $scriptName $LINENO "Deleting everything in [$(pwd)]."
		rm -rf *
		scriptPrint $scriptName $LINENO "After deletion in [$(pwd)] contents: [$(ls)]"
	fi
elif [ "$scriptOption" == "configureWithDefaultCompiler" ]; then
	cmake -DCMAKE_BUILD_TYPE=$buildType "../$immediateDirectoryName/"
elif [ "$scriptOption" == "configureWithGcc" ]; then
	cmake -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ "../$immediateDirectoryName/"
elif [ "$scriptOption" == "configureWithClang" ]; then
	cmake -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ "../$immediateDirectoryName/"
elif [ "$scriptOption" == "configureWithClangWithAsan" ]; then
	cmake -DCMAKE_BUILD_TYPE=$buildType -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" "../$immediateDirectoryName/"
elif [ "$scriptOption" == "build" ]; then
	cmake --build . --config $buildType
elif [ "$scriptOption" == "install" ]; then
	cmake --install . --verbose --config $buildType
elif [ "$scriptOption" == "run" ]; then
    cd install/bin
    for fileInBin in ./*; do
        if [[ -x "$fileInBin" ]]; then
            scriptPrint $scriptName $LINENO "Running executable: [$fileInBin]."
            "$fileInBin"
        fi
    done
else
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	scriptPrintInCppMatcherFormat $scriptPath $LINENO ${BASH_LINENO[0]} "error: The script option [$scriptOption] is NOT supported by the shell script."
	exit 1
fi

scriptPrint $scriptName $LINENO "The exit code is: [$?]"