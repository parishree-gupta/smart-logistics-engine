#ifndef TRAFFIC_MANAGER_H
#define TRAFFIC_MANAGER_H
#include "graph.h"
class TrafficManager {
private:
    Graph& graph;
public:
    // constructor
    TrafficManager(Graph& g);
    // simulate traffic updates
    void simulateTraffic();
    // simulate blocked roads
    void simulateRoadBlocks();
};
#endif
