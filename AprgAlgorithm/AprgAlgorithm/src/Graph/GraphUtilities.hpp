#pragma once

#include <Graph/GraphTypes.hpp>
#include <Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba
{

namespace algorithm
{

unsigned int getDegreeAt(BaseUndirectedGraph const& graph, Vertex const vertex);
unsigned int getMaxDegree(BaseUndirectedGraph const& graph);
double getAverageDegree(BaseUndirectedGraph const& graph);
unsigned int getNumberOfSelfLoops(BaseUndirectedGraph const& graph);

}

}
