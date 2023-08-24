#pragma once

#include <Algebra/Retrieval/BaseRetriever.hpp>
#include <Common/Math/Number/AlbaNumberTypes.hpp>

namespace alba::algebra {

class ExponentsRetriever final : public BaseRetriever {
public:
    [[nodiscard]] AlbaNumbersSet const& getExponents() const;

    void retrieveFromMonomial(Monomial const& monomial) override;

private:
    AlbaNumbersSet m_exponents;
};

}  // namespace alba::algebra
