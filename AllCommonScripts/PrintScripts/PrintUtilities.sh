#!/bin/bash

dateTimePrintCommand="date +%Y-%m-%dT%H:%M:%S"

scriptPrint() {
    local scriptName="$1"
    local lineNumber="$2"
    local message="$3"
    echo "$($dateTimePrintCommand) | $scriptName:$lineNumber | $message"
}

scriptPrintInCppMatcherFormat() {
    local scriptPath="$1"
    local lineNumber="$2"
    local columnNumber="$3"
    local message="$4"
    echo "$scriptPath:$lineNumber:$columnNumber: $message"
}
