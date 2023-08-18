#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
svnDiffsPath=$(realpath "$scriptDirectory/../../svn/diffs/")
revision="$1"

if [ -z "$revision" ]; then
    echo "No parameter was given. Please provide revision number as a parameter."
    exit 1
fi

set -e
diffFilePath="$svnDiffsPath/r$revision.diff"
echo "diffFilePath: [$diffFilePath]"
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
# perform dos2unix, because in the previous migration there were differences due to line endings
dos2unix "$diffFilePath" 
git apply --check --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"
git apply --ignore-space-change --ignore-whitespace --inaccurate-eof "$diffFilePath"