#include "AlbaGrepFile.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <fstream>

using namespace std;

namespace alba {

AlbaGrepFile::AlbaGrepFile(string const& lineCondition)
    : m_isOutputFileWritten(false), m_lineGrepEvaluator(lineCondition) {}

AlbaGrepFile::AlbaGrepFile(string const& lineCondition, UpdateFunctionWithPercentage const& function)
    : m_isOutputFileWritten(false),
      m_lineGrepEvaluator(lineCondition),
      m_updateFunctionAfterOneIterationOptional(function) {}

bool AlbaGrepFile::isOutputFileWritten() const { return m_isOutputFileWritten; }

void AlbaGrepFile::processFile(string const& inputFilePath, string const& outputFilePath) {
    m_isOutputFileWritten = false;
    AlbaLocalPathHandler const inputPathHandler(inputFilePath);
    AlbaLocalPathHandler const outputPathHandler(outputFilePath);
    ifstream inputFileStream(inputPathHandler.getPath());
    ofstream outputFileStream(outputPathHandler.getPath());
    AlbaFileReader fileReader(inputFileStream);
    double const sizeOfFile = fileReader.getFileSize();
    while (fileReader.isNotFinished()) {
        string const lineInLogs(fileReader.getLineAndIgnoreWhiteSpaces());
        if (m_lineGrepEvaluator.evaluate(lineInLogs)) {
            m_isOutputFileWritten = true;
            outputFileStream << lineInLogs << "\n";
        }
        if (fileReader.isNotFinished()) {
            updateAfterOneIteration(fileReader.getCurrentLocation() * 100 / sizeOfFile);
        }
    }
    updateAfterOneIteration(100);
}

AlbaGrepStringEvaluator& AlbaGrepFile::getGrepEvaluator() { return m_lineGrepEvaluator; }

void AlbaGrepFile::updateAfterOneIteration(double const percentage) {
    if (m_updateFunctionAfterOneIterationOptional) {
        m_updateFunctionAfterOneIterationOptional.value()(percentage);
    }
}

}  // namespace alba
