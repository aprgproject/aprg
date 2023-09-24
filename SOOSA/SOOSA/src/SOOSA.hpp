#pragma once

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Geometry/TwoDimensions/Constructs/Line.hpp>
#include <Geometry/TwoDimensions/Constructs/Point.hpp>
#include <InputConfiguration.hpp>
#include <SoosaConfiguration.hpp>
#include <Statistics/DataCollection.hpp>
#include <Statistics/KMeansClustering.hpp>
#include <Statistics/TwoDimensionsStatistics.hpp>

#include <array>
#include <deque>
#include <fstream>
#include <map>
#include <string>
#include <vector>

namespace alba::soosa {

class SOOSA {
public:
    enum class LineOrientation { ConsideredHorizontal, ConsideredVertical };

    class FrequencyDatabase {
    public:
        FrequencyDatabase(int const numberOfQuestions, int const numberOfChoices);
        [[nodiscard]] int getFrequencyOfAnswer(int const questionIndex, int const answerIndex) const;
        void initialize();
        void addAnswer(int const questionIndex, int const answerIndex);

    private:
        int m_numberOfQuestions;
        int m_numberOfChoices;
        matrix::AlbaMatrix<int> m_frequenciesOnQuestionByAnswer;
    };

    class Status {
        Status();

    public:
        [[nodiscard]] std::string getStatusString() const;
        [[nodiscard]] bool isStatusNoError() const;
        void setError(std::string const& error);
        void clearErrors();
        static Status& getInstance();

    private:
        alba::stringHelper::strings m_errors;
    };

    using Answers = std::vector<int>;
    using RangeOfInts = AlbaValueRange<int>;
    using RangeOfDoubles = AlbaValueRange<double>;
    using VectorOfDoubles = std::vector<double>;
    using Line = TwoDimensions::Line;
    using Point = TwoDimensions::Point;
    using Bitmap = AprgBitmap::Bitmap;
    using BitmapSnippet = AprgBitmap::BitmapSnippet;
    using BitmapXY = AprgBitmap::BitmapXY;
    using OneDimensionSample = DataSample<1>;
    using TwoDimensionSample = DataSample<2>;
    using OneDimensionSamples = std::vector<OneDimensionSample>;
    using TwoDimensionSamples = std::vector<TwoDimensionSample>;
    using GroupOfOneDimensionSamples = std::vector<OneDimensionSamples>;
    using GroupOfTwoDimensionSamples = std::vector<TwoDimensionSamples>;
    using ValueToTwoDimensionSampleMultimap = std::multimap<double, TwoDimensionSample>;
    using OneDimensionKMeans = KMeansClustering<1>;
    using TwoDimensionKMeans = KMeansClustering<2>;
    using OneDimensionStatistics = DataStatistics<1>;
    using TwoDimensionStatistics = DataStatistics<2>;
    using DoubleCollection = DataCollection<double>;
    using QuestionBarCoordinate = std::pair<Point, Point>;
    using QuestionBarCoordinates = std::vector<QuestionBarCoordinate>;
    using PointAndWidthPair = std::pair<Point, double>;
    using PointAndWidthPairs = std::vector<PointAndWidthPair>;
    using DequeOfPoints = std::deque<Point>;
    using EndPointIndexes = std::pair<int, int>;
    using CountToEndPointIndexesMultiMap = std::multimap<int, EndPointIndexes>;
    SOOSA(SoosaConfiguration const& soosaConfiguration, InputConfiguration const& inputConfiguration);
    SOOSA(SoosaConfiguration&& soosaConfiguration, InputConfiguration&& inputConfiguration);
    [[nodiscard]] int getNumberOfAnswers() const;
    [[nodiscard]] int getAnswerToQuestion(int const questionIndex) const;
    void process();

private:
    [[nodiscard]] Answers getAnswersAtQuestion(
        BitmapSnippet const& snippet, QuestionBarCoordinate const& leftCoordinate,
        QuestionBarCoordinate const& rightCoordinate) const;

    [[nodiscard]] DoubleCollection getAcceptableSquareErrorCollectionUsingRemovalRatio(
        ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap) const;

    [[nodiscard]] Line findLeftLine(BitmapSnippet const& snippet) const;
    [[nodiscard]] Line findRightLine(BitmapSnippet const& snippet) const;
    [[nodiscard]] Line findTopLine(BitmapSnippet const& snippet) const;
    [[nodiscard]] Line findBottomLine(BitmapSnippet const& snippet) const;
    [[nodiscard]] Line findLeftLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const;
    [[nodiscard]] Line findRightLineUsingStartingLine(BitmapSnippet const& snippet, Line const& startingLine) const;

