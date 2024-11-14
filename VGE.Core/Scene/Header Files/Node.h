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
#include "NodeDataType.h"

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

    // ... (Properties from NodeVisuals.h, NodeExecution.h, NodeConnections.h, NodeData.h, NodeState.h)

    // ... (CreationTime, LastModifiedTime, Parent, Children, Connections, Id, Comment, Components)

    // Methods
    void AddComponent(std::unique_ptr<NodeComponent> component);
    void RemoveComponent(const std::string& type);
    NodeComponent* GetComponent(const std::string& type) const;

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

    // ... (Serialization and Deserialization - declarations will be in NodeSerialization.h)
};

#endif // NODE_H