#include "RenderComponent.h"
#include "Node.h"
#include <memory>
#include <string>

namespace VGE
{
	RenderComponent::RenderComponent()
	{
	}

    void RenderComponent::Update(float deltaTime)
    {
        // Example implementation: Update the component's state
        // For instance, you might want to update the position or other properties
        // based on deltaTime. This is a placeholder example.
        if (m_Node)
        {
            // Update the node's state or properties
            // Example: m_Node->UpdateTransform(deltaTime);
        }
    }

    void RenderComponent::Render()
    {
        // Example implementation: Render the component
        // This could involve setting up rendering states, shaders, etc.
        if (m_Node)
        {
            // Render the node or its associated graphics
            // Example: m_Node->Render();
        }
    }
}
