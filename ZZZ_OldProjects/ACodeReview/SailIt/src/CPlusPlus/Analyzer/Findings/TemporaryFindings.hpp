#pragma once

#include <CPlusPlus/Analyzer/Findings/FindingsBuffer.hpp>

namespace codeReview {

class TemporaryFindings {
public:
    explicit TemporaryFindings(FindingsBuffer& findingsBuffer);
    ~TemporaryFindings();
    void copyCurrentFindings(Findings& findings);
    void saveCurrentFindings();

private:
    FindingsBuffer& m_findingsBuffer;
};

}  // namespace codeReview
