#include <AprgGnuPlot/AprgGnuPlot3D.hpp>

using namespace alba::ThreeDimensions;
using namespace std;

namespace alba {

void AprgGnuPlot3D::graph(PointsInGraph const& points, string const& graphName, string const& configurationString) {
    m_gnuPlot << m_gnuPlot.binFile1d(points, "record") << " " << configurationString << " title '" << graphName << "'";
    m_gnuPlot << ", ";
}

void AprgGnuPlot3D::graph(
    ThreeDimensions::Points const& geometryPoints, string const& graphName, string const& configurationString) {
    PointsInGraph points;
    for (auto const& point : geometryPoints) {
        points.emplace_back(make_pair(make_pair(point.getX(), point.getY()), point.getZ()));
    }
    graph(points, graphName, configurationString);
}

AprgGnuPlot3D::PointInGraph AprgGnuPlot3D::getPoint(double const x, double const y, double const z) {
    return static_cast<AprgGnuPlot3D::PointInGraph>(make_pair(make_pair(x, y), z));
}

void AprgGnuPlot3D::startGraph() { m_gnuPlot << "splot "; }

}  // namespace alba
