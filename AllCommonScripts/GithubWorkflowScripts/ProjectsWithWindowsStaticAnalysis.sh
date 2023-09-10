#!/bin/bash

projectsWithWindowsStaticAnalysis='
"AprgCommon/AprgCommon",
"AprgLocalScreenMonitoring/AprgLocalScreenMonitoring",
"AprgLocalUserAutomation/AprgLocalUserAutomation",
"ChessPeek/ChessPeek",
"ChessUtilities/ChessUtilities",
"ZZZ_OldProjects/FesterRobot/FesterRobot"
'

projectsWithWindowsStaticAnalysis=$(echo "$projectsWithWindowsStaticAnalysis" | tr '\n' ' ')

export projectsWithWindowsStaticAnalysis

