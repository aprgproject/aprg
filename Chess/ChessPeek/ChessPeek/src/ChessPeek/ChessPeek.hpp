#pragma once

#include <ChessPeek/Book.hpp>
#include <ChessPeek/CalculationDetails.hpp>
#include <ChessPeek/Configuration.hpp>
#include <ChessPeek/DetailsFromTheScreen.hpp>
#include <ChessPeek/DetailsOnTheEngine.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>

namespace alba::chess::ChessPeek {

class ChessPeek {
public:
    using EngineCalculationDetails = chess::CalculationDetails;
    ChessPeek();
    void runForever();
    void runOneIteration();
    void checkScreenAndSaveDetails();
    void startEngineAnalysisWithBoardFromScreen();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    [[nodiscard]] Move getPerformedMove() const;
    [[nodiscard]] bool shouldAnalyzeBoard() const;
    [[nodiscard]] bool didPlayerChange() const;
    [[nodiscard]] bool didBoardChange() const;
    void initialize();
    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);
    void printCalculationDetailsWithFiltering();
    void printCalculationDetailsIfPending();
    void printCalculationDetails();
    Configuration m_configuration;
    ChessEngineHandler m_engineHandler;
    ChessEngineControllerWithUci m_engineController;
    AlbaLocalTimer m_printFilteringTimer;
    DetailsFromTheScreen m_detailsFromTheScreen;
    DetailsOnTheEngine m_detailsOnTheEngine;
    Book m_book;
    CalculationDetails m_calculationDetails;
    CalculationDetails m_printCalculationDetails;
    bool m_engineWasJustReset;
    bool m_hasPendingPrintAction;
};

}  // namespace alba::chess::ChessPeek
