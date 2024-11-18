#ifndef IRenderable_H
#define IRenderable_H

class IRenderable
{
public:
    virtual ~IRenderable() = default;

    // Pure virtual function to be implemented by derived classes
    virtual void Render() = 0;
};

#endif // IRenderable_H
