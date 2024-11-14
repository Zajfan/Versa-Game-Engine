// Tip: Source file for the Connection class
#include "Connection.h"
#include "Node.h"
#include "Pin.h"
#include <set>
#include <stack>

bool Connection::IsValid() const
{
    // Basic null checks
    if (Source == nullptr || Target == nullptr || SourcePin == nullptr || TargetPin == nullptr)
        return false;

    // Type compatibility check
    if (SourcePin->DataType != TargetPin->DataType)
        return false;

    // Prevent circular connections (optional)
    if (IsCircularConnection())
        return false;

    // Additional checks can be added here

    return true;
}

bool Connection::IsCircularConnection() const
{
    std::set<Node*> visited;
    std::stack<Node*> stack;
    stack.push(Source);

    while (!stack.empty())
    {
        Node* current = stack.top();
        stack.pop();

        if (visited.count(current) > 0)
            continue;

        visited.insert(current);

        if (current == Target)
            return true; // Circular connection detected

        for (Node* connectedNode : current->GetConnectedNodes())
        {
            stack.push(connectedNode);
        }
    }

    return false; // No circular connection found
}