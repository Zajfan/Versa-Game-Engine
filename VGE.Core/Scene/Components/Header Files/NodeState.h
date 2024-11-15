#ifndef NODESTATE_H
#define NODESTATE_H

#include <string> // Include for std::string

// Define state-related properties and methods of a Node
class NodeState
{
public:
    enum class ExecutionState { NotExecuted, Executing, Executed, Failed };

    // Properties
    std::string ErrorMessage;
    ExecutionState CurrentState;

    // Methods
    void Reset();
    bool HasError() const;
    void ClearError();
};

#endif // NODESTATE_H