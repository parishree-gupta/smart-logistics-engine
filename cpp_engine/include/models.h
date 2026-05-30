#ifndef MODELS_H
#define MODELS_H
#include <string>
using namespace std;
// ---------- ORDER ----------
struct Order {
    int city;
    int weight;
    int deadline;
    int priority;
    bool emergency;
};
// ---------- AGENT ----------
struct Agent {
    int city;
    int capacity;
};
// ---------- ROAD ----------
struct Road {
    int from;
    int to;
    int distance;
    int trafficLevel;
    bool blocked;
    double fuelCostMultiplier;
};

// ---------- VEHICLE ----------
struct Vehicle {
    string type;
    int fuelCapacity;
    double mileage;
};
// ---------- DELIVERY RESULT ----------
struct DeliveryResult {
    int totalCost;
    int totalDistance;
    int deliveriesCompleted;
};

#endif
