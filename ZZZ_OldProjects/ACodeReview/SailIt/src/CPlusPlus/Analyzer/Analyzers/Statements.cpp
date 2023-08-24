#include <CPlusPlus/Analyzer/Findings/TemporaryFindings.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzer.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzerTemplateFunctions.hpp>
#include <CPlusPlus/Database/CPlusPlusDatabase.hpp>
#include <CPlusPlus/Term/TermChecker.hpp>

#include <array>
#include <iostream>

using namespace std;

namespace codeReview {

bool TermAnalyzer::isModifiedDueToStatements(Looper const& startLooper) {
    DBGPRINT1("isModifiedDueToStatements");
    bool isModified = true;
    if (isModifiedDueToVariableDeclaration(startLooper)) {
        ;
    } else if (isModifiedDueToCStyleArrayDeclaration(startLooper)) {
        ;
    } else if (isModifiedDueToAssignment(startLooper)) {
        ;
    } else if (isModifiedDueToRValueCanBeALine(startLooper)) {
        ;
    } else if (isModifiedDueToUsingNamespaceKeyword(startLooper)) {
        ;
    } else if (isModifiedDueToTypeDefStatement(startLooper)) {
        ;
    } else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToVariableDeclaration(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToVariableDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType), TermChecker(Term(TermType::WhiteSpace))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        CPlusPlusType type(startLooper.getContentReference().getValueTypeReference());
        VectorOfStrings variableNames;
        if (areVariableFoundForVariableDeclarationAndMoveLooper(compareLooper, variableNames)) {
            for (string const& variableName : variableNames) {
                m_database.addVariable(variableName, type);
            }
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(
                compareLooper);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToCStyleArrayDeclaration(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToVariableDeclaration");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 7> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType),
        TermChecker(Term(TermType::WhiteSpace)),
        TermChecker({Term(TermType::Identifier), Term(TermType::Variable)}),
        TermChecker(Term(TermType::Operator, "[")),
        TermChecker(Term(TermType::Constant_Number)),
        TermChecker(Term(TermType::Operator, "]")),
        TermChecker(Term(TermType::Operator, ";"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        string const variableName(terms[2].getString());
        CPlusPlusType elementType(startLooper.getContentReference().getValueTypeReference());
        CPlusPlusTemplateClass& cStyleArrayTemplateClass = m_database.getTemplateClassReference("__CStyleArray");
        CPlusPlusClassTemplateSignature cPlusPlusClassTemplateSignature;
        cPlusPlusClassTemplateSignature.addParameter(elementType, "ElementType");
        CPlusPlusType instantiationType(
            cStyleArrayTemplateClass.getTemplateClassInstantiationType(cPlusPlusClassTemplateSignature));

        m_database.addVariable(variableName, instantiationType);
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToAssignment(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToAssignment");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 6> const termCheckers{
        TermChecker(TermCheckerType::isValue),
        TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isAssignmentOperator),
        TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isValue),
        TermChecker(Term(TermType::Operator, ";"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToRValueCanBeALine(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToRValueCanBeALine");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 2> const expectedTerms{Term(TermType::Value_RValue_CanBeALine), Term(TermType::Operator, ";")};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToUsingNamespaceKeyword(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToUsingNamespaceKeyword");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 6> const expectedTerms{
        Term(TermType::Keyword, "using"), Term(TermType::WhiteSpace), Term(TermType::Keyword, "namespace"),
        Term(TermType::WhiteSpace),       Term(TermType::Namespace),  Term(TermType::Operator, ";")};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(compareLooper);
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        m_database.addUsingNamespace(terms[4].getString());
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefStatement(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeDefStatement");
    Looper compareLooper(startLooper);
    array<Term, 2> const termCheckers{Term(TermType::Keyword, "typedef"), Term(TermType::WhiteSpace)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        simplifyPrimitiveTypesForCurrentStatement(compareLooper);
        bool isModified = true;
        if (isModifiedDueToTypeDefWithNormalParameters(startLooper, compareLooper)) {
            ;
        } else if (isModifiedDueToTypeDefWithStructAndBracesCStyleStatement(startLooper, compareLooper)) {
            ;
        } else {
            isModified = false;
        }
        return isModified;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefWithNormalParameters(Looper const& startLooper, Looper const& nextLooper) {
    DBGPRINT2("isModifiedDueToTypeDefWithNormalParameters");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(nextLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType), TermChecker(Term(TermType::WhiteSpace))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
            compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(nextLooper, termCheckers));
        CPlusPlusType const& cPlusPlusType(terms[0].getValueTypeReference());
        MapOfCPlusPlusTypesForTypedef typeMap;
        if (areTypesFoundForTypedefThenFillAndMoveLooper(compareLooper, cPlusPlusType, typeMap)) {
            for (auto const& typePair : typeMap) {
                m_database.addType(typePair.first, typePair.second);
            }
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(
                compareLooper);
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTerm(startLooper, compareLooper, TermType::ProcessedTerm);
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeDefWithStructAndBracesCStyleStatement(
    Looper const& startLooper, Looper const& nextLooper) {
    DBGPRINT2("isModifiedDueToCStyleTypeDefWtihStructWithBracesStatement");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(nextLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(Term(TermType::Keyword, "struct")), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker({Term(TermType::Identifier), Term(TermType::Class)})};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
            compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(nextLooper, termCheckers));
        string structName(string("struct ") + terms[2].getString());
        Looper afterOpeningBraces(compareLooper);
        Looper afterClosingBraces(compareLooper);
        if (isBothBracesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBraces, afterClosingBraces)) {
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterOpeningBraces);
            Looper afterSemiColon(afterClosingBraces);
            incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::None>(afterSemiColon);
            CPlusPlusType cPlusPlusType(structName, CPlusPlusTypeType::Class);
            MapOfCPlusPlusTypesForTypedef typeMap;
            if (areTypesFoundForTypedefThenFillAndMoveLooper(afterSemiColon, cPlusPlusType, typeMap)) {
                m_database.performInClass(
                    structName, [&]() { analyzeThisScope(Looper(afterOpeningBraces, afterClosingBraces - 1)); });
                for (auto const& typePair : typeMap) {
                    m_database.addType(typePair.first, typePair.second);
                }
                incrementLooperIfWhiteSpaceAndOneNewLine<FindingsToAdd::ExpectsNewLineAndUnexpectsWhiteSpace>(
                    afterSemiColon);
                temporaryFindings.copyCurrentFindings(m_findings);
                combineToASingleTerm(startLooper, afterSemiColon, TermType::ProcessedTerm);
                return true;
            }
        }
    }
    return false;
}

bool TermAnalyzer::areVariableFoundForVariableDeclarationAndMoveLooper(
    Looper& movableLooper, VectorOfStrings& variableNames) {
    array<TermChecker, 5> const variableWithValueChecker{
        TermChecker({Term(TermType::Identifier), Term(TermType::Variable)}), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isAssignmentOperator), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isValue)};
    array<TermChecker, 1> const variableChecker{TermChecker({Term(TermType::Identifier), Term(TermType::Variable)})};
    array<Term, 2> const separator{Term(TermType::Operator, ","), Term(TermType::WhiteSpace)};
    array<Term, 1> const finisher{Term(TermType::Operator, ";")};
    bool isNextVariableExpected(true);
    while (movableLooper.isNotFinished()) {
        Looper movableLooperCopy(movableLooper);
        if (isNextVariableExpected) {
            if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                    movableLooper, variableWithValueChecker)) {
                variableNames.emplace_back(movableLooperCopy.getContentReference().getString());
                isNextVariableExpected = false;
            } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                           movableLooper, variableChecker)) {
                variableNames.emplace_back(movableLooperCopy.getContentReference().getString());
                isNextVariableExpected = false;
            }
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                       movableLooper, separator)) {
            isNextVariableExpected = true;
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::WhiteSpaceAndNewLine>(
                       movableLooper, finisher)) {
            return true;
        }
        if (movableLooperCopy.getCurrentIndex() == movableLooper.getCurrentIndex()) {
            return false;
        }
    }
    return false;
}

