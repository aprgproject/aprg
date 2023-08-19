#!/bin/bash

projectsWithGsl='
"AprgGsl/AprgGsl"
'

projectsWithGsl=$(echo "$projectsWithGsl" | tr '\n' ' ')

export projectsWithGsl

