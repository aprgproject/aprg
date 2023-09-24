#include "BitmapFilters.hpp"

#include <BitmapManipulator/ColorStatistics.hpp>
#include <BitmapManipulator/ColorUtilities.hpp>
#include <BitmapManipulator/PenCirclesDrawer.hpp>
#include <BitmapManipulator/Traversal/OutwardCircleTraversal.hpp>
#include <BitmapManipulator/Traversal/OutwardSnakeLikeTraversal.hpp>
#include <BitmapManipulator/Utilities.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Geometry/TwoDimensions/Utilities/TwoDimensionsUtilities.hpp>

using namespace alba::AprgBitmap::ColorUtilities;
using namespace alba::mathHelper;
using namespace alba::TwoDimensions;
using namespace std;
using namespace std::filesystem;

namespace {
constexpr int MAX_PEN_CIRCLE_RADIUS_COORDINATE = 5;
}  // namespace

namespace alba::AprgBitmap {

BitmapFilters::BitmapFilters(path const& filePath) : m_bitmap(filePath) {}
BitmapSnippet BitmapFilters::getWholeBitmapSnippet() const { return m_bitmap.getSnippetReadFromFileWholeBitmap(); }

BitmapSnippet BitmapFilters::getBlankSnippet(uint8_t const backgroundColorByte) const {
    return m_bitmap.createColorFilledSnippetWithSizeOfWholeBitmap(backgroundColorByte);
}

BitmapSnippet BitmapFilters::getBlankSnippetWithBackground() const {
    return getBlankSnippet(static_cast<uint8_t>(m_backgroundColor & 0xFF));
}

BitmapSnippet BitmapFilters::getBlankSnippetWithColor(uint32_t const color) const {
    return getBlankSnippet(static_cast<uint8_t>(color & 0xFF));
}

bool BitmapFilters::isBackgroundColor(uint32_t const color) const {
    return getColorValueOnly(color) == m_backgroundColor;
}

bool BitmapFilters::isNotBackgroundColor(uint32_t const color) const {
    return getColorValueOnly(color) != m_backgroundColor;
}

void BitmapFilters::saveSnippetIntoCurrentBitmapFile(BitmapSnippet const& snippet) const {
    m_bitmap.setSnippetWriteToFile(snippet);
}

void BitmapFilters::determineConnectedComponentsByOneComponentAtATime(BitmapSnippet const& inputSnippet) {
    int currentLabel = 1;
    deque<BitmapXY> pointsInDeque;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor) {
        int const pixelLabel = m_labelForPixels.getLabel(currentPoint);
        if (isNotBackgroundColor(currentPointColor) && isInitialLabel(pixelLabel)) {
            m_labelForPixels.setLabel(currentPoint, currentLabel);
            pointsInDeque.push_front(currentPoint);
            while (!pointsInDeque.empty()) {
                BitmapXY const poppedPoint(pointsInDeque.back());
                pointsInDeque.pop_back();
                analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
                    inputSnippet, pointsInDeque, poppedPoint, currentLabel);
            }
            ++currentLabel;
        }
    });
}

void BitmapFilters::determineConnectedComponentsUsingTwoPass(BitmapSnippet const& inputSnippet) {
    UnionFindForLabels unionFindForLabels;
    determineConnectedComponentsUsingTwoPassInFirstPass(inputSnippet, unionFindForLabels);
    determineConnectedComponentsUsingTwoPassInSecondPass(inputSnippet, unionFindForLabels);
}

void BitmapFilters::drawBlurredNonPenPoints(
    PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet,
    double const blurRadius, uint32_t const similarityColorLimit) {
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const) {
        bool const isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if (!isPenPoint) {
            outputSnippet.setPixelAt(
                bitmapPoint,
                getBlurredColorUsingACircle(
                    inputSnippet, bitmapPoint, blurRadius,
                    [&](uint32_t const centerColor, uint32_t const currentColor, BitmapXY const& pointInCircle) {
                        bool const isPointInCircleAPenPoint(penPoints.isPenPoint(pointInCircle));
                        return isSimilar(centerColor, currentColor, similarityColorLimit) &&
                               isNotBackgroundColor(currentColor) && !isPointInCircleAPenPoint;
                    }));
        }
    });
}

