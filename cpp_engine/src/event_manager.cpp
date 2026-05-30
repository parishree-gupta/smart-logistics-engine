#include "../include/event_manager.h"
#include <iostream>
#include <cstdlib>
using namespace std;
// ---------- CONSTRUCTOR ----------
EventManager::EventManager(Graph &g)
    : graph(g)
{
}
// ---------- GENERATE EVENTS ----------
void EventManager::generateEvents()
{
    events.clear();
    int eventCount =
        1 + rand() % 5;
    vector<string> eventTypes = {
        "ACCIDENT",
        "ROADBLOCK",
        "EMERGENCY_ORDER",
        "TRAFFIC_SPIKE"};
    for (int i = 0; i < eventCount; i++)
    {

        Event e;

        e.type =
            eventTypes[rand() % eventTypes.size()];

        e.severity =
            1 + rand() % 10;

        e.description =
            "Dynamic logistics event triggered";

        // ---------- DYNAMIC ROAD BLOCK ----------
        if (
            (e.type == "ACCIDENT" || e.type == "ROADBLOCK") &&
            graph.getVertices() > 1)
        {

            int from =
                rand() % graph.getVertices();

            int to =
                rand() % graph.getVertices();

            while (to == from)
            {

                to =
                    rand() % graph.getVertices();
            }

            graph.blockRoad(from, to);

            e.description =
                "Road blocked between " + graph.getCityName(from) + " and " + graph.getCityName(to);
        }

        events.push_back(e);
    }
}
// ---------- SHOW EVENTS ----------
void EventManager::showEvents()
{

    cout << "\n========== LIVE EVENTS ==========\n";

    for (auto &e : events)
    {

        cout
            << "Event: "
            << e.type
            << " | Severity: "
            << e.severity
            << " | "
            << e.description
            << "\n";
    }

    cout << "=================================\n";
}
