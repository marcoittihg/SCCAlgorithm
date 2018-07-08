
#include "SCCAlgorithm/StrongConnectedComponents.h"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/timer/timer.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/connected_components.hpp>

#include <fstream>




int main() {
    typedef boost::adjacency_list<boost::multimapS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(0);

    VertexType v0 = boost::add_vertex(g);
    VertexType v1 = boost::add_vertex(g);
    VertexType v2 = boost::add_vertex(g);
    VertexType v3 = boost::add_vertex(g);
    VertexType v4 = boost::add_vertex(g);
    VertexType v5 = boost::add_vertex(g);
    VertexType v6 = boost::add_vertex(g);
    VertexType v7 = boost::add_vertex(g);
    VertexType v8 = boost::add_vertex(g);

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v0,g);
    boost::add_edge(v2,v3,g);
    boost::add_edge(v2,v6,g);
    boost::add_edge(v3,v5,g);
    boost::add_edge(v5,v4,g);
    boost::add_edge(v4,v3,g);
    boost::add_edge(v4,v7,g);
    boost::add_edge(v6,v7,g);
    boost::add_edge(v7,v8,g);
    boost::add_edge(v8,v6,g);
    boost::add_edge(v3,v6,g);

    boost::strong_components(g, map);
    //boost::strongConnectedComponents(g, map);

    return 0;
}