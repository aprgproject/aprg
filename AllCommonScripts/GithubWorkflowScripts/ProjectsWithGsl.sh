#!/bin/bash

projectsWithGsl='
"AprgModelling/AprgModelling"
'

projectsWithGsl=$(echo "$projectsWithGsl" | tr '\n' ' ')

export projectsWithGsl

