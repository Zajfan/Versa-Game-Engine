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
    // Initialize the node with default values

    // 1. Set default size based on node type
    SetSize(glm::vec2(100.0f, 100.0f)); // Example default size

    // 2. Set default color based on node type
    SetColor("white"); // Example default color

    // 3. Add default pins based on node type
    AddInputPin("DefaultInput", NodeDataType::Float);
    AddOutputPin("DefaultOutput", NodeDataType::Float);

    // 4. Set default values for other properties
    Comment = "Default comment";
    VisualStyle = "Default style";
	IsActive = true;
	IsDirty = false;
	IsExecuting = false;
}

Node::~Node()
{
    // ... Cleanup logic

	// Delete all child nodes
	for (auto child : Children)
	{
		delete child;
	}

	// Clear the list of child nodes
	Children.clear();

}

// Interface implementations
void Node::Select()
{
	// ... (Select the node)
}

void Node::Deselect()
{
	// ... (Deselect the node)
}

bool Node::IsSelected() const
{
	// ... (Check if the node is selected)
	return false;
}

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

	// Reset the state of all child nodes
	for (auto child : Children)
	{
		child->Reset();
	}

	// Reset the state of all components
	for (auto& component : Components)
	{
		component->Reset();
	}
}