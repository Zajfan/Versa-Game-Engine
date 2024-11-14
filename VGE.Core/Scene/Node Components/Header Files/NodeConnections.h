// NodeConnections.h
#ifndef NODECONNECTIONS_H
#define NODECONNECTIONS_H

#include "Node.h"
#include "Connection.h" // Include Connection.h

// ... other includes if needed

class NodeConnections
{
public:
    static void AddConnection(Node* node, Connection* connection);
    static void RemoveConnection(Node* node, Connection* connection);
    static std::vector<Node*> GetConnectedNodes(const Node& node);
    static bool CanConnectTo(const Node& node, Node* otherNode, Pin* myPin, Pin* otherPin);
};

#endif // NODECONNECTIONS_H