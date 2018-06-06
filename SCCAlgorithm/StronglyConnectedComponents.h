//
// Created by Marco on 06/06/18.
//

#ifndef SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
#define SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H

#include <boost/graph/adjacency_list.hpp>
#include <iostream>

template<typename Graph, typename ComponentsMap>
inline typename boost::property_traits<ComponentsMap>::value_type
tarjanAlgorithm(Graph &g, ComponentsMap c) {
    typename boost::property_traits<ComponentsMap>::value_type total;

#ifndef SILENCE
    std::cout << "\t The graph is directed -> Tarjan algorithm"<<std::endl;
#endif

    return total;
};


template<typename Graph, typename ComponentsMap>
inline typename boost::property_traits<ComponentsMap>::value_type
searchComponentsDFS(Graph &g, ComponentsMap c) {
    typedef typename boost::property_traits<ComponentsMap>::value_type Count;

    Count count(0);

#ifndef SILENCE
    std::cout << "\t The graph is undirected -> simple DFS exploration until all nodes are in a component"<<std::endl;
#endif

    return count;

};

template<typename Graph, typename ComponentsMap>
typename boost::property_traits<ComponentsMap>::value_type
computeSCC(Graph &g, ComponentsMap c) {
    BOOST_CONCEPT_ASSERT((boost::VertexAndEdgeListGraphConcept<Graph>));
    using namespace boost;


#ifndef SILENCE
    std::cout << "Start of Strongly Connected Component Algorithm"<<std::endl;
#endif

    if (boost::is_directed(g)) {
        return tarjanAlgorithm(g,c);
    } else {
        return searchComponentsDFS(g,c);
    }
};

#endif //SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