void BitmapFilters::drawBlurredColorsUsingCircles(
    BitmapSnippet& snippet, double const blurRadius, uint32_t const similarityColorLimit) {
    BitmapSnippet tempSnippet(snippet);
    tempSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const) {
        snippet.setPixelAt(
            bitmapPoint, getBlurredColorUsingACircle(
                             tempSnippet, bitmapPoint, blurRadius,
                             [&](uint32_t const centerColor, uint32_t const currentColor, BitmapXY const&) {
                                 return isSimilar(centerColor, currentColor, similarityColorLimit) &&
                                        isNotBackgroundColor(currentColor);
                             }));
    });
}

void BitmapFilters::drawToFillGapsUsingBlur(BitmapSnippet& snippet, double const blurRadius) {
    BitmapXYs backgroundPoints;
    snippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color) {
        if (isBackgroundColor(color)) {
            backgroundPoints.emplace_back(bitmapPoint);
        }
    });
    int previousNumberOfPoints = 0;
    while (previousNumberOfPoints != static_cast<int>(backgroundPoints.size()) && !backgroundPoints.empty()) {
        previousNumberOfPoints = static_cast<int>(backgroundPoints.size());
        BitmapXYs newBackgroundPoints;
        BitmapSnippet tempSnippet(snippet);
        for (BitmapXY const& backgroundPoint : backgroundPoints) {
            uint32_t const newColor = getBlurredColorUsingACircle(
                snippet, backgroundPoint, blurRadius,
                [&](uint32_t const, uint32_t const currentColor, BitmapXY const&) {
                    return isNotBackgroundColor(currentColor);
                });
            if (isBackgroundColor(newColor)) {
                newBackgroundPoints.emplace_back(backgroundPoint);
            } else {
                tempSnippet.setPixelAt(backgroundPoint, newColor);
            }
        }
        backgroundPoints = newBackgroundPoints;
        snippet = tempSnippet;
    }
}

void BitmapFilters::drawNewColorForLabels(BitmapSnippet& snippet) {
    snippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const) {
        int const pixelLabel = m_labelForPixels.getLabel(bitmapPoint);
        if (!isInitialOrInvalidLabel(pixelLabel)) {
            snippet.setPixelAt(bitmapPoint, getLabelColor(pixelLabel));
        }
    });
}

void BitmapFilters::saveSnippetIntoFileInTheSameDirectory(BitmapSnippet const& snippet, path const& filename) {
    AlbaLocalPathHandler const originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    saveSnippetIntoFileWithFullFilePath(snippet, originalBitmapPathHandler.getDirectory() / filename);
}

void BitmapFilters::saveSnippetIntoFileWithFullFilePath(BitmapSnippet const& snippet, path const& fullFilePath) {
    AlbaLocalPathHandler const originalBitmapPathHandler(m_bitmap.getConfiguration().getPath());
    AlbaLocalPathHandler const newFilePathHandler(fullFilePath);
    if (originalBitmapPathHandler.copyFileToAndIsSuccessful(newFilePathHandler.getPath())) {
        Bitmap const newBitmap(newFilePathHandler.getPath());
        newBitmap.setSnippetWriteToFile(snippet);
    }
}

void BitmapFilters::setBackgroundColor(uint32_t const backgroundColor) { m_backgroundColor = backgroundColor; }

void BitmapFilters::gatherAndSaveColorDataAndStatistics() {
    gatherAndSaveColorStatistics(m_bitmap.getConfiguration().getPath());
}

void BitmapFilters::determinePenPoints(
    PenPoints& penPoints, BitmapSnippet const& inputSnippet, double const penSearchRadius,
    uint32_t const similarityColorLimit) {
    inputSnippet.traverse([&](BitmapXY const& centerXY, uint32_t const centerColor) {
        Circle const circle(convertBitmapXYToPoint(centerXY), penSearchRadius);
        BitmapXYs bitmapPointsWithSimilarColors;
        BitmapXYs bitmapPointsWithDisimilarColors;
        BitmapSnippetTraversal const snippetTraversal(inputSnippet);
        snippetTraversal.traverseCircleArea(circle, [&](BitmapXY const& pointInCircle) {
            uint32_t const currentColor(inputSnippet.getColorAt(pointInCircle));
            if (isSimilar(centerColor, currentColor, similarityColorLimit)) {
                bitmapPointsWithSimilarColors.emplace_back(pointInCircle);
            } else {
                bitmapPointsWithDisimilarColors.emplace_back(pointInCircle);
            }
        });
        if (bitmapPointsWithSimilarColors.size() > bitmapPointsWithDisimilarColors.size()) {
            penPoints.addAsPenPoints(bitmapPointsWithDisimilarColors);
        } else {
            penPoints.addAsPenPoints(bitmapPointsWithSimilarColors);
        }
    });
}

void BitmapFilters::determinePenCirclesFromPenPoints(
    PenCircles& penCircles, PenPoints const& penPoints, BitmapSnippet const& inputSnippet,
    uint32_t const similarityColorLimit, double const acceptablePenPercentage) {
    map<BitmapXY, Circle> penPointsToPenCircles;
    determinePenPointsToPenCircles(
        penPointsToPenCircles, penPoints, inputSnippet, similarityColorLimit, acceptablePenPercentage);
    for (auto const& penPointAndPenCirclePair : penPointsToPenCircles) {
        penCircles.addAsPenCircle(
            penPointAndPenCirclePair.first, penPointAndPenCirclePair.second.getRadius(),
            inputSnippet.getColorAt(penPointAndPenCirclePair.first));
    }
}

void BitmapFilters::drawPenPoints(
    PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet) {
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color) {
        bool const isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if (isPenPoint) {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawNonPenPoints(
    PenPoints const& penPoints, BitmapSnippet const& inputSnippet, BitmapSnippet& outputSnippet) {
    inputSnippet.traverse([&](BitmapXY const& bitmapPoint, uint32_t const color) {
        bool const isPenPoint(penPoints.isPenPoint(bitmapPoint));
        if (!isPenPoint) {
            outputSnippet.setPixelAt(bitmapPoint, color);
        }
    });
}

void BitmapFilters::drawPenCircles(PenCircles const& penCircles, BitmapSnippet& snippet) {
    PenCirclesDrawer drawer(penCircles, snippet);
    drawer.draw();
}

void BitmapFilters::drawPenCirclesOnly(PenCircles const& penCircles, BitmapSnippet& snippet) {
    for (auto const& pointAndPenCircleDetailsPair : penCircles.getPenCircles()) {
        BitmapXY const& centerPoint(pointAndPenCircleDetailsPair.first);
        BitmapSnippetTraversal const snippetTraversal(snippet);
        Circle const penCircle(convertBitmapXYToPoint(centerPoint), pointAndPenCircleDetailsPair.second.radius);
        snippetTraversal.traverseCircleArea(penCircle, [&](BitmapXY const& pointInPenCircle) {
            snippet.setPixelAt(pointInPenCircle, pointAndPenCircleDetailsPair.second.color);
        });
    }
}

void BitmapFilters::drawWithBlurringDisimilarColors(
    BitmapSnippet& snippet, int const numberOfPasses, uint32_t const similarityColorLimit) {
    PointToColorMap disimilarPointsToNewColors;

    for (int i = 0; i < numberOfPasses; ++i) {
        disimilarPointsToNewColors.clear();
        collectDisimilarPointsToNewColors(disimilarPointsToNewColors, snippet, similarityColorLimit);
        for (auto const& disimilarPointAndNewColorPair : disimilarPointsToNewColors) {
            snippet.setPixelAt(disimilarPointAndNewColorPair.first, disimilarPointAndNewColorPair.second);
        }
    }
}

void BitmapFilters::drawWithBlurUsingSnakeLikeTraversal(BitmapSnippet& snippet, uint32_t const similarityColorLimit) {
    BitmapXY const topLeft(snippet.getTopLeftCorner());
    BitmapXY const bottomRight(snippet.getBottomRightCorner());
    BitmapXY const middle((topLeft.getX() + bottomRight.getX()) / 2, (topLeft.getY() + bottomRight.getY()) / 2);

    BitmapXYs pointsToBlur;
    OutwardSnakeLikeTraversal traversal(
        middle, OutwardSnakeLikeTraversal::Direction::Up, topLeft.getX(), bottomRight.getX(), topLeft.getY(),
        bottomRight.getY());
    while (!traversal.isTraversalFinished()) {
        BitmapXY const centerPoint(traversal.getNextPoint());
        drawToBlurForCenterPoint(snippet, pointsToBlur, centerPoint, similarityColorLimit);
        while (!pointsToBlur.empty()) {
            BitmapXYs newPointsToBlur;
            for (BitmapXY const& pointToBlur : pointsToBlur) {
                drawToBlurForCenterPoint(snippet, newPointsToBlur, pointToBlur, similarityColorLimit);
            }
            pointsToBlur = newPointsToBlur;
        }
    }
}

void BitmapFilters::drawAnimeColor(BitmapSnippet& snippet, AnimizeColor const& animizeColor) {
    snippet.traverse([&](BitmapXY const& position, uint32_t const color) {
        snippet.setPixelAt(position, animizeColor.getNewColor(color));
    });
}

optional<Circle> BitmapFilters::getPossiblePenCircle(
    BitmapSnippet const& inputSnippet, BitmapXY const& centerPoint, uint32_t const similarityColorLimit,
    double const acceptablePenPercentage) {
    optional<Circle> result;
    uint32_t const centerColor(inputSnippet.getColorAt(centerPoint));
    int similarPixelsCount(0);
    int totalPixelCount(0);
    BitmapSnippetTraversal const snippetTraversal(inputSnippet);
    OutwardCircleTraversal const outwardTraversal(MAX_PEN_CIRCLE_RADIUS_COORDINATE);
    OutwardCircleTraversal::RadiusToCoordinates const& radiusToCoordinates(outwardTraversal.getRadiusToCoordinates());
    double currentRadius(0);
    double previousRadius(0);
    for (auto const& radiusAndCoordinatePair : radiusToCoordinates) {
        currentRadius = radiusAndCoordinatePair.first;
        snippetTraversal.traverseCoordinatesCombinations(
            centerPoint, radiusAndCoordinatePair.second.coordinate1, radiusAndCoordinatePair.second.coordinate2,
            [&](BitmapXY const& pointInCircle) {
                uint32_t const currentColor(inputSnippet.getColorAt(pointInCircle));
                if (isSimilar(centerColor, currentColor, similarityColorLimit)) {
                    ++similarPixelsCount;
                }
                ++totalPixelCount;
            });
        if (previousRadius != currentRadius) {
            double const calculatedPenPercentage = static_cast<double>(similarPixelsCount) / totalPixelCount;
            if (calculatedPenPercentage < acceptablePenPercentage) {
                result.emplace(convertBitmapXYToPoint(centerPoint), previousRadius);
                break;
            }
            previousRadius = currentRadius;
        }
    }
    if (!result) {
        result.emplace(convertBitmapXYToPoint(centerPoint), currentRadius);
    }
    return result;
}

uint32_t BitmapFilters::getBlurredColorUsingACircle(
    BitmapSnippet const& snippet, BitmapXY const& centerXY, double const blurRadius,
    BlurCondition const& isIncludedInBlur) const {
    uint32_t const centerColor(snippet.getColorAt(centerXY));
    double totalBlurredColorRed(0);
    double totalBlurredColorGreen(0);
    double totalBlurredColorBlue(0);
    double totalBlurWeight(0);
    bool isChanged(false);
    Circle const circle(convertBitmapXYToPoint(centerXY), blurRadius);
    BitmapSnippetTraversal const snippetTraversal(snippet);
    snippetTraversal.traverseCircleArea(circle, [&](BitmapXY const& pointInCircle) {
        uint32_t const currentColor(snippet.getColorAt(pointInCircle));
        if (isIncludedInBlur(centerColor, currentColor, pointInCircle)) {
            isChanged = true;
            double const distanceFromCenter(twoDimensionsUtilities::getDistance(
                convertBitmapXYToPoint(centerXY), convertBitmapXYToPoint(pointInCircle)));
            double const blurWeight(getBlurWeight(distanceFromCenter, blurRadius));
            totalBlurredColorRed += blurWeight * extractRed(currentColor);
            totalBlurredColorGreen += blurWeight * extractGreen(currentColor);
            totalBlurredColorBlue += blurWeight * extractBlue(currentColor);
            totalBlurWeight += blurWeight;
        }
    });
    uint32_t blurredColor(m_backgroundColor);
    if (isChanged) {
        blurredColor = combineRgbToColor(
            static_cast<uint8_t>(totalBlurredColorRed / totalBlurWeight),
            static_cast<uint8_t>(totalBlurredColorGreen / totalBlurWeight),
            static_cast<uint8_t>(totalBlurredColorBlue / totalBlurWeight));
    }
    return blurredColor;
}

void BitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsOneComponentAtATime(
    BitmapSnippet const& inputSnippet, deque<BitmapXY>& pointsInDeque, BitmapXY const& poppedPoint,
    int const currentLabel) {
    // 4-connectivity
    BitmapXY const neighbor1(poppedPoint.getX() - 1, poppedPoint.getY());
    BitmapXY const neighbor2(poppedPoint.getX(), poppedPoint.getY() - 1);
    BitmapXY const neighbor3(poppedPoint.getX() + 1, poppedPoint.getY());
    BitmapXY const neighbor4(poppedPoint.getX(), poppedPoint.getY() + 1);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor1, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor2, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor3, currentLabel);
    analyzeNeighborPointForConnectedComponentsOneComponentAtATime(inputSnippet, pointsInDeque, neighbor4, currentLabel);
}

void BitmapFilters::analyzeNeighborPointForConnectedComponentsOneComponentAtATime(
    BitmapSnippet const& inputSnippet, deque<BitmapXY>& pointsInDeque, BitmapXY const& neighborPoint,
    int const currentLabel) {
    if (inputSnippet.isPositionInsideTheSnippet(neighborPoint)) {
        uint32_t const neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        int const neighborPointLabel = m_labelForPixels.getLabel(neighborPoint);
        if (isNotBackgroundColor(neighborPointColor) && isInitialLabel(neighborPointLabel)) {
            m_labelForPixels.setLabel(neighborPoint, currentLabel);
            pointsInDeque.push_front(neighborPoint);
        }
    }
}

void BitmapFilters::determineConnectedComponentsUsingTwoPassInFirstPass(
    BitmapSnippet const& inputSnippet, UnionFindForLabels& unionFindForLabels) {
    int currentLabel = 1;
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor) {
        if (isNotBackgroundColor(currentPointColor)) {
            int const smallestNeighborLabel =
                analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
                    inputSnippet, unionFindForLabels, currentPoint);
            if (!isInvalidLabel(smallestNeighborLabel)) {
                m_labelForPixels.setLabel(currentPoint, smallestNeighborLabel);
            } else {
                m_labelForPixels.setLabel(currentPoint, currentLabel);
                ++currentLabel;
            }
        }
    });
}

void BitmapFilters::determineConnectedComponentsUsingTwoPassInSecondPass(
    BitmapSnippet const& inputSnippet, UnionFindForLabels const& unionFindForLabels) {
    inputSnippet.traverse([&](BitmapXY const& currentPoint, uint32_t const currentPointColor) {
        int const pixelLabel = m_labelForPixels.getLabel(currentPoint);
        if (isNotBackgroundColor(currentPointColor) && !isInitialLabel(pixelLabel)) {
            int const smallestLabel = unionFindForLabels.getRoot(pixelLabel);
            m_labelForPixels.setLabel(currentPoint, smallestLabel);
        }
    });
}

int BitmapFilters::analyzeFourConnectivityNeighborPointsForConnectedComponentsTwoPassAndReturnSmallestLabel(
    BitmapSnippet const& inputSnippet, UnionFindForLabels& unionFindForLabels, BitmapXY const& neighborPoint) {
    // 4-connectivity
    int smallestLabel = INVALID_LABEL_VALUE;
    BitmapXY const neighbor1(neighborPoint.getX() - 1, neighborPoint.getY());
    BitmapXY const neighbor2(neighborPoint.getX(), neighborPoint.getY() - 1);
    int const neighbor1Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(inputSnippet, neighbor1);
    int const neighbor2Label = analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(inputSnippet, neighbor2);
    smallestLabel = min(smallestLabel, neighbor1Label);
    smallestLabel = min(smallestLabel, neighbor2Label);
    updateUnionFindForLabels(unionFindForLabels, smallestLabel, neighbor1Label, neighbor2Label);
    return smallestLabel;
}

