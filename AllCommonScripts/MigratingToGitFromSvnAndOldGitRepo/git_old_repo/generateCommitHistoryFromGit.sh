#!/bin/bash

# Set variable values
scriptDirectory=$(dirname "$(realpath "$0")")

git log --oneline --pretty=format:"([{%h}]) ([{%ad}]) ([{%an <%ae>}]) ([{%s}])" --date=iso-strict > "$scriptDirectory/formattedGitHistory.txt"
