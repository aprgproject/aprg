#pragma once

#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/AnimizeColor.hpp>
#include <BitmapManipulator/LabelForPoints.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <BitmapManipulator/PenPoints.hpp>
#include <BitmapManipulator/Traversal/BitmapSnippetTraversal.hpp>
#include <Geometry/TwoDimensions/Constructs/Circle.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>

#include <deque>
#include <filesystem>
#include <functional>
#include <optional>

namespace alba::AprgBitmap {

class BitmapFilters {
public:
    using BlurCondition = std::function<bool(uint32_t const, uint32_t const, BitmapXY const&)>;
    using UnionFindForLabels = algorithm::UnionFindUsingMap<int>;
    using PointToColorMap = std::map<BitmapXY, uint32_t>;
    using PointAndColorPair = std::pair<BitmapXY, uint32_t>;
    using PenPointToPenCircleMap = std::map<BitmapXY, TwoDimensions::Circle>;
    using PenPointAndPenCirclePair = std::pair<BitmapXY, TwoDimensions::Circle>;
    explicit BitmapFilters(std::filesystem::path const& filePath);
    [[nodiscard]] BitmapSnippet getWholeBitmapSnippet() const;
    [[nodiscard]] BitmapSnippet getBlankSnippet(uint8_t const backgroundColorByte) const;
    [[nodiscard]] BitmapSnippet getBlankSnippetWithBackground() const;
    [[nodiscard]] BitmapSnippet getBlankSnippetWithColor(uint32_t const color) const;
    [[nodiscard]] bool isBackgroundColor(uint32_t const color) const;
    [[nodiscard]] bool isNotBackgroundColor(uint32_t const color) const;
    void saveSnippetIntoCurrentBitmapFile(BitmapSnippet const& snippet) const;
    void determineConnectedComponentsByOneComponentAtATime(BitmapSnippet const& inputSnippet);
    void determineConnectedComponentsUsingTwoPass(BitmapSnippet const& inputSnippet);

    void drawBlurredNonPenPoints(
        PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet,
        double const blurRadius, uint32_t const similarityColorLimit);

    void drawBlurredColorsUsingCircles(
        BitmapSnippet& snippet, double const blurRadius, uint32_t const similarityColorLimit);

    // other draw functions
    void drawToFillGapsUsingBlur(BitmapSnippet& snippet, double const blurRadius);
    void drawNewColorForLabels(BitmapSnippet& snippet);
    void saveSnippetIntoFileInTheSameDirectory(BitmapSnippet const& snippet, std::filesystem::path const& filename);
    void saveSnippetIntoFileWithFullFilePath(BitmapSnippet const& snippet, std::filesystem::path const& fullFilePath);
    void setBackgroundColor(uint32_t const backgroundColor);
    void gatherAndSaveColorDataAndStatistics();

    // determine functions
    static void determinePenPoints(
        PenPoints& penPoints, BitmapSnippet const& inputSnippet, double const penSearchRadius,
        uint32_t const similarityColorLimit);

    static void determinePenCirclesFromPenPoints(
        PenCircles& penCircles, PenPoints const& penPoints, BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit, double const acceptablePenPercentage);

    // draw pen and non pen functions
    static void drawPenPoints(
        PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet);

    static void drawNonPenPoints(
        PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet);

    static void drawPenCircles(PenCircles const& penCircles, BitmapSnippet& snippet);
    static void drawPenCirclesOnly(PenCircles const& penCircles, BitmapSnippet& snippet);

    // draw blur functions
    static void drawWithBlurringDisimilarColors(
        BitmapSnippet& snippet, int const numberOfPasses, uint32_t const similarityColorLimit);

    static void drawWithBlurUsingSnakeLikeTraversal(BitmapSnippet& snippet, uint32_t const similarityColorLimit);
    static void drawAnimeColor(BitmapSnippet& snippet, AnimizeColor const& animizeColor);

    static std::optional<TwoDimensions::Circle> getPossiblePenCircle(
        BitmapSnippet const& inputSnippet, BitmapXY const& centerPoint, uint32_t const similarityColorLimit,
        double const acceptablePenPercentage);

private:
    [[nodiscard]] uint32_t getBlurredColorUsingACircle(
        BitmapSnippet const& snippet, BitmapXY const& centerXY, double const blurRadius,
        BlurCondition const& isIncludedInBlur) const;

    void analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
        BitmapSnippet const& inputSnippet, std::deque<BitmapXY>& pointsInDeque, BitmapXY const& poppedPoint,
        int const currentLabel);

    void analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
        BitmapSnippet const& inputSnippet, std::deque<BitmapXY>& pointsInDeque, BitmapXY const& neighborPoint,
        int const currentLabel);

    void determineConnectedComponentsUsingTwoPassInFirstPass(
        BitmapSnippet const& inputSnippet, UnionFindForLabels& unionFindForLabels);

    void determineConnectedComponentsUsingTwoPassInSecondPass(
        BitmapSnippet const& inputSnippet, UnionFindForLabels const& unionFindForLabels);

    int analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
        BitmapSnippet const& inputSnippet, UnionFindForLabels& unionFindForLabels, BitmapXY const& neighborPoint);

    int analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
        BitmapSnippet const& inputSnippet, BitmapXY const& neighborPoint);

    [[nodiscard]] static uint32_t getBlurredColor(
        uint32_t const centerColor, uint32_t const colorToCompare, uint32_t const similarityColorLimit);

    static void collectDisimilarPointsToNewColors(
        PointToColorMap& disimilarPointsToNewColors, BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit);

    static void determinePenPointsToPenCircles(
        PenPointToPenCircleMap& penPointsToPenCircles, PenPoints const& penPoints, BitmapSnippet const& inputSnippet,
        uint32_t const similarityColorLimit, double const acceptablePenPercentage);

    static void drawToBlurForCenterPoint(
        BitmapSnippet& snippet, BitmapXYs& pointsToBlur, BitmapXY const& point, uint32_t const similarityColorLimit);

    static void drawToBlurForNonCenterPoint(
        BitmapSnippet& snippet, BitmapXYs& pointsToBlur, BitmapXY const& point, uint32_t const centerColor,
        uint32_t const similarityColorLimit);

    static void updateUnionFindForLabels(
        UnionFindForLabels& unionFindForLabels, int const smallestLabel, int const neighbor1Label,
        int const neighbor2Label);

    static double getBlurWeight(double const distanceFromCenter, double const blurRadius);

    static uint8_t getBlurredColorPart(
        uint8_t const centerColorPart, uint8_t const colorToComparePart, uint32_t const similarityColorLimit);

    static bool isThisPenCircleBetter(
        BitmapXY const& penBitmapXY, TwoDimensions::Circle const& circleToCheck,
        TwoDimensions::Circle const& circleToCompare);

    uint32_t m_backgroundColor{0xFFFFFF};
    Bitmap m_bitmap;
    LabelForPoints m_labelForPixels;
};

}  // namespace alba::AprgBitmap
