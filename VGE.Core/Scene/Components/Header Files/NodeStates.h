#ifndef NODESTATES_H
#define NODESTATES_H

#include <string>

// Define state-related properties and methods of a Node
class NodeStates
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

#endif // NODESTATES_H