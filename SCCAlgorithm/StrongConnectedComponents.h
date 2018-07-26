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

#include <mach/mach.h>

vm_size_t maxMemSize;

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
        
        struct TarjanExe{
        private:
            Count count;
            Graph &g;
            ComponentsMap c;    //OUT
            IndexMap indexMap;
            Count index;
            Count nVertices;
            boost::dynamic_bitset<> root;

            //Stacks to simulate recursion
            std::stack<VertexType> vS, S;
            std::stack<outEdgeIter> itS;

        public:
            TarjanExe(Graph &g, ComponentsMap c) : g(g), c(c) {

                nVertices = boost::num_vertices(g);

                indexMap = get(vertex_index, g);

                count = Count(nVertices-1);
                root = boost::dynamic_bitset<>(nVertices);

                VertexIterator vi, vi_end;
                for (boost::tie(vi, vi_end) = boost::vertices(g); vi != vi_end; ++vi){
                    boost::put(c, *vi, 0);
                }

                index = 1;
            }


            inline void beginVisiting(VertexType v){
                outEdgeIter itStart, itEnd;

                while( boost::get(c, v) == 0 ){
#ifndef SILENCE
                    std::cout << "\t\t\t Start visiting vertex " << indexMap[v] << std::endl;
#endif

                    boost::tie(itStart, itEnd) = boost::out_edges(v, g);

                    itS.push(itStart);
                    vS.push(v);

                    root[indexMap[v]] = true;
                    boost::put(c, v, index);

                    index++;

                    if(itStart != itEnd)
                        v = boost::target( *itStart, g);
                    else
                        return;
                }
            }


            inline bool beginEdge(VertexType v, outEdgeIter k) {
                VertexType w = boost::target(*k, g);

#ifndef SILENCE
                std::cout << "\t\t\t Expand vertex: " <<  indexMap[v] <<" => "<< indexMap[w] <<std::endl;
#endif

                if(boost::get(c, w) == 0){
#ifndef SILENCE
                    std::cout << "\t\t\t vertex: " << indexMap[w] <<" not already visited " <<std::endl;
#endif

                    beginVisiting(w);
                    return true;

                } else {
#ifndef SILENCE
                    std::cout << "\t\t\t vertex: " << indexMap[w] <<" already visited " <<std::endl;
#endif
                    return false;
                }
            }
            inline void finishVisiting(VertexType v){

                struct task_basic_info t_info;
                mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

                if (KERN_SUCCESS != task_info(mach_task_self(),
                                              TASK_BASIC_INFO, (task_info_t) &t_info,
                                              &t_info_count)) {
                    std::cout << "Something wrong happened" << std::endl;
                    return;
                }
                vm_size_t newMemSize = t_info.resident_size / 1024 / 1024;

                if (newMemSize > maxMemSize)
                    maxMemSize = newMemSize;


                itS.pop();
                vS.pop();


                if(root[indexMap[v]]){
#ifndef SILENCE
                    std::cout << "\t\t\t Vertex: " << indexMap[v] << " is a root vertex" <<std::endl;
#endif
                    index--;

                    while(!S.empty() && boost::get(c, v) <= boost::get(c, S.top()) ){

                        boost::put(c, S.top(), count);
#ifndef SILENCE
                        std::cout << "\t\t\t\t -> Insert vertex: " << indexMap[S.top()] << " in component " << count <<std::endl;
#endif
                        S.pop();
                        index--;
                    }

                    boost::put(c, v, count);

#ifndef SILENCE
                    std::cout << "\t\t\t\t -> Insert vertex: " << indexMap[v] << " in component " << count <<std::endl;
#endif
                    count--;
                } else {
#ifndef SILENCE
                    std::cout << "\t\t\t Vertex: " << indexMap[v] << " is not a root" <<std::endl;
#endif
                    S.push(v);
                }
            }

            inline void finishEdge(VertexType v, VertexType w){
                Count rIndexV = boost::get(c, v);
                Count rIndexW = boost::get(c, w);

                if(rIndexW < rIndexV) {
                    boost::put(c, v, rIndexW);
                    root[indexMap[v]] = false;
                }
            }

            inline void visitLoop(){
                VertexType v, ve;
                outEdgeIter it;

                v = vS.top();
                it = itS.top();

                outEdgeIter itStart, itEnd;
                boost::tie(itStart, itEnd) = boost::out_edges(v, g);

                while(it != itEnd){
                    ve = boost::target(*it, g);
                    finishEdge(v, ve);

                    it++;
                    itS.pop();
                    itS.push(it);

                    if(it != itEnd && beginEdge(v, it))
                        return;
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

                    if(boost::get(c, vert) == 0) {
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
