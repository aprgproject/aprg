#include "AnimeFilter.hpp"

#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/Utilities.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <iostream>
#include <sstream>

using namespace std;

namespace alba::AprgBitmap {

void animize(string const& inputFile, string const& outputFile) {
    AlbaLocalTimer localTimer;
    AlbaLocalPathHandler inputFilePathHandler(inputFile);
    AlbaLocalPathHandler outputFilePathHandler(outputFile);
    BitmapFilters bitmapFilters(inputFilePathHandler.getFullPath());
    BitmapSnippet tempSnippet(bitmapFilters.getWholeBitmapSnippet());
    BitmapSnippet outputSnippet(bitmapFilters.getBlankSnippetWithBackground());
    BitmapSnippet debugSnippet(bitmapFilters.getBlankSnippetWithBackground());
    PenPoints penPointsBeforeAnimeColor;
    PenPoints penPointsAfterAnimeColor;
    PenCircles penCirclesBeforeAnimeColor;
    PenCircles penCirclesAfterAnimeColor;

    localTimer.resetTimer();

    AnimizeColor animizeColor;
    animizeColor.gatherStatistics(inputFilePathHandler.getFullPath());
    animizeColor.calculateNewValues();
    doStuffsAfterSteps(localTimer, "Determining the new colors for animizing");

    alba::AprgBitmap::BitmapFilters::determinePenPoints(penPointsBeforeAnimeColor, tempSnippet, 3, 0x08);
    alba::AprgBitmap::BitmapFilters::drawPenPoints(penPointsBeforeAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(
        localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen points (before anime color)");

    alba::AprgBitmap::BitmapFilters::determinePenCirclesFromPenPoints(
        penCirclesBeforeAnimeColor, penPointsBeforeAnimeColor, tempSnippet, 0x06, 0.90);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(
        localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen circles (before anime color)");

    alba::AprgBitmap::BitmapFilters::drawAnimeColor(tempSnippet, animizeColor);
    doStuffsAfterSteps(localTimer, bitmapFilters, tempSnippet, inputFile, "Drawing to anime color");

    alba::AprgBitmap::BitmapFilters::drawWithBlurringDisimilarColors(tempSnippet, 5, 0x02);
    doStuffsAfterSteps(localTimer, bitmapFilters, tempSnippet, inputFile, "Blur disimilar colors");

    alba::AprgBitmap::BitmapFilters::determinePenPoints(
        penPointsAfterAnimeColor, tempSnippet, 3, 0x08);  // detect pixelation
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawPenPoints(penPointsAfterAnimeColor, tempSnippet, debugSnippet);
    doStuffsAfterSteps(
        localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen points (after anime color)");

    alba::AprgBitmap::BitmapFilters::determinePenCirclesFromPenPoints(
        penCirclesAfterAnimeColor, penPointsAfterAnimeColor, tempSnippet, 0x08, 0.60);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(
        localTimer, bitmapFilters, debugSnippet, inputFile, "Determining pen circles (after anime color)");

    alba::AprgBitmap::BitmapFilters::drawNonPenPoints(penPointsAfterAnimeColor, tempSnippet, outputSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, outputSnippet, inputFile, "Drawing non pen points");

    bitmapFilters.drawToFillGapsUsingBlur(outputSnippet, 2);
    doStuffsAfterSteps(localTimer, bitmapFilters, outputSnippet, inputFile, "Drawing to fill gaps");

    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesAfterAnimeColor, outputSnippet);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesAfterAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Drawing pen circles (after anime color)");

    animeColorsInPenCircles(penCirclesBeforeAnimeColor, animizeColor);
    doStuffsAfterSteps(localTimer, "Convert pen circles (before anime color) to anime color");

    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesBeforeAnimeColor, outputSnippet);
    debugSnippet = bitmapFilters.getBlankSnippetWithBackground();
    alba::AprgBitmap::BitmapFilters::drawPenCircles(penCirclesBeforeAnimeColor, debugSnippet);
    doStuffsAfterSteps(localTimer, bitmapFilters, debugSnippet, inputFile, "Drawing pen circles (before anime color)");

    bitmapFilters.saveSnippetIntoFileWithFullFilePath(outputSnippet, outputFilePathHandler.getFullPath());
}

void doStuffsAfterSteps(AlbaLocalTimer& localTimer, string const& description) {
    localTimer.stopTimer();
    cout << localTimer.getDifferenceAsAlbaDateTime() << ": " << description << "\n";
    localTimer.resetTimer();
}

void doStuffsAfterSteps(
    AlbaLocalTimer& localTimer, BitmapFilters& bitmapFilters, BitmapSnippet const& snippet, string const& inputFilePath,
    string const& description) {
    static int step = 1;
    localTimer.stopTimer();
    bitmapFilters.saveSnippetIntoFileWithFullFilePath(snippet, getNewFilePath(inputFilePath, ++step, description));
    cout << localTimer.getDifferenceAsAlbaDateTime() << ": " << description << "\n";
    localTimer.resetTimer();
}

string getNewFilePath(string const& inputFilePath, int const step, string const& description) {
    AlbaLocalPathHandler inputFilePathHandler(inputFilePath);
    stringstream ss;
    ss << inputFilePathHandler.getDirectory() << inputFilePathHandler.getFilenameOnly() << "_Step" << step << "_("
       << stringHelper::getStringAndReplaceNonAlphanumericCharactersToUnderScore(description) << ")."
       << inputFilePathHandler.getExtension();
    return ss.str();
}

}  // namespace alba::AprgBitmap
