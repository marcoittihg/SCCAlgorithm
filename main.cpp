
#include "SCCAlgorithm/StronglyConnectedComponents.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>

int main() {

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    std::map<int, std::vector<int>> results;
    boost::associative_property_map<std::map<int, std::vector<int>>> map(results);

    Graph g;
    computeSCC(g, map);

    return 0;
}