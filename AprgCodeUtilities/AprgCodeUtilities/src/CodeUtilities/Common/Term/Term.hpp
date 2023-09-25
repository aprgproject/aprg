#pragma once

#include <CodeUtilities/Common/Term/TermType.hpp>

#include <ostream>
#include <string>
#include <vector>

namespace alba::CodeUtilities {

class Term {
public:
    Term(TermType const termType, std::string&& content);
    Term(TermType const termType, std::string const& content);
    bool operator==(Term const& term) const;
    bool operator!=(Term const& term) const;
    [[nodiscard]] TermType getTermType() const;
    [[nodiscard]] std::string getContent() const;
    [[nodiscard]] std::string getTermTypeString() const;
    void clear();
    void setTermType(TermType const termType);
    void setContent(std::string const& content);
    friend std::ostream& operator<<(std::ostream& out, Term const& term);

private:
    TermType m_termType;
    std::string m_content;
};

using Terms = std::vector<Term>;

}  // namespace alba::CodeUtilities
