#!/bin/bash

projectsWithBoost='
"Boost/Boost",
"AprgGnuPlot/AprgGnuPlot"
'

projectsWithBoost=$(echo "$projectsWithBoost" | tr '\n' ' ')

export projectsWithBoost

