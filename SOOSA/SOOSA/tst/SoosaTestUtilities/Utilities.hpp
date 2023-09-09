#pragma once

#include <SOOSA.hpp>

#include <gtest/gtest.h>

namespace alba::soosa {
void checkAnswersForCharityPayWardsPattern1(SOOSA const& soosa);
void checkAnswersForDemObasPattern1(SOOSA const& soosa);
void checkAnswersForDemObasPattern2(SOOSA const& soosa);
void checkAnswersForDemObasPattern3(SOOSA const& soosa);
void checkAnswersForDemObasPattern4(SOOSA const& soosa);
void checkAnswersForDemObasPattern5(SOOSA const& soosa);
void checkAnswersForSpecialUnitsPattern1(SOOSA const& soosa);
void checkAnswersForSpecialUnitsPattern2(SOOSA const& soosa);
void checkAnswersForSpecialUnitsPattern3(SOOSA const& soosa);
void checkAnswersForEmptyForm(SOOSA const& soosa);
InputConfiguration getInputConfigurationForCharityPayWards(std::string const& inputPath);
InputConfiguration getInputConfigurationForDemObas(std::string const& inputPath);
InputConfiguration getInputConfigurationForSpecialUnits(std::string const& inputPath);
SoosaConfiguration getSoosaConfiguration();
}  // namespace alba::soosa
