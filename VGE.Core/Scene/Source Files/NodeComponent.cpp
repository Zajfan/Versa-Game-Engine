#include "NodeComponent.h"
#include "Event.h"

NodeComponent::NodeComponent(Node* owner) : m_owner(owner) {}

void NodeComponent::Initialize() {
    // Initialization logic
}

void NodeComponent::Terminate() {
    // Termination logic
}

void NodeComponent::Update(float deltaTime) {
    // Update logic
}

void NodeComponent::HandleEvent(const Event& event) {
    // Handle event logic
}
