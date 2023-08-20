#!/bin/bash

projectsWith7Zip='
"AprgFileExtractor/AprgFileExtractor"
'

projectsWith7Zip=$(echo "$projectsWith7Zip" | tr '\n' ' ')

export projectsWith7Zip

