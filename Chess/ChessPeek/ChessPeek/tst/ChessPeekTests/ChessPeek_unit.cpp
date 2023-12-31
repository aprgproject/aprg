#include <ChessPeek/ChessPeek.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::chess::ChessPeek {

// TEST(ChessPeekTest, DISABLED_CalculationDetailsSavedAndCanBeDisplayedLater) {
//    ChessPeek chessPeek;
//    ChessPeek::EngineCalculationDetails details1{}, details2{}, details3{};
//    details1.depthInPlies = 1;
//    details2.depthInPlies = 2;
//    details3.depthInPlies = 3;
//    Sleep(500);
//    chessPeek.calculationMonitoringCallBackForEngine(details1);
//    chessPeek.calculationMonitoringCallBackForEngine(details2);
//    chessPeek.calculationMonitoringCallBackForEngine(details3);
//    Sleep(500);
//    chessPeek.displayCalculationDetailsIfNotDisplayedYet();
//}
TEST(ChessPeekTest, DISABLED_RunForeverWorks) {
    ChessPeek chessPeek;

    chessPeek.runForever();
}

TEST(ChessPeekTest, DISABLED_RunOneIterationWorks) {
    ChessPeek chessPeek;

    chessPeek.runOneIteration();
    Sleep(10000);
}

TEST(ChessPeekTest, DISABLED_CheckScreenAndSaveDetailsWorks) {
    ChessPeek chessPeek;

    chessPeek.checkScreenAndSaveDetails();
}

TEST(ChessPeekTest, DISABLED_StartNewAnalysisUsingEngineWorks) {
    ChessPeek chessPeek;

    chessPeek.startEngineAnalysisWithBoardFromScreen();
    Sleep(10000);
}

TEST(ChessPeekTest, DISABLED_CalculationDetailsAreFilteredByTimer) {
    ChessPeek chessPeek;
    ChessPeek::EngineCalculationDetails details1{};
    ChessPeek::EngineCalculationDetails details2{};
    ChessPeek::EngineCalculationDetails details3{};
    details1.depthInPlies = 1;
    details2.depthInPlies = 2;
    details3.depthInPlies = 3;

    Sleep(500);
    chessPeek.calculationMonitoringCallBackForEngine(details1);
    chessPeek.calculationMonitoringCallBackForEngine(details2);
    chessPeek.calculationMonitoringCallBackForEngine(details3);
}

}  // namespace alba::chess::ChessPeek
