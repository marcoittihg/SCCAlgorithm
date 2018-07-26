//
// Created by Marco on 25/06/18.
//


#define BOOST_TEST_MODULE SCCTestingNuutila

#include <boost/test/included/unit_test.hpp>

#include "../SCCAlgorithm/StrongConnectedComponentsNuutila.h"

#include <boost/graph/adjacency_matrix.hpp>

BOOST_AUTO_TEST_CASE( test_case_empty ){
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);


    Graph g(0);

    boost::strongConnectedComponents(g, map);

    BOOST_TEST( results.empty() );
}

BOOST_AUTO_TEST_CASE( test_case_just_vertices ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(10);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<VertexType, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<VertexType, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_chain ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(0);

    VertexType v0 = boost::add_vertex(g);
    VertexType v1 = boost::add_vertex(g);
    VertexType v2 = boost::add_vertex(g);
    VertexType v3 = boost::add_vertex(g);
    VertexType v4 = boost::add_vertex(g);

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v3,g);
    boost::add_edge(v3,v4,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<VertexType, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<VertexType, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_chain_with_self ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(0);
    VertexType v0 = boost::add_vertex(g);
    VertexType v1 = boost::add_vertex(g);
    VertexType v2 = boost::add_vertex(g);
    VertexType v3 = boost::add_vertex(g);
    VertexType v4 = boost::add_vertex(g);

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v3,g);
    boost::add_edge(v3,v4,g);

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<VertexType, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<VertexType, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_half_circle ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(0);

    VertexType v0 = boost::add_vertex(g);
    VertexType v1 = boost::add_vertex(g);
    VertexType v2 = boost::add_vertex(g);
    VertexType v3 = boost::add_vertex(g);
    VertexType v4 = boost::add_vertex(g);

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v3,g);
    boost::add_edge(v3,v4,g);
    boost::add_edge(v4,v2,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(v0) != results.at(v1)) &&
                  (results.at(v1) != results.at(v2)) &&
                  (results.at(v2) == results.at(v3)) &&
                  (results.at(v3) == results.at(v4));

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_circle ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(0);

    VertexType v0 = boost::add_vertex(g);
    VertexType v1 = boost::add_vertex(g);
    VertexType v2 = boost::add_vertex(g);
    VertexType v3 = boost::add_vertex(g);
    VertexType v4 = boost::add_vertex(g);

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v3,g);
    boost::add_edge(v3,v4,g);
    boost::add_edge(v4,v0,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<VertexType, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<VertexType, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second != it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v0,g);

    boost::add_edge(v3,v4,g);
    boost::add_edge(v4,v5,g);
    boost::add_edge(v5,v3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(v0) == results.at(v1) && results.at(v1) == results.at(v2) && results.at(v2) == results.at(v0))
                  &&
                  (results.at(v3) == results.at(v4) && results.at(v4) == results.at(v5) && results.at(v5) == results.at(v3))
                  &&
                  (results.at(v2) != results.at(v3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v0,g);

    boost::add_edge(v3,v4,g);
    boost::add_edge(v4,v5,g);
    boost::add_edge(v5,v3,g);

    boost::add_edge(v2,v3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(v0) == results.at(v1) && results.at(v1) == results.at(v2) && results.at(v2) == results.at(v0))
                  &&
                  (results.at(v3) == results.at(v4) && results.at(v4) == results.at(v5) && results.at(v5) == results.at(v3))
                  &&
                  (results.at(v2) != results.at(v3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link_with_self ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v1,g);
    boost::add_edge(v1,v2,g);
    boost::add_edge(v2,v0,g);

    boost::add_edge(v3,v4,g);
    boost::add_edge(v4,v5,g);
    boost::add_edge(v5,v3,g);

    boost::add_edge(v2,v3,g);

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(v0) == results.at(v1) && results.at(v1) == results.at(v2) && results.at(v2) == results.at(v0))
                  &&
                  (results.at(v3) == results.at(v4) && results.at(v4) == results.at(v5) && results.at(v5) == results.at(v3))
                  &&
                  (results.at(v2) != results.at(v3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_complete_vecS_vecS ) {
    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_listS ) {
    typedef boost::adjacency_list<boost::vecS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_setS ) {
    typedef boost::adjacency_list<boost::vecS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_mapS ) {
    typedef boost::adjacency_list<boost::vecS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_multisetS ) {
    typedef boost::adjacency_list<boost::vecS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_multimapS ) {
    typedef boost::adjacency_list<boost::vecS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_hash_setS ) {
    typedef boost::adjacency_list<boost::vecS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_hash_mapS ) {
    typedef boost::adjacency_list<boost::vecS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::vecS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_vecS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::vecS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_listS_vecS ) {
    typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_listS ) {
    typedef boost::adjacency_list<boost::listS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_setS ) {
    typedef boost::adjacency_list<boost::listS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_mapS ) {
    typedef boost::adjacency_list<boost::listS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_multisetS ) {
    typedef boost::adjacency_list<boost::listS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_multimapS ) {
    typedef boost::adjacency_list<boost::listS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_hash_setS ) {
    typedef boost::adjacency_list<boost::listS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_hash_mapS ) {
    typedef boost::adjacency_list<boost::listS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::listS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_listS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::listS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_setS_vecS ) {
    typedef boost::adjacency_list<boost::setS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_listS ) {
    typedef boost::adjacency_list<boost::setS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_setS ) {
    typedef boost::adjacency_list<boost::setS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_mapS ) {
    typedef boost::adjacency_list<boost::setS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_multisetS ) {
    typedef boost::adjacency_list<boost::setS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_multimapS ) {
    typedef boost::adjacency_list<boost::setS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_hash_setS ) {
    typedef boost::adjacency_list<boost::setS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_hash_mapS ) {
    typedef boost::adjacency_list<boost::setS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::setS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_setS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::setS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_mapS_vecS ) {
    typedef boost::adjacency_list<boost::mapS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_listS ) {
    typedef boost::adjacency_list<boost::mapS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_setS ) {
    typedef boost::adjacency_list<boost::mapS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_mapS ) {
    typedef boost::adjacency_list<boost::mapS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_multisetS ) {
    typedef boost::adjacency_list<boost::mapS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_multimapS ) {
    typedef boost::adjacency_list<boost::mapS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_hash_setS ) {
    typedef boost::adjacency_list<boost::mapS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_hash_mapS ) {
    typedef boost::adjacency_list<boost::mapS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::mapS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_mapS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::mapS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_multisetS_vecS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_listS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_setS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_mapS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_multisetS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_multimapS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_hash_setS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_hash_mapS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multisetS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::multisetS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}
/*
BOOST_AUTO_TEST_CASE( test_case_complete_multimapS_vecS ) {
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}
/*
BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_listS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_setS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_mapS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_multisetS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_multimapS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_hash_setS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_hash_mapS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_multimapS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::multimapS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}
*/

BOOST_AUTO_TEST_CASE( test_case_complete_hash_setS_vecS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_listS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_setS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_mapS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_multisetS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_multimapS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_hash_setS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_hash_mapS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_setS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::hash_setS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_hash_mapS_vecS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_listS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_setS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_mapS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_multisetS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_multimapS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_hash_setS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_hash_mapS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_mapS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::hash_mapS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_hash_multisetS_vecS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_listS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_setS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_mapS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_multisetS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_multimapS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_hash_setS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_hash_mapS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multisetS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::hash_multisetS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_hash_multimapS_vecS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::vecS, boost::directedS> Graph;
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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_listS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::listS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_setS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_mapS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_multisetS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_multimapS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_hash_setS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::hash_setS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_hash_mapS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::hash_mapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_hash_multisetS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::hash_multisetS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_hash_multimapS_hash_multimapS ) {
    typedef boost::adjacency_list<boost::hash_multimapS, boost::hash_multimapS, boost::directedS, boost::property<boost::vertex_index_t, int> > Graph;

    typedef typename Graph::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

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

    boost::add_edge(v0,v0,g);
    boost::add_edge(v1,v1,g);
    boost::add_edge(v2,v2,g);
    boost::add_edge(v3,v3,g);
    boost::add_edge(v4,v4,g);
    boost::add_edge(v5,v5,g);
    boost::add_edge(v6,v6,g);
    boost::add_edge(v7,v7,g);
    boost::add_edge(v8,v8,g);


    //initialization of the index map
    VertexIterator i, iend;
    IndexMap indexMap = get(boost::vertex_index, g);
    int a = 0;
    for (boost::tie(i, iend) = boost::vertices(g); i != iend; ++i, ++a) {
        indexMap[*i] = a;
    }

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(v0) == results.at(v1) &&
            results.at(v1) == results.at(v2) &&
            results.at(v2) == results.at(v0) &&

            results.at(v3) == results.at(v4) &&
            results.at(v4) == results.at(v5) &&
            results.at(v5) == results.at(v3) &&

            results.at(v6) == results.at(v7) &&
            results.at(v7) == results.at(v8) &&
            results.at(v8) == results.at(v6) &&

            results.at(v0) != results.at(v3) &&
            results.at(v3) != results.at(v6) &&
            results.at(v0) != results.at(v6)
    );

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_complete_with_adjmatrix ) {
    typedef boost::adjacency_matrix<boost::directedS> Graph;

    typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;
    typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
    typedef typename boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;

    std::map<VertexType, int> results;
    boost::associative_property_map<std::map<VertexType, int>> map(results);

    Graph g(9);


    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);
    boost::add_edge(2,3,g);
    boost::add_edge(2,6,g);
    boost::add_edge(3,5,g);
    boost::add_edge(5,4,g);
    boost::add_edge(4,3,g);
    boost::add_edge(4,7,g);
    boost::add_edge(6,7,g);
    boost::add_edge(7,8,g);
    boost::add_edge(8,6,g);
    boost::add_edge(3,6,g);

    boost::add_edge(0,0,g);
    boost::add_edge(1,1,g);
    boost::add_edge(2,2,g);
    boost::add_edge(3,3,g);
    boost::add_edge(4,4,g);
    boost::add_edge(5,5,g);
    boost::add_edge(6,6,g);
    boost::add_edge(7,7,g);
    boost::add_edge(8,8,g);

    boost::strongConnectedComponents(g, map);

    bool result = (
            results.at(0) == results.at(1) &&
            results.at(1) == results.at(2) &&
            results.at(2) == results.at(0) &&

            results.at(3) == results.at(4) &&
            results.at(4) == results.at(5) &&
            results.at(5) == results.at(3) &&

            results.at(6) == results.at(7) &&
            results.at(7) == results.at(8) &&
            results.at(8) == results.at(6) &&

            results.at(0) != results.at(3) &&
            results.at(3) != results.at(6) &&
            results.at(0) != results.at(6)
    );

    BOOST_TEST( result );
}
