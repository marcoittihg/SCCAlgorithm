
#include "SCCAlgorithm/StrongConnectedComponentsNuutila.h"
#include <boost/graph/random.hpp>
#include <boost/random.hpp>
#include <boost/timer/timer.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/connected_components.hpp>

#include <fstream>
#include <mach/mach.h>
#include <thread>

#include <vector>

void generateSamplesSpace(){
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

        maxMemSize = std::numeric_limits<vm_size_t>::min();

        boost::generate_random_graph(g, v, e, r);

        struct task_basic_info t_info;
        mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

        if (KERN_SUCCESS != task_info(mach_task_self(),
                                      TASK_BASIC_INFO, (task_info_t) &t_info,
                                      &t_info_count)) {
            std::cout << "Something reeeealy wrong happened" << std::endl;
            return;
        }
        vm_size_t graphMemSize = t_info.resident_size / 1024 / 1024;

        std::ofstream outF;
        outF.open("outBoostAlgorithmSpace.txt", std::ofstream::out | std::ofstream::app);

        std::ofstream outF2;
        outF2.open("outBoostAlgorithmSpaceDiff.txt", std::ofstream::out | std::ofstream::app);

        std::cout<<"a"<<std::endl;
        boost::strongConnectedComponents(g, boost::make_assoc_property_map(map));

        std::cout << v << " " << e << " " << maxMemSize << " " << maxMemSize - graphMemSize << std::endl;
        outF << v << " " << e << " " << maxMemSize << std::endl;
        outF2 << v << " " << e << " " << maxMemSize - graphMemSize << std::endl;

        outF.flush();
        outF.close();

        outF2.flush();
        outF2.close();
    }
}

void generateSamplesTime(){
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
        outF.open("outMyAlgorithmNuutila.txt", std::ofstream::out | std::ofstream::app);

        std::cout<<"a"<<std::endl;

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

void upd(){
    while(true) {
        struct task_basic_info t_info;
        mach_msg_type_number_t t_info_count = TASK_BASIC_INFO_COUNT;

        if (KERN_SUCCESS != task_info(mach_task_self(),
                                      TASK_BASIC_INFO, (task_info_t) &t_info,
                                      &t_info_count)) {
            std::cout << "Something reeeealy wrong happened" << std::endl;
            return;
        }
        vm_size_t newMemSize = t_info.resident_size / 1024 / 1024;

        if (newMemSize > maxMemSize)
            maxMemSize = newMemSize;

        //std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
int main() {

    //maxMemSize = std::numeric_limits<vm_size_t>::min();

    //std::thread updThread(upd);
    generateSamplesTime();

    return 0;
}