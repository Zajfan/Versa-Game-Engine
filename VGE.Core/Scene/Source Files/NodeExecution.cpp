#include "NodeExecution.h"
#include "Node.h"

void Node::Execute()
{
    // Check if the node has a condition and evaluate it
    if (!Condition.empty() && !EvaluateCondition())
    {
        return; // Skip execution if the condition is false
    }

    for (auto& component : Components)
    {
        component->Execute();
    }
}

bool Node::EvaluateCondition()
{
    // TODO: Implement condition evaluation logic
    return true; // Placeholder: Always return true for now
}