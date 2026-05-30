#ifndef OPTIMIZER_H
#define OPTIMIZER_H
#include "graph.h"
#include "models.h"
#include <vector>
using namespace std;
class Optimizer {
private:
    Graph& graph;
public:
    // constructor
    Optimizer(Graph& g);
    // greedy assignment
    int greedyAssign(
        vector<Agent>& agents,
        vector<Order>& orders
    );
    // knapsack optimization
    vector<Order> knapsack(
        vector<Order>& orders,
        int capacity
    );
    // tsp routing
    pair<vector<int>, int> tsp(
        vector<int>& nodes
    );
};

#endif