    [[nodiscard]] Line findVerticalLineUsingStartingLine(
        BitmapSnippet const& snippet, Line const& startingLine, RangeOfInts const& rangeForX) const;

    // Line modeling functions
    [[nodiscard]] Line getLeftLineModel(TwoDimensionSamples& samples) const;
    [[nodiscard]] Line getRightLineModel(TwoDimensionSamples& samples) const;
    [[nodiscard]] Line getTopLineModel(TwoDimensionSamples& samples) const;
    [[nodiscard]] Line getBottomLineModel(TwoDimensionSamples& samples) const;
    [[nodiscard]] Line getLineModel(TwoDimensionSamples& samples) const;

    [[nodiscard]] Point getCenterOfCircleForChoiceChecking(
        BitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, double const radius,
        int const choiceIndex) const;

    [[nodiscard]] Point getNearestBlackPointFromLine(
        BitmapSnippet const& snippet, Line const& line, Point const& pointInLine) const;

    [[nodiscard]] Point getLeftOrRightMostBlackPoint(
        BitmapSnippet const& snippet, Point const& nearestBlackPoint, Line const& perpendicularLine,
        int const maxLineAndBarWidth, int const sign) const;

    [[nodiscard]] PointAndWidthPairs getAcceptablePointAndWidthPairs(
        BitmapSnippet const& snippet, Line const& line, Point const& startPoint, Point const& endPoint) const;

    [[nodiscard]] QuestionBarCoordinates getQuestionBarCoordinatesFromLine(
        BitmapSnippet const& snippet, Line const& line, Point const& startPoint, Point const& endPoint,
        int const numberQuestionsInColumn) const;

    // Widths functions
    [[nodiscard]] RangeOfDoubles getMinMaxCriteriaForBar(PointAndWidthPairs const& pointAndWidthPairs) const;

    [[nodiscard]] TwoDimensionSamples getSamplesInVerticalLine(
        BitmapSnippet const& snippet, RangeOfInts const& range) const;

    [[nodiscard]] TwoDimensionSamples getSamplesInHorizontalLine(
        BitmapSnippet const& snippet, RangeOfInts const& range) const;

    // output related functions
    [[nodiscard]] std::string getCsvFilePath(std::string const& path) const;
    [[nodiscard]] std::string getReportHtmlFilePath(std::string const& path) const;

    [[nodiscard]] double getShadePercentage(
        BitmapSnippet const& snippet, Point const& leftPoint, Point const& rightPoint, double const radius,
        int const choiceIndex) const;

