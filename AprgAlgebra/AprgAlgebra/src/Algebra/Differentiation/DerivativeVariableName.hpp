#pragma once

#include <string>

namespace alba::algebra {

class DerivativeVariableName {
public:
    DerivativeVariableName(
        int const differentiationLevel, std::string const& baseVariable, std::string const& dependentVariable);
    explicit DerivativeVariableName(std::string const& derivativeVariableInLeibnizNotation);

    [[nodiscard]] bool isValid() const;
    [[nodiscard]] int getDifferentiationLevel() const;
    [[nodiscard]] std::string const& getBaseVariable() const;
    [[nodiscard]] std::string const& getDependentVariable() const;
    [[nodiscard]] std::string getNameInLeibnizNotation() const;

    void differentiate();

private:
    void processNumerator(std::string const& numerator);
    void processDenominator(std::string const& denominator);
    bool m_isValid;
    int m_differentiationLevel;
    std::string m_baseVariable;
    std::string m_dependentVariable;
};

}  // namespace alba::algebra
