#ifndef SPECIFICCOMPONENT_H
#define SPECIFICCOMPONENT_H

#include "NodeComponent.h"

class SpecificComponent : public NodeComponent
{
public:
    SpecificComponent(Node* owner);
    virtual ~SpecificComponent() = default;

    virtual std::string GetType() const override;
	virtual void Update(float deltaTime) override;

    // Other methods...
};

#endif // SPECIFICCOMPONENT_H
