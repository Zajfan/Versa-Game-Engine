// DataTypeUtils.h

#ifndef DATATYPEUTILS_H
#define DATATYPEUTILS_H

#include "Node.h" // Include the Node.h header to access NodeDataType

template <typename T>
NodeDataType GetNodeDataType()
{
    if constexpr (std::is_same_v<T, int>)
        return NodeDataType::Int;
    else if constexpr (std::is_same_v<T, float>)
        return NodeDataType::Float;
    else if constexpr (std::is_same_v<T, bool>)
        return NodeDataType::Bool;
    else if constexpr (std::is_same_v<T, std::string>)
        return NodeDataType::String;
    else if constexpr (std::is_same_v<T, glm::vec2>)
        return NodeDataType::Vector2;
    else if constexpr (std::is_same_v<T, glm::vec3>)
        return NodeDataType::Vector3;
    // ... add cases for other types as needed
    else
        static_assert(false, "Unsupported type for NodeDataType"); // Trigger a compile-time error for unsupported types
}

#endif // DATATYPEUTILS_H