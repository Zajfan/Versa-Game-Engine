#ifndef ISELECTABLE_H
#define ISELECTABLE_H

class ISelectable
{
public:
    virtual ~ISelectable() = default;
    virtual bool IsSelected() const = 0;
    virtual void Select() = 0;
    virtual void Deselect() = 0;
};

#endif // ISELECTABLE_H
