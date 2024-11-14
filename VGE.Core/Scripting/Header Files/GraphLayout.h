#ifndef GRAPHLAYOUT_H
#define GRAPHLAYOUT_H

#include "Graph.h"

class GraphLayout
{
public:
    static void ApplyLayout(Graph& graph);

private:
    // ... Helper functions for specific layout algorithms (e.g., force-directed, hierarchical)
};

#endif // GRAPHLAYOUT_H