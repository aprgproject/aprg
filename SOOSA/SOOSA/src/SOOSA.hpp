#pragma once

#include <Bitmap/Bitmap.hpp>
#include <Bitmap/BitmapSnippet.hpp>
#include <Common/Container/AlbaValueRange.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <Geometry/TwoDimensions/Line.hpp>
#include <Geometry/TwoDimensions/Point.hpp>
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

namespace alba
{

namespace soosa
{

class SOOSA
{
public:
    class FrequencyDatabase
    {
    public:
        FrequencyDatabase(unsigned int const numberOfQuestions, unsigned int const numberOfChoices);
        void initialize();
        void addAnswer(unsigned int const questionNumber, unsigned int const answer);
        unsigned int getFrequencyOfAnswer(unsigned int const questionNumber, unsigned int const answer) const;
    private:
        unsigned int m_numberOfQuestions;
        unsigned int m_numberOfChoices;
        matrix::AlbaMatrix<unsigned int> m_frequenciesOnQuestionByAnswer;
    };

    class ColumnLineDetail
    {
    public:
        ColumnLineDetail(TwoDimensions::Point const& point, double const width);
        TwoDimensions::Point getPoint() const;
        double getWidth() const;
    private:
        TwoDimensions::Point m_point;
        double m_width;
    };

    class Status
    {
        Status();
    public:
        static Status getInstance();
        std::string getStatusString() const;
        void setError(std::string const& error);
        void clearErrors();
        bool isStatusNoError() const;
    private:
        alba::stringHelper::strings m_errors;
    };

    using RangeOfInts = AlbaValueRange<int>;
    using RangeOfDoubles = AlbaValueRange<double>;
    using VectorOfDoubles = std::vector<double>;
    using QuestionBarCoordinate = std::pair<TwoDimensions::Point, TwoDimensions::Point>;
    using QuestionBarCoordinates = std::vector<QuestionBarCoordinate>;
    using VectorOfColumnLineDetails = std::vector<ColumnLineDetail>;
    using OneDimensionKMeans = KMeansClustering<1>;
    using TwoDimensionKMeans = KMeansClustering<2>;
    using OneDimensionStatistics = DataStatistics<1>;
    using DequeOfPoints = std::deque<TwoDimensions::Point>;

    SOOSA(SoosaConfiguration const& soosaConfiguration, InputConfiguration const& inputConfiguration);
    unsigned int getNumberOfAnswers() const;
    unsigned int getAnswerToQuestion(unsigned int const questionNumber) const;
    void process();

private:
    std::string getCsvFileName(std::string const& path) const;
    std::string getReportHtmlFileName(std::string const& path) const;
    std::string getPrintableStringForPercentage(double const numerator, double const denominator) const;
    void setAnswerToQuestionInColumn(unsigned int const columnNumber, unsigned int const questionOffsetInColumn, unsigned int const answer);
    void saveDataToCsvFile(std::string const& processedFilePath) const;
    void saveHeadersToCsvFile() const;
    void saveOutputHtmlFile(std::string const& processedFilePath) const;
    void saveTableToOutputHtmlFile(std::ofstream & reportHtmlFileStream) const;
    void saveFrequencyDatabaseIfNoError();

    void processDirectory(std::string const & directoryPath);
    void processFile(std::string const & filePath);

    TwoDimensions::Line findLeftLine(AprgBitmap::BitmapSnippet const& snippet) const;
    TwoDimensions::Line findRightLine(AprgBitmap::BitmapSnippet const& snippet) const;
    TwoDimensions::Line findTopLine(AprgBitmap::BitmapSnippet const& snippet) const;
    TwoDimensions::Line findBottomLine(AprgBitmap::BitmapSnippet const& snippet) const;
    TwoDimensions::Line findVerticalLine(AprgBitmap::BitmapSnippet const& snippet, RangeOfInts const& range) const;
    TwoDimensions::Line findHorizontalLine(AprgBitmap::BitmapSnippet const& snippet, RangeOfInts const& range) const;
    TwoDimensions::Line findLeftLineUsingStartingLine(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& startingLine) const;
    TwoDimensions::Line findRightLineUsingStartingLine(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& startingLine) const;
    TwoDimensions::Line findVerticalLineUsingStartingLine(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& startingLine, RangeOfInts const& rangeForX) const;
    TwoDimensions::Line getLineModel(TwoDimensionsStatistics::Samples const& samples) const;

