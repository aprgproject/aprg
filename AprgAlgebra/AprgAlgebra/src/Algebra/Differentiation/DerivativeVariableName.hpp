#pragma once

#include <string>

namespace alba::algebra {

class DerivativeVariableName {
public:
    explicit DerivativeVariableName(std::string const& derivativeVariableInLeibnizNotation);
    DerivativeVariableName(
        int const differentiationLevel, std::string const& baseVariable, std::string const& dependentVariable);
    DerivativeVariableName(int const differentiationLevel, std::string&& baseVariable, std::string&& dependentVariable);
    [[nodiscard]] std::string const& getBaseVariable() const;
    [[nodiscard]] std::string const& getDependentVariable() const;
    [[nodiscard]] std::string getNameInLeibnizNotation() const;
    [[nodiscard]] int getDifferentiationLevel() const;
    [[nodiscard]] bool isValid() const;
    void differentiate();

private:
    void processNumerator(std::string const& numerator);
    void processDenominator(std::string const& denominator);
    bool m_isValid{false};
    int m_differentiationLevel{};
    std::string m_baseVariable;
    std::string m_dependentVariable;
};

}  // namespace alba::algebra
