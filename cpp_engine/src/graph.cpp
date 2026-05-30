#include "../include/graph.h"
#include <queue>
#include <climits>
#define INF 1e9
// ---------- CONSTRUCTOR ----------
Graph::Graph(int vertices) {
    n = vertices;
    adj.resize(n);
    cityNames.resize(n);
}
// ---------- SET CITY NAME ----------
void Graph::setCityName(int index, string name) {

    cityNames[index] = name;
}
// ---------- ADD EDGE ----------
void Graph::addEdge(
    int from,
    int to,
    int distance,
    int trafficLevel,
    bool blocked,
    double fuelCostMultiplier
) {
   Road road1 = {
        from,
        to,
        distance,
        trafficLevel,
        blocked,
        fuelCostMultiplier
    };
    Road road2 = {
        to,
        from,
        distance,
        trafficLevel,
        blocked,
        fuelCostMultiplier
    };
    adj[from].push_back(road1);
    adj[to].push_back(road2);
}
// ---------- DIJKSTRA ----------
vector<int> Graph::dijkstra(int src) {
    vector<int> dist(n, INF);
    priority_queue<
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > pq;
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()) {
        auto current = pq.top();
        pq.pop();
        int u = current.second;
        for(auto edge : adj[u]) {
            // skip blocked roads
            if(edge.blocked)
                continue;
            int v = edge.to;
            // dynamic weight
            int weight =
                edge.distance
                + edge.trafficLevel * 2;
            if(dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
// ---------- BLOCK ROAD ---------
void Graph::blockRoad(int from, int to) {

    for(auto& road : adj[from]) {

        if(road.to == to) {

            road.blocked = true;
        }
    }

    for(auto& road : adj[to]) {

        if(road.to == from) {

            road.blocked = true;
        }
    }
}

// ---------- GETTERS ----------
int Graph::getVertices() {

    return n;
}

string Graph::getCityName(int index) {

    return cityNames[index];
}

vector<vector<Road>> Graph::getAdjacencyList() {

    return adj;
}
