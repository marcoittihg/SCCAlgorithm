//
// Created by Marco on 06/06/18.
//

#ifndef SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
#define SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <stack>

namespace boost {
    template<typename Graph, typename ComponentsMap>
    inline typename boost::property_traits<ComponentsMap>::value_type
    tarjanAlgorithm(Graph &g, ComponentsMap c, unsigned int nVertices) {

#ifndef SILENCE
        std::cout << "\t The graph is directed -> Tarjan algorithm" << std::endl;
#endif

        typedef typename boost::property_traits<ComponentsMap>::value_type Count;
        typedef typename graph_traits<Graph>::vertex_descriptor VertexType;
        typedef typename property_map<Graph, vertex_index_t>::type IndexMap;
        typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
        typedef typename boost::graph_traits<Graph>::degree_size_type OutDegree;
        typedef typename boost::graph_traits<Graph>::out_edge_iterator outEdgeIter;

        struct TarjanExe{
            Count count;
            Graph &g;
            ComponentsMap c;

        private:
            unsigned int index;
            unsigned int nVertices;
            boost::dynamic_bitset<> root;
            unsigned int* rIndex;
            IndexMap indexMap;
            std::stack<VertexType> iS, vS, S;

        public:
            TarjanExe(Graph &g, ComponentsMap c, unsigned int nVertices) : g(g), c(c), nVertices(nVertices) {
                count = Count(nVertices-1);
                root = boost::dynamic_bitset<>(nVertices);
                rIndex = new unsigned int[nVertices];

                for (int i = 0; i < nVertices; ++i) { rIndex[i] = 0; }

                index = 1;
                indexMap = get(vertex_index, g);
            }

            inline void beginVisiting(VertexType v){
#ifndef SILENCE
                std::cout << "\t\t\t Start visiting vertex " <<indexMap[v]<< std::endl;
#endif
                vS.push(v);
                iS.push(0);
                root[indexMap[v]] = true;
                rIndex[indexMap[v]] = index;

                index++;
            }

            inline void finishEdge(VertexType v, VertexType k){
                std::pair<outEdgeIter, outEdgeIter > iEdge = boost::out_edges(v, g);

                VertexType w = boost::target(*(iEdge.first + k), g);

                if(rIndex[indexMap[w]] < rIndex[indexMap[v]]) {
                    rIndex[indexMap[v]] = rIndex[indexMap[w]];
                    root[v] = false;
                }
            }

            inline bool beginEdge(VertexType v, VertexType k){

                std::pair<outEdgeIter, outEdgeIter > iEdge = boost::out_edges(v, g);

                VertexType w = boost::target(*(iEdge.first + k), g);

#ifndef SILENCE
                std::cout << "\t\t\t Expand vertex: " << indexMap[v] <<" => "<< indexMap[w] <<std::endl;
#endif

                if(rIndex[indexMap[w]] == 0){
                    iS.pop();
                    iS.push(k + 1);

#ifndef SILENCE
                    std::cout << "\t\t\t vertex: " << indexMap[w] <<" not already visited " <<std::endl;
#endif
                    beginVisiting(w);
                    return true;
                }else {
#ifndef SILENCE
                    std::cout << "\t\t\t vertex: " << indexMap[w] <<" already visited " <<std::endl;
#endif
                    return false;
                }
            }

            inline void finishVisiting(VertexType v){
#ifndef SILENCE
                std::cout << "\t\t\t Finish visiting vertex: " << indexMap[v] <<std::endl;
#endif
                vS.pop();
                iS.pop();

                if(root[indexMap[v]]){
#ifndef SILENCE
                    std::cout << "\t\t\t Vertex: " << indexMap[v] << " is a root" <<std::endl;
#endif
                    index--;

                    while(!S.empty() && rIndex[indexMap[v]] <= rIndex[indexMap[S.top()]] ){
                        rIndex[indexMap[S.top()]] = count;
                        boost::put(c, S.top(), count);
#ifndef SILENCE
                        std::cout << "\t\t\t\t -> Insert vertex: " << indexMap[S.top()] << " in component " << count <<std::endl;
#endif
                        S.pop();
                        index--;
                    }

                    rIndex[indexMap[v]] = count;
                    boost::put(c, v, count);
#ifndef SILENCE
                    std::cout << "\t\t\t\t -> Insert vertex: " << indexMap[v] << " in component " << count <<std::endl;
#endif
                    count--;
                }else{
#ifndef SILENCE
                    std::cout << "\t\t\t Vertex: " << indexMap[v] << " is not a root" <<std::endl;
#endif
                    S.push(v);
                }
            }


            inline void visitLoop(){
                VertexType v,i;
                v = vS.top();
                i = iS.top();

                OutDegree outDegree = boost::out_degree(v, g);

                while(i <= outDegree){
                    if (i > 0) finishEdge(v, i - 1);
                    if (i < outDegree && beginEdge(v, i)) return;

                    i++;
                }

                finishVisiting(v);
            }


            inline void visit(VertexType vert){
                beginVisiting(vert);

                while(!vS.empty())
                    visitLoop();
            }

            inline Count exe(){

#ifndef SILENCE
                std::cout << "\t\tStart execution" << std::endl;
#endif

                std::pair<VertexIterator, VertexIterator > vp;
                for(vp = boost::vertices(g); vp.first != vp.second; vp.first++) {
                    VertexType vert = *vp.first;

                    if(rIndex[indexMap[vert]] == 0) {
#ifndef SILENCE
                        std::cout << "\t\t Visit vertex: " << indexMap[vert] <<std::endl;
#endif
                        visit(vert);
                    } else {
#ifndef SILENCE
                        std::cout << "\t\t Visit vertex: " << indexMap[vert]<<" [ skip ] "<<std::endl;
#endif
                    }
                }

                delete[] rIndex;
                return count;
            }

        } tarjanExe(g, c, nVertices);

        return tarjanExe.exe();
    };


