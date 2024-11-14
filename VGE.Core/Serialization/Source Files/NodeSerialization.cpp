#include "NodeSerialization.h"

void NodeSerialization::Serialize(Node& node, NodeSerializer& serializer)
{
    serializer.Serialize("Name", node.m_Name);
    serializer.Serialize("Position", node.m_Position);
    serializer.Serialize("Rotation", node.m_Rotation);
    serializer.Serialize("Scale", node.m_Scale);
    serializer.Serialize
    (
        "Components",
        node.m_Components,
        [](NodeSerializer& componentSerializer, std::shared_ptr<Component>& component)
        {
            component->Serialize(componentSerializer);
        }
    );
    serializer.Serialize
    (
        "Children",
        node.m_Children,
        [](NodeSerializer& childSerializer, std::shared_ptr<Node>& child)
        {
            child->Serialize(childSerializer);
        }
    );
}

void NodeSerialization::Deserialize(Node& node, NodeDeserializer& deserializer)
{
    deserializer.Deserialize("Name", node.m_Name);
    deserializer.Deserialize("Position", node.m_Position);
    deserializer.Deserialize("Rotation", node.m_Rotation);
    deserializer.Deserialize("Scale", node.m_Scale);
    deserializer.Deserialize
    (
        "Components",
        node.m_Components,
        [&node](NodeDeserializer& componentDeserializer, std::shared_ptr<Component>& component)
        {
            component = std::make_shared<Component>();
            component->Deserialize(componentDeserializer);
            component->SetNode(node.shared_from_this());
        }
    );
    deserializer.Deserialize
    (
        "Children",
        node.m_Children,
        [&node](NodeDeserializer& childDeserializer, std::shared_ptr<Node>& child)
        {
            child = std::make_shared<Node>();
            child->Deserialize(childDeserializer);
            child->SetParent(node.shared_from_this());
        }
    );

    // Update the transform based on position, rotation, and scale
    node.m_Transform = glm::translate(glm::mat4(1.0f), node.m_Position) * glm::mat4_cast(node.m_Rotation) * glm::scale(glm::mat4(1.0f), node.m_Scale);

    // Update the world transform based on parent's world transform
    if (auto parent = node.m_Parent.lock())
    {
        node.m_WorldTransform = parent->GetWorldTransform() * node.m_Transform;
    }
    else
    {
        node.m_WorldTransform = node.m_Transform;
    }

    // Deserialize custom properties
    for (auto& [key, value] : node.CustomProperties)
    {
        deserializer.Deserialize(key, value);
    }

    // Deserialize other properties
    deserializer.Deserialize("IsEnabled", node.IsEnabled);
    deserializer.Deserialize("IsVisible", node.IsVisible);
    deserializer.Deserialize("Tags", node.Tags);

    // Deserialize data
    deserializer.Deserialize("Data", node.Data);

    // Deserialize creation and last modified times
    deserializer.Deserialize("CreationTime", node.CreationTime);
    deserializer.Deserialize("LastModifiedTime", node.LastModifiedTime);

    // Deserialize ID
    deserializer.Deserialize("Id", node.Id);

    // Deserialize color
    deserializer.Deserialize("Color", node.Color);

    // Deserialize size
    deserializer.Deserialize("Size", node.Size);

    // Deserialize pins
    deserializer.Deserialize("InputPorts", node.InputPorts);
    deserializer.Deserialize("OutputPorts", node.OutputPorts);

    // Deserialize type
    deserializer.Deserialize("Type", node.Type);

    // Deserialize description
    deserializer.Deserialize("Description", node.CustomProperties["Description"]);

    // Deserialize other custom properties
    for (auto& [key, value] : node.CustomProperties)
    {
        deserializer.Deserialize(key, value);
    }
}
