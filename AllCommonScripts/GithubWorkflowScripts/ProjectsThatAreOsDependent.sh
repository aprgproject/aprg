#!/bin/bash

projectsThatAreWindowsOnly='
"AprgLocalScreenMonitoring/AprgLocalScreenMonitoring",
"AprgLocalUserAutomation/AprgLocalUserAutomation",
"Chess/ChessPeek/ChessPeek",
"Chess/ChessUtilities/ChessUtilities",
"ZZZ_OldProjects/FesterRobot/FesterRobot"
'

projectsThatAreLinuxOnly='
"boost/BoostTest",
"AprgGnuPlot/AprgGnuPlot"
'

excludedConfigurations='
{"project": "Chess/ChessPeek/ChessPeek", "configurationName": "UbuntuLatestGcc"},
{"project": "Chess/ChessPeek/ChessPeek", "configurationName": "UbuntuLatestClang"},
{"project": "Chess/ChessUtilities/ChessUtilities", "configurationName": "UbuntuLatestGcc"},
{"project": "Chess/ChessUtilities/ChessUtilities", "configurationName": "UbuntuLatestClang"},
{"project": "ZZZ_OldProjects/FesterRobot/FesterRobot", "configurationName": "UbuntuLatestGcc"},
{"project": "ZZZ_OldProjects/FesterRobot/FesterRobot", "configurationName": "UbuntuLatestClang"},
{"project": "boost/BoostTest", "configurationName": "WindowsLatestMsvc"},
{"project": "boost/BoostTest", "configurationName": "WindowsLatestMingw"},
{"project": "boost/BoostTest", "configurationName": "WindowsLatestClang"},
{"project": "AprgGnuPlot/AprgGnuPlot", "configurationName": "WindowsLatestMsvc"},
{"project": "AprgGnuPlot/AprgGnuPlot", "configurationName": "WindowsLatestMingw"},
{"project": "AprgGnuPlot/AprgGnuPlot", "configurationName": "WindowsLatestClang"}
'

projectsThatAreWindowsOnly=$(echo "$projectsThatAreWindowsOnly" | tr '\n' ' ')
projectsThatAreLinuxOnly=$(echo "$projectsThatAreLinuxOnly" | tr '\n' ' ')
excludedConfigurations=$(echo "$excludedConfigurations" | tr '\n' ' ')

export projectsThatAreWindowsOnly
export projectsThatAreLinuxOnly
export excludedConfigurations

