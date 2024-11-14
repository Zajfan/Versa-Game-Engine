#include "Node.h"
#include "NodeData.h"
#include "NodeConnections.h"
#include "NodeExecution.h"
#include "NodeComponent.h"
#include "Event.h"

#include <algorithm>
#include <iostream>
#include <chrono>

// Define the global node ID counter
int g_nodeIdCounter = 0;

// Constructor
Node::Node(const std::string& name) : Name(name),
CreationTime(std::chrono::system_clock::now()),
LastModifiedTime(std::chrono::system_clock::now()),
Id(++g_nodeIdCounter)
{
    // 1. Set default size based on node type
    // ... (same as before)

    // 2. Set default color based on node type
    // ... (same as before)

    // 3. Add default pins based on node type
    // ... (same as before)

    // 4. Set default values for other properties
    // ... (same as before)
}

Node::~Node()
{
    // ... (Potential cleanup logic)
}

// Interface implementations
// ... (IsSelected, Select, Deselect)

void Node::Update(float deltaTime)
{
    if (IsEnabled)
    {
        for (auto& component : Components)
        {
            component->Update(deltaTime);
        }
    }
}

// Node-specific methods
void Node::Initialize()
{
    for (auto& component : Components)
    {
        component->Initialize();
    }
}

void Node::Terminate()
{
    for (auto& component : Components)
    {
        component->Terminate();
    }
}

void Node::HandleEvent(Event event)
{
    for (auto& component : Components)
    {
        component->HandleEvent(event);
    }
}

// Method to add components
void Node::AddComponent(std::unique_ptr<NodeComponent> component)
{
    Components.push_back(std::move(component));
}

void Node::Reset()
{
    CurrentState = ExecutionState::NotExecuted;
    // ... (Reset other state variables as needed)
    // ... (Potentially reset the state of child nodes or components)
}