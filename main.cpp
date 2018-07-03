
#include "SCCAlgorithm/StrongConnectedComponents.h"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/timer/timer.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/connected_components.hpp>

#include <fstream>


void generateSamples(){

    boost::random::mt19937 r{static_cast<const uint32_t &>(std::time(0))};

    const int maxVert = 10000000;
    boost::random::uniform_int_distribution<> randVert(1, maxVert);
    boost::random::uniform_int_distribution<> randEdg(1, 5 * maxVert);

    while( true ) {

        typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS> Graph;

        typedef typename boost::graph_traits<Graph>::vertices_size_type V;
        typedef typename boost::graph_traits<Graph>::edges_size_type E;

        typedef typename boost::graph_traits<Graph>::vertex_descriptor VertexType;

        std::map<VertexType, int> map;

        Graph g(0);

        V v;
        E e;
        while (true) {
            v = randVert(r);
            e = randEdg(r);

            if (e <= v * v) {
                break;
            }
        }

        std::cout << "V: " << v << " E: " << e << std::endl;

        boost::generate_random_graph(g, v, e, r);

        std::ofstream outF;
        outF.open("outMyAlgorithm2.txt", std::ofstream::out | std::ofstream::app);

        boost::timer::auto_cpu_timer t;


        boost::strongConnectedComponents(g, boost::make_assoc_property_map(map));

        boost::timer::nanosecond_type outTime = t.elapsed().user + t.elapsed().system;
        outF << v << " " << e << " " << outTime / 1000000 << std::endl;


        outF.flush();
        outF.close();
    }
}