    template<typename Graph, typename ComponentsMap>
    inline typename boost::property_traits<ComponentsMap>::value_type
    searchComponentsDFS(Graph &g, ComponentsMap c, unsigned int nVertices) {
        typedef typename boost::property_traits<ComponentsMap>::value_type Count;
        Count count(nVertices-1);

#ifndef SILENCE
        std::cout << "\t The graph is undirected -> simple DFS exploration until all nodes are in a component"
                  << std::endl;
#endif
        typedef typename graph_traits<Graph>::vertex_descriptor VertexType;

        class DfsComponentVisitor : public dfs_visitor<>{

            bool discoveredVertices;

            ComponentsMap _c;

            Count _count;

        public:
            DfsComponentVisitor(ComponentsMap c,Count count) {
                _c = c;
                _count = count;
                discoveredVertices = false;
            }


            void finish_vertex(VertexType v, const Graph&){
                if(!discoveredVertices)
                    return;

#ifndef SILENCE
                std::cout << "\t\tComponent "<< _count <<" exploration finished" << std::endl;
#endif
                discoveredVertices = false;
                _count--;

            }

            void discover_vertex(VertexType u, const Graph&){
#ifndef SILENCE
                std::cout << "\t\tNew discovered Vertex" << u << std::endl;
#endif
                boost::put(_c, u, _count);
                discoveredVertices = true;
            }
        };


        DfsComponentVisitor vis(c, count);
        boost::depth_first_search(g, boost::visitor(vis));

        return count;
    };

    template<typename Graph, typename ComponentsMap>
    typename boost::property_traits<ComponentsMap>::value_type
    strongConnectedComponents(Graph &g, ComponentsMap c) {
        BOOST_CONCEPT_ASSERT((boost::VertexAndEdgeListGraphConcept<Graph>));
        using namespace boost;

        typedef typename boost::property_traits<ComponentsMap>::value_type Count;
        Count count;

#ifndef SILENCE
        std::cout << "Start of Strongly Connected Component Algorithm" << std::endl;
#endif

        //Get number of vertices and create in component
        typedef typename boost::graph_traits<Graph>::vertices_size_type NumVertices;
        NumVertices nVertices = boost::num_vertices(g);

        if (boost::is_directed(g)) {
            count = tarjanAlgorithm(g, c, nVertices);
        } else {
            count = searchComponentsDFS(g, c, nVertices);
        }

#ifndef SILENCE
        std::cout << "End of Strongly Connected Component Algorithm" << std::endl << std::endl;
#endif
        return count;
    };
}
#endif //SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
