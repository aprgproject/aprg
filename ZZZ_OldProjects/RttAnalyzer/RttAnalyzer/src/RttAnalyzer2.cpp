#include "RttAnalyzer2.hpp"

#include <Common/File/AlbaFileReader.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace alba::stringHelper;
using namespace std;

namespace alba {

RttAnalyzer2::RttAnalyzer2(string const& outputFilePath) : m_outputLogStream(outputFilePath) {}
void RttAnalyzer2::saveTitle2() { m_outputLogStream << "fileName,dateTime,maxPos,refPos,difference\n"; }

void RttAnalyzer2::processFile2(string const& file) {
    AlbaLocalPathHandler const pathHandler(file);
    ifstream logStream(pathHandler.getPath());

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string const lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            processLine2(pathHandler.getFile().string(), lineInFile);
        }
    }
}

void RttAnalyzer2::processLine2(string const& fileName, string const& line) {
    static string dateTime;
    if (isStringFoundNotCaseSensitive(line, "2019 Apr")) {
        dateTime = getStringInBetweenTwoStrings(line, "2019 Apr  3  ", "  [");
    } else if (isStringFoundNotCaseSensitive(line, "RXD_FILT")) {
        auto maxPos = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "max_pos[0]: "));
        auto refPos = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "ref_pos: "));
        int const difference = static_cast<int>(maxPos) - static_cast<int>(refPos);
        m_outputLogStream << fileName << "," << dateTime << "," << maxPos << "," << refPos << "," << difference << "\n";
    }
}

void RttAnalyzer2::processFile(string const& file) {
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getPath());
    ofstream outputLogStream(pathHandler.getDirectory() / "BtsLogRtt.csv");
    pathHandler.input(pathHandler.getDirectory().string() + pathHandler.getFilenameOnly().string() + ".csv");
    ofstream const collectedRttDetails(pathHandler.getPath());

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string const lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            if (isStringFoundNotCaseSensitive(lineInFile, "final RTT value reported to DSP explorer")) {
                processLine(outputLogStream, lineInFile);
            }
        }
    }
}

void RttAnalyzer2::processLine(ofstream& outputFile, string const& line) {
    static string const dateTime;
    string const time = getStringInBetweenTwoStrings(line, "<", "Z>");
    auto rtt = convertStringToNumber<unsigned int>(
        getStringAfterThisString(line, "final RTT value reported to DSP explorer = "));
    outputFile << time << "," << rtt << "\n";
}

void RttAnalyzer2::processFile3(string const& file) {
    AlbaLocalPathHandler pathHandler(file);
    ifstream logStream(pathHandler.getPath());
    ofstream outputLogStream(pathHandler.getDirectory() / "PeakPosCx8FromUeLogs.csv");
    pathHandler.input(pathHandler.getDirectory().string() + pathHandler.getFilenameOnly().string() + ".csv");
    ofstream const collectedRttDetails(pathHandler.getPath());

    outputLogStream << "peak_pos_cx8\n";

    if (logStream.is_open()) {
        AlbaFileReader logFileReader(logStream);

        while (logFileReader.isNotFinished()) {
            string const lineInFile(logFileReader.getLineAndIgnoreWhiteSpaces());
            if (isStringFoundNotCaseSensitive(lineInFile, "peak_pos_cx8")) {
                processLine3(outputLogStream, lineInFile);
            }
        }
    }
}

void RttAnalyzer2::processLine3(ofstream& outputFile, string const& line) {
    static string const dateTime;
    auto peakPosCx8 = convertStringToNumber<unsigned int>(getNumberAfterThisString(line, "peak_pos_cx8 "));
    outputFile << peakPosCx8 << "\n";
}

}  // namespace alba
