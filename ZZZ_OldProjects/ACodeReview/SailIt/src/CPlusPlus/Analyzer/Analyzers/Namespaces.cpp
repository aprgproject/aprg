#include <CPlusPlus/Analyzer/Findings/TemporaryFindings.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzer.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzerTemplateFunctions.hpp>
#include <CPlusPlus/Database/CPlusPlusDatabase.hpp>
#include <CPlusPlus/Term/TermChecker.hpp>

#include <array>
#include <iostream>

using namespace std;

namespace codeReview {

bool TermAnalyzer::isModifiedDueToNamespaces(Looper const& startLooper) {
    DBGPRINT1("isModifiedDueToNamespaces");
    bool isModified = true;
    if (isModifiedDueToNamespaceDefinition(startLooper))
        ;
    else if (isModifiedDueToExternBlock(startLooper))
        ;
    else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToNamespaceDefinition(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{
        Term(TermType::Keyword, "namespace"), Term(TermType::WhiteSpace), Term(TermType::Identifier)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces)) {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            VectorOfTerms terms(getTerms(startLooper, expectedTerms));
            m_database.performInNamespace(
                terms[2].getString(), [&]() { analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1)); });
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterClosingBraces, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToExternBlock(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(Term(TermType::Keyword, "extern")), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker({Term(TermType::Constant_String, "\"C\""), Term(TermType::Constant_String, "\"C++\"")})};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces)) {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            m_database.performInNewScope(
                [&]() { analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1)); });
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBraces);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterClosingBraces, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

}  // namespace codeReview
