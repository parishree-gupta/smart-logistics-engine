#include "../include/graph.h"
#include "../include/models.h"
#include "../include/optimizer.h"
#include "../include/traffic_manager.h"
#include "../include/event_manager.h"

#include <iostream>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <mutex>

using namespace std;

// ---------- MAIN ----------
int main() {

    srand(time(0));

    int n;

    cin >> n;

    // ---------- CREATE GRAPH ----------
    Graph graph(n);

    // ---------- CITY NAMES ----------
    for(int i = 0; i < n; i++) {

        string city;

        cin >> city;

        graph.setCityName(i, city);
    }

    // ---------- GRAPH MATRIX ----------
    vector<vector<int>> matrix(
        n,
        vector<int>(n)
    );

    for(int i = 0; i < n; i++) {

        for(int j = 0; j < n; j++) {

            cin >> matrix[i][j];

            // avoid duplicate roads
            if(i < j && matrix[i][j] != 0) {

                int trafficLevel =
                    rand() % 6;

                bool blocked = false;

                double fuelMultiplier =
                    1.0 + (trafficLevel * 0.1);

                graph.addEdge(
                    i,
                    j,
                    matrix[i][j],
                    trafficLevel,
                    blocked,
                    fuelMultiplier
                );
            }
        }
    }

    // ---------- AGENTS + ORDERS ----------
    int agentsCount, ordersCount;

    cin >> agentsCount >> ordersCount;

    vector<Agent> agents(agentsCount);

    vector<Order> orders(ordersCount);

    // ---------- INPUT AGENTS ----------
    for(int i = 0; i < agentsCount; i++) {

        cin >> agents[i].city
            >> agents[i].capacity;
    }

    // ---------- INPUT ORDERS ----------
    for(int i = 0; i < ordersCount; i++) {

        cin >> orders[i].city
            >> orders[i].weight
            >> orders[i].deadline
            >> orders[i].priority;

        // random emergency generation
        orders[i].emergency =
            (rand() % 5 == 0);
    }

    // ---------- SORT ORDERS ----------
    priority_queue<pair<int,int>> pq;

    for(int i = 0; i < orders.size(); i++) {

        int effectivePriority =
            orders[i].priority;

        // emergency boost
        if(orders[i].emergency) {

            effectivePriority += 10;
        }

        pq.push({
            effectivePriority,
            i
        });
    }

    vector<Order> sortedOrders;

    while(!pq.empty()) {

        sortedOrders.push_back(
            orders[pq.top().second]
        );

        pq.pop();
    }

    // ---------- CREATE SYSTEMS ----------
    Optimizer optimizer(graph);

    TrafficManager trafficManager(graph);

    EventManager eventManager(graph);

    auto start =
        chrono::high_resolution_clock::now();

    // ---------- GREEDY OPTIMIZATION ----------
    int greedyCost =
        optimizer.greedyAssign(
            agents,
            sortedOrders
        );

    // ---------- TRAFFIC SIMULATION ----------
    trafficManager.simulateTraffic();

    trafficManager.simulateRoadBlocks();

    // ---------- LIVE EVENTS ----------
    eventManager.generateEvents();

    eventManager.showEvents();

    auto end =
        chrono::high_resolution_clock::now();

    double executionTime =
        chrono::duration<double, milli>(
            end - start
        ).count();

    // ---------- OUTPUT ----------
    cout << "\n";
    cout << "====================================\n";
    cout << " SMART LOGISTICS ENGINE\n";
    cout << "====================================\n\n";

    cout << "Cities           : "
         << n << "\n";

    cout << "Agents           : "
         << agentsCount << "\n";

    cout << "Orders           : "
         << ordersCount << "\n\n";

    cout << "Greedy Cost      : "
         << greedyCost << "\n";

    cout << "Execution Time   : "
         << executionTime
         << " ms\n\n";

    // ---------- PARALLEL AGENT PROCESSING ----------
    mutex outputMutex;

    auto processAgent = [&](int i) {

        string result;

        result += "------------------------------------\n";

        result += "Agent "
            + to_string(i)
            + " | City: "
            + graph.getCityName(
                agents[i].city
            )
            + "\n";

        auto selected =
            optimizer.knapsack(
                sortedOrders,
                agents[i].capacity
            );

        vector<int> nodes = {
            agents[i].city
        };

        for(auto& order : selected) {

            if(order.city != agents[i].city) {

                nodes.push_back(order.city);
            }
        }

        auto tspResult =
            optimizer.tsp(nodes);

        auto route = tspResult.first;

        int routeCost = tspResult.second;

        result += "Deliveries:\n";

        for(auto& order : selected) {

            auto dist =
                graph.dijkstra(
                    agents[i].city
                );

            result += "- "
                + graph.getCityName(order.city)
                + " | Distance: "
                + to_string(dist[order.city])
                + " | Priority: "
                + to_string(order.priority);

            if(order.emergency) {

                result += " | EMERGENCY";
            }

            result += "\n";
        }

        result += "\nRoute:\n";

        for(int j = 0; j < route.size(); j++) {

            result += graph.getCityName(route[j]);

            if(j != route.size() - 1) {

                result += " -> ";
            }
        }

        result += "\n";

        result += "Route Cost: "
            + to_string(routeCost)
            + "\n";

        // thread-safe output
        lock_guard<mutex> lock(outputMutex);

        cout << result;
    };

    // ---------- CREATE THREADS ----------
    vector<thread> threads;

    for(int i = 0; i < agents.size(); i++) {

        threads.push_back(
            thread(processAgent, i)
        );
    }

    // ---------- WAIT FOR THREADS ----------
    for(auto& t : threads) {

        t.join();
    }

    cout << "\n====================================\n";

    return 0;
}