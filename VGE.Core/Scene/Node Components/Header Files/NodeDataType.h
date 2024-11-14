#ifndef NODEDATATYPE_H
#define NODEDATATYPE_H

// This file defines the data types and node types that can be used in a visual scripting system.
// You can add more data types and node types as needed for your specific visual scripting system.
// The data types are used to define the type of data that can be passed between nodes.
// The node types are used to define the type of nodes that can be created in the visual scripting system.

// Define an enum for supported data types in your visual scripting system
enum class NodeDataType
{
    Undefined,        // For undefined or generic data types
    Integer,         // Integer values
    Float,           // Floating-point values
    Boolean,         // Boolean values (true/false)
    String,          // Text strings
    Vector2,         // 2D vectors
    Vector3,         // 3D vectors
    Color,           // Color values (e.g., RGB)
    ObjectReference, // References to game objects or assets
    // ... add other data types as needed
};

// Define an enum for node types
enum class NodeType
{
    Undefined,
    Input,
    Output,
    Process,
	Condition,
	Loop,
	Comment,
	Group,
	CommentGroup,
    // ... add other node types as needed
};

#endif // NODEDATATYPE_H
