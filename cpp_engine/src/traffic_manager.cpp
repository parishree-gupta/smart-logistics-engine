#include "../include/traffic_manager.h"
#include <iostream>
#include <cstdlib>
using namespace std;
// ---------- CONSTRUCTOR ----------
TrafficManager::TrafficManager(Graph& g)
    : graph(g)
{
}
// ---------- TRAFFIC SIMULATION ----------
void TrafficManager::simulateTraffic() {
    auto adj =
        graph.getAdjacencyList();
    cout << "\n========== TRAFFIC UPDATE ==========\n";
    for(int i = 0; i < adj.size(); i++) {
        for(auto& road : adj[i]) {
            int newTraffic =
                rand() % 10;
            cout
                << "Road "
                << graph.getCityName(road.from)
                << " -> "
                << graph.getCityName(road.to)
                << " | Traffic Level: "
                << newTraffic
                << "\n";
        }
    }
    cout << "====================================\n";
}
// --------- ROAD BLOCK SIMULATION ----------
void TrafficManager::simulateRoadBlocks() {
    auto adj =
        graph.getAdjacencyList();
    cout << "\n========== ROAD STATUS ==========\n";
    for(int i = 0; i < adj.size(); i++) {
        for(auto& road : adj[i]) {

            bool blocked =
                (rand() % 20 == 0);

            cout
                << "Road "
                << graph.getCityName(road.from)
                << " -> "
                << graph.getCityName(road.to)
                << " | ";

            if(blocked) {

                cout << "BLOCKED";
            }
            else {

                cout << "OPEN";
            }

            cout << "\n";
        }
    }

    cout << "=================================\n";
}
