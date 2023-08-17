#include "KickStart_2021_RoundA_P2_LShapedPlots.hpp"
#include <Fake/FakeObjects.hpp>

#include <gtest/gtest.h>

using namespace alba;
using namespace std;

namespace KickStart_2021_RoundA_P2_LShapedPlots {

TEST(KickStart_2021_RoundA_P2_LShapedPlotsTest, DISABLED_Test1) {
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

}  // namespace KickStart_2021_RoundA_P2_LShapedPlots
