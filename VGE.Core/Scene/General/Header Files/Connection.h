#ifndef CONNECTION_H
#define CONNECTION_H

#include "Node.h"
#include "Pin.h"

class Connection
{
public:
    Node* Source = nullptr;
    Node* Target = nullptr;

    Pin* SourcePin = nullptr;
    Pin* TargetPin = nullptr;

    // ... (You might have other properties here, e.g., for connection type, color, etc.)

    bool IsValid() const;

private:
    bool IsCircularConnection() const;
};

#endif // CONNECTION_H