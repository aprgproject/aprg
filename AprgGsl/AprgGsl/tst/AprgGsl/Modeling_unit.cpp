#include <AprgGsl/Modeling.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>

#include <gtest/gtest.h>

using namespace std;

#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_SIMPLE_DATA_SET \
    APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\SimpleDataSet.csv)"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_DATA1 \
    APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\FileFormat1_DataSet1.csv)"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_DATA2 \
    APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\FileFormat1_DataSet2.csv)"
#define ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_DATA1 \
    APRG_DIR R"(\AprgGsl\FilesForTests\DataSets\FileFormat2_DataSet1.csv)"

namespace alba {

TEST(SampleTest, TestForSimpleDataSet) {
    AlbaLocalPathHandler testFilePath(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_SIMPLE_DATA_SET);
    Modeling modeling;
    modeling.retrieveDataFromFileWithFileFormat1(testFilePath.getFullPath());
    modeling.printRetrievedData();
    unsigned int numberOfSamples(modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingData(numberOfSamples);
    modeling.saveRetrievedDataToValidationData(numberOfSamples);

    modeling.modelUsingLeastSquares();

    modeling.printModelingData();
    modeling.printValidationData();
    Modeling::ValidationResult result = modeling.validate();
    cout << "totalSquareError: " << std::setprecision(20) << result.totalSquareError << "\n";
    cout << "resultSize: " << std::setprecision(20) << result.resultSize << "\n";
    cout << "meanSquareError: " << std::setprecision(20) << result.meanSquareError << "\n";
    cout << "rootMeanSquareError: " << std::setprecision(20) << result.rootMeanSquareError << "\n";

    Modeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout << "Coefficients:" << coefficients << "\n";
}

TEST(SampleTest, TestForFileFormat1) {
    AlbaLocalPathHandler testFilePath(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT1_DATA1);
    Modeling modeling;
    modeling.retrieveDataFromFileWithFileFormat1(testFilePath.getFullPath());
    modeling.printRetrievedData();
    unsigned int numberOfSamples(modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingData(numberOfSamples);  // include all samples
    modeling.saveRetrievedDataToValidationData(numberOfSamples);

    modeling.modelUsingLeastSquares();

    modeling.printModelingData();
    modeling.printValidationData();
    Modeling::ValidationResult result = modeling.validate();
    cout << "totalSquareError: " << std::setprecision(20) << result.totalSquareError << "\n";
    cout << "resultSize: " << std::setprecision(20) << result.resultSize << "\n";
    cout << "meanSquareError: " << std::setprecision(20) << result.meanSquareError << "\n";
    cout << "rootMeanSquareError: " << std::setprecision(20) << result.rootMeanSquareError << "\n";

    Modeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout << "Coefficients:" << coefficients << "\n";
}

TEST(SampleTest, TestForFileFormat2) {
    AlbaLocalPathHandler testFilePath(ALBA_MODELING_DATA_SET_WITH_FILE_FORMAT2_DATA1);
    Modeling modeling;
    modeling.retrieveDataFromFileWithFileFormat2(testFilePath.getFullPath());
    modeling.printRetrievedData();
    unsigned int numberOfSamples(modeling.getNumberOfSamples());
    modeling.saveRetrievedDataToModelingData(numberOfSamples);
    modeling.saveRetrievedDataToValidationData(numberOfSamples);

    modeling.modelUsingLeastSquares();

    modeling.printModelingData();
    modeling.printValidationData();
    Modeling::ValidationResult result = modeling.validate();
    cout << "totalSquareError: " << std::setprecision(20) << result.totalSquareError << "\n";
    cout << "resultSize: " << std::setprecision(20) << result.resultSize << "\n";
    cout << "meanSquareError: " << std::setprecision(20) << result.meanSquareError << "\n";
    cout << "rootMeanSquareError: " << std::setprecision(20) << result.rootMeanSquareError << "\n";

    Modeling::MatrixOfDoubles coefficients(modeling.getCoefficients());
    cout << "Coefficients:" << coefficients << "\n";
}

}  // namespace alba
