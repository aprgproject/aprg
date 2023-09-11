#include <TddLecture.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, DISABLED_SampleTest1) { TddLecture const entity; }

TEST(SampleTest, SampleTest1) {
    TddLecture const entity;
    TddLecture::UnsignedInts const oneToTen(alba::TddLecture::getUnsignedIntsOneToTen());

    // ASSERT_EQ(10, oneToTen.size()); // this will fail
}

}  // namespace alba
