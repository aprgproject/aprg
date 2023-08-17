#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")

svn log > "$scriptDirectory/svnRevisionDetails.txt"
