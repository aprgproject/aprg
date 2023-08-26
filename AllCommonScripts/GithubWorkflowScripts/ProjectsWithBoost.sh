#!/bin/bash

projectsWithBoost='
"boost/BoostTest",
"AprgGnuPlot/AprgGnuPlot"
'

projectsWithBoost=$(echo "$projectsWithBoost" | tr '\n' ' ')

export projectsWithBoost

