#include <MapAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MapAnalyzerTest, DISABLED_AnalyzeWorks) {
    MapAnalyzer mapAnalyzer;
    mapAnalyzer.analyze();
    mapAnalyzer.printResult();
}

}  // namespace alba
