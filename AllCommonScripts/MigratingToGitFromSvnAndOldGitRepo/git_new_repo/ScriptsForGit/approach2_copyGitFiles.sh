#!/bin/bash

scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
gitNewRepoPath=$(realpath "$scriptDirectory/../gitNewRepoHere/")
gitOldRepoPath=$(realpath "$scriptDirectory/../../git_old_repo/gitOldRepoHere/")
revisionHash=$1

if [ -z "$revisionHash" ]; then
    echo "No parameter was given. Please provide revisionHash number as a parameter."
    exit 1
fi

set -e
cd "$gitOldRepoPath"
echo "Changing directory to $(pwd)"

set +e
while true; do
    echo "Performing: git checkout $revisionHash"
    git checkout $revisionHash
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
        sleep 10
    fi
done
echo "List directory (check if .git folder is deleted): $(ls -la)"
echo "Copying from [$gitOldRepoPath/*] to [$gitNewRepoPath]"
rsync --verbose --archive --recursive --force --exclude='.svn/' $gitOldRepoPath/* $gitNewRepoPath
# dont perform dos2unix because git handles different line endings depending on git configuration
#find "$gitNewRepoPath" -type f ! -path '/**/.git/**/*' -exec dos2unix {} \;
