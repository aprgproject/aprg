#!/bin/bash

dateTimePrintCommand="date +%Y-%m-%dT%H:%M:%S"

scriptPrint() {
    local scriptName
    local lineNumber
    local message
    scriptName="$1"
    lineNumber="$2"
    message="$3"
    echo -e "\033[35m$($dateTimePrintCommand)\033[0m | \033[33m$scriptName:$lineNumber\033[0m | $message"
}

scriptPrintInCppMatcherFormat() {
    local scriptPath
    local lineNumber
    local columnNumber
    local message
    scriptPath="$1"
    lineNumber="$2"
    columnNumber="$3"
    message="$4"
    echo "$scriptPath:$lineNumber:$columnNumber: $message"
}
