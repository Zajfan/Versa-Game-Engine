#pragma once
#ifndef VGE_CORE_SCRIPTING_GRAPHCONNECTION_H
#define VGE_CORE_SCRIPTING_GRAPHCONNECTION_H

#include "GraphNode.h"
#include "GraphPin.h"

class Node;
class Pin;

class Connection {
public:
    Node* Source = nullptr;
    Node* Target = nullptr;

    Pin* SourcePin = nullptr;
    Pin* TargetPin = nullptr;

    // ... (You might have other properties here, e.g., for connection type, color, etc.)

    bool IsValid() const;

private:
    bool IsCircularConnection() const;
};

#endif // VGE_CORE_SCRIPTING_GRAPHCONNECTION_H
