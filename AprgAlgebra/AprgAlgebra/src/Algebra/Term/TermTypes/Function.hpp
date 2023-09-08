#pragma once

#include <Algebra/Term/TermTypes/BaseTerm.hpp>
#include <Algebra/Term/TermTypes/BaseTermData.hpp>
#include <Algebra/Term/TermTypes/BaseTermPointers.hpp>
#include <Common/Math/Number/AlbaNumber.hpp>

#include <functional>
#include <string>

namespace alba::algebra {

class Function : public BaseTermData {
public:
    using EvaluationFunction = std::function<AlbaNumber(AlbaNumber const&)>;
    // rule of five of six
    ~Function() override = default;
    Function(Function&& functionObject) = default;
    Function& operator=(Function&& functionObject) = default;
    Function();
    Function(std::string const& functionName, BaseTerm const& baseTerm, EvaluationFunction const& evaluationFunction);
    Function(std::string const& functionName, BaseTerm&& baseTerm, EvaluationFunction const& evaluationFunction);
    Function(Function const& functionObject);
    Function& operator=(Function const& functionObject);
    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;
    [[nodiscard]] bool isSimplified() const;
    [[nodiscard]] std::string getFunctionName() const;
    [[nodiscard]] std::string getDebugString() const;
    [[nodiscard]] AlbaNumber performFunctionAndReturnResultIfPossible() const;
    [[nodiscard]] BaseTerm const& getInputTerm() const;
    [[nodiscard]] EvaluationFunction const& getEvaluationFunction() const;
    BaseTerm& getInputTermReference();
    void simplify();
    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();

private:
    friend std::ostream& operator<<(std::ostream& out, Function const& functionObject);
    std::string m_functionName;
    BaseTermUniquePointer m_inputTermPointer;
    EvaluationFunction m_evaluationFunction;
    bool m_isSimplified;
};

}  // namespace alba::algebra
