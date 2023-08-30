#pragma once

#include <CPlusPlus/Findings/Finding.hpp>

#include <map>
#include <string>

using std::multimap;
using std::pair;
using std::string;

namespace codeReview {
using MultiMapOfFindings = multimap<int, Finding>;
using FindingsPair = pair<int, Finding>;

class Findings {
public:
    MultiMapOfFindings& getMultiMapOfFindingsReference();

    void printFindings(ostream& outputStream);
    void printFindings(ostream& outputStream, string const& details);

    void addFinding(unsigned int const lineNumber, string const& fileLocator, string const& content);
    void addFinding(
        unsigned int const lineNumber, string const& fileLocator, string const& content, string const& locator);
    void copyFindings(Findings& findings);
    void clear();
    void setFileName(string const& fileName);

private:
    MultiMapOfFindings m_findings;
    string m_fileName;
};

}  // namespace codeReview
