#include <Common/Print/AlbaPrintFunctions.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

#include <array>
#include <deque>
#include <forward_list>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

TEST(AlbaPrintFunctionsTest, PrintLogHeaderWorks) {
    stringstream ssToVerify;

    printLogHeader(
        ssToVerify, "Drive:/Folder1/Folder2/Folder3/Folder4/Filename.txt", 265, "prefixVeryVeryVeryVeryVeryVerySuffix");

    string const actualPrintString(ssToVerify.str());
    int runningIndex = 0;
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "Filename.txt", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "prefix", runningIndex));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "Suffix", runningIndex));
}

TEST(AlbaPrintFunctionsTest, PrintCurrentDateTimeWorks) {
    stringstream ssToVerify;

    printCurrentDateTime(ssToVerify);

    EXPECT_FALSE(ssToVerify.str().empty());
}

TEST(AlbaPrintFunctionsTest, PrintStringAndShortenIfPossibleWorks) {
    stringstream ssToVerify;

    printStringAndShortenIfPossible(ssToVerify, "ThisISVeRYvERYVEryVerYveryVERYveRYVEryLoNG", 10, 10);

    EXPECT_EQ("ThisISVeRY...RYVEryLoNG", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithItemsThatCanPrint) {
    stringstream ssToVerify;
    constexpr int integerToTest = 500;

    printParameterWithName(ssToVerify, "name", integerToTest);

    EXPECT_EQ("name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithStrings) {
    stringstream ssToVerify;
    string const stringToTest = "std::string to test";

    printParameterWithName(ssToVerify, "name1", stringToTest);
    printParameterWithName(ssToVerify, "no name", "string literal to test");

    EXPECT_EQ(R"(name1 : ["std::string to test"]["string literal to test"])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPointer) {
    stringstream ssToVerify;
    int integerToTest = 500;

    printParameterWithName(ssToVerify, "name", &integerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithCharacterLiteral) {
    stringstream ssToVerify;

    printParameterWithName(ssToVerify, "name", "ThisIsACharacterLiteralSoNameIsNotIncluded");

    EXPECT_EQ(R"(["ThisIsACharacterLiteralSoNameIsNotIncluded"])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUniquePointer) {
    stringstream ssToVerify;
    unique_ptr<int> const pointerToTest(make_unique<int>(500));

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSharedPointer) {
    stringstream ssToVerify;
    shared_ptr<int> const pointerToTest(make_shared<int>(500));

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("*name : [500]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithWeakPointer) {
    stringstream ssToVerify;
    shared_ptr<int> const sharedPointer(make_shared<int>(500));
    weak_ptr<int> const pointerToTest(sharedPointer);

    printParameterWithName(ssToVerify, "name", pointerToTest);

    EXPECT_EQ("name has use count: [1]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithOptional) {
    stringstream ssToVerify;
    optional<int> const emptyOptional;
    optional<int> const nonEmptyOptional(300);

    printParameterWithName(ssToVerify, "name1", emptyOptional);
    ssToVerify << ", ";
    printParameterWithName(ssToVerify, "name2", nonEmptyOptional);

    EXPECT_EQ("name1 : [empty], name2 : [300]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPair) {
    stringstream ssToVerify;
    pair<int, char> const pairToTest{300, 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);

    EXPECT_EQ("name : [(300, A)]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithTuple) {
    stringstream ssToVerify;
    tuple<int, string, char> const pairToTest{300, "hello", 'A'};

    printParameterWithName(ssToVerify, "name", pairToTest);

    EXPECT_EQ(R"(name : [(300, "hello", A)])", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithArray) {
    stringstream ssToVerify;
    array<int, 5> const arrayToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", arrayToTest);

    EXPECT_EQ("name : [{Constant size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithVector) {
    stringstream ssToVerify;
    vector<int> const vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithDeque) {
    stringstream ssToVerify;
    deque<int> const vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithSet) {
    stringstream ssToVerify;
    set<int> const vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | 500, 501, 502, 503, 504, }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithMap) {
    stringstream ssToVerify;
    map<int, char> const vectorToTest{{500, 'A'}, {501, 'B'}, {502, 'C'}, {503, 'D'}, {504, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{size: 5 | (500, A), (501, B), (502, C), (503, D), (504, E), }]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedSet) {
    stringstream ssToVerify;
    unordered_set<int> const vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    string const actualPrintString(ssToVerify.str());
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "size: 5 "));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "500"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "501"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "502"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "503"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "504"));
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithUnorderedMap) {
    stringstream ssToVerify;
    unordered_map<int, char> const vectorToTest{{500, 'A'}, {501, 'B'}, {502, 'C'}, {503, 'D'}, {504, 'E'}};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    string const actualPrintString(ssToVerify.str());
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "size: 5 "));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(500, A)"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(501, B)"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(502, C)"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(503, D)"));
    EXPECT_TRUE(isStringFoundCaseSensitive(actualPrintString, "(504, E)"));
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithStack) {
    stringstream ssToVerify;
    stack<int> const adapter({1, 2, 3});

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithQueue) {
    stringstream ssToVerify;
    queue<int> const adapter({1, 2, 3});

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 1, 2, 3, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithPriorityQueue) {
    stringstream ssToVerify;
    priority_queue<int> adapter;
    adapter.push(1U);
    adapter.push(2U);
    adapter.push(3U);

    printParameterWithName(ssToVerify, "name", adapter);

    EXPECT_EQ("name : [{adapter: {size: 3 | 3, 1, 2, }}]", ssToVerify.str());
}

TEST(AlbaPrintFunctionsTest, PrintParameterWithNameWorksWithForwardList) {
    stringstream ssToVerify;
    forward_list<int> const vectorToTest{500, 501, 502, 503, 504};

    printParameterWithName(ssToVerify, "name", vectorToTest);

    EXPECT_EQ("name : [{500, 501, 502, 503, 504, }]", ssToVerify.str());
}

}  // namespace alba
