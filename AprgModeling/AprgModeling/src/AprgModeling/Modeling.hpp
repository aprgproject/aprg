#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <string>
#include <vector>

namespace alba {

class Modeling {
public:
    struct ValidationResult {
        double totalSquareError;
        double resultSize;
        double meanSquareError;
        double rootMeanSquareError;
    };

    using VectorOfDoubles = std::vector<double>;
    using MatrixOfDoubles = matrix::AlbaMatrix<double>;
    Modeling();
    [[nodiscard]] unsigned int getNumberOfSamples [[nodiscard]] () const;
    [[nodiscard]] MatrixOfDoubles getCoefficients() const;
    void retrieveDataFromFileWithFileFormat1(std::string const& filePath);
    void retrieveDataFromFileWithFileFormat2(std::string const& filePath);

    void saveRetrievedDataForXAndY(
        unsigned int const numberOfIndicators, unsigned int const numberOfSamples,
        VectorOfDoubles const& retrievedDataForX, VectorOfDoubles const& retrievedDataForY);

    void saveRetrievedDataToModelingDataRandomly(unsigned int const numberOfSamples);
    void saveRetrievedDataToValidationDataRandomly(unsigned int const numberOfSamples);
    void saveRetrievedDataToModelingData(unsigned int const numberOfSamples);
    void saveRetrievedDataToValidationData(unsigned int const numberOfSamples);
    void printRetrievedData();
    void printModelingData();
    void printValidationData();
    void modelUsingLeastSquares();
    ValidationResult validate();

private:
    void saveRetrievedDataToMatrixRandomly(
        MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY, unsigned int const numberOfSamples);

    void saveRetrievedDataToMatrix(
        MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY, unsigned int const numberOfSamples);

    void calculateCoefficientsUsingLeastSquares();

    static void copyVectorToMatrix(
        unsigned int const numberOfColumns, unsigned int const numberOfRows, VectorOfDoubles const& retrievedDataForX,
        MatrixOfDoubles& matrixOfDoubles);

    static void printData(MatrixOfDoubles& matrixInX, MatrixOfDoubles& matrixInY);
    static unsigned int getIndex(unsigned int const i, unsigned int const j, unsigned int const numberOfColumns);
    MatrixOfDoubles m_coefficients;
    MatrixOfDoubles m_modelingDataForX;
    MatrixOfDoubles m_modelingDataForY;
    MatrixOfDoubles m_validationDataForX;
    MatrixOfDoubles m_validationDataForY;
    MatrixOfDoubles m_retrievedDataForX;
    MatrixOfDoubles m_retrievedDataForY;
};

}  // namespace alba
