#!/bin/bash

# Set variable values
scriptPath=$(realpath "$0")
scriptDirectory=$(dirname "$scriptPath")
copyCommand=$(realpath "$scriptDirectory/copyFileToSeveralLocations.sh")

$copyCommand cmake/LocateAprgDirectory.cmake
$copyCommand cmake/AddFlags.cmake
$copyCommand cmake/SpecificStepsAsExecutable.cmake
$copyCommand cmake/SpecificStepsAsLibrary.cmake
$copyCommand .vscode/launch.json
$copyCommand .vscode/tasks.json
$copyCommand .vscode/locateAprgDirectory.sh
$copyCommand .vscode/runWslCommonScript.sh
$copyCommand ProjectDirectory/CMakePresets.json
