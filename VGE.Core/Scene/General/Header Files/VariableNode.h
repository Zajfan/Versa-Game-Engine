#ifndef VARIABLENODE_H
#define VARIABLENODE_H

#include "Node.h"

class VariableNode : public Node
{
public:
    VariableNode(const std::string& name);

    // Properties specific to variable nodes (e.g., variable type, value)
    // ...

    // Methods for accessing and modifying the variable's value
    // ...
};

#endif // VARIABLENODE_H