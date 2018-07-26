//
// Created by Marco on 25/07/18.
//

#ifndef SCCALGORITHM_STRONGCONNECTEDCOMPONENTSNUUTILA_H
#define SCCALGORITHM_STRONGCONNECTEDCOMPONENTSNUUTILA_H


#include <boost/property_map/property_map.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/graph_concepts.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <stack>
#include <iostream>

#include <mach/mach.h>
vm_size_t maxMemSize;

unsigned long maxSize = 0;

namespace boost {
    template<typename Graph, typename ComponentsMap>
    inline typename boost::property_traits<ComponentsMap>::value_type
    strongConnectedComponents(Graph &g, ComponentsMap c) {
        using namespace boost;

        //Required concepts for the execution of the algorithm
        BOOST_CONCEPT_ASSERT((boost::VertexAndEdgeListGraphConcept<Graph>));
        typedef typename graph_traits<Graph>::directed_category DirCat;
        BOOST_STATIC_ASSERT((is_convertible<DirCat*, directed_tag*>::value));

#ifndef SILENCE
        std::cout << "Start of Strongly Connected Component Algorithm, Nuutila version" << std::endl;
#endif

        typedef typename boost::property_traits<ComponentsMap>::value_type Count;
        typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;
        typedef typename boost::property_map<Graph, vertex_index_t>::type IndexMap;

        Count nVertices = boost::num_vertices(g);
        VertexType* root = new VertexType[nVertices];

        class NuutilaDFSVisitor : public dfs_visitor<>{
        private:
            typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
            typedef typename boost::graph_traits<Graph>::edge_descriptor EdgeType;

            Count count;
            Graph &g;
            IndexMap indexMap;
            Count index;
            Count nVertices;

            Count rootCounter;

            VertexType* root;
            Count* visitIndex;

            boost::dynamic_bitset<> inComponent;

            std::vector<VertexType> S;

            std::set<int> setS;

        public:

            NuutilaDFSVisitor(Graph &g, VertexType* root) : g(g), root(root) {
                nVertices = boost::num_vertices(g);

                indexMap = get(vertex_index, g);

                count = Count(nVertices-1);

                rootCounter = Count(0);

                inComponent = boost::dynamic_bitset<>(nVertices);
                for (int j = 0; j < nVertices; ++j) {
                    inComponent[j] = false;
                }

                visitIndex = new Count[nVertices];

                index = 1;
            }

            void discover_vertex(VertexType v,
                                 const Graph& g){

#ifndef SILENCE
                std::cout << "\t Start visiting vertex " << indexMap[v] << std::endl;
#endif
                unsigned int vIndex = indexMap[v];

                root[vIndex] = v;
                inComponent[vIndex] = false;
                visitIndex[vIndex] = index;

                index += 1;
            }

            void finish_edge(EdgeType e,
                             const Graph& g){

                VertexType v = boost::source(e, g);
                VertexType w = boost::target(e, g);

#ifndef SILENCE
                std::cout << "\t Finished edge " << indexMap[v] << " => " << indexMap[w] << std::endl;
#endif

                VertexType rootW = root[indexMap[w]];

                if(!inComponent[indexMap[rootW]]){
#ifndef SILENCE
                    std::cout << "\t\t Root of target (" << indexMap[w] << ") without component" << std::endl;
#endif
                    unsigned int vIndex = indexMap[v];
                    unsigned int rootVIndex = indexMap[root[vIndex]];

                    if(visitIndex[rootVIndex] > visitIndex[indexMap[rootW]]){
#ifndef SILENCE
                        std::cout << "\t\t\t Change root of " << vIndex << " to " << indexMap[rootW] << std::endl;
#endif
                        root[vIndex] = rootW;
                    } else{
#ifndef SILENCE
                        std::cout << "\t\t\t Root of " << vIndex << " unchanged "<< std::endl;
#endif
                    }
                }else{
#ifndef SILENCE
                    std::cout << "\t\t Root of target (" << indexMap[w] << ") already in one component" << std::endl;
#endif
                }
            }

            void finish_vertex(VertexType v,
                               const Graph& g){
                unsigned int vIndex = indexMap[v];

#ifndef SILENCE
                std::cout << "\t Finished vertex " << vIndex << std::endl;
#endif

                if(root[vIndex] == v){

#ifndef SILENCE
                    std::cout << "\t\t Vertex " << vIndex << " is a root vertex" << std::endl;
#endif

                    rootCounter += 1;

                    VertexType sTop;
                    Count vVIndex;

                    vVIndex = visitIndex[vIndex];

                    if(!S.empty() && visitIndex[indexMap[S.back()]] >= vVIndex){
                        do{
                            sTop = S.back();
                            setS.erase(indexMap[sTop]);

                            S.pop_back();

                            inComponent[indexMap[sTop]] = true;


                        }while(!S.empty() && visitIndex[indexMap[sTop]] >= vVIndex);
                    }else{
                        inComponent[vIndex] = true;
                    }
                }else{
#ifndef SILENCE
                    std::cout << "\t\t Vertex " << vIndex << " is not a root vertex" << std::endl;
#endif
                    VertexType rootV = root[vIndex];

                    if(setS.find(indexMap[rootV]) == setS.end()) {
#ifndef SILENCE
                        std::cout << "\t\t\t Root of vertex " << vIndex << " ("<<indexMap[rootV]<<") pushed onto the stack" << std::endl;
#endif
                        S.push_back(rootV);
                        setS.insert(indexMap[rootV]);

                    }else{
#ifndef SILENCE
                        std::cout << "\t\t\t Root of vertex " << vIndex << " ("<<indexMap[rootV]<<") already into the stack" << std::endl;
#endif
                    }
                }
            }

            void clearMemory(){
                delete[] visitIndex;

                S.clear();
            }

            Count getRootCounter(){
                return rootCounter;
            }

        } nuutilaDFSVisitor(g,root);

        boost::depth_first_search(g, boost::visitor(nuutilaDFSVisitor));

        nuutilaDFSVisitor.clearMemory();


        IndexMap indexMap = boost::get(vertex_index, g);

        typedef typename graph_traits<Graph>::vertex_iterator VertexIterator;
        VertexIterator vi, vi_end;
        for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi){
            boost::put(c, *vi, indexMap[root[indexMap[*vi]]]);
        }

        delete[] root;

        return nuutilaDFSVisitor.getRootCounter();
    };
}

#endif //SCCALGORITHM_STRONGCONNECTEDCOMPONENTSNUUTILA_H