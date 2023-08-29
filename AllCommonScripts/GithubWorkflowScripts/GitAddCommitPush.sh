#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
scriptName=$(basename "$scriptPath")
aprgDirectory=$(realpath "$scriptDirectory/../../")
jobIdentifier="$1"
commitMessage="$2"

# Source needed scripts
source "$aprgDirectory/AllCommonScripts/UtilitiesScripts/PrintUtilities.sh"

scriptPrint "$scriptName" "$LINENO"  "Performing [git add] to add all versioned files that was changed..."
git add -u
scriptPrint "$scriptName" "$LINENO"  "Performing [git diff] to see the local changes (file paths only):"
git diff --cached --name-only
scriptPrint "$scriptName" "$LINENO"  "Performing [git commit] with a message..."
git commit -m "JobId[$jobIdentifier] $commitMessage"

maxRetries=3
retries=0
gitPushExitStatus=1

while [ "$retries" -lt "$maxRetries" ] && [ "$gitPushExitStatus" -ne 0 ]; do
    scriptPrint "$scriptName" "$LINENO" "The current number of retries: [$retries], the max number of retries: [$maxRetries]."
    scriptPrint "$scriptName" "$LINENO" "Performing [git pull] before [push] to merge with recent commits..."
    git pull --no-rebase --no-edit
    scriptPrint "$scriptName" "$LINENO" "Performing [git commit --amend] to overwrite with correct commit message..."
    git commit --amend -m "JobId[$jobIdentifier] $commitMessage"
    scriptPrint "$scriptName" "$LINENO" "Commit message: [$(git log -1 --pretty=%B)]"

    set +e
    scriptPrint "$scriptName" "$LINENO" "Performing [git push]..."
    git push
    gitPushExitStatus=$?
    set -e

    retries=$((retries + 1))
done

if [ "$gitPushExitStatus" -eq 0 ]; then
    scriptPrint "$scriptName" "$LINENO" "The git push done has finished, the changes should exist now in the repository."
else
    scriptPrint "$scriptName" "$LINENO" "The git push has failed even after trying for $retries times, exiting as failure."
    exit "$gitPushExitStatus"
fi