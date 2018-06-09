//
// Created by Marco on 09/06/18.
//

#ifndef SCCALGORITHM_TESTS_H
#define SCCALGORITHM_TESTS_H

#include "SCCAlgorithm/StronglyConnectedComponents.h"

bool testDirectedEmpty(){
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(0);

    boost::strongConnectedComponents(g, map);

    for(std::map<int, int> ::const_iterator it = results.begin();
        it != results.end(); ++it){
        std::cout<< it->first << " - " << it->second << std::endl;
    }

    return results.empty();
};

bool testUndirectedEmpty(){
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS> Graph;

    Graph g(0);

    boost::strongConnectedComponents(g, map);

    for(std::map<int, int> ::const_iterator it = results.begin();
        it != results.end(); ++it){
        std::cout<< it->first << " - " << it->second << std::endl;
    }

    return results.empty();
};

bool testJustVertices(){
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(10);

    boost::strongConnectedComponents(g, map);

};

bool test1(){
    std::map<int, int> results;
    boost::associative_property_map<std::map<int, int>> map(results);

    typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

    Graph g(10);
    boost::add_edge(1, 2, g);
    boost::add_edge(2, 8, g);
    boost::add_edge(8, 1, g);

    boost::strongConnectedComponents(g, map);

};

#endif //SCCALGORITHM_TESTS_H
