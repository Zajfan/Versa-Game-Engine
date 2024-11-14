#include "SpecificComponent.h"

SpecificComponent::SpecificComponent(Node* owner)
    : NodeComponent(owner)
{
}

std::string SpecificComponent::GetType() const
{
    return "SpecificComponent"; // Return the type as a string
}
