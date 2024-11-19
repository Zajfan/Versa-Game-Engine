#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory> 

#include "Connection.h" 
#include "SceneNodeComponent.h"
#include "ISelectable.h"
#include "Pin.h"

// Define an enum for supported data types
enum class NodeDataType
{
    Int,
    Float,
    Bool,
    String,
    Vector2,
    Vector3,
    // ... other types as needed
};

class Pin
{
public:
    std::string Name;
    NodeDataType DataType; // Use the NodeDataType enum
    // ... other pin-related properties (e.g., connection point location)
};

// Forward declaration of the Event class
class Event;

class Node : public ISelectable
{
public:
    Node(const std::string& name);
    ~Node();

    // Properties
    std::string Name;
    glm::vec2 Position;
    glm::vec2 Size = glm::vec2(100, 50);
    NodeType Type = NodeType::Undefined;
    std::any Data;

    std::vector<std::string> Tags;
    std::map<std::string, std::any> CustomProperties;

    bool IsEnabled = true;
    bool IsVisible = true;

    // Visual Representation and Editor Interaction
    enum class NodeShape { Rectangle, RoundedRectangle, Circle, Custom };
    NodeShape Shape = NodeShape::Rectangle;
    glm::vec3 Color = glm::vec3(1.0f); // Using vec3 for RGB color
    std::string Icon; // Path or ID for the icon image
    std::string Tooltip;
    bool IsCollapsed = false;

    // Execution and Logic
    int ExecutionPriority = 0;
    bool IsBreakpoint = false;
    std::string Condition; // String to store a conditional expression
    // ... (Properties or methods for state management)

    // Node Relationships and Connections
    enum class ConnectionType { Data, Event, Control };
    std::vector<ConnectionType> AllowedConnectionTypes;
    // ... (Properties or methods for dynamic ports)

    // Data and Metadata
    std::string Version;
    std::map<std::string, std::string> UserDefinedMetadata;

    std::vector<Pin> InputPins;
    std::vector<Pin> OutputPins;

    std::chrono::system_clock::time_point CreationTime;
    std::chrono::system_clock::time_point LastModifiedTime;

    Node* Parent = nullptr;
    std::vector<Node*> Children;
    std::vector<Connection*> Connections;

    int Id;
    std::string Comment;

    // Components (using unique_ptr for ownership)
    std::vector<std::unique_ptr<NodeComponent>> Components;

    // Methods
    void AddConnection(Connection* connection);
    void RemoveConnection(Connection* connection);
    std::vector<Node*> GetConnectedNodes();

    // Interface implementations
    virtual bool IsSelected() const override;
    virtual void Select() override;
    virtual void Deselect() override;

    // Node-specific methods (examples)
    virtual void Initialize();
    virtual void Terminate();
    virtual void HandleEvent(Event event);
    virtual void Execute();

    // Type-safe data access methods
    template <typename T>
    T GetData() const
    {
        if (Data.type() == typeid(T))
        {
            return std::any_cast<T>(Data);
        }
        else
        {
            // Handle the case where the type does not match 
            throw std::bad_any_cast();
        }
    }

    template <typename T>
    void SetData(const T& data)
    {
        Data = data;
    }

    // Connection validation
    bool CanConnectTo(Node* otherNode, Pin* myPin, Pin* otherPin) const;

    // Method to add components
    void AddComponent(std::unique_ptr<NodeComponent> component);

    // Templated methods for type-safe data access (New additions)
    template <typename T>
    void SetInputData(const std::string& pinName, const T& value);

    template <typename T>
    T GetOutputData(const std::string& pinName) const;

    // ... (Serialization and Deserialization)
};

#endif // NODE_H