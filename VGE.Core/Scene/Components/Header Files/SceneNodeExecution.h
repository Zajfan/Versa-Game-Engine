// NodeExecution.h

#ifndef NODEEXECUTION_H
#define NODEEXECUTION_H

#include <string> // Include for std::string

enum class ExecutionMode {
    Default,
    Immediate,
    // Add other execution modes as needed
};

// Define execution-related properties of a Node
struct NodeExecution
{
    int ExecutionPriority;
    bool IsBreakpoint;
    std::string Condition;
    ExecutionMode ExecMode;
    int LoopCount;
    // ... (Other properties or methods for state management)
};

#endif // NODEEXECUTION_H