#include <BooleanAlgebra/Algorithm/QuineMcCluskey/Utilities/Utilities.hpp>

#include <gtest/gtest.h>

namespace alba::booleanAlgebra {

TEST(QuineMcCluskeyUtilitiesTest, GetLogicalValueWorks) {
    EXPECT_EQ(LogicalValue::False, getLogicalValue(false));
    EXPECT_EQ(LogicalValue::True, getLogicalValue(true));
}

}  // namespace alba