    VectorOfDoubles getAcceptableSquareErrorsUsingRetainRatio(TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const;
    void updateSamplesForLineModelingFromSquareErrorToSampleMultimap(TwoDimensionsStatistics::Samples & samplesLineModeling, TwoDimensionsStatistics::ValueToSampleMultimap const& squareErrorToSampleMultimap) const;

    void processColumn(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& leftLine, TwoDimensions::Line const& rightLine, unsigned int const columnNumber);
    unsigned int getAnswerToQuestionAndChangeNumberSelectedChoices(unsigned int & numberOfSelectedChoices, AprgBitmap::BitmapSnippet const& snippet, QuestionBarCoordinate const& leftCoordinate, QuestionBarCoordinate const& rightCoordinate) const;
    bool isChoiceShaded(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Point const& leftPoint, TwoDimensions::Point const& rightPoint, unsigned int const choiceIndex, unsigned int const radius) const;
    QuestionBarCoordinates getQuestionBarCoordinatesFromLine(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& line, unsigned int const numberQuestionsInColumn) const;
    VectorOfColumnLineDetails getAcceptableColumnLineDetails(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& line) const;
    RangeOfDoubles getMinMaxRangeFromKMeansSamples(OneDimensionKMeans::Samples const& samples) const;
    TwoDimensions::Point getNearestBlackPointFromLine(AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& line, TwoDimensions::Point const& pointInLine) const;
    void addColumnLineDetailIfAcceptable(VectorOfColumnLineDetails & columnLineDetails, AprgBitmap::BitmapSnippet const& snippet, TwoDimensions::Line const& line, TwoDimensions::Point const& blackPoint) const;
    void retrieveBarPointsThatFitAndSaveToKMeans(TwoDimensionKMeans & barPointKMeans, VectorOfColumnLineDetails const& pointsAndWidths, RangeOfDoubles const& minMaxForBar) const;
    void removeIncorrectBarPointsBasedFromHeight(TwoDimensionKMeans & barPointKMeans, unsigned int const numberQuestionsInColumn) const;
    void saveHeightDetailsFromBarPoints(TwoDimensionKMeans::GroupOfSamples const& groupOfGroupOfBarPoints, OneDimensionStatistics::Samples & barHeights, DataCollection<double> & heightCollection) const;
    void saveQuestionBarCoordinatesFromKMeansWithBarPoints(TwoDimensionKMeans const& barPointKMeans, QuestionBarCoordinates & questionBarCoordinates, unsigned int const numberQuestionsInColumn) const;

    // debug

    AprgBitmap::BitmapXY convertToBitmapXY(TwoDimensions::Point const& point) const;
    AprgBitmap::BitmapXY convertToBitmapXY(TwoDimensionsStatistics::Sample const& sample) const;
    TwoDimensions::Point convertToPoint(AprgBitmap::BitmapXY const& bitmapXY) const;
    TwoDimensions::Point convertToPoint(TwoDimensionsStatistics::Sample const& sample) const;
    TwoDimensionsStatistics::Sample convertToTwoDimensionSample(TwoDimensions::Point const& point) const;

    SoosaConfiguration m_soosaConfiguration;
    InputConfiguration m_inputConfiguration;
    unsigned int m_numberOfRespondents;
    std::map<unsigned int, unsigned int> m_questionToAnswersMap;
    FrequencyDatabase m_frequencyDatabase;
};

}

}
