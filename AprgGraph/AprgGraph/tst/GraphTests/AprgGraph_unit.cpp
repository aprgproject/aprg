#include <Algebra/Equation/EquationUtilities.hpp>
#include <Algebra/Term/Utilities/StringHelpers.hpp>
#include <Common/PathHandler/AlbaLocalPathHandler.hpp>
#include <Graph/AprgGraph.hpp>

#include <gtest/gtest.h>

#include <cmath>

using namespace alba::AprgBitmap;
using namespace alba::algebra;
using namespace alba::TwoDimensions;
using namespace std;

#define APRG_GRAPH_24_BIT_DEFAULT_FILE APRG_DIR R"(\AprgGraph\FilesForTests\Bitmaps\Default24Bit.bmp)"
#define APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE APRG_DIR R"(\AprgGraph\FilesForTests\Bitmaps\GraphOutput.bmp)"

namespace alba {

TEST(AprgGraphTest, DISABLED_BitmapGraph24Bits) {
    AlbaLocalPathHandler const defaultFile(APRG_GRAPH_24_BIT_DEFAULT_FILE);
    AlbaLocalPathHandler const graphOutputFile(APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE);
    EXPECT_TRUE(graphOutputFile.deleteFileAndIsSuccessful());
    EXPECT_TRUE(defaultFile.copyFileToAndIsSuccessful(graphOutputFile.getPath()));

    AprgGraph graph(graphOutputFile.getPath(), BitmapXY(800, 450), BitmapDoubleXY(50, 50));
    graph.drawGrid(BitmapDoubleXY(static_cast<double>(5), static_cast<double>(5)));
    graph.drawLine(Line(1, 1, 1), 0x00FF0000);
    graph.drawCircle(Circle(Point(0, 0), 10), 0x000000FF);
    graph.drawEllipse(Ellipse(Point(0, 0), 15, 10), 0x0000FFFF);
    graph.drawHyperbola(Hyperbola(Point(0, 0), 10, 7.5), 0x0000FFFF);

    Term const polynomialTermInX(buildTermIfPossible("x^4 +- 2*x^3 - 7*x^2 + 10*x + 10"));
    Term const polynomialTermInY(buildTermIfPossible("y^4 - y^3 - y^2 - 2*y - 6"));
    graph.drawTermWithXYSubstitution(polynomialTermInX, 0x0055A1BA);
    graph.drawTermWithXYSubstitution(polynomialTermInY, 0x00A1BA55);

    Equation const equation1(buildEquationIfPossible("x*y - x^2 + 1 = 0"));
    Equation const equation2(buildEquationIfPossible("x^2 - 2*x*y + y^2 + 2*x - 3*y + 2 = 0"));
    Equation const equation3(buildEquationIfPossible("y^2 - x - 2 = 0"));
    Equation const equation4(buildEquationIfPossible("(x^2 + 9)/(x-2) = y"));
    graph.drawEquationWithXYSubstitution(equation1, 0x0000A1BA);
    graph.drawEquationWithXYSubstitution(equation2, 0x00A1BA00);
    graph.drawEquationWithXYSubstitution(equation3, 0x00A100BA);
    graph.drawEquationWithXYSubstitution(equation4, 0x0000BAA1);

    graph.drawFunctionUsingX(0x00AA0033, [](double const xValue) -> double { return 5 * sin(xValue / 2); });
    graph.drawFunctionUsingY(0x003300AA, [](double const yValue) -> double { return 5 * sin(yValue / 2); });
    graph.saveChangesToBitmapFile();
}

TEST(AprgGraphTest, DISABLED_TemporaryTest) {
    AlbaLocalPathHandler const defaultFile(APRG_GRAPH_24_BIT_DEFAULT_FILE);
    AlbaLocalPathHandler const graphOutputFile(APRG_GRAPH_24_BIT_GRAPH_OUTPUT_FILE);
    EXPECT_TRUE(graphOutputFile.deleteFileAndIsSuccessful());
    EXPECT_TRUE(defaultFile.copyFileToAndIsSuccessful(graphOutputFile.getPath()));

    AprgGraph graph(graphOutputFile.getPath(), BitmapXY(800, 450), BitmapDoubleXY(50, 50));
    graph.drawGrid(BitmapDoubleXY(static_cast<double>(5), static_cast<double>(5)));

    Equation const equation(buildEquationIfPossible("x^x = y"));
    graph.drawEquationWithXYSubstitution(equation, 0x0000A1BA);

    graph.saveChangesToBitmapFile();
}

}  // namespace alba
