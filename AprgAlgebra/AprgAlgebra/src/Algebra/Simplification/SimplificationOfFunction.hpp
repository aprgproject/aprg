#pragma once

#include <Algebra/Term/TermTypes/Term.hpp>

namespace alba::algebra::Simplification {

class SimplificationOfFunction {
public:
    explicit SimplificationOfFunction(Function const& functionObject);
    explicit SimplificationOfFunction(Function&& functionObject);
    [[nodiscard]] Function getFunction() const;
    void simplify();

private:
    Function m_function;
};

}  // namespace alba::algebra::Simplification
