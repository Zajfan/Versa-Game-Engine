#ifndef EVENTNODE_H
#define EVENTNODE_H

#include "Node.h"

class EventNode : public Node
{
public:
    EventNode(const std::string& name);

    // Properties specific to event nodes (e.g., event type, event data)
    // ...

    // Methods for handling events, triggering actions, etc.
    // ...
};

#endif // EVENTNODE_H