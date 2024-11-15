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
	void Reset();

    // ... other graph-level operations (e.g., layout, search, filtering)

private:
	// Internal methods
	void UpdateExecutionOrder();
	void UpdateVisuals();
	void UpdateData();
	void UpdateState();
	void UpdateConnections();
	void UpdateHierarchy();
	void UpdateTags();
	void UpdateCustomProperties();
	void UpdatePosition();
	void UpdateSize();
	void UpdateColor();
	void UpdateVisualStyle();
	void UpdateName();
	void UpdateComment();
};

#endif // GRAPH_H