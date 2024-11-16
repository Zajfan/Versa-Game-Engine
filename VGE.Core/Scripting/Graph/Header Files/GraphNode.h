#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <map>
#include <any>
#include <chrono>
#include <memory>
#include <glm/glm.hpp>

#include "Connection.h"
#include "NodeComponent.h"
#include "Event.h"
#include "ISelectable.h"
#include "Pin.h"

// Node includes
#include "NodeDataType.h"
#include "NodeVisuals.h"
#include "NodeExecution.h"
#include "NodeConnections.h"
#include "NodeData.h"
#include "NodeStates.h"

class Node : public ISelectable
{
public:
    Node(const std::string& name);
    ~Node();

    // Properties - Basic
    std::string Name;
    glm::vec2 Position;
    glm::vec2 Size;
    NodeType Type = NodeType::Undefined;
    std::any Data;
    std::vector<std::string> Tags;
    std::map<std::string, std::any> CustomProperties;
    bool IsEnabled = true;
    bool IsVisible = true;

    // Properties from NodeVisuals.h
    std::string VisualStyle;
    std::string Color;

    // Properties from NodeExecution.h
    bool IsExecuting;
    std::chrono::time_point<std::chrono::steady_clock> ExecutionStartTime;

    // Properties from NodeConnections.h
    std::vector<Connection> InputConnections;
    std::vector<Connection> OutputConnections;

    // Properties from NodeData.h
    std::map<std::string, std::any> NodeData;
    std::vector<Pin> InputPins;
    std::vector<Pin> OutputPins;

    // Properties from NodeState.h
    bool IsActive;
    bool IsDirty;

    // Additional properties
    std::chrono::time_point<std::chrono::steady_clock> CreationTime;
    std::chrono::time_point<std::chrono::steady_clock> LastModifiedTime;
    Node* Parent;
    std::vector<Node*> Children;
    std::vector<Connection> Connections;
    std::string Id;
    std::string Comment;
	std::vector<std::string> Tags;
	std::map<std::string, std::any> CustomProperties;
	std::vector<Pin> InputPins;
	std::vector<Pin> OutputPins;
    std::vector<std::unique_ptr<NodeComponent>> Components;

    // Methods
    void AddComponent(std::unique_ptr<NodeComponent> component);
    void RemoveComponent(const std::string& type);
    NodeComponent* GetComponent(const std::string& type) const;
    void Execute();
    void Reset();
    void AddConnection(const Connection& connection);
    void RemoveConnection(const Connection& connection);
    void RemoveConnection(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void RemoveAllConnections();
    void AddChild(Node* child);
    void RemoveChild(Node* child);
    void RemoveAllChildren();
    void AddTag(const std::string& tag);
    void RemoveTag(const std::string& tag);
    void RemoveAllTags();
    void AddCustomProperty(const std::string& name, const std::any& value);
    void RemoveCustomProperty(const std::string& name);
    void RemoveAllCustomProperties();
    void SetData(const std::any& data);
    std::any GetData() const;
    void SetPosition(const glm::vec2& position);
    glm::vec2 GetPosition() const;
    void SetSize(const glm::vec2& size);
    glm::vec2 GetSize() const;
    void SetType(NodeType type);
    NodeType GetType() const;
    void SetName(const std::string& name);
    std::string GetName() const;
    void SetComment(const std::string& comment);
    std::string GetComment() const;
    void SetColor(const std::string& color);
    std::string GetColor() const;
    void SetVisualStyle(const std::string& style);
    std::string GetVisualStyle() const;
    void SetEnabled(bool enabled);
    bool IsEnabled() const;
    void SetVisible(bool visible);
    bool IsVisible() const;
    void SetActive(bool active);
    bool IsActive() const;
    void SetDirty(bool dirty);
    bool IsDirty() const;
    void SetExecuting(bool executing);
    bool IsExecuting() const;
    void SetCreationTime(const std::chrono::time_point<std::chrono::steady_clock>& time);
    std::chrono::time_point<std::chrono::steady_clock> GetCreationTime() const;
    void SetLastModifiedTime(const std::chrono::time_point<std::chrono::steady_clock>& time);
    std::chrono::time_point<std::chrono::steady_clock> GetLastModifiedTime() const;
    void SetParent(Node* parent);
    Node* GetParent() const;
    void AddInputConnection(const Connection& connection);
    void RemoveInputConnection(const Connection& connection);
    void RemoveInputConnection(Node* sourceNode, const std::string& outputPin, const std::string& inputPin);
    void RemoveAllInputConnections();
    void AddOutputConnection(const Connection& connection);
    void RemoveOutputConnection(const Connection& connection);
    void RemoveOutputConnection(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void RemoveAllOutputConnections();
    void AddConnection(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void RemoveConnection(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void RemoveAllConnections();
    void AddChild(Node* child);
    void RemoveChild(Node* child);
    void RemoveAllChildren();
    void AddTag(const std::string& tag);
    void RemoveTag(const std::string& tag);
    void RemoveAllTags();
    void AddCustomProperty(const std::string& name, const std::any& value);
    void RemoveCustomProperty(const std::string& name);
    void RemoveAllCustomProperties();

    void AddInputPin(const std::string& name, NodeDataType type);
    void AddOutputPin(const std::string& name, NodeDataType type);
    void RemoveInputPin(const std::string& name);
    void RemoveOutputPin(const std::string& name);
    Pin* GetInputPin(const std::string& name) const;
    Pin* GetOutputPin(const std::string& name) const;
    std::vector<Pin> GetInputPins() const;
    std::vector<Pin> GetOutputPins() const;
    void SetInputData(const std::string& pinName, const std::any& value);
    std::any GetOutputData(const std::string& pinName) const;
    bool IsValidInput(const std::string& pinName, const std::any& value) const;
    bool IsValidOutput(const std::string& pinName) const;
    void ConnectTo(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void DisconnectFrom(Node* targetNode, const std::string& outputPin, const std::string& inputPin);
    void DisconnectFromAll();
    void UpdateConnections();
    void UpdateExecutionState();
    void UpdateVisuals();
    void UpdateData();
    void UpdateState();
    void UpdateComponents();
    void UpdateChildren();
    void UpdateParent();
    void UpdateHierarchy();
    void UpdateTags();
    void UpdateCustomProperties();
    void UpdatePosition();
    void UpdateSize();
    void UpdateColor();
    void UpdateVisualStyle();
    void UpdateName();
    void UpdateComment();

    // Interface implementations
    virtual bool IsSelected() const override;
    virtual void Select() override;
    virtual void Deselect() override;

    // Node-specific methods
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    void Render(/* ... graphics context */);
    void HandleEvent(Event event);
	void Execute();
	void Reset();

    // ... (Serialization and Deserialization - declarations will be in NodeSerialization.h)
};

#endif // NODE_H