    [[nodiscard]] double getRadiusForChoiceChecking(
        QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const;

    [[nodiscard]] double getMaximumDistanceForBetweenBarHeights(double const previousHeight) const;
    [[nodiscard]] int getMaximumLineAndBarWidth(BitmapSnippet const& snippet) const;
    // utilities
    [[nodiscard]] bool isBlackAt(BitmapSnippet const& snippet, BitmapXY const bitmapXy) const;
    void performStepsWhenNumberOfAnswersNotEqualToNumberOfQuestions() const;

    void removeFurthestSamplesUntilLineOrientationMatch(
        TwoDimensionSamples& samples, LineOrientation const lineOrientation) const;

    void removeErroneousSamplesInLine(TwoDimensionSamples& samples) const;

    void addAndRetainWidthsIfPossible(
        OneDimensionKMeans& kMeansForWidths, OneDimensionStatistics& groupStatistics,
        double const acceptableSdOverMeanDeviation) const;

    void addPointAndWidthPairIfAcceptable(
        PointAndWidthPairs& pointAndWidthPairs, BitmapSnippet const& snippet, Line const& line,
        Point const& pointInLine) const;

    // Height functions
    void removeBarPointsWithFewHeightPoints(
        TwoDimensionKMeans& kMeansForBarPoints, int const numberQuestionsInColumn) const;

    void removeBarPointsToGetConsistentHeight(
        TwoDimensionKMeans& kMeansForBarPoints, int const numberQuestionsInColumn) const;

    void addAndRetainBarPointsIfPossible(
        TwoDimensionKMeans& kMeansForBarPoints, GroupOfTwoDimensionSamples const& listOfGroupOfBarPoints,
        int const indexToRemove) const;

    void saveDataToCsvFile(std::string const& processedFilePath) const;
    void saveHeadersToCsvFile() const;
    void saveOutputHtmlFile(std::string const& processedFilePath) const;
    void saveTableToOutputHtmlFile(std::ofstream& reportHtmlFileStream) const;

    CountToEndPointIndexesMultiMap getHeightPointsCountToEndPointIndexesMultimap(
        TwoDimensionKMeans& kMeansForBarPoints) const;

    void processDirectory(std::string const& directoryPath);
    void processFile(std::string const& filePath);
    void processBitmapFile(Bitmap const& bitmap);
    void saveToFrequencyDatabase();

    // Column functions
    void processTwoColumns(
        BitmapSnippet const& globalSnippet, Line const& leftLine, Line const& rightLine, Line const& topLine,
        Line const& bottomLine);

    void processOneColumn(
        BitmapSnippet const& globalSnippet, Line const& leftLine, Line const& rightLine, Line const& topLine,
        Line const& bottomLine);

    void processColumn(
        int& questionNumber, BitmapSnippet const& snippet, Line const& leftLine, Line const& rightLine,
        Line const& topLine, Line const& bottomLine, int const columnNumber);

    void processQuestions(
        int& questionNumber, BitmapSnippet const& snippet, QuestionBarCoordinates const& questionBarsOnTheLeft,
        QuestionBarCoordinates const& questionsBarsOnTheRight, int const columnNumber,
        int const numberQuestionsInColumn);

    void setAnswerToQuestionInColumn(int const columnNumber, int const questionOffsetInColumn, int const answer);
    [[nodiscard]] static OneDimensionSamples getBarHeights(GroupOfTwoDimensionSamples const& groupOfBarPoints);
    [[nodiscard]] static double getHeight(TwoDimensionSamples const& barPoints);
    [[nodiscard]] static int getRetainSizeInLineModel(int const size, double const removalRatio);

    // find line
    [[nodiscard]] static bool areLinesValid(
        Line const& leftLine, Line const& rightLine, Line const& topLine, Line const& bottomLine);

    [[nodiscard]] static bool isConsideredHorizontal(double const aCoefficient, double const bCoefficient);
    [[nodiscard]] static bool isConsideredVertical(double const aCoefficient, double const bCoefficient);

    static void updateSamplesForLineModeling(
        TwoDimensionSamples& samplesLineModeling, ValueToTwoDimensionSampleMultimap const& squareErrorToSampleMultimap,
        double const maxAcceptableSquareError);

    static void retrieveBarPointsThatFitAndSaveToKMeans(
        TwoDimensionKMeans& kMeansForBarPoints, PointAndWidthPairs const& pointAndWidthPairs,
        RangeOfDoubles const& minMaxCriteriaForBar);

    static void saveQuestionBarCoordinatesFromKMeansWithBarPoints(
        QuestionBarCoordinates& questionBarCoordinates, TwoDimensionKMeans const& kMeansForBarPoints,
        int const numberQuestionsInColumn);

    static void removeBarPointsWithFewHeightPointsCount(
        TwoDimensionKMeans& kMeansForBarPoints, int const numberQuestionsInColumn,
        CountToEndPointIndexesMultiMap const& countToEndPointsIndexesMultiMap);

    static BitmapXY convertToBitmapXY(Point const& point);
    static BitmapXY convertToBitmapXY(TwoDimensionSample const& sample);
    static OneDimensionKMeans getKMeansForWidths(PointAndWidthPairs const& pointAndWidthPairs);
    static Point convertToPoint(BitmapXY const& bitmapXY);
    static Point convertToPoint(TwoDimensionSample const& sample);

    static RangeOfDoubles getMinMaxCriteriaForBar(
        OneDimensionStatistics& firstGroupStatistics, OneDimensionStatistics& secondGroupStatistics);

    static RangeOfDoubles getMinMaxRangeOfSamples(OneDimensionSamples const& samples);
    static TwoDimensionSample convertToTwoDimensionSample(Point const& point);
    static std::string getPrintableStringForPercentage(double const numerator, double const denominator);
    SoosaConfiguration m_soosaConfiguration;
    InputConfiguration m_inputConfiguration;
    int m_numberOfRespondents{};
    std::map<int, int> m_questionToAnswersMap;
    FrequencyDatabase m_frequencyDatabase;
};

}  // namespace alba::soosa
