
#include "SCCAlgorithm/StronglyConnectedComponents.h"
#include "Tests.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>

int main() {

    bool result = testUndirectedEmpty();

    if(result){
        std::cout << "Passed!" << std::endl;
    }else{
        std::cout << "Failed!" << std::endl;
    }

    return 0;
}