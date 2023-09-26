#pragma once

#include <BooleanAlgebra/Term/TermTypes/BaseTermData.hpp>

#include <string>
#include <vector>

namespace alba::booleanAlgebra {

class VariableTerm : public BaseTermData {
public:
    VariableTerm();
    explicit VariableTerm(std::string const& variableName);
    VariableTerm operator~() const;
    bool operator==(VariableTerm const& second) const;
    bool operator!=(VariableTerm const& second) const;
    bool operator<(VariableTerm const& second) const;
    [[nodiscard]] std::string getVariableTermName() const;
    [[nodiscard]] bool isNegated() const;
    void setVariableTermName(std::string const& variableName);
    void negate();
    // rule of zero
    static VariableTerm createNegatedVariableTerm(std::string const& variableName);

private:
    void initializeIfNotEmpty();
    friend std::ostream& operator<<(std::ostream& out, VariableTerm const& variableTerm);
    std::string m_variableName;
    bool m_isNegated;
};

using VariableTerms = std::vector<VariableTerm>;

}  // namespace alba::booleanAlgebra
