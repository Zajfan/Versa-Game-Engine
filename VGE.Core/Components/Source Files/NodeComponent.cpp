#include "NodeComponent.h"
#include "Node.h"

NodeComponent::NodeComponent(Node* owner) : m_owner(owner) {}

void NodeComponent::Initialize()
{
    // Default implementation, can be overridden in derived classes
}

void NodeComponent::Terminate()
{
    // Default implementation, can be overridden in derived classes
}

void NodeComponent::Update(float deltaTime)
{
    // Default implementation, can be overridden in derived classes
}