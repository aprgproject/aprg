#!/bin/bash

# Set variables
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
svnRepoPath=$(realpath "$scriptDirectory/../../svn/svnRepoHere/")
revision=$1

if [ -z "$revision" ]; then
    echo "No parameter was given. Please provide revision number as a parameter."
    exit 1
fi

set -e
cd "$svnRepoPath"
echo "Changing directory to $(pwd)"

set +e
while true; do
    echo "Performing: svn update -r $revision"
    svn update -r $revision
    if [[ $? -eq 0 ]]; then
        break
    else
        echo "There is some error during checkout, sleeping for 1 minute before trying again."
        sleep 60
    fi
done

set -e
cd "$gitNewRepoPath"
echo "Changing directory to $(pwd)"
while true; do
    echo "Perform \"rm -rf *\", it should avoid deleting the \".git\" folder."
    rm -rf *
    if [[ $? -eq 0 ]]; then
        break
    else
        echo "there is some error during deletion, sleeping for 10 seconds before trying again."
        sleep 10
    fi
done
echo "List directory (check if .git folder is deleted): $(ls -la)"
echo "Copying from [$svnRepoPath/*] to [$gitNewRepoPath]"
rsync --verbose --archive --recursive --force --exclude='.svn/' $svnRepoPath/* $gitNewRepoPath
# perform dos2unix, because in the previous migration there were differences due to line endings
find "$gitNewRepoPath" -type f ! -path '/**/.git/**/*' -exec dos2unix {} \;
