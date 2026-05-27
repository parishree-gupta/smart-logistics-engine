#include "../include/optimizer.h"

#include <algorithm>

#define INF 1e9

// ---------- CONSTRUCTOR ----------
Optimizer::Optimizer(Graph& g)
    : graph(g)
{
}

// ---------- GREEDY ASSIGN ----------
int Optimizer::greedyAssign(
    vector<Agent>& agents,
    vector<Order>& orders
) {

    int total = 0;

    for(auto& order : orders) {

        int best = INF;

        for(auto& agent : agents) {

            auto dist = graph.dijkstra(agent.city);

            best = min(best, dist[order.city]);
        }

        total += best;
    }

    return total;
}

// ---------- KNAPSACK ----------
vector<Order> Optimizer::knapsack(
    vector<Order>& orders,
    int capacity
) {

    int m = orders.size();

    vector<vector<int>> dp(
        m + 1,
        vector<int>(capacity + 1, 0)
    );

    for(int i = 1; i <= m; i++) {

        for(int w = 0; w <= capacity; w++) {

            if(orders[i - 1].weight <= w) {

                dp[i][w] = max(
                    dp[i - 1][w],

                    dp[i - 1][w - orders[i - 1].weight]
                    + orders[i - 1].priority * 10
                );
            }
            else {

                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    vector<Order> selected;

    int w = capacity;

    for(int i = m; i > 0; i--) {

        if(dp[i][w] != dp[i - 1][w]) {

            selected.push_back(orders[i - 1]);

            w -= orders[i - 1].weight;
        }
    }

    return selected;
}

// ---------- TSP ----------
pair<vector<int>, int> Optimizer::tsp(
    vector<int>& nodes
) {

    int m = nodes.size();

    if(m <= 1)
        return {{nodes[0]}, 0};

    vector<bool> visited(m, false);

    vector<int> route;

    int current = 0;

    route.push_back(nodes[current]);

    visited[current] = true;

    int cost = 0;

    for(int i = 1; i < m; i++) {

        int next = -1;
        int best = INF;

        auto dist = graph.dijkstra(nodes[current]);

        for(int j = 0; j < m; j++) {

            if(!visited[j] && dist[nodes[j]] < best) {

                best = dist[nodes[j]];
                next = j;
            }
        }

        if(next == -1)
            break;

        route.push_back(nodes[next]);

        visited[next] = true;

        cost += best;

        current = next;
    }

    auto finalDist = graph.dijkstra(nodes[current]);

    cost += finalDist[nodes[0]];

    route.push_back(nodes[0]);

    return {route, cost};
}