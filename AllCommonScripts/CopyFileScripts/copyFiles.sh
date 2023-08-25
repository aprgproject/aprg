#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")
copyCommand=$(realpath "$scriptDirectory/copyFileToSeveralLocations.sh")

$copyCommand CppProjects/cmake/LocateAprgDirectory.cmake
$copyCommand CppProjects/cmake/AddFlags.cmake
$copyCommand CppProjects/.vscode/c_cpp_properties.json
$copyCommand CppProjects/.vscode/launch.json
$copyCommand CppProjects/.vscode/settings.json
$copyCommand CppProjects/.vscode/tasks.json
$copyCommand CppProjects/.vscode/locateAprgDirectory.sh
$copyCommand CppProjects/.vscode/runWslCommonScript.sh
$copyCommand CppProjects/CMakePresets.json
