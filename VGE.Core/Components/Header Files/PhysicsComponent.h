#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#include "NodeComponent.h"

class PhysicsComponent : public NodeComponent
{
public:
    PhysicsComponent(Node* owner);

    // Properties specific to physics (e.g., mass, velocity, collision shape)
    // ...

    // Methods for physics simulation, collision handling, etc.
    // ...
};

#endif // PHYSICSCOMPONENT_H#pragma once
