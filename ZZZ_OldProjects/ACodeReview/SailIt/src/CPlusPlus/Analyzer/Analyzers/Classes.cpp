#include <CPlusPlus/Analyzer/Findings/TemporaryFindings.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzer.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzerTemplateFunctions.hpp>
#include <CPlusPlus/Database/CPlusPlusDatabase.hpp>
#include <CPlusPlus/Term/TermChecker.hpp>

#include <array>
#include <iostream>

using namespace std;

namespace codeReview {

bool TermAnalyzer::isModifiedDueToClasses(Looper const& startLooper) {
    DBGPRINT1("isModifiedDueToClasses");
    bool isModified = true;
    if (isModifiedDueToClassDeclaration(startLooper)) {
        ;
    } else if (isModifiedDueToClassDefinition(startLooper)) {
        ;
    } else if (isModifiedDueToCStyleStructDefinition(startLooper)) {
        ;
    } else if (isModifiedDueToCStyleStructArrayDefinition(startLooper)) {
        ;
    } else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToClassDeclaration(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToClassDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 4> const termCheckers{
        TermChecker({Term(TermType::Keyword, "class"), Term(TermType::Keyword, "struct")}),
        TermChecker(Term(TermType::WhiteSpace)), TermChecker(Term(TermType::Identifier)),
        TermChecker(Term(TermType::Operator, ";"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        m_database.addClass(terms[2].getString());
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToClassDefinition(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker({Term(TermType::Keyword, "class"), Term(TermType::Keyword, "struct")}),
        TermChecker(Term(TermType::WhiteSpace)), TermChecker(Term(TermType::Identifier))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        Looper afterSemiColon(compareLooper);
        if (isBothBracesFoundWithSemicolonAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces, afterSemiColon)) {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            VectorOfTerms terms(getTerms(startLooper, termCheckers));
            m_database.performInClass(
                terms[2].getString(), [&]() { analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1)); });
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterSemiColon);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToCStyleStructDefinition(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 1> const expectedTerms{Term(TermType::Keyword, "struct")};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces)) {
            Looper afterClosingBracesAndNewLine(afterClosingBraces);
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBracesAndNewLine);
            Looper afterSemiColon(afterClosingBracesAndNewLine);
            array<Term, 2> const expectedTermsAfterBraces{Term(TermType::Identifier), Term(TermType::Operator, ";")};
            if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                    afterSemiColon, expectedTermsAfterBraces)) {
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
                VectorOfTerms terms(getTerms(afterClosingBracesAndNewLine, expectedTermsAfterBraces));
                m_database.performInClass(terms[0].getString(), [&]() {
                    analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1));
                });
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToCStyleStructArrayDefinition(Looper const& startLooper) {
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 1> const expectedTerms{Term(TermType::Keyword, "struct")};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces)) {
            Looper afterClosingBracesAndNewLine(afterClosingBraces);
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterClosingBracesAndNewLine);
            Looper afterSemiColon(afterClosingBracesAndNewLine);
            array<Term, 5> const expectedTermsAfterBraces{
                Term(TermType::Identifier), TermChecker(Term(TermType::Operator, "[")), Term(TermType::Constant_Number),
                Term(TermType::Operator, "]"), Term(TermType::Operator, ";")};
            if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                    afterSemiColon, expectedTermsAfterBraces)) {
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
                VectorOfTerms terms(getTerms(afterClosingBracesAndNewLine, expectedTermsAfterBraces));
                string const variableAndClassName(terms[0].getString());
                m_database.performInClass(variableAndClassName, [&]() {
                    analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1));
                });

                CPlusPlusType elementType(
                    m_database.getTemplateClassReference(variableAndClassName).getTypeReference());
                CPlusPlusTemplateClass& cStyleArrayTemplateClass =
                    m_database.getTemplateClassReference("__CStyleArray");
                CPlusPlusClassTemplateSignature cPlusPlusClassTemplateSignature;
                cPlusPlusClassTemplateSignature.addParameter(elementType, "ElementType");
                CPlusPlusType instantiationType(
                    cStyleArrayTemplateClass.getTemplateClassInstantiationType(cPlusPlusClassTemplateSignature));
                m_database.addVariable(variableAndClassName, instantiationType);

                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

}  // namespace codeReview