void generateData(){

    struct Record{
        unsigned int v;
        unsigned int e;
        unsigned int ms;
    };


    std::vector<Record> myRecords;
    std::vector<Record> myRecordsArray;
    std::vector<Record> boostRecords;

    std::ifstream inMy;
    inMy.open("outMyAlgorithm.txt", std::ifstream::in);
    std::ifstream inMyArray;
    inMyArray.open("outMyAlgorithmArray.txt", std::ifstream::in);
    std::ifstream inBoost;
    inBoost.open("outBoostAlgorithm.txt", std::ifstream::in);

    //Read records
    unsigned int minV, maxV;
    unsigned int minE, maxE;
    unsigned int maxMS;

    minV = std::numeric_limits<unsigned int>::max();
    maxV = std::numeric_limits<unsigned int>::min();
    minE = std::numeric_limits<unsigned int>::max();
    maxE = std::numeric_limits<unsigned int>::min();

    maxMS = std::numeric_limits<unsigned int>::min();

    while (!inMy.eof()){
        Record record;
        inMy >> record.v;
        inMy >> record.e;
        inMy >> record.ms;

        if(record.v < minV)
            minV = record.v;
        if(record.e < minE)
            minE = record.e;

        if(record.v > maxV)
            maxV = record.v;
        if(record.e > maxE)
            maxE = record.e;

        if(record.ms > maxMS)
            maxMS = record.ms;

        myRecords.push_back(record);
    }
    while (!inMyArray.eof()){
        Record record;
        inMyArray >> record.v;
        inMyArray >> record.e;
        inMyArray >> record.ms;

        if(record.v < minV)
            minV = record.v;
        if(record.e < minE)
            minE = record.e;

        if(record.v > maxV)
            maxV = record.v;
        if(record.e > maxE)
            maxE = record.e;

        if(record.ms > maxMS)
            maxMS = record.ms;

        myRecordsArray.push_back(record);
    }
    while (!inBoost.eof()){
        Record record;
        inBoost >> record.v;
        inBoost >> record.e;
        inBoost >> record.ms;

        if(record.v < minV)
            minV = record.v;
        if(record.e < minE)
            minE = record.e;

        if(record.v > maxV)
            maxV = record.v;
        if(record.e > maxE)
            maxE = record.e;

        if(record.ms > maxMS)
            maxMS = record.ms;

        boostRecords.push_back(record);
    }

    //Generate samples
    unsigned int rangeV = maxV - minV;
    unsigned int rangeE = maxE - minE;

    const float numStep = 30;

    unsigned int step = std::min(rangeV / numStep, rangeE / numStep);

    std::cout << " MinV: "<< minV << " MinE: "<<minE << " step: "<< step<< std::endl;
    std::cout << " MaxV: "<< maxV << " MaxE: "<<maxE  << " MaxMS: "<<maxMS << std::endl;

    const float maxDist = 0.05f;

    float vCount = minV;
    float eCount = minE;

    std::ofstream outMy;
    outMy.open("outMySamples.txt", std::ofstream::out | std::ofstream::app);

    while(vCount <= maxV){
        while(eCount <= maxE){

            //std::cout << "V: " << vCount << " E:" << eCount << std::endl;

            unsigned long int sumMs = 0;
            unsigned int nearPointsCounter = 0;

            for (std::vector<Record>::iterator it = myRecords.begin() ; it != myRecords.end(); ++it){
                float vDist = std::abs(it->v - vCount) / rangeV;
                float eDist = std::abs(it->e - eCount) / rangeE;

                if(vDist*vDist + eDist*eDist < maxDist*maxDist) {
                    sumMs += it->ms;
                    nearPointsCounter++;
                }
            }

            float meanMs = sumMs / nearPointsCounter;

            //outF <<(unsigned int)vCount << " " << (unsigned int)eCount << " " << (unsigned int)meanMs << std::endl;

            outMy << (unsigned int)meanMs << " ";

            eCount += step * 5;
        }

        outMy << std::endl;

        eCount = minE;
        vCount += step;
    }
    outMy.flush();
    outMy.close();


    vCount = minV;
    eCount = minE;

    std::ofstream outMyArray;
    outMyArray.open("outMySamplesArray.txt", std::ofstream::out | std::ofstream::app);

    while(vCount <= maxV){
        while(eCount <= maxE){

            //std::cout << "V: " << vCount << " E:" << eCount << std::endl;

            unsigned long int sumMs = 0;
            unsigned int nearPointsCounter = 0;

            for (std::vector<Record>::iterator it = myRecordsArray.begin() ; it != myRecordsArray.end(); ++it){
                float vDist = std::abs(it->v - vCount) / rangeV;
                float eDist = std::abs(it->e - eCount) / rangeE;

                if(vDist*vDist + eDist*eDist < maxDist*maxDist) {
                    sumMs += it->ms;
                    nearPointsCounter++;
                }
            }

            float meanMs = sumMs / nearPointsCounter;

            //outF <<(unsigned int)vCount << " " << (unsigned int)eCount << " " << (unsigned int)meanMs << std::endl;

            outMyArray << (unsigned int)meanMs << " ";

            eCount += step * 5;
        }

        outMyArray << std::endl;

        eCount = minE;
        vCount += step;
    }


    outMyArray.flush();
    outMyArray.close();


    vCount = minV;
    eCount = minE;

    std::ofstream outBoost;
    outBoost.open("outBoostSamples.txt", std::ofstream::out | std::ofstream::app);

    while(vCount <= maxV){
        while(eCount <= maxE){

            //std::cout << "V: " << vCount << " E:" << eCount << std::endl;

            unsigned long int sumMs = 0;
            unsigned int nearPointsCounter = 0;

            for (std::vector<Record>::iterator it = boostRecords.begin() ; it != boostRecords.end(); ++it){
                float vDist = std::abs(it->v - vCount) / rangeV;
                float eDist = std::abs(it->e - eCount) / rangeE;

                if(vDist*vDist + eDist*eDist < maxDist*maxDist) {
                    sumMs += it->ms;
                    nearPointsCounter++;
                }
            }

            float meanMs = sumMs / nearPointsCounter;

            //outF <<(unsigned int)vCount << " " << (unsigned int)eCount << " " << (unsigned int)meanMs << std::endl;

            outBoost << (unsigned int)meanMs << " ";

            eCount += step * 5;
        }

        outBoost << std::endl;

        eCount = minE;
        vCount += step;
    }


    outBoost.flush();
    outBoost.close();


}


int main() {
    //generateSamples();

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