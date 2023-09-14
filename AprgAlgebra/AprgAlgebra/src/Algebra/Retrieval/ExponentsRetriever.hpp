#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra {

class ExponentsRetriever final : public BaseRetriever {
public:
    void retrieveFromMonomial(Monomial const& monomial) override;
    [[nodiscard]] AlbaNumbersSet const& getExponents() const;

private:
    AlbaNumbersSet m_exponents;
};

}  // namespace alba::algebra