int BitmapFilters::analyzeNeighborPointForConnectedComponentsTwoPassAneReturnLabel(
    BitmapSnippet const& inputSnippet, BitmapXY const& neighborPoint) {
    int labelResult = INVALID_LABEL_VALUE;
    if (inputSnippet.isPositionInsideTheSnippet(neighborPoint)) {
        uint32_t const neighborPointColor = inputSnippet.getColorAt(neighborPoint);
        int const neighborPointLabel = m_labelForPixels.getLabel(neighborPoint);
        if (isNotBackgroundColor(neighborPointColor) && !isInitialLabel(neighborPointLabel)) {
            labelResult = neighborPointLabel;
        }
    }
    return labelResult;
}

uint32_t BitmapFilters::getBlurredColor(
    uint32_t const centerColor, uint32_t const colorToCompare, uint32_t const similarityColorLimit) {
    uint8_t const red = getBlurredColorPart(extractRed(centerColor), extractRed(colorToCompare), similarityColorLimit);
    uint8_t const green =
        getBlurredColorPart(extractGreen(centerColor), extractGreen(colorToCompare), similarityColorLimit);
    uint8_t const blue =
        getBlurredColorPart(extractBlue(centerColor), extractBlue(colorToCompare), similarityColorLimit);
    return combineRgbToColor(red, green, blue);
}

void BitmapFilters::collectDisimilarPointsToNewColors(
    PointToColorMap& disimilarPointsToNewColors, BitmapSnippet const& inputSnippet,
    uint32_t const similarityColorLimit) {
    BitmapSnippetTraversal snippetTraversal(inputSnippet);
    inputSnippet.traverse([&](BitmapXY const& point, uint32_t const pointColor) {
        double redTotal(0);
        double greenTotal(0);
        double blueTotal(0);
        int neighborCount(0);
        int disimilarNeighborCount(0);
        snippetTraversal.traverse8WayConnectivity(point, [&](BitmapXY const& neighborPoint) {
            uint32_t const neighborPointColor = inputSnippet.getColorAt(neighborPoint);
            redTotal += extractRed(neighborPointColor);
            greenTotal += extractGreen(neighborPointColor);
            blueTotal += extractBlue(neighborPointColor);
            ++neighborCount;
            if (!isSimilar(pointColor, neighborPointColor, similarityColorLimit)) {
                ++disimilarNeighborCount;
            }
        });
        uint32_t const newColor = combineRgbToColor(
            static_cast<uint8_t>(round(redTotal / neighborCount)),
            static_cast<uint8_t>(round(greenTotal / neighborCount)),
            static_cast<uint8_t>(round(blueTotal / neighborCount)));

        if (disimilarNeighborCount > 0) {
            disimilarPointsToNewColors[point] = newColor;
        }
    });
}

