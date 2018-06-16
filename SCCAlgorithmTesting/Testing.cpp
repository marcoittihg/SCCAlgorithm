//
// Created by Marco on 16/06/18.
//


#define BOOST_TEST_MODULE SCCTesting
#include <boost/test/included/unit_test.hpp>

#include "../SCCAlgorithm/StronglyConnectedComponents.h"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>

BOOST_AUTO_TEST_CASE( test_case_empty_directed ){
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(0);

    boost::strongConnectedComponents(g, map);

    BOOST_TEST( results.empty() );
}
BOOST_AUTO_TEST_CASE( test_case_empty_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(0);

    boost::strongConnectedComponents(g, map);

    BOOST_TEST( results.empty() );
}

BOOST_AUTO_TEST_CASE( test_case_just_vertices_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(10);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}
BOOST_AUTO_TEST_CASE( test_case_just_vertices_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(10);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_chain_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}
BOOST_AUTO_TEST_CASE( test_case_chain_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second != it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_chain_with_self_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);

    boost::add_edge(0,0,g);
    boost::add_edge(1,1,g);
    boost::add_edge(2,2,g);
    boost::add_edge(3,3,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second == it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}
BOOST_AUTO_TEST_CASE( test_case_chain_with_self_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);

    boost::add_edge(0,0,g);
    boost::add_edge(1,1,g);
    boost::add_edge(2,2,g);
    boost::add_edge(3,3,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second != it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_half_circle_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::add_edge(4,2,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) != results.at(1)) &&
                  (results.at(1) != results.at(2)) &&
                  (results.at(2) == results.at(3)) &&
                  (results.at(3) == results.at(4));

    BOOST_TEST( result );
}
BOOST_AUTO_TEST_CASE( test_case_half_circle_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::add_edge(4,2,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1)) &&
                  (results.at(1) == results.at(2)) &&
                  (results.at(2) == results.at(3)) &&
                  (results.at(3) == results.at(4));

    BOOST_TEST( result );
}

BOOST_AUTO_TEST_CASE( test_case_circle_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::add_edge(4,0,g);

    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second != it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}
BOOST_AUTO_TEST_CASE( test_case_circle_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(5);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,3,g);
    boost::add_edge(3,4,g);
    boost::add_edge(4,0,g);
    boost::strongConnectedComponents(g, map);

    bool found = false;

    for(std::map<int, int> ::const_iterator it1 = results.begin();
        it1 != results.end(); ++it1){

        for(std::map<int, int> ::const_iterator it2 = results.begin();
            it2 != results.end(); ++it2) {

            if(it1->first != it2->first)
                if(it1->second != it2->second)
                    found = true;
        }
    }

    BOOST_TEST( !found );
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) != results.at(3));

    BOOST_TEST(result);
}
BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) != results.at(3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::add_edge(2,3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) != results.at(3));

    BOOST_TEST(result);
}
BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::add_edge(2,3,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) == results.at(3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link_with_self_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::add_edge(2,3,g);

    boost::add_edge(0,0,g);
    boost::add_edge(1,1,g);
    boost::add_edge(2,2,g);
    boost::add_edge(3,3,g);
    boost::add_edge(4,4,g);
    boost::add_edge(5,5,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) != results.at(3));

    BOOST_TEST(result);
}
BOOST_AUTO_TEST_CASE( test_case_two_disjoint_circles_link_with_self_undirected ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(6);
    boost::add_edge(0,1,g);
    boost::add_edge(1,2,g);
    boost::add_edge(2,0,g);

    boost::add_edge(3,4,g);
    boost::add_edge(4,5,g);
    boost::add_edge(5,3,g);

    boost::add_edge(2,3,g);

    boost::add_edge(0,0,g);
    boost::add_edge(1,1,g);
    boost::add_edge(2,2,g);
    boost::add_edge(3,3,g);
    boost::add_edge(4,4,g);
    boost::add_edge(5,5,g);

    boost::strongConnectedComponents(g, map);

    bool result = (results.at(0) == results.at(1) && results.at(1) == results.at(2) && results.at(2) == results.at(0))
                  &&
                  (results.at(3) == results.at(4) && results.at(4) == results.at(5) && results.at(5) == results.at(3))
                  &&
                  (results.at(2) == results.at(3));

    BOOST_TEST(result);
}

BOOST_AUTO_TEST_CASE( test_case_complete_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

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

    std::cout<<"a"<<std::endl;
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
BOOST_AUTO_TEST_CASE( test_case_complete_with_self_directed ) {
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

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

    std::cout<<"a"<<std::endl;
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
