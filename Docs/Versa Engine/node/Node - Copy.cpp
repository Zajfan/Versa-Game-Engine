#include "Node.h"
#include <algorithm>
#include <stdexcept> // For std::runtime_error
#include "DataTypeUtils.h"

// Global node ID counter
int g_nodeIdCounter = 0; // Initialize a global counter for node IDs

// Constructor
Node::Node(const std::string& name) : Name(name),
CreationTime(std::chrono::system_clock::now()),
LastModifiedTime(std::chrono::system_clock::now()),
Id(++g_nodeIdCounter)
{
    // Initialize other properties here

    // 1. Set default size based on node type
    switch (Type)
    {
    case NodeType::Event:
        Size = glm::vec2(150, 80);
        break;
    case NodeType::Variable:
        Size = glm::vec2(120, 60);
        break;
    case NodeType::Function:
        Size = glm::vec2(200, 100);
        break;
    default:
        Size = glm::vec2(100, 50);
        break;
    }

    // 2. Set default color based on node type
    switch (Type)
    {
    case NodeType::Event:
        Color = glm::vec3(0.8f, 0.6f, 0.2f);
        break;
    case NodeType::Variable:
        Color = glm::vec3(0.2f, 0.8f, 0.6f);
        break;
    case NodeType::Function:
        Color = glm::vec3(0.6f, 0.2f, 0.8f);
        break;
    default:
        Color = glm::vec3(1.0f);
        break;
    }

    // 3. Add default pins based on node type
    if (Type == NodeType::Variable)
    {
        Pin outputPin;
        outputPin.Name = "Value";
        outputPin.DataType = NodeDataType::Float;
        OutputPins.push_back(outputPin);
    }
    else if (Type == NodeType::Function)
    {
        Pin inputPin;
        inputPin.Name = "Input";
        inputPin.DataType = NodeDataType::Float;
        InputPins.push_back(inputPin);

        Pin outputPin;
        outputPin.Name = "Output";
        outputPin.DataType = NodeDataType::Float;
        OutputPins.push_back(outputPin);
    }

    // 4. Set default values for other properties if needed

    // Example: Set a default tooltip based on node type
    switch (Type)
    {
    case NodeType::Event:
        Tooltip = "Triggers an event.";
        break;
    case NodeType::Variable:
        Tooltip = "Stores a value.";
        break;
    case NodeType::Function:
        Tooltip = "Executes a function.";
        break;
    default:
        Tooltip = "A node in the graph.";
        break;
    }

    // Example: Set IsCollapsed based on node type
    if (Type == NodeType::Function)
    {
        IsCollapsed = true;
    }

    // Example: Set ExecutionPriority based on node type
    if (Type == NodeType::Event)
    {
        ExecutionPriority = 1;
    }

    // ... (Add initialization for other properties as needed)
}

Node::~Node()
{
    // You might want to add cleanup logic here in the future
    // For example, releasing resources held by the node
}

// Methods for managing connections
void Node::AddConnection(Connection* connection)
{
    Connections.push_back(connection);
}

void Node::RemoveConnection(Connection* connection)
{
    // Find and remove the connection from the vector
    auto it = std::find(Connections.begin(), Connections.end(), connection);
    if (it != Connections.end())
    {
        Connections.erase(it);
    }
}

std::vector<Node*> Node::GetConnectedNodes()
{
    std::vector<Node*> connectedNodes;
    for (auto connection : Connections)
    {
        if (connection->Source == this)
        {
            connectedNodes.push_back(connection->Target);
        }
        else if (connection->Target == this)
        {
            connectedNodes.push_back(connection->Source);
        }
    }
    return connectedNodes;
}

// Interface implementations
void Node::Render(/* ... graphics context */)
{
    if (IsVisible)
    {
        for (auto& component : Components)
        {
            // Use dynamic_cast to check if the component is renderable
            if (auto* renderable = dynamic_cast<IRenderable*>(component.get()))
            {
                renderable->Render(/* ... graphics context */);
            }
        }
    }
}

bool Node::IsSelected() const
{
    // TODO: Implement selection logic (e.g., check if the node is in a selected state)
    return false;
}

void Node::Select()
{
    // TODO: Implement selection logic (e.g., set a flag to indicate selection, update visual appearance)
}

void Node::Deselect()
{
    // TODO: Implement deselection logic (e.g., clear the selection flag, update visual appearance)
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
        // You might need a more specific event handling mechanism here
        // depending on your event system design
        component->HandleEvent(event);
    }
}

void Node::Execute()
{
    // Check if the node has a condition and evaluate it
    if (!Condition.empty())
    {
        // TODO: Implement condition evaluation logic
        // If the condition is false, skip execution
    }

    for (auto& component : Components)
    {
        // You might need a more specific execution mechanism here
        // depending on your visual scripting design
        component->Execute();
    }
}

bool Node::CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const
{
    // Check if connection types are compatible
    if (std::find(AllowedConnectionTypes.begin(), AllowedConnectionTypes.end(), otherNode->Type) == AllowedConnectionTypes.end())
    {
        return false;
    }

    // Check if pin data types are compatible
    if (myPin->DataType != otherPin->DataType)
    {
        return false;
    }

    // ... other connection validation logic (e.g., prevent circular connections)

    return true;
}

// Serialization and Deserialization
// (You'll need to implement these using your chosen XML serialization library)
std::string Node::Serialize() const
{
    // TODO: Implement serialization logic using TinyXML2 or your preferred library
    return ""; // Placeholder
}

void Node::Deserialize(const std::string& xmlData)
{
    // TODO: Implement deserialization logic using TinyXML2 or your preferred library
}

// Method to add components
void Node::AddComponent(std::unique_ptr<NodeComponent> component)
{
    Components.push_back(std::move(component));
}

// Templated methods for type-safe data access
template <typename T>
void Node::SetInputData(const std::string& pinName, const T& value)
{
    // 1. Find the input pin with the given name
    auto it = std::find_if(InputPins.begin(), InputPins.end(),
        [&](const Pin& pin) { return pin.Name == pinName; });

    if (it != InputPins.end())
    {
        // 2. Check if the pin's data type matches the type of 'value'
        if (it->DataType == GetNodeDataType<T>())
        {
            // 3. If the types match, store the value in the pin's data
            it->Data = value;
        }
        else
        {
            // 4. If the types don't match, handle the error
            throw std::runtime_error("Input data type mismatch for pin: " + pinName);
        }
    }
    else
    {
        // Handle the case where the pin is not found
        throw std::runtime_error("Output pin not found: " + pinName);
    }
}

// ... (You'll likely need to implement serialization and deserialization methods here
//      using your chosen XML serialization library)