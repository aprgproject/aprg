#include <Algorithm/Random/KnuthShuffle.hpp>

#include <gtest/gtest.h>

#include <set>

using namespace std;

namespace alba::algorithm {

namespace {
using Characters = vector<char>;
using CharactersSet = set<char>;
using CharactersShuffler = KnuthShuffle<Characters>;
}  // namespace

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersShuffler const shuffler;
    Characters emptyContainer;

    shuffler.shuffleWhileMovingForward(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersUsingOneValueExample) {
    CharactersShuffler const shuffler;
    Characters valuesToShuffle{'E'};

    shuffler.shuffleWhileMovingForward(valuesToShuffle);

    Characters const valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToShuffle);
}

TEST(KnuthShuffleTest, ShuffleWhileMovingForwardWorksOnCharactersUsingExample1) {
    CharactersShuffler const shuffler;
    Characters const givenValues{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Characters valuesToShuffle(givenValues);

    shuffler.shuffleWhileMovingForward(valuesToShuffle);

    CharactersSet const valuesSetToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_NE(givenValues, valuesToShuffle);
    EXPECT_EQ(valuesSetToExpect, CharactersSet(valuesToShuffle.cbegin(), valuesToShuffle.cend()));
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersAndDoesNotCrashUsingEmptyExample) {
    CharactersShuffler const shuffler;
    Characters emptyContainer;

    shuffler.shuffleWhileMovingBackward(emptyContainer);

    EXPECT_TRUE(emptyContainer.empty());
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersUsingOneValueExample) {
    CharactersShuffler const shuffler;
    Characters valuesToShuffle{'E'};

    shuffler.shuffleWhileMovingBackward(valuesToShuffle);

    Characters const valuesToExpect{'E'};
    EXPECT_EQ(valuesToExpect, valuesToShuffle);
}

TEST(KnuthShuffleTest, ShuffleWhileMovingBackwardWorksOnCharactersUsingExample1) {
    CharactersShuffler const shuffler;
    Characters const givenValues{'S', 'O', 'R', 'T', 'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    Characters valuesToShuffle(givenValues);

    shuffler.shuffleWhileMovingBackward(valuesToShuffle);

    CharactersSet const valuesSetToExpect{'A', 'E', 'E', 'L', 'M', 'O', 'P', 'R', 'S', 'T', 'X'};
    EXPECT_NE(givenValues, valuesToShuffle);
    EXPECT_EQ(valuesSetToExpect, CharactersSet(valuesToShuffle.cbegin(), valuesToShuffle.cend()));
}

}  // namespace alba::algorithm