void BitmapFilters::determinePenPointsToPenCircles(
    PenPointToPenCircleMap& penPointsToPenCircles, PenPoints const& penPoints, BitmapSnippet const& inputSnippet,
    uint32_t const similarityColorLimit, double const acceptablePenPercentage) {
    PenPoints::PenPointsSet const& penPointsSet(penPoints.getPenPoints());
    for (BitmapXY const& penPoint : penPointsSet) {
        optional<Circle> penCircleOptional(
            getPossiblePenCircle(inputSnippet, penPoint, similarityColorLimit, acceptablePenPercentage));
        if (penCircleOptional) {
            Circle const& possiblePenCircle(penCircleOptional.value());
            BitmapSnippetTraversal const snippetTraversal(inputSnippet);
            snippetTraversal.traverseCircleArea(possiblePenCircle, [&](BitmapXY const& pointInPossibleCircle) {
                bool const isPointInCircleAPenPoint(penPoints.isPenPoint(pointInPossibleCircle));
                if (isPointInCircleAPenPoint &&
                    isThisPenCircleBetter(
                        pointInPossibleCircle, possiblePenCircle, penPointsToPenCircles[pointInPossibleCircle])) {
                    penPointsToPenCircles[pointInPossibleCircle] = possiblePenCircle;
                }
            });
        }
    }
}

void BitmapFilters::drawToBlurForCenterPoint(
    BitmapSnippet& snippet, BitmapXYs& pointsToBlur, BitmapXY const& centerPoint, uint32_t const similarityColorLimit) {
    if (snippet.isPositionInsideTheSnippet(centerPoint)) {
        uint32_t const centerColor(snippet.getColorAt(centerPoint));
        BitmapSnippetTraversal const snippetTraversal(snippet);
        snippetTraversal.traverse8WayConnectivity(centerPoint, [&](BitmapXY const& pointInPossibleCircle) {
            drawToBlurForNonCenterPoint(
                snippet, pointsToBlur, pointInPossibleCircle, centerColor, similarityColorLimit);
        });
    }
}

void BitmapFilters::drawToBlurForNonCenterPoint(
    BitmapSnippet& snippet, BitmapXYs& pointsToBlur, BitmapXY const& point, uint32_t const centerColor,
    uint32_t const similarityColorLimit) {
    uint32_t const colorToCompare(snippet.getColorAt(point));
    uint32_t const newColor(getBlurredColor(centerColor, colorToCompare, similarityColorLimit));
    snippet.setPixelAt(point, newColor);
    if (!isSimilar(colorToCompare, newColor, similarityColorLimit)) {
        pointsToBlur.emplace_back(point);
    }
}

void BitmapFilters::updateUnionFindForLabels(
    UnionFindForLabels& unionFindForLabels, int const smallestLabel, int const neighbor1Label,
    int const neighbor2Label) {
    if (!isInvalidLabel(smallestLabel) && !isInvalidLabel(neighbor1Label)) {
        unionFindForLabels.connect(smallestLabel, neighbor1Label);
    }
    if (!isInvalidLabel(smallestLabel) && !isInvalidLabel(neighbor2Label)) {
        unionFindForLabels.connect(smallestLabel, neighbor2Label);
    }
}

double BitmapFilters::getBlurWeight(double const distanceFromCenter, double const blurRadius) {
    return (blurRadius - distanceFromCenter + 1) / (blurRadius + 1);
}

uint8_t BitmapFilters::getBlurredColorPart(
    uint8_t const centerColorPart, uint8_t const colorToComparePart, uint32_t const similarityColorLimit) {
    uint8_t blurredColorPart(colorToComparePart);
    auto positiveDelta(getPositiveDelta<uint32_t>(centerColorPart, colorToComparePart));
    if (positiveDelta > similarityColorLimit) {
        if (centerColorPart > colorToComparePart) {
            blurredColorPart = centerColorPart - similarityColorLimit;
        } else {
            blurredColorPart = centerColorPart + similarityColorLimit;
        }
    }
    return blurredColorPart;
}

bool BitmapFilters::isThisPenCircleBetter(
    BitmapXY const& penBitmapXY, Circle const& circleToCheck, Circle const& circleToCompare) {
    bool isBetter(false);
    if (circleToCheck.getRadius() == circleToCompare.getRadius()) {
        Point const penPoint(convertBitmapXYToPoint(penBitmapXY));
        isBetter = twoDimensionsUtilities::getDistance(penPoint, circleToCheck.getCenter()) <
                   twoDimensionsUtilities::getDistance(penPoint, circleToCompare.getCenter());
    } else {
        isBetter = circleToCheck.getRadius() > circleToCompare.getRadius();
    }
    return isBetter;
}

}  // namespace alba::AprgBitmap
