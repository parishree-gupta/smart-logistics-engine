#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

#include "models.h"

using namespace std;

class Graph {

private:

    int n;

    // advanced adjacency list
    vector<vector<Road>> adj;

    // city names
    vector<string> cityNames;

public:

    // constructor
    Graph(int vertices);

    // set city name
    void setCityName(int index, string name);

    // add advanced road
    void addEdge(
        int from,
        int to,
        int distance,
        int trafficLevel,
        bool blocked,
        double fuelCostMultiplier
    );

    // shortest path
    vector<int> dijkstra(int src);

    // block road dynamically
    void blockRoad(int from, int to);

    // getters
    int getVertices();

    string getCityName(int index);

    vector<vector<Road>> getAdjacencyList();
};

#endif