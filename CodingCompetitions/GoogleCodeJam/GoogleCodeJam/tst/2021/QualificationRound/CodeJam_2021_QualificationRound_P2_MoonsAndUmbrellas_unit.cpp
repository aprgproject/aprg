#include "CodeJam_2021_QualificationRound_P2_MoonsAndUmbrellas.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace CodeJam_2021_QualificationRound_P2_MoonsAndUmbrellas {

TEST(CodeJam_2021_QualificationRound_P2_MoonsAndUmbrellasTest, DISABLED_Test1) {
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

}  // namespace CodeJam_2021_QualificationRound_P2_MoonsAndUmbrellas
