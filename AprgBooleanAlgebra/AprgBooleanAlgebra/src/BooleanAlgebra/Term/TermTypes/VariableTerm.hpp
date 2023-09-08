#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

class VariableTerm : public BaseTermData {
public:
    explicit VariableTerm(std::string const& variableName);
    VariableTerm();
    bool operator==(VariableTerm const& second) const;
    bool operator!=(VariableTerm const& second) const;
    bool operator<(VariableTerm const& second) const;
    VariableTerm operator~() const;
    // rule of zero
    static VariableTerm createNegatedVariableTerm(std::string const& variableName);
    [[nodiscard]] bool isNegated() const;
    [[nodiscard]] std::string getVariableTermName() const;
    void setVariableTermName(std::string const& variableName);
    void negate();

private:
    void initializeIfNotEmpty();
    friend std::ostream& operator<<(std::ostream& out, VariableTerm const& variableTerm);
    std::string m_variableName;
    bool m_isNegated;
};

using VariableTerms = std::vector<VariableTerm>;

}  // namespace alba::booleanAlgebra
