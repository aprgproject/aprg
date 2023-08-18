#!/bin/bash

excludedConfigurations='
{"project": "Boost/Boost", "configurationName": "WindowsLatestMsvc"},
{"project": "Boost/Boost", "configurationName": "WindowsLatestMingw"},
{"project": "AprgGnuPlot/AprgGnuPlot", "configurationName": "WindowsLatestMsvc"},
{"project": "AprgGnuPlot/AprgGnuPlot", "configurationName": "WindowsLatestMingw"},
{"project": "Chess/ChessPeek/ChessPeek", "configurationName": "UbuntuLatestGcc"},
{"project": "Chess/ChessPeek/ChessPeek", "configurationName": "UbuntuLatestClang"},
{"project": "Chess/ChessUtilities/ChessUtilities", "configurationName": "UbuntuLatestGcc"},
{"project": "Chess/ChessUtilities/ChessUtilities", "configurationName": "UbuntuLatestClang"},
{"project": "ZZZ_OldProjects/FesterRobot/FesterRobot", "configurationName": "UbuntuLatestGcc"},
{"project": "ZZZ_OldProjects/FesterRobot/FesterRobot", "configurationName": "UbuntuLatestClang"}
'
excludedConfigurations=$(echo "$excludedConfigurations" | tr '\n' ' ')

export excludedConfigurations

