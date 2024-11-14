#ifndef NODECOMPONENT_H
#define NODECOMPONENT_H

#include <string>
#include "Event.h"

class Node;

class NodeComponent
{
public:
    NodeComponent(Node* owner);
    virtual ~NodeComponent() = default;

    virtual void Initialize();
    virtual void Terminate();
    virtual void Update(float deltaTime);
    virtual void HandleEvent(const Event& event);
    virtual std::string GetType() const = 0;

    virtual void Execute();
    virtual void Reset();

protected:
    Node* m_owner; // Pointer to the owning Node
};

#endif // NODECOMPONENT_H
