#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
copyCommand=$(realpath "$scriptDirectory/copyFileToSeveralLocations.sh")

$copyCommand .vscode/tasks.json
