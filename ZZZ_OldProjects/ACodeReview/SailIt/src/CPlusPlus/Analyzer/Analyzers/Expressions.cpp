#include <CPlusPlus/Analyzer/Findings/TemporaryFindings.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzer.hpp>
#include <CPlusPlus/Analyzer/TermAnalyzerTemplateFunctions.hpp>
#include <CPlusPlus/Database/CPlusPlusDatabase.hpp>
#include <CPlusPlus/Term/TermChecker.hpp>

#include <array>
#include <iostream>

using namespace std;

namespace codeReview {

void TermAnalyzer::simplifyExpressions(Looper const& startLooper) {
    Looper conditionLooper(startLooper);
    LooperIndex previousUpdatedIndexForMacro(startLooper.getCurrentIndex());
    LooperIndex previousUpdatedIndexForOthers(startLooper.getCurrentIndex());
    LooperIndex previousModifiedIndex(startLooper.getCurrentIndex());
    m_findingsBuffer.createNewTemporaryFindingsBuffer();
    while (conditionLooper.isNotFinished()) {
        DBGPRINT2(
            "simplifyExpressions file=[" << m_fileName << "] conditionLooper:[" << conditionLooper << " size:"
                                         << m_terms.size() << " " << conditionLooper.getContentReference() << "]");
        clearFlagsForAnotherIteration();
        if (isModifiedDueToUpdatedIdentifiers(
                conditionLooper, previousUpdatedIndexForMacro, previousUpdatedIndexForOthers)) {
            ;
        } else if (isModifiedDueToExpressions(conditionLooper)) {
            ;
        } else {
        }
        updateAfterOneIteration(conditionLooper, previousModifiedIndex);
    }
    m_findingsBuffer.saveCurrentFindings();
    m_findingsBuffer.deleteCurrentBuffer();
}

void TermAnalyzer::simplifyPrimitiveTypesForCurrentStatement(Looper const& startLooper) {
    Looper conditionLooper(startLooper);
    LooperIndex previousUpdatedIndexForMacro(startLooper.getCurrentIndex());
    LooperIndex previousUpdatedIndexForOthers(startLooper.getCurrentIndex());
    LooperIndex previousModifiedIndex(startLooper.getCurrentIndex());
    m_findingsBuffer.createNewTemporaryFindingsBuffer();
    while (conditionLooper.isNotFinished()) {
        DBGPRINT2(
            "simplifyPrimitiveTypesForCurrentStatement file=[" << m_fileName << "] conditionLooper:[" << conditionLooper
                                                               << " size:" << m_terms.size() << " "
                                                               << conditionLooper.getContentReference() << "]");
        clearFlagsForAnotherIteration();
        if (isModifiedDueToUpdatedIdentifiers(
                conditionLooper, previousUpdatedIndexForMacro, previousUpdatedIndexForOthers)) {
            ;
        } else if (isModifiedDueToMultipleTypes(conditionLooper)) {
            ;
        } else if (conditionLooper.getContentReference() == Term(TermType::Operator, ";")) {
            break;
        } else {
        }
        updateAfterOneIteration(conditionLooper, previousModifiedIndex);
    }
    m_findingsBuffer.saveCurrentFindings();
    m_findingsBuffer.deleteCurrentBuffer();
}

bool TermAnalyzer::isModifiedDueToExpressions(Looper const& startLooper) {
    DBGPRINT1("isModifiedDueToExpressions");
    bool isModified = true;
    if (isModifiedDueToScopeOperator(startLooper)) {
        ;
    } else if (isModifiedDueToSuffixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToPeriodOperator(startLooper)) {
        ;
    } else if (isModifiedDueToArrowOperator(startLooper)) {
        ;
    } else if (isModifiedDueToFunctionCall(startLooper)) {
        ;
    } else if (isModifiedDueToBracketOperator(startLooper)) {
        ;
    } else if (isModifiedDueToRelationalPrefixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToIncrementDecrementPrefixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToIndirectionPrefixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToAddressOfPrefixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToBiDirectionalRelationalOperator(startLooper)) {
        ;
    } else if (isModifiedDueToBiDirectionalOperator(startLooper)) {
        ;
    } else if (isModifiedDueToParenthesesWithValue(startLooper)) {
        ;
    } else if (isModifiedDueToPrefixOperator(startLooper)) {
        ;
    } else if (isModifiedDueToTypeSimplification(startLooper)) {
        ;
    } else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToScopeOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToScopeOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker({Term(TermType::Class), Term(TermType::Namespace)}), TermChecker(Term(TermType::Operator, "::")),
        TermChecker(
            {Term(TermType::Class), Term(TermType::Namespace), Term(TermType::Variable), Term(TermType::FunctionName),
             Term(TermType::Type), Term(TermType::Identifier)})};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, terms[2].getTermType(), terms[2].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToSuffixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToSuffixOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isLValue), TermChecker(TermCheckerType::isIncrementDecrementOperator)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(
            startLooper, compareLooper, TermType::Value_RValue_CanBeALine, terms[0].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToPeriodOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPeriodOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(TermCheckerType::isValue), TermChecker(Term(TermType::Operator, ".")),
        TermChecker(Term(TermType::Identifier))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, terms[0].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToArrowOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToArrowOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(TermCheckerType::isValue), TermChecker(Term(TermType::Operator, "->")),
        TermChecker(Term(TermType::Identifier))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, terms[0].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToFunctionCall(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToFunctionCall");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 1> const expectedTerms{Term(TermType::FunctionName)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        Looper afterOpeningParenthesis(compareLooper);
        Looper afterClosingParenthesis(compareLooper);
        if (isBothParenthesesFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningParenthesis, afterClosingParenthesis)) {
            CPlusPlusFunction& cPlusPlusFunction(
                m_database.getFunctionReferenceWithAlias(startLooper.getContentReference().getString()));
            CPlusPlusFunctionSignature cPlusPlusFunctionSignature;
            fillFunctionSignatureFromFunctionCall(
                Looper(afterOpeningParenthesis, afterClosingParenthesis - 1), cPlusPlusFunctionSignature);
            if (!cPlusPlusFunction.isFunctionSignatureExistBasedFromFunctionCall(cPlusPlusFunctionSignature)) {
                addFinding(
                    constructFileLocator(__FILE__, __LINE__),
                    "The signature in function call does not match the signature in declaration", compareLooper);
            }
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTermWithValueType(
                startLooper, afterClosingParenthesis, TermType::Value_RValue_CanBeALine,
                cPlusPlusFunctionSignature.getReturnTypeReference());
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToBracketOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToBracketOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 1> const expectedTerms{Term(TermType::Variable)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        Looper afterOpeningBracket(compareLooper);
        Looper afterClosingBracket(compareLooper);
        if (isBothBracketsFoundAndMoveLoopers<LooperConnector::WhiteSpaceAndNewLine>(
                compareLooper, afterOpeningBracket, afterClosingBracket)) {
            CPlusPlusFunctionSignature cPlusPlusFunctionSignature;
            fillFunctionSignatureFromFunctionCall(
                Looper(afterOpeningBracket, afterClosingBracket - 1), cPlusPlusFunctionSignature);
            CPlusPlusType bracketUserType(startLooper.getContentReference().getValueType());
            CPlusPlusType returnType(bracketUserType);
            string const typeName = bracketUserType.getTypeName();
            if (m_database.isClassWithAlias(typeName)) {
                CPlusPlusFunctionOptional functionOptional(
                    m_database.getFunctionOptionalInClass(typeName, "operator[]"));
                if (functionOptional) {
                    returnType = functionOptional.getReference().getReturnTypeWithSignature(cPlusPlusFunctionSignature);
                }
            } else if (
                bracketUserType.isTemplateClassInstantiation() && m_database.isTemplateClassWithAlias(typeName)) {
                CPlusPlusFunctionOptional functionOptional(m_database.getFunctionOptionalInTemplateClass(
                    typeName, "operator[]", bracketUserType.getTemplateInstantiationIndex()));
                if (functionOptional) {
                    returnType = functionOptional.getReference().getReturnTypeWithSignature(cPlusPlusFunctionSignature);
                }
            }
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTermWithValueType(
                startLooper, afterClosingBracket, TermType::Value_RValue_CanBeALine, returnType);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToRelationalPrefixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPrefixRelationalOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isRelationalPrefixOperator), TermChecker(TermCheckerType::isLValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(
            startLooper, compareLooper, TermType::Value_RValue, CPlusPlusType("bool", CPlusPlusTypeType::Primitive));
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToIncrementDecrementPrefixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPrefixRelationalOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isIncrementDecrementOperator), TermChecker(TermCheckerType::isLValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(
            startLooper, compareLooper, TermType::Value_RValue_CanBeALine, terms[1].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToIndirectionPrefixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPrefixOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(Term(TermType::Operator, "*")), TermChecker(TermCheckerType::isValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        CPlusPlusType type(terms[1].getValueType());
        type.decrementPointerCount();
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, type);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToAddressOfPrefixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPrefixOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(Term(TermType::Operator, "&")), TermChecker(TermCheckerType::isValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        CPlusPlusType type(terms[1].getValueType());
        type.incrementPointerCount();
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, type);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToPrefixOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToPrefixOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isPrefixOperator), TermChecker(TermCheckerType::isValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        CPlusPlusType type(terms[1].getValueType());
        type.decrementPointerCount();
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, type);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToBiDirectionalRelationalOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToBiDirectionalRelationalOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 5> const termCheckers{
        TermChecker(TermCheckerType::isValue), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isRelationalBiDirectionalOperator), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        if (!CheckerHelpers::isConstant(terms[0]) && CheckerHelpers::isConstant(terms[4])) {
            addFinding(constructFileLocator(__FILE__, __LINE__), "Not yoda style in comparison", startLooper);
        }
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(
            startLooper, compareLooper, TermType::Value_RValue, CPlusPlusType("bool", CPlusPlusTypeType::Primitive));
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToBiDirectionalOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToBiDirectionalOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 5> const termCheckers{
        TermChecker(TermCheckerType::isValue), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isBiDirectionalOperator), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isValue)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        if (CheckerHelpers::isConstant(terms[0]) && !CheckerHelpers::isConstant(terms[4])) {
            addFinding(
                constructFileLocator(__FILE__, __LINE__), "Constants should be after the bidirectional operation",
                startLooper);
        }
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, terms[0].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToParenthesesWithValue(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToParenthesesWithValue");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(Term(TermType::Operator, "(")), TermChecker(TermCheckerType::isValue),
        TermChecker(Term(TermType::Operator, ")"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        // check if parenthesis is redundant, think of an algorithm on how to do that.
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Value_RValue, terms[1].getValueType());
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeSimplification(Looper const& startLooper) {
    bool isModified = true;
    if (isModifiedDueToMultipleTypes(startLooper)) {
        ;
    } else if (isModifiedDueToTypeWithConstQualifier(startLooper)) {
        ;
    } else if (isModifiedDueToTypeWithConstQualifierInvalidPosition(startLooper)) {
        ;
    } else if (isModifiedDueToTypeWithDereferenceOperator(startLooper)) {
        ;
    } else if (isModifiedDueToTypeWithPointerOperator(startLooper)) {
        ;
    } else if (isModifiedDueToTypeWithExternKeyword(startLooper)) {
        ;
    } else {
        isModified = false;
    }
    return isModified;
}

bool TermAnalyzer::isModifiedDueToMultipleTypes(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToMultiplePrimitiveTypes");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<Term, 3> const expectedTerms{Term(TermType::Type), Term(TermType::WhiteSpace), Term(TermType::Type)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, expectedTerms)) {
        VectorOfTerms terms(getTerms(startLooper, expectedTerms));
        CPlusPlusType& type1(terms[0].getValueTypeReference());
        CPlusPlusType& type2(terms[2].getValueTypeReference());
        if (areTheTypesValidForCombination(type1, type2)) {
            type1.setTypeName(type1.getTypeName() + " " + type2.getTypeName());
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Type, type1);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeWithConstQualifier(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeWithConstQualifier");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(Term(TermType::Keyword, "const"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        CPlusPlusType type(terms[0].getValueType());
        if (type.isNotAPointerOrReference()) {
            addFinding(
                constructFileLocator(__FILE__, __LINE__),
                "Const qualifier should be before pointer or reference operator", startLooper);
        }
        type.setAsConst();
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Type, type);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeWithConstQualifierInvalidPosition(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeWithConstQualifierInvalidPosition");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(Term(TermType::Keyword, "const")), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isCPlusPlusType)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        addFinding(constructFileLocator(__FILE__, __LINE__), "Const qualifier should be after the type", startLooper);
        CPlusPlusType type(terms[2].getValueTypeReference());
        type.setAsConst();
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Type, type);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeWithDereferenceOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeWithDereferenceOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType), TermChecker(Term(TermType::Operator, "&"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        CPlusPlusType type(terms[0].getValueTypeReference());
        if (type.isNotAPointerOrReference()) {
            type.setAsReference();
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Type, type);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeWithPointerOperator(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeWithPointerOperator");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 2> const termCheckers{
        TermChecker(TermCheckerType::isCPlusPlusType), TermChecker(Term(TermType::Operator, "*"))};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        VectorOfTerms terms(getTerms(startLooper, termCheckers));
        CPlusPlusType type(terms[0].getValueTypeReference());
        if (!type.isReference()) {
            type.incrementPointerCount();
            temporaryFindings.copyCurrentFindings(m_findings);
            combineToASingleTermWithValueType(startLooper, compareLooper, TermType::Type, type);
            m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
            return true;
        }
    }
    return false;
}

bool TermAnalyzer::isModifiedDueToTypeWithExternKeyword(Looper const& startLooper) {
    DBGPRINT2("isModifiedDueToTypeWithExternKeyword");
    TemporaryFindings temporaryFindings(m_findingsBuffer);
    Looper compareLooper(startLooper);
    array<TermChecker, 3> const termCheckers{
        TermChecker(Term(TermType::Keyword, "extern")), TermChecker(Term(TermType::WhiteSpace)),
        TermChecker(TermCheckerType::isCPlusPlusType)};
    if (isMultiLineComparisonSatisfiedThenMoveLooper<LooperConnector::None>(compareLooper, termCheckers)) {
        temporaryFindings.copyCurrentFindings(m_findings);
        combineToASingleTerm(startLooper, compareLooper - 1, TermType::ProcessedTerm);
        m_moveBackType = MoveBackType::GotoPreviousModifiedTerm;
        return true;
    }
    return false;
}

bool TermAnalyzer::areTheTypesValidForCombination(CPlusPlusType const& type1, CPlusPlusType const& type2) {
    if (type1.isPrimitive() && type1.isNotAPointerOrReference() && type2.isPrimitive() &&
        type2.isNotAPointerOrReference()) {
        string const typeName1(type1.getTypeName());
        string const typeName2(type2.getTypeName());
        if (typeName1 == typeName2) {
            if ("unsigned" == typeName1 || "signed" == typeName1) {
                return false;
            }
        }
        return true;
    }
    return false;
}

}  // namespace codeReview
