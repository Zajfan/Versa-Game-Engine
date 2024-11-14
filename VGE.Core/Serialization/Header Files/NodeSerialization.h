#ifndef NODE_SERIALIZATION_H
#define NODE_SERIALIZATION_H

#include "Node.h"
#include "NodeSerializer.h"
#include "NodeDeserializer.h"

class NodeSerialization
{
public:
    static void Serialize(Node& node, NodeSerializer& serializer);
    static void Deserialize(Node& node, NodeDeserializer& deserializer);
};

#endif // NODE_SERIALIZATION_H
// Compare this snippet from Versa Game Engine Core/Scene/Source Files/NodeSerialization.cpp: