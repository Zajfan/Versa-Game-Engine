#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

#include "Node.h"
#include "Connection.h"

class Graph
{
public:
    std::vector<Node*> Nodes;
    std::vector<Connection*> Connections;

    // Methods for managing nodes
    void AddNode(Node* node);
    void RemoveNode(Node* node);
    Node* FindNodeById(int id);

    // Methods for managing connections
    void CreateConnection(Node* source, Pin* sourcePin, Node* target, Pin* targetPin);
    void DeleteConnection(Connection* connection);

    // Other potential methods
    void Serialize(const std::string& filePath);
    void Deserialize(const std::string& filePath);
    void Execute();

    // ... other graph-level operations (e.g., layout, search, filtering)
};

#endif // GRAPH_H