#include <UniqueProblems/SpecialProblems/TowersOfHanoi.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(TowersOfHanoiTest, DISABLED_TransferDisksFromStartToFinishWorksWithOneDisk) {
    TowersOfHanoi const towersOfHanoi;

    towersOfHanoi.transferDisksFromStartToFinish(1);
}

TEST(TowersOfHanoiTest, DISABLED_TransferDisksFromStartToFinishWorksWithTwoDisks) {
    TowersOfHanoi const towersOfHanoi;

    towersOfHanoi.transferDisksFromStartToFinish(2);
}

TEST(TowersOfHanoiTest, DISABLED_TransferDisksFromStartToFinishWorksWithThreeDisks) {
    TowersOfHanoi const towersOfHanoi;

    towersOfHanoi.transferDisksFromStartToFinish(3);
}

TEST(TowersOfHanoiTest, DISABLED_TransferDisksFromStartToFinishWorksWith10Disks) {
    TowersOfHanoi const towersOfHanoi;

    towersOfHanoi.transferDisksFromStartToFinish(10);
}

}  // namespace alba
