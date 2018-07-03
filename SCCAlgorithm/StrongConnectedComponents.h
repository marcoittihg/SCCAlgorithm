//
// Created by Marco on 06/06/18.
//

#ifndef SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
#define SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/adjacency_matrix.hpp>
#include <boost/math/special_functions/round.hpp>
#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <stack>

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
        std::cout << "Start of Strongly Connected Component Algorithm" << std::endl;
#endif

        //Definition of needed types
        typedef typename boost::property_traits<ComponentsMap>::value_type Count;
        typedef typename boost::property_map<Graph, vertex_index_t>::type IndexMap;
        typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;
        typedef typename boost::graph_traits<Graph>::vertices_size_type NumVertices;
        typedef typename boost::graph_traits<Graph>::vertex_iterator VertexIterator;
        typedef typename boost::graph_traits<Graph>::degree_size_type OutDegree;
        typedef typename boost::graph_traits<Graph>::out_edge_iterator outEdgeIter;
        typedef typename boost::property_map<Graph, boost::vertex_index_t >::type IndexMap;


#ifndef SILENCE
        std::cout << "\t The graph is directed -> Tarjan algorithm" << std::endl;
#endif
        struct TarjanExe{
            Count count;
            Graph &g;
            ComponentsMap c;    //OUT
            IndexMap indexMap;

        private:

            Count index;
            Count nVertices;

            boost::dynamic_bitset<> root;

            Count* rIndex;

            //Stacks to simulate recursion
            std::stack<VertexType>  vS, S;
            std::stack<OutDegree> iS;

            //Contain the out degree of the nodes
            std::stack<OutDegree> oS;

            //Iterator over the forward star set
            std::stack<outEdgeIter > itS;

            //Previously not already finished edge
            std::stack<VertexType> ovS;


        public:
            TarjanExe(Graph &g, ComponentsMap c) : g(g), c(c) {

                nVertices = boost::num_vertices(g);

                indexMap = get(vertex_index, g);

                count = Count(nVertices-1);
                root = boost::dynamic_bitset<>(nVertices);
                rIndex = new Count[nVertices];

                for (int i = 0; i < nVertices; ++i) { rIndex[i] = 0; }

                index = 1;
            }


            inline void beginVisiting(VertexType v){
#ifndef SILENCE
                std::cout << "\t\t\t Start visiting vertex " << indexMap[v] << std::endl;
#endif
                vS.push(v);
                iS.push(0);
                oS.push(boost::out_degree(v, g));
                itS.push(boost::out_edges(v, g).first);
                VertexType ov;
                ovS.push(ov);

                root[indexMap[v]] = true;
                rIndex[indexMap[v]] = index;

                index++;
            }

            inline void finishEdge(VertexType v, VertexType w){
                if(rIndex[indexMap[w]] < rIndex[indexMap[v]]) {
                    rIndex[indexMap[v]] = rIndex[indexMap[w]];
                    root[indexMap[v]] = false;
                }
            }

            inline bool beginEdge(VertexType v, outEdgeIter k){
                VertexType w = boost::target(*k, g);

#ifndef SILENCE
                std::cout << "\t\t\t Expand vertex: " <<  indexMap[v] <<" => "<< indexMap[w] <<std::endl;
#endif

                if(rIndex[indexMap[w]] == 0){
#ifndef SILENCE
                    std::cout << "\t\t\t vertex: " << indexMap[w] <<" not already visited " <<std::endl;
#endif
                    OutDegree i = iS.top();
                    iS.pop();
                    iS.push(i + 1);

                    ovS.pop();
                    ovS.push(w);

                    k++;
                    itS.pop();
                    itS.push(k);

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
                oS.pop();
                itS.pop();
                ovS.pop();

                if(root[indexMap[v]]){
#ifndef SILENCE
                    std::cout << "\t\t\t Vertex: " << indexMap[v] << " is a root vertex" <<std::endl;
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
                VertexType v;
                OutDegree i;
                outEdgeIter it;
                VertexType ov;

                v = vS.top();
                i = iS.top();
                it = itS.top();
                ov = ovS.top();

                OutDegree outDegree = oS.top();

                while(i <= outDegree){
                    if (i > 0) {
                        finishEdge(v, ov);
                    }

                    if (i < outDegree && beginEdge(v, it)){
                        return;
                    }

                    i++;
                    iS.pop();
                    iS.push(i);

                    if(i <= outDegree) {
                        ov = boost::target(*it, g);
                        ovS.pop();
                        ovS.push(ov);

                        it++;
                    }
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
                        std::cout << "\t\t Visit vertex: " << indexMap[vert] <<" [ skip ] "<<std::endl;
#endif
                    }
                }

                delete[] rIndex;
                return count;
            }

        }tarjanExe(g, c);

        Count _count;
        _count = tarjanExe.exe();

#ifndef SILENCE
        std::cout << "End of Strongly Connected Component Algorithm" << std::endl << std::endl;
#endif
        return _count;
    };

}
#endif //SCCALGORITHM_STRONGLYCONNECTEDCOMPONENTS_H
