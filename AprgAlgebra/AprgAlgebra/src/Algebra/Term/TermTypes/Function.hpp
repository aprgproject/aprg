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
    Function();
    Function(std::string const& functionName, BaseTerm const& baseTerm, EvaluationFunction const& evaluationFunction);
    Function(std::string&& functionName, BaseTerm&& baseTerm, EvaluationFunction&& evaluationFunction);
    // rule of five of six
    ~Function() override = default;
    Function(Function const& functionObject);
    Function(Function&& functionObject) noexcept = default;
    Function& operator=(Function const& functionObject);
    Function& operator=(Function&& functionObject) noexcept = default;
    bool operator==(Function const& second) const;
    bool operator!=(Function const& second) const;
    bool operator<(Function const& second) const;
    [[nodiscard]] AlbaNumber performFunctionAndReturnResultIfPossible() const;
    [[nodiscard]] BaseTerm const& getInputTerm() const;
    [[nodiscard]] EvaluationFunction const& getEvaluationFunction() const;
    [[nodiscard]] std::string getFunctionName() const;
    [[nodiscard]] std::string getDebugString() const;
    [[nodiscard]] bool isSimplified() const;
    void simplify();
    void setAsSimplified();
    void clearSimplifiedFlag();
    void clearAllInnerSimplifiedFlags();
    BaseTerm& getInputTermReference();

private:
    friend std::ostream& operator<<(std::ostream& out, Function const& functionObject);
    std::string m_functionName;
    BaseTermUniquePointer m_inputTermPointer;
    EvaluationFunction m_evaluationFunction;
    bool m_isSimplified{false};
};

}  // namespace alba::algebra
