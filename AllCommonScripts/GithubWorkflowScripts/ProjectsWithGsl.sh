#!/bin/bash

projectsWithGsl='
"gsl/GslTest",
"AprgModelling/AprgModelling"
'

projectsWithGsl=$(echo "$projectsWithGsl" | tr '\n' ' ')

export projectsWithGsl

