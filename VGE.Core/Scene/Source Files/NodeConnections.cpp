#include "NodeConnections.h"
#include "Connection.h"
#include "Node.h"
#include <algorithm>

void NodeConnections::AddConnection(Node* node, Connection* connection) {
    if (node && connection) {
        node->Connections.push_back(connection);
    }
}

void NodeConnections::RemoveConnection(Node* node, Connection* connection) {
    if (node) {
        node->Connections.erase(std::remove(node->Connections.begin(), node->Connections.end(), connection), node->Connections.end());
    }
}

std::vector<Node*> NodeConnections::GetConnectedNodes(const Node& node) {
    std::vector<Node*> connectedNodes;
    for (const auto& connection : node.Connections) {
        if (connection->Source == &node) {
            connectedNodes.push_back(connection->Target);
        }
        else if (connection->Target == &node) {
            connectedNodes.push_back(connection->Source);
        }
    }
    return connectedNodes;
}

bool NodeConnections::CanConnectTo(const Node& node, Node* otherNode, Pin* myPin, Pin* otherPin) {
    // Implement your logic to determine if the node can connect to another node
    // ... (Consider type compatibility, connection limits, etc.)
    return true; // Placeholder implementation
}