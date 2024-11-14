#include "Graph.h"
#include "GraphSerializer.h" 
#include "GraphExecutor.h"  
#include <algorithm>
#include <stack>

// Methods for managing nodes
void Graph::AddNode(Node* node)
{
    Nodes.push_back(node);
    node->Initialize();
}

void Graph::RemoveNode(Node* node)
{
    // Remove node from the list
    Nodes.erase(std::remove(Nodes.begin(), Nodes.end(), node), Nodes.end());

    // Remove any connections associated with this node
    Connections.erase(std::remove_if(Connections.begin(), Connections.end(),
        [node](Connection* c) { return c->Source == node || c->Target == node; }), Connections.end());

    // If the node has a parent, remove it from the parent's children list
    if (node->Parent != nullptr)
    {
        node->Parent->Children.erase(std::remove(node->Parent->Children.begin(), node->Parent->Children.end(), node), node->Parent->Children.end());
    }

    // Recursively remove all child nodes
    for (Node* child : node->Children)
    {
        RemoveNode(child);
    }

    node->Terminate();
}

Node* Graph::FindNodeById(int id)
{
    auto it = std::find_if(Nodes.begin(), Nodes.end(), [id](Node* n) { return n->Id == id; });
    if (it != Nodes.end())
    {
        return *it;
    }
    else
    {
        return nullptr;
    }
}

// Methods for managing connections
void Graph::CreateConnection(Node* source, Pin* sourcePin, Node* target, Pin* targetPin)
{
    if (source->CanConnectTo(target, sourcePin, targetPin))
    {
        Connection* connection = new Connection();
        connection->Source = source;
        connection->Target = target;
        connection->SourcePin = sourcePin;
        connection->TargetPin = targetPin;
        Connections.push_back(connection);
        source->AddConnection(connection);
        target->AddConnection(connection);
    }
    else
    {
        // Handle invalid connection attempt
    }
}

void Graph::DeleteConnection(Connection* connection)
{
    // Find and remove the connection from the vector
    auto it = std::find(Connections.begin(), Connections.end(), connection);
    if (it != Connections.end())
    {
        Connections.erase(it);
    }

    connection->Source->RemoveConnection(connection);
    connection->Target->RemoveConnection(connection);

    delete connection;
}

// XML Serialization and Deserialization (delegated to GraphSerializer)
void Graph::Serialize(const std::string& filePath)
{
    GraphSerializer::Serialize(*this, filePath);
}

void Graph::Deserialize(const std::string& filePath)
{
    GraphSerializer::Deserialize(*this, filePath);
}

// Graph Execution (delegated to GraphExecutor)
void Graph::Execute()
{
    GraphExecutor::Execute(*this);
}

// Other graph-level operations
// TODO: Implement these methods based on your needs
std::vector<Node*> Graph::FindNodesByType(NodeType type)
{
    std::vector<Node*> result;
    for (auto& node : Nodes)
    {
        if (node->Type == type)
        {
            result.push_back(node);
        }
    }
    return result;
}

std::vector<Node*> Graph::FindNodesByTag(const std::string& tag)
{
    std::vector<Node*> result;
    for (auto& node : Nodes)
    {
        if (std::find(node->Tags.begin(), node->Tags.end(), tag) != node->Tags.end())
        {
            result.push_back(node);
        }
    }
    return result;
}

// ... (Other potential graph-level operations)

// Topological Sort Implementation (if not in GraphExecutor)
std::vector<Node*> Graph::TopologicalSort()
{
    std::vector<Node*> sortedNodes;
    std::set<Node*> visited;
    std::stack<Node*> stack;

    for (Node* node : Nodes)
    {
        if (visited.count(node) == 0)
        {
            TopologicalSortUtil(node, visited, stack);
        }
    }

    while (!stack.empty())
    {
        sortedNodes.push_back(stack.top());
        stack.pop();
    }

    return sortedNodes;
}

void Graph::TopologicalSortUtil(Node* node, std::set<Node*>& visited, std::stack<Node*>& stack)
{
    visited.insert(node);

    for (Node* connectedNode : node->GetConnectedNodes())
    {
        if (visited.count(connectedNode) == 0)
        {
            TopologicalSortUtil(connectedNode, visited, stack);
        }
    }

    stack.push(node);
}