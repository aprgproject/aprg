#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
immediateDirectoryName=$(basename "$(dirname "$(pwd)")")
wslBuildDirectoryName="WslBuild"
numberOfCoresInTheSystem=$(nproc)
exitCode=0
scriptOption=$1
firstArgument=$2

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/PrintScripts/PrintUtilities.sh"

# Display variable values
scriptPrint $scriptName $LINENO "The build option is [$scriptOption]"
scriptPrint $scriptName $LINENO "The script path is [$scriptPath]"
scriptPrint $scriptName $LINENO "The immediate directory name is [$immediateDirectoryName]"
scriptPrint $scriptName $LINENO "The WSL build directory name is [$wslBuildDirectoryName]"
scriptPrint $scriptName $LINENO "The first argument is [$firstArgument]"

# Setup folders for compilation
cd ..
mkdir -p $wslBuildDirectoryName
cd $wslBuildDirectoryName
scriptPrint $scriptName $LINENO "The build path is [$(pwd)]"

# Enable the "exit on error" option to automatically stop if there is a failure
set -e

# Perform script actions
if [ "$scriptOption" == "clean" ]; then
	if [ "$wslBuildDirectoryName" = $(basename "$(pwd)") ]; then
		scriptPrint $scriptName $LINENO "Deleting everything in [$(pwd)]."
		rm -rf *
		exitCode=$?
		scriptPrint $scriptName $LINENO "After deletion in [$(pwd)] contents: [$(ls)]"
	fi
elif [ "$scriptOption" == "buildWithGcc" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_CXX_COMPILER=/usr/bin/g++ "../$immediateDirectoryName/"
	make -j$numberOfCoresInTheSystem
	exitCode=$?
elif [ "$scriptOption" == "buildWithClang" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ "../$immediateDirectoryName/"
	make -j$numberOfCoresInTheSystem
	exitCode=$?
elif [ "$scriptOption" == "buildWithClangWithAsan" ]; then
	cmake -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" -DCMAKE_CXX_FLAGS:STRING="${CMAKE_C_FLAGS} -g --coverage -fsanitize=address -fno-omit-frame-pointer" "../$immediateDirectoryName/"
	make -j$numberOfCoresInTheSystem
	exitCode=$?
elif [ "$scriptOption" == "install" ]; then
	make install
	exitCode=$?
elif [ "$scriptOption" == "run" ]; then
    projectName=$(cmake -P $aprgDirectory/AprgCMakeHelpers/GetProjectName.cmake)
    if [ -z "$projectName" ]; then
        scriptPrint $scriptName $LINENO "Error: The projectName is not determined using cmake."
	    exit 1
    fi
	scriptPrint $scriptName $LINENO "Running executable: [$(pwd)/$projectName]."
	"./$projectName" "$firstArgument"
	exitCode=$?
else
	scriptPrint $scriptName $LINENO "The script option [$scriptOption] is not found."
	echo "$scriptPath:$LINENO:${BASH_LINENO[0]}: error: The script option [$scriptOption] is not supported by the WSL shell script."
	exitCode=1
fi

scriptPrint $scriptName $LINENO "The exit code is: [$exitCode]"
exit $exitCode