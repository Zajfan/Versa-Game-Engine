#ifndef RenderComponent_H
#define RenderComponent_H

#include "NodeComponent.h"
#include "IRenderable.h"

class RenderComponent : public NodeComponent, public IRenderable
{
public:
    RenderComponent(Node* owner);

    // Properties specific to rendering (e.g., color, shape, texture)
    // ...

    // IRenderable implementation
    virtual void Render(/* ... graphics context */) override;

    // Other methods related to rendering
    // ...
};

#endif // RenderComponent_H