#pragma once

#include <Algebra/Equation/Equation.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <string>

namespace alba::algebra {

class EquationBuilder {
public:
    explicit EquationBuilder(std::string const& equationInString);
    // rule of zero
    [[nodiscard]] Equation getEquation() const;
    [[nodiscard]] stringHelper::strings const& getTermStrings() const;
    [[nodiscard]] stringHelper::strings const& getEquationOperatorStrings() const;

private:
    void splitAndSaveOperatorAndTermStrings(std::string const& equationInString);
    stringHelper::strings m_termStrings;
    stringHelper::strings m_equationOperatorStrings;
};

}  // namespace alba::algebra
