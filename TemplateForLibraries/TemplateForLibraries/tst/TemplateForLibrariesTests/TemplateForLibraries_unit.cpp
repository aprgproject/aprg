#include <TemplateForLibraries/TemplateForLibraries.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, DISABLED_SampleTest1) {
    TemplateForLibraries const entity;
    EXPECT_EQ(0, entity.getSample());
}

}  // namespace alba
