#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra {

class NumbersRetriever final : public BaseRetriever {
public:
    void retrieveFromConstant(Constant const& constant) override;
    void retrieveFromVariable(Variable const& variable) override;
    void retrieveFromMonomial(Monomial const& monomial) override;
    [[nodiscard]] AlbaNumbersSet const& getNumbers() const;

private:
    AlbaNumbersSet m_numbers;
};

}  // namespace alba::algebra
