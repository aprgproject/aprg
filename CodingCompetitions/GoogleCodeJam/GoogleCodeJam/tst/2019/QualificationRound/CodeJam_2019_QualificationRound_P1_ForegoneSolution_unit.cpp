#include "CodeJam_2019_QualificationRound_P1_ForegoneSolution.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2019_QualificationRound_P1_ForegoneSolution {

TEST(CodeJam_2019_QualificationRound_P1_ForegoneSolutionTest, Test1) {
    stringstream& inputStringStream(FakeObjects::getInstance().inputStringStream);
    stringstream& outputStringStream(FakeObjects::getInstance().outputStringStream);
    inputStringStream = stringstream();
    outputStringStream = stringstream();
    inputStringStream << ""
                         "\n"
                      << ""
                         "\n"
                      << ""
                         "\n"
                      << ""
                         "\n"
                      << endl;

    main();

    EXPECT_EQ(
        ""
        "\n"
        ""
        "\n"
        ""
        "\n"
        ""
        "\n",
        outputStringStream.str());
}

}  // namespace CodeJam_2019_QualificationRound_P1_ForegoneSolution
