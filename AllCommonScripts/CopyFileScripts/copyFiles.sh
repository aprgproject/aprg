#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
copyCommand=$(realpath "$scriptDirectory/copyFileToSeveralLocations.sh")

$copyCommand cmake/LocateAprgDirectory.cmake
$copyCommand cmake/AddFlags.cmake
$copyCommand .vscode/c_cpp_properties.json
$copyCommand .vscode/launch.json
$copyCommand .vscode/tasks.json
$copyCommand .vscode/locateAprgDirectory.sh
$copyCommand .vscode/runWslCommonScript.sh
$copyCommand ProjectDirectory/CMakePresets.json
