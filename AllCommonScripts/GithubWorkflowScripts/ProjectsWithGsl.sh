#!/bin/bash

projectsWithGsl='
"gsl/GslTest",
"AprgModeling/AprgModeling"
'

projectsWithGsl=$(echo "$projectsWithGsl" | tr '\n' ' ')

export projectsWithGsl

