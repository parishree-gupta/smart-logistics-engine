#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H
#include "graph.h"
#include "models.h"
#include <vector>
#include <string>
using namespace std;
// ---------- EVENT ----------
struct Event {
    string type;
    string description;
    int severity;
};
class EventManager {
private:
    Graph& graph;
    vector<Event> events;
public:
    // constructor
    EventManager(Graph& g);
    // generate random events
    void generateEvents();
    // display events
    void showEvents();
};
#endif
