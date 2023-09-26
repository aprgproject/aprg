#pragma once

#include <Algebra/Term/TermTypes/BaseTermData.hpp>

#include <string>

namespace alba::algebra {

class Variable : public BaseTermData {
public:
    Variable() = default;
    explicit Variable(std::string const& variableName);
    explicit Variable(std::string&& variableName);
    // rule of zero
    bool operator==(Variable const& second) const;
    bool operator!=(Variable const& second) const;
    bool operator<(Variable const& second) const;
    [[nodiscard]] std::string getVariableName() const;
    void setVariableName(std::string const& variableName);

private:
    friend std::ostream& operator<<(std::ostream& out, Variable const& variable);
    std::string m_variableName;
};

}  // namespace alba::algebra
