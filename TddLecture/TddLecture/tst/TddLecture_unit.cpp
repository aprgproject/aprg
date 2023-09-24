#include <TddLecture.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(SampleTest, SampleTest1) {
    TddLecture::UnsignedInts const oneToTen(TddLecture::getUnsignedIntsOneToTen());

    // ASSERT_EQ(10, oneToTen.size()); // this will fail
}

}  // namespace alba