bool TermAnalyzer::areTypesFoundForTypedefThenFillAndMoveLooper(
    Looper& movableLooper, CPlusPlusType const& type, MapOfCPlusPlusTypesForTypedef& typeMap) {
    array<TermChecker, 1> const typeChecker{
        TermChecker({Term(TermType::Identifier), Term(TermType::Type), Term(TermType::Class)})};
    array<TermChecker, 2> const typePointerChecker{
        TermChecker(Term(TermType::Operator, "*")),
        TermChecker({Term(TermType::Identifier), Term(TermType::Type), Term(TermType::Class)})};
    array<Term, 1> const separator1{Term(TermType::WhiteSpace)};
    array<Term, 1> const separator2{Term(TermType::Operator, ",")};
    array<Term, 1> const finisher{Term(TermType::Operator, ";")};
    bool isNextTypeExpected(true);
    while (movableLooper.isNotFinished()) {
        Looper movableLooperCopy(movableLooper);
        Looper afterOpeningParenthesis(movableLooper);
        Looper afterClosingParenthesis(movableLooper);
        if (isNextTypeExpected &&
            isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, typeChecker)) {
            typeMap.emplace(movableLooperCopy.getContentReference().getString(), type);
            isNextTypeExpected = false;
        } else if (
            isNextTypeExpected &&
            isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, typePointerChecker)) {
            VectorOfTerms terms(getTerms(movableLooperCopy, typePointerChecker));
            CPlusPlusType pointerType(type);
            pointerType.incrementPointerCount();
            typeMap.emplace(terms[1].getString(), pointerType);
            isNextTypeExpected = false;
        } else if (
            isNextTypeExpected && isBothParenthesesFoundAndMoveLoopers<LooperConnector::None>(
                                      movableLooper, afterOpeningParenthesis, afterClosingParenthesis)) {
            movableLooper.copyLooper(afterClosingParenthesis);
            isNextTypeExpected = false;
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, separator1)) {
            isNextTypeExpected = true;
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, separator2)) {
            isNextTypeExpected = true;
        } else if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(movableLooper, finisher)) {
            return true;
        } else {
            incrementLooperIfWhiteSpaceAndNewLine<FindingsToAdd::UnexpectsNewLineAndUnexpectsWhiteSpace>(movableLooper);
            if (movableLooperCopy.getCurrentIndex() == movableLooper.getCurrentIndex()) {
                return false;
            }
        }
    }
    return false;
}

}  // namespace codeReview